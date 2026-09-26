#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
#include <EEPROM.h>

// Initialize I2C LCD at address 0x20 (all address pins grounded)
LiquidCrystal_I2C lcd(0x20, 20, 4); 
RTC_DS1307 rtc;

// Hardware Pin Definitions
const int SLOT1_SENSOR = 6;  // PD6
const int SLOT2_SENSOR = 7;  // PD7

const int LED1_PIN1 = 8;     // PB0 (Slot 1 LED Leg 1)
const int LED1_PIN2 = 9;     // PB1 (Slot 1 LED Leg 2)
const int LED2_PIN1 = 10;    // PB2 (Slot 2 LED Leg 1)
const int LED2_PIN2 = 11;    // PB3 (Slot 2 LED Leg 2)

// Global State Variables
bool lastSlot1State = true; 
bool lastSlot2State = true;
uint32_t slot1EntryTime = 0;
uint32_t slot2EntryTime = 0;

const float HOURLY_RATE = 2.0; // Fee per hour

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Configure Sensor Inputs
  pinMode(SLOT1_SENSOR, INPUT_PULLUP);
  pinMode(SLOT2_SENSOR, INPUT_PULLUP);
  
  // Configure 2-Pin LED Outputs
  pinMode(LED1_PIN1, OUTPUT);
  pinMode(LED1_PIN2, OUTPUT);
  pinMode(LED2_PIN1, OUTPUT);
  pinMode(LED2_PIN2, OUTPUT);

  // Initialize display
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" SMART PARKING LOT ");
  lcd.setCursor(0, 1);
  lcd.print(" INITIALIZING SYSTEM");

  if (!rtc.begin()) {
    Serial.println("Error: RTC not found!");
    lcd.setCursor(0, 2);
    lcd.print("RTC Error!");
  }
  
  // Set default initial state (Green = Available)
  setLEDColor(1, true);
  setLEDColor(2, true);
  delay(1500);
  lcd.clear();
}

void loop() {
  DateTime now = rtc.now();
  
  // Read raw inputs (0 = Car present, 1 = Empty)
  bool currentSlot1 = digitalRead(SLOT1_SENSOR);
  bool currentSlot2 = digitalRead(SLOT2_SENSOR);
  
  // --- SLOT 1 LOGIC CHANGES ---
  if (currentSlot1 != lastSlot1State) {
    if (currentSlot1 == LOW) { // Car Just Arrived
      slot1EntryTime = now.unixtime();
      setLEDColor(1, false); // Turn Red
      Serial.print("Slot 1 Occupied at: ");
      printTime(now);
    } else { // Car Just Left
      uint32_t exitTime = now.unixtime();
      setLEDColor(1, true); // Turn Green
      calculateAndPrintBill(1, slot1EntryTime, exitTime);
    }
    lastSlot1State = currentSlot1;
  }

  // --- SLOT 2 LOGIC CHANGES ---
  if (currentSlot2 != lastSlot2State) {
    if (currentSlot2 == LOW) { // Car Just Arrived
      slot2EntryTime = now.unixtime();
      setLEDColor(2, false); // Turn Red
      Serial.print("Slot 2 Occupied at: ");
      printTime(now);
    } else { // Car Just Left
      uint32_t exitTime = now.unixtime();
      setLEDColor(2, true); // Turn Green
      calculateAndPrintBill(2, slot2EntryTime, exitTime);
    }
    lastSlot2State = currentSlot2;
  }

  // --- REFRESH LCD DISPLAY PANEL ---
  int totalAvailable = (currentSlot1 == HIGH ? 1 : 0) + (currentSlot2 == HIGH ? 1 : 0);
  
  lcd.setCursor(0, 0);
  lcd.print("--- PARKING LIVE ---");
  
  lcd.setCursor(0, 1);
  lcd.print("Slot 1: ");
  lcd.print(currentSlot1 == HIGH ? "AVAILABLE" : "OCCUPIED ");
  
  lcd.setCursor(0, 2);
  lcd.print("Slot 2: ");
  lcd.print(currentSlot2 == HIGH ? "AVAILABLE" : "OCCUPIED ");
  
  lcd.setCursor(0, 3);
  lcd.print("Total Spots Free: ");
  lcd.print(totalAvailable);
  
  delay(200); // Small delay to optimize simulation stability
}

// Function to control 2-pin reversible bi-color LEDs
void setLEDColor(int slot, bool available) {
  if (slot == 1) {
    if (available) { // Green
      digitalWrite(LED1_PIN1, LOW);
      digitalWrite(LED1_PIN2, HIGH);
    } else { // Red
      digitalWrite(LED1_PIN1, HIGH);
      digitalWrite(LED1_PIN2, LOW);
    }
  } else if (slot == 2) {
    if (available) { // Green
      digitalWrite(LED2_PIN1, LOW);
      digitalWrite(LED2_PIN2, HIGH);
    } else { // Red
      digitalWrite(LED2_PIN1, HIGH);
      digitalWrite(LED2_PIN2, LOW);
    }
  }
}

// Billing Math Engine
void calculateAndPrintBill(int slot, uint32_t entry, uint32_t exit) {
  uint32_t durationSeconds = exit - entry;
  
  // For simulation purposes, treat 5 seconds as 1 hour so you don't have to wait!
  float hours = (float)durationSeconds / 5.0; 
  if (hours < 0.1) hours = 0.1; // Baseline minimum format
  
  float totalBill = hours * HOURLY_RATE;
  
  Serial.println("\n==============================");
  Serial.print("        EXIT BILL RECIEPT      \n");
  Serial.println("==============================");
  Serial.print("Vacated Slot: "); Serial.println(slot);
  Serial.print("Duration (Sim Hours): "); Serial.println(hours, 2);
  Serial.print("Rate Per Hour: $"); Serial.println(HOURLY_RATE, 2);
  Serial.print("TOTAL CHARGES: $"); Serial.println(totalBill, 2);
  Serial.println("==============================\n");
}

void printTime(DateTime t) {
  Serial.print(t.hour()); Serial.print(":");
  Serial.print(t.minute()); Serial.print(":");
  Serial.println(t.second());
}


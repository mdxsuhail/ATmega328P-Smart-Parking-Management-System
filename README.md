# 🚗 ATmega328P Smart Parking System

A microcontroller-based **Smart Parking System** developed using the **ATmega328P**. The system monitors parking slot occupancy in real time, displays slot availability on a 20×4 LCD, provides visual status through LEDs, records entry time using a DS1307 RTC, and calculates parking charges when a vehicle leaves.

---

## 📌 Project Overview

The Smart Parking System is designed to monitor two parking slots.

Each slot can have two states:

- 🟢 **AVAILABLE** – No vehicle detected
- 🔴 **OCCUPIED** – Vehicle detected

The ATmega328P continuously monitors the parking slots and updates the LCD display accordingly.

The system also uses a **DS1307 Real-Time Clock (RTC)** to record vehicle entry and exit times. When a vehicle leaves a slot, the system calculates the parking duration and generates a simulated parking bill through the Serial Monitor.

---

## ✨ Features

- 🚗 Real-time parking slot monitoring
- 🅿️ Two parking slots
- 🟢 Green indication for available slots
- 🔴 Red indication for occupied slots
- 📟 20×4 I²C LCD display
- 🕐 DS1307 Real-Time Clock
- 💰 Automatic parking fee calculation
- 📡 Serial Monitor billing output
- 🔄 Real-time availability counter
- ⚡ ATmega328P-based embedded system

---

## 🖥️ System Display

The LCD continuously displays the current parking status:

```text
--- PARKING LIVE ---
Slot 1: AVAILABLE
Slot 2: OCCUPIED
Total Spots Free: 1
``` 
The number of available spaces is automatically updated whenever the parking-slot state changes.
## 🏗️ System Architecture
                          ┌─────────────────────┐
             │   Parking Sensors   │
             │                     │
             │   Slot 1   Slot 2   │
             └──────────┬──────────┘
                        │
                        ▼
              ┌──────────────────┐
              │    ATmega328P    │
              │                  │
              │ Slot Monitoring  │
              │ Time Management  │
              │ Billing Logic    │
              └───────┬──────────┘
                      │
          ┌───────────┼────────────┐
          │           │            │
          ▼           ▼            ▼
    ┌──────────┐ ┌──────────┐ ┌──────────┐
    │ 20×4 LCD │ │  DS1307  │ │   LEDs   │
    │ Display  │ │   RTC    │ │ R / G    │
    └──────────┘ └──────────┘ └──────────┘
                      │
                      ▼
               ┌─────────────┐
               │   Billing   │
               │ Calculation │
               └─────────────┘
``
##🔧 Hardware Components
Component	Quantity
ATmega328P	1
20×4 LCD	1
PCF8574 I²C LCD Interface	1
DS1307 RTC	1
Crystal	1
Parking Slot Sensors	2
Bi-color LEDs	2
Resistors	3
Serial/COMPIM Interface	1
Power Supply	1
📸 Circuit & Simulation
🔌 Complete Circuit Diagram

The complete Proteus circuit contains the ATmega328P controller, DS1307 RTC, LCD interface, parking indicators, and serial communication interface.

🅿️ Case 1 — One Parking Slot Occupied

When one vehicle occupies a parking slot, the LCD updates the slot status and shows that one parking space remains available.

Example Display
--- PARKING LIVE ---
Slot 1: OCCUPIED
Slot 2: AVAILABLE
Total Spots Free: 1
🅿️🅿️ Case 2 — Both Parking Slots Occupied

When both parking slots are occupied, the system displays zero available spaces.

Example Display
--- PARKING LIVE ---
Slot 1: OCCUPIED
Slot 2: OCCUPIED
Total Spots Free: 0
🕐 Real-Time Clock

A DS1307 RTC is used to obtain the current date and time.

The RTC allows the system to record:

Vehicle entry time
Vehicle exit time
Parking duration

The system uses the DS1307 RTC for time-based parking management.

💰 Parking Fee Calculation

The system calculates the parking charge when a vehicle leaves a slot.

The current program uses:

const float HOURLY_RATE = 2.0;

For simulation purposes, the program treats:

5 seconds = 1 simulated hour

This allows parking billing to be demonstrated quickly without waiting for an actual hour.

Billing Example
==============================
        EXIT BILL RECEIPT
==============================
Vacated Slot: 1
Duration (Sim Hours): 2.00
Rate Per Hour: $2.00
TOTAL CHARGES: $4.00
==============================

The billing rate and simulation time can be changed in the source code.

🔴🟢 LED Status

Each parking slot uses a two-pin bi-color LED.

🟢 Green
Slot Available
🔴 Red
Slot Occupied

The ATmega328P changes the LED state whenever a vehicle enters or leaves a parking slot.

🔄 Working Principle
The system starts and initializes the ATmega328P peripherals.
The LCD displays the system initialization message.
The DS1307 RTC is initialized.
Both parking slots initially indicate availability.
The sensors continuously monitor both slots.
When a vehicle enters a slot:
The slot becomes OCCUPIED.
The corresponding LED changes to RED.
The entry time is recorded.
When the vehicle leaves:
The slot becomes AVAILABLE.
The corresponding LED changes to GREEN.
The exit time is recorded.
Parking duration is calculated.
The parking bill is printed through the Serial Monitor.
The LCD continuously displays the current parking status.
💻 Software

The project is programmed using Arduino-compatible C/C++.

Libraries Used
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
#include <EEPROM.h>
Main Software Functions
Parking slot monitoring
LCD display control
RTC time management
LED status control
Parking duration calculation
Parking fee calculation
Serial billing output
📂 Repository Structure
ATmega328P-Smart-Parking-System/
│
├── README.md
│
├── sketch_sep26a.ino
│
├── Circuit Diagram.pdf
│
├── Case01-when one parking spot is ocuppied.png
│
└── case02-when both are occupied.png
🛠️ Tools Used
Arduino IDE
Proteus Design Suite
ATmega328P
Embedded C/C++
Serial Monitor
🎯 Learning Objectives

This project demonstrates:

ATmega328P microcontroller programming
Digital input and output
I²C communication
LCD interfacing
RTC interfacing
Real-time monitoring
Sensor-based parking detection
LED status indication
Time-based billing
Embedded-system design
🚀 Future Improvements

Possible future improvements include:

Increase the number of parking slots
Add RFID-based vehicle identification
Add automatic barrier control
Add mobile/web-based parking monitoring
Add ultrasonic parking detection
Add online payment integration
Store vehicle and billing records
Add a parking reservation system
## 👨‍💻 Author

Mohammed Suhail

Electronics and Communication Engineering

⭐ If you find this project useful, consider giving the repository a star.


### ⚠️ One important thing about the images

GitHub **will not display a PDF as an image** using:

```markdown
![Complete Circuit Diagram](Circuit%20Diagram.pdf)

For the circuit diagram, convert/save the circuit screenshot as a PNG or JPG and put it in your repository.

For example:

ATmega328P-Smart-Parking-System/
│
├── README.md
├── sketch_sep26a.ino
├── Circuit-Diagram.png
├── Case01-when-one-parking-spot-is-occupied.png
└── Case02-when-both-are-occupied.png

Then change that section to:

## 🔌 Complete Circuit Diagram

![Complete Circuit Diagram](Circuit-Diagram.png)

The two screenshots you already have are perfect for the README because they visually demonstrate the one-slot-occupied and both-slots-occupied states.

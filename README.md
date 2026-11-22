# ATmega328P Smart Parking Management System

A **two-slot parking monitoring and simulated billing system** built around the ATmega328P. It tracks slot occupancy, displays availability on a 20×4 I²C LCD, indicates slot status with LEDs, records arrival time with an RTC, and prints a simulated parking bill to the Serial Monitor when a vehicle leaves.

> **Scope:** Academic prototype / simulation. Billing time is accelerated for demonstration; it is not a production parking controller.

## Features

- Monitors two parking slots using digital sensors.
- Displays each slot as **AVAILABLE** or **OCCUPIED**.
- Shows total free spaces on a 20×4 LCD.
- Uses DS1307 RTC timestamps for entry/exit events.
- Changes bi-color LED indication per slot (green available, red occupied).
- Prints simulated parking duration and fee to Serial Monitor.

## Hardware

| Component | Quantity | Purpose |
|---|---:|---|
| ATmega328P | 1 | Controller |
| Slot sensors | 2 | Detect occupancy (LOW = occupied in current logic) |
| 20×4 I²C LCD + PCF8574 interface | 1 | Status display |
| DS1307 RTC | 1 | Time source |
| Two bi-color LEDs | 2 | Slot status |
| Supporting resistors, power | — | Circuit support |

## Pin mapping in firmware

| Signal | Arduino pin |
|---|---|
| Slot 1 sensor | D6 |
| Slot 2 sensor | D7 |
| Slot 1 LED control | D8, D9 |
| Slot 2 LED control | D10, D11 |
| LCD | I²C via `Wire` |

## System logic

1. Initialize serial, I²C, sensors, LEDs, LCD and RTC.
2. Read the two slot sensor inputs repeatedly.
3. Detect a state change to occupied and record the RTC timestamp.
4. Detect a state change to available, calculate elapsed time, and print a bill.
5. Refresh the LCD with the two slot states and available-space count.

## Billing model (simulation)

The sketch currently uses:

- Hourly rate: **2.0** (displayed with a dollar sign in the serial receipt)
- **5 seconds = 1 simulated hour**
- Minimum billable display duration: **0.1 simulated hour**

This accelerated time model makes billing easier to demonstrate. Adjust the rate and conversion factor in the sketch for experiments.

## Software

- Arduino-compatible C/C++
- `Wire.h`
- `LiquidCrystal_I2C.h`
- `RTClib.h`
- Arduino IDE
- Proteus (circuit simulation)

## Repository contents

- Arduino sketch: `sketch_sep26a.ino` (confirm exact filename in the repo)
- Proteus project/circuit file(s)
- Screenshots of occupancy states, if included

## How to test

1. Open the sketch in Arduino IDE and install the LCD and RTC libraries.
2. Verify sensor pin logic (the code uses `INPUT_PULLUP`; LOW means occupied).
3. Set the DS1307 time correctly before testing.
4. Simulate or connect the sensors and check both available/occupied states.
5. Trigger an occupied-to-available transition and inspect the bill in Serial Monitor (9600 baud).
6. Test both slots independently and together.

## Limitations & next steps

- Two-slot system only.
- Sensor behavior depends on the actual sensor type and wiring.
- No vehicle identity or persistent parking record.
- The current billing logic uses a time acceleration factor and a fixed minimum duration.
- Add debounce/filtering, configurable tariff, more slots, and persistent logs if extending the project.

## Learning outcomes

Digital input monitoring · I²C communication · RTC integration · LCD updates · state-change detection · elapsed-time calculation · serial debugging.

---

**Author:** Mohammed Suhail · Electronics & Communication Engineering student

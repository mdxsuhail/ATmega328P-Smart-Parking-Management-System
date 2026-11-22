# ATmega328P Smart Parking Management System

Two-slot parking monitor using an ATmega328P. The system senses occupancy, updates a 20×4 I²C LCD, controls slot LEDs, records entry time with a DS1307 RTC, and prints a simulated bill when a vehicle leaves.

> **Scope:** Academic prototype/simulation. Billing time is accelerated.

## Features
- Two digital parking-slot inputs
- LCD displays AVAILABLE/OCCUPIED and total free slots
- Bi-color LEDs: green available, red occupied
- DS1307 RTC entry/exit timestamps
- Serial Monitor billing output

## Hardware
| Part | Function |
|---|---|
| ATmega328P | Controller |
| 2 slot sensors | Occupancy detection |
| 20×4 LCD + PCF8574 I²C | Status display |
| DS1307 RTC | Time source |
| 2 bi-color LEDs | Slot indicators |
| Resistors/power | Supporting circuit |

## Pin mapping (firmware)
| Signal | Pin |
|---|---|
| Slot sensors | D6, D7 |
| Slot 1 LED | D8, D9 |
| Slot 2 LED | D10, D11 |
| LCD | I²C |

Sensor input uses `INPUT_PULLUP`; LOW is interpreted as occupied.

## How it works
1. Initialize Serial, I²C, LCD, sensors and RTC.
2. Poll sensor inputs and detect occupancy changes.
3. On arrival, record RTC time and set LED red.
4. On departure, set LED green, calculate duration and print bill.
5. Refresh LCD with occupancy and available-slot count.

## Simulation billing
- Rate constant: 2.0 (receipt uses a dollar sign)
- 5 seconds = 1 simulated hour
- Minimum displayed duration = 0.1 simulated hour

These are demo parameters, not real tariff settings.

## Software
Arduino C/C++ · `Wire.h` · `LiquidCrystal_I2C.h` · `RTClib.h` · Arduino IDE · Proteus

## Repository files
Arduino sketch, Proteus project, and occupancy screenshots (check repository file list for exact filenames).

## Test it
Test both slots separately and together; verify LCD/LED states, set the RTC, trigger arrival/departure, and inspect Serial Monitor at 9600 baud.

## Limitations & future work
- Only two slots; sensor type/wiring affect reliability.
- No vehicle identity or persistent transaction records.
- Accelerated time and fixed fee are simulation-only.
- Add sensor filtering/debounce, configurable rate, persistent records, and additional slots.

**Learning outcomes:** digital inputs, state-change detection, I²C, RTC, LCD, serial debugging, elapsed-time calculations.

**Author:** Mohammed Suhail · ECE student
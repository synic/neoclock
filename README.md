# NeoClockº

A WS2812B LED-based analog clock that uses a DS3231 real-time clock module for accurate timekeeping.

## Features

- Multiple display modes for clock face
- 11 color schemes
- Brightness adjustment with 5 levels
- Battery backup with RTC
- Automatic fallback mode if RTC fails
- Diagnostic routines for troubleshooting

## Hardware Requirements

- Arduino Micro (or compatible board)
- DS3231 RTC module
- WS2812B LED strip (60 LEDs)
- 4 push buttons for control
- USB power supply

## Installation

1. Install the arduino-cli:

   ```bash
   $ brew install arduino-cli   # macOS
   ```

2. Edit `vars.mak` and update any values to match your system.

3. Plug in your board and run `make` to compile and upload.

## Usage

The clock has four buttons for control:

- HOUR: Increment hour
- MINUTE: Increment minute
- BRIGHTNESS: Cycle through brightness levels
- MODE: Cycle between setting modes

Hold HOUR + BRIGHTNESS to reset to defaults.

## Development

This project uses FastLED for LED control and RTCLib for the real-time clock. The code is structured with:
- Comprehensive hardware configuration
- Multiple display modes and color schemes
- RTC diagnostics and fallback modes
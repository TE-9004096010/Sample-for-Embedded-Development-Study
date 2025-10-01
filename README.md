# Strike Gundam Striker Pack Change System

Arduino/ESP32 based embedded system that simulates the Strike Gundam striker pack changing sequences.

## Features

- Servo motor controlled striker pack switching
- LED effects for Phase Shift Armor
- LCD display for status information
- Sound effects for mechanical operations
- Button controls for each striker pack type

## Hardware Requirements

- Arduino Uno or ESP32 development board
- 3x Servo motors (for backpack and wing movements)
- 4x LEDs (for PS Armor effects)
- 1x LCD display (16x2)
- 4x Tactile switches (input buttons)
- 1x Buzzer or piezo speaker
- Resistors and breadboard for connections

## Striker Pack Types

1. **Base Mode** - Strike Gundam without any pack
2. **Aile Striker** - High mobility with wing thrusters
3. **Sword Striker** - Close combat with Schwert Gewehr
4. **Launcher Striker** - Heavy artillery configuration

## Getting Started

1. Connect hardware according to the wiring diagram
2. Upload the code to your Arduino/ESP32
3. Press buttons to change striker packs
4. Watch the LED effects and servo movements

## Building and Uploading

### Using Arduino IDE
1. Install Arduino IDE from https://www.arduino.cc/en/software
2. Copy the contents of `src/main.cpp` into a new Arduino sketch
3. Install required libraries:
   - Servo library (usually pre-installed)
   - LiquidCrystal library (usually pre-installed)
4. Select Board: Tools → Board → Arduino Uno
5. Select Port: Tools → Port → (your Arduino port)
6. Click Upload button

### Using Arduino CLI (if installed)
```bash
# Install Arduino CLI first
arduino-cli core update-index
arduino-cli core install arduino:avr

# Compile and upload
arduino-cli compile --fqbn arduino:avr:uno .
arduino-cli upload -p COM3 --fqbn arduino:avr:uno .
```

### Using PlatformIO (alternative)
1. Install PlatformIO extension for VS Code
2. Create platformio.ini file in project root
3. Use PlatformIO: Build and PlatformIO: Upload commands

## Project Structure

```
├── src/
│   ├── main.cpp              # Main Arduino sketch
│   ├── StrikeSystem.h        # Strike Gundam system header
│   ├── StrikeSystem.cpp      # Strike Gundam system implementation
│   └── config.h              # Pin definitions and constants
├── docs/
│   ├── wiring_diagram.md     # Hardware connection guide
│   └── specifications.md     # Technical specifications
├── examples/
│   └── basic_test.cpp        # Simple test program
└── README.md
```

## License

MIT License - Feel free to modify and distribute.
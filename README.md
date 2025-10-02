# Strike Gundam Striker Pack Change System

STM32 based embedded system that simulates the Strike Gundam striker pack changing sequences.

## Features

- Servo motor controlled striker pack switching
- LED effects for Phase Shift Armor
- LCD display for status information
- Sound effects for mechanical operations
- Button controls for each striker pack type

## Hardware Requirements

- STM32F103C8T6 (Blue Pill) or STM32F401CCU6 (Black Pill)
- 3x Servo motors (for backpack and wing movements)
- 4x LEDs (for PS Armor effects)
- 1x LCD display (16x2)
- 4x Tactile switches (input buttons)
- 1x Buzzer or piezo speaker
- Resistors and breadboard for connections
- ST-Link V2 programmer (for uploading code)

## Striker Pack Types

1. **Base Mode** - Strike Gundam without any pack
2. **Aile Striker** - High mobility with wing thrusters
3. **Sword Striker** - Close combat with Schwert Gewehr
4. **Launcher Striker** - Heavy artillery configuration
5. **I.W.S.P** - Integrated Weapons Striker Pack
6. **Ohtori Striker** - Enhanced mobility pack
7. **Perfect Strike** - All weapons simultaneously equipped

## Getting Started

1. Connect hardware according to the wiring diagram
2. Upload the code to your Arduino/ESP32
3. Press buttons to change striker packs
4. Watch the LED effects and servo movements

## Building and Uploading

### Using STM32CubeIDE
1. Install STM32CubeIDE from ST Microelectronics
2. Import project as existing STM32 project
3. Configure clock settings for your board
4. Build and upload via ST-Link

### Using PlatformIO (Recommended)
1. Install PlatformIO extension for VS Code
2. Select target board in platformio.ini:
   - `bluepill_f103c8` for STM32F103C8T6 Blue Pill
   - `blackpill_f401cc` for STM32F401CCU6 Black Pill
3. Use PlatformIO: Build and PlatformIO: Upload commands
4. Connect ST-Link V2 programmer to your STM32 board

### Using Arduino IDE with STM32 Core
1. Install Arduino IDE
2. Add STM32 board package: https://github.com/stm32duino/BoardManagerFiles
3. Install STM32duino LiquidCrystal library
4. Select your STM32 board from Tools → Board
5. Set upload method to ST-Link
6. Copy main.cpp content to Arduino sketch and upload

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
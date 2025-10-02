# Technical Specifications

## System Overview
Strike Gundam Striker Pack Change System - Embedded C++ project for STM32

## Hardware Requirements

### Microcontroller
- **Primary**: STM32F103C8T6 (Blue Pill)
- **Alternative**: STM32F401CCU6 (Black Pill)
- **Memory**: 64KB Flash, 20KB RAM (STM32F103)
- **Clock**: 72MHz (STM32F103)

### Actuators
- **3x Servo Motors**: SG90 or similar (180° rotation)
  - Torque: 1.8kg⋅cm minimum
  - Operating Voltage: 4.8V - 6V
  - Control Signal: PWM (50Hz, 1-2ms pulse width)

### Display
- **LCD**: 16x2 character display (HD44780 compatible)
- **Backlight**: Optional LED backlight
- **Interface**: 4-bit parallel connection

### Input/Output
- **4x Tactile Switches**: 6x6mm momentary push buttons
- **4x LEDs**: 5mm standard LEDs (red/blue recommended)
- **1x Buzzer**: Passive piezo buzzer

### Power Supply
- **STM32**: 3.3V via USB or external regulator
- **Servo Power**: External 5V/2A power supply
- **Current Draw**: ~1.5A peak (with all servos active)

## Software Specifications

### Programming Language
- **Language**: C++ (STM32 HAL/Arduino framework)
- **Compiler**: ARM-GCC
- **IDE**: STM32CubeIDE, PlatformIO, or Arduino IDE with STM32 core
- **Libraries**: 
  - STM32 HAL drivers
  - Servo library (STM32 compatible)
  - LiquidCrystal library (STM32 compatible)

### Memory Usage
- **Program Storage**: ~16KB (estimated)
- **Dynamic Memory**: ~2KB (estimated)
- **Stack Usage**: ~512 bytes (estimated)

### Timing Specifications
- **Main Loop**: ~1kHz execution rate
- **Button Debounce**: 300ms
- **Servo Movement**: 500ms transition time
- **LED Fade**: 10ms per step
- **PWM Frequency**: 50Hz (servo control)

## Performance Characteristics

### Response Times
- **Button Response**: <50ms detection
- **Striker Change**: 2-3 seconds complete sequence
- **PS Armor Effect**: 1 second fade in/out
- **Servo Positioning**: ±2° accuracy

### Operating Conditions
- **Temperature**: -40°C to 85°C
- **Humidity**: 20% to 80% RH (non-condensing)
- **Power Consumption**: 300mA typical, 1.5A peak
- **Supply Voltage**: 3.3V ±5%

## Striker Pack Configurations

### Base Mode (NO_PACK)
- Backpack: 90° (neutral position)
- Wings: 0° (folded)
- LED Pattern: Off

### Aile Striker (AILE_STRIKER)
- Backpack: 45° (forward tilt)
- Wings: 90° (extended)
- LED Pattern: Blue pulse

### Sword Striker (SWORD_STRIKER)
- Backpack: 135° (rear tilt)
- Left Wing: 0°→180° (sword deployment)
- LED Pattern: Red flash

### Launcher Striker (LAUNCHER_STRIKER)
- Backpack: 180° (full rear)
- Wings: 45° (launcher position)
- LED Pattern: White strobe

## Safety Features
- Input voltage protection
- Servo current limiting
- Emergency stop capability
- Overcurrent protection (external fuse recommended)
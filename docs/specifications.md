# Technical Specifications

## System Overview
Strike Gundam Striker Pack Change System - Embedded C++ project for Arduino/ESP32

## Hardware Requirements

### Microcontroller
- **Primary**: Arduino Uno R3
- **Alternative**: ESP32 DevKit V1
- **Memory**: 32KB Flash, 2KB RAM (Arduino Uno)
- **Clock**: 16MHz (Arduino Uno)

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
- **Arduino**: 5V via USB or 7-12V DC adapter
- **Servo Power**: External 5V/2A power supply recommended
- **Current Draw**: ~1.5A peak (with all servos active)

## Software Specifications

### Programming Language
- **Language**: C++ (Arduino framework)
- **Compiler**: AVR-GCC
- **Libraries**: 
  - Servo.h (servo control)
  - LiquidCrystal.h (LCD display)

### Memory Usage
- **Program Storage**: ~8KB (estimated)
- **Dynamic Memory**: ~512 bytes (estimated)
- **Stack Usage**: ~256 bytes (estimated)

### Timing Specifications
- **Main Loop**: ~100Hz execution rate
- **Button Debounce**: 300ms
- **Servo Movement**: 500ms transition time
- **LED Fade**: 20ms per step
- **PWM Frequency**: 50Hz (servo control)

## Performance Characteristics

### Response Times
- **Button Response**: <50ms detection
- **Striker Change**: 2-3 seconds complete sequence
- **PS Armor Effect**: 1 second fade in/out
- **Servo Positioning**: ±2° accuracy

### Operating Conditions
- **Temperature**: 0°C to 50°C
- **Humidity**: 20% to 80% RH (non-condensing)
- **Power Consumption**: 500mA typical, 1.5A peak

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
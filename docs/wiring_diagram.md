# Hardware Wiring Diagram

## STM32F103C8T6 (Blue Pill) Pin Connections

### Servo Motors
- **Backpack Servo**: PA6 (PWM Timer 3, Channel 1)
- **Left Wing Servo**: PA7 (PWM Timer 3, Channel 2)
- **Right Wing Servo**: PB0 (PWM Timer 3, Channel 3)

### PS Armor LEDs
- **LED 1**: PB12 (with 220Ω resistor)
- **LED 2**: PB13 (with 220Ω resistor)
- **LED 3**: PB14 (with 220Ω resistor)
- **LED 4**: PB15 (with 220Ω resistor)

### LCD Display (16x2)
- **RS**: PA8
- **Enable**: PA9
- **D4**: PA10
- **D5**: PA11
- **D6**: PA12
- **D7**: PA15
- **VSS**: GND
- **VDD**: 3.3V
- **V0**: Potentiometer (contrast adjustment)

### Buzzer
- **Positive**: PB1 (PWM Timer 3, Channel 4)
- **Negative**: GND

### Input Buttons
- **Aile Button**: PC13 (with internal pull-up)
- **Sword Button**: PC14 (with internal pull-up)
- **Launcher Button**: PC15 (with internal pull-up)
- **Base Button**: PA0 (with internal pull-up)
- **I.W.S.P Button**: PA1 (with internal pull-up)
- **Ohtori Button**: PA2 (with internal pull-up)
- **Perfect Button**: PA3 (with internal pull-up)

## Power Supply
- **STM32**: 3.3V via USB or external 3.3V regulator
- **Servos**: External 5V power supply (separate from STM32)
- **Logic Level**: 3.3V (STM32 is NOT 5V tolerant on most pins)

## Connection Notes
1. Use common ground for all components
2. **IMPORTANT**: STM32 operates at 3.3V - use level shifters for 5V devices if needed
3. External 5V power supply required for servo motors
4. Use pull-up resistors (10kΩ) for button inputs (or enable internal pull-ups)
5. Add bypass capacitors (100nF) near STM32 power pins
6. Test each component individually before full assembly
7. Servo control signals are 3.3V compatible
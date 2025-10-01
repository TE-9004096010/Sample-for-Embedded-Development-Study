# Hardware Wiring Diagram

## Arduino Uno Pin Connections

### Servo Motors
- **Backpack Servo**: Pin 9 (PWM)
- **Left Wing Servo**: Pin 6 (PWM)
- **Right Wing Servo**: Pin 7 (PWM)

### PS Armor LEDs
- **LED 1**: Pin 8 (with 220Ω resistor)
- **LED 2**: Pin 9 (with 220Ω resistor)
- **LED 3**: Pin 10 (with 220Ω resistor)
- **LED 4**: Pin 11 (with 220Ω resistor)

### LCD Display (16x2)
- **RS**: Pin 12
- **Enable**: Pin 11
- **D4**: Pin 5
- **D5**: Pin 4
- **D6**: Pin 3
- **D7**: Pin 2
- **VSS**: GND
- **VDD**: 5V
- **V0**: Potentiometer (contrast adjustment)

### Buzzer
- **Positive**: Pin 13
- **Negative**: GND

### Input Buttons
- **Aile Button**: Pin A0 (with pull-up resistor)
- **Sword Button**: Pin A1 (with pull-up resistor)
- **Launcher Button**: Pin A2 (with pull-up resistor)
- **Base Button**: Pin A3 (with pull-up resistor)

## Power Supply
- **Arduino**: USB or 7-12V DC adapter
- **Servos**: External 5V power supply recommended for multiple servos
- **LEDs**: Powered from Arduino 5V through resistors

## Connection Notes
1. Use common ground for all components
2. External power supply recommended for servo motors
3. Add bypass capacitors near servo power connections
4. Use pull-up resistors (10kΩ) for button inputs
5. Test each component individually before full assembly
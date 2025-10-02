#include "mock_arduino.h"

// Global mock functions implementation
void pinMode(int pin, int mode) {
    ArduinoMock::getInstance().pinMode(pin, mode);
}

void digitalWrite(int pin, int value) {
    ArduinoMock::getInstance().digitalWrite(pin, value);
}

int digitalRead(int pin) {
    return ArduinoMock::getInstance().digitalRead(pin);
}

void analogWrite(int pin, int value) {
    ArduinoMock::getInstance().analogWrite(pin, value);
}

void delay(unsigned long ms) {
    ArduinoMock::getInstance().delay(ms);
}

void tone(int pin, int frequency, unsigned long duration) {
    ArduinoMock::getInstance().tone(pin, frequency, duration);
}
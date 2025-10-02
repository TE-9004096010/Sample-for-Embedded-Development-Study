#ifndef MOCK_ARDUINO_H
#define MOCK_ARDUINO_H

// STM32 Mock Framework for Google Test
// Provides Arduino API compatibility layer for STM32F103C8T6 embedded testing

#include <gmock/gmock.h>
#include <map>
#include <vector>

// Arduino constants
#define HIGH 1
#define LOW 0
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2

// Pin definitions for testing
#define PA6 1
#define PA7 2
#define PB0 3
#define PB12 4
#define PB13 5
#define PB14 6
#define PB15 7
#define PC13 8
#define PC14 9
#define PC15 10
#define PA0 11
#define PA1 12
#define PA2 13
#define PA3 14

// Mock Arduino functions
class ArduinoMock {
public:
    static ArduinoMock& getInstance() {
        static ArduinoMock instance;
        return instance;
    }
    
    MOCK_METHOD(void, pinMode, (int pin, int mode));
    MOCK_METHOD(void, digitalWrite, (int pin, int value));
    MOCK_METHOD(int, digitalRead, (int pin));
    MOCK_METHOD(void, analogWrite, (int pin, int value));
    MOCK_METHOD(void, delay, (unsigned long ms));
    MOCK_METHOD(void, tone, (int pin, int frequency, unsigned long duration));
    
    // State tracking for tests
    std::map<int, int> pinModes;
    std::map<int, int> digitalStates;
    std::map<int, int> analogValues;
    std::vector<std::string> toneHistory;
};

// Global mock functions that redirect to the mock object
void pinMode(int pin, int mode);
void digitalWrite(int pin, int value);
int digitalRead(int pin);
void analogWrite(int pin, int value);
void delay(unsigned long ms);
void tone(int pin, int frequency, unsigned long duration = 0);

// Mock Servo class
class Servo {
public:
    MOCK_METHOD(void, attach, (int pin));
    MOCK_METHOD(void, write, (int angle));
    MOCK_METHOD(int, read, ());
    MOCK_METHOD(void, detach, ());
    
private:
    int pin_;
    int angle_;
};

// Mock LiquidCrystal class
class LiquidCrystal {
public:
    LiquidCrystal(int rs, int enable, int d4, int d5, int d6, int d7) 
        : rs_(rs), enable_(enable), d4_(d4), d5_(d5), d6_(d6), d7_(d7) {}
    
    MOCK_METHOD(void, begin, (int cols, int rows));
    MOCK_METHOD(void, clear, ());
    MOCK_METHOD(void, setCursor, (int col, int row));
    MOCK_METHOD(size_t, print, (const char* str));
    
private:
    int rs_, enable_, d4_, d5_, d6_, d7_;
};

#endif // MOCK_ARDUINO_H
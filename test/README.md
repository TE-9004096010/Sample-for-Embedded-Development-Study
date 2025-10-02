# Strike Gundam Test Framework

This directory contains the comprehensive Google Test framework implementation for the STM32 Strike Gundam striker pack changing system.

## Overview

The test framework provides complete testing coverage for the embedded C++ Strike Gundam project, including:

- **Unit Tests**: Individual component testing with mocked dependencies
- **Integration Tests**: System-level testing with component interactions
- **Hardware Effect Tests**: LED and sound effect validation
- **Mock Framework**: Complete Arduino API mocking for PC-based testing

## Structure

```
test/
├── README.md                      # This documentation
├── CMakeLists.txt                # CMake build configuration
├── Makefile                      # Alternative Make build system
├── run_tests.ps1                 # PowerShell test runner for Windows
├── test_main.cpp                 # Test runner main function
├── mocks/                        # Mock implementations
│   ├── mock_arduino.h            # Arduino API mock declarations
│   └── mock_arduino.cpp          # Arduino API mock implementations
├── unit/                         # Unit test cases
│   ├── test_strike_system.cpp    # Core striker system tests
│   ├── test_servo_control.cpp    # Servo motor control tests
│   ├── test_led_effects.cpp      # LED effects and control tests
│   └── test_sound_effects.cpp    # Sound/buzzer effect tests
└── integration/                  # Integration test cases
    └── test_system_integration.cpp # Full system integration tests
```

## Dependencies

- **Google Test (gtest)**: Unit testing framework
- **Google Mock (gmock)**: Mocking framework for dependencies
- **CMake**: Primary build system
- **Make**: Alternative build system (MinGW/MSYS2 on Windows)

## Quick Start

### Windows PowerShell (Recommended)

```powershell
# Run all tests
.\run_tests.ps1

# Run specific test types
.\run_tests.ps1 -TestType unit
.\run_tests.ps1 -TestType integration

# Run with verbose output
.\run_tests.ps1 -Verbose

# Run specific test case
.\run_tests.ps1 -TestCase "StrikeSystemTest.*"

# Show help
.\run_tests.ps1 -Help
```

### Using CMake

```bash
# Create and enter build directory
mkdir build && cd build

# Configure project
cmake ..

# Build tests
cmake --build . --config Debug

# Run tests
./striker_tests  # Linux/macOS
.\Debug\striker_tests.exe  # Windows
```

### Using Make (MinGW/MSYS2)

```bash
# Build all tests
make

# Run tests
make test

# Run specific test types
make unit-test
make integration-test

# Generate coverage report
make coverage

# Clean build files
make clean
```

## Test Categories

### Unit Tests

- **StrikeSystemTest**: Core striker pack system functionality
- **ServoControlTest**: Servo motor control and movement
- **LEDEffectsTest**: LED control and visual effects
- **SoundEffectsTest**: Audio feedback and buzzer control

### Integration Tests

- **SystemIntegrationTest**: Complete system functionality
- Multi-component striker pack changes
- Error handling and recovery
- Performance and memory validation

## Mock Framework Features

The comprehensive mock framework provides:

- **ArduinoMock**: Complete Arduino API coverage
- **ServoMock**: Servo library functionality
- **LiquidCrystalMock**: LCD display operations

## Running Tests

```bash
# Run all tests
./striker_tests

# Run specific test filters
./striker_tests --gtest_filter="*Test.*"
./striker_tests --gtest_filter="StrikeSystemTest.*"
./striker_tests --gtest_filter="IntegrationTest.*"

# Verbose output with timing
./striker_tests --gtest_print_time=1 --gtest_color=yes
```

## Code Coverage and Analysis

```bash
# Generate coverage report
make coverage

# Static analysis
make static-analysis

# Memory leak detection
make memcheck
```

## STM32 Hardware Validation

Tests validate STM32F103C8T6 specific:
- Pin configuration and GPIO layout
- 72MHz ARM Cortex-M3 timing constraints
- 64KB Flash / 20KB RAM memory limits
- 3.3V logic level compatibility
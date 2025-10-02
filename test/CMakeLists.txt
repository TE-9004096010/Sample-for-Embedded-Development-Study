cmake_minimum_required(VERSION 3.14)
project(StrikeGundamTests)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)

# Find required packages
find_package(GTest REQUIRED)
find_package(GMock REQUIRED)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
    ${CMAKE_CURRENT_SOURCE_DIR}/mocks
    ${GTEST_INCLUDE_DIRS}
    ${GMOCK_INCLUDE_DIRS}
)

# Add compiler flags for testing
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTESTING_MODE")

# Source files (excluding Arduino-specific code for testing)
set(SOURCES
    ../src/StrikeSystem.cpp
    mocks/mock_arduino.cpp
)

# Test files
set(TEST_SOURCES
    unit/test_strike_system.cpp
    unit/test_servo_control.cpp
    unit/test_led_effects.cpp
    integration/test_full_sequence.cpp
    test_main.cpp
)

# Create test executable
add_executable(run_tests ${SOURCES} ${TEST_SOURCES})

# Link libraries
target_link_libraries(run_tests
    ${GTEST_LIBRARIES}
    ${GMOCK_LIBRARIES}
    pthread
)

# Enable testing
enable_testing()

# Add tests
add_test(NAME StrikeGundamTests COMMAND run_tests)
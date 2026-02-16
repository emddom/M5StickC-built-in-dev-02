# M5StickC SPL and Audio Streamer

## Project Overview
This project is an embedded application for the M5StickC (ESP32-based development board) designed to measure Sound Pressure Level (SPL) and stream raw audio data over a serial connection.

The core logic resides in `src/main.cpp`, which implements:
-   **Microphone Reading:** Captures audio data using the M5StickC's built-in microphone via the `M5Unified` Mic API.
-   **SPL Calculation:** Calculates the Root Mean Square (RMS) of the audio signal and converts it to a decibel (dB) SPL value.
-   **Real-time Display:** Shows the calculated SPL value on the M5StickC's LCD screen using `M5GFX`.
-   **Data Streaming:** Sends raw audio samples to the serial port for external processing or visualization.

## Hardware
-   **Device:** M5StickC
-   **Microphone:** Internal MEMS microphone (SPM1423)
-   **Display:** 0.96" TFT LCD

## Project Structure
-   `src/main.cpp`: Main application logic (Standard C++ format).
-   `platformio.ini`: PlatformIO configuration file.
-   `CMakeLists.txt`: CMake build configuration.

## Recent Changes & Refactoring (2026-02-16)

The project has undergone significant modernization and fixes:

### 1. Migration from .ino to C++
-   **Action:** Converted the Arduino sketch `mic_SPL_and_stream_RT_2025.ino` to a standard C++ source file `src/main.cpp`.
-   **Details:** Added `#include <Arduino.h>` and ensured proper function declarations.

### 2. Library Migration (M5Unified)
-   **Action:** Replaced the deprecated `M5StickC` library with the modern `M5Unified` and `M5GFX` libraries.
-   **Details:**
    -   Updated `platformio.ini` dependencies to `m5stack/M5Unified` and `m5stack/M5GFX`.
    -   Refactored `setup()` to use `M5.config()` and `M5.begin(cfg)`.
    -   Replaced `M5.Lcd` with `M5.Display`.
    -   Replaced manual I2S initialization and reading with `M5.Mic` API (`M5.Mic.begin()`, `M5.Mic.record()`).
    -   Explicitly configured the internal microphone usage (`cfg.internal_mic = true`).

### 3. Build Configuration Fixes
-   **Framework:** Corrected `platformio.ini` to use `framework = arduino` (previously incorrectly set to `espidf`).
-   **Conflict Resolution:** Removed the original `src/main.cpp` which conflicted with the main logic file.

## Development

### Prerequisites
-   PlatformIO (VS Code extension or CLI)

### Build & Upload
```bash
# Build the project
pio run

# Upload firmware to M5StickC
pio run --target upload

# Monitor serial output
pio device monitor
```

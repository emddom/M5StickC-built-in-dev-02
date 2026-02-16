# M5StickC Built-in Hardware Dev (IMU)

## Project Overview
This project is a development sandbox for the M5StickC (ESP32-based development board) focused on utilizing its built-in hardware features, specifically the **6-Axis IMU (MPU6886 or SH200Q)**.

The core logic resides in `src/main.cpp`. The goal is to:
-   **Initialize IMU:** Detect and configure the internal accelerometer and gyroscope.
-   **Read Sensor Data:** Capture motion data (acceleration, rotation).
-   **Display Data:** Visualize sensor readings (Accel X/Y/Z, Gyro X/Y/Z) on the LCD using `M5GFX`.

## Hardware
-   **Device:** M5StickC
-   **IMU:** MPU6886 or SH200Q (6-Axis)
-   **Display:** 0.96" TFT LCD
-   **Other:** Power Management (AXP192), RTC, IR Transmitter, Button, LED

## Project Structure
-   `src/main.cpp`: Main application logic.
-   `platformio.ini`: PlatformIO configuration file.
-   `context7.json`: Context7 MCP configuration.
-   `CMakeLists.txt`: CMake build configuration.

## PlatformIO Configuration (`platformio.ini`)

The project uses the following key configurations:
-   **platform:** `espressif32`
-   **board:** `m5stick-c`
-   **framework:** `arduino`
-   **lib_deps:**
    -   `M5Unified`: Unified API for all M5Stack devices.
    -   `M5GFX`: Modern graphics library.
-   **monitor_speed:** `115200`

## Development

### IDE Setup
-   **VS Code Extension:** This project is configured to use the [PlatformIO IDE](https://platformio.org/platformio-ide) extension.
-   **Context7 MCP:** This project includes a `context7.json` configuration for better integration with Context7-enabled tools.

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

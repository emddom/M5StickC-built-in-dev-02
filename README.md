# M5StickC Built-in Hardware Dev (IMU)

A development sandbox for the M5StickC (ESP32) utilizing its built-in 6-Axis IMU (MPU6886 or SH200Q).

## Features
- **IMU Visualization:** Displays real-time Accelerometer (X, Y, Z) and Gyroscope (X, Y, Z) data on the built-in LCD.
- **Refresh Control:**
  - Updates display at 2Hz (every 500ms).
  - **Button A** toggles the display between "Frozen" and "Released" states.
- **Status Indicator:** Visual feedback on the display showing the current refresh state.

## Hardware
- **Device:** M5Stack M5StickC
- **Sensors:** 6-Axis IMU (MPU6886 or SH200Q)
- **Display:** 0.96" TFT LCD (managed via M5GFX)

## Development Environment
- **Platform:** PlatformIO (VS Code Extension)
- **Framework:** Arduino
- **Libraries:**
  - `M5Unified`
  - `M5GFX`

## Build & Upload

1. Open the project in VS Code with PlatformIO extension.
2. Build the project:
   ```bash
   pio run
   ```
3. Upload to device:
   ```bash
   pio run --target upload
   ```

## Notes
See [NOTES.md](./NOTES.md) for development decisions and environment recommendations.

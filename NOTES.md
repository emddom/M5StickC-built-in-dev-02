# Development Notes

## IDE & Environment

### VS Code Extensions
- **Makefile Tools (Microsoft):** 
    - **Recommendation:** Do not install (or ignore).
    - **Reason:** This project uses PlatformIO, which manages its own build system and IntelliSense. The Makefile Tools extension is for projects using standard Makefiles and is redundant/unnecessary for this environment.

### Framework Choice
- **Arduino Framework:**
    - **Recommendation:** Keep using the Arduino framework.
    - **Reason:** The `M5Unified` and `M5GFX` libraries are specifically optimized for the Arduino framework. While ESP-IDF is more "bare-metal" and powerful, the Arduino framework provides the best balance of ease of use and library support for M5Stack hardware features like the IMU and Display.

- **Hybrid Approach:**
    - **Concept:** Using ESP-IDF features within the Arduino environment.
    - **Details:** Since the Arduino core for ESP32 is built as a component of ESP-IDF, you can seamlessly use a hybrid approach. This allows for using high-level Arduino libraries (for UI/IMU) while utilizing ESP-IDF's lower-level capabilities—such as creating FreeRTOS tasks (`xTaskCreate`), using direct hardware timers, or utilizing the ESP-IDF specific drivers—to handle performance-critical or background operations.

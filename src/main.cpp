#include <M5Unified.h>

void setup() {
    auto cfg = M5.config();
    cfg.internal_imu = true; // Use internal IMU
    M5.begin(cfg);
    
    M5.Display.setRotation(3);
    M5.Display.fillScreen(BLACK);
    M5.Display.setTextColor(WHITE, BLACK);
    M5.Display.setTextSize(1);
}

void loop() {
    M5.update(); // Update button states
    
    static bool isPaused = false;
    static unsigned long lastUpdate = 0;

    if (M5.BtnA.wasPressed()) {
        isPaused = !isPaused;
        // Update only the status line immediately when button is pressed
        M5.Display.setCursor(0, 70); // Position for the bottom status line
        M5.Display.setTextColor(isPaused ? RED : GREEN, BLACK);
        M5.Display.printf("Status: %s", isPaused ? "FROZEN  " : "RELEASED");
        M5.Display.setTextColor(WHITE, BLACK); // Reset color
    }

    if (!isPaused && (millis() - lastUpdate > 500)) {
        lastUpdate = millis();
        
        float accX, accY, accZ;
        float gyroX, gyroY, gyroZ;

        M5.Imu.getAccel(&accX, &accY, &accZ);
        M5.Imu.getGyro(&gyroX, &gyroY, &gyroZ);

        M5.Display.setCursor(0, 0);
        M5.Display.println("IMU Data:");
        
        M5.Display.printf("Acc X: %5.2f\n", accX);
        M5.Display.printf("Acc Y: %5.2f\n", accY);
        M5.Display.printf("Acc Z: %5.2f\n", accZ);
        
        M5.Display.println("-------------");
        
        M5.Display.printf("Gyr X: %5.2f\n", gyroX);
        M5.Display.printf("Gyr Y: %5.2f\n", gyroY);
        M5.Display.printf("Gyr Z: %5.2f\n", gyroZ);

        // Ensure status line is visible during refresh
        M5.Display.setCursor(0, 70);
        M5.Display.setTextColor(GREEN, BLACK);
        M5.Display.print("Status: RELEASED");
        M5.Display.setTextColor(WHITE, BLACK);
    }

    delay(10);
}

/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5StickC sample source code
* Visit for more information: https://docs.m5stack.com/en/core/m5stickc
* Describe:  Micophone.
* Date: 2022/2/22
*******************************************************************************
*/
#include <Arduino.h>
#include <M5Unified.h>
#include <math.h>

#define READ_LEN    256 // Number of samples (int16_t), not bytes
#define START_BYTE1 0xAA
#define START_BYTE2 0xFF


int16_t adcBuffer[READ_LEN];

typedef float fftData_t;

void mic_record_task(void *arg) {
    double y;

    double blockAvg;
    double blockSum;
    int16_t blockCount = 1;
    int16_t oneSecCount = 1;

    double rmsSum = 0;
    double rmsAvg = 0;
    double rms = 0;

  
    while (1) {
      // M5.Mic.record returns true if successful. 
      // It blocks until the buffer is filled if the third argument (sample rate) is provided? 
      // Actually M5Unified record usually attempts to fill. 
      // Using a simple blocking approach if available or polling.
      // The example used record(rec_data, len, rate).
      
      if (M5.Mic.record(adcBuffer, READ_LEN, 10000)) {
        
        // Send Start Markers
        Serial.write(START_BYTE1);
        Serial.write(START_BYTE2);

        // Send raw data (samples * sizeof(int16_t))
        Serial.write((char *)adcBuffer, READ_LEN * sizeof(int16_t));

        blockSum = (double)adcBuffer[0];
        blockCount = 1;

        for (int n = 1; n < READ_LEN; n++) {
            y = (double)adcBuffer[n]; 
            blockSum += y; 
            blockCount++;
            oneSecCount++;
        }
        
        blockAvg = blockSum / blockCount;
        
        //Do a very simple normalization by subtracting average/bias from every sample
        for (int i = 0; i < READ_LEN; i++){ 
            y = (double)adcBuffer[i];
            double v = (y - blockAvg)/32768;
            rmsSum += v*v; 
        } 
        
        //calculate RMS and SPL
        if (oneSecCount > 9999){
            M5.Display.fillScreen(WHITE);
            M5.Display.setCursor(0,0);
    
            //calculate RMS      
            rmsAvg = rmsSum / oneSecCount;
            rms = sqrt(rmsAvg);
            
            //Calculate SPL
            // using calibration parameter to correct spl level closer to fit actual measurements
            int16_t spl = 20 * log10((rms)) + 94;  
        
            M5.Display.println(spl);
            //reinitialize variables
            oneSecCount = 1; 
            rmsSum = 0;
        }
      } else {
        // If no data, delay slightly to yield
        vTaskDelay(1);
      }
    }
}

void setup() {
    auto cfg = M5.config();
    cfg.internal_mic = true; // Use internal microphone
    M5.begin(cfg);
    M5.Mic.begin(); // Initialize microphone
    
    M5.Display.setRotation(3);
    M5.Display.fillScreen(WHITE);
    M5.Display.setTextColor(BLACK, WHITE);
    M5.Display.setTextFont(1);
    M5.Display.setTextSize(6);
    M5.Display.println("mic test");
    

    Serial.begin(500000);
    Serial.flush();
    xTaskCreate(mic_record_task, "mic_record_task", 2048, NULL, 1, NULL);
}

void loop() {
    vTaskDelay(1000 / portTICK_RATE_MS); 
}
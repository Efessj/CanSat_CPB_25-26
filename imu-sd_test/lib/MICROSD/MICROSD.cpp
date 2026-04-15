#include <Arduino.h>

#include <SPI.h>
#include <SD.h>
#include <GLOBAL.cpp>
#include <IMU.cpp>

SPIClass SPI_SD(VSPI);

// Buffer en RAM (1 segundo)
//Sample buffer[SAMPLES_PER_BLOCK];



class MICROSD {
  public:

    void begin(){
        SD.begin(SD_CS);
        delay(100);
    }

    void appendCSV(const char* filename, String data) {

        File file = SD.open(filename, FILE_APPEND);

        if (!file) {
            Serial.println("Error abriendo archivo");
            return;
        }

        file.println(data);
        file.close();
    }

    void writeCSV(const char* filename, String data) {

        File file = SD.open(filename, FILE_WRITE);

        if (!file) {
            Serial.println("Error abriendo archivo");
            return;
        }

        file.print(data);
        file.close();
    }

    void readCSV(const char* filename) {

        File file = SD.open(filename);

        if (!file) {
            Serial.println("Error abriendo archivo");
            return;
        }

        while (file.available()) {
            String line = file.readStringUntil('\n');
            Serial.println(line);
            APC.println(line);
        }

        file.close();
    }

    void saveOneSecond(File &file, IMU imu) {
        uint32_t startMicros = micros();
        Block block;

        for (int i = 0; i < SAMPLES_PER_BLOCK; i++) {

            uint32_t target = startMicros + i * SAMPLE_INTERVAL_US;

            // Espera activa precisa
            while ((int32_t)(micros() - target) < 0) {
                // No hacer nada, solo esperar
            }

            Sample s;   
            imu.readDataSD(s);
            s.t = micros();
            
            
            block.header = BLOCK_HEADER;
            block.samples[i] = s;
            
            //buffer[i] = block;
        }

        // Escritura en bloque
        file.write((uint8_t*)&block, sizeof(block));
        file.flush();
    }
};
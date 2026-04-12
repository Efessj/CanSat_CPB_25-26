#include <Arduino.h>

#include <SPI.h>
#include <SD.h>
#include <GLOBAL.cpp>
#include <IMU.cpp>

SPIClass SPI_SD(VSPI);

#define SAMPLE_INTERVAL_US 5000
#define SAMPLES_PER_BLOCK 200  // 1 segundo



// Buffer en RAM (1 segundo)
Sample buffer[SAMPLES_PER_BLOCK];



class MICROSD {
  public:

    void begin(){
        SD.begin(SD_CS);
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

        for (int i = 0; i < SAMPLES_PER_BLOCK; i++) {

            uint32_t target = startMicros + i * SAMPLE_INTERVAL_US;

            // Espera activa precisa
            while ((int32_t)(micros() - target) < 0) {
                // No hacer nada, solo esperar
            }

            Sample s;   
            imu.readDataSD(s);
            

            s.t = micros();
            buffer[i] = s;
        }

        // Escritura en bloque
        file.write((uint8_t*)buffer, sizeof(buffer));
        file.flush();
    }
};
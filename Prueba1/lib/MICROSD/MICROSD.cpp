#include <Arduino.h>

#include <SPI.h>
#include <SD.h>
#include <GLOBAL.cpp>

SPIClass SPI_SD(VSPI);
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
        }

        file.close();
    }

};
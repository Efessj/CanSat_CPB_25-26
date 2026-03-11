#include <Arduino.h>

#include <SPI.h>
#include <SD.h>

#define SD_CS 32
#define SD_MOSI 25
#define SD_MISO 16
#define SD_SCK 33

SPIClass SPI_SD(HSPI);

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



void setup() {
  Serial.begin(9600);
  SPI_SD.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  if (!SD.begin(SD_CS, SPI_SD)) {
    Serial.println("Error SD");
  }else{
    Serial.println("SD lista");
  }

  writeCSV("/data.csv", "temp,press\n");
  appendCSV("/data.csv", "23,101300\n");
  readCSV("/data.csv");
}

void loop() {
  readCSV("/data.csv");
  delay(1000);
}

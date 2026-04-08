#include <Arduino.h>

#include <SPI.h>
#include <SD.h>

#define SD_CS 32

SPIClass SPI_SD(VSPI);

#define VCC 13

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
  pinMode(VCC, OUTPUT);
  digitalWrite(VCC, HIGH);

  Serial.begin(9600);

  //SPI_SD.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  
  SD.begin(SD_CS);

  
  /*SPI_SD.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  if (!SD.begin(SD_CS, SPI_SD)) {
    Serial.println("Error SD");
  }else{
    Serial.println("SD lista");
  }*/

  writeCSV("/data.csv", "temp,press\n");
  appendCSV("/data.csv", "23,101300\n");
  readCSV("/data.csv");
}

void loop() {
  

  Serial.print("Card Type: ");
  switch (SD.cardType()) {
    case CARD_NONE: Serial.println("No SD card attached"); break;
    case CARD_MMC: Serial.println("MMC"); break;
    case CARD_SD: Serial.println("SDSC"); break;
    case CARD_SDHC: Serial.println("SDHC"); break;
    default: Serial.println("Unknown"); break;
  }
  
  //readCSV("/data.csv");
  delay(1000);
}

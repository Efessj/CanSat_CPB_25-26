#include <Arduino.h>

#include <SPI.h>
#include <SD.h>

#define SD_CS 10   // pin CS típico en Arduino

void setup() {
  Serial.begin(9600);

  if (!SD.begin(SD_CS)) {
    Serial.println("Error: no se pudo montar la SD");
    while (1);
  }

  Serial.println("SD montada correctamente");
}

void loop() {
}
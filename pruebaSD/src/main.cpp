#include <Arduino.h>

#include <SPI.h>
#include <SD.h>

#define SD_CS 5

void setup() {
  Serial.begin(9600);
  Serial.print("hola mundo");
  delay(3000);

}

void loop() {
  if (!SD.begin(SD_CS)) {
    Serial.println("Error: no se pudo montar la SD");
  } else {
    Serial.println("SD montada correctamente");
  }
  delay(1000);
}
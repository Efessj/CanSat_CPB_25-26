#include <Arduino.h>

#include <BH1750.h>
#include <Wire.h>
BH1750 lightMeter;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println("Sensor BH1750 iniciado correctamente");
  } else {
    Serial.println("Error al iniciar el BH1750");
  }
}

void loop() {
  float lux = lightMeter.readLightLevel();
  Serial.print("Luz: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);
}
#include <Arduino.h>
#include <BH1750.h>
#include <Wire.h>
#include <GLOBAL.cpp>

BH1750 lightMeter;

float lux;



/*
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
}*/


class LUX {
public:
  void begin(){
    Wire.begin();
    
    if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
      Serial.println("BH1750 init success");
      apc.println("BH1750 init success");
    } else {
      Serial.println("Error init BH1750");
      apc.println("Error init BH1750");
    }
  }

  void readData(){
    lux = lightMeter.readLightLevel();
  }

  void sendData(){
    Serial.print(" Luz: ");
    apc.print(" Luz: ");

    Serial.print(lux);
    apc.print(lux);

    Serial.println(" lx");
    apc.println(" lx");
  }
};


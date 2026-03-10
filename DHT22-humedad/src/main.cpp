#include <Arduino.h>
#include "DHT.h"



#define DHTTYPE DHT22

const int DHTPin = 5; 

DHT dht(DHTPin, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT22 test!");

  dht.begin();
}

void loop() {
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  float h = dht.readHumidity();

  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");

}
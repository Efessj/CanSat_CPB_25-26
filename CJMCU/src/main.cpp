#include <Arduino.h>

#define sensorPin 4

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
}

void loop() {
  //Serial.println(analogRead(sensorPin));
  Serial.println(analogRead(sensorPin)*(3.3/4095.0));

  delay(1000);
}

//////////////////NO SIRVE
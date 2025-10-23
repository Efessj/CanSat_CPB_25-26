#include <Arduino.h>

#define sensorPin 4
#define VCC 15

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(VCC, OUTPUT);
  digitalWrite(VCC, HIGH);
}

void loop() {
  Serial.println(analogRead(sensorPin));
  delay(1000);
}
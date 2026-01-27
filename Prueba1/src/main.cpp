#include <Arduino.h>
#include <MP.cpp>
#include <LUX.cpp>
#include <GLOBAL.cpp>

/*
SCL - 21
SDA - 22
OneWire - 19 (cambiar en global)


*/



MP mp;
LUX light;

unsigned long workingTime = 0;

void setup(){
  Serial.begin(9600);
  apc.begin(9600, SERIAL_8N1, 16, 17);
  pinMode(VCC_APC,OUTPUT);
  pinMode(VCC_PCB_UP,OUTPUT);
  digitalWrite(VCC_APC,HIGH);
  digitalWrite(VCC_PCB_UP,HIGH);

  mp.begin();
  light.begin();
}

void loop(){
  if (workingTime < millis()){
    mp.readData();
    light.readData();
    mp.sendData();
    light.sendData();

    workingTime += 1000;
  }
}
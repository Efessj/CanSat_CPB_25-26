#include <Arduino.h>
#include <MP.cpp>
#include <LUX.cpp>
#include <IMU.cpp>
#include <GLOBAL.cpp>

/*
SCL - 21
SDA - 22
OneWire - 19 (cambiar en global)


*/



MP mp;
LUX light;
IMU imu;

unsigned long workingTime = 0;

void setup(){
  Serial.begin(9600);
  apc_.begin(9600, SERIAL_8N1, 16, 17);
  pinMode(VCC_APC,OUTPUT);
  pinMode(VCC_PCB_UP,OUTPUT);
  digitalWrite(VCC_APC,HIGH);
  digitalWrite(VCC_PCB_UP,HIGH);

  mp.begin();
  light.begin();
  imu.begin();
  imu.calcOffset();
}

void loop(){
  if (workingTime < millis()){
    mp.readData();
    light.readData();
    imu.readData();
    mp.sendData();
    light.sendData();
    imu.sendData();

    workingTime += 1000;
  }
}
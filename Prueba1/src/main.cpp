#include <Arduino.h>
#include <MP.cpp>
#include <LUX.cpp>
#include <IMU.cpp>
#include <HUMIDITY.cpp>
#include <MICROSD.cpp>
#include <GLOBAL.cpp>

/*
SCL - 21
SDA - 22
OneWire - 19 (cambiar en global)


*/



MP mp;
LUX light;
IMU imu;
HUMIDITY hum;
MICROSD sd;

unsigned long workingTime = 0;
unsigned long packet = 0;


void sendIdentifier(){
    Serial.print(packet);
    Serial2.print(packet);
    Serial.print(":Island Sunnergy:");
    Serial2.print(":Island Sunnergy:");
}

void setup(){
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  pinMode(VCC_APC,OUTPUT);
  pinMode(VCC_PCB_UP,OUTPUT);
  pinMode(VCC_SD,OUTPUT);
  pinMode(VCC_POWER,OUTPUT);
  digitalWrite(VCC_APC,HIGH);
  digitalWrite(VCC_PCB_UP,HIGH);
  digitalWrite(VCC_SD,HIGH);
  digitalWrite(VCC_POWER,HIGH);

  //mp.begin();
  //light.begin();
  //hum.begin();
  imu.begin();
  imu.calcOffset();
  //sd.begin();
}

void loop(){
  if (workingTime < millis()){
    //mp.readData();
    //light.readData();
    //hum.readData();
    imu.readData();
    
    sendIdentifier();
    //mp.sendData();
    //light.sendData();
    //hum.sendData();
    imu.sendData();

    workingTime += 1000;
    packet++;
  }
}

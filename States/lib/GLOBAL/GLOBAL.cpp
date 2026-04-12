#include <Arduino.h>


#ifndef GLOBAL_H
#define GLOBAL_H

#define SEA_LEVEL_PRESSURE    1013.25   // sea level pressure
#define ONE_WIRE_BUS 27
#define VCC_APC 33
#define VCC_PCB_UP 13
#define VCC_SD 14
#define VCC_POWER 35
#define DHTTYPE DHT22
#define DHTPin 26
#define RXD2 16//
#define TXD2 17//
#define SD_CS 5
#define BZZ 4

//struct para guardar los datos del MPU
struct Sample {
  int16_t ax, ay, az;       //accel
  int16_t gx, gy, gz;       //gyro
  uint32_t t;               //timestamp
};

HardwareSerial APC(2);             //APC.begin(9600, SERIAL_8N1, TXD2, RXD2);
#endif
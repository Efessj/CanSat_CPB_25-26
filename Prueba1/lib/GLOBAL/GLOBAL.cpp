#include <Arduino.h>
#include <OneWire.h>


#define SEA_LEVEL_PRESSURE    1013.25   // sea level pressure
#define ONE_WIRE_BUS 14
#define VCC_APC 33
#define VCC_PCB_UP 26
#define VCC_SD 13
#define VCC_POWER 25
#define DHTTYPE DHT22
#define DHTPin 27
#define RXD2 16//
#define TXD2 17//
#define SD_CS 32

#pragma once

OneWire oneWire_(ONE_WIRE_BUS);
//HardwareSerial Serial2(2);             //Serial2.begin(9600, SERIAL_8N1, TXD2, RXD2);

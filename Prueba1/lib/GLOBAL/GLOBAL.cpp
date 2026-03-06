#include <Arduino.h>
#include <OneWire.h>


#define SEA_LEVEL_PRESSURE    1013.25   // sea level pressure
#define ONE_WIRE_BUS 19
#define VCC_APC 5
#define VCC_PCB_UP 18

#pragma once

OneWire oneWire_(ONE_WIRE_BUS);
HardwareSerial apc_(2);
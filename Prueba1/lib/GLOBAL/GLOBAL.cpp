#include <Arduino.h>



#define SEA_LEVEL_PRESSURE    1013.25   // sea level pressure
#define ONE_WIRE_BUS 19
#define VCC_APC 5
#define VCC_PCB_UP 18

OneWire oneWire(ONE_WIRE_BUS);
HardwareSerial apc(2);
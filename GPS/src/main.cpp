#include <Arduino.h>
#include "SoftwareSerial.h"
#include <TinyGPS++.h>

static const int RXPin = 5, TXPin = 18;

SoftwareSerial gpsSerial(RXPin, TXPin);
TinyGPSPlus gps;
float lattitude,longitude;

void setup() {
  gpsSerial.begin(9600);
  Serial.begin(9600);
}


void loop()
{
  while (gpsSerial.available() > 0){
    Serial.print(gpsSerial.read());
  }

  gps.encode(char(gpsSerial.read()));

  lattitude = (gps.location.lat());
  longitude = (gps.location.lng());

  /*

  Serial.print ("lattitude: ");
  Serial.println (lattitude, 6);
  Serial.print ("longitude: ");
  Serial.println (longitude, 6);
  
  delay(1000);

  */
 
}

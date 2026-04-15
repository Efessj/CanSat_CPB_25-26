#include <Arduino.h>

#include <SoftwareSerial.h>

#define rxPin 11
#define txPin 10
#define vccPin 13

// Set up a new SoftwareSerial object
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

void setup()  {
    // Define pin modes for TX and RX
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    pinMode(vccPin, OUTPUT);
    
    // Set the baud rate for the SoftwareSerial object
    mySerial.begin(9600);
    Serial.begin(9600);
    Serial.println("Serial started");
}

void loop() {
    while (mySerial.available() > 0) {
        Serial.print(char(mySerial.read()));
    }
    Serial.print("");
}
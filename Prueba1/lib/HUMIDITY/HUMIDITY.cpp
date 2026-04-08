#include <Arduino.h>
#include <DHT.h>
#include <GLOBAL.cpp>

DHT dht(DHTPin, DHTTYPE);

float humidity;

class HUMIDITY {
public:
    void begin(){
        dht.begin();
    }

    void readData(){
        humidity = dht.readHumidity();
    }

    void sendData(){
        Serial.print("Hum: ");
        Serial2.print("Hum: ");
        Serial.println(humidity);
        Serial2.println(humidity);
    }
};

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
        apc_.print("Hum: ");
        Serial.print(humidity);
        apc_.print(humidity);
    }
};
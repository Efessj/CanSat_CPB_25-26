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
        APC.print("Hum: ");
        Serial.println(humidity);
        APC.println(humidity);
    }

    String getData(){
        return String(humidity);
    }
};

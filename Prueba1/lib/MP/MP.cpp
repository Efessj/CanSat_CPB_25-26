#include <Arduino.h>
#include <DFRobot_BMP280.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <GLOBAL.cpp>


typedef DFRobot_BMP280_IIC    BMP;    // ******** use abbreviations instead of full names ********

BMP   bmp(&Wire, BMP::eSdoLow);
DallasTemperature ds18(&oneWire_);

unsigned long packet = 0;
uint32_t pressure;
float temp;
float altittude;

/*void setup()
{
  bmp.reset();
  Serial.println("bmp config test");
  while(bmp.begin() != BMP::eStatusOK) {
    Serial.println("bmp begin faild");
    printLastOperateStatus(bmp.lastOperateStatus);
    delay(2000);
  }
  Serial.println("bmp begin success");

  bmp.setConfigFilter(BMP::eConfigFilter_off);        // set config filter
  bmp.setConfigTStandby(BMP::eConfigTStandby_125);    // set standby tiempo
  bmp.setCtrlMeasSamplingTemp(BMP::eSampling_X8);     // set temperature over sampling
  bmp.setCtrlMeasSamplingPress(BMP::eSampling_X8);    // set pressure over sampling
  bmp.setCtrlMeasMode(BMP::eCtrlMeasModeNormal);      // set control measurement mode to make these settings effective

  delay(100);
}

void loop() {


  if (tiempo + 1000 < millis()){
    sendData();
  }
}
*/

class MP {
public:
  // show last sensor operate status
  void printLastOperateStatus(BMP::eStatus_t eStatus){
    switch(eStatus) {
      case BMP::eStatusOK:
        Serial.println("everything ok");
        apc_.println("everything ok");
        break;
      case BMP::eStatusErr:
        Serial.println("unknow error");
        apc_.println("unknow error");
        break;
      case BMP::eStatusErrDeviceNotDetected:
        Serial.println("device not detected");
        apc_.println("device not detected");
        break;
      case BMP::eStatusErrParameter:
        Serial.println("parameter error");
        apc_.println("parameter error");
        break;
      default:
        Serial.println("unknow status");
        apc_.println("unknow status");
        break;
    }
  }

  void begin(){
    bmp.reset();
    ds18.begin();
    Serial.println("bmp config test");
    apc_.println("bmp config test");

    if (bmp.begin() != BMP::eStatusOK) {
      Serial.println("bmp begin faild");
      apc_.println("bmp begin faild");
      printLastOperateStatus(bmp.lastOperateStatus);
      delay(1500);
    }

    Serial.println("bmp begin success");
    apc_.println("bmp begin success");


    bmp.setConfigFilter(BMP::eConfigFilter_off);        // set config filter
    bmp.setConfigTStandby(BMP::eConfigTStandby_125);    // set standby tiempo
    bmp.setCtrlMeasSamplingTemp(BMP::eSampling_X8);     // set temperature over sampling
    bmp.setCtrlMeasSamplingPress(BMP::eSampling_X8);    // set pressure over sampling
    bmp.setCtrlMeasMode(BMP::eCtrlMeasModeNormal);      // set control measurement mode to make these settings effective
  }

  void readData(){
    pressure = bmp.getPressure();
    //temp = bmp.getTemperature();
    ds18.requestTemperatures();
    temp = ds18.getTempCByIndex(0);
    altittude = bmp.calAltitude(SEA_LEVEL_PRESSURE, pressure);
  }

  void sendData() {
    Serial.print(packet);
    apc_.print(packet);
    Serial.print(" presió: ");
    apc_.print(" presió: ");
    Serial.print(pressure);
    apc_.print(pressure);
    Serial.print(" temperatura: ");
    apc_.print(" temperatura: ");
    Serial.print(temp);
    apc_.print(temp);
    Serial.print(" altitud: ");
    apc_.print(" altitud: ");
    Serial.print(altittude);
    apc_.print(altittude);

    packet ++;
  } 
};

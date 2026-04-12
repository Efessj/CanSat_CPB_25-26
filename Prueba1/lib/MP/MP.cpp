#include <Arduino.h>
#include <DFRobot_BMP280.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <GLOBAL.cpp>


typedef DFRobot_BMP280_IIC    BMP;    // ******** use abbreviations instead of full names ********
OneWire oneWire_(ONE_WIRE_BUS);
BMP   bmp(&Wire, BMP::eSdoLow);
DallasTemperature ds18(&oneWire_);


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
        Serial2.println("everything ok");
        break;
      case BMP::eStatusErr:
        Serial.println("unknow error");
        Serial2.println("unknow error");
        break;
      case BMP::eStatusErrDeviceNotDetected:
        Serial.println("device not detected");
        Serial2.println("device not detected");
        break;
      case BMP::eStatusErrParameter:
        Serial.println("parameter error");
        Serial2.println("parameter error");
        break;
      default:
        Serial.println("unknow status");
        Serial2.println("unknow status");
        break;
    }
  }

  void begin(){
    bmp.reset();
    ds18.begin();
    Serial.println("bmp config test");
    Serial2.println("bmp config test");

    if (bmp.begin() != BMP::eStatusOK) {
      Serial.println("bmp begin faild");
      Serial2.println("bmp begin faild");
      printLastOperateStatus(bmp.lastOperateStatus);
      delay(1500);
    } else {
      Serial.println("bmp begin success");
      Serial2.println("bmp begin success");
    }


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
    Serial.print(" presió: ");
    Serial2.print(" presió: ");
    Serial.print(pressure);
    Serial2.print(pressure);
    Serial.print(" temperatura: ");
    Serial2.print(" temperatura: ");
    Serial.print(temp);
    Serial2.print(temp);
    Serial.print(" altitud: ");
    Serial2.print(" altitud: ");
    Serial.println(altittude);
    Serial2.println(altittude);
  } 
};

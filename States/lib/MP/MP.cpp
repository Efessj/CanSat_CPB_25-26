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
        APC.println("everything ok");
        break;
      case BMP::eStatusErr:
        Serial.println("unknow error");
        APC.println("unknow error");
        break;
      case BMP::eStatusErrDeviceNotDetected:
        Serial.println("device not detected");
        APC.println("device not detected");
        break;
      case BMP::eStatusErrParameter:
        Serial.println("parameter error");
        APC.println("parameter error");
        break;
      default:
        Serial.println("unknow status");
        APC.println("unknow status");
        break;
    }
  }

  void begin(){
    bmp.reset();
    ds18.begin();
    Serial.println("bmp config test");
    APC.println("bmp config test");

    if (bmp.begin() != BMP::eStatusOK) {
      Serial.println("bmp begin faild");
      APC.println("bmp begin faild");
      printLastOperateStatus(bmp.lastOperateStatus);
      delay(1500);
    } else {
      Serial.println("bmp begin success");
      APC.println("bmp begin success");
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
    APC.print(" presió: ");
    Serial.print(pressure);
    APC.print(pressure);
    Serial.print(" temperatura: ");
    APC.print(" temperatura: ");
    Serial.print(temp);
    APC.print(temp);
    Serial.print(" altitud: ");
    APC.print(" altitud: ");
    Serial.println(altittude);
    APC.println(altittude);
  }

  String getData(){
    String data = String(pressure) + "," + String(temp) + "," + String(altittude);
    return data;
  }
};

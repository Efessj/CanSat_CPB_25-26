#include <Arduino.h>

#include <DFRobot_BMP280.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>


typedef DFRobot_BMP280_IIC    BMP;    // ******** use abbreviations instead of full names ********


#define SEA_LEVEL_PRESSURE 1018.05   // sea level pressure
#define BMP_VCC 15
#define ONE_WIRE_BUS 4

BMP   bmp(&Wire, BMP::eSdoLow);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

unsigned long tiempo = 0;
unsigned long packet = 0;
uint32_t pressure;
float temp;
float altittude;

void printLastOperateStatus(BMP::eStatus_t eStatus);
void sendData();

void setup()
{
  Serial.begin(9600);
  pinMode(BMP_VCC, OUTPUT);
  digitalWrite(BMP_VCC, HIGH);
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
  pressure = bmp.getPressure();
  //temp = bmp.getTemperature();
  sensors.requestTemperatures();
  temp = sensors.getTempCByIndex(0);
  altittude = bmp.calAltitude(SEA_LEVEL_PRESSURE, pressure);

  if (tiempo + 1000 < millis()){
    sendData();
  }
}

void sendData() {
  Serial.print(packet);
  Serial.print(" presió: ");
  Serial.print(pressure);
  Serial.print(" temperatura: ");
  Serial.print(temp);
  Serial.print(" altitud: ");
  Serial.println(altittude);
  packet ++;
  tiempo = millis();
}

// show last sensor operate status
void printLastOperateStatus(BMP::eStatus_t eStatus)
{
  switch(eStatus) {
  case BMP::eStatusOK:    Serial.println("everything ok"); break;
  case BMP::eStatusErr:   Serial.println("unknow error"); break;
  case BMP::eStatusErrDeviceNotDetected:    Serial.println("device not detected"); break;
  case BMP::eStatusErrParameter:    Serial.println("parameter error"); break;
  default: Serial.println("unknow status"); break;
  }
}
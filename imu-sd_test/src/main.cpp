#include <Arduino.h>
#include <GLOBAL.cpp>
#include <MICROSD.cpp>
#include <IMU.cpp>

IMU imu;
MICROSD sd;

File imuFile;

void setup() {
  Serial.begin(9600);

  //printf("sizeof(Sample) = %lu\n", sizeof(Sample));

  imu.begin();
  imu.calcOffset();
  sd.begin();
  imuFile = SD.open("/imu_data.bin", FILE_WRITE);

  Serial.println("Setup completo");
  delay(1000);
}

void loop() {
  imu.readData();
  Serial.print("Aceleracion: ");
  Serial.println(imu.getAccelModule(), 3);
  sd.saveOneSecond(imuFile, imu);

  delay(1000);
}

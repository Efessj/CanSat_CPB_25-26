#include <Arduino.h>

#include <Wire.h>
#include <MPU9250_asukiaaa.h>

MPU9250_asukiaaa mpu;

enum mode {
  ACELERACION, GIROSCOPIO
};
mode currentMode = ACELERACION;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.setWire(&Wire);
  mpu.beginAccel();
  mpu.beginGyro();
  mpu.beginMag();
}

void loop() {
  switch (currentMode){
    case ACELERACION:
      mpu.accelUpdate();
      Serial.print("Acel (g): ");
      Serial.print(mpu.accelX(), 3); Serial.print(", ");
      Serial.print(mpu.accelY(), 3); Serial.print(", ");
      Serial.println(mpu.accelZ(), 3);
      break;
    case GIROSCOPIO:
      mpu.gyroUpdate();
      Serial.print("Gyro (°/s): ");
      Serial.print(mpu.gyroX(), 3); Serial.print(", ");
      Serial.print(mpu.gyroY(), 3); Serial.print(", ");
      Serial.println(mpu.gyroZ(), 3);
      break;
    default:
      Serial.println("Unknown mode");
      break;
  }

  delay(500);
}


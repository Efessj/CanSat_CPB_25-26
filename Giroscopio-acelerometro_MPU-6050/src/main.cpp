#include <Arduino.h>

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

enum mode {
  ACELERACION, GIROSCOPIO
};
mode currentMode = GIROSCOPIO;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 conectado correctamente");
  } else {
    Serial.println("Error al conectar MPU6050");
  }
}

void loop() {
  switch (currentMode){
    case ACELERACION:
      //mpu.accelUpdate();
      Serial.print("Acel (g): ");
      Serial.print(mpu.getAccelerationX()/ 16384.0, 3); Serial.print(", ");
      Serial.print(mpu.getAccelerationY()/ 16384.0, 3); Serial.print(", ");
      Serial.println(mpu.getAccelerationZ()/ 16384.0, 3);
      break;
    case GIROSCOPIO:
      //mpu.gyroUpdate();
      Serial.print("Gyro (°/s): ");
      Serial.print(mpu.getRotationX()/ 131.0, 3); Serial.print(", ");
      Serial.print(mpu.getRotationY()/ 131.0, 3); Serial.print(", ");
      Serial.println(mpu.getRotationZ()/ 131.0, 3);
      break;
    default:
      Serial.println("Unknown mode");
      break;
  }

  delay(500);
}


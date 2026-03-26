#include <Arduino.h>
#include <GLOBAL.cpp>
#include <MPU6050.h>
#include <Wire.h>

float acceleration[3] = {0,0,0};
float angularVelocity[3] = {0,0,0};
float accelerationOffset[3] = {0,0,0};
float angularVelocityOffset[3] = {0,0,0};
MPU6050 mpu;

class IMU {
public:
    void begin(){
        Wire.begin();
        mpu.initialize();
        if (mpu.testConnection()) {
            Serial.println("MPU6050 conectado correctamente");
        } else {
            Serial.println("Error al conectar MPU6050");
        }
    }

    void calcOffset(){
        Serial.println("**NO MOVER CanSat-Calculando offset del IMU...");

        delay(2000); // Esperar 2 segundos para estabilizar el sensor

        unsigned long lastTime = micros();
        int i = 0;
        while (i < 100) {
            unsigned long currentTime = micros();
            if (currentTime - lastTime >= 5000UL) {
                accelerationOffset[0] += mpu.getAccelerationX();
                accelerationOffset[1] += mpu.getAccelerationY();
                accelerationOffset[2] += mpu.getAccelerationZ();
                angularVelocityOffset[0] += mpu.getRotationX();
                angularVelocityOffset[1] += mpu.getRotationY();
                angularVelocityOffset[2] += mpu.getRotationZ();
                lastTime = currentTime;
                i++;
            }
        }
        accelerationOffset[0] /= 100;
        accelerationOffset[1] /= 100;
        accelerationOffset[2] /= 100;
        angularVelocityOffset[0] /= 100;
        angularVelocityOffset[1] /= 100;
        angularVelocityOffset[2] /= 100;
        delay(100);
        Serial.println("Offset del IMU calculado");
    }

    void readData(){
        acceleration[0] = (mpu.getAccelerationX() - accelerationOffset[0]) / 16384.0;
        acceleration[1] = (mpu.getAccelerationY() - accelerationOffset[1]) / 16384.0;
        acceleration[2] = (mpu.getAccelerationZ() - accelerationOffset[2]) / 16384.0;
        angularVelocity[0] = (mpu.getRotationX() - angularVelocityOffset[0]) / 131.0;
        angularVelocity[1] = (mpu.getRotationY() - angularVelocityOffset[1]) / 131.0;
        angularVelocity[2] = (mpu.getRotationZ() - angularVelocityOffset[2]) / 131.0;
    }

    void sendData(){
        Serial.print("Acel: ");
        apc_.print("Acel: ");
        Serial.print(acceleration[0], 3); Serial.print(", ");
        apc_.print(acceleration[0], 3); apc_.print(", ");
        Serial.print(acceleration[1], 3); Serial.print(", ");
        apc_.print(acceleration[1], 3); apc_.print(", ");
        Serial.println(acceleration[2], 3);
        apc_.println(acceleration[2], 3);
        Serial.print("Gyro: ");
        apc_.print("Gyro: ");
        Serial.print(angularVelocity[0], 3); Serial.print(", ");
        apc_.print(angularVelocity[0], 3); apc_.print(", ");
        Serial.print(angularVelocity[1], 3); Serial.print(", ");
        apc_.print(angularVelocity[1], 3); apc_.print(", ");
        Serial.println(angularVelocity[2], 3);
        apc_.println(angularVelocity[2], 3);
    }
};
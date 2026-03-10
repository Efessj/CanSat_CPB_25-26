#include <Arduino.h>
#include <GLOBAL.cpp>
#include <MPU9250_asukiaaa.h>
#include <Wire.h>

float acceleration[3] = {0,0,0};
float angularVelocity[3] = {0,0,0};
float accelerationOffset[3] = {0,0,0};
float angularVelocityOffest[3] = {0,0,0};
MPU9250_asukiaaa mpu;

class IMU {
public:
    void begin(){
        mpu.setWire(&Wire);
        mpu.beginAccel();
        mpu.beginGyro();
    }

    void calcOffset(){
        unsigned long lastTime = micros();
        int i = 0;
        while (i < 100) {
            unsigned long currentTime = micros();
            if (currentTime - lastTime >= 5000UL) {
                mpu.accelUpdate();
                accelerationOffset[0] += mpu.accelX();
                accelerationOffset[1] += mpu.accelY();
                accelerationOffset[2] += mpu.accelZ();
                mpu.gyroUpdate();
                angularVelocity[0] += mpu.gyroX();
                angularVelocity[1] += mpu.gyroY();
                angularVelocity[2] += mpu.gyroZ();
                lastTime = currentTime;
                i++;
            }
        }
        accelerationOffset[0] /= 100;
        accelerationOffset[1] /= 100;
        accelerationOffset[2] /= 100;
        angularVelocityOffest[0] /= 100;
        angularVelocityOffest[1] /= 100;
        angularVelocityOffest[2] /= 100;
        delay(100);
    }

    void readData(){
        mpu.accelUpdate();
        acceleration[0] = mpu.accelX() - accelerationOffset[0];
        acceleration[1] = mpu.accelY() - accelerationOffset[1];
        acceleration[2] = mpu.accelZ() - accelerationOffset[2];
        mpu.gyroUpdate();
        angularVelocity[0] = mpu.gyroX() - angularVelocityOffest[0];
        angularVelocity[1] = mpu.gyroY() - angularVelocityOffest[1];
        angularVelocity[2] = mpu.gyroZ() - angularVelocityOffest[2];
    }

    void sendData(){
        Serial.print("Acel: ");
        apc_.print("Acel: ");
        Serial.print(acceleration[0], 3); Serial.print(", ");
        apc_.print(acceleration[1], 3); Serial.print(", ");
        Serial.print(acceleration[1], 3); Serial.print(", ");
        apc_.print(acceleration[1], 3); Serial.print(", ");
        Serial.println(acceleration[2], 3);
        apc_.println(acceleration[2], 3);
        Serial.print("Gyro: ");
        apc_.print("Gyro: ");
        Serial.print(angularVelocity[0], 3); Serial.print(", ");
        apc_.print(angularVelocity[0], 3); Serial.print(", ");
        Serial.print(angularVelocity[1], 3); Serial.print(", ");
        apc_.print(angularVelocity[1], 3); Serial.print(", ");
        Serial.println(angularVelocity[2], 3);
        apc_.println(angularVelocity[2], 3);
    }
};
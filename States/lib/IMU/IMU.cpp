#include <Arduino.h>
#include <GLOBAL.cpp>
#include <MPU6050.h>
#include <Wire.h>
#include <math.h>

#ifndef IMU_H
#define IMU_H

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
        for (int i = 0; i < 3; i++) {
            acceleration[i] = 0;
            angularVelocity[i] = 0;
        }

        delay(2000); // Esperar 2 segundos para estabilizar el sensor

        unsigned long lastTime = micros();
        int i = 0;
        while (i < 100) {
            unsigned long currentTime = micros();
            if (currentTime - lastTime >= 5000UL) {
                int16_t ax, ay, az, gx, gy, gz;
                mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
                accelerationOffset[0] += (ax / 16384.0);
                accelerationOffset[1] += (ay / 16384.0);
                accelerationOffset[2] += (az / 16384.0);
                angularVelocityOffset[0] += (gx / 131.0);
                angularVelocityOffset[1] += (gy / 131.0);
                angularVelocityOffset[2] += (gz / 131.0);
                lastTime = currentTime;
                i++;
            }
        }

        for (int i = 0; i < 3; i++) {
            accelerationOffset[i] /= 100.0;
            angularVelocityOffset[i] /= 100.0;
        }

        int axis = 0;
        float maxVal = abs(accelerationOffset[0]);

        for (int i = 1; i < 3; i++) {
            if (abs(accelerationOffset[i]) > maxVal) {
                maxVal = abs(accelerationOffset[i]);
                axis = i;
            }
        }

        if (accelerationOffset[axis] > 0) {
            accelerationOffset[axis] -= 1;
        } else {
            accelerationOffset[axis] += 1;
        }

        
        delay(100);
        Serial.println("Offset del IMU calculado");
    }

    void readData(){
        int16_t ax, ay, az, gx, gy, gz;
        mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        acceleration[0] = (ax / 16384.0 - accelerationOffset[0]);
        acceleration[1] = (ay / 16384.0 - accelerationOffset[1]);
        acceleration[2] = (az / 16384.0 - accelerationOffset[2]);
        angularVelocity[0] = (gx / 131.0 - angularVelocityOffset[0]);
        angularVelocity[1] = (gy / 131.0 - angularVelocityOffset[1]);
        angularVelocity[2] = (gz / 131.0 - angularVelocityOffset[2]);
    }

    void readDataSD(Sample &sample){
        int16_t ax, ay, az, gx, gy, gz;
        mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        sample.ax = ax / 16384.0 - accelerationOffset[0];
        sample.ay = ay / 16384.0 - accelerationOffset[1];
        sample.az = az / 16384.0 - accelerationOffset[2];
        sample.gx = gx / 131.0 - angularVelocityOffset[0];
        sample.gy = gy / 131.0 - angularVelocityOffset[1];
        sample.gz = gz / 131.0 - angularVelocityOffset[2];
        sample.t = micros();
    }

    void sendData(){
        Serial.print("Acel: ");
        APC.print("Acel: ");
        Serial.print(acceleration[0], 3); Serial.print(", ");
        APC.print(acceleration[0], 3); APC.print(", ");
        Serial.print(acceleration[1], 3); Serial.print(", ");
        APC.print(acceleration[1], 3); APC.print(", ");
        Serial.print(acceleration[2], 3);
        APC.print(acceleration[2], 3);
        Serial.print(", Gyro: ");
        APC.print(", Gyro: ");
        Serial.print(angularVelocity[0], 3); Serial.print(", ");
        APC.print(angularVelocity[0], 3); APC.print(", ");
        Serial.print(angularVelocity[1], 3); Serial.print(", ");
        APC.print(angularVelocity[1], 3); APC.print(", ");
        Serial.println(angularVelocity[2], 3);
        APC.println(angularVelocity[2], 3);
    }

    float getAccelModule(){
        return sqrt(acceleration[0]*acceleration[0] + acceleration[1]*acceleration[1] + acceleration[2]*acceleration[2]);
    }
};


#endif
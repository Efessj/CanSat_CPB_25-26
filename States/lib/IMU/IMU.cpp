#include <Arduino.h>
#include <GLOBAL.cpp>
#include <MPU6050.h>
#include <Wire.h>
#include <math.h>

#ifndef IMU_H
#define IMU_H

float acceleration[3] = {0,0,0};
float angularVelocity[3] = {0,0,0};
int16_t accelerationOffset[3] = {0,0,0};
int16_t angularVelocityOffset[3] = {0,0,0};
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
                accelerationOffset[0] += (ax);
                accelerationOffset[1] += (ay);
                accelerationOffset[2] += (az);
                angularVelocityOffset[0] += (gx);
                angularVelocityOffset[1] += (gy);
                angularVelocityOffset[2] += (gz);
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
            accelerationOffset[axis] -= ACCEL_SCALE;
        } else {
            accelerationOffset[axis] += ACCEL_SCALE;
        }

        
        delay(100);
        Serial.println("Offset del IMU calculado");
    }

    void readData(){
        int16_t ax, ay, az, gx, gy, gz;
        mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        acceleration[0] = ((ax  - accelerationOffset[0])/ ACCEL_SCALE);
        acceleration[1] = ((ay - accelerationOffset[1]) / ACCEL_SCALE);
        acceleration[2] = ((az - accelerationOffset[2]) / ACCEL_SCALE);
        angularVelocity[0] = ((gx - angularVelocityOffset[0]) / GYRO_SCALE);
        angularVelocity[1] = ((gy - angularVelocityOffset[1]) / GYRO_SCALE);
        angularVelocity[2] = ((gz - angularVelocityOffset[2]) / GYRO_SCALE);
    }

    void readDataSD(Sample &sample){
        int16_t ax, ay, az, gx, gy, gz;
        mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        sample.ax = (ax  - accelerationOffset[0]);
        sample.ay = (ay - accelerationOffset[1]);
        sample.az = (az - accelerationOffset[2]);
        sample.gx = (gx - angularVelocityOffset[0]);
        sample.gy = (gy - angularVelocityOffset[1]);
        sample.gz = (gz - angularVelocityOffset[2]);
        sample.t = micros();

        Serial.print("Sample: ");
        Serial.print(sample.ax); Serial.print(", ");
        Serial.print(sample.ay); Serial.print(", ");
        Serial.print(sample.az); Serial.print(", ");
        Serial.print(sample.gx); Serial.print(", ");
        Serial.print(sample.gy); Serial.print(", ");
        Serial.println(sample.gz);
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
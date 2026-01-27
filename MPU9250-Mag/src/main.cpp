#include <Arduino.h>
#include <Wire.h>

#include <Wire.h>

#define MPU_ADDR 0x68  // Dirección del MPU9250 (AD0=0)
#define AK_ADDR  0x0C  // Dirección del magnetómetro AK8963

// Funciones auxiliares I2C
void writeMPU(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

uint8_t readAK(uint8_t reg) {
  Wire.beginTransmission(AK_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(AK_ADDR, (uint8_t)1);
  if (Wire.available()) return Wire.read();
  return 0xFF;
}

void writeAK(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(AK_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(115200);
  Wire.begin(); // SDA=21, SCL=22
  delay(100);

  // Despertar MPU9250
  writeMPU(0x6B, 0x00);
  delay(10);

  // Activar bypass I2C para acceder al magnetómetro directamente
  writeMPU(0x37, 0x02); // BYPASS_EN = 1
  delay(10);

  // Comprobar AK8963 WHO_AM_I
  uint8_t who = readAK(0x00);
  Serial.print("AK8963 WHO_AM_I = 0x");
  Serial.println(who, HEX); // debe ser 0x48
  if(who != 0x48){
    Serial.println("Error: magnetometro no detectado!");
    while(1);
  }

  // Reset del AK8963
  writeAK(0x0B, 0x01);
  delay(100);

  // Modo continuo 16-bit, 100Hz
  writeAK(0x0A, 0x16);
  delay(10);

  Serial.println("Magnetómetro listo...");
}

void loop() {
  // Leer registro de estado ST1
  uint8_t st1 = readAK(0x02);
  if (st1 & 0x01) { // Data ready
    Wire.beginTransmission(AK_ADDR);
    Wire.write(0x03); // Primer registro de datos: HXL
    Wire.endTransmission(false);
    Wire.requestFrom(AK_ADDR, (uint8_t)7); // HXL..HZH + ST2
    if (Wire.available() >= 7) {
      int16_t hx = (int16_t)(Wire.read() | (Wire.read() << 8));
      int16_t hy = (int16_t)(Wire.read() | (Wire.read() << 8));
      int16_t hz = (int16_t)(Wire.read() | (Wire.read() << 8));
      uint8_t st2 = Wire.read();
      if (!(st2 & 0x08)) { // Revisar overflow
        Serial.print("Mag X: "); Serial.print(hx);
        Serial.print("  Y: "); Serial.print(hy);
        Serial.print("  Z: "); Serial.println(hz);
      } else {
        Serial.println("Overflow de magnetómetro, ignorando lectura");
      }
    }
  }
  delay(50); // 20Hz aprox
}

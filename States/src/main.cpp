#include <Arduino.h>

#include <GLOBAL.cpp>
#include <MP.cpp>
#include <LUX.cpp>
#include <IMU.cpp>
#include <HUMIDITY.cpp>
#include <MICROSD.cpp>

/*
SCL - 21
SDA - 22
OneWire - 19 (cambiar en global)
MOSI - 23
MISO - 19
SCK  - 18
CS   - 32

estructura de CSV:
paket  temp  press  altitud  hum  lux  accel(modulo)
*/

double accelerationModule = 0;
bool dataDumping = false;
uint8_t dataDumpFile;
#define FILE_DATA 1
#define FILE_IMU 2

enum states {
  WAITING, LIFTING_OFF, FLYING, RESCUIT, DATA_DUMP, SURVIVEING
};
states currentState = WAITING;


MP mp;
LUX light;
IMU imu;
HUMIDITY hum;
MICROSD sd;

unsigned long workingTime = 0;
unsigned long packet = 0;
File imuFile;

void sendIdentifier(){
    Serial.print(packet);
    Serial2.print(packet);
    Serial.print(":Island Sunnergy:");
    Serial2.print(":Island Sunnergy:");
}

//leer datos de sensores
void DataCollection();
//enviar datos pos serial y apc
void DataTransmission();
void ReadSerial();
void ToggleComponents(uint8_t apc, uint8_t pcb, uint8_t sd, uint8_t power);
void Buzzer(bool on);

void Waiting();
void LiftingOff();
void Flying();
void Rescuit();
void DataDump();
void Surviveing();

void setup() {
  Serial.begin(9600);

  //buzzer
  ledcSetup(0, 2000, 8);
  ledcAttachPin(BZZ, 0);
}

void loop() {
  ReadSerial();

  switch (currentState) {
    case WAITING:
        Waiting();
        break;
    case LIFTING_OFF:
        LiftingOff();
        break;
    case FLYING:
        Flying();
        break;
    case RESCUIT:
        Rescuit();
        break;
    case DATA_DUMP:
        DataDump();
        break;
    case SURVIVEING:
        Surviveing();
        break;
    default:
        //Serial.println("Estado desconocido");
        break;
  }
}

void ToggleComponents(uint8_t apc, uint8_t pcb, uint8_t sd, uint8_t power) {
  digitalWrite(VCC_APC, apc);
  digitalWrite(VCC_PCB_UP, pcb);
  digitalWrite(VCC_SD, sd);
  digitalWrite(VCC_POWER, power);
}

void ReadSerial() {
  while (APC.available()) {
    char c = APC.read();
    switch (c) {
      case 'l':
        currentState = LIFTING_OFF;
        break;
      case 'f':
        currentState = FLYING;
        break;
      case 'r':
        currentState = RESCUIT;
        break;
      case 'd':
        currentState = DATA_DUMP;
        dataDumpFile = FILE_DATA;
        break;
      case 'i':
        currentState = DATA_DUMP;
        dataDumpFile = FILE_IMU;
        break;
      case 's':
        currentState = SURVIVEING;
        break;
      default:
        //Serial.println("Comando desconocido");
        break;
    }
  }
}

void Buzzer(bool on) {
  if (on) ledcWriteTone(0, 1000);
  else ledcWriteTone(0, 0);
}

void Waiting() {
  //Serial.println("Esperando");
  ToggleComponents(HIGH, LOW, LOW, HIGH);
  delay(1000);

  APC.begin(9600, SERIAL_8N1, TXD2, RXD2);
  imu.begin();
  imu.calcOffset();

  while (true){
    imu.readData();
    accelerationModule = imu.getAccelModule();
    APC.print("IslandSunnergy:");     Serial.print("IslandSunnergy:");
    APC.print("WAITING: ");           Serial.print("WAITING: ");
    APC.print("Aceleracion: ");       Serial.print("Aceleracion: ");
    APC.print(accelerationModule, 3); Serial.println(accelerationModule, 3);

    ReadSerial();

    delay(100);
    
    if (currentState != WAITING) break;
  }
}


void LiftingOff() {
  //Serial.println("Despegando");
  ToggleComponents(HIGH, HIGH, HIGH, HIGH);
  delay(1000);
  mp.begin();
  light.begin();
  hum.begin();
  sd.begin();

  delay(500);

  sd.writeCSV("/data.csv", "paket,temp,press,altitud,hum,lux,accel(modulo)\n");

  while (true){
    imu.readData();
    accelerationModule = imu.getAccelModule();
    APC.print("IslandSunnergy: ");    Serial.print("IslandSunnergy: ");
    APC.print("LIFTING_OFF: ");       Serial.print("LIFTING_OFF: ");
    APC.print("Aceleracion: ");       Serial.print("Aceleracion: ");
    APC.print(accelerationModule, 3); Serial.println(accelerationModule, 3);

    ReadSerial();

    delay(100);

    if (currentState != LIFTING_OFF) break;
  }
  //if (accelerationModule < 10.0) currentState = FLYING;
}

void Flying() {
  //Serial.println("Volando");
  workingTime = millis()+1000;

  while (true){
    if (workingTime < millis()){
      DataCollection();
      DataTransmission();
      accelerationModule = imu.getAccelModule();

      String dataline = String(packet) + "," + mp.getData() + "," + light.getData() + "," + hum.getData() + "," + String(accelerationModule, 3) + "\n";
      sd.appendCSV("/data.csv", dataline);

      workingTime += 1000;
      packet++;
    }
    

    ReadSerial();

    if (currentState != FLYING || (accelerationModule > 0.5 && accelerationModule < 1.1)) break;
  }
  

  //if (accelerationModule > 10.0) currentState = RESCUIT;
}

void Rescuit() {
  //Serial.println("Rescatando");
  if (dataDumping) currentState = DATA_DUMP;
  else currentState = SURVIVEING;
}

void DataDump() {
  //Serial.println("Volcando");
}

void Surviveing() {
  //Serial.println("Sobreviviendo");
  if (dataDumping) currentState = DATA_DUMP;
}


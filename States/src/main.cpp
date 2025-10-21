#include <Arduino.h>

float acceleration = 0;
bool dataDumping = false;

enum states {
  WAITING, LIFTING_OFF, FLYING, RESCUIT, DATA_DUMP, SURVIVEING
};
states currentState = WAITING;

void PrimaryMision();
void TertiaryMision();
void QuaternaryMision();
void Waiting();
void LiftingOff();
void Flying();
void Rescuit();
void DataDump();
void Surviveing();

void setup() {

}

void loop() {
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
        Serial.println("Estado desconocido");
        break;
  }
}

void PrimaryMision(){}
void TertiaryMision(){}
void QuaternaryMision(){}

void Waiting() {
  Serial.println("Esperando");

  if (acceleration > 20){
    currentState = LIFTING_OFF;
    return;
  }
}

void LiftingOff() {
  Serial.println("Despegando");
  if (acceleration < -10) currentState = FLYING;
}

void Flying() {
  Serial.println("Volando");
  if (acceleration > 10) currentState = RESCUIT;
}

void Rescuit() {
  Serial.println("Rescatando");
  if (dataDumping) currentState = DATA_DUMP;
  else currentState = SURVIVEING;
}

void DataDump() {
  Serial.println("Volcando");
}

void Surviveing() {
  Serial.println("Sobreviviendo");
  if (dataDumping) currentState = DATA_DUMP;
}


#include <Arduino.h>
#define BZZ 5

void setup() {
  ledcSetup(0, 2000, 8);
  ledcAttachPin(BZZ, 0);
}

void loop() {
  ledcWriteTone(0, 440);
  delay(1000);
  ledcWriteTone(0, 220);
  delay(1000);
}

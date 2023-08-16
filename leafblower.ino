#include <Servo.h>

#define EDF_LEFT 5
#define EDF_RIGHT 6

#define DELAY 1000

#define RAMP_TIME 1000

// max is 1000
#define ZERO 1000
#define POWER 1000

Servo edfLeft;
Servo edfRight;
Servo ledBuiltin;

void setAll(int val) {
  edfLeft.writeMicroseconds(val + ZERO);
  edfRight.writeMicroseconds(val + ZERO);
  ledBuiltin.writeMicroseconds(val + ZERO);
}

void setup() {
  edfLeft.attach(EDF_LEFT);
  edfRight.attach(EDF_RIGHT);
  ledBuiltin.attach(LED_BUILTIN);
  setAll(0);

  while (millis() < DELAY) {}
  while((millis() - DELAY) < RAMP_TIME) {
    setAll((POWER * (millis() - DELAY)) / RAMP_TIME);
  }
  setAll(POWER);
}

void loop() {
}

#include <Servo.h>

#define EDF_LEFT 5
#define EDF_RIGHT 6

#define OFF_PIN 8
#define FULLPOWER_PIN 9

#define LOOP_STEP 50
#define LOOP_DELAY 50

#define ZERO 1000
// 0-1000
#define OFF_POWER 0
#define ENDU_POWER 80
#define FULL_POWER 1000

Servo edfLeft;
Servo edfRight;
Servo ledBuiltin;

int current_value = OFF_POWER;
int target_value = OFF_POWER;

void setAll() {
  edfLeft.writeMicroseconds(current_value + ZERO);
  edfRight.writeMicroseconds(current_value + ZERO);
  ledBuiltin.writeMicroseconds(current_value + ZERO);
}

void setup() {
  edfLeft.attach(EDF_LEFT);
  edfRight.attach(EDF_RIGHT);
  ledBuiltin.attach(LED_BUILTIN);
  setAll();

  pinMode(OFF_PIN, INPUT_PULLUP);
  pinMode(FULLPOWER_PIN, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(OFF_PIN) == LOW) {
    target_value = OFF_POWER;
  } else if (digitalRead(FULLPOWER_PIN) == LOW) {
    target_value = FULL_POWER;
  } else {
    target_value = ENDU_POWER;
  }
  if (current_value < target_value) {
    current_value += LOOP_STEP ;
    current_value = min(current_value, target_value);
  } else if (current_value > target_value) {
    current_value -= LOOP_STEP;
    current_value = max(current_value, target_value);
  }
  setAll();

  delay(LOOP_DELAY);
}

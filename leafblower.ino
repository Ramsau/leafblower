#include <Servo.h>

#define EDF_LEFT 5
#define EDF_RIGHT 6

#define OFF_PIN 8
#define FULLPOWER_PIN 9

#define LOOP_STEP 5
#define LOOP_DELAY 50

#define ZERO 1000
// 0-1000
#define OFF_POWER 0
#define ENDU_POWER 80
#define FULL_POWER 1000

#define OFF_ANGLE 0
#define ENDU_ANGLE 14
#define FULL_ANGLE 180

Servo edfLeft;
Servo edfRight;
Servo ledBuiltin;

int current_value = OFF_ANGLE;
int target_value = OFF_ANGLE;

void setAll() {
  // edfLeft.writeMicroseconds(current_value + ZERO);
  // edfRight.writeMicroseconds(current_value + ZERO);
  // ledBuiltin.writeMicroseconds(current_value + ZERO);
  edfLeft.write(current_value);
  edfRight.write(current_value);
  ledBuiltin.write(current_value);  
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
    // target_value = OFF_POWER;
    target_value = OFF_ANGLE;
  } else if (digitalRead(FULLPOWER_PIN) == LOW) {
    // target_value = FULL_POWER;
    target_value = FULL_ANGLE;
  } else {
    // target_value = ENDU_POWER;
    target_value = ENDU_ANGLE;
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

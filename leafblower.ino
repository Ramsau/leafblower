#include <Servo.h>

#define EDF_LEFT 5
#define EDF_RIGHT 6

#define POWER_PIN 8


#define RAMP_TIME 1000
#define LOOP_DELAY 100

#define ZERO 1000
// 0-1000
#define LOW_POWER 0
#define FULL_POWER 1000

Servo edfLeft;
Servo edfRight;
Servo ledBuiltin;

int current_value = LOW_POWER;
int target_value = LOW_POWER;

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

  pinMode(POWER_PIN, INPUT);
}

void loop() {
  bool input = digitalRead(POWER_PIN);
  target_value = input ? FULL_POWER : LOW_POWER;
  if (current_value < target_value) {
    current_value += 1000 * RAMP_TIME / LOOP_DELAY;
    current_value = min(current_value, target_value);
  } else if (current_value > target_value) {
    current_value -= 1000 * RAMP_TIME / LOOP_DELAY;
    current_value = max(current_value, target_value);
  }
  setAll();

  delay(LOOP_DELAY);
}

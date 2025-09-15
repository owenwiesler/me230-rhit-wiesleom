#include <Stepper.h>

const int stepsPerRevolution = 2048;  // 32 steps * 64:1 gearhead
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
void setup() {
  myStepper.setSpeed(5); 
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
}


void loop() {
  // step one revolution  in one direction:
  if (!digitalRead(2)) {
    myStepper.step(stepsPerRevolution/4);
    delay(500);
  }

  // step one revolution in the other direction:
  if (!digitalRead(3)) {
    myStepper.step(-stepsPerRevolution/4);
    delay(500);
  }

}

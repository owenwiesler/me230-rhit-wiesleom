#include <Servo.h>

Servo esc;

const int escPin = 9;            // ESC signal connected to D9
const int minThrottle = 1000;    // Minimum pulse width (0%)
const int maxThrottle = 2000;    // Maximum pulse width (100%)
const int targetThrottle = 1500; // 50% throttle

void setup() {
  esc.attach(escPin);
  
  // Arm the ESC at minimum throttle
  esc.writeMicroseconds(minThrottle);
  delay(2000);  // Wait 2 seconds for arming

  int rampTime = 5000; // milliseconds for ramp up or down
  int steps = 100;     // number of increments
  int stepDelay = rampTime / steps;

  // --- Ramp Up to 50% ---
  for (int i = 0; i <= steps; i++) {
    int throttle = map(i, 0, steps, minThrottle, targetThrottle);
    esc.writeMicroseconds(throttle);
    delay(stepDelay);
  }

  // --- Ramp Down to 0% ---
  for (int i = steps; i >= 0; i--) {
    int throttle = map(i, 0, steps, minThrottle, targetThrottle);
    esc.writeMicroseconds(throttle);
    delay(stepDelay);
  }

  // Stop at 0% throttle
  esc.writeMicroseconds(minThrottle);
}

void loop() {
  // Do nothing — the ramp runs once only
}

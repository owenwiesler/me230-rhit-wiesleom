#include <Servo.h>

Servo esc;

const int escPin = 9;           // ESC signal
const int potPin = A0;          // Potentiometer input

const int minThrottle = 1000;   // 0% throttle
const int maxThrottle = 1250;   // 25% throttle

void setup() {
  esc.attach(escPin);
  
  // Arm the ESC at 0% throttle
  esc.writeMicroseconds(minThrottle);
  delay(2000);  // Wait for arming
}

void loop() {
  int potValue = analogRead(potPin);  // 0–1023
  int throttle = map(potValue, 0, 1023, minThrottle, maxThrottle);
  
  esc.writeMicroseconds(throttle);
  delay(20);  // Update every 20 ms (typical ESC refresh rate)
}

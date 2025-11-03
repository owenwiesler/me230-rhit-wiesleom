#include <PIO_DShot.h>

#define PIN            15      // ESC signal pin
#define POT_PIN        26      // potentiometer input (GP26 = ADC0)
#define MOTOR_POLES    6
#define MAX_THROTTLE   400
#define THRESHOLD      80      // increase if motor twitches at idle

BidirDShotX1 *esc;
uint16_t throttle = 0;
uint32_t rpm = 0;

void setup() {
  Serial.begin(115200);
  delay(500);

  esc = new BidirDShotX1(PIN);   // use pin 15 now
  delay(500);

  Serial.println("ESC ready — turn the potentiometer slowly.");
}

void loop() {
  delayMicroseconds(200);

  esc->getTelemetryErpm(&rpm);
  rpm /= MOTOR_POLES / 2;

  int potValue = analogRead(POT_PIN);

  if (potValue <= THRESHOLD) {
    throttle = 0;
  } else {
    throttle = map(potValue, THRESHOLD, 1023, 0, MAX_THROTTLE);
    throttle = constrain(throttle, 0, MAX_THROTTLE);
  }

  uint16_t sendValue = (throttle > 0) ? throttle + 48 : 0;
  esc->sendThrottle(sendValue);

  static uint32_t lastPrint = 0;
  if (millis() - lastPrint > 200) {
    lastPrint = millis();
    Serial.print("Pot: ");
    Serial.print(potValue);
    Serial.print("  Throttle: ");
    Serial.print(throttle);
    Serial.print("  Send: ");
    Serial.print(sendValue);
    Serial.print("  RPM: ");
    Serial.println(rpm);
  }
}

#include <Servo.h>
Servo esc;

const int escPin = 9;          // PWM to ESC
const int potPin = A0;         // Potentiometer input
const int polePairs = 3;       // Your 6 magnets = 3 pole pairs

// --- telemetry config ---
#define TELEMETRY Serial1      // Mega RX1 = pin 19
#define TELEMETRY_BAUD 115200

// Increase serial buffer size (temporary software buffer)
#define LOCAL_BUFFER 200
byte frame[10];
byte localBuf[LOCAL_BUFFER];

unsigned long lastGood = 0;

// -------------------------

// Calculate CRC (simple 8-bit sum, as BLHeli_32 uses)
byte calcCRC(byte *data, byte len) {
  byte crc = 0;
  for (byte i = 0; i < len - 1; i++) crc += data[i];
  return crc;
}

void setup() {
  Serial.begin(115200);
  TELEMETRY.begin(TELEMETRY_BAUD);
  esc.attach(escPin, 1000, 2000);

  Serial.println("\n=== BLHeli_32 Telemetry Reader (Mega tuned) ===");
  Serial.println("Use pot to control throttle (0–25%)");
}

void loop() {
  // --- PWM control ---
  int potValue = analogRead(potPin);
  float throttle = (float)potValue / 1023.0 * 0.25;  // 0–25%
  int pulse = 1000 + (int)(throttle * 1000.0);
  esc.writeMicroseconds(pulse);

  // --- telemetry read ---
  if (TELEMETRY.available() >= 10) {
    TELEMETRY.readBytes(frame, 10);  // read one full 10-byte frame

    byte crc = calcCRC(frame, 10);
    if (crc == frame[9]) {
      lastGood = millis();

      unsigned int erpm   = (frame[1] << 8) | frame[0];
      unsigned int volts  = (frame[3] << 8) | frame[2];
      unsigned int amps   = (frame[5] << 8) | frame[4];
      unsigned int temp   = (frame[7] << 8) | frame[6];

      float mechRPM = (float)erpm / polePairs;
      float voltage = volts / 100.0;   // typical scaling
      float current = amps / 100.0;
      float tempC   = temp / 100.0;

      Serial.print("RPM: "); Serial.print(mechRPM, 0);
      Serial.print("  V: "); Serial.print(voltage, 2);
      Serial.print("  I: "); Serial.print(current, 2);
      Serial.print("A  T: "); Serial.print(tempC, 1);
      Serial.println("°C");
    } else {
      Serial.print("Bad CRC  Raw: ");
      for (byte i = 0; i < 10; i++) {
        if (frame[i] < 16) Serial.print("0");
        Serial.print(frame[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
    }
  }

  // --- heartbeat ---
  if (millis() - lastGood > 2000) {
    Serial.println("(no telemetry data yet)");
    lastGood = millis();
  }

  delay(10); // light CPU breather
}

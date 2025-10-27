int speedCounter = 0;

void setup()
{
  pinMode(6, OUTPUT);  // A
  pinMode(7, OUTPUT);  // B
  pinMode(8, OUTPUT);  // C
  pinMode(9, OUTPUT);  // D
  pinMode(10, OUTPUT);  // E
  pinMode(11, OUTPUT);  // F
  pinMode(12, OUTPUT);  // G
  pinMode(13, OUTPUT);  // DP
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);

  set7SegmentValue(speedCounter);

}

void set7SegmentValue(uint8_t value) {
  switch (value) {
    case 0:
      digitalWrite7Segment(1, 1, 1, 1, 1, 1, 0);
      break;
    case 1:
      digitalWrite7Segment(0, 1, 1, 0, 0, 0, 0); // 0 is LOW, 1 is HIGH
      break;
    case 2:
      digitalWrite7Segment(1, 1, 0, 1, 1, 0, 1);
      break;
    case 3:
      digitalWrite7Segment(1, 1, 1, 1, 0, 0, 1);
      break;
    case 4:
      digitalWrite7Segment(0, 1, 1, 0, 0, 1, 1);
      break;
    case 5:
      digitalWrite7Segment(1, 0, 1, 1, 0, 1, 1);
      break;
    case 6:
      digitalWrite7Segment(1, 0, 1, 1, 1, 1, 1);
      break;
    case 7:
      digitalWrite7Segment(1, 1, 1, 0, 0, 1, 0);
      break;
    case 8:
      digitalWrite7Segment(1, 1, 1, 1, 1, 1, 1);
      break;
    case 9:
      digitalWrite7Segment(1, 1, 1, 1, 0, 1, 1);
      break;
    case 10:
      digitalWrite7Segment(1, 1, 1, 0, 1, 1, 1); // A (A = 10 in hex)
      break;
    default:
      digitalWrite7Segment(0, 0, 0, 0, 0, 0, 0);
      break;
  }

}

void digitalWrite7Segment(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f, uint8_t g) {
  digitalWrite(6, a);
  digitalWrite(7, b);
  digitalWrite(8, c);
  digitalWrite(9, d);
  digitalWrite(10, e);
  digitalWrite(11, f);
  digitalWrite(12, g);
}

void setpoint(uint8_t dp) {
  digitalWrite(13, dp);
}

void loop() {
  while (speedCounter <= 5) {
    if (!digitalRead(2)) {
      delay(50);
      if (digitalRead(2)) {
        speedCounter++;
        if (speedCounter == 6) {
          return;
        }
        set7SegmentValue(speedCounter);
      }
    }
    else if (!digitalRead(4)) {
      speedCounter = 0;
      set7SegmentValue(speedCounter);
      delay(200);
    }


    if (analogRead(A0) < 512) {
      setpoint(1);
      analogWrite(3, speedCounter*50);
    }
    else {
      setpoint(0);
      analogWrite(3, 0);
    }

    if (analogRead(A1) < 512) {
      analogWrite(5, speedCounter*50);
    }
    else {
      analogWrite(5, 0);
    }
  }

  if (!digitalRead(4)) {
      speedCounter = 0;
      set7SegmentValue(speedCounter);
      delay(200);
  }

}


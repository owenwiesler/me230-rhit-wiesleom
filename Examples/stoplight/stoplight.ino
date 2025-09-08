void setup() {
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(4, INPUT_PULLUP);

}

void loop() {
  digitalWrite(9, HIGH);
  
  
  if (digitalRead(4) == LOW){
    digitalWrite(9, LOW);
    digitalWrite(11, HIGH);
    delay(3000);
    digitalWrite(11, LOW);
    digitalWrite(13, HIGH);
    delay(3000);
    digitalWrite(13, LOW);
  }
}

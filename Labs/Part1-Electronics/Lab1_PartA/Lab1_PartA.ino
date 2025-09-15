// C++ code
//
void setup()
{
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(A0, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);

}

void loop()
{
  digitalWrite(4, !digitalRead(2));
  digitalWrite(12, !digitalRead(2));
  
  digitalWrite(5, !digitalRead(3));
  digitalWrite(13, !digitalRead(3));
  
  analogWrite(6, analogRead(A0)/4);
  analogWrite(11, analogRead(A0)/4);
  
}
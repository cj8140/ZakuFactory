

void setup()
{
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop()
{
  digitalWrite(3, HIGH);
  digitalWrite(5, LOW);
  while(digitalRead(2) == LOW) {
    delay(100);
  }
  while(digitalRead(2) == HIGH) {     // 감지 안됐을경우 루프
    delay(100);
  }                                   // 감지 되면 탈출하며 다음 코드로

  digitalWrite(3, LOW);
  digitalWrite(5, HIGH);
  while(digitalRead(2) == LOW) {      // 대고 있을 경우 정지
    delay(100);
  }                                   // 때면 이제 감지 될때까지 루프
  while(digitalRead(2) == HIGH) {
    delay(100);
  }
}
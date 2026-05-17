void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  if (digitalRead(2) == HIGH) { // 터치 감지하면 HIGH신호(Active HIGH)
    for (int i = 0 ; i <= 255; i ++) {
      analogWrite(3, i);
      delay(15); // 속력조절
    }
  }

  if (digitalRead(2) == LOW) {
    analogWrite(3, 0); // 꺼짐
  }
}
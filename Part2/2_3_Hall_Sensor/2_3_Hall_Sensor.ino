int state = 0;  //0이면 3, 1이면 5켜기

void setup()
{
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop()
{
  if (digitalRead(2) == LOW) {  // 자석 감지하면 LOW신호(Active LOW)
    // v 대체 가능 v
    if(state == 0) {
      state = 1;
    }
    else {
      state = 0;
    }
    // ^ 대체 코드 ^
    // state = !state;

    delay(500);
  }

  if (state == 0) {  
    digitalWrite(3, HIGH);
    digitalWrite(5, LOW);
  }
  else {
    digitalWrite(3, LOW);
    digitalWrite(5, HIGH);
  }
}
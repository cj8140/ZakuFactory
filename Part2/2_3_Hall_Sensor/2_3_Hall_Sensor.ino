int state = 0;  //0이면 3, 1이면 5켜기
int detected = 0;

void setup()
{
  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop()
{
  if (digitalRead(2) == LOW) {  // 자석 감지하면 LOW신호(Active LOW)
    if(detected == 0) {
      detected = 1;
      if(state == 0) {
        state = 1;
      }
      else {
        state = 0;
      }
      delay(200);
    }
  }
  else {
    detected = 0;
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
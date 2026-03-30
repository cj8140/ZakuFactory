void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT); //Triger
  pinMode(4, INPUT); //Echo

  pinMode(3, OUTPUT);  // LED 1
  pinMode(5, OUTPUT);  // LED 2
}

void loop()
{
  digitalWrite(2, LOW);  // 추가
  delayMicroseconds(2); // 추가
  digitalWrite(2, HIGH);
  delayMicroseconds(10);
  digitalWrite(2, LOW);

  unsigned long duration = pulseIn(4, HIGH);  //트리거 핀 시간측정
  int distance = duration * 0.017; // 측정단위 줄이기

  Serial.print("Distance: "); 
  Serial.print(distance);
  Serial.println(" cm"); //줄바꿈, cm추가

  if (distance <= 10) {  //0~10
    digitalWrite(3, HIGH);
    digitalWrite(5, HIGH);
  }

  else if (distance <= 20) {  //11~20
    digitalWrite(3, HIGH);
    digitalWrite(5, LOW);
  }
  else {
    digitalWrite(3, LOW);
    digitalWrite(5, LOW);
  }

  delay(60); // 딜레이 없으면 측정 오류로 잠깐 LED가 켜지므로 약한 불빛으로 깜빡이는 것 처럼 보임. 센서 간섭도 줄임.
  // 대체 코드
  // if (distance < 20) {
  //   digitalWrite(3, HIGH);
  // }
  // else {
  //   digitalWrite(3, LOW);
  // }
  // if (distance < 10) {
  //   digitalWrite(5, HIGH);
  // }
  // else {
  //   digitalWrite(5, LOW);
  // }
}
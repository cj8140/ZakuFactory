//Elehobby3 Coding P3 F4F_V1.4 2025.04.08 By CJ Park, Fin code edited 25.10.20
#define PIN_TRIG 3
#define PIN_ECHO 4
#define PIN_IN1 5
#define PIN_IN2 6
#define PIN_LED_YELLOW1 8
#define PIN_LED_YELLOW2 10
#define PIN_LED_YELLOW3 12

void setup() {
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_LED_YELLOW1, OUTPUT);
  pinMode(PIN_LED_YELLOW2, OUTPUT);
  pinMode(PIN_LED_YELLOW3, OUTPUT);

  Serial.begin(9600);
  Serial.println("Starting");  
}

void loop() {
  digitalWrite(PIN_TRIG, LOW);  // 추가
  delayMicroseconds(2); // 추가
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  unsigned long duration = pulseIn(PIN_ECHO, HIGH);  //트리거 핀 시간측정

  int distance = duration * 0.017; // 측정단위 줄이기
  
  if(duration == 0) { //Timeout 발생  
    distance = 99;
  }
  distance = constrain(distance, 10, 30);
  int speed = map(distance, 10, 30, 255, 0);  //speed 범위 조정

  Serial.print("Dist: ");
  Serial.print(distance);
  Serial.print("\t\tSpeed: ");
  Serial.println(speed);

  digitalWrite(PIN_IN1, 0);  //모터 코드
  analogWrite(PIN_IN2, speed);

  digitalWrite(PIN_LED_YELLOW1, distance < 30);  // 거리를 3구간으로 나누기
  digitalWrite(PIN_LED_YELLOW2, distance <= 20);
  digitalWrite(PIN_LED_YELLOW3, distance <= 10);
}
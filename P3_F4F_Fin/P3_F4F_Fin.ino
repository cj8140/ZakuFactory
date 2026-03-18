//Elehobby3 Coding P3 F4F_V1.4 2025.04.08 By CJ Park, Fin code edited 25.10.20
#define TRIG_PIN 3
#define ECHO_PIN 4
#define IN1_PIN 5
#define IN2_PIN 6
#define LED_YELLOW_PIN 8
#define LED_RED_PIN 10
#define LED_BLUE_PIN 12

void setup() {
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(LED_YELLOW_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
  Serial.println("Starting");  
}

void loop() {
  long duration, distance;
  
  digitalWrite(TRIG_PIN, LOW);    // 트리거 핀을 LOW로 설정하여 초기화
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);  // 트리거 핀을 HIGH로 설정하여 초음파 신호 발사
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH, 10000);   // Echo 핀에서 신호가 돌아오는 시간 측정

  if(duration == 0) { //Timeout 발생  
    distance = 99;
  }

  else {
    distance = duration * 0.0344 / 2;  // 거리는 시간 * 속도 / 2로 계산 (속도는 공기 중에서 약 343m/s)
  }
  int speed = map(constrain(distance, 10, 30), 10, 30, 255, 0);  //speed 범위 조정

  Serial.print("Dist: ");
  Serial.print(distance);
  Serial.print("\t\tSpeed: ");
  Serial.println(speed);

  digitalWrite(IN1_PIN, 0);  //모터 코드
  analogWrite(IN2_PIN, speed);

  digitalWrite(LED_YELLOW_PIN, distance <= 30);  // 거리를 3구간으로 나누기
  digitalWrite(LED_RED_PIN, distance <= 20);
  digitalWrite(LED_BLUE_PIN, distance <= 10);
}
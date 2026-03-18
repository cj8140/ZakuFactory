//Elehobby3 Coding P4 Zaku Factory V0.1 2026.02.21 By Kyoji Park
//Elehobby3 Coding P4 Zaku Factory V0.2 2026.03.01 By Kyoji Park
//Elehobby3 Coding P4 Zaku Factory V1.0 2026.03.01 By C.j. Park
//Elehobby3 Coding P4 Zaku Factory V1.1 2026.03.02 By Kypji Park ; Change bridge1 angle close 134->170, open 51->87 ; Crane 왼쪽붙이기 ; Motor1,2 Analog Write
//Elehobby3 Coding P4 Zaku Factory V1.2 2026.03.02 By C.J.Park Bridge Angle Adjust, Blinking Cockpit Light.
//Elehobby3 Coding P4 Zaku Factory V1.3 2026.03.03 By C.J.Park 브릿지 노이즈 방어 로직 수정
//Elehobby3 Coding P4 Zaku Factory V1.4 2026.03.06 By Kyoji Angle adjust. servo_bridge2 82->78 ; servo_lift 79->70
//Elehobby3 Coding P4 Zaku Factory V1.5 2026.03.011 By Kyoji Angle adjust. servo_bridge2 open 21->17 ; Add Mp3 player

//Elehobby3 Coding P4 Zaku Factory V1.6 2026.03.011 By C.J.Park 네이밍 수정, 주석 추가

#define DELAY_CRANE 30
#define DELAY_HATCH 20
#define DELAY_BRIDGE 20
#define DELAY_LIFT 40
#define DELAY_ALARM 150

#include <Servo.h>
#include <DFPlayer_Mini_Mp3.h>
#include <FastLED.h>

//CRANE(Overhead Traveling Crane)
#define MOTOR1 11             //Motor Driver IN1
#define MOTOR2 12             //Motor Driver IN2
#define SW_LIMIT_LEFT 32      //SW_LIMIT SWITCH
#define SW_LIMIT_RIGHT 50     //SW_LIMIT SWITCH
#define LED_CRANE_RED1 37     //220ohm/red wire
#define LED_CRANE_RED2 38     //220ohm/red wire
#define LED_CRANE_MONITOR 39  //100ohm/blue wire
Servo servo_crane;             //D10 LOW 49, [HIGH 105]

//LIFT(Aerial Work Platform)
#define LED_LIFT_MONITOR 33  //100ohm/yellow wire
#define LED_LIFT_RED1 34     //220ohm/red wire
#define LED_LIFT_RED2 35     //220ohm/red wire
Servo servo_lift;             //D9 [LOW 0], HIGH 70

//BRIDGE(Cockpit Access Panel)
#define LED_BRIDGE_MONITOR 51  //100ohm/blue wire
#define LED_BRIDGE_RED1 52     //220ohm/red wire
#define LED_BRIDGE_RED2 53     //220ohm/red wire
Servo servo_bridge1;            //D46 CLOSE 170, [OPEN 90]
Servo servo_bridge2;            //D45 CLOSE 78, [OPEN 17]

//Body
#define LED_DOME 6     //220ohm/white wire
#define LED_MONITOR 5  //220ohm/green wire, *4=Blank
#define HALL_NECK 3  //Hall Sensor
#define WS_EYE 36      //Robot Eye WS 2812 ; default = yellow; HALL_NECK 3 = purple; HALL_3F 49 = green;
Servo servo_hatch;      //D2 [CLOSE 90], OPEN 132

CRGB ws_eye[1];
#define BRIGHTNESS 100  // 밝기 (0~255)

//3F
#define LED_3F_TORCH 47    //220ohm/yellow wire
#define LED_3F_MONITOR 48  //100ohm/blue wire
#define HALL_3F 49       //220ohm/green wire
Servo servo_torch;          //D44 LOW 52, [HIGH 103]

//Controller
#define SW_DOME A3       // Cockpit Dome LED White
#define SW_MONITOR A4    // Cockpit Monitor LED White
#define POT_HATCH A5     // Hatch Servo ; Close(Servo Angle88 / Open(Servo Angle 132)
#define POT_BRIDGE A6    // Bridge Servo ; Undock BRIDGE1(CLOSE 170, [OPEN 87]) / BRIDGE2(D45 CLOSE 78, [OPEN 17])
#define POT_LIFT A7      // LIFT Servo [LOW 0], HIGH 70
#define SW_JOY_HOIST 24  // CRANE Servo UP LOW 49, [HIGH 105]
#define SW_JOY_LOWER 25  // CRANE Servo UP LOW 49, [HIGH 105]
#define SW_JOY_LEFT 26   // CRANE Motor
#define SW_JOY_RIGHT 27  // CRANE Motor



void setup()
{
  Serial1.begin(9600);
  mp3_set_serial(Serial1);
  mp3_set_volume(29);
  delay(50);

  FastLED.addLeds<WS2812, WS_EYE, GRB>(ws_eye, 1);
  FastLED.setBrightness(BRIGHTNESS);

  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  digitalWrite(22, LOW);  // Controller GND
  digitalWrite(23, LOW);  // Controller GND

  servo_hatch.attach(2);
  servo_hatch.write(90);  // [CLOSE 90], OPEN 132
  servo_bridge1.attach(46);
  servo_bridge1.write(90);  // CLOSE 170, [OPEN 90]
  servo_bridge2.attach(45);
  servo_bridge2.write(17);  // CLOSE 78, [OPEN 17]
  servo_lift.attach(9);
  servo_lift.write(0);  // [LOW 0], HIGH 70
  servo_torch.attach(44);
  servo_torch.write(103);  // LOW 52, [HIGH 103]
  servo_crane.attach(10);
  servo_crane.write(105);  // LOW 49, [HIGH 105]

  pinMode(LED_DOME, OUTPUT);
  pinMode(LED_MONITOR, OUTPUT);
  pinMode(LED_BRIDGE_MONITOR, OUTPUT);
  pinMode(LED_BRIDGE_RED1, OUTPUT);
  pinMode(LED_BRIDGE_RED2, OUTPUT);
  pinMode(LED_LIFT_MONITOR, OUTPUT);
  pinMode(LED_LIFT_RED1, OUTPUT);
  pinMode(LED_LIFT_RED2, OUTPUT);
  pinMode(LED_CRANE_MONITOR, OUTPUT);
  pinMode(LED_CRANE_RED1, OUTPUT);
  pinMode(LED_CRANE_RED2, OUTPUT);
  pinMode(LED_3F_MONITOR, OUTPUT);
  pinMode(LED_3F_TORCH, OUTPUT);

  pinMode(HALL_NECK, INPUT_PULLUP);
  pinMode(HALL_3F, INPUT_PULLUP);

  pinMode(SW_JOY_HOIST, INPUT_PULLUP);
  pinMode(SW_JOY_LEFT, INPUT_PULLUP);
  pinMode(SW_JOY_LOWER, INPUT_PULLUP);
  pinMode(SW_JOY_RIGHT, INPUT_PULLUP);

  pinMode(SW_LIMIT_LEFT, INPUT_PULLUP);
  pinMode(SW_LIMIT_RIGHT, INPUT_PULLUP);

  pinMode(SW_MONITOR, INPUT_PULLUP);
  pinMode(SW_DOME, INPUT_PULLUP);

  ws_eye[0] = CRGB(255, 255, 0);
  FastLED.show();
  //  while (digitalRead(SW_LIMIT_RIGHT) == HIGH) {   //오른쪽붙이기
  //    digitalWrite(MOTOR1, HIGH);
  //    digitalWrite(MOTOR2, LOW);
  //  }
  while (digitalRead(SW_LIMIT_LEFT) == HIGH) {  //왼쪽붙이기
    digitalWrite(MOTOR1, LOW);
    digitalWrite(MOTOR2, HIGH);
  }
  digitalWrite(MOTOR1, LOW);
  digitalWrite(MOTOR2, LOW);

  mp3_play(1);  // produced by
//  mp3_play(2);  // 0004_factory-ambience.mp3
}

void loop()
{
//part: Head
  //Crane 모니터 LED 제어, 리미트 스위치가 눌렸을 때 꺼짐
  if (digitalRead(SW_LIMIT_LEFT) == LOW || digitalRead(SW_LIMIT_RIGHT) == LOW) {
    digitalWrite(LED_CRANE_MONITOR, LOW);
  }
  else {
    digitalWrite(LED_CRANE_MONITOR, HIGH);
  }
  //Crane 모터 제어
  if (digitalRead(SW_JOY_RIGHT) == LOW && digitalRead(SW_LIMIT_RIGHT) == HIGH) {
    analogWrite(MOTOR1, 150);
    digitalWrite(MOTOR2, LOW);
  }
  else if (digitalRead(SW_JOY_LEFT) == LOW && digitalRead(SW_LIMIT_LEFT) == HIGH) {
    digitalWrite(MOTOR1, LOW);
    analogWrite(MOTOR2, 150);
  }
  else {
    digitalWrite(MOTOR1, LOW);
    digitalWrite(MOTOR2, LOW);
  }

  //Crane 서보 제어
  static int angle_crane = 105;
  static long last_crane_time = 0;

  //깡 delay 써서 쉬운코드로 바꾸는 것이 가능할수도 -------------------------------------------------------------------------------------------------------
  if (digitalRead(SW_JOY_HOIST) == LOW && millis() - last_crane_time > DELAY_CRANE && angle_crane < 105) {
    last_crane_time = millis();
    angle_crane++;
    servo_crane.write(angle_crane);
  }
  else if (digitalRead(SW_JOY_LOWER) == LOW && millis() - last_crane_time > DELAY_CRANE && angle_crane > 49) {
    last_crane_time = millis();
    angle_crane--;
    servo_crane.write(angle_crane);
  }

  //Crane 조이스틱 작동시 레드 LED 깜빡임
  if (digitalRead(SW_JOY_HOIST) == LOW || digitalRead(SW_JOY_LOWER) == LOW || digitalRead(SW_JOY_LEFT) == LOW || digitalRead(SW_JOY_RIGHT) == LOW) {
    digitalWrite(LED_CRANE_RED1, (millis() / DELAY_ALARM) % 2);
    digitalWrite(LED_CRANE_RED2, (millis() / DELAY_ALARM) % 2);
  }
  else {
    digitalWrite(LED_CRANE_RED1, LOW);
    digitalWrite(LED_CRANE_RED2, LOW);
  }
  
  //Hall Sensor 상태 저장 변수, 0은 Air, 1은 Neck, 2는 3F, 이전 상태 저장 변수
  
  static int prev_state_hall = 0b00;  //불가능상태(두 홀센서 모두 켜짐) 으로 초기화
  //3F 센서를 2의 자리로, 목 센서를 1의 자리로 해서 홀센서 상태를 저장
  int state_hall = (digitalRead(HALL_3F) << 1) | digitalRead(HALL_NECK);
  
  //3F로 왔을 경우 
  if (state_hall == 0b01 && prev_state_hall != 0b01) {  //3f
    mp3_play(3);  // torch
    delay(300);

    digitalWrite(LED_3F_MONITOR, HIGH);
    digitalWrite(MOTOR1, LOW);
    digitalWrite(MOTOR2, LOW);
    ws_eye[0] = CRGB(0, 255, 0); // Green color
    FastLED.show();

    for (int i = 103; i >= 52; i--) {
      servo_torch.write(i);
      delay(5);
    }
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 7; i++) {
        digitalWrite(LED_3F_TORCH, HIGH);
        delay(60);

        digitalWrite(LED_3F_TORCH, LOW);
        delay(60);
      }
      delay(200);
    }
  }
  //목 위로 왔을 경우
  if (state_hall == 0b10 && prev_state_hall != 0b10) {  //Neck
    ws_eye[0] = CRGB(250, 0, 255);
    FastLED.show();
  }
  //Air 상태로 왔을 경우
  if (state_hall == 0b11 && prev_state_hall != 0b11) {  //Air
    digitalWrite(LED_3F_MONITOR, LOW);
    ws_eye[0] = CRGB(150, 0, 0);
    FastLED.show();
    servo_torch.write(103);
  }
  prev_state_hall = state_hall;

//part: Hatch
  //해치 상태 저장 변수, 0은 닫힘, 1은 열림, 이전 상태 저장 변수
  static int state_hatch = 0;
  static int prev_state_hatch = 0;
  //열려있을 때
  if (analogRead(POT_HATCH) > 1020) {  //Close
    state_hatch = 0;
    digitalWrite(LED_DOME, LOW);
    digitalWrite(LED_MONITOR, LOW);
  }
  //닫혀 있을 때
  else if (analogRead(POT_HATCH) < 700) {  //Open
    state_hatch = 1;
    if (digitalRead(SW_DOME) == LOW) digitalWrite(LED_DOME, HIGH);
    else digitalWrite(LED_DOME, LOW);
    if (digitalRead(SW_MONITOR) == LOW) digitalWrite(LED_MONITOR, HIGH);
    else digitalWrite(LED_MONITOR, LOW);
  }
  //닫기
  if (state_hatch == 0 && prev_state_hatch != 0) {  //Close
  mp3_play(8); // hatch open sound
  delay(300);
    for (int i = 132; i >= 90; i--) { //닫는 도중, 각각 스위치 켜져있을 경우 깜빡임 추가
      if (digitalRead(SW_DOME) == LOW) digitalWrite(LED_DOME, i / 7 % 2);
      if (digitalRead(SW_MONITOR) == LOW) digitalWrite(LED_MONITOR, i / 7 % 2);
      servo_hatch.write(i);
      delay(DELAY_HATCH);
    }
  }
  //열기
  if (state_hatch == 1 && prev_state_hatch != 1) {  //Open
  mp3_play(8);
  delay(300);    
    for (int i = 90; i <= 132; i++) { //열리는 도중, 각각 스위치 켜져있을 경우 깜빡임 추가
      if (digitalRead(SW_DOME) == LOW) digitalWrite(LED_DOME, i / 7 % 2);
      if (digitalRead(SW_MONITOR) == LOW) digitalWrite(LED_MONITOR, i / 7 % 2);
      servo_hatch.write(i);
      delay(DELAY_HATCH);
    }
    mp3_play(9);  // MonoEye
  }
  prev_state_hatch = state_hatch;

//part: Bridge
  //Bridge DOCK-679 UNDOCK-1023
  
  static float filtered_pot_bridge = 1023;
  static int angle_bridge1 = 90;
  static int wanted_angle_bridge1 = 90;
  static unsigned long last_bridge_time = 0;

  //센서 노이즈 방어 로직, 0.1은 새 값 가중치, 0.9는 기존 값 가중치
  filtered_pot_bridge = (0.1 * analogRead(POT_BRIDGE)) + (0.9 * filtered_pot_bridge);

  //목표 각도 설정
  wanted_angle_bridge1 = map((int)filtered_pot_bridge, 679, 1023, 170, 90);

  //목표 각도와 현재 각도가 다르고, 마지막으로 각도를 변경한 지 DELAY_BRIDGE 시간이 지났다면 각도 변경
  if (angle_bridge1 != wanted_angle_bridge1 && (millis() - last_bridge_time) > DELAY_BRIDGE) {
    digitalWrite(LED_BRIDGE_RED1, (millis() / DELAY_ALARM) % 2);
    digitalWrite(LED_BRIDGE_RED2, (millis() / DELAY_ALARM) % 2);

    if (angle_bridge1 < wanted_angle_bridge1) angle_bridge1++;
    else angle_bridge1--;
    servo_bridge1.write(angle_bridge1);
    //bridge1 각도에 따른 servo_bridge2 각도 조정, 170->78, 90->17
    servo_bridge2.write(map(angle_bridge1, 170, 90, 78, 17));
    last_bridge_time = millis();
  }
  if (angle_bridge1 == wanted_angle_bridge1) {
    digitalWrite(LED_BRIDGE_RED1, LOW);
    digitalWrite(LED_BRIDGE_RED2, LOW);
  }
  //각도가 160 이상일 때 모니터 LED 켜기
  if (angle_bridge1 > 160) {
    digitalWrite(LED_BRIDGE_MONITOR, HIGH);
  }
  else {
    digitalWrite(LED_BRIDGE_MONITOR, LOW);
  }
//part: Lift | bridge와 동일한 로직,
  //Lift DOWN 3 ~ 1023 Up
  static float filtered_pot_lift = 0;
  static int angle_lift = 0;
  static int wanted_angle_lift = 0;
  static unsigned long last_lift_time = 0;

  filtered_pot_lift = (0.1 * analogRead(POT_LIFT)) + (0.9 * filtered_pot_lift);
  wanted_angle_lift = map((int)filtered_pot_lift, 3, 1023, 0, 70);

  if (angle_lift != wanted_angle_lift && (millis() - last_lift_time) > DELAY_LIFT) {
    digitalWrite(LED_LIFT_RED1, (millis() / DELAY_ALARM) % 2);
    digitalWrite(LED_LIFT_RED2, (millis() / DELAY_ALARM) % 2);

    if (angle_lift < wanted_angle_lift) angle_lift++;
    else angle_lift--;
    servo_lift.write(angle_lift);
    last_lift_time = millis();
  }
  if (angle_lift == wanted_angle_lift) {
    digitalWrite(LED_LIFT_RED1, LOW);
    digitalWrite(LED_LIFT_RED2, LOW);
  }
  if (angle_lift > 65) {
    digitalWrite(LED_LIFT_MONITOR, HIGH);
  }
  else {
    digitalWrite(LED_LIFT_MONITOR, LOW);
  }
}

/*
Mp3 
0001_producedby
0002_factory_noise
0003_torch_short
0004_factory-ambience
0005_lift
0006_crane
0007_bridge
0008_hatch
0009_monoeye
0010_Groundcontrol
0011_herewego
*/

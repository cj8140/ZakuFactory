//Elehobby3 Coding P4 Zaku Factory V0.1 2026.02.21 By Kyoji Park
//Elehobby3 Coding P4 Zaku Factory V0.2 2026.03.01 By Kyoji Park
//Elehobby3 Coding P4 Zaku Factory V1.0 2026.03.01 By C.j. Park
//Elehobby3 Coding P4 Zaku Factory V1.1 2026.03.02 By Kypji Park ; Change bridge1 angle close 134->170, open 51->87 ; Crane 왼쪽붙이기 ; Motor1,2 Analog Write
//Elehobby3 Coding P4 Zaku Factory V1.2 2026.03.02 By C.J.Park Bridge Angle Adjust, Blinking Cockpit Light.
//Elehobby3 Coding P4 Zaku Factory V1.3 2026.03.03 By C.J.Park 브릿지 노이즈 방어 로직 수정
//Elehobby3 Coding P4 Zaku Factory V1.4 2026.03.06 By Kyoji Angle adjust. ServoBridge2 82->78 ; ServoLift 79->70

#define DELAY_CRANE 30
#define DELAY_BRIDGE 20
#define DELAY_LIFT 40

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
Servo ServoCrane;             //D10 LOW 49, [HIGH 105]

//LIFT(Aerial Work Platform)
#define LED_LIFT_MONITOR 33  //100ohm/yellow wire
#define LED_LIFT_RED1 34     //220ohm/red wire
#define LED_LIFT_RED2 35     //220ohm/red wire
Servo ServoLift;             //D9 [LOW 0], HIGH 70

//BRIDGE(Cockpit Access Panel)
#define LED_BRIDGE_MONITOR 51  //100ohm/blue wire
#define LED_BRIDGE_RED1 52     //220ohm/red wire
#define LED_BRIDGE_RED2 53     //220ohm/red wire
Servo ServoBridge1;            //D46 CLOSE 170, [OPEN 90]
Servo ServoBridge2;            //D45 CLOSE 78, [OPEN 21]

//Body
#define LED_DOME 6     //220ohm/white wire
#define LED_MONITOR 5  //220ohm/green wire, *4=Blank
#define SENSOR_NECK 3  //220ohm/green wire
#define WS_EYE 36      //Robot Eye WS 2812 ; default = yellow; NECK_SENSOR 3 = purple; F3_SENSOR 49 = green;
Servo ServoHatch;      //D2 [CLOSE 90], OPEN 132

CRGB ws_eye[1];
#define BRIGHTNESS 100  // 밝기 (0~255)

//3F
#define LED_3F_TORCH 47    //220ohm/yellow wire
#define LED_3F_MONITOR 48  //100ohm/blue wire
#define SENSOR_3F 49       //220ohm/green wire
Servo ServoTorch;          //D44 LOW 52, [HIGH 103]

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

int prev_eye_state = 1;

int craneAngle = 105;
unsigned long lastCraneTime = 0;

int hatch_state = 0;
int prev_hatch_state = 0;

float bridge_smooth_pot = 1023;
int bridge1Angle = 90;
int bridge1WantedAngle = 90;
unsigned long lastBridgeTime = 0;

float lift_smooth_pot = 0;
int liftAngle = 0;
int liftWantedAngle = 0;
unsigned long lastLiftTime = 0;



void setup()
{
  Serial.begin(9600);

  mp3_set_serial(Serial);
  mp3_set_volume(29);
  delay(50);

  FastLED.addLeds<WS2812, WS_EYE, GRB>(ws_eye, 1);
  FastLED.setBrightness(BRIGHTNESS);


  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  digitalWrite(22, LOW);  // Controller GND
  digitalWrite(23, LOW);  // Controller GND

  ServoHatch.attach(2);
  ServoHatch.write(90);  // [CLOSE 90], OPEN 132
  ServoBridge1.attach(46);
  ServoBridge1.write(90);  // CLOSE 170, [OPEN 90]
  ServoBridge2.attach(45);
  ServoBridge2.write(21);  // CLOSE 78, [OPEN 21]
  ServoLift.attach(9);
  ServoLift.write(0);  // [LOW 0], HIGH 70
  ServoTorch.attach(44);
  ServoTorch.write(103);  // LOW 52, [HIGH 103]
  ServoCrane.attach(10);
  ServoCrane.write(105);  // LOW 49, [HIGH 105]

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

  pinMode(SENSOR_NECK, INPUT_PULLUP);
  pinMode(SENSOR_3F, INPUT_PULLUP);


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
}

void loop()
{

  //Crane
  if (digitalRead(SW_LIMIT_LEFT) == LOW || digitalRead(SW_LIMIT_RIGHT) == LOW) {
    digitalWrite(LED_CRANE_MONITOR, LOW);
  }
  else {
    digitalWrite(LED_CRANE_MONITOR, HIGH);
  }
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
    digitalWrite(LED_CRANE_RED1, LOW);
    digitalWrite(LED_CRANE_RED2, LOW);
  }


  if (digitalRead(SW_JOY_HOIST) == LOW && millis() - lastCraneTime > DELAY_CRANE && craneAngle < 105) {
    lastCraneTime = millis();
    craneAngle++;
    ServoCrane.write(craneAngle);
  }
  else if (digitalRead(SW_JOY_LOWER) == LOW && millis() - lastCraneTime > DELAY_CRANE && craneAngle > 49) {
    lastCraneTime = millis();
    craneAngle--;
    ServoCrane.write(craneAngle);
  }

  if (digitalRead(SW_JOY_HOIST) == LOW || digitalRead(SW_JOY_LOWER) == LOW || digitalRead(SW_JOY_LEFT) == LOW || digitalRead(SW_JOY_RIGHT) == LOW) {
    digitalWrite(LED_CRANE_RED1, (millis() / 150) % 2);
    digitalWrite(LED_CRANE_RED2, (millis() / 150 + 0) % 2);
  }
  else {
    digitalWrite(LED_CRANE_RED1, LOW);
    digitalWrite(LED_CRANE_RED2, LOW);
  }

  //Eye
  int eye_state = (digitalRead(SENSOR_3F) << 1) | digitalRead(SENSOR_NECK);

  if (eye_state == 0b01 && prev_eye_state != 0b01) {  //3f
    digitalWrite(LED_3F_MONITOR, HIGH);
    digitalWrite(MOTOR1, LOW);
    digitalWrite(MOTOR2, LOW);
    ws_eye[0] = CRGB(0, 255, 0);
    FastLED.show();
    for (int i = 103; i >= 52; i--) {
      ServoTorch.write(i);
      delay(5);
    }
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 7; i++) {
        digitalWrite(LED_3F_TORCH, HIGH);
        delay(50);

        digitalWrite(LED_3F_TORCH, LOW);
        delay(50);
      }
      delay(200);
    }
  }
  if (eye_state == 0b10 && prev_eye_state != 0b10) {  //Neck
    ws_eye[0] = CRGB(250, 0, 255);
    FastLED.show();
  }
  if (eye_state == 0b11 && prev_eye_state != 0b11) {  //Air
    digitalWrite(LED_3F_MONITOR, LOW);
    ws_eye[0] = CRGB(150, 0, 0);
    FastLED.show();
    ServoTorch.write(103);
  }
  prev_eye_state = eye_state;


  if (analogRead(POT_HATCH) > 1020) {  //Close
    hatch_state = 0;
    digitalWrite(LED_DOME, LOW);
    digitalWrite(LED_MONITOR, LOW);
  }
  else if (analogRead(POT_HATCH) < 700) {  //Open
    hatch_state = 1;
    if (digitalRead(SW_DOME) == LOW) digitalWrite(LED_DOME, HIGH);
    else digitalWrite(LED_DOME, LOW);
    if (digitalRead(SW_MONITOR) == LOW) digitalWrite(LED_MONITOR, HIGH);
    else digitalWrite(LED_MONITOR, LOW);
  }
  if (hatch_state == 0 && prev_hatch_state != 0) {  //Close
    for (int i = 132; i >= 90; i--) {
      if (digitalRead(SW_DOME) == LOW) digitalWrite(LED_DOME, i / 7 % 2);
      if (digitalRead(SW_MONITOR) == LOW) digitalWrite(LED_MONITOR, i / 7 % 2);
      ServoHatch.write(i);
      delay(20);
    }
  }
  else if (hatch_state == 1 && prev_hatch_state != 1) {  //Open
    for (int i = 90; i <= 132; i++) {
      if (digitalRead(SW_DOME) == LOW) digitalWrite(LED_DOME, i / 7 % 2);
      if (digitalRead(SW_MONITOR) == LOW) digitalWrite(LED_MONITOR, i / 7 % 2);
      ServoHatch.write(i);
      delay(20);
    }
  }
  prev_hatch_state = hatch_state;


  //Bridge DOCK-679 UNDOCK-1023
  bridge_smooth_pot = (0.1 * analogRead(POT_BRIDGE)) + (0.9 * bridge_smooth_pot);

  bridge1WantedAngle = map((int)bridge_smooth_pot, 679, 1023, 170, 90);


  if (bridge1Angle != bridge1WantedAngle && (millis() - lastBridgeTime) > DELAY_BRIDGE) {
    digitalWrite(LED_BRIDGE_RED1, (millis() / 150) % 2);
    digitalWrite(LED_BRIDGE_RED2, (millis() / 150 + 0) % 2);

    if (bridge1Angle < bridge1WantedAngle) bridge1Angle++;
    else bridge1Angle--;
    ServoBridge1.write(bridge1Angle);
    ServoBridge2.write(map(bridge1Angle, 170, 90, 78, 21));
    lastBridgeTime = millis();
  }
  if (bridge1Angle == bridge1WantedAngle) {
    digitalWrite(LED_BRIDGE_RED1, LOW);
    digitalWrite(LED_BRIDGE_RED2, LOW);
  }
  if (bridge1Angle > 160) {
    digitalWrite(LED_BRIDGE_MONITOR, HIGH);
  }
  else {
    digitalWrite(LED_BRIDGE_MONITOR, LOW);
  }


  //Lift DOWN 3 ~ 1023 Up
  
  lift_smooth_pot = (0.1 * analogRead(POT_LIFT)) + (0.9 * lift_smooth_pot);
  liftWantedAngle = map((int)lift_smooth_pot, 3, 1023, 0, 70);

  if (liftAngle != liftWantedAngle && (millis() - lastLiftTime) > DELAY_LIFT) {
    digitalWrite(LED_LIFT_RED1, (millis() / 150) % 2);
    digitalWrite(LED_LIFT_RED2, (millis() / 150 + 0) % 2);

    if (liftAngle < liftWantedAngle) liftAngle++;
    else liftAngle--;
    ServoLift.write(liftAngle);
    lastLiftTime = millis();
  }
  if (liftAngle == liftWantedAngle) {
    digitalWrite(LED_LIFT_RED1, LOW);
    digitalWrite(LED_LIFT_RED2, LOW);
  }
  if (liftAngle > 65) {
    digitalWrite(LED_LIFT_MONITOR, HIGH);
  }
  else {
    digitalWrite(LED_LIFT_MONITOR, LOW);
  }
}
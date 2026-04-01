//Elehobby3 Coding P4 Police Zaku V1.2 2025.09.08 By CJ Park
#include "Servo.h"
#include <DFPlayer_Mini_Mp3.h>

#define PERIOD_MAIN 1600
#define DURATION_BLINKABLE 800

#define PERIOD_BLINK 200  // Up slow, Down High
#define DURATION_ON 100

#define PERIOD_CROSSFADING 1000

#define PIN_LED_EYE 3  // 0806 Magenta SMD, Yellow Wire
#define PIN_LED_WARN_R 5  // 0402 Red SMD, Red Wire
#define PIN_LED_WARN_L 6  // 0402 Red SMD, Red Wire -
#define PIN_LED_GUN 11  // 2mm Orange LED, Orange Wire
#define PIN_LED_V_UP 4  // 2mm Blue LED, Blue Wire
#define PIN_LED_V_DOWN 7  // 2mm Blue LED, Blue Wire -
#define PIN_LED_V_R 8  // 3mm Cyan LED x2, White Wire
#define PIN_LED_V_L 12  // 3mm Cyan LED x2, White Wire -

#define PIN_SW_TRIGGER 2 // Blue wire
#define PIN_SW_RESET A0 // Blue wire -

#define PIN_SW_STICK_DOWN A1 // Yellow 1
#define PIN_SW_STICK_UP A2 // Yellow 2  
#define PIN_SW_STICK_R A3 // Yellow 3
#define PIN_SW_STICK_L A4 // Yellow 4
#define PIN_SW_REV A5 // White 1
#define PIN_SW_MODE A6 // White 2
#define PIN_POT_SPD A7 // White 3

Servo servo_tilt; // Up high 48, Init 88, Down Low 127
Servo servo_pan; // Right 12, Init98, Left 180

int angle_tilt = 88;
int angle_pan = 98;
int delay_servo = 20;
int period_eye = 2000;
bool triggered = false;

void setup()
{
  servo_tilt.attach(9);
  servo_pan.attach(10);

  pinMode(PIN_LED_EYE, OUTPUT);
  pinMode(PIN_LED_WARN_R, OUTPUT);
  pinMode(PIN_LED_WARN_L, OUTPUT);
  pinMode(PIN_LED_GUN, OUTPUT);

  pinMode(PIN_LED_V_UP, OUTPUT);
  pinMode(PIN_LED_V_DOWN, OUTPUT);
  pinMode(PIN_LED_V_L, OUTPUT);
  pinMode(PIN_LED_V_R, OUTPUT);

  pinMode(PIN_SW_TRIGGER, INPUT_PULLUP);
  pinMode(PIN_SW_RESET, INPUT_PULLUP);

  pinMode(PIN_SW_STICK_DOWN, INPUT_PULLUP);
  pinMode(PIN_SW_STICK_UP, INPUT_PULLUP);
  pinMode(PIN_SW_STICK_R, INPUT_PULLUP);
  pinMode(PIN_SW_STICK_L, INPUT_PULLUP);
  pinMode(PIN_SW_REV, INPUT_PULLUP);
  pinMode(PIN_SW_MODE, INPUT_PULLUP);

  servo_tilt.write(88);
  servo_pan.write(98);
  
  Serial.begin(9600);
  mp3_set_serial(Serial);
  mp3_set_volume(29);
  delay(50);
  mp3_play(0001);  // alam
}
int oldpot = 1;

void loop()
{
  
  analogWrite(PIN_LED_EYE, (int)(sin(TWO_PI * (millis() % period_eye) / float(period_eye)) + 1) * 110 + 20);

  angle_tilt = constrain(angle_tilt, 48, 127);
  angle_pan = constrain(angle_pan, 12, 180);

  if (digitalRead(PIN_SW_REV) == LOW) {
    bool is_blinkable = (millis() % PERIOD_MAIN) <= DURATION_BLINKABLE;
    bool is_blink_on = (millis() % PERIOD_BLINK) <= DURATION_ON;

    digitalWrite(PIN_LED_WARN_L, is_blinkable && is_blink_on);
    digitalWrite(PIN_LED_WARN_R, is_blinkable && is_blink_on);
    if (digitalRead(PIN_SW_STICK_L) == LOW)
      move_left();
    else
      digitalWrite(PIN_LED_V_R, LOW);
    if (digitalRead(PIN_SW_STICK_R) == LOW)
      move_right();
    else
      digitalWrite(PIN_LED_V_L, LOW);
  }
  else {
    float sin_value = sin(TWO_PI * float(millis() % PERIOD_CROSSFADING) / float(PERIOD_CROSSFADING));
    analogWrite(PIN_LED_WARN_L, (int)(sin_value + 1) * 127.5);
    analogWrite(PIN_LED_WARN_R, (int)(-sin_value + 1) * 127.5);

    if (digitalRead(PIN_SW_STICK_L) == LOW)
      move_right();
    else
      digitalWrite(PIN_LED_V_L, LOW);
    if (digitalRead(PIN_SW_STICK_R) == LOW)
      move_left();
    else
      digitalWrite(PIN_LED_V_R, LOW);
  }

  if (digitalRead(PIN_SW_STICK_DOWN) == LOW) {  // Tilt LOW limit 127
    angle_tilt += 1;
    servo_tilt.write(angle_tilt);
    digitalWrite(PIN_LED_V_DOWN, HIGH);
    delay(delay_servo);
  }
  else
    digitalWrite(PIN_LED_V_DOWN, LOW);

  if (digitalRead(PIN_SW_STICK_UP) == LOW) {   // Tilt High limit 48
    angle_tilt -= 1;
    servo_tilt.write(angle_tilt);
    digitalWrite(PIN_LED_V_UP, HIGH);
    delay(delay_servo);
  }
  else
    digitalWrite(PIN_LED_V_UP, LOW);

  if (digitalRead(PIN_SW_RESET) == LOW) {
    while (angle_pan != 98 || angle_tilt != 88) {
      if(angle_pan != 98)
        angle_pan += (98 - angle_pan > 0) * 2 - 1;
      if(angle_tilt != 88)
        angle_tilt += (88 - angle_tilt > 0) * 2 - 1;
      servo_pan.write(angle_pan);
      servo_tilt.write(angle_tilt);
      delay(10);
      Serial.println(angle_tilt);
    }
  }
  delay_servo = map(analogRead(PIN_POT_SPD), 450, 820, 30, 0);
  int pot = analogRead(PIN_POT_SPD);
  if (pot - oldpot < -10 || pot - oldpot > 10) {
    period_eye = map(pot, 450, 820, 8000, 500);
    oldpot = pot;
  }
  if (analogRead(PIN_SW_MODE) < 100) {  //▶singl shot
    if (digitalRead(PIN_SW_TRIGGER) == LOW) {
      if (triggered == false) {
        triggered = true;
        mp3_play(0004);          // single shot
        digitalWrite(PIN_LED_GUN, HIGH);
        servo_tilt.write(angle_tilt - 5);
        delay(70);
        digitalWrite(PIN_LED_GUN, LOW);
        servo_tilt.write(angle_tilt);
        delay(100);
      }
    }
    else {
      triggered = false;
    }
  }

  else {
    if (digitalRead(PIN_SW_TRIGGER) == LOW) {  //▶▶▶machinegun Mode
      mp3_play(0004);          // single shot
      digitalWrite(PIN_LED_GUN, HIGH);
      servo_tilt.write(angle_tilt - 5);
      delay(70);
      digitalWrite(PIN_LED_GUN, LOW);
      servo_tilt.write(angle_tilt);
      delay(100);
    }
  }
}

void move_left()
{
  angle_pan += 1;
  //mp3_play(0003);
  servo_pan.write(angle_pan);
  digitalWrite(PIN_LED_V_R, HIGH);
  delay(delay_servo);
}

void move_right()
{
  angle_pan -= 1;
  //mp3_play(0003);
  servo_pan.write(angle_pan);
  digitalWrite(PIN_LED_V_L, HIGH);
  delay(delay_servo);
}
//Elehobby3 Coding P4 Police Zaku V1.2 2025.09.08 By CJ Park
#include "Servo.h"
#include <DFPlayer_Mini_Mp3.h>

#define WARN_WHOLE_PERIOD 1600
#define WARN_WHOLE_OFF_DELAY 800
#define WARN_BLINK_PERIOD 200  // Up slow, Down High
#define WARN_BLINK_OFF_DELAY 100
#define WARN_CROSS_DELAY 1000

#define LED_EYE 3  // 0806 Magenta SMD, Yellow Wire
#define LED_WARN_R 5  // 0402 Red SMD, Red Wire
#define LED_WARN_L 6  // 0402 Red SMD, Red Wire -
#define LED_GUN 11  // 2mm Orange LED, Orange Wire
#define LED_V_UP 4  // 2mm Blue LED, Blue Wire
#define LED_V_DOWN 7  // 2mm Blue LED, Blue Wire -
#define LED_V_R 8  // 3mm Cyan LED x2, White Wire
#define LED_V_L 12  // 3mm Cyan LED x2, White Wire -

#define SW_TRIGGER 2 // Blue wire
#define SW_RESET A0 // Blue wire -

#define SW_STICK_DOWN A1 // Yellow 1
#define SW_STICK_UP A2 // Yellow 2  
#define SW_STICK_R A3 // Yellow 3
#define SW_STICK_L A4 // Yellow 4
#define SW_REV A5 // White 1
#define SW_MODE A6 // White 2
#define POT_SPD A7 // White 3

Servo s_tilt; // Up high 48, Init 88, Down Low 127
Servo s_pan; // Right 12, Init98, Left 180

int angle_tilt = 88;
int angle_pan = 98;
int servo_delay = 20;
int eye_period = 2000;
bool triggered = false;

void setup()
{
  s_tilt.attach(9);
  s_pan.attach(10);

  pinMode(LED_EYE, OUTPUT);
  pinMode(LED_WARN_R, OUTPUT);
  pinMode(LED_WARN_L, OUTPUT);
  pinMode(LED_GUN, OUTPUT);

  pinMode(LED_V_UP, OUTPUT);
  pinMode(LED_V_DOWN, OUTPUT);
  pinMode(LED_V_L, OUTPUT);
  pinMode(LED_V_R, OUTPUT);

  pinMode(SW_TRIGGER, INPUT_PULLUP);
  pinMode(SW_RESET, INPUT_PULLUP);

  pinMode(SW_STICK_DOWN, INPUT_PULLUP);
  pinMode(SW_STICK_UP, INPUT_PULLUP);
  pinMode(SW_STICK_R, INPUT_PULLUP);
  pinMode(SW_STICK_L, INPUT_PULLUP);
  pinMode(SW_REV, INPUT_PULLUP);
  pinMode(SW_MODE, INPUT_PULLUP);

  s_tilt.write(88);
  s_pan.write(98);
  
  Serial.begin(9600);
  mp3_set_serial(Serial);
  mp3_set_volume(29);
  delay(50);
  mp3_play(0001);  // alam
}
int oldpot = 1;

void loop()
{
  analogWrite(LED_EYE, (sin(2 * 3.14 * float(millis() % eye_period) / float(eye_period)) + 1) * 110 + 20);

    angle_tilt = constrain(angle_tilt, 48, 127);
    angle_pan = constrain(angle_pan, 12, 180);

  if (digitalRead(SW_REV) == LOW) {
    digitalWrite(LED_WARN_L, (millis() % WARN_WHOLE_PERIOD / WARN_WHOLE_OFF_DELAY) * millis() % WARN_BLINK_PERIOD / WARN_BLINK_OFF_DELAY);
    digitalWrite(LED_WARN_R, (millis() % WARN_WHOLE_PERIOD / WARN_WHOLE_OFF_DELAY) * millis() % WARN_BLINK_PERIOD / WARN_BLINK_OFF_DELAY);
    if (digitalRead(SW_STICK_L) == LOW)
      move_left();
    else
      digitalWrite(LED_V_R, LOW);
    if (digitalRead(SW_STICK_R) == LOW)
      move_right();
    else
      digitalWrite(LED_V_L, LOW);
  }
  else {
    analogWrite(LED_WARN_L, (sin(2 * 3.14 * (millis() % WARN_CROSS_DELAY) / WARN_CROSS_DELAY + 3.14) + 1) * 127.5);
    analogWrite(LED_WARN_R, (sin(2 * 3.14 * (millis() % WARN_CROSS_DELAY) / WARN_CROSS_DELAY) + 1) * 127.5);
    if (digitalRead(SW_STICK_L) == LOW)
      move_right();
    else
      digitalWrite(LED_V_L, LOW);
    if (digitalRead(SW_STICK_R) == LOW)
      move_left();
    else
      digitalWrite(LED_V_R, LOW);
  }

  if (digitalRead(SW_STICK_DOWN) == LOW) {  // Tilt LOW limit 127
    angle_tilt += 1;
    s_tilt.write(angle_tilt);
    digitalWrite(LED_V_DOWN, HIGH);
    delay(servo_delay);
  }
  else
    digitalWrite(LED_V_DOWN, LOW);

  if (digitalRead(SW_STICK_UP) == LOW) {   // Tilt High limit 48
    angle_tilt -= 1;
    s_tilt.write(angle_tilt);
    digitalWrite(LED_V_UP, HIGH);
    delay(servo_delay);
  }
  else
    digitalWrite(LED_V_UP, LOW);

  if (digitalRead(SW_RESET) == LOW) {
    while (angle_pan != 98 || angle_tilt != 88) {
      if(angle_pan != 98)
        angle_pan += (98 - angle_pan > 0) * 2 - 1;
      if(angle_tilt != 88)
        angle_tilt += (88 - angle_tilt > 0) * 2 - 1;
      s_pan.write(angle_pan);
      s_tilt.write(angle_tilt);
      delay(10);
      Serial.println(angle_tilt);
    }
  }
  servo_delay = map(analogRead(POT_SPD), 450, 820, 30, 0);
  int pot = analogRead(POT_SPD);
  if (pot - oldpot < -10 || pot - oldpot > 10) {
    eye_period = map(pot, 450, 820, 8000, 500);
    oldpot = pot;
  }
  if (analogRead(SW_MODE) < 100) {  //▶singl shot
    if (digitalRead(SW_TRIGGER) == LOW) {
      if (triggered == false) {
        triggered = true;
        mp3_play(0004);          // single shot
        digitalWrite(LED_GUN, HIGH);
        s_tilt.write(angle_tilt - 5);
        delay(70);
        digitalWrite(LED_GUN, LOW);
        s_tilt.write(angle_tilt);
        delay(100);
      }
    }
    else {
      triggered = false;
    }
  }

  else {
    if (digitalRead(SW_TRIGGER) == LOW) {  //▶▶▶machinegun Mode
      mp3_play(0004);          // single shot
      digitalWrite(LED_GUN, HIGH);
      s_tilt.write(angle_tilt - 5);
      delay(70);
      digitalWrite(LED_GUN, LOW);
      s_tilt.write(angle_tilt);
      delay(100);
    }
  }
}

void move_left()
{
  angle_pan += 1;
  //mp3_play(0003);
  s_pan.write(angle_pan);
  digitalWrite(LED_V_R, HIGH);
  delay(servo_delay);
}

void move_right()
{
  angle_pan -= 1;
  //mp3_play(0003);
  s_pan.write(angle_pan);
  digitalWrite(LED_V_L, HIGH);
  delay(servo_delay);
}
//Elehobby3 Coding P3 Kumamon_V1.0 2025.05.25 By CJ Park, Fin code edited 25.10.20
#include <Servo.h>

#define PIN_IR_RIGHT 2
#define PIN_IR_CENTER 3
#define PIN_IR_LEFT 4

Servo servo_head;                   //Left 141 Center 96 Right 51
Servo servo_waist;                  //Down 35 Center 90 Over 145

void setup() {
  pinMode(PIN_IR_RIGHT, INPUT);
  pinMode(PIN_IR_CENTER, INPUT);
  pinMode(PIN_IR_LEFT, INPUT);

  servo_head.attach(9);
  servo_waist.attach(10);
  servo_head.write(96);
  servo_waist.write(90);
}

void loop() {
  if(digitalRead(PIN_IR_RIGHT) == LOW) { //Sensing RIGHT----
    for(int i = 96; i >= 51; i--) {
      servo_head.write(i);
      delay(10);
    }
    delay(500);

//Bow-Start--------------
    for(int i = 90; i >= 35; i--) {
      servo_waist.write(i);
      delay(10);
    }
    delay(500);
    for(int i = 35; i <= 90; i++) {
      servo_waist.write(i);
      delay(10);
    }
//Bow-End--------------

    for(int i = 51; i <= 96; i++) {
      servo_head.write(i);
      delay(10);
    }
  }

  if(digitalRead(PIN_IR_CENTER) == LOW) { //Sensing CENTER----
//Bow-Start--------------
    for(int i = 90; i >= 35; i--) {
      servo_waist.write(i);
      delay(10);
    }
    delay(500);
    for(int i = 35; i <= 90; i++) {
      servo_waist.write(i);
      delay(10);
    }
//Bow-End--------------
  }

  if(digitalRead(PIN_IR_LEFT) == LOW) { //Sensing LEFT----
    for(int i = 96; i <= 141; i++) {
      servo_head.write(i);
      delay(10);
    }
    delay(500);

//Bow-Start--------------
    for(int i = 90; i >= 35; i--) {
      servo_waist.write(i);
      delay(10);
    }
    delay(500);
    for(int i = 35; i <= 90; i++) {
      servo_waist.write(i);
      delay(10);
    }
//Bow-End--------------

    for(int i = 141; i >= 96; i--) {
      servo_head.write(i);
      delay(10);
    }
  }
}
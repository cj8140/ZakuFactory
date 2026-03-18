//Elehobby3 Coding P3 Kumamon_V1.0 2025.05.25 By CJ Park, Fin code edited 25.10.20
#include <Servo.h>

#define IR_RIGHT_PIN 2
#define IR_CENTER_PIN 3
#define IR_LEFT_PIN 4

Servo head_Servo;                   //Left 141 Center 96 Right 51
Servo waist_Servo;                  //Down 35 Center 90 Over 145

void setup() {
  pinMode(IR_RIGHT_PIN, INPUT);
  pinMode(IR_CENTER_PIN, INPUT);
  pinMode(IR_LEFT_PIN, INPUT);

  head_Servo.attach(9);
  waist_Servo.attach(10);
  head_Servo.write(96);
  waist_Servo.write(90);
}

void loop() {
  if(digitalRead(IR_RIGHT_PIN) == LOW) { //Sensing RIGHT----
    for(int i = 96; i >= 51; i--) {
      head_Servo.write(i);
      delay(10);
    }
    delay(500);

//Bow-Start--------------
    for(int i = 90; i >= 35; i--) {
      waist_Servo.write(i);
      delay(10);
    }
    delay(500);
    for(int i = 35; i <= 90; i++) {
      waist_Servo.write(i);
      delay(10);
    }
//Bow-End--------------

    for(int i = 51; i <= 96; i++) {
      head_Servo.write(i);
      delay(10);
    }
  }

  if(digitalRead(IR_CENTER_PIN) == LOW) { //Sensing CENTER----
//Bow-Start--------------
    for(int i = 90; i >= 35; i--) {
      waist_Servo.write(i);
      delay(10);
    }
    delay(500);
    for(int i = 35; i <= 90; i++) {
      waist_Servo.write(i);
      delay(10);
    }
//Bow-End--------------
  }

  if(digitalRead(IR_LEFT_PIN) == LOW) { //Sensing LEFT----
    for(int i = 96; i <= 141; i++) {
      head_Servo.write(i);
      delay(10);
    }
    delay(500);

//Bow-Start--------------
    for(int i = 90; i >= 35; i--) {
      waist_Servo.write(i);
      delay(10);
    }
    delay(500);
    for(int i = 35; i <= 90; i++) {
      waist_Servo.write(i);
      delay(10);
    }
//Bow-End--------------

    for(int i = 141; i >= 96; i--) {
      head_Servo.write(i);
      delay(10);
    }
  }
}
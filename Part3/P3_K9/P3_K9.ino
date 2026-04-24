#include <Servo.h>

#define PIN_JOY_X A1  //left 0 522
#define PIN_JOY_Y A2  //up 0   519
#define PIN_JOY_SW A3

Servo servo_turret;  // 180 98 16
Servo servo_barrel;  //HIGH 32  99 104    LOW ; Ori HIGH 36 106 108 LOW

int angle_turret = 98;
int angle_barrel = 99;

void setup()
{
  pinMode(PIN_JOY_SW, INPUT_PULLUP);

  servo_turret.write(angle_turret);
  servo_barrel.write(angle_barrel);

  servo_turret.attach(9);
  servo_barrel.attach(10);
}

void loop()
{
  if (analogRead(PIN_JOY_X) > 720) {  //right
    angle_turret -= 1;
    delay(60);
  }
  else if (analogRead(PIN_JOY_X) < 320) {  //left
    angle_turret += 1;
    delay(60);
  }
  angle_turret = constrain(angle_turret, 16, 180);
  servo_turret.write(angle_turret);

  if (analogRead(PIN_JOY_Y) > 720) {  //down
    angle_barrel += 1;
    delay(60);
  }
  else if (analogRead(PIN_JOY_Y) < 320) {  //up
    angle_barrel -= 1;
    delay(60);
  }
  angle_barrel = constrain(angle_barrel, 32, 104);
  servo_barrel.write(angle_barrel);

  if (digitalRead(PIN_JOY_SW) == LOW) {                          //천천히 리셋
    for (int i = 0; i < 100; i++) {
      servo_turret.write(map(i, 0, 100, angle_turret, 98));
      servo_barrel.write(map(i, 0, 100, angle_barrel, 99));
      delay(10);
    }
    angle_turret = 98;
    angle_barrel = 99;
  }  
}
//1 그냥 매핑
// servo_turret.write(map(analogRead(PIN_JOY_X), 0, 1023, 180, 16));
// if(analogRead(PIN_JOY_Y) < 520) {
//   servo_barrel.write(map(analogRead(PIN_JOY_Y), 0, 520, 32, 104));
// }


//2 느린 매핑
  // angle_turret = angle_turret*0.9 + map(analogRead(PIN_JOY_X), 0, 1023, 180, 16)*0.1;  //*숫자 두 합 1이 되도록. 앞의 숫자가 클 수록 느려짐
  // angle_barrel = angle_barrel*0.9 + map(analogRead(PIN_JOY_Y), 0, 1023, 32, 104)*0.1;
  // servo_turret.write(angle_turret);
  // servo_barrel.write(angle_barrel);
  // delay(100);
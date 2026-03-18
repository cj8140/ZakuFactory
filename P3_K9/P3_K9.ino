#include <Servo.h>

#define JOYX_PIN A1  //left 0 522
#define JOYY_PIN A2  //up 0   519
#define JOYSW_PIN A3

Servo turret_Servo;  // 180 98 16
Servo barrel_Servo;  //HIGH 32  99 104    LOW ; Ori HIGH 36 106 108 LOW

int turret_angle = 98;
int barrel_angle = 99;

void setup()
{
  pinMode(JOYSW_PIN, INPUT_PULLUP);

  turret_Servo.write(98);
  barrel_Servo.write(99);

  barrel_Servo.attach(9);
  turret_Servo.attach(10);
}

void loop()
{
  if (analogRead(JOYX_PIN) > 720) {  //right
    turret_angle -= 1;
    delay(60);
  }
  else if (analogRead(JOYX_PIN) < 320) {  //left
    turret_angle += 1;
    delay(60);
  }
  turret_angle = constrain(turret_angle, 16, 180);
  turret_Servo.write(turret_angle);

  if (analogRead(JOYY_PIN) > 720) {  //down
    barrel_angle += 1;
    delay(60);
  }
  else if (analogRead(JOYY_PIN) < 320) {  //up
    barrel_angle -= 1;
    delay(60);
  }
  barrel_angle = constrain(barrel_angle, 32, 104);
  barrel_Servo.write(barrel_angle);

  if (digitalRead(JOYSW_PIN) == LOW) {                          //천천히 리셋
    for (int i = 0; i < 100; i++) {
      turret_Servo.write(map(i, 0, 100, turret_angle, 98));
      barrel_Servo.write(map(i, 0, 100, barrel_angle, 99));
      delay(10);
    }
    turret_angle = 98;
    barrel_angle = 99;
  }  
}
//1 그냥 매핑
// turret_Servo.write(map(analogRead(JOYX_PIN), 0, 1023, 180, 16));
// if(analogRead(JOYY_PIN) < 520) {
//   barrel_Servo.write(map(analogRead(JOYY_PIN), 0, 520, 32, 104));
// }


//2 느린 매핑
  // turret_angle = turret_angle*0.9 + map(analogRead(JOYX_PIN), 0, 1023, 180, 16)*0.1;  //*숫자 두 합 1이 되도록. 앞의 숫자가 클 수록 느려짐
  // barrel_angle = barrel_angle*0.9 + map(analogRead(JOYY_PIN), 0, 1023, 32, 104)*0.1;
  // turret_Servo.write(turret_angle);
  // barrel_Servo.write(barrel_angle);
  // delay(100);
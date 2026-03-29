#include <Servo.h>

Servo my_servo;

int angle_servo = 45;

void setup()
{
  my_servo.attach(9);  //핀 연결
  my_servo.write(45);

  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
}

void loop()
{
  if (digitalRead(2) == LOW) {
    angle_servo++;
    if(angle_servo > 180) {
      angle_servo = 180;
    }
    my_servo.write(angle_servo);
    delay(10);
  }
  if (digitalRead(4) == LOW) {
    angle_servo--;
    if(angle_servo < 0) {
      angle_servo = 0;
    }
    my_servo.write(angle_servo);
    delay(10);
  }
}

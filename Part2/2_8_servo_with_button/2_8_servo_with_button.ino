#include <Servo.h>

Servo my_servo;

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
    my_servo.write(45);
  }
  if (digitalRead(4) == LOW) {
    my_servo.write(135);
  }
}

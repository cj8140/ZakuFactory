#define PIN_BUTTON_CW 2
#define PIN_BUTTON_CCW 4

#define PIN_MOTOR_A 5
#define PIN_MOTOR_B 6

#define SPEED_MOTOR 127

void setup()
{
  pinMode(PIN_BUTTON_CW, INPUT_PULLUP);
  pinMode(PIN_BUTTON_CCW, INPUT_PULLUP);

  analogWrite(PIN_MOTOR_A, 0);
  analogWrite(PIN_MOTOR_B, 0);
}

void loop()
{
  if (digitalRead(PIN_BUTTON_CW) == LOW) {
    analogWrite(PIN_MOTOR_A, 0);
    analogWrite(PIN_MOTOR_B, SPEED_MOTOR);
  }
  else if (digitalRead(PIN_BUTTON_CCW) == LOW) {
    analogWrite(PIN_MOTOR_A, SPEED_MOTOR);
    analogWrite(PIN_MOTOR_B, 0);
  }
  else {
    analogWrite(PIN_MOTOR_A, 0);
    analogWrite(PIN_MOTOR_B, 0);
  }
}

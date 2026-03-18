//Elehobby3 Coding P3 F4F_V1.0 2025.10.01 By Kyoji Park
#include <Servo.h>

#define TOUCH 2 // Red LED Yellow -- wire
#define LED_COCKPIT 3 // War-W LED Orange wire
#define LED_BACK 5 // Red LED Yellow -- wire
#define LED_LEFT 6 // Yellow LED Yellow wire
#define LED_FRONT 11 // Blue LED Blue wire

#define DELAY_FRONT 3000 // Ori 1000 code from Police Zaku
#define BRIGHT_SENSOR 40 // Red, Yellow LED
#define BRIGHT_FRONT 70 // Blue LED

Servo SERVO_HATCH;      //Close 90,  Open 53 <- Ori 91,44
int STATE=1;   // for switch toggle

void setup() {
  pinMode(TOUCH, INPUT);

  SERVO_HATCH.attach(9);
  SERVO_HATCH.write(90);

  analogWrite(LED_FRONT, BRIGHT_FRONT);
  analogWrite(LED_LEFT, BRIGHT_SENSOR);
  analogWrite(LED_BACK, BRIGHT_SENSOR);
}

void loop() {
  analogWrite(LED_FRONT, (sin(2 * 3.14 * (millis() % DELAY_FRONT) / DELAY_FRONT + 3.14) + 1) * BRIGHT_FRONT);

  if (digitalRead(TOUCH) == HIGH && STATE==1) {
    for(int i = BRIGHT_SENSOR; i >= 0; i--) {
      analogWrite(LED_LEFT, i);
      analogWrite(LED_BACK, i);
      delay(10);
    }
    delay(500);

    analogWrite(LED_COCKPIT, 80);

      for(int i = 90; i >= 53; i--) {
      SERVO_HATCH.write(i);
      delay(40);
    }
    STATE=0;
  }

  if (digitalRead(TOUCH) == HIGH && STATE==0) {
      for(int i = 53; i <= 90; i++) {
      SERVO_HATCH.write(i);
      delay(40);
      }
    delay(530);

    analogWrite(LED_COCKPIT, 0);

    for(int i = 0; i <= BRIGHT_SENSOR; i++) {
      analogWrite(LED_LEFT, i);
      analogWrite(LED_BACK, i);
      delay(40);
    }
    STATE=1;
  }
}
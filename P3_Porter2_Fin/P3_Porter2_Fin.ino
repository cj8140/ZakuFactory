//Elehobby3 Coding P3 Porter2 V1.0 2025.05.08 By CJ Park, Fin Code by Kyoji Park 25.10.20
#define RELAY_PIN 2

#define SW_LEFT_PIN 4
#define SW_RIGHT_PIN 5
#define SW_HAZARD_PIN 7
#define SW_LIGHT_PIN 8

#define LED_LIGHT_PIN 10
#define LED_LEFT_PIN 11
#define LED_RIGHT_PIN 12

bool hazardOn = 0;

void setup()
{
  pinMode(RELAY_PIN, OUTPUT);

  pinMode(LED_LEFT_PIN, OUTPUT);
  pinMode(LED_RIGHT_PIN, OUTPUT);
  pinMode(LED_LIGHT_PIN, OUTPUT);

  pinMode(SW_LEFT_PIN, INPUT_PULLUP);
  pinMode(SW_RIGHT_PIN, INPUT_PULLUP);
  pinMode(SW_HAZARD_PIN, INPUT_PULLUP);
  pinMode(SW_LIGHT_PIN, INPUT_PULLUP);
}

void loop()
{
  if (digitalRead(SW_LIGHT_PIN) == LOW) {
    digitalWrite(LED_LIGHT_PIN, HIGH);
  }
  else {
    digitalWrite(LED_LIGHT_PIN, LOW);
  }

  if (digitalRead(SW_HAZARD_PIN) == LOW) {
    hazardOn = !hazardOn;
    delay(300);
  }
  bool timing = (millis() % 800) / 400 && HIGH;  //%(전체 시간), /(꺼져있는 시간)

  bool leftSign = !digitalRead(SW_LEFT_PIN);
  bool rightSign = !digitalRead(SW_RIGHT_PIN);

  if (hazardOn) {
    if (timing) {
      digitalWrite(LED_LEFT_PIN, HIGH);
      digitalWrite(LED_RIGHT_PIN, HIGH);
      digitalWrite(RELAY_PIN, HIGH);
    }
    else {
      digitalWrite(LED_LEFT_PIN, LOW);
      digitalWrite(LED_RIGHT_PIN, LOW);
      digitalWrite(RELAY_PIN, LOW);
    }
  }

  else if (leftSign) {
    if (timing) {
      digitalWrite(LED_LEFT_PIN, HIGH);
      digitalWrite(LED_RIGHT_PIN, LOW);
      digitalWrite(RELAY_PIN, HIGH);
    }
    else {
      digitalWrite(LED_LEFT_PIN, LOW);
      digitalWrite(RELAY_PIN, LOW);
    }
  }

  else if (rightSign) {
    if (timing) {
      digitalWrite(LED_RIGHT_PIN, HIGH);
      digitalWrite(LED_LEFT_PIN, LOW);
      digitalWrite(RELAY_PIN, HIGH);
    }
    else {
      digitalWrite(LED_RIGHT_PIN, LOW);
      digitalWrite(RELAY_PIN, LOW);
    }
  }

  else {
      digitalWrite(LED_RIGHT_PIN, LOW);
      digitalWrite(LED_LEFT_PIN, LOW);
      digitalWrite(RELAY_PIN, LOW);
  }
}
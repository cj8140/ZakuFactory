//Elehobby3 Coding P3 Porter2 V1.5 2026.04.13 By CJ Park // 
#define DURATION_BLINK 400   // 200->400 조금빠른듯해서 숫자변경

#define PIN_RELAY 2

#define PIN_SW_LEFT 4
#define PIN_SW_RIGHT 5
#define PIN_SW_HAZARD 7
#define PIN_SW_LIGHT 8

#define PIN_LED_LIGHT 10
#define PIN_LED_LEFT 11
#define PIN_LED_RIGHT 12

bool state_hazard = 0;

void setup()
{
  pinMode(PIN_RELAY, OUTPUT);

  pinMode(PIN_LED_LEFT, OUTPUT);
  pinMode(PIN_LED_RIGHT, OUTPUT);
  pinMode(PIN_LED_LIGHT, OUTPUT);

  pinMode(PIN_SW_LEFT, INPUT_PULLUP);
  pinMode(PIN_SW_RIGHT, INPUT_PULLUP);
  pinMode(PIN_SW_HAZARD, INPUT_PULLUP);
  pinMode(PIN_SW_LIGHT, INPUT_PULLUP);
}

void loop()
{
  if (digitalRead(PIN_SW_LIGHT) == LOW) {
    digitalWrite(PIN_LED_LIGHT, HIGH);
  }
  else {
    digitalWrite(PIN_LED_LIGHT, LOW);
  }

  if (digitalRead(PIN_SW_HAZARD) == LOW) {
    state_hazard = !state_hazard;
    delay(300);
  }
  
  bool light_on = (millis() / DURATION_BLINK) % 2 ;

  if (state_hazard) {
    if (light_on) {
      digitalWrite(PIN_LED_LEFT, HIGH);
      digitalWrite(PIN_LED_RIGHT, HIGH);
      digitalWrite(PIN_RELAY, HIGH);
    }
    else {
      digitalWrite(PIN_LED_LEFT, LOW);
      digitalWrite(PIN_LED_RIGHT, LOW);
      digitalWrite(PIN_RELAY, LOW);
    }
  }

  else if (digitalRead(PIN_SW_LEFT) == LOW) {
    if (light_on) {
      digitalWrite(PIN_LED_LEFT, HIGH);
      digitalWrite(PIN_LED_RIGHT, LOW);
      digitalWrite(PIN_RELAY, HIGH);
    }
    else {
      digitalWrite(PIN_LED_LEFT, LOW);
      digitalWrite(PIN_RELAY, LOW);
    }
  }

  else if (digitalRead(PIN_SW_RIGHT) == LOW) {
    if (light_on) {
      digitalWrite(PIN_LED_LEFT, LOW);
      digitalWrite(PIN_LED_RIGHT, HIGH);
      digitalWrite(PIN_RELAY, HIGH);
    }
    else {
      digitalWrite(PIN_LED_RIGHT, LOW);
      digitalWrite(PIN_RELAY, LOW);
    }
  }

  else {
      digitalWrite(PIN_LED_LEFT, LOW);
      digitalWrite(PIN_LED_RIGHT, LOW);
      digitalWrite(PIN_RELAY, LOW);
  }
}
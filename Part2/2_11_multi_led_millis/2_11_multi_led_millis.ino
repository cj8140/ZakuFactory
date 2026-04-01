#define LED1 2
#define LED2 3

#define PERIOD_BLINK 500
#define PERIOD_FADING 1000

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop()
{
  digitalWrite(LED1, (millis() / (PERIOD_BLINK/2)) % 2);                  //PERIOD_BLINK/2 만큼 켜지고 PERIOD_BLINK/2 만큼 꺼지고
  analogWrite(LED2, (int)((sin(TWO_PI * millis() / (float)PERIOD_FADING) + 1.0) * 127.5));
}

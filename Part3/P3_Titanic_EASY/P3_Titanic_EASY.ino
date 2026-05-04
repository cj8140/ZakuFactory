#include <FastLED.h>

#define PIN_SW_COLOR 2
#define PIN_SW_MODE 4
#define PIN_LED 6       // LED 스트립 연결 핀

#define NUM_LEDS 20     // LED 개수
#define BRIGHTNESS 255  // 밝기 (0~255)

CRGB leds[NUM_LEDS];
int value[NUM_LEDS];
int delta[NUM_LEDS];

void setup()
{
  pinMode(PIN_SW_COLOR, INPUT_PULLUP);
  pinMode(PIN_SW_MODE, INPUT_PULLUP);

  FastLED.addLeds<WS2812, PIN_LED, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255, 0, 0);
    value[i] = 0;
    delta[i] = 0;
  }
  FastLED.show();
}

void loop()
{
  if (digitalRead(PIN_SW_MODE) == LOW) {
    static unsigned long timer = 0;
    if (millis() - timer > 200) {
      int who_start = random(0, NUM_LEDS);
      delta[who_start] = 2;
      timer = millis();
    }
    for (int i = 0; i < NUM_LEDS; i++) {
      value[i] += delta[i];
      if (value[i] < 0) {
        value[i] = 0;
        delta[i] = 0;
      }
      if (value[i] > 250) {
        value[i] = 250;
        delta[i] = -20;
      }
      if (digitalRead(PIN_SW_COLOR) == LOW) {
        leds[i] = CRGB(value[i], value[i], value[i]);
      }
      else {
        leds[i] = CRGB(value[i], (int)(value[i] * 0.5), (int)(value[i] * 0.05));
      }
    }
  }
  else {
    for (int i = 0; i < NUM_LEDS; i++) {
      if (digitalRead(PIN_SW_COLOR) == LOW) {
        leds[i] = CRGB(255, 255, 255);
      }
      else {
        leds[i] = CRGB(255, 153, 13);
      }
    }
  }
  FastLED.show();
  delay(10);
}
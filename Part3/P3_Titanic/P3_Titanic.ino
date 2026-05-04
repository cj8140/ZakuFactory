#include <FastLED.h>

#define PIN_SW_COLOR 2
#define PIN_SW_MODE 4
#define PIN_LED 6       // LED 스트립 연결 핀

#define NUM_LEDS 20     // LED 개수
#define BRIGHTNESS 255  // 밝기 (0~255)

CRGB leds[NUM_LEDS];

void setup() {
  pinMode(PIN_SW_COLOR, INPUT_PULLUP);
  pinMode(PIN_SW_MODE, INPUT_PULLUP);

  FastLED.addLeds<WS2812, PIN_LED, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255, 0, 0);
  }
  FastLED.show();
}

void loop() {
  if( digitalRead(PIN_SW_MODE)  == LOW) {
    for(int i = 0; i < NUM_LEDS; i++) {
      int value_noise = inoise8(i*100, millis()/3);
      if(digitalRead(PIN_SW_COLOR) == LOW) {
        leds[i] = CRGB(value_noise, value_noise, value_noise);
      }
      else {
        int RED = value_noise;
        int GREEN = value_noise * 0.5;   // 초록 50%
        int BLUE = value_noise * 0.05;  // 파랑  5%
        leds[i] = CRGB(RED, GREEN, BLUE);
      }
    }
  }
  else {
    for(int i = 0; i < NUM_LEDS; i++) {
      if(digitalRead(PIN_SW_COLOR) == LOW) {
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
#include <FastLED.h>

#define LED_PIN 3      // LED 스트립 연결 핀
#define NUM_LEDS 1     // LED 개수
#define BRIGHTNESS 100  

CRGB leds[NUM_LEDS];

int state = 0;

void setup() {
  pinMode(2, INPUT_PULLUP);

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  leds[0] = CRGB(255,0,0);
  FastLED.show();
}


void loop() {
  if(digitalRead(2) == LOW) {
    state++;
    if(state == 3) {
      state = 0;
    }
    
    if(state == 0) {
      leds[0] = CRGB(255,0,0);
    }
    else if(state == 1) {
      leds[0] = CRGB(0,255,0);
    }
    else if(state == 2) {
      leds[0] = CRGB(0,0,255);
    }
    FastLED.show();
    delay(500);
  }
}

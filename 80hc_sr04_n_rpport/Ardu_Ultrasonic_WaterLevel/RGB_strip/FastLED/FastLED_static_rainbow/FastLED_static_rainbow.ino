//FastLED_static_rainbow
#define LED_PIN 6
#define LED_NUM 7
#include "FastLED.h"
CRGB leds[LED_NUM];
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_NUM);
  FastLED.setBrightness(50);

  for (int i = 0; i < LED_NUM; i++) {
    leds[i].setHue(i * 255 / LED_NUM);
  }
  FastLED.show();
}
void loop(){}

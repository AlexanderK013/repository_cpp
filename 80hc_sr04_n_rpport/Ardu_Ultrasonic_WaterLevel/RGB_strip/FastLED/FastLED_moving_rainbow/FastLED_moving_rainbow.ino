//FastLED_moving_rainbow
#define LED_PIN 6
#define LED_NUM 7
#include "FastLED.h"
CRGB leds[LED_NUM];
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, LED_NUM);
  FastLED.setBrightness(50);
}
byte counter;
void loop() {
  for (int i = 0; i < LED_NUM; i++) {
    leds[i].setHue(counter + i * 255 / LED_NUM);
  }
  counter++;        // counter меняется от 0 до 255 (тип данных byte)
  FastLED.show();
  delay(30);        // скорость движения радуги
}

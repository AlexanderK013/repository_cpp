//FastLED_moving_range
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
	counter++;
	if(counter > LED_NUM)counter = 0;
    for(int dot = counter; dot < LED_NUM; dot++) {
        leds[dot] = CRGB::Red;
        //FastLED.show();
    }
    for(int dot = 0; dot < counter; dot++) {
        leds[dot] = CRGB::Blue;
        // FastLED.show();
    }
    FastLED.show();
    delay(500);
    }

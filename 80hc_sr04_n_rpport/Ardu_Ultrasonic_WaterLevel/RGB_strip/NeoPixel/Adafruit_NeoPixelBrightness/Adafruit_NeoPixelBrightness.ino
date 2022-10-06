//Adafruit_NeoPixelBrightness
#include <Adafruit_NeoPixel.h>
//#define PIN 6
#define PIXEL_PIN 6 //13 //
#define PIXEL_COUNT 7  // количество пикселей (светодиодов) в ленте
// объявление объекта:
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = количество пикселей (светодиодов)
// Argument 2 = номер управляющего пина
// Argument 3 = тип светодиода по порядку и количеству цветов, а также скорости передачи данных:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();              // начинаем
  strip.setBrightness(50);    // делаем яркость 50 (максимум 254)
  strip.show();               // очищаем экран (рекомендуется при запуске для отключения случайных пикселей
  for (byte i = 0; i < PIXEL_COUNT; i++) {
    strip.setPixelColor(i, (i+1) * 30, 0, 0); // увеличиваем яркость каждого следующего светодиода на 10
    //strip.setPixelColor(i, i * 250/PIXEL_COUNT, 0, 0); // увеличиваем яркость каждого следующего светодиода на 10
  }
  strip.show();               // выводим
}

void loop() {
}

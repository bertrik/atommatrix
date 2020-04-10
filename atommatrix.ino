#include <stdint.h>

#include <Arduino.h>
#include <FastLED.h>

#define DATA_PIN_LED 27

static CRGB leds[25];

void setup(void)
{
    Serial.begin(115200);
    Serial.println("\nHello World!");

    FastLED.addLeds < WS2812B, DATA_PIN_LED, GRB > (leds, 25);
}

void loop(void)
{
    static uint8_t hue = 0;

    Serial.println(hue);
    hue++;
    CRGB color = CHSV(hue, 255, 64);
    FastLED.showColor(color);

    delay(50);
}

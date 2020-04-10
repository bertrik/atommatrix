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
    FastLED.setBrightness(20);
}

void loop(void)
{
    static uint8_t hue = 0;
    static uint32_t last_time = 0;

    uint32_t time = millis() / 50;
    if (time != last_time) {
        last_time = time;
        hue++;
    }

    CRGB color = CHSV(hue, 255, 255);
    FastLED.showColor(color);
}

#include <stdint.h>

#include <Arduino.h>
#include <FastLED.h>

#include "MPU6886.h"

#define DATA_PIN_LED 27

static CRGB leds[25];
static MPU6886 mpu;

void setup(void)
{
    Serial.begin(115200);
    Serial.println("\nHello World!");

    FastLED.addLeds < WS2812B, DATA_PIN_LED, GRB > (leds, 25);
    FastLED.setBrightness(20);

    mpu.Init();
}

static int accel_to_color(float a)
{
    int v = 128 + 127 * a;
    return (v < 0) ? 0 : (v > 255) ? 255 : v;
}

void loop(void)
{
    float x, y, z;

    mpu.getAccelData(&x, &y, &z);
    Serial.printf("%f %f %f\n", x, y, z);

    int r = accel_to_color(x);
    int g = accel_to_color(y);
    int b = accel_to_color(z);
    CRGB color = CRGB(r, g, b);
    FastLED.showColor(color);
}

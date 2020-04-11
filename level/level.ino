#include <stdint.h>
#include <string.h>

#include <Arduino.h>
#include <FastLED.h>

#include "MPU6886.h"

#define DATA_PIN_LED 27

const float gain = -5.0;

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

static void setled(int x, int y, CRGB c)
{
    leds[y * 5 + x] = c;
}

// x, y can be -1, 0, +1
static void draw_bubble(int x, int y)
{
    x = 2 + ((x < 0) ? -1 : (x > 0) ? 1 : 0);
    y = 2 + ((y < 0) ? -1 : (y > 0) ? 1 : 0);

    memset(leds, 0, sizeof(leds));
    CRGB c = CRGB::White;

    setled(x - 1,   y - 1,  c);
    setled(x,       y - 1,  c);
    setled(x + 1,   y - 1,  c);
    setled(x + 1,   y,      c);
    setled(x + 1,   y + 1,  c);
    setled(x,       y + 1,  c);
    setled(x - 1,   y + 1,  c);
    setled(x - 1,   y,      c);
}



void loop(void)
{
    float x, y, z;

    mpu.getAccelData(&x, &y, &z);
    int lr = (gain * x);
    int fb = (gain * y);

    Serial.printf("%f %f %f\n", x, y, z);

    draw_bubble(lr, fb);

    FastLED.show();
}



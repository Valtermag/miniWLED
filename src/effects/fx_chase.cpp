#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_chase(uint32_t now, const EffectParams& p) {
    static int pos = 0;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 50, 6)) return;
    last = now;

    fadeToBlackBy(leds, NUM_LEDS, 50);
    leds[pos] = p.color;

    pos = (pos + 1) % NUM_LEDS;
}
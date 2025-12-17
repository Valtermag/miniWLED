#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_kitt(uint32_t now, const EffectParams& p) {
    static int pos = 0;
    static int dir = 1;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 40, 6)) return;
    last = now;

    fadeToBlackBy(leds, NUM_LEDS, 40);
    leds[pos] = p.color;

    pos += dir;
    if (pos <= 0 || pos >= NUM_LEDS - 1) dir = -dir;
}
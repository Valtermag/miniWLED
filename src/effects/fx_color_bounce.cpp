#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_color_bounce(uint32_t now, const EffectParams& p) {
    static int pos = 0;
    static int dir = 1;
    static uint32_t last = 0;

    uint16_t interval = map(p.speed, 0, 255, 40, 4);
    if (now - last < interval) return;
    last = now;

    fadeToBlackBy(leds, NUM_LEDS, 60);
    leds[pos] = p.color;

    pos += dir;
    if (pos <= 0 || pos >= NUM_LEDS - 1) dir = -dir;
}
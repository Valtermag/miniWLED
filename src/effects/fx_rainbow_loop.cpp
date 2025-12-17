#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_rainbow_loop(uint32_t now, const EffectParams& p) {
    static uint16_t pos = 0;
    static uint32_t last = 0;

    uint16_t interval = map(p.speed, 0, 255, 50, 5);
    if (now - last < interval) return;
    last = now;

    fadeToBlackBy(leds, NUM_LEDS, 40);
    leds[pos] = CHSV(now / 10, 255, 255);

    pos = (pos + 1) % NUM_LEDS;
}
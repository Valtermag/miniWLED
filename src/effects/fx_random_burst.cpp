#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_random_burst(uint32_t now, const EffectParams& p) {
    static uint32_t last = 0;
    uint16_t interval = map(p.speed, 0, 255, 120, 10);
    if (now - last < interval) return;
    last = now;

    fadeToBlackBy(leds, NUM_LEDS, 50);

    uint16_t i = random16(NUM_LEDS);
    leds[i] = CHSV(random8(), 255, 255);
}
#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_sparkle_white(uint32_t now, const EffectParams& p) {
    static uint32_t last = 0;
    if (now - last < map(p.speed, 0, 255, 80, 10)) return;
    last = now;

    fadeToBlackBy(leds, NUM_LEDS, 40);
    leds[random16(NUM_LEDS)] = CRGB::White;
}

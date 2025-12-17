#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_strip_march_ccw(uint32_t now, const EffectParams& p) {
    static uint32_t last = 0;
    if (now - last < map(p.speed, 0, 255, 80, 12)) return;
    last = now;

    CRGB prev = leds[0];
    for (uint16_t i = 0; i < NUM_LEDS - 1; i++) {
        leds[i] = leds[i + 1];
    }
    leds[NUM_LEDS - 1] = prev;
}
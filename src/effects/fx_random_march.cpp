#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_random_march(uint32_t now, const EffectParams& p) {
    static uint32_t last = 0;
    if (now - last < map(p.speed, 0, 255, 80, 10)) return;
    last = now;

    bool cw = random8() > 128;
    CRGB prev[NUM_LEDS];
    memcpy(prev, leds, sizeof(prev));

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        int j = cw ? (i + 1) % NUM_LEDS : (i - 1 + NUM_LEDS) % NUM_LEDS;
        leds[i] = prev[j];
    }
}
#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_rwb_march(uint32_t now, const EffectParams& p) {
    static uint32_t last = 0;
    if (now - last < map(p.speed, 0, 255, 80, 10)) return;
    last = now;

    CRGB prev[NUM_LEDS];
    memcpy(prev, leds, sizeof(prev));

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        leds[i] = prev[(i + 1) % NUM_LEDS];
    }
}

#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_ems_strobe(uint32_t now, const EffectParams& p) {
    static bool phase = false;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 100, 20)) return;
    last = now;

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        bool left = i < NUM_LEDS / 2;
        leds[i] = (phase ^ left) ? CRGB::Red : CRGB::Blue;
    }

    phase = !phase;
}
#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_flicker(uint32_t now, const EffectParams& p) {
    static uint32_t last = 0;
    if (now - last < 30) return;
    last = now;

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(20, 200, random8(120, 255));
    }
}
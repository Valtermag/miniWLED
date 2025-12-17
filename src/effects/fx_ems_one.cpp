#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_ems_one(uint32_t now, const EffectParams& p) {
    static bool side = false;
    static uint32_t last = 0;

    if (now - last < 120) return;
    last = now;

    fill_solid(leds, NUM_LEDS, CRGB::Black);

    for (uint16_t i = 0; i < NUM_LEDS / 2; i++) {
        uint16_t idx = side ? i : i + NUM_LEDS / 2;
        leds[idx] = side ? CRGB::Red : CRGB::Blue;
    }

    side = !side;
}
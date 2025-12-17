#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_theater_chase_soft(uint32_t now, const EffectParams& p) {
    static uint8_t q = 0;
    q = (q + 1) % 3;

    fill_solid(leds, NUM_LEDS, CRGB::Black);

    for (int i = q; i < NUM_LEDS; i += 3) {
        leds[i] = p.color;
    }
}
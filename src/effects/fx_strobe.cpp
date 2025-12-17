#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_strobe(uint32_t now, const EffectParams& p) {
    static bool on = false;
    static uint32_t last = 0;

    uint16_t interval = map(p.speed, 0, 255, 120, 20);
    if (now - last < interval) return;
    last = now;

    fill_solid(leds, NUM_LEDS, on ? CRGB::White : CRGB::Black);
    on = !on;
}
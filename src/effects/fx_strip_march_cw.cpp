#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_strip_march_cw(uint32_t now, const EffectParams& p) {
    static uint32_t last = 0;
    if (now - last < map(p.speed, 0, 255, 80, 12)) return;
    last = now;

    CRGB prev = leds[NUM_LEDS - 1];
    for (int i = NUM_LEDS - 1; i > 0; i--) {
        leds[i] = leds[i - 1];
    }
    leds[0] = prev;
}
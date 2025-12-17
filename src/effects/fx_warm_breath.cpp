#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_warm_breath(uint32_t now, const EffectParams& p) {
    static uint8_t phase = 0;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 45, 15)) return;
    last = now;

    phase++;

    uint8_t b = sin8(phase);
    CRGB warm(255, 140, 40);
    warm.nscale8(b);

    fill_solid(leds, NUM_LEDS, warm);
}
#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_rainbow_fade(uint32_t now, const EffectParams& p) {
    static uint8_t hue = 0;
    static uint32_t last = 0;

    uint16_t interval = map(p.speed, 0, 255, 40, 2);
    if (now - last < interval) return;
    last = now;

    hue++;

    fill_rainbow(leds, NUM_LEDS, hue, 1);
}
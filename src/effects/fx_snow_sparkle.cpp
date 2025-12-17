#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_snow_sparkle(uint32_t now, const EffectParams& p) {
    static uint32_t last = 0;
    if (now - last < 40) return;
    last = now;

    fill_solid(leds, NUM_LEDS, CHSV(160, 20, 180));

    if (random8() < map(p.intensity, 0, 255, 20, 80)) {
        leds[random16(NUM_LEDS)] = CRGB::White;
    }
}
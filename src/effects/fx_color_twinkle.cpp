#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_color_twinkle(uint32_t now, const EffectParams& p) {
    fadeToBlackBy(leds, NUM_LEDS, 40);

    if (random8() < map(p.intensity, 0, 255, 5, 40)) {
        leds[random16(NUM_LEDS)] = CHSV(random8(), 255, 255);
    }
}
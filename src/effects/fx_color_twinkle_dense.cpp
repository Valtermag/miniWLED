#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_color_twinkle_dense(uint32_t now, const EffectParams& p) {
    fadeToBlackBy(leds, NUM_LEDS, 25);

    uint8_t count = map(p.intensity, 0, 255, 1, 8);
    for (uint8_t i = 0; i < count; i++) {
        leds[random16(NUM_LEDS)] = CHSV(random8(), 255, 255);
    }
}
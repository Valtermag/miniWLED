#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_quad_bright_curve(uint32_t now, const EffectParams& p) {
    CHSV base = rgb2hsv_approximate(p.color);

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        float x = (float)i / (float)(NUM_LEDS - 1);
        uint8_t b = (uint8_t)(x * x * 255.0f);
        leds[i] = CHSV(base.h, base.s, b);
    }
}
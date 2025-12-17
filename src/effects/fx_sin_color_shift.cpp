#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_sin_color_shift(uint32_t now, const EffectParams& p) {
    static uint8_t t = 0;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 25, 6)) return;
    last = now;

    t++;

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        uint8_t h = sin8(i * 5 + t);
        uint8_t b = sin8(i * 3 + t);
        leds[i] = CHSV(h, 255, b);
    }
}
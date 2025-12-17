#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_soft_color_noise(uint32_t now, const EffectParams& p) {
    static uint16_t t = 0;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 40, 12)) return;
    last = now;

    t++;

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        uint8_t n = inoise8(i * 20, t);
        leds[i] = CHSV(n, 200, 120);
    }
}
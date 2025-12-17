#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_aurora(uint32_t now, const EffectParams& p) {
    static uint16_t t = 0;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 40, 10)) return;
    last = now;

    t++;

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        uint8_t n = inoise8(i * 15, t);
        leds[i] = CHSV(96 + n / 4, 180, n);
    }
}
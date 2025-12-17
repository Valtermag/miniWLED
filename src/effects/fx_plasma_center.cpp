#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_plasma_center(uint32_t now, const EffectParams& p) {
    static uint8_t t = 0;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 35, 8)) return;
    last = now;

    t++;

    int center = NUM_LEDS / 2;
    for (int i = 0; i < NUM_LEDS; i++) {
        uint8_t d = abs(i - center);
        uint8_t v = sin8(d * 8 + t);
        leds[i] = CHSV(v, 255, v);
    }
}
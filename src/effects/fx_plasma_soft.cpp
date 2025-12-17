#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_plasma_soft(uint32_t now, const EffectParams& p) {
    static uint8_t offset = 0;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 35, 8)) return;
    last = now;

    offset++;

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        uint8_t v = sin8(i * 8 + offset) + cos8(i * 4 + offset);
        leds[i] = CHSV(v, 255, v);
    }
}
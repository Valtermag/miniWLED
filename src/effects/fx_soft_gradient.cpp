#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_soft_gradient(uint32_t now, const EffectParams& p) {
    static uint8_t offset = 0;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 50, 15)) return;
    last = now;

    offset++;

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(offset + i * 2, 180, 180);
    }
}
#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_fire_slow(uint32_t now, const EffectParams& p) {
    static uint16_t nx = 0, ny = 0, nz = 0;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 60, 15)) return;
    last = now;

    nz += 1;
    ny += 1;
    nx += 1;

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        uint8_t n = inoise8(i * 50 + nx, ny, nz);
        leds[i] = CHSV(5 + n / 20, 255, n);
    }
}
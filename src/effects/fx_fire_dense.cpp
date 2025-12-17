#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_fire_dense(uint32_t now, const EffectParams& p) {
    static uint16_t nx = 0, ny = 0, nz = 0;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 30, 8)) return;
    last = now;

    nz += map(p.intensity, 0, 255, 2, 6);
    ny += 4;
    nx += 2;

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        uint8_t n = inoise8(i * 30 + nx, ny, nz);
        uint8_t b = qadd8(n, n / 2);
        leds[i] = CHSV(6 + n / 14, 255, b);
    }
}
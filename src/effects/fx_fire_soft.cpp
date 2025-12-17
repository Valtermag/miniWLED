#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_fire_soft(uint32_t now, const EffectParams& p) {
    static uint16_t nx = 0, ny = 0, nz = 0;

    nz += map(p.speed,0,255,1,6);
    ny += 2;
    nx += 1;

    for (int i = 0; i < NUM_LEDS; i++) {
        uint8_t n = inoise8(i * 40 + nx, ny, nz);
        uint8_t bri = scale8(n, map(p.intensity,0,255,120,255));
        leds[i] = CHSV(5 + n / 12, 255, bri);
    }
}
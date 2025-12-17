#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_fire(uint32_t now, const EffectParams& p) {
    static uint16_t noiseX = 0;
    static uint16_t noiseY = 0;
    static uint16_t noiseZ = 0;
    static uint32_t last = 0;

    uint16_t interval = map(p.speed, 0, 255, 40, 10);
    if (now - last < interval) return;
    last = now;

    noiseZ += map(p.intensity, 0, 255, 1, 4);
    noiseY += 3;
    noiseX += 1;

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        uint8_t n = inoise8(i * 40 + noiseX, noiseY, noiseZ);
        uint8_t bri = qadd8(n, n / 2);

        leds[i] = CHSV(
            5 + (n / 12),   // красный → жёлтый
            255,
            bri
        );
    }
}
#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_fire_center(uint32_t now, const EffectParams& p) {
    static uint16_t t = 0;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 35, 10)) return;
    last = now;

    t++;

    int center = NUM_LEDS / 2;
    for (int i = 0; i < NUM_LEDS; i++) {
        uint8_t d = abs(i - center);
        uint8_t n = inoise8(i * 30, t * 2);
        uint8_t b = qsub8(n, d * 3);
        leds[i] = CHSV(8 + b / 12, 255, b);
    }
}

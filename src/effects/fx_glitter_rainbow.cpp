#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_glitter_rainbow(uint32_t now, const EffectParams& p) {
    static uint8_t h = 0;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 35, 8)) return;
    last = now;

    h++;

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(h + i * 2, 255, 180);
    }

    if (random8() < map(p.intensity, 0, 255, 10, 60)) {
        leds[random16(NUM_LEDS)] += CRGB::White;
    }
}

#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_rainbow_cycle(uint32_t now, const EffectParams& p) {
    static uint8_t baseHue = 0;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 30, 5)) return;
    last = now;

    baseHue += map(p.intensity, 0, 255, 1, 4);

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(baseHue + (i * 255 / NUM_LEDS), 255, 255);
    }
}
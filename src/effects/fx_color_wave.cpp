#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_color_wave(uint32_t now, const EffectParams& p) {
    static uint8_t phase = 0;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 30, 6)) return;
    last = now;

    phase++;

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        uint8_t b = sin8(i * 6 + phase);
        leds[i] = CHSV(p.color.r, 255, b);
    }
}
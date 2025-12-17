#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_sin_bright_wave(uint32_t now, const EffectParams& p) {
    static uint8_t offset = 0;
    static uint32_t last = 0;

    // скорость волны
    if (now - last < map(p.speed, 0, 255, 30, 5)) return;
    last = now;

    offset += map(p.intensity, 0, 255, 1, 6);

    // переводим базовый цвет из CRGB в CHSV
    CHSV base = rgb2hsv_approximate(p.color);

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        uint8_t b = sin8(i * 8 + offset);
        leds[i] = CHSV(base.h, base.s, b);
    }
}
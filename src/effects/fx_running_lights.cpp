#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_running_lights(uint32_t now, const EffectParams& p) {
    static uint16_t pos = 0;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 30, 5)) return;
    last = now;

    pos++;

    CHSV base = rgb2hsv_approximate(p.color);

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        uint8_t b = sin8(i * 16 + pos);
        leds[i] = CHSV(base.h, base.s, b);
    }
}
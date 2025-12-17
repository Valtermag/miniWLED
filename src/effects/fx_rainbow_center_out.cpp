#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_rainbow_center_out(uint32_t now, const EffectParams& p) {
    static uint8_t hue = 0;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 45, 12)) return;
    last = now;

    hue++;

    int center = NUM_LEDS / 2;
    for (int i = 0; i < NUM_LEDS; i++) {
        uint8_t offset = abs(i - center) * 255 / center;
        leds[i] = CHSV(hue + offset, 255, 255);
    }
}
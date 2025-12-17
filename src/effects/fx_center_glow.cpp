#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_center_glow(uint32_t now, const EffectParams& p) {
    int center = NUM_LEDS / 2;

    for (int i = 0; i < NUM_LEDS; i++) {
        uint8_t d = abs(i - center);
        uint8_t b = qsub8(200, d * 6);
        leds[i] = CHSV(p.color.r, 180, b);
    }
}

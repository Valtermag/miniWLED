#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_pulse_color(uint32_t now, const EffectParams& p) {
    static int8_t dir = 1;
    static uint8_t b = 0;
    static uint32_t last = 0;

    if (now - last < 20) return;
    last = now;

    b += dir * 4;
    if (b >= 255 || b <= 10) dir = -dir;

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        leds[i] = p.color;
        leds[i].fadeToBlackBy(255 - b);
    }
}
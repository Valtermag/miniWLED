#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_color_loop_vardelay(uint32_t now, const EffectParams& p) {
    static uint16_t pos = 0;
    static uint32_t last = 0;

    uint16_t base = map(p.speed, 0, 255, 80, 10);
    uint16_t center = NUM_LEDS / 2;
    uint16_t d = abs((int)pos - (int)center);

    if (now - last < base + d) return;
    last = now;

    fill_solid(leds, NUM_LEDS, p.color);
    pos = (pos + 1) % NUM_LEDS;
}
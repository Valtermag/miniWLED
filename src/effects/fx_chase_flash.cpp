#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_chase_flash(uint32_t now, const EffectParams& p) {
    static int pos = 0;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 60, 8)) return;
    last = now;

    fill_solid(leds, NUM_LEDS, CRGB::Black);
    leds[pos] = p.color;

    if (pos % 10 == 0) {
        fill_solid(leds, NUM_LEDS, p.color);
    }

    pos = (pos + 1) % NUM_LEDS;
}
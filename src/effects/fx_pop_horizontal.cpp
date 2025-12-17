#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_pop_horizontal(uint32_t now, const EffectParams& p) {
    static int pos = 0;
    static bool dir = false;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 60, 10)) return;
    last = now;

    fill_solid(leds, NUM_LEDS, CRGB::Black);

    if (!dir) {
        for (int i = 0; i <= pos && i < NUM_LEDS; i++) leds[i] = p.color;
        pos++;
        if (pos >= NUM_LEDS - 1) dir = true;
    } else {
        for (int i = NUM_LEDS - 1; i >= pos && i >= 0; i--) leds[i] = p.color;
        pos--;
        if (pos <= 0) dir = false;
    }
}
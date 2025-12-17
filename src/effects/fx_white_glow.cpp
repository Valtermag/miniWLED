#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_white_glow(uint32_t now, const EffectParams& p) {
    static int8_t dir = 1;
    static uint8_t b = 20;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 30, 8)) return;
    last = now;

    b += dir * 3;
    if (b <= 20 || b >= 255) dir = -dir;

    fill_solid(leds, NUM_LEDS, CRGB(b, b, b));
}
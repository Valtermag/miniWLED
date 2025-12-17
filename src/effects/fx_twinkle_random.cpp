#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_twinkle_random(uint32_t now, const EffectParams& p) {
    static uint32_t last = 0;
    if (now - last < map(p.speed, 0, 255, 60, 8)) return;
    last = now;

    leds[random16(NUM_LEDS)] = CHSV(random8(), 255, 255);
}

#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_pacman(uint32_t now, const EffectParams& p) {
    static int pos = 0;
    static bool mouth = false;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 120, 20)) return;
    last = now;

    fill_solid(leds, NUM_LEDS, CHSV(64, 255, 40));
    leds[pos] = CHSV(64, 255, 255);

    if (mouth) leds[(pos + 1) % NUM_LEDS] = CRGB::Black;

    pos = (pos + 1) % NUM_LEDS;
    mouth = !mouth;
}
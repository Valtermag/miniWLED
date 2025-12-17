#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_running_dots(uint32_t now, const EffectParams& p) {
    static uint16_t pos = 0;
    pos += map(p.speed,0,255,1,4);

    fill_solid(leds, NUM_LEDS, CRGB::Black);

    for (int i = 0; i < 3; i++) {
        leds[(pos + i * 10) % NUM_LEDS] = p.color;
    }
}
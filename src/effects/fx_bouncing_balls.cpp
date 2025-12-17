#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_bouncing_balls(uint32_t now, const EffectParams& p) {
    const uint8_t BALLS = 3;
    static int pos[BALLS] = { 0, NUM_LEDS / 3, (NUM_LEDS * 2) / 3 };
    static int dir[BALLS] = { 1, 1, 1 };
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 40, 8)) return;
    last = now;

    fill_solid(leds, NUM_LEDS, CRGB::Black);

    for (uint8_t i = 0; i < BALLS; i++) {
        pos[i] += dir[i];
        if (pos[i] <= 0 || pos[i] >= NUM_LEDS - 1) dir[i] = -dir[i];
        leds[pos[i]] = CHSV(p.color.r + i * 40, 255, 255);
    }
}

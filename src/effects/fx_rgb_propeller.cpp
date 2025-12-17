#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_rgb_propeller(uint32_t now, const EffectParams& p) {
    static uint16_t offset = 0;
    static uint32_t last = 0;

    if (now - last < map(p.speed, 0, 255, 40, 6)) return;
    last = now;

    offset++;

    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        uint16_t j = (i + offset) % NUM_LEDS;
        uint8_t section = (uint32_t)i * 3 / NUM_LEDS;
        leds[j] = (section == 0) ? CRGB::Red :
                  (section == 1) ? CRGB::Green :
                                   CRGB::Blue;
    }
}
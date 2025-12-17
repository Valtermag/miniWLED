#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_blackout(uint32_t now, const EffectParams& p) {
    fill_solid(leds, NUM_LEDS, CRGB::Black);
}
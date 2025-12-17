#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_off_soft(uint32_t now, const EffectParams& p) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].fadeToBlackBy(30);
    }
}
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_soft_breath(uint32_t now, const EffectParams& p) {
    float t = now * 0.001f * map(p.speed,0,255,1,6);
    uint8_t b = (sin(t) * 127) + 128;

    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = p.color;
        leds[i].fadeToBlackBy(255 - scale8(b, p.intensity));
    }
}
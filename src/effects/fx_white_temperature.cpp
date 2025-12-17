#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_white_temperature(uint32_t now, const EffectParams& p) {
    for (uint16_t i = 0; i < NUM_LEDS; i++) {
        uint8_t pos = (uint32_t)i * 255 / (NUM_LEDS - 1);

        CRGB c;
        if (pos < 128) {
            float k = pos / 128.0f;
            c.r = 255;
            c.g = 147 + (uint8_t)((255 - 147) * k);
            c.b = 41  + (uint8_t)((255 - 41) * k);
        } else {
            float k = (pos - 128) / 127.0f;
            c.r = 255 - (uint8_t)((255 - 180) * k);
            c.g = 255 - (uint8_t)((255 - 200) * k);
            c.b = 255;
        }
        leds[i] = c;
    }
}
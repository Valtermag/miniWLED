#include <FastLED.h>
#include "Effects.h"
#include <math.h>

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_radiation(uint32_t now, const EffectParams& p) {
    static float t = 0.0f;
    static uint32_t last = 0;

    if (now - last < 20) return;
    last = now;

    t += 0.05f;
    if (t > 6.28318f) t = 0.0f;

    int N3 = NUM_LEDS / 3;
    int N6 = NUM_LEDS / 6;

    CHSV base = rgb2hsv_approximate(p.color);

    for (int i = 0; i < N6; i++) {
        uint8_t b = (sin(t) * 127) + 128;

        int j0 = (i + NUM_LEDS - N6) % NUM_LEDS;
        int j1 = (j0 + N3) % NUM_LEDS;
        int j2 = (j1 + N3) % NUM_LEDS;

        leds[j0] = CHSV(base.h, base.s, b);
        leds[j1] = CHSV(base.h, base.s, b);
        leds[j2] = CHSV(base.h, base.s, b);
    }
}
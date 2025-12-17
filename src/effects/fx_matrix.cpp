#include <FastLED.h>
#include "Effects.h"

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_matrix(uint32_t now, const EffectParams& p) {
    static uint32_t last = 0;

    // скорость "падения" зелёных точек
    uint16_t interval = map(p.speed, 0, 255, 120, 20);
    if (now - last < interval) return;
    last = now;

    // сдвигаем всё вниз (к концу ленты)
    for (int i = NUM_LEDS - 1; i > 0; --i) {
        leds[i] = leds[i - 1];
    }

    // вероятность появления нового "зерна" в начале
    uint8_t chance = map(p.intensity, 0, 255, 20, 140);

    CRGB headColor;
    if (random8() < chance) {
        // зелёный "матричный" цвет
        headColor = CRGB(0, 255, 70);
    } else {
        headColor = CRGB::Black;
    }

    leds[0] = headColor;
}
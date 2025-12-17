#include "Effects.h"
#include <FastLED.h>

extern CRGB leds[];
extern const uint16_t NUM_LEDS;

void fx_warm_center(uint32_t now, const EffectParams& p) {
    static uint16_t radius = 0;
    static uint32_t last = 0;
    static bool finished = false;

    // ---- СБРОС при смене эффекта ----
    static uint8_t lastFx = 255;
    if (lastFx != EffectState::internal.currentEffect) {
        lastFx = EffectState::internal.currentEffect;
        radius = 0;
        finished = false;
        fill_solid(leds, NUM_LEDS, CRGB::Black);
    }

    // ---- Если уже полностью зажглись — держим статичный свет ----
    if (finished) {
        return;
    }

    // ---- Замедляем анимацию ----
    if (now - last < 40) return;   // было быстрее — теперь мягче
    last = now;

    const uint16_t center = NUM_LEDS / 2;

    // Тёплый цвет (≈4000K)
    CRGB warm = CRGB(255, 147, 41);
    if (p.color.r || p.color.g || p.color.b) {
        warm = p.color;
    }

    // ---- ЗАЖИГАНИЕ ОТ ЦЕНТРА К КРАЯМ ----
    if (radius <= center) {
        if (center >= radius)
            leds[center - radius] = warm;

        if (center + radius < NUM_LEDS)
            leds[center + radius] = warm;

        radius++;
    } else {
        // Всё зажглось — фиксируем состояние
        finished = true;
    }
}
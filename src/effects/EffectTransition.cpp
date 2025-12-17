#include "EffectTransition.h"
#include "state/EffectState.h"
#include <FastLED.h>

namespace EffectTransition {

    static bool active = false;
    static uint8_t targetFx = 0;

    static uint8_t step = 0;
    static const uint8_t MAX_STEP = 24; // плавность

    void begin(uint8_t newFx) {
        targetFx = newFx;
        step = 0;
        active = true;
    }

    bool isActive() {
        return active;
    }

    void loop() {
        if (!active) return;

        // FADE OUT
        if (step < MAX_STEP) {
            uint8_t bri = map(step, 0, MAX_STEP, 255, 0);
            FastLED.setBrightness(bri);
            step++;
            return;
        }

        // SWITCH EFFECT
        EffectState::setEffect(targetFx);

        // FADE IN
        for (uint8_t i = 0; i <= MAX_STEP; i++) {
            uint8_t bri = map(
                i,
                0,
                MAX_STEP,
                0,
                EffectState::internal.params.brightness
            );
            FastLED.setBrightness(bri);
            delay(4);
        }

        active = false;
    }
}
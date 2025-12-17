#include "State.h"
#include "LedEngine.h"
#include "EffectEngine.h"
#include <FastLED.h>

namespace State {

    GlobalState state = {
        .on = true,
        .brightness = 128,
        .color = CRGB(255, 255, 255)
    };

    void init() {
        LedEngine::setPower(state.on);
        LedEngine::setBrightness(state.brightness);
        EffectEngine::setColor(state.color);
    }

    void setOn(bool value) {
        state.on = value;
        LedEngine::setPower(value);
    }

    void setBrightness(uint8_t value) {
        state.brightness = value;
        LedEngine::setBrightness(value);
    }

    void setColor(const CRGB& c) {
        state.color = c;
        EffectEngine::setColor(c);
    }

}
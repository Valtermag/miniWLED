#pragma once
#include <Arduino.h>
#include <FastLED.h>

namespace State {

    struct GlobalState {
        bool on;
        uint8_t brightness;
        CRGB color;
    };

    extern GlobalState state;

    void init();
    void setOn(bool value);
    void setBrightness(uint8_t value);
    void setColor(const CRGB& c);

}
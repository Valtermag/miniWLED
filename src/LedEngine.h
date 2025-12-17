#pragma once
#include <Arduino.h>
#include <FastLED.h>
#include "Config.h"

extern uint16_t NUM_LEDS;
extern CRGB leds[];

namespace LedEngine {
    void init();
    void setPower(bool on);
    void setBrightness(uint8_t bri);
}
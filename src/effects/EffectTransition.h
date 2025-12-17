#pragma once
#include <Arduino.h>

namespace EffectTransition {

    void begin(uint8_t newFx);
    void loop();

    bool isActive();
}
#pragma once
#include <Arduino.h>
#include <FastLED.h>

namespace EffectEngine {

    void init();

    void setEffect(uint16_t effectId);
    void setSpeed(uint8_t speed);
    void setIntensity(uint8_t intensity);
    void setBrightness(uint8_t bri);
    //void setColor(const CRGB& c);
    void setColor(const CRGB& color);

    void loop(); // позже сюда войдёт рендер
}
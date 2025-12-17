#pragma once
#include <Arduino.h>
#include <FastLED.h>

// =======================
// Параметры эффекта (CURRENT)
// =======================
struct EffectParams {
    uint8_t brightness;   // 0–255
    uint8_t speed;        // sx
    uint8_t intensity;    // ix
    uint8_t contrast;
    uint8_t palette;
    CRGB    color;
};

// =======================
// ЦЕЛЕВЫЕ параметры (TARGET)
// =======================
struct EffectTargets {
    uint8_t brightness;
    CRGB    color;
};

// =======================
// WLED-совместимое хранилище
// =======================
struct EffectStateData {
    uint8_t effectId;
    uint8_t speed;
    uint8_t intensity;
};

// =======================
// ВНУТРЕННЕЕ состояние (для движка)
// =======================
struct EffectStateInternal {
    uint8_t        currentEffect;
    EffectParams   params;   // ТЕКУЩИЕ (используют эффекты)
    EffectTargets  target;   // ЦЕЛЕВЫЕ (для плавных переходов)
};

// =======================
// EffectState — ХРАНИЛИЩЕ СОСТОЯНИЯ
// =======================
class EffectState {
public:
    // используется WebServer / API
    static EffectStateData effect;

    // используется EffectEngine / Effects
    static EffectStateInternal internal;

    static void init();

    // --- WLED API ---
    static void setEffect(uint8_t id);
    static void setSpeed(uint8_t v);
    static void setIntensity(uint8_t v);

    // --- НОВОЕ: целевые значения ---
    static void setBrightnessTarget(uint8_t v);
    static void setColorTarget(const CRGB& c);

    // --- внутреннее ---
    static void applyBrightness();
};

// Getters (для Web / API)
uint8_t getCurrentEffect();
uint8_t getSpeed();
uint8_t getIntensity();
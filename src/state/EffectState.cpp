#include "EffectState.h"
#include <FastLED.h>

// =======================
// STATIC STORAGE
// =======================
EffectStateData     EffectState::effect;
EffectStateInternal EffectState::internal;

static const CRGB DEFAULT_WARM = CRGB(255, 147, 41);

// =======================
// INIT
// =======================
void EffectState::init() {

    // WLED state
    effect.effectId  = 0;
    effect.speed     = 128;
    effect.intensity = 128;

    // CURRENT
    internal.currentEffect        = 0;
    internal.params.brightness    = 128;
    internal.params.speed         = 128;
    internal.params.intensity     = 128;
    internal.params.contrast      = 128;
    internal.params.palette       = 0;
    internal.params.color         = DEFAULT_WARM;

    // TARGET (сначала совпадает с current)
    internal.target.brightness    = internal.params.brightness;
    internal.target.color         = internal.params.color;

    applyBrightness();
}

// =======================
// WLED API
// =======================
void EffectState::setEffect(uint8_t id) {
    effect.effectId = id;
    internal.currentEffect = id;
}

void EffectState::setSpeed(uint8_t v) {
    effect.speed = v;
    internal.params.speed = v;
}

void EffectState::setIntensity(uint8_t v) {
    effect.intensity = v;
    internal.params.intensity = v;
}

// =======================
// TARGET SETTERS (14.4)
// =======================
void EffectState::setBrightnessTarget(uint8_t v) {
    internal.target.brightness = v;
}

void EffectState::setColorTarget(const CRGB& c) {
    internal.target.color = c;
}

// =======================
// INTERNAL
// =======================
void EffectState::applyBrightness() {
    FastLED.setBrightness(internal.params.brightness);
}

// =======================
// GETTERS
// =======================
uint8_t getCurrentEffect() {
    return EffectState::internal.currentEffect;
}

uint8_t getSpeed() {
    return EffectState::effect.speed;
}

uint8_t getIntensity() {
    return EffectState::effect.intensity;
}

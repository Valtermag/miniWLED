#pragma once

#include <Arduino.h>
#include <FastLED.h>
#include "state/EffectState.h"   // здесь должен быть ЕДИНСТВЕННЫЙ EffectParams

typedef void (*EffectFn)(uint32_t now, const EffectParams& p);

// effect list (таблица функций)
extern EffectFn g_effectList[];
extern const uint16_t G_EFFECT_COUNT;

// управление
void setCurrentEffect(uint8_t id);
void runCurrentEffect();
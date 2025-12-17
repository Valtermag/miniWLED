#include "EffectEngine.h"
#include "state/EffectState.h"

namespace EffectEngine {

    // как часто обновляем сглаживание (мс)
    static uint32_t lastTick = 0;
    static const uint16_t TICK_MS = 15;

    // шаг яркости за тик (1..6 — подберём позже)
    static const uint8_t BRI_STEP = 2;

    // шаг “приближения” цвета (0..255), меньше = плавнее
    static const uint8_t COLOR_BLEND = 18;

    void init() {
        // пока ничего
    }

    void setEffect(uint16_t effectId) {
        EffectState::setEffect((uint8_t)effectId);
    }

    void setSpeed(uint8_t speed) {
        EffectState::setSpeed(speed);
        // speed остаётся мгновенным (плавность можно позже)
    }

    void setIntensity(uint8_t intensity) {
        EffectState::setIntensity(intensity);
        // intensity остаётся мгновенным (плавность можно позже)
    }

    // 14.4: brightness меняем как TARGET
    void setBrightness(uint8_t bri) {
        EffectState::setBrightnessTarget(bri);
    }

    // 14.4: color меняем как TARGET
    void setColor(const CRGB& c) {
        EffectState::setColorTarget(c);
    }

    void loop() {
        uint32_t now = millis();
        if (now - lastTick < TICK_MS) return;
        lastTick = now;

        // --- плавная яркость ---
        uint8_t curB = EffectState::internal.params.brightness;
        uint8_t trgB = EffectState::internal.target.brightness;

        if (curB != trgB) {
            if (curB < trgB) {
                uint8_t nb = curB + BRI_STEP;
                if (nb < curB || nb > trgB) nb = trgB;
                EffectState::internal.params.brightness = nb;
            } else {
                uint8_t nb = (curB > BRI_STEP) ? (curB - BRI_STEP) : 0;
                if (nb > curB || nb < trgB) nb = trgB;
                EffectState::internal.params.brightness = nb;
            }
            EffectState::applyBrightness();
        }

        // --- плавный цвет ---
        CRGB &curC = EffectState::internal.params.color;
        const CRGB &trgC = EffectState::internal.target.color;

        if (curC != trgC) {
            // nblend: плавно подтягивает curC к trgC
            nblend(curC, trgC, COLOR_BLEND);
        }
    }
}
#include <Arduino.h>

#include "Config.h"
#include "WebServer.h"
#include "LedEngine.h"
#include "state/State.h"
#include "state/EffectState.h"
#include "EffectEngine.h"
#include "effects/Effects.h"

void setup() {
    Serial.begin(115200);
    delay(300);

    // БАЗОВАЯ ИНФРАСТРУКТУРА
    Config::init();
    LedEngine::init();
    State::init();

    // ШАГ 12 — параметры эффектов
    EffectState::init();
    setCurrentEffect(0);

    // ДВИЖКИ
    EffectEngine::init();

    // WEB / API
    HttpServer::init();

    Serial.println("[MAIN] Setup complete");
}

void loop() {
    // Инфраструктура
    Config::loop();
    HttpServer::loop();

    // Логика эффектов (таймеры, смена состояний)
    EffectEngine::loop();

    // Рендер
    if (State::state.on) {
        runCurrentEffect();
    } else {
        LedEngine::setPower(false);
    }
}
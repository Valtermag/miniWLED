#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include "WebServer.h"

#include <ArduinoJson.h>
#include <LittleFS.h>

#include "state/State.h"
#include "state/EffectState.h"

#include "effects/Effects.h"
#include "LedEngine.h"
#include "EffectEngine.h"

// ----------------------------
//  ГЛОБАЛЬНЫЙ СЕРВЕР
// ----------------------------
ESP8266WebServer server(80);

// ----------------------------
//  CALLBACK WiFiManager
// ----------------------------
void configModeCallback(WiFiManager *wm) {
    Serial.println("=== CONFIG PORTAL MODE ===");
    Serial.print("AP SSID: ");
    Serial.println(wm->getConfigPortalSSID());
}

// ----------------------------
//       ИНИЦИАЛИЗАЦИЯ
// ----------------------------
void HttpServer::init() {
    Serial.println("HttpServer::init()");

    // -------- WiFi ----------
    WiFiManager wm;
    wm.setAPCallback(configModeCallback);
    wm.setConfigPortalTimeout(300);

    bool res = wm.autoConnect("mini-WLED-SETUP", "12345678");
    if (!res) {
        Serial.println("[WiFi] Failed to connect. Rebooting...");
        delay(3000);
        ESP.restart();
    }

    Serial.println("[WiFi] Connected!");
    Serial.print("[WiFi] IP: ");
    Serial.println(WiFi.localIP());

    // -------- FS -----------
    if (!LittleFS.begin()) {
        Serial.println("[FS] LittleFS mount FAILED");
    } else {
        Serial.println("[FS] LittleFS mounted");
    }

    // ============================
    // BASIC ENDPOINTS
    // ============================
    server.on("/ping", HTTP_GET, []() {
        server.send(200, "application/json", "{\"status\":\"ok\"}");
    });

    server.on("/state", HTTP_GET, []() {
        server.send(200, "application/json", "{\"state\":\"placeholder\"}");
    });

    server.on("/effect", HTTP_GET, []() {
        server.send(200, "application/json", "{\"effects\":\"coming soon\"}");
    });

    // ============================
    // WLED API — /json/info
    // ============================
    server.on("/json/info", HTTP_GET, []() {
        String json = "{";
        json += "\"ver\":\"miniWLED-1.0\",";
        json += "\"name\":\"miniWLED\",";
        json += "\"udpport\":21324,";
        json += "\"live\":false,";
        json += "\"fxcount\":" + String(G_EFFECT_COUNT) + ",";
        json += "\"palcount\":1,";
        json += "\"arch\":\"ESP8266\",";
        json += "\"leds\":{";
            json += "\"count\":" + String(NUM_LEDS) + ",";
            json += "\"rgbw\":false";
        json += "}";
        json += "}";

        server.send(200, "application/json", json);
    });

    // ============================
    // WLED API — /json/effects
    // (ПОКА FX 0..N — ИМЕНА ПОЗЖЕ)
    // ============================
    // server.on("/json/effects", HTTP_GET, []() {
    //     String json = "[";
    //     for (uint16_t i = 0; i < G_EFFECT_COUNT; i++) {
    //         json += "\"FX " + String(i) + "\"";
    //         if (i < G_EFFECT_COUNT - 1) json += ",";
    //     }
    //     json += "]";
    //     server.send(200, "application/json", json);
    // });
    server.on("/json/effects", HTTP_GET, []() {
        String json = "[";
        for (uint16_t i = 0; i < G_EFFECT_COUNT; i++) {
            json += "\"";
            json += g_effectNames[i];
            json += "\"";
            if (i < G_EFFECT_COUNT - 1) json += ",";
        }
        json += "]";
        server.send(200, "application/json", json);
    });
    // ============================
    // WLED API — /json/pal
    // ============================
    server.on("/json/pal", HTTP_GET, []() {
        server.send(200, "application/json", "[\"Default\"]");
    });

    // ============================
    // WLED API — GET /json/state
    // ============================
    server.on("/json/state", HTTP_GET, []() {
        const CRGB& c = State::state.color;

        String json = "{";
        json += "\"on\":" + String(State::state.on ? "true" : "false") + ",";
        json += "\"bri\":" + String(State::state.brightness) + ",";
        json += "\"fx\":" + String(getCurrentEffect()) + ",";
        json += "\"sx\":" + String(getSpeed()) + ",";
        json += "\"ix\":" + String(getIntensity()) + ",";
        json += "\"seg\":[{";
            json += "\"id\":0,";
            json += "\"fx\":" + String(getCurrentEffect()) + ",";
            json += "\"col\":[[" +
                    String(c.r) + "," +
                    String(c.g) + "," +
                    String(c.b) + "]]";
        json += "}]";
        json += "}";

        server.send(200, "application/json", json);
    });

    // ============================
    // WLED API — POST /json/state
    // ============================
    server.on("/json/state", HTTP_POST, []() {

        if (!server.hasArg("plain")) {
            server.send(400, "application/json", "{\"error\":\"no body\"}");
            return;
        }

        StaticJsonDocument<512> doc;
        if (deserializeJson(doc, server.arg("plain"))) {
            server.send(400, "application/json", "{\"error\":\"bad json\"}");
            return;
        }

        if (doc.containsKey("on")) {
            State::setOn(doc["on"]);
        }

        if (doc.containsKey("bri")) {
            State::setBrightness(doc["bri"]);
        }

        if (doc.containsKey("fx")) {
            EffectState::setEffect(doc["fx"]);
        }

        if (doc.containsKey("sx")) {
            EffectState::setSpeed(doc["sx"]);
        }

        if (doc.containsKey("ix")) {
            EffectState::setIntensity(doc["ix"]);
        }

        if (doc.containsKey("seg")) {
            JsonArray seg = doc["seg"];
            if (!seg.isNull() && seg.size() > 0) {
                JsonArray col = seg[0]["col"];
                if (!col.isNull() && col.size() > 0) {
                    JsonArray rgb = col[0];
                    if (rgb.size() >= 3) {
                        State::setColor(
                            CRGB(rgb[0], rgb[1], rgb[2])
                        );
                    }
                }
            }
        }

        server.send(200, "application/json", "{\"success\":true}");
    });

    // ============================
    // WEB UI
    // ============================
    server.on("/", HTTP_GET, []() {
        server.sendHeader("Location", "/index.html", true);
        server.send(302, "text/plain", "");
    });

    server.serveStatic("/", LittleFS, "/");

    server.begin();
    Serial.println("[HTTP] Web server started");
}

// ----------------------------
// LOOP
// ----------------------------
void HttpServer::loop() {
    server.handleClient();
}
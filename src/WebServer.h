#pragma once
#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

namespace HttpServer {
    void init();
    void loop();
}
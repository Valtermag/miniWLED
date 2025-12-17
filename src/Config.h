#pragma once

// ================= LED CONFIG =================
#define LED_PIN     D4
#define LED_COUNT   140
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB


namespace Config {
  void init();
  void loop();
}
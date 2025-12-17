#include "LedEngine.h"

uint16_t NUM_LEDS = LED_COUNT;
CRGB leds[LED_COUNT];

namespace LedEngine {
    static bool power = true;

    void init() {
        FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, LED_COUNT);
        FastLED.setBrightness(128);
        fill_solid(leds, LED_COUNT, CRGB::Black);
        FastLED.show();
    }

    void setPower(bool on) {
        power = on;
        if (!on) {
            FastLED.clear();
            FastLED.show();
        }
    }

    void setBrightness(uint8_t bri) {
        FastLED.setBrightness(bri);
        if (power) FastLED.show();
    }
}
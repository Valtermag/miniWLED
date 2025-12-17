#include "Effects.h"
#include <FastLED.h>
#include "state/EffectState.h"

// ======================================================
// DECLARATIONS (СТРОГО ПО ТВОЕМУ СПИСКУ)
// ======================================================
void fx_ambient_warm(uint32_t, const EffectParams&);
void fx_aurora(uint32_t, const EffectParams&);
void fx_blackout(uint32_t, const EffectParams&);
void fx_bouncing_balls(uint32_t, const EffectParams&);
void fx_bouncing_colored_balls(uint32_t, const EffectParams&);
void fx_center_glow(uint32_t, const EffectParams&);
void fx_center_pulse(uint32_t, const EffectParams&);
void fx_center_wave_warm(uint32_t, const EffectParams&);
void fx_chase(uint32_t, const EffectParams&);
void fx_chase_flash(uint32_t, const EffectParams&);
void fx_chase_rainbow(uint32_t, const EffectParams&);
void fx_cold_static(uint32_t, const EffectParams&);
void fx_color_bounce(uint32_t, const EffectParams&);
void fx_color_loop_vardelay(uint32_t, const EffectParams&);
void fx_color_twinkle(uint32_t, const EffectParams&);
void fx_color_wave(uint32_t, const EffectParams&);
void fx_cylon_bounce(uint32_t, const EffectParams&);
void fx_ems_all(uint32_t, const EffectParams&);
void fx_ems_one(uint32_t, const EffectParams&);
void fx_ems_strobe(uint32_t, const EffectParams&);
void fx_fire(uint32_t, const EffectParams&);
void fx_fire_dense(uint32_t, const EffectParams&);
void fx_fire_slow(uint32_t, const EffectParams&);
void fx_fire_soft(uint32_t, const EffectParams&);
void fx_flicker(uint32_t, const EffectParams&);
void fx_glitter_rainbow(uint32_t, const EffectParams&);
void fx_kitt(uint32_t, const EffectParams&);
void fx_matrix(uint32_t, const EffectParams&);
void fx_new_kitt(uint32_t, const EffectParams&);
void fx_off_soft(uint32_t, const EffectParams&);
void fx_pacman(uint32_t, const EffectParams&);
void fx_plasma_center(uint32_t, const EffectParams&);
void fx_plasma_soft(uint32_t, const EffectParams&);
void fx_pop_horizontal(uint32_t, const EffectParams&);
void fx_pulse_color(uint32_t, const EffectParams&);
void fx_quad_bright_curve(uint32_t, const EffectParams&);
void fx_radiation(uint32_t, const EffectParams&);
void fx_rainbow_center_out(uint32_t, const EffectParams&);
void fx_rainbow_cycle(uint32_t, const EffectParams&);
void fx_rainbow_fade(uint32_t, const EffectParams&);
void fx_rainbow_loop(uint32_t, const EffectParams&);
void fx_rainbow_soft(uint32_t, const EffectParams&);
void fx_rainbow_vertical(uint32_t, const EffectParams&);
void fx_random_burst(uint32_t, const EffectParams&);
void fx_random_color_pop(uint32_t, const EffectParams&);
void fx_random_march(uint32_t, const EffectParams&);
void fx_rgb_propeller(uint32_t, const EffectParams&);
void fx_running_dots(uint32_t, const EffectParams&);
void fx_running_lights(uint32_t, const EffectParams&);
void fx_rwb_march(uint32_t, const EffectParams&);
void fx_sin_bright_wave(uint32_t, const EffectParams&);
void fx_slow_rainbow_breath(uint32_t, const EffectParams&);
void fx_snow_sparkle(uint32_t, const EffectParams&);
void fx_soft_color_noise(uint32_t, const EffectParams&);
void fx_soft_fade_color(uint32_t, const EffectParams&);
void fx_soft_gradient(uint32_t, const EffectParams&);
void fx_sparkle(uint32_t, const EffectParams&);
void fx_sparkle_white(uint32_t, const EffectParams&);
void fx_static_warm(uint32_t, const EffectParams&);
void fx_strip_march_ccw(uint32_t, const EffectParams&);
void fx_strip_march_cw(uint32_t, const EffectParams&);
void fx_strobe(uint32_t, const EffectParams&);
void fx_theater_chase_soft(uint32_t, const EffectParams&);
void fx_twinkle_random(uint32_t, const EffectParams&);
void fx_warm_breath(uint32_t, const EffectParams&);
void fx_warm_center(uint32_t, const EffectParams&);
void fx_warm_static(uint32_t, const EffectParams&);
void fx_white_glow(uint32_t, const EffectParams&);
void fx_white_temperature(uint32_t, const EffectParams&);

// ======================================================
// EFFECT TABLE
// ======================================================
EffectFn g_effectList[] = {
    fx_warm_center,
    fx_ambient_warm,
    fx_warm_static,
    fx_warm_breath,
    fx_fire,
    fx_fire_soft,
    fx_fire_slow,
    fx_fire_dense,
    fx_matrix,
    fx_rainbow_fade,
    fx_rainbow_loop,
    fx_rainbow_cycle,
    fx_rainbow_soft,
    fx_rainbow_vertical,
    fx_rainbow_center_out,
    fx_color_wave,
    fx_color_bounce,
    fx_color_twinkle,
    fx_color_loop_vardelay,
    fx_chase,
    fx_chase_flash,
    fx_chase_rainbow,
    fx_cylon_bounce,
    fx_kitt,
    fx_new_kitt,
    fx_bouncing_balls,
    fx_bouncing_colored_balls,
    fx_rgb_propeller,
    fx_plasma_center,
    fx_plasma_soft,
    fx_radiation,
    fx_quad_bright_curve,
    fx_sin_bright_wave,
    fx_random_burst,
    fx_random_color_pop,
    fx_random_march,
    fx_running_dots,
    fx_running_lights,
    fx_rwb_march,
    fx_strip_march_ccw,
    fx_strip_march_cw,
    fx_flicker,
    fx_glitter_rainbow,
    fx_sparkle,
    fx_sparkle_white,
    fx_twinkle_random,
    fx_snow_sparkle,
    fx_ems_one,
    fx_ems_all,
    fx_ems_strobe,
    fx_strobe,
    fx_off_soft,
    fx_white_glow,
    fx_white_temperature,
    fx_cold_static
};

const uint16_t G_EFFECT_COUNT =
    sizeof(g_effectList) / sizeof(g_effectList[0]);

// ======================================================
// EFFECT CONTROL
// ======================================================
void setCurrentEffect(uint8_t id) {
    if (id >= G_EFFECT_COUNT) id = 0;
    EffectState::setEffect(id);
}

void runCurrentEffect() {
    uint32_t now = millis();
    EffectFn fn = g_effectList[EffectState::internal.currentEffect];
    fn(now, EffectState::internal.params);
    FastLED.show();
}
#include "coramoor.h"
#include "features/rgb_matrix_custom.h"
#include "definitions/layers.h"
#ifdef SMART_CASE_ENABLE
    #include "features/smart_case.h"
#endif
#ifdef CUSTOM_LEADER_ENABLE
    #include "features/leader.h"
#endif

extern led_config_t g_led_config;

__attribute__((weak)) bool rgb_matrix_indicators_keymap(void) { return true; }
__attribute__((weak)) bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) {
    return true;
}

void rgb_matrix_set_custom_indicators(uint8_t led_min, uint8_t led_max, int led_type, uint16_t hue, uint8_t sat, uint8_t val) {
        val = rgb_matrix_get_val();
        for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
            HSV hsv = {
                .h = hue,
                .s = sat,
                .v = val,
            };
                if (HAS_ANY_FLAGS(g_led_config.flags[i], led_type)) {
                    RGB rgb = hsv_to_rgb(hsv);
                    RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
               }
        }
}

//
void set_layer_rgb_matrix(uint16_t hue, uint8_t sat, uint8_t val, uint8_t led_min, uint8_t led_max) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }

    RGB rgb       = hsv_to_rgb(hsv);
    // rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        switch (rgb_matrix_get_flags()) {
            case LED_FLAG_ALL:
            case LED_FLAG_UNDERGLOW:
                if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
                    RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
                }
                break;
        }
    }
}

void rgb_custom_thumb_indicators(uint16_t hue, uint8_t sat, uint8_t val) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }

    RGB rgb       = hsv_to_rgb(hsv);
        rgb_matrix_set_color(11, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(42, rgb.r, rgb.g, rgb.b);
}

bool rgb_matrix_indicators_user(void) { rgb_matrix_indicators_keymap(); return true; }

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if (!rgb_matrix_indicators_advanced_keymap(led_min, led_max)) {
            return false;
        }

#ifdef RGB_MATRIX_CUSTOM_ENABLED

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _FUNCTION:
            set_layer_rgb_matrix(FUNCTION_UNDERGLOW, led_min, led_max);
            break;
        case _HEX:
            set_layer_rgb_matrix(HEX_UNDERGLOW, led_min, led_max);
            break;
        default:
            set_layer_rgb_matrix(rgb_matrix_get_hue(), rgb_matrix_get_sat(), rgb_matrix_get_val(), led_min, led_max);

 #endif
            break;
    }

    return false;
}

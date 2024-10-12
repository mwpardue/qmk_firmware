#include "coramoor.h"
#include "features/rgb_matrix_custom.h"
#include "definitions/layers.h"
#ifdef SMART_CASE_ENABLE
    #include "features/smart_case.h"
#endif
#ifdef CASEMODE_ENABLE
    #include "features/casemodes.h"
    extern enum xcase_state xcase_state;
    extern bool caps_word_on;
#endif
#ifdef CAPS_WORD_ENABLE
    #include "features/caps_word.h"
#endif

#ifdef CUSTOM_LEADER_ENABLE
    #include "features/leader.h"
#endif

#ifdef DYNAMIC_MACRO_ENABLE
    extern bool is_dynamic_recording;
#endif

extern led_config_t g_led_config;

uint8_t rgb_matrix_get_heatmap_spread(void) {
    return user_config.rgb_matrix_heatmap_spread;
}

uint8_t rgb_matrix_get_heatmap_area_limit(void) {
    return user_config.rgb_matrix_heatmap_area;
}

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
		    // rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
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
        rgb_matrix_set_color(12, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(43, rgb.r, rgb.g, rgb.b);
}

bool rgb_matrix_indicators_user(void) { rgb_matrix_indicators_keymap(); return true; }

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    bool isOneShotShift = get_oneshot_mods() & MOD_MASK_SHIFT || get_oneshot_locked_mods() & MOD_MASK_SHIFT;
    bool isShift = get_mods() & MOD_MASK_SHIFT;
    bool isOneShotCtrl = get_oneshot_mods() & MOD_MASK_CTRL || get_oneshot_locked_mods() & MOD_MASK_CTRL;

    if (!rgb_matrix_indicators_advanced_keymap(led_min, led_max)) {
            return false;
        }

#ifdef RGB_MATRIX_CUSTOM_ENABLED

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _NUMPAD:
            set_layer_rgb_matrix(NUMPAD_UNDERGLOW, led_min, led_max);
            break;
        case _NAVIGATION:
            set_layer_rgb_matrix(NAVIGATION_UNDERGLOW, led_min, led_max);
            break;
        case _SYMBOL:
            set_layer_rgb_matrix(SYMBOL_UNDERGLOW, led_min, led_max);
            break;
        case _VIM:
            set_layer_rgb_matrix(VIM_UNDERGLOW, led_min, led_max);
            break;
        case _FUNCTION:
            set_layer_rgb_matrix(FUNCTION_UNDERGLOW, led_min, led_max);
            break;
        case _APPSWITCH:
            set_layer_rgb_matrix(APPSWITCH_UNDERGLOW, led_min, led_max);
            break;
        case _COLEMAK_DH:
            set_layer_rgb_matrix(COLEMAK_DH_UNDERGLOW, led_min, led_max);
            break;
        case _HEX:
            set_layer_rgb_matrix(HEX_UNDERGLOW, led_min, led_max);
            break;
        case _GAMING:
                set_layer_rgb_matrix(GAMING_UNDERGLOW, led_min, led_max);
            break;
        case _GAMENUM:
            if (is_keyboard_master()) {
                set_layer_rgb_matrix(GAMING_UNDERGLOW, led_min, led_max);
            } else {
                set_layer_rgb_matrix(0, 0, 0, led_min, led_max);
            }
            break;
        default:
            set_layer_rgb_matrix(rgb_matrix_get_hue(), rgb_matrix_get_sat(), rgb_matrix_get_val(), led_min, led_max);

            switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL:
                case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR):
                    #ifdef CASEMODE_ENABLE
                         if ((xcase_state == XCASE_ON) && (host_keyboard_led_state().caps_lock)) {
                                    rgb_custom_thumb_indicators(XCASE_ON_STRONG_INDICATOR);
                        } else if ((xcase_state == XCASE_WAIT) && (host_keyboard_led_state().caps_lock)) {
                                    rgb_custom_thumb_indicators(XCASE_WAIT_STRONG_INDICATOR);
                        } else if ((xcase_state == XCASE_WAIT)) {
                                    rgb_custom_thumb_indicators(XCASE_WAIT_INDICATOR);
                        } else if ((xcase_state == XCASE_ON)) {
                                    rgb_custom_thumb_indicators(XCASE_ON_INDICATOR);
                        } else if (host_keyboard_led_state().caps_lock) {
                                    rgb_custom_thumb_indicators(CAPS_LOCK_INDICATOR);
                        } else if (isOneShotShift || isShift) {
                                    rgb_custom_thumb_indicators(SHIFT_INDICATOR);
                        } else if (isOneShotCtrl) {
                                    rgb_custom_thumb_indicators(CTRL_INDICATOR);
                        }
                    #endif

                    #endif
                }
            break;
    }
    #ifdef DYNAMIC_MACRO_ENABLE
        if (is_dynamic_recording) {
            rgb_matrix_set_custom_indicators(led_min, led_max, LED_FLAG_KEYLIGHT, HSV_RED);
        }
    #endif

    #ifdef CUSTOM_LEADER_ENABLE
        if (is_leading()) {
            rgb_matrix_set_custom_indicators(led_min, led_max, LED_FLAG_KEYLIGHT, HSV_RED);
    }
    #endif

    return false;
}

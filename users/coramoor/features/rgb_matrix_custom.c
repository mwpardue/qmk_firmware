
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

void rgb_matrix_set_custom_indicators(uint8_t led_min, uint8_t led_max, int led_type, uint8_t hue, uint8_t sat, uint8_t val) {
    if ((get_highest_layer(layer_state | default_layer_state)) == _BASE) {
        uint8_t val = rgb_matrix_get_val();
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
}

//
void set_layer_rgb_matrix(uint8_t hue, uint8_t sat, uint8_t val, uint8_t led_min, uint8_t led_max) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }

    RGB rgb       = hsv_to_rgb(hsv);
    rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
            RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

bool rgb_matrix_indicators_user(void) { rgb_matrix_indicators_keymap(); return true; }

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

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
        case _MACROS:
            set_layer_rgb_matrix(MACROS_UNDERGLOW, led_min, led_max);
            break;
        case _FUNCTION:
            set_layer_rgb_matrix(FUNCTION_UNDERGLOW, led_min, led_max);
            break;
        case _MEDIA:
            set_layer_rgb_matrix(MEDIA_UNDERGLOW, led_min, led_max);
            break;
        case _COLEMAK_DH:
            set_layer_rgb_matrix(COLEMAK_DH_UNDERGLOW, led_min, led_max);
            break;
        case _HEX:
            set_layer_rgb_matrix(HEX_UNDERGLOW, led_min, led_max);
            break;
        default:
            set_layer_rgb_matrix(BASE_UNDERGLOW, led_min, led_max);
            #ifdef CASEMODE_ENABLE
                 if ((xcase_state == XCASE_ON) && (host_keyboard_led_state().caps_lock)) {
                            rgb_matrix_set_custom_indicators(led_min, led_max, LED_FLAG_KEYLIGHT, HSV_PURPLE);
                } else if ((xcase_state == XCASE_WAIT) && (host_keyboard_led_state().caps_lock)) {
                            rgb_matrix_set_custom_indicators(led_min, led_max, LED_FLAG_KEYLIGHT, HSV_ORANGE);
                } else if ((xcase_state == XCASE_WAIT)) {
                            rgb_matrix_set_custom_indicators(led_min, led_max, LED_FLAG_KEYLIGHT, HSV_YELLOW);
                } else if ((xcase_state == XCASE_ON)) {
                            rgb_matrix_set_custom_indicators(led_min, led_max, LED_FLAG_KEYLIGHT, HSV_BLUE);
                } else if (host_keyboard_led_state().caps_lock) {
                            rgb_matrix_set_custom_indicators(led_min, led_max, LED_FLAG_KEYLIGHT, HSV_RED);
                }
            #endif

            bool isHyper = get_mods() & (MOD_BIT(KC_LCTL) && get_mods() & MOD_BIT(KC_LSFT) && get_mods() & MOD_BIT(KC_LALT) && get_mods() & MOD_BIT(KC_LGUI));
            bool isOneShotHyper = get_oneshot_mods() & (MOD_BIT(KC_LCTL) && get_oneshot_mods() & MOD_BIT(KC_LSFT) && get_oneshot_mods() & MOD_BIT(KC_LALT) && get_oneshot_mods() & MOD_BIT(KC_LGUI));
            bool isMeh = get_mods() & (MOD_BIT(KC_LCTL) && get_mods() & MOD_BIT(KC_LSFT) && get_mods() & MOD_BIT(KC_LALT));
            bool isOneShotMeh = get_oneshot_mods() & (MOD_BIT(KC_LCTL) && get_oneshot_mods() & MOD_BIT(KC_LSFT) && get_oneshot_mods() & MOD_BIT(KC_LALT));

                if (isHyper||isOneShotHyper) {
                    rgb_matrix_set_custom_indicators(led_min, led_max, LED_FLAG_MODIFIER, HSV_BLUE);
                } else if (isMeh||isOneShotMeh) {
                    rgb_matrix_set_custom_indicators(led_min, led_max, LED_FLAG_MODIFIER, HSV_YELLOW);
                } else if ((get_mods()|get_oneshot_mods()) & MOD_MASK_SHIFT) {
                    rgb_matrix_set_custom_indicators(led_min, led_max, LED_FLAG_MODIFIER, HSV_RED);
                } else if ((get_mods()|get_oneshot_mods()) & MOD_MASK_GUI) {
                    rgb_matrix_set_custom_indicators(led_min, led_max, LED_FLAG_MODIFIER, HSV_GREEN);
                } else if ((get_mods()|get_oneshot_mods()) & MOD_MASK_ALT) {
                    rgb_matrix_set_custom_indicators(led_min, led_max, LED_FLAG_MODIFIER, HSV_ORANGE);
                } else if ((get_mods()|get_oneshot_mods()) & MOD_MASK_CTRL) {
                    rgb_matrix_set_custom_indicators(led_min, led_max, LED_FLAG_MODIFIER, HSV_TURQUOISE);
                }
#endif
            break;
    }
    return false;
}

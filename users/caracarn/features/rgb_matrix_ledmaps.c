#include "caracarn.h"
#include "features/rgb_matrix_ledmaps.h"
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

bool ledmap_active;

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
		    rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
                if (HAS_ANY_FLAGS(g_led_config.flags[i], led_type)) {
                    RGB rgb = hsv_to_rgb(hsv);
                    RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
               }
        }
    }
}

#ifdef RGB_MATRIX_LEDMAPS_ENABLED

static bool enabled = true;

#endif  // RGB_MATRIX_LEDMAPS_ENABLED

bool rgb_matrix_indicators_user(void) { rgb_matrix_indicators_keymap(); return true; }
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
#ifdef RGB_MATRIX_LEDMAPS_ENABLED
    if (rgb_matrix_is_enabled() && enabled) {
        switch (rgb_matrix_get_flags()) {
            case LED_FLAG_ALL: {
                set_layer_rgb_matrix(led_min, led_max, get_highest_layer(layer_state | default_layer_state), (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR | LED_FLAG_UNDERGLOW));
            }
            break;
            case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                set_layer_rgb_matrix(led_min, led_max, get_highest_layer(layer_state | default_layer_state), (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR));
            }
            break;
            case LED_FLAG_UNDERGLOW: {
                set_layer_rgb_matrix(led_min, led_max, get_highest_layer(layer_state | default_layer_state), (LED_FLAG_UNDERGLOW));
            }
            break;
            default: {
                set_layer_rgb_matrix(led_min, led_max, get_highest_layer(layer_state | default_layer_state), (LED_FLAG_NONE));
            }
            break;
        }
    }

#endif  // RGB_MATRIX_LEDMAPS_ENABLED
    rgb_matrix_indicators_advanced_keymap(led_min, led_max);
  return true;
}

void rgb_matrix_base_underglow(void) {

}

#ifdef RGB_MATRIX_LEDMAPS_ENABLED

void set_layer_rgb_matrix(uint8_t led_min, uint8_t led_max, int layer, int led_type) {
    const ledmap *l = &(ledmaps[layer]);
    uint8_t val = rgb_matrix_get_val();
        for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
            if (!user_config.rgb_matrix_ledmap_active) {
                HSV hsv = {
                    .h = (*l)[0][0],
                    .s = (*l)[0][1],
                    .v = val,
                };
			    rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
              // if ((get_highest_layer(layer_state | default_layer_state)) != _BASE && (get_highest_layer(layer_state | default_layer_state)) != _ADJUST && (get_highest_layer(layer_state | default_layer_state)) != _COLEMAK_DH ) {
                if (HAS_ANY_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
                    RGB rgb = hsv_to_rgb(hsv);
                    RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
                }
              // }
            } else {
                HSV hsv = {
                    .h = (*l)[i][0],
                    .s = (*l)[i][1],
                    .v = val,
            };
                if (hsv.h || hsv.s) {
                    RGB rgb = hsv_to_rgb(hsv);
                    if (HAS_ANY_FLAGS(g_led_config.flags[i], led_type)) {
                        RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
                    }
                } else {
                    if ((get_highest_layer(layer_state | default_layer_state)) != _BASE && (get_highest_layer(layer_state | default_layer_state)) != _ADJUST && (get_highest_layer(layer_state | default_layer_state)) != _COLEMAK_DH ) {
                        if (HAS_ANY_FLAGS(g_led_config.flags[i], led_type)) {
                            RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 0);
                            }
                        }
                    }
            }
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
              if (HAS_ANY_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
                rgb_matrix_set_color(i, RGB_BLUE);
              }
            } else if (isMeh||isOneShotMeh) {
              if (HAS_ANY_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
                rgb_matrix_set_color(i, RGB_YELLOW);
              }
            } else if ((get_mods()|get_oneshot_mods()) & MOD_MASK_SHIFT) {
              if (HAS_ANY_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
                rgb_matrix_set_color(i, RGB_RED);
              }
            } else if ((get_mods()|get_oneshot_mods()) & MOD_MASK_GUI) {
              if (HAS_ANY_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
                rgb_matrix_set_color(i, RGB_GREEN);
              }
            } else if ((get_mods()|get_oneshot_mods()) & MOD_MASK_ALT) {
              if (HAS_ANY_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
                rgb_matrix_set_color(i, RGB_ORANGE);
              }
            } else if ((get_mods()|get_oneshot_mods()) & MOD_MASK_CTRL) {
              if (HAS_ANY_FLAGS(g_led_config.flags[i], LED_FLAG_MODIFIER)) {
                rgb_matrix_set_color(i, RGB_TURQUOISE);
              }
            }
        // }
    }
}

void rgb_matrix_layers_enable() {
    dprintf("ledmaps are enabled\n");
    enabled = true;
}

void rgb_matrix_layers_disable() {
    dprintf("ledmaps are disabled\n");
    enabled = false;
}

#endif  // RGB_MATRIX_LEDMAPS_ENABLED

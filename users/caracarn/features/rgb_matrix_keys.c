#include QMK_KEYBOARD_H

#include "rgb_matrix_keys.h"
#include "caracarn.h"
#include "rgb_matrix.h"

extern bool ledmap_active;

// static void heatmap_spread_report(void) {
//     const char *heatmap_spread_str = get_u16_str(user_config.rgb_matrix_heatmap_spread, ' ');
//     // Skip padding spaces
//     while (*heatmap_spread_str == ' ') {
//         heatmap_spread_str++;
//     }
//     send_string(heatmap_spread_str);
// }

// static void heatmap_area_report(void) {
//     const char *heatmap_area_str = get_u16_str(user_config.rgb_matrix_heatmap_area, ' ');
//     // Skip padding spaces
//     while (*heatmap_area_str == ' ') {
//         heatmap_area_str++;
//     }
//     send_string(heatmap_area_str);
// }

process_record_result_t process_rgb_matrix_keys(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_CHG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                    rgb_matrix_set_color_all(0, 0, 0);
                    dprintf("rgb_matrix_get_flags (KMI)= %d\n", rgb_matrix_get_flags());
                  }
                  break;
                case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                    dprintf("rgb_matrix_get_flags (UG)= %d\n", rgb_matrix_get_flags());
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                    dprintf("rgb_matrix_get_flags (OFF)= %d\n", rgb_matrix_get_flags());
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                    dprintf("rgb_matrix_get_flags (ALL)= %d\n", rgb_matrix_get_flags());
                  }
                  break;
              }
              return PROCESS_RECORD_RETURN_FALSE;
            }

        case RGB_SPP:
            if (record->event.pressed) {
                // rgb_matrix_typing_heatmap_spread = rgb_matrix_typing_heatmap_spread + 1;
                // user_config.rgb_matrix_heatmap_spread = rgb_matrix_typing_heatmap_spread;
                user_config.rgb_matrix_heatmap_spread = user_config.rgb_matrix_heatmap_spread + 1;
                eeconfig_update_user(user_config.raw);
                dprintf("Heatmap Spread(+) = %d\n", user_config.rgb_matrix_heatmap_spread);
                // heatmap_spread_report();
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;

        case RGB_SPM:
            if (record->event.pressed) {
                // rgb_matrix_typing_heatmap_spread = rgb_matrix_typing_heatmap_spread - 1;
                // user_config.rgb_matrix_heatmap_spread = rgb_matrix_typing_heatmap_spread;
                user_config.rgb_matrix_heatmap_spread = user_config.rgb_matrix_heatmap_spread - 1;
                eeconfig_update_user(user_config.raw);
                dprintf("Heatmap Spread(-) = %d\n", user_config.rgb_matrix_heatmap_spread);
                // heatmap_spread_report();
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;

        case RGB_ALP:
            if (record->event.pressed) {
                // rgb_matrix_typing_heatmap_area_limit = rgb_matrix_typing_heatmap_area_limit + 1;
                // user_config.rgb_matrix_heatmap_area = rgb_matrix_typing_heatmap_area_limit;
                user_config.rgb_matrix_heatmap_area = user_config.rgb_matrix_heatmap_area + 1;
                eeconfig_update_user(user_config.raw);
                dprintf("Heatmap Area Limit(+) = %d\n", user_config.rgb_matrix_heatmap_area);
                // heatmap_area_report();
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;

        case RGB_ALM:
            if (record->event.pressed) {
                // rgb_matrix_typing_heatmap_area_limit = rgb_matrix_typing_heatmap_area_limit - 1;
                // user_config.rgb_matrix_heatmap_area = rgb_matrix_typing_heatmap_area_limit;
                user_config.rgb_matrix_heatmap_area = user_config.rgb_matrix_heatmap_area - 1;
                eeconfig_update_user(user_config.raw);
                dprintf("Heatmap Area Limit(-) = %d\n", user_config.rgb_matrix_heatmap_area);
                // heatmap_area_report();
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;

        case RGB_MDT:
            if (record->event.pressed) {
                user_config.rgb_matrix_ledmap_active ^= 1;
                eeconfig_update_user(user_config.rgb_matrix_ledmap_active);
            }
            break;
  }
    return PROCESS_RECORD_CONTINUE; // Process all other keycodes normally
}

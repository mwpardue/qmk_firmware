#include QMK_KEYBOARD_H

#include "coramoor.h"

bool check_menu(uint8_t menu_item) {
    if (user_config.rgb_menu_selector == menu_item) {
        return true;
    } else {
        return false;
    }
}

uint8_t viewport_begin(void) {
    if (user_config.rgb_menu_selector <= 3) {
        return 1;
    } else if (user_config.rgb_menu_selector >= (MENU_MAX - 3)) {
        return (MENU_MAX - VIEWPORT_HEIGHT);
    } else {
        return (user_config.rgb_menu_selector - 3);
    }
}

void menu_items(void) {
char rgb_matrix_speed_str[8];
char rgb_matrix_hue_str[8];
char rgb_matrix_sat_str[8];
char rgb_matrix_val_str[8];
uint8_t mode_length = strlen(rmodes[rgb_matrix_get_mode()]);
    oled_write_P(PSTR(" Kyria Configuration "), false);
    for (uint8_t i = viewport_begin(); i <= (viewport_begin() + 6); i++) {
        switch(i) {
            case MENU_FLAGS:
                oled_write_P(PSTR("LED FLAGS:"), check_menu(MENU_FLAGS));
                    switch (rgb_matrix_get_flags()) {
                        case LED_FLAG_ALL: {
                            oled_write_P(PSTR("        ALL"), check_menu(MENU_FLAGS));
                        }
                        break;
                        case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                            oled_write_P(PSTR("        KMI"), check_menu(MENU_FLAGS));
                        }
                        break;
                        case LED_FLAG_UNDERGLOW: {
                            oled_write_P(PSTR("  UNDERGLOW"), check_menu(MENU_FLAGS));
                        }
                        break;
                        default: {
                            oled_write_P(PSTR("       NONE"), check_menu(MENU_FLAGS));
                        }
                        break;
                    }
                    break;
            case MENU_SPEED:
                sprintf(rgb_matrix_speed_str, "%03d", rgb_matrix_get_speed());
                oled_write_P(PSTR("RGB SPEED:        "), check_menu(MENU_SPEED));
                oled_write_P(rgb_matrix_speed_str, check_menu(MENU_SPEED));
                break;
            case MENU_HUE:
                sprintf(rgb_matrix_hue_str, "%03d", rgb_matrix_get_hue());
                oled_write_P(PSTR("RGB HUE:          "), check_menu(MENU_HUE));
                oled_write_P(rgb_matrix_hue_str, check_menu(MENU_HUE));
                break;
            case MENU_SAT:
                sprintf(rgb_matrix_sat_str, "%03d", rgb_matrix_get_sat());
                oled_write_P(PSTR("RGB SATURATION:   "), check_menu(MENU_SAT));
                oled_write_P(rgb_matrix_sat_str, check_menu(MENU_SAT));
                break;
            case MENU_VAL:
                sprintf(rgb_matrix_val_str, "%03d", rgb_matrix_get_val());
                oled_write_P(PSTR("RGB VALUE:        "), check_menu(MENU_VAL));
                oled_write_P(rgb_matrix_val_str, check_menu(MENU_VAL));
                break;
            case MENU_RGBMODE:
                oled_write_P(PSTR("MODE: "), check_menu(MENU_RGBMODE));
                uint8_t space_length = (VIEWPORT_WIDTH - 6) - mode_length;
                for (uint8_t i = 1; i <= space_length; i++) {
                    oled_write_P(PSTR(" "), check_menu(MENU_RGBMODE));
                }
                oled_write_P(rmodes[rgb_matrix_get_mode()], check_menu(MENU_RGBMODE));
                break;
            case MENU_OSFLAG:
                oled_write_P(PSTR("CURRENT OS:"), check_menu(MENU_OSFLAG));
                switch (user_config.os) {
                case WINDOWS:
                    oled_write_P(PSTR("   WINDOWS"), check_menu(MENU_OSFLAG));
                    break;
                case LINUX:
                    oled_write_P(PSTR("     LINUX"), check_menu(MENU_OSFLAG));
                    break;
                default:
                    oled_write_P(PSTR("     MACOS"), check_menu(MENU_OSFLAG));
                    break;
                }
                break;
            case MENU_DEBUG:
                if (kb_state.debug_enabled) {
                oled_write_P(PSTR("DEBUG STATUS:      ON"), check_menu(MENU_DEBUG));
                } else {
                oled_write_P(PSTR("DEBUG STATUS:     OFF"), check_menu(MENU_DEBUG));
                }
                break;
            case MENU_EECLEAR:
                oled_write_P(PSTR("         CLEAR EEPROM"), check_menu(MENU_EECLEAR));
                break;
            default:
            break;
        }
    }
}

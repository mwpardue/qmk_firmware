#include QMK_KEYBOARD_H

#include "coramoor.h"

extern uint16_t sft_tapping_term;

extern uint16_t modtap_tapping_term;

extern uint16_t achordion_tapping_term;

extern uint16_t gqt_tapping_term;

extern uint16_t sgqt_tapping_term;

// GENERAL MENU FUNCTIONS

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

// HEATMAP SECTION
uint8_t get_heatmap_area(void) {
    return user_config.rgb_matrix_heatmap_area;
}

uint8_t get_heatmap_spread(void) {
    return user_config.rgb_matrix_heatmap_spread;
}

char heatmap_area_str[8];
char heatmap_spread_str[8];

// TAPPING TERM SECTION
uint16_t get_shift_tapping_term_str(void) {
    return sft_tapping_term;
}

uint16_t get_tapping_term_str(void) {
    return g_tapping_term;
}

uint16_t get_modtap_tapping_term_str(void) {
    return modtap_tapping_term;
}

uint16_t get_achordion_tapping_term_str(void) {
    return achordion_tapping_term;
}

uint16_t get_gqt_tapping_term_str(void) {
    return gqt_tapping_term;
}

uint16_t get_sgqt_tapping_term_str(void) {
    return sgqt_tapping_term;
}

char shift_tapping_term_str[16];
char g_tapping_term_str[16];
char modtap_tapping_term_str[16];
char achordion_tapping_term_str[16];
char gqt_tapping_term_str[16];
char sgqt_tapping_term_str[16];

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
            case MENU_HMAREA:
                sprintf(heatmap_area_str, "%03d", get_heatmap_area());
                oled_write_P(PSTR("HEATMAP AREA:     "), check_menu(MENU_HMAREA));
                oled_write_P(heatmap_area_str, check_menu(MENU_HMAREA));
                break;
            case MENU_HMSPREAD:
                sprintf(heatmap_spread_str, "%03d", get_heatmap_spread());
                oled_write_P(PSTR("HEATMAP SPREAD:   "), check_menu(MENU_HMSPREAD));
                oled_write_P(heatmap_spread_str, check_menu(MENU_HMSPREAD));
                break;
            case MENU_STT:
                sprintf(shift_tapping_term_str, "%03d", get_shift_tapping_term_str());
                oled_write_P(PSTR("SHIFT TAP TERM:   "), check_menu(MENU_STT));
                oled_write_P(shift_tapping_term_str, check_menu(MENU_STT));
                break;
            case MENU_TT:
                sprintf(g_tapping_term_str, "%03d", get_tapping_term_str());
                oled_write_P(PSTR("TAPPING TERM:     "), check_menu(MENU_TT));
                oled_write_P(g_tapping_term_str, check_menu(MENU_TT));
                break;
            case MENU_MT:
                sprintf(modtap_tapping_term_str, "%03d", get_modtap_tapping_term_str());
                oled_write_P(PSTR("MOD TAP TERM:     "), check_menu(MENU_MT));
                oled_write_P(modtap_tapping_term_str, check_menu(MENU_MT));
                break;
            case MENU_AT:
                sprintf(achordion_tapping_term_str, "%03d", get_achordion_tapping_term_str());
                oled_write_P(PSTR("ACH TAP TERM:     "), check_menu(MENU_AT));
                oled_write_P(achordion_tapping_term_str, check_menu(MENU_AT));
                break;
            case MENU_GQT:
                sprintf(gqt_tapping_term_str, "%03d", get_gqt_tapping_term_str());
                oled_write_P(PSTR("GQT TAP TERM:     "), check_menu(MENU_GQT));
                oled_write_P(gqt_tapping_term_str, check_menu(MENU_GQT));
                break;
            case MENU_SGQT:
                sprintf(sgqt_tapping_term_str, "%03d", get_sgqt_tapping_term_str());
                oled_write_P(PSTR("SGQT TAP TERM:    "), check_menu(MENU_SGQT));
                oled_write_P(sgqt_tapping_term_str, check_menu(MENU_SGQT));
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

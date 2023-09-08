#pragma once
// #include "features/os_toggle.h"

extern uint32_t transport_user_state;

extern uint16_t sft_tapping_term;

extern uint16_t modtap_tapping_term;

extern uint16_t achordion_tapping_term;

extern uint16_t gqt_tapping_term;

extern uint16_t sgqt_tapping_term;

extern layer_state_t locked_layers;

// extern rgb_menu_selector_t rgb_menu_selector;

// extern os_t os;

// bool check_menu(uint8_t menu_item) {
//     if (user_config.rgb_menu_selector == menu_item) {
//         return true;
//     } else {
//         return false;
//     }
// }

bool check_lock(void) {
    if (locked_layers) {
        return true;
    } else {
        return false;
    }
}

// uint8_t viewport_begin(void) {
//     if (user_config.rgb_menu_selector <= 3) {
//         return 1;
//     } else if (user_config.rgb_menu_selector >= (RGBM_MAX - 3)) {
//         return (RGBM_MAX - VIEWPORT_HEIGHT);
//     } else {
//         return (user_config.rgb_menu_selector - 3);
//     }
// }

#ifdef CASEMODE_ENABLE
    extern enum xcase_state xcase_state;
    extern bool caps_word_on;
#endif

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

void render_led_flags(void);
void render_matrix_mode(void);
void render_rgb_speed(void);
void render_rgb_hue(void);
void render_stt_specs(void);
void render_tt_specs(void);
void render_mt_specs(void);
void render_at_specs(void);

void render_newline(void) {
    oled_write_P(PSTR("\n"), false);
}

void render_blank_line(void) {
    oled_write_P(PSTR("                     "), false);
}

void render_mod_status_gui_alt_1(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

}

void render_mod_status_gui_alt_2(uint8_t modifiers) {
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift_1(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }
}

void render_mod_status_ctrl_shift_2(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_logo1(void) {
    static const char PROGMEM mac_logo1[] = {
        0x80,0x81,0x82,0x83,0x84,0};
    static const char PROGMEM win_logo1[] = {
        0x80,0x97,0x98,0x99,0x9a,0};
    static const char PROGMEM linux_logo1[] = {
        0x80,0x9b,0x9c,0x9d,0x9e,0};
    switch (user_config.os) {
        case WINDOWS:
            oled_write_P(win_logo1, false);
            break;
        case LINUX:
            oled_write_P(linux_logo1, false);
            break;
        default:
            oled_write_P(mac_logo1, false);
            break;
    }
}

void render_logo2(void) {
    static const char PROGMEM mac_logo2[] = {
        0xa0,0xa1,0xa2,0xa3,0xa4,0};
    static const char PROGMEM win_logo2[] = {
        0xa0,0xb7,0xb8,0xb9,0xba,0};
    static const char PROGMEM linux_logo2[] = {
        0xa0,0xbb,0xbc,0xbd,0xbe,0};
    switch (user_config.os) {
        case WINDOWS:
            oled_write_P(win_logo2, false);
            break;
        case LINUX:
            oled_write_P(linux_logo2, false);
            break;
        default:
            oled_write_P(mac_logo2, false);
            break;
    }
}

void render_logo3(void) {
    static const char PROGMEM mac_logo3[] = {
        0xc0,0xc1,0xc2,0xc3,0xc4,0};
    static const char PROGMEM win_logo3[] = {
        0xc0,0xd7,0xd8,0xd9,0xda,0};
    static const char PROGMEM linux_logo3[] = {
        0xc0,0xdb,0xdc,0xdd,0xde,0};
    switch (user_config.os) {
        case WINDOWS:
            oled_write_P(win_logo3, false);
            break;
        case LINUX:
            oled_write_P(linux_logo3, false);
            break;
        default:
            oled_write_P(mac_logo3, false);
            break;
    }
}

void render_logo_slave(void) {
    static const char PROGMEM mod_spacer[] = {
        0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0};
    static const char PROGMEM logo1_spacer[] = {
        0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0};
    oled_write_P(mod_spacer, false);
    render_mod_status_gui_alt_1(get_mods()|get_oneshot_mods());
    render_logo1();
    oled_write_P(logo1_spacer, false);
    render_mod_status_gui_alt_2(get_mods()|get_oneshot_mods());
    render_logo2();
    oled_write_P(PSTR(" Kyria     "), false);
    render_mod_status_ctrl_shift_1(get_mods()|get_oneshot_mods());
    render_logo3();
    oled_write_P(PSTR(" rev3.1    "), false);
    render_mod_status_ctrl_shift_2(get_mods()|get_oneshot_mods());
}

void render_logo_master(void) {
    static const char PROGMEM mod_spacer[] = {
        0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0};
    static const char PROGMEM logo1_spacer[] = {
        0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0};
    render_mod_status_gui_alt_1(get_mods()|get_oneshot_mods());
    oled_write_P(mod_spacer, false);
    render_mod_status_gui_alt_2(get_mods()|get_oneshot_mods());
    oled_write_P(logo1_spacer,false);
    render_logo1();
    render_mod_status_ctrl_shift_1(get_mods()|get_oneshot_mods());
    oled_write_P(PSTR("      Kyria"), false);
    render_logo2();
    render_mod_status_ctrl_shift_2(get_mods()|get_oneshot_mods());
    oled_write_P(PSTR("     rev3.1"), false);
    render_logo3();
}

void render_layer_state(void) {
        // Host Keyboard Layer Status
    static const char PROGMEM layer_box_top[] = {
        0x80,0x80,0x80,0x80,0x94,0x95,0x95,0x95,0x95,0x95,0x95,0x95,0x95,0x95,0x95,0x96, 0};
    static const char PROGMEM layer_box_bottom[] = {
        0x80,0x80,0x80,0x80,0xd4,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd6, 0};
    static const char PROGMEM layer_box_left[] = {
        0x80,0x80,0x80,0x80,0xb4, 0};
    static const char PROGMEM layer_box_right[] = {
        0xb6, 0};
    static const char PROGMEM locked_layer_box_top[] = {
        0x80,0x80,0x80,0x80,0x93,0xd2,0xd2,0xd2,0xd2,0xd2,0xd2,0xd2,0xd2,0xd2,0xd2,0x9f, 0};
    static const char PROGMEM locked_layer_box_left[] = {
        0x80,0x80,0x80,0x80,0xb3, 0};
    static const char PROGMEM locked_layer_box_right[] = {
        0xbf, 0};
    static const char PROGMEM locked_layer_box_bottom[] = {
        0x80,0x80,0x80,0x80,0xd3,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xd1,0xdf, 0};
    if (locked_layers) {
        oled_write_P(locked_layer_box_top, false);
        render_newline();
        oled_write_P(locked_layer_box_left, false);
    } else {
        oled_write_P(layer_box_top, false);
        render_newline();
        oled_write_P(layer_box_left, false);
    }
    switch (get_highest_layer(layer_state|default_layer_state)) {
        case _BASE:
            oled_write_P(PSTR("  QWERTY  "), check_lock());
            break;
        case _COLEMAK_DH:
            oled_write_P(PSTR("COLEMAK-DH"), check_lock());
            break;
        case _NAVIGATION:
            oled_write_P(PSTR("NAVIGATION"), check_lock());
            break;
        case _SYMBOL:
            oled_write_P(PSTR("  SYMBOL  "), check_lock());
            break;
        case _FUNCTION:
            oled_write_P(PSTR(" FUNCTION "), check_lock());
            break;
        case _ADJUST:
            oled_write_P(PSTR("  ADJUST  "), check_lock());
            break;
        case _NUMPAD:
            oled_write_P(PSTR("  NUMPAD  "), check_lock());
            break;
        case _MACROS:
            oled_write_P(PSTR("  MACROS  "), check_lock());
            break;
        case _HEX:
            oled_write_P(PSTR("   HEX    "), check_lock());
            break;
        case _MEDIA:
            oled_write_P(PSTR("  MEDIA   "), check_lock());
            break;
        case _GAMING:
            oled_write_P(PSTR("  GAMING  "), check_lock());
            break;
        case _GAMENUM:
            oled_write_P(PSTR(" GAMENUM  "), check_lock());
            break;
        default:
            oled_write_P(PSTR("UNDEFINED "), check_lock());
    }
    if (locked_layers) {
        oled_write_P(locked_layer_box_right, false);
        render_newline();
        oled_write_P(locked_layer_box_bottom, false);
        render_newline();
    } else {
        oled_write_P(layer_box_right, false);
        render_newline();
        oled_write_P(layer_box_bottom, false);
        render_newline();
    }
}

void render_led_state_main(void) {
        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();

        oled_write_P(PSTR("          "), false);
        if ((led_usb_state.caps_lock) && (xcase_state == XCASE_ON)) {
            oled_write_P(PSTR("   XCASE   "), false);
        } else if (xcase_state == XCASE_ON) {
            oled_write_P(PSTR("   xcase   "), false);
        } else if ((led_usb_state.caps_lock) && (xcase_state == XCASE_WAIT)) {
            oled_write_P(PSTR("   XWAIT   "), false);
        } else if (xcase_state == XCASE_WAIT) {
            oled_write_P(PSTR("   xwait   "), false);
        } else if (caps_word_on) {
            oled_write_P(PSTR(" CAPSWORD  "), false);
        } else if (led_usb_state.num_lock) {
            oled_write_P(PSTR(" NUMLOCK   "), false);
        } else if (led_usb_state.caps_lock) {
            oled_write_P(PSTR(" CAPSLOCK  "), false);
        } else {
            oled_write_P(PSTR("           "), false);
        }
}

void render_led_state_slave(void) {
        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();

        if ((led_usb_state.caps_lock) && (xcase_state == XCASE_ON)) {
            oled_write_P(PSTR("   XCASE   "), false);
        } else if (xcase_state == XCASE_ON) {
            oled_write_P(PSTR("   xcase   "), false);
        } else if ((led_usb_state.caps_lock) && (xcase_state == XCASE_WAIT)) {
            oled_write_P(PSTR("   XWAIT   "), false);
        } else if (xcase_state == XCASE_WAIT) {
            oled_write_P(PSTR("   xwait   "), false);
        } else if (caps_word_on) {
            oled_write_P(PSTR(" CAPSWORD  "), false);
        } else if (led_usb_state.num_lock) {
            oled_write_P(PSTR(" NUMLOCK   "), false);
        } else if (led_usb_state.caps_lock) {
            oled_write_P(PSTR(" CAPSLOCK  "), false);
        } else {
            oled_write_P(PSTR("           "), false);
        }
        oled_write_P(PSTR("          "), false);
}

// char rgb_matrix_mode_str[8];
// char rgb_matrix_speed_str[8];
// char rgb_matrix_val_str[8];
// char rgb_matrix_hue_str[8];
// char rgb_matrix_sat_str[8];

// void render_led_flags(void) {
//     oled_write_P(PSTR("LED FLAGS:"), check_menu(RGBM_FLG));
//         switch (rgb_matrix_get_flags()) {
//             case LED_FLAG_ALL: {
//                 oled_write_P(PSTR("        ALL"), check_menu(RGBM_FLG));
//             }
//             break;
//             case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
//                 oled_write_P(PSTR("        KMI"), check_menu(RGBM_FLG));
//             }
//             break;
//             case LED_FLAG_UNDERGLOW: {
//                 oled_write_P(PSTR("  UNDERGLOW"), check_menu(RGBM_FLG));
//             }
//             break;
//             default: {
//                 oled_write_P(PSTR("       NONE"), check_menu(RGBM_FLG));
//             }
//             break;
//         }
// }

// void render_matrix_mode(void) {
//     uint8_t mode_length = strlen(rmodes[rgb_matrix_get_mode()]);
//     oled_write_P(PSTR("MODE: "), check_menu(RGBM_MOD));
//     uint8_t space_length = (VIEWPORT_WIDTH - 6) - mode_length;
//     for (uint8_t i = 1; i <= space_length; i++) {
//         oled_write_P(PSTR(" "), check_menu(RGBM_MOD));
//     }
//     oled_write_P(rmodes[rgb_matrix_get_mode()], check_menu(RGBM_MOD));
// }

// void render_rgb_speed(void) {
//     sprintf(rgb_matrix_speed_str, "%03d", rgb_matrix_get_speed());
//     oled_write_P(PSTR("RGB SPEED:        "), check_menu(RGBM_SPD));
//     oled_write_P(rgb_matrix_speed_str, check_menu(RGBM_SPD));
// }

// void render_rgb_hue(void) {
//     sprintf(rgb_matrix_hue_str, "%03d", rgb_matrix_get_hue());
//     oled_write_P(PSTR("RGB HUE:          "), check_menu(RGBM_HUE));
//     oled_write_P(rgb_matrix_hue_str, check_menu(RGBM_HUE));
// }

// void render_rgb_sat(void) {
//     sprintf(rgb_matrix_sat_str, "%03d", rgb_matrix_get_sat());
//     oled_write_P(PSTR("RGB SATURATION:   "), check_menu(RGBM_SAT));
//     oled_write_P(rgb_matrix_sat_str, check_menu(RGBM_SAT));
// }

// void render_rgb_value(void) {
//     sprintf(rgb_matrix_val_str, "%03d", rgb_matrix_get_val());
//     oled_write_P(PSTR("RGB VALUE:        "), check_menu(RGBM_VAL));
//     oled_write_P(rgb_matrix_val_str, check_menu(RGBM_VAL));
// }

uint8_t get_heatmap_area(void) {
    return user_config.rgb_matrix_heatmap_area;
}

uint8_t get_heatmap_spread(void) {
    return user_config.rgb_matrix_heatmap_spread;
}

char heatmap_area_str[8];
char heatmap_spread_str[8];

void render_heatmap_specs(void) {
    sprintf(heatmap_area_str, "%03d", get_heatmap_area());
    sprintf(heatmap_spread_str, "%03d", get_heatmap_spread());
    // oled_write_P(PSTR("            AREA: "), false);
    oled_write_P(PSTR("              "), false);
    oled_write_P(heatmap_area_str, false);
    oled_write_P(PSTR("/"), false);
    // oled_write_P(PSTR("          SPREAD: "), false);
    oled_write_P(heatmap_spread_str, false);
    oled_write_P(PSTR(""), false);
    }

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

void render_stt_specs(void) {
  sprintf(shift_tapping_term_str, "%03d", get_shift_tapping_term_str());
  oled_write_P(PSTR("        STT: "), false);
  oled_write_P(shift_tapping_term_str, false);
}

void render_tt_specs(void) {
  sprintf(g_tapping_term_str, "%03d", get_tapping_term_str());
  oled_write_P(PSTR("        GTT: "), false);
  oled_write_P(g_tapping_term_str, false);
}

void render_mt_specs(void) {
  sprintf(modtap_tapping_term_str, "%03d", get_modtap_tapping_term_str());
  oled_write_P(PSTR("        MTT: "), false);
  oled_write_P(modtap_tapping_term_str, false);
}

void render_at_specs(void) {
  sprintf(achordion_tapping_term_str, "%03d", get_achordion_tapping_term_str());
  oled_write_P(PSTR("             ATT: "), false);
  oled_write_P(achordion_tapping_term_str, false);
}

void render_gqt_specs(void) {
  sprintf(gqt_tapping_term_str, "%03d", get_gqt_tapping_term_str());
  oled_write_P(PSTR("             GQT: "), false);
  oled_write_P(gqt_tapping_term_str, false);
}

void render_sgqt_specs(void) {
  sprintf(sgqt_tapping_term_str, "%03d", get_sgqt_tapping_term_str());
  oled_write_P(PSTR("            SGQT: "), false);
  oled_write_P(sgqt_tapping_term_str, false);
}

// void render_os(void) {
//     oled_write_P(PSTR("CURRENT OS:"), check_menu(OLED_OS));
//     switch (user_config.os) {
//     case WINDOWS:
//         oled_write_P(PSTR("   WINDOWS"), check_menu(OLED_OS));
//         break;
//     case LINUX:
//         oled_write_P(PSTR("     LINUX"), check_menu(OLED_OS));
//         break;
//     default:
//         oled_write_P(PSTR("     MACOS"), check_menu(OLED_OS));
//         break;
//     }
// }

// void render_eeprom_clear(void) {
//     oled_write_P(PSTR("         CLEAR EEPROM"), check_menu(OLED_EEC));
// }

// void render_debug(void) {
//     if (kb_state.debug_enabled) {
//     oled_write_P(PSTR("DEBUG STATUS:      ON"), check_menu(OLED_DBG));
//     } else {
//     oled_write_P(PSTR("DEBUG STATUS:     OFF"), check_menu(OLED_DBG));
//     }
// }

// void render_menu_header(void) {
//     oled_write_P(PSTR(" Kyria Configuration "), false);
// }

// void render_begin(void) {
// }
//
// void render_max(void) {
// }

// void (*menuView[])(void) = {
//         render_begin,
//         render_led_flags,
//         render_rgb_speed,
//         render_rgb_hue,
//         render_rgb_sat,
//         render_rgb_value,
//         render_matrix_mode,
//         render_os,
//         render_debug,
//         render_eeprom_clear,
//         render_max
//     };

void render_menu(void) {
    menu_items();
    // for (uint8_t i = viewport_begin(); i <= (viewport_begin() + 6); i++) {
    //      menuView[i]();
    // }
}

bool oled_task_user(void) {
    if (get_highest_layer(layer_state | default_layer_state) == _ADJUST) {
            // render_menu_header();
            render_menu();
    } else {
        if (is_keyboard_master()) {
            render_logo_master();
            render_layer_state();
            render_led_state_main();
        } else {
            render_logo_slave();
            render_layer_state();
            render_led_state_slave();
        }
    }
    return false;
}


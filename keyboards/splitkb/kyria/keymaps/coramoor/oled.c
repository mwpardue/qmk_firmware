#pragma once
// #include "features/os_toggle.h"

extern uint32_t transport_user_state;

extern uint16_t sft_tapping_term;

extern uint16_t modtap_tapping_term;

extern uint16_t achordion_tapping_term;

extern layer_state_t locked_layers;

// extern os_t os;

#ifdef CASEMODE_ENABLE
    extern enum xcase_state xcase_state;
    extern bool caps_word_on;
#endif

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

void render_led_flags(void);
void render_matrix_mode(void);
void render_rgb_speed(void);

void render_newline(void) {
    oled_write_P(PSTR("\n"), false);
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

void render_single_space(void) {
    static const char PROGMEM single_space[] = {
        0x80,0};
    oled_write_P(single_space, false);
}


// void render_qmk_logo_version_mods(void) {
// // QMK Logo and version information
// // clang-format off
//     static const char PROGMEM mod_spacer[] = {
//         0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0};
//     static const char PROGMEM qmk_logo1[] = {
//         0x80,0x81,0x82,0x83,0x84,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0};
//     static const char PROGMEM qmk_logo2[] = {
//         0xa0,0xa1,0xa2,0xa3,0xa4,0x80,0};
//     static const char PROGMEM qmk_logo3[] = {
//         0xc0,0xc1,0xc2,0xc3,0xc4,0x80,0};
//     oled_write_P(mod_spacer, false);
//     render_mod_status_gui_alt_1(get_mods()|get_oneshot_mods());
//     oled_write_P(qmk_logo1, false);
//     render_mod_status_gui_alt_2(get_mods()|get_oneshot_mods());
//     oled_write_P(qmk_logo2, false);
//     oled_write_P(PSTR("Kyria     "), false);
//     render_mod_status_ctrl_shift_1(get_mods()|get_oneshot_mods());
//     oled_write_P(qmk_logo3, false);
//     oled_write_P(PSTR("rev3.1    "), false);
//     render_mod_status_ctrl_shift_2(get_mods()|get_oneshot_mods());
// }

void render_logo_short(void) {
    render_newline();
    render_logo1();
    render_single_space();
    render_led_flags();
    render_logo2();
    render_single_space();
    render_matrix_mode();
    render_logo3();
    render_single_space();
    render_rgb_speed();
}

// void render_qmk_logo_version_short(void) {
// // QMK Logo and version information
// // clang-format off
//     static const char PROGMEM qmk_logo1_short[] = {
//         0x80,0x81,0x82,0x83,0x84,0x80,0};
//     static const char PROGMEM qmk_logo2_short[] = {
//         0xa0,0xa1,0xa2,0xa3,0xa4,0x80,0};
//     static const char PROGMEM qmk_logo3_short[] = {
//         0xc0,0xc1,0xc2,0xc3,0xc4,0x80,0};
//     render_newline();
//     oled_write_P(qmk_logo1_short, false);
//     render_led_flags();
//     oled_write_P(qmk_logo2_short, false);
//     render_matrix_mode();
//     oled_write_P(qmk_logo3_short, false);
//     render_rgb_speed();
// }

void render_layer_box_top(void) {
    static const char PROGMEM layer_box_top[] = {
        0x80,0x80,0x80,0x80,0x94,0x95,0x95,0x95,0x95,0x95,0x95,0x95,0x95,0x95,0x95,0x96, 0};
    oled_write_P(layer_box_top, false);
    render_newline();
}

void render_layer_box_bottom(void) {
    static const char PROGMEM layer_box_bottom[] = {
        0x80,0x80,0x80,0x80,0xd4,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd5,0xd6, 0};
    oled_write_P(layer_box_bottom, false);
    render_newline();
}

void render_layer_state(void) {
        // Host Keyboard Layer Status
        static const char PROGMEM layer_box_left[] = {
            0x80,0x80,0x80,0x80,0xb4, 0};
        static const char PROGMEM layer_box_right[] = {
            0xb6, 0};
        oled_write_P(layer_box_left, false);
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _BASE:
                oled_write_P(PSTR("  QWERTY  "), false);
                break;
            case _COLEMAK_DH:
                oled_write_P(PSTR("COLEMAK-DH"), false);
                break;
            case _NAVIGATION:
                oled_write_P(PSTR("NAVIGATION"), false);
                break;
            case _SYMBOL:
                oled_write_P(PSTR("  SYMBOL  "), false);
                break;
            case _FUNCTION:
                oled_write_P(PSTR(" FUNCTION "), false);
                break;
            case _ADJUST:
                oled_write_P(PSTR("  ADJUST  "), false);
                break;
            case _NUMPAD:
                oled_write_P(PSTR("  NUMPAD  "), false);
                break;
            case _MACROS:
                oled_write_P(PSTR("  MACROS  "), false);
                break;
            case _HEX:
                oled_write_P(PSTR("   HEX    "), false);
                break;
            case _MEDIA:
                oled_write_P(PSTR("  MEDIA   "), false);
                break;
            default:
                oled_write_P(PSTR("UNDEFINED "), false);
        }
        oled_write_P(layer_box_right, false);
        render_newline();
}

void render_led_state_main(void) {
        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();

        if (locked_layers) {
            oled_write_P(PSTR("  LOCKED  "), false);
        } else {
            oled_write_P(PSTR("          "), false);
        }

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

        if (locked_layers) {
            oled_write_P(PSTR("  LOCKED  "), false);
        } else {
            oled_write_P(PSTR("          "), false);
        }
}

char rgb_matrix_mode_str[8];
char rgb_matrix_speed_str[8];
char rgb_matrix_val_str[8];
char rgb_matrix_hue_str[8];
char rgb_matrix_sat_str[8];

void render_led_flags(void) {
    oled_write_P(PSTR("       FLG:"), false);
        switch (rgb_matrix_get_flags()) {
            case LED_FLAG_ALL: {
                oled_write_P(PSTR(" ALL"), false);
            }
            break;
            case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                oled_write_P(PSTR(" KMI"), false);
            }
            break;
            case LED_FLAG_UNDERGLOW: {
                oled_write_P(PSTR(" UG "), false);
            }
            break;
            default: {
                oled_write_P(PSTR(" OFF"), false);
            }
            break;
        }
}

void render_matrix_mode(void) {
    sprintf(rgb_matrix_mode_str, "%03d", rgb_matrix_get_mode());
    oled_write_P(PSTR("       MOD: "), false);
    oled_write_P(rgb_matrix_mode_str, false);
}

void render_rgb_speed(void) {
    sprintf(rgb_matrix_speed_str, "%03d", rgb_matrix_get_speed());
    oled_write_P(PSTR("       SPD: "), false);
    oled_write_P(rgb_matrix_speed_str, false);
}

void render_rgb_hue(void) {
    sprintf(rgb_matrix_hue_str, "%03d", rgb_matrix_get_hue());
    oled_write_P(PSTR("             HUE: "), false);
    oled_write_P(rgb_matrix_hue_str, false);
}

void render_rgb_sat(void) {
    sprintf(rgb_matrix_sat_str, "%03d", rgb_matrix_get_sat());
    oled_write_P(PSTR("             SAT: "), false);
    oled_write_P(rgb_matrix_sat_str, false);
}

void render_rgb_value(void) {
    sprintf(rgb_matrix_val_str, "%03d", rgb_matrix_get_val());
    oled_write_P(PSTR("             VAL: "), false);
    oled_write_P(rgb_matrix_val_str, false);
}

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


bool oled_task_user(void) {
    if (get_highest_layer(layer_state | default_layer_state) == _ADJUST) {
        render_logo_short();
        render_rgb_hue();
        render_rgb_sat();
        render_rgb_value();
        render_heatmap_specs();
    } else {
        if (is_keyboard_master()) {
            // render_qmk_logo_version_mods();
            render_logo_master();
            render_layer_box_top();
            render_layer_state();
            render_layer_box_bottom();
            render_led_state_main();
        } else {
            render_logo_slave();
            render_layer_box_top();
            render_layer_state();
            render_layer_box_bottom();
            render_led_state_slave();
        }
    }
    return false;
}


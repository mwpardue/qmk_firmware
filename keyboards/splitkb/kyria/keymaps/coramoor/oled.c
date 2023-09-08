#pragma once
// #include "features/os_toggle.h"

extern uint32_t transport_user_state;

extern uint16_t sft_tapping_term;

extern uint16_t modtap_tapping_term;

extern uint16_t achordion_tapping_term;

extern uint16_t gqt_tapping_term;

extern uint16_t sgqt_tapping_term;

extern layer_state_t locked_layers;

bool check_lock(void) {
    if (locked_layers) {
        return true;
    } else {
        return false;
    }
}

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

void render_menu(void) {
    menu_items();
}

bool oled_task_user(void) {
    if (get_highest_layer(layer_state | default_layer_state) == _ADJUST) {
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


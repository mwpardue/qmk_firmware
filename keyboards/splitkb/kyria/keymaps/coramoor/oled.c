#pragma once

extern layer_state_t locked_layers;

#ifdef CASEMODE_ENABLE
    extern enum xcase_state xcase_state;
    extern bool caps_word_on;
#endif

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; }

void render_newline(void) {
    oled_write_P(PSTR("\n"), false);
}

void render_qmk_logo_version(void) {
// QMK Logo and version information
// clang-format off
    static const char PROGMEM qmk_logo1[] = {
        0x80,0x81,0x82,0x83,0x84,0x80,0};
    static const char PROGMEM qmk_logo2[] = {
        0xa0,0xa1,0xa2,0xa3,0xa4,0x80,0};
    static const char PROGMEM qmk_logo3[] = {
        0xc0,0xc1,0xc2,0xc3,0xc4,0x80,0};
    oled_write_P(qmk_logo1, false);
    render_newline();
    oled_write_P(qmk_logo2, false);
    render_newline();
    oled_write_P(qmk_logo3, false);
    oled_write_P(PSTR("Kyria rev3.0\n"), false);
}

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

void render_led_state(void) {
        // Write host Keyboard LED Status to OLEDs
        led_t led_usb_state = host_keyboard_led_state();

        if (locked_layers) {
            oled_write_P(PSTR("  LOCKED  "), false);
        } else {
            oled_write_P(PSTR("     "), false);
        }

        if ((led_usb_state.caps_lock) && (xcase_state == XCASE_ON)) {
            oled_write_P(PSTR("  XCASE   "), false);
        } else if (xcase_state == XCASE_ON) {
            oled_write_P(PSTR("  xcase   "), false);
        } else if ((led_usb_state.caps_lock) && (xcase_state == XCASE_WAIT)) {
            oled_write_P(PSTR("  XWAIT   "), false);
        } else if (xcase_state == XCASE_WAIT) {
            oled_write_P(PSTR("  xwait   "), false);
        } else if (caps_word_on) {
            oled_write_P(PSTR(" CAPSWORD "), false);
        } else if (led_usb_state.num_lock) {
            oled_write_P(PSTR("  NUMLCK  "), false);
        } else if (led_usb_state.caps_lock) {
            oled_write_P(PSTR("  CAPLCK  "), false);
        } else {
            oled_write_P(PSTR("     "), false);
        }
}

void render_mod_state(uint8_t modifiers) {
        if((modifiers) & MOD_MASK_CTRL) {
            oled_write_P(PSTR("C"), false);
        } else {
            oled_write_P(PSTR(" "), false);
        }

        if((modifiers) & MOD_MASK_ALT) {
            oled_write_P(PSTR("A"), false);
        } else {
            oled_write_P(PSTR(" "), false);
        }

        if((modifiers) & MOD_MASK_SHIFT) {
            oled_write_P(PSTR("S"), false);
        } else {
            oled_write_P(PSTR(" "), false);
        }

        if((modifiers) & MOD_MASK_GUI) {
            oled_write_P(PSTR("G"), false);
        } else {
            oled_write_P(PSTR(" "), false);
        }
}

bool oled_task_user(void) {
    render_qmk_logo_version();
    render_layer_box_top();
    render_layer_state();
    render_layer_box_bottom();
    render_newline();
    render_led_state();
    // render_newline();
    render_mod_state(get_mods()|get_oneshot_mods());
    return false;
}


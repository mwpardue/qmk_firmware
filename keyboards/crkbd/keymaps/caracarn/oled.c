#pragma once

extern uint8_t is_master;

extern bool ledmap_active;

extern uint32_t transport_user_state;

extern uint16_t sft_tapping_term;

extern uint16_t modtap_tapping_term;

extern uint16_t achordion_tapping_term;

void render_heatmap_specs(void);

#ifdef CASEMODE_ENABLE
    extern enum xcase_state xcase_state;
    extern bool caps_word_on;
#endif

// extern uint8_t user_config.rgb_matrix_heatmap_area;

// extern uint8_t user_config.rgb_matrix_heatmap_spread;

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

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

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

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

// void render_logo(void) {
//     static const char PROGMEM corne_logo[] = {
//         0x80, 0x81, 0x82, 0x83, 0x84,
//         0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
//         0xc0, 0xc1, 0xc2, 0xc3, 0xc4,
//         0x20, 0x99, 0x9a, 0x9b, 0x20, 0};
//     oled_write_P(corne_logo, false);
// }

void render_layer_box_top(void) {
    static const char PROGMEM layer_top[] = {
        0x94, 0x95, 0x96, 0x97, 0x98, 0};
    oled_write_P(layer_top, false);
}

void render_layer_box_bottom(void) {
    static const char PROGMEM layer_bottom[] = {
        0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0};
    oled_write_P(layer_bottom, false);
}

void render_layer_state(void) {
    static const char PROGMEM base_layer[] = {
        0xb4, 0x42, 0x41, 0x53, 0xb8, 0};
    static const char PROGMEM numpad_layer[] = {
        0xb4, 0x4e, 0x55, 0x4d, 0xb8, 0};
    static const char PROGMEM macro_layer[] = {
        0xb4, 0x4d, 0x41, 0x43, 0xb8, 0};
    static const char PROGMEM symbol_layer[] = {
        0xb4, 0x53, 0x59, 0x4d, 0xb8, 0};
    static const char PROGMEM hex_layer[] = {
        0xb4, 0x48, 0x45, 0x58, 0xb8, 0};
    static const char PROGMEM function_layer[] = {
        0xb4, 0x46, 0x55, 0x4e, 0xb8, 0};
    static const char PROGMEM navigation_layer[] = {
        0xb4, 0x4e, 0x41, 0x56, 0xb8, 0};
    static const char PROGMEM colemak_layer[] = {
        0xb4, 0x43, 0x4d, 0x4b, 0xb8, 0};
    static const char PROGMEM media_layer[] = {
        0xb4, 0x4d, 0x45, 0x44, 0xb8, 0};
    static const char PROGMEM adjust_layer[] = {
        0xb4, 0x41, 0x44, 0x4a, 0xb8, 0};
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _NUMPAD:
            oled_write_P(numpad_layer, false);
            break;
        case _MACROS:
            oled_write_P(macro_layer, false);
            break;
        case _SYMBOL:
            oled_write_P(symbol_layer, false);
            break;
        case _HEX:
            oled_write_P(hex_layer, false);
            break;
        case _FUNCTION:
            oled_write_P(function_layer, false);
            break;
        case _NAVIGATION:
            oled_write_P(navigation_layer, false);
            break;
        case _BASE:
            oled_write_P(base_layer, false);
            break;
        case _COLEMAK_DH:
            oled_write_P(colemak_layer, false);
            break;
        case _MEDIA:
            oled_write_P(media_layer, false);
            break;
        case _ADJUST:
            oled_write_P(adjust_layer, false);
            break;
    }
}

void render_led_state(void) {
    // if (get_highest_layer(layer_state | default_layer_state) == _ADJUST) {
        if (user_config.rgb_matrix_ledmap_active) {
            oled_write_P(PSTR(" LED "), false);
        } else {
            oled_write_P(PSTR(" RGB "), false);
        }
}
    // } else {

void render_smart_case(void) {
        #ifdef SMART_CASE_ENABLE
            if (has_smart_case(CAMEL_CASE) && has_smart_case(WORD_CASE)) {
                oled_write_P(PSTR(" Pas "), false);
            } else if (has_smart_case(SNAKE_CASE) && has_smart_case(WORD_CASE)) {
                oled_write_P(PSTR("_SNK_"), false);
            } else if (has_smart_case(KEBAB_CASE) && has_smart_case(WORD_CASE)) {
                oled_write_P(PSTR("-KBB-"), false);
            } else if (has_smart_case(CAMEL_CASE) && !has_smart_case(WORD_CASE)) {
                oled_write_P(PSTR(" cam "), false);
            } else if (has_smart_case(SNAKE_CASE) && !has_smart_case(WORD_CASE)) {
                oled_write_P(PSTR("_snk_"), false);
            } else if (has_smart_case(KEBAB_CASE) && !has_smart_case(WORD_CASE)) {
                oled_write_P(PSTR("-kbb-"), false);
            } else if (has_smart_case(CAPS_LOCK)) {
                oled_write_P(PSTR("CPSLK"), false);
            } else if (has_smart_case(WORD_CASE)) {
                oled_write_P(PSTR("CPSWD"), false);
        #endif
        #ifdef CASEMODE_ENABLE
            static const char PROGMEM xcase_caps[] = {
                0xb4, 0x58, 0x43, 0x53, 0xb8, 0};
            static const char PROGMEM xcase[] = {
                0xb4, 0x78, 0x63, 0x73, 0xb8, 0};
            static const char PROGMEM xwait_caps[] = {
                0xb4, 0x58, 0x57, 0x54, 0xb8, 0};
            static const char PROGMEM xwait[] = {
                0xb4, 0x78, 0x77, 0x74, 0xb8, 0};
            static const char PROGMEM capsword[] = {
                0xb4, 0x43, 0x41, 0x50, 0xb8, 0};
            static const char PROGMEM capslock[] = {
                0xb4, 0x43, 0x50, 0x9c, 0xb8, 0};
            // static const char PROGMEM blank[] = {
            //     0xb4, 0xbc, 0xbc, 0xbc, 0xb8, 0};
            if ((host_keyboard_led_state().caps_lock) && (xcase_state == XCASE_ON)) {
                render_layer_box_top();
                oled_write_P(xcase_caps, false);
                render_layer_box_bottom();
            } else if ((xcase_state == XCASE_ON)) {
                render_layer_box_top();
                oled_write_P(xcase, false);
                render_layer_box_bottom();
            } else if ((host_keyboard_led_state().caps_lock) && (xcase_state == XCASE_WAIT)) {
                render_layer_box_top();
                oled_write_P(xwait_caps, false);
                render_layer_box_bottom();
            } else if ((xcase_state == XCASE_WAIT)) {
                render_layer_box_top();
                oled_write_P(xwait, false);
                render_layer_box_bottom();
            } else if (caps_word_on) {
                render_layer_box_top();
                oled_write_P(capsword, false);
                render_layer_box_bottom();
            } else if (host_keyboard_led_state().caps_lock) {
                render_layer_box_top();
                oled_write_P(capslock, false);
                render_layer_box_bottom();
        #endif
            } else {
                // oled_write_P(blank, false);
                // oled_write_P(blank, false);
                // oled_write_P(blank, false);
                render_heatmap_specs();
            }
}

uint8_t get_heatmap_area(void) {
    return user_config.rgb_matrix_heatmap_area;
}

uint8_t get_heatmap_spread(void) {
    return user_config.rgb_matrix_heatmap_spread;
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

char heatmap_area_str[8];
char heatmap_spread_str[8];
char shift_tapping_term_str[16];
char g_tapping_term_str[16];
char modtap_tapping_term_str[16];
char achordion_tapping_term_str[16];

void render_heatmap_specs(void) {
    sprintf(heatmap_area_str, "%03d", get_heatmap_area());
    sprintf(heatmap_spread_str, "%03d", get_heatmap_spread());
    oled_write_P(PSTR("A:"), false);
    oled_write_P(heatmap_area_str, false);
    oled_write_P(PSTR("\nS:"), false);
    oled_write_P(heatmap_spread_str, false);
    oled_write_P(PSTR("\n"), false);
        // render_smart_case();
    }
    // }
    // else {
        // render_space();
void render_modtap_specs(void) {
  sprintf(shift_tapping_term_str, "%03d", get_shift_tapping_term_str());
  sprintf(g_tapping_term_str, "%03d", get_tapping_term_str());
  sprintf(modtap_tapping_term_str, "%03d", get_modtap_tapping_term_str());
  sprintf(achordion_tapping_term_str, "%03d", get_achordion_tapping_term_str());
  // if ((get_highest_layer(layer_state | default_layer_state) == _ADJUST) && is_keyboard_master()) {
  oled_write_P(PSTR("ST"), false);
  oled_write_P(shift_tapping_term_str, false);
  oled_write_P(PSTR("\n"), false);
  oled_write_P(PSTR("TT"), false);
  oled_write_P(g_tapping_term_str, false);
  oled_write_P(PSTR("\n"), false);
  oled_write_P(PSTR("MT"), false);
  oled_write_P(modtap_tapping_term_str, false);
  oled_write_P(PSTR("\n"), false);
  oled_write_P(PSTR("AT"), false);
  oled_write_P(achordion_tapping_term_str, false);
  // oled_write_P(PSTR("\n"), false);
        // render_space();
        // render_smart_case();
        // render_space();
    // }
}

// void render_heatmap_spread(void) {
//     sprintf(heatmap_spread_str, "%03d", get_heatmap_spread());
//     oled_write_ln_P(heatmap_spread_str, false);
//     oled_write_P(PSTR("\n"), false);
// }

bool oled_task_user(void) {
    if (get_highest_layer(layer_state | default_layer_state) == _ADJUST) {
      render_modtap_specs();
      render_layer_box_top();
      render_layer_state();
      render_layer_box_bottom();
      render_heatmap_specs();
      render_led_state();
    } else {
    // Renders the current keyboard state (layers and mods)
    // render_logo();
    // render_space();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
    render_space();
    render_space();
    render_layer_box_top();
    render_layer_state();
    render_layer_box_bottom();
    // render_space();
    // render_heatmap_specs();
    render_space();
    render_smart_case();
    render_space();
    // render_space();
    // render_smart_case();
    // render_heatmap_spread();
  }
  return false;
}

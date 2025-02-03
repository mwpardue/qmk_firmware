#include QMK_KEYBOARD_H

// #include "rgb_matrix_keys.h"
#include "qkeys.h"
#include "coramoor.h"
#include "rgb_matrix.h"
#include "features/qmenu.h"
#include "features/qpainter.h"


extern uint16_t sft_tapping_term;
extern uint16_t modtap_tapping_term;
extern uint16_t achordion_tapping_term;
extern uint16_t gqt_tapping_term;
extern uint16_t sgqt_tapping_term;

process_record_result_t process_qmenu_keys(uint16_t keycode, keyrecord_t *record) {
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

        case MENU_MD:
            if (record->event.pressed) {
                switch (user_config.submenu_selector) {
                    case SUBMENU_LIGHTING:
                        if (user_config.menu_selector == LIGHTING_END - 1) {
                            user_config.menu_selector = LIGHTING_HEADING;
                        } else {
                            user_config.menu_selector = user_config.menu_selector + 1;
                        };
                        lcd_dirty = true;
                        break;
                    case SUBMENU_MODTAP:
                        if (user_config.menu_selector == MODTAP_END - 1) {
                            user_config.menu_selector = MODTAP_HEADING;
                        } else {
                            user_config.menu_selector = user_config.menu_selector + 1;
                        };
                        lcd_dirty = true;
                        break;
                    case SUBMENU_KB:
                        if (user_config.menu_selector == KB_END - 1) {
                            user_config.menu_selector = KB_HEADING;
                        } else {
                            user_config.menu_selector = user_config.menu_selector + 1;
                        };
                        lcd_dirty = true;
                        break;
                }
                dprintf("Menu Selector is %d\n", user_config.menu_selector);
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;

        case MENU_MU:
            if (record->event.pressed) {
                switch (user_config.submenu_selector) {
                    case SUBMENU_LIGHTING:
                        if (user_config.menu_selector == LIGHTING_HEADING) {
                            user_config.menu_selector = LIGHTING_END - 1;
                        } else {
                            user_config.menu_selector = user_config.menu_selector - 1;
                        }
                        lcd_dirty = true;
                        break;
                    case SUBMENU_MODTAP:
                        if (user_config.menu_selector == MODTAP_HEADING) {
                            user_config.menu_selector = MODTAP_END - 1;
                        } else {
                            user_config.menu_selector = user_config.menu_selector - 1;
                        }
                        lcd_dirty = true;
                        break;
                    case SUBMENU_KB:
                        if (user_config.menu_selector == KB_HEADING) {
                            user_config.menu_selector = KB_END - 1;
                        } else {
                            user_config.menu_selector = user_config.menu_selector - 1;
                        }
                        lcd_dirty = true;
                        break;
                    }
                dprintf("Menu Selector is %d\n", user_config.menu_selector);
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;

        case MENU_AU:
            if (record->event.pressed) {
                dprintln("MENU_AU pressed");
                switch (user_config.submenu_selector) {
                    case SUBMENU_LIGHTING:
                        switch (user_config.menu_selector) {
                            case LIGHTING_HEADING:
                                qp_clear(lcd_surface);
                                user_config.submenu_selector = SUBMENU_MODTAP;
                                break;
                            case MENU_HUE:
                                rgb_matrix_increase_hue();
                                break;
                            case MENU_SAT:
                                rgb_matrix_increase_sat();
                                break;
                            case MENU_VAL:
                                rgb_matrix_increase_val();
                                break;
                            case MENU_SPEED:
                                rgb_matrix_increase_speed();
                                break;
                            case MENU_RGBMODE:
                                rgb_matrix_step();
                                break;
                            case MENU_FLAGS:
                                switch (rgb_matrix_get_flags()) {
                                    case LED_FLAG_ALL: {
                                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                                        dprintf("rgb_matrix_get_flags (KMI)= %d\n", rgb_matrix_get_flags());
                                    }
                                    break;
                                    case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
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
                            break;
                        }
                        break;
                    case SUBMENU_MODTAP:
                        switch (user_config.menu_selector) {
                            case MODTAP_HEADING:
                                qp_clear(lcd_surface);
                                user_config.submenu_selector = SUBMENU_KB;
                                break;
                            case MENU_STT:
                                sft_tapping_term = sft_tapping_term + 5;
                                dprintf("Shift Tapping Term = %d\n", sft_tapping_term);
                                break;
                            case MENU_TT:
                                g_tapping_term = g_tapping_term + 5;
                                dprintf("General Tapping Term = %d\n", g_tapping_term);
                                break;
                            case MENU_MT:
                                modtap_tapping_term = modtap_tapping_term + 5;
                                dprintf("Mod-Tap Tapping Term = %d\n", modtap_tapping_term);
                                break;
                            case MENU_AT:
                                achordion_tapping_term = achordion_tapping_term + 50;
                                dprintf("Achordion Tapping Term = %d\n", achordion_tapping_term);
                                break;
                            case MENU_GQT:
                                gqt_tapping_term = gqt_tapping_term + 5;
                                dprintf("GQT Tapping Term = %d\n", gqt_tapping_term);
                                break;
                            case MENU_SGQT:
                                sgqt_tapping_term = sgqt_tapping_term + 5;
                                dprintf("SGQT Tapping Term = %d\n", sgqt_tapping_term);
                                break;
                        } //MODTAP menu switch
                    break;
                    case SUBMENU_KB:
                        switch (user_config.menu_selector) {
                            case KB_HEADING:
                                qp_clear(lcd_surface);
                                user_config.submenu_selector = SUBMENU_LIGHTING;
                                break;
                            case MENU_EECLEAR:
                                #ifdef NO_RESET
                                    eeconfig_init();
                                #else
                                    eeconfig_disable();
                                    soft_reset_keyboard();
                                #endif
                                break;
                            case MENU_DEBUG:
                                #ifndef NO_DEBUG
                                    debug_enable ^= 1;
                                    kb_state.debug_enabled = debug_enable;
                                    eeconfig_update_user(kb_state.raw);
                                    if (debug_enable) {
                                        print("DEBUG: enabled.\n");
                                    } else {
                                        print("DEBUG: disabled.\n");
                                    }
                                #endif
                                break;
                            case MENU_OSFLAG:
                                switch (user_config.os) {
                                    case MACOS:
                                        user_config.os = WINDOWS;
                                        eeconfig_update_user(user_config.raw);
                                        break;
                                    case WINDOWS:
                                        user_config.os = LINUX;
                                        eeconfig_update_user(user_config.raw);
                                        break;
                                    case LINUX:
                                        user_config.os = MACOS;
                                        eeconfig_update_user(user_config.raw);
                                        break;
                                }
                                break;
                            case MENU_NKRO:
                                if (keymap_config.nkro) {
                                    clear_keyboard(); // clear first buffer to prevent stuck keys
                                    keymap_config.nkro = false;
                                } else {
                                    clear_keyboard(); // clear first buffer to prevent stuck keys
                                    keymap_config.nkro = true;
                                }
                                break;
                            case MENU_BOOTLOADER:
                                reset_keyboard();
                                break;
                            case MENU_DEFAULTLAYER:
                                switch (get_highest_layer(default_layer_state)) {
                                    case _BASE:
                                        set_single_persistent_default_layer(_COLEMAK_DH);
                                        break;
                                    case _COLEMAK_DH:
                                        set_single_persistent_default_layer(_GAMING);
                                        break;
                                    case _GAMING:
                                        set_single_persistent_default_layer(_BASE);
                                        break;
                                    default:
                                        break;
                                }
                                break;
                        }
                    break;
                }
                lcd_dirty = true;
                return PROCESS_RECORD_RETURN_FALSE;
            }
        break;

        case MENU_AD:
                dprintln("MENU_AD pressed");
            if (record->event.pressed) {
                switch (user_config.submenu_selector) {
                    case SUBMENU_LIGHTING:
                        switch (user_config.menu_selector) {
                            case LIGHTING_HEADING:
                                qp_clear(lcd_surface);
                                user_config.submenu_selector = SUBMENU_KB;
                                break;
                            case MENU_HUE:
                                rgb_matrix_decrease_hue();
                                break;
                            case MENU_SAT:
                                rgb_matrix_decrease_sat();
                                break;
                            case MENU_VAL:
                                rgb_matrix_decrease_val();
                                break;
                            case MENU_SPEED:
                                rgb_matrix_decrease_speed();
                                break;
                            case MENU_RGBMODE:
                                rgb_matrix_step_reverse();
                                // substring_timer = timer_read32();
                                break;
                            case MENU_FLAGS:
                                switch (rgb_matrix_get_flags()) {
                                    case LED_FLAG_ALL: {
                                        rgb_matrix_set_flags(LED_FLAG_NONE);
                                        rgb_matrix_disable_noeeprom();
                                        dprintf("rgb_matrix_get_flags (OFF)= %d\n", rgb_matrix_get_flags());
                                    }
                                    break;
                                    case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                                        rgb_matrix_set_flags(LED_FLAG_ALL);
                                        dprintf("rgb_matrix_get_flags (ALL)= %d\n", rgb_matrix_get_flags());
                                    }
                                    break;
                                    case LED_FLAG_UNDERGLOW: {
                                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                                        dprintf("rgb_matrix_get_flags (KMI)= %d\n", rgb_matrix_get_flags());
                                    }
                                    break;
                                    default: {
                                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                                        rgb_matrix_enable_noeeprom();
                                        dprintf("rgb_matrix_get_flags (UG)= %d\n", rgb_matrix_get_flags());
                                    }
                                    break;
                                }
                                break;
                        }
                    break;
                    case SUBMENU_MODTAP:
                        switch (user_config.menu_selector) {
                            case MODTAP_HEADING:
                                qp_clear(lcd_surface);
                                user_config.submenu_selector = SUBMENU_LIGHTING;
                                break;
                            case MENU_STT:
                                sft_tapping_term = sft_tapping_term - 5;
                                dprintf("Shift Tapping Term = %d\n", sft_tapping_term);
                                break;
                            case MENU_TT:
                                g_tapping_term = g_tapping_term - 5;
                                dprintf("General Tapping Term = %d\n", g_tapping_term);
                                break;
                            case MENU_MT:
                                modtap_tapping_term = modtap_tapping_term - 5;
                                dprintf("Mod-Tap Tapping Term = %d\n", modtap_tapping_term);
                                break;
                            case MENU_AT:
                                achordion_tapping_term = achordion_tapping_term - 50;
                                dprintf("Achordion Tapping Term = %d\n", achordion_tapping_term);
                                break;
                            case MENU_GQT:
                                gqt_tapping_term = gqt_tapping_term - 5;
                                dprintf("GQT Tapping Term = %d\n", gqt_tapping_term);
                                break;
                            case MENU_SGQT:
                                sgqt_tapping_term = sgqt_tapping_term - 5;
                                dprintf("SGQT Tapping Term = %d\n", sgqt_tapping_term);
                                break;
                        }
                    break;
                    case SUBMENU_KB:
                        switch (user_config.menu_selector) {
                            case KB_HEADING:
                                qp_clear(lcd_surface);
                                user_config.submenu_selector = SUBMENU_MODTAP;
                                break;
                            case MENU_EECLEAR:
                                #ifdef NO_RESET
                                    eeconfig_init();
                                #else
                                    eeconfig_disable();
                                    soft_reset_keyboard();
                                #endif
                                break;
                            case MENU_DEBUG:
                                #ifndef NO_DEBUG
                                    debug_enable ^= 1;
                                    kb_state.debug_enabled = debug_enable;
                                    eeconfig_update_user(kb_state.raw);
                                    if (debug_enable) {
                                        print("DEBUG: enabled.\n");
                                    } else {
                                        print("DEBUG: disabled.\n");
                                    }
                                #endif
                                break;
                            case MENU_OSFLAG:
                                switch (user_config.os) {
                                    case MACOS:
                                        user_config.os = LINUX;
                                        eeconfig_update_user(user_config.raw);
                                        break;
                                    case WINDOWS:
                                        user_config.os = MACOS;
                                        eeconfig_update_user(user_config.raw);
                                        break;
                                    case LINUX:
                                        user_config.os = WINDOWS;
                                        eeconfig_update_user(user_config.raw);
                                        break;
                                }
                                break;
                            case MENU_NKRO:
                                if (keymap_config.nkro) {
                                    clear_keyboard(); // clear first buffer to prevent stuck keys
                                    keymap_config.nkro = false;
                                } else {
                                    clear_keyboard(); // clear first buffer to prevent stuck keys
                                    keymap_config.nkro = true;
                                }
                                break;
                            case MENU_BOOTLOADER:
                                reset_keyboard();
                                break;
                            case MENU_DEFAULTLAYER:
                                switch (get_highest_layer(default_layer_state)) {
                                    case _BASE:
                                        set_single_persistent_default_layer(_COLEMAK_DH);
                                        break;
                                    case _COLEMAK_DH:
                                        set_single_persistent_default_layer(_GAMING);
                                        break;
                                    case _GAMING:
                                        set_single_persistent_default_layer(_BASE);
                                        break;
                                    default:
                                        break;
                                }
                                break;
                        }
                    break;
                }
                lcd_dirty = true;
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
            case TB_MENU:
                if (record->event.pressed) {
                    switch (user_config.submenu_selector) {
                        case SUBMENU_LIGHTING:
                            user_config.submenu_selector = SUBMENU_MODTAP;
                            break;
                        case SUBMENU_MODTAP:
                            user_config.submenu_selector = SUBMENU_KB;
                            break;
                        case SUBMENU_KB:
                            user_config.submenu_selector = SUBMENU_LIGHTING;
                            break;
                    }
                }
            qp_clear(lcd_surface);
            lcd_dirty = true;
            return PROCESS_RECORD_RETURN_FALSE;
            break;
    }
    return PROCESS_RECORD_CONTINUE; // Process all other keycodes normally
}

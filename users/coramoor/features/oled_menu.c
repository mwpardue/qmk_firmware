#include QMK_KEYBOARD_H

#include <ctype.h>
#include "coramoor.h"


uint16_t sft_tapping_term = SHIFT_TAPPING_TERM;

uint16_t get_sft_tapping_term(void) {
    return sft_tapping_term;
}

uint16_t modtap_tapping_term = MODTAP_TAPPING_TERM;

uint16_t get_modtap_tapping_term(void) {
    return modtap_tapping_term;
}

uint16_t achordion_tapping_term = ACHORDION_TAPPING_TERM;

uint16_t get_achordion_tapping_term(void) {
    return achordion_tapping_term;
}

uint16_t gqt_tapping_term = GQT_TAPPING_TERM;

uint16_t get_gqt_tapping_term(void) {
    return gqt_tapping_term;
}

uint16_t sgqt_tapping_term = SGQT_TAPPING_TERM;

uint16_t sget_gqt_tapping_term(void) {
    return sgqt_tapping_term;
}

extern uint32_t substring_timer;

extern uint8_t viewport_begin(void);


__attribute__((unused)) int            start_index = 0;

__attribute__((unused)) uint32_t        substring_timer = 0;

__attribute__((unused)) uint32_t scroll_time = 1000;
//----------------------------------------------------------
// GENERAL MENU FUNCTIONS

bool check_menu(uint8_t menu_item) {
    if (user_config.oled_menu_selector == menu_item) {
        return true;
    } else {
        return false;
    }
}

uint8_t viewport_begin(void) {
    if (user_config.oled_menu_selector <= 3) {
        return 1;
    } else if (user_config.oled_menu_selector >= (MENU_MAX - 3)) {
        return (MENU_MAX - VIEWPORT_HEIGHT);
    } else {
        return (user_config.oled_menu_selector - 3);
    }
}

void render_menu_item(const char *label, uint16_t property, uint8_t menu_item) {
    size_t label_length = strlen(label);

    char property_str[20];
    snprintf(property_str, sizeof(property_str), "%d", property);
    uint8_t property_length = strlen(property_str);

    uint8_t spacer_length = (VIEWPORT_WIDTH - label_length - property_length);
    oled_write_P(PSTR(label), check_menu(menu_item));
    for (uint8_t i = 1; i <= spacer_length; i++) {
        oled_write_P(PSTR(" "), check_menu(menu_item));
    }
    oled_write_P(PSTR(property_str), check_menu(menu_item));
}

void render_bool_menu_item(const char *label, bool property, uint8_t menu_item) {
    char property_str[4];
    uint8_t property_length = strlen(property_str);
    size_t label_length = strlen(label);

    if (property) {
        strcpy(property_str, "ON");
    } else {
        strcpy(property_str, "OFF");
    }
    property_length = strlen(property_str);

    uint8_t spacer_length = (VIEWPORT_WIDTH - label_length - property_length);
    oled_write_P(PSTR(label), check_menu(menu_item));
    for (uint8_t i = 1; i <= spacer_length; i++) {
        oled_write_P(PSTR(" "), check_menu(menu_item));
    }
    oled_write_P(PSTR(property_str), check_menu(menu_item));
}

void menu_items(void) {
    oled_write_P(PSTR("   Dractyl Config    "), false);
    for (uint8_t i = viewport_begin(); i <= (viewport_begin() + 6); i++) {
        switch(i) {
            case MENU_STT:
                render_menu_item("SHIFT TAP TERM:", sft_tapping_term, i);
                break;
            case MENU_TT:
                render_menu_item("TAPPING TERM:", g_tapping_term, i);
                break;
            case MENU_MT:
                render_menu_item("MOD TAP TERM:", modtap_tapping_term, i);
                break;
            case MENU_AT:
                render_menu_item("ACH TAP TERM:", achordion_tapping_term, i);
                break;
            case MENU_GQT:
                render_menu_item("GQT TAP TERM:", gqt_tapping_term, i);
                break;
            case MENU_SGQT:
                render_menu_item("SGQT TAP TERM:", sgqt_tapping_term, i);
                break;
            case MENU_DEFAULTLAYER:
                switch (get_highest_layer(default_layer_state)) {
                    case _BASE:
                        oled_write_P(PSTR("DF LAYER:      QWERTY"), check_menu(MENU_DEFAULTLAYER));
                        break;
                    case _COLEMAK_DH:
                        oled_write_P(PSTR("DF LAYER:     COLEMAK"), check_menu(MENU_DEFAULTLAYER));
                        break;
                    default:
                        oled_write_P(PSTR("DF LAYER:       OTHER"), check_menu(MENU_DEFAULTLAYER));
                        break;
                }
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
                oled_write_P(PSTR("CLEAR EEPROM: EXECUTE"), check_menu(MENU_EECLEAR));
                break;
            case MENU_NKRO:
                render_bool_menu_item("NKRO:", keymap_config.nkro, i);
                break;
            case MENU_BOOTLOADER:
                oled_write_P(PSTR("FLASH FW:     EXECUTE"), check_menu(MENU_BOOTLOADER));
                break;
            default:
            break;
        }
    }
}





process_record_result_t process_oled_menu_keys(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MENU_MD:
            if (record->event.pressed) {
                if (user_config.oled_menu_selector == MENU_MAX - 1) {
                    user_config.oled_menu_selector = 1;
                } else {
                    user_config.oled_menu_selector = user_config.oled_menu_selector + 1;
                };
                dprintf("RGB Selector is %d\n", user_config.oled_menu_selector);
                dprintf("Viewport min is %d\n", viewport_begin());
                substring_timer = timer_read32();
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;

        case MENU_MU:
            if (record->event.pressed) {
                if (user_config.oled_menu_selector == 1) {
                    user_config.oled_menu_selector = MENU_MAX - 1;
                } else {
                    user_config.oled_menu_selector = user_config.oled_menu_selector - 1;
                }
                dprintf("RGB Selector is %d\n", user_config.oled_menu_selector);
                dprintf("Viewport min is %d\n", viewport_begin());
                substring_timer = timer_read32();
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;

        case MENU_AU:
            if (record->event.pressed) {
                switch (user_config.oled_menu_selector) {
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
                                set_single_persistent_default_layer(_BASE);
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;

        case MENU_AD:
            if (record->event.pressed) {
                switch (user_config.oled_menu_selector) {
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
                                set_single_persistent_default_layer(_BASE);
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;

  }
    return PROCESS_RECORD_CONTINUE; // Process all other keycodes normally
}


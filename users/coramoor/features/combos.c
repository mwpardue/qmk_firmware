#include QMK_KEYBOARD_H

#include "combos.h"

#include "casemodes.h"

#ifdef CUSTOM_LEADER_ENABLE
    #include "features/leader.h"
#endif

#ifdef CASEMODE_ENABLE
    #include "casemodes.h"
#endif

extern enum xcase_state xcase_state;
extern bool caps_word_on;

//Shortcuts
// const uint16_t PROGMEM bootloader_combo[] = {OL_THUM, KC_Q, KC_T, COMBO_END};
// const uint16_t PROGMEM bootloadercm_combo[] = {OL_THUM, KC_Q, KC_B, COMBO_END};
// const uint16_t PROGMEM sleep_combo[] = {OL_THUM, KC_Q, KC_W, COMBO_END};
// const uint16_t PROGMEM escape_combo[] = {KC_D, KC_S, COMBO_END};
// const uint16_t PROGMEM playpause_combo[] = {OL_THUM, KC_S, KC_D, COMBO_END};
// const uint16_t PROGMEM previous_combo[] = {OL_THUM, KC_A, KC_S, COMBO_END};
// const uint16_t PROGMEM next_combo[] = {OL_THUM, KC_D, KC_F, COMBO_END};
// const uint16_t PROGMEM login_combo[] = {OR_THUM, KC_O, KC_P, COMBO_END};
// const uint16_t PROGMEM logincm_combo[] = {OR_THUM, KC_Y, KC_SCLN, COMBO_END};
// const uint16_t PROGMEM copy_combo[] = {IL_THUM, KC_X, KC_C, COMBO_END};
// const uint16_t PROGMEM cut_combo[] = {IL_THUM, KC_Z, KC_X, COMBO_END};
// const uint16_t PROGMEM paste_combo[] = {IL_THUM, KC_C, KC_V, COMBO_END};
// const uint16_t PROGMEM debug_combo[] = {IL_THUM, KC_D, KC_G, COMBO_END};
// const uint16_t PROGMEM delete_combo[] = {ESC_MEH, KC_S, KC_A, COMBO_END};
// const uint16_t PROGMEM enter_combo[] = {OL_THUM, KC_S, KC_D, COMBO_END};
// const uint16_t PROGMEM capsword_combo[] = {KC_D, RHM_K, COMBO_END};
// const uint16_t PROGMEM capswordcm_combo[] = {CLHM_S, CRHM_E, COMBO_END};
// const uint16_t PROGMEM tab_combo[] = {KC_X, KC_C, COMBO_END};
//
// combo_t key_combos[] = {
//   COMBO(bootloader_combo, QK_BOOT),
//   COMBO(bootloadercm_combo, QK_BOOT),
//   COMBO(sleep_combo, MACSLEP),
//   COMBO(escape_combo, QK_GESC),
//   COMBO(playpause_combo, KC_MPLY),
//   COMBO(previous_combo, KC_MPRV),
//   COMBO(next_combo, KC_MNXT),
//   COMBO(login_combo, SM_LOGN),
//   COMBO(logincm_combo, SM_LOGN),
//   COMBO(copy_combo, LGUI(KC_C)),
//   COMBO(cut_combo, LGUI(KC_X)),
//   COMBO(paste_combo, LGUI(KC_V)),
//   COMBO(debug_combo, DB_TOGG),
//   COMBO(delete_combo, KC_BACKSPACE),
//   COMBO(enter_combo, KC_ENTER),
//   COMBO(capsword_combo, SM_CW),
//   COMBO(capswordcm_combo, SM_CW),
//   COMBO(tab_combo, KC_TAB)
// };

// extern os_t os;

#ifndef DEFAULT_MOD_ENABLE
    #ifndef SHORTCUTS_ENABLE
        bool should_send_ctrl(bool isWindowsOrLinux, bool isOneShotShift) {
            return (isWindowsOrLinux && !isOneShotShift) || (!isWindowsOrLinux && isOneShotShift);
        }
    #endif
#endif

bool get_combo_must_tap(uint16_t index, combo_t *combo) {

    uint16_t key;
    uint8_t idx = 0;
    bool combo_must_tap = false;
    while ((key = pgm_read_word(&combo->keys[idx])) != COMBO_END) {
        switch (key) {
            case QK_MOD_TAP...QK_MOD_TAP_MAX:
            case QK_LAYER_TAP...QK_LAYER_TAP_MAX:
            case QK_MOMENTARY...QK_MOMENTARY_MAX:
                combo_must_tap = true;
                break;
            default:
                combo_must_tap = false;
                break;
        }
        if (!combo_must_tap) {
            return false;
        }
        idx += 1;
    }
    return combo_must_tap;
}

 process_record_result_t process_combos(uint16_t keycode, keyrecord_t *record) {

    bool isOneShotLockedShift = get_oneshot_locked_mods() & MOD_MASK_SHIFT;
    bool isOneShotLockedCtrl = get_oneshot_locked_mods() & MOD_MASK_CTRL;
    bool isOneShotLockedAlt = get_oneshot_locked_mods() & MOD_MASK_ALT;
    bool isOneShotLockedGui = get_oneshot_locked_mods() & MOD_MASK_GUI;
    bool isAnyOneShotLockedMod = isOneShotLockedShift || isOneShotLockedCtrl || isOneShotLockedAlt || isOneShotLockedGui;
    bool kbFeature = caps_word_on || xcase_state == XCASE_ON || xcase_state == XCASE_WAIT || isAnyOneShotLockedMod || is_leading() || host_keyboard_led_state().caps_lock;

    switch (keycode) {

        case SM_LOGN:
            if (record->event.pressed) {
                    send_string(secrets[1]);
                    tap_code16(KC_ENTER);
                    return PROCESS_RECORD_RETURN_FALSE;
            }
            break;

        case SM_ESC:
            if (record->event.pressed) {
                if (kbFeature) {
                    if (caps_word_on) {
                        disable_caps_word();
                        tap_code16(KC_ESC);
                    }
                    if (host_keyboard_led_state().caps_lock) {
                        tap_code16(KC_CAPS);
                    }
                    disable_xcase();
                    clear_locked_and_oneshot_mods();
                    stop_leading();
                    return PROCESS_RECORD_RETURN_FALSE;
                } else {
                    tap_code16(KC_ESC);
                    dprintln("SM_ESC default");
                    return PROCESS_RECORD_RETURN_FALSE;
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            break;

        case SM_CW:
            if (record->event.pressed) {
                    toggle_caps_word();
                    return PROCESS_RECORD_RETURN_FALSE;
            }
            break;

        case SM_PAR:
            if (record->event.pressed) {
                tap_code16(KC_LPRN);
                tap_code16(KC_RPRN);
                tap_code16(KC_LEFT);
            }
            break;

        case SM_CUR:
            if (record->event.pressed) {
                tap_code16(KC_LCBR);
                tap_code16(KC_RCBR);
                tap_code16(KC_LEFT);
            }
            break;

        case SM_BRC:
            if (record->event.pressed) {
                tap_code16(KC_LBRC);
                tap_code16(KC_RBRC);
                tap_code16(KC_LEFT);
            }
            break;

        case SM_ANG:
            if (record->event.pressed) {
                tap_code16(KC_LT);
                tap_code16(KC_GT);
                tap_code16(KC_LEFT);
            }
            break;

        case LEADER:
        if (record->event.pressed) {
                start_leading();
        }
        break;

}


    return PROCESS_RECORD_CONTINUE;
}

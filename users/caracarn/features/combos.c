#include QMK_KEYBOARD_H

#include "combos.h"

//Shortcuts
const uint16_t PROGMEM bootloader_combo[] = {SFT_NUM, KC_Q, KC_T, COMBO_END};
const uint16_t PROGMEM sleep_combo[] = {SFT_NUM, KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM playpause_combo[] = {SFT_NUM, ALT_S, CTL_D, COMBO_END};
const uint16_t PROGMEM previous_combo[] = {SFT_NUM, SFT_A, ALT_S, COMBO_END};
const uint16_t PROGMEM next_combo[] = {SFT_NUM, CTL_D, GUI_F, COMBO_END};
const uint16_t PROGMEM login_combo[] = {SFT_BSP, KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM copy_combo[] = {ENT_NAV, KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cut_combo[] = {ENT_NAV, KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {ENT_NAV, KC_C, ALT_V, COMBO_END};
const uint16_t PROGMEM debug_combo[] = {ENT_NAV, CTL_D, KC_G, COMBO_END};
const uint16_t PROGMEM delete_combo[] = {ESC_MEH, ALT_S, SFT_A, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {ESC_MEH, ALT_S, CTL_D, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {

  COMBO(bootloader_combo, QK_BOOT),
  COMBO(sleep_combo, MACSLEP),
  COMBO(playpause_combo, KC_MPLY),
  COMBO(previous_combo, KC_MPRV),
  COMBO(next_combo, KC_MNXT),
  COMBO(login_combo, SM_LOGN),
  COMBO(copy_combo, LGUI(KC_C)),
  COMBO(cut_combo, LGUI(KC_X)),
  COMBO(paste_combo, LGUI(KC_V)),
  COMBO(debug_combo, DB_TOGG),
  COMBO(delete_combo, KC_BACKSPACE),
  COMBO(enter_combo, KC_ENTER)

};

extern os_t os;

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

    // bool isWindowsOrLinux = os.type == WINDOWS || os.type == LINUX;
    // bool isOneShotShift = get_oneshot_mods() & MOD_MASK_SHIFT || get_oneshot_locked_mods() & MOD_MASK_SHIFT;

    switch (keycode) {

        case SM_LOGN:
            if (record->event.pressed) {
                    send_string(secrets[1]);
                    tap_code16(KC_ENTER);
                    return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
        }

    return PROCESS_RECORD_CONTINUE;
}

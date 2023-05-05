#include QMK_KEYBOARD_H

#include "combos.h"

#include "casemodes.h"

//Shortcuts
const uint16_t PROGMEM bootloader_combo[] = {TAB_NUM, KC_Q, KC_T, COMBO_END};
const uint16_t PROGMEM bootloadercm_combo[] = {TAB_NUM, KC_Q, KC_B, COMBO_END};
const uint16_t PROGMEM sleep_combo[] = {TAB_NUM, KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM escape_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM playpause_combo[] = {TAB_NUM, CTL_S, SFT_D, COMBO_END};
const uint16_t PROGMEM previous_combo[] = {TAB_NUM, ALT_A, CTL_S, COMBO_END};
const uint16_t PROGMEM next_combo[] = {TAB_NUM, SFT_D, GUI_F, COMBO_END};
const uint16_t PROGMEM login_combo[] = {ENT_GUI, KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM logincm_combo[] = {ENT_GUI, KC_Y, KC_SCLN, COMBO_END};
const uint16_t PROGMEM copy_combo[] = {BSP_NAV, KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cut_combo[] = {BSP_NAV, KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {BSP_NAV, KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM debug_combo[] = {BSP_NAV, SFT_D, KC_G, COMBO_END};
const uint16_t PROGMEM delete_combo[] = {ESC_MEH, CTL_S, ALT_A, COMBO_END};
const uint16_t PROGMEM enter_combo[] = {ESC_MEH, CTL_S, SFT_D, COMBO_END};
const uint16_t PROGMEM capsword_combo[] = {SFT_D, SFT_K, COMBO_END};
const uint16_t PROGMEM capswordcm_combo[] = {SFT_S, SFT_E, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {

  COMBO(bootloader_combo, QK_BOOT),
  COMBO(bootloadercm_combo, QK_BOOT),
  COMBO(sleep_combo, MACSLEP),
  COMBO(escape_combo, QK_GESC),
  COMBO(playpause_combo, KC_MPLY),
  COMBO(previous_combo, KC_MPRV),
  COMBO(next_combo, KC_MNXT),
  COMBO(login_combo, SM_LOGN),
  COMBO(logincm_combo, SM_LOGN),
  COMBO(copy_combo, LGUI(KC_C)),
  COMBO(cut_combo, LGUI(KC_X)),
  COMBO(paste_combo, LGUI(KC_V)),
  COMBO(debug_combo, DB_TOGG),
  COMBO(delete_combo, KC_BACKSPACE),
  COMBO(enter_combo, KC_ENTER),
  COMBO(capsword_combo, SM_CW),
  COMBO(capswordcm_combo, SM_CW)

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

        case SM_CW:
            if (record->event.pressed) {
                    toggle_caps_word();
                    return PROCESS_RECORD_RETURN_FALSE;
            }
            break;
        }

    return PROCESS_RECORD_CONTINUE;
}

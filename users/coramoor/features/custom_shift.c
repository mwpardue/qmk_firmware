#include QMK_KEYBOARD_H

#include "custom_shift.h"
#include "tapdance.h"

extern os_t os;
static bool custom_shifting = false;

process_record_result_t process_custom_shift(uint16_t keycode, keyrecord_t *record) {

    bool isOneShotLockedShift = get_oneshot_locked_mods() & MOD_MASK_SHIFT;
    bool isOneShotShift = isOneShotLockedShift || get_oneshot_mods() & MOD_MASK_SHIFT;
    bool isShifted = custom_shifting || isOneShotShift || get_mods() & MOD_MASK_SHIFT;
    uint16_t key = extract_base_tapping_keycode(keycode);

    // Numpad Custom Shifts (make it work even on MacOS)

    switch (key) {

        // Ignore space for one-shot shift

        case KC_SPC:
            if (record->event.pressed) {
                if (isOneShotShift) {
                    tap_code(KC_SPC);
                    add_oneshot_mods(MOD_LSFT);
                    return PROCESS_RECORD_RETURN_FALSE;
                }
            }
            return PROCESS_RECORD_CONTINUE;

        // Shift+Backspace for Delete (when not one-shot)

        case KC_BSPC:
            // if (record->event.pressed) {
            //     if (isShifted && !isOneShotShift) {
            //         register_code(KC_DEL);
            //         return PROCESS_RECORD_RETURN_FALSE;
            //     }
            // }
            // return PROCESS_RECORD_RETURN_TRUE;

            if (isShifted && !isOneShotShift) {
                if (record->event.pressed && record->tap.count>0) {
                  tap_code16(KC_DEL);
                  return PROCESS_RECORD_RETURN_FALSE;
                }
                return PROCESS_RECORD_RETURN_TRUE;
            }
            return PROCESS_RECORD_CONTINUE;

    }

    return PROCESS_RECORD_CONTINUE;
}

#include QMK_KEYBOARD_H

#include "smart_thumb_keys.h"
#include "leader.h"
#ifdef CASEMODE_ENABLE
    #include "casemodes.h"
#endif
#ifdef HLC_TFT_DISPLAY
    #include "features/qpainter.h"
#endif

uint8_t smart_mods = 0;
extern enum xcase_state xcase_state;
extern bool caps_word_on;
extern uint16_t idle_timer;

bool should_send_ctrl(bool isWindowsOrLinux, bool isOneShotShift) {
    return (isWindowsOrLinux && !isOneShotShift) || (!isWindowsOrLinux && isOneShotShift);
}

process_record_result_t process_smart_thumb_keys(uint16_t keycode, keyrecord_t *record) {
    bool isOneShotLockedShift = get_oneshot_locked_mods() & MOD_MASK_SHIFT;
    bool isOneShotShift       = get_oneshot_mods() & MOD_MASK_SHIFT || isOneShotLockedShift;
    bool isOneShotCtrl        = get_oneshot_mods() & MOD_MASK_CTRL || get_oneshot_locked_mods() & MOD_MASK_CTRL;
    bool isOneShotAlt         = get_oneshot_mods() & MOD_MASK_ALT || get_oneshot_locked_mods() & MOD_MASK_ALT;
    bool isOneShotGui         = get_oneshot_mods() & MOD_MASK_GUI || get_oneshot_locked_mods() & MOD_MASK_GUI;
    bool isCtrl               = get_mods() & MOD_MASK_CTRL || isOneShotCtrl;
    bool isShift               = get_mods() & MOD_MASK_SHIFT || isOneShotShift || isOneShotLockedShift;
    bool isAlt               = get_mods() & MOD_MASK_ALT || isOneShotAlt;
    bool isGui               = get_mods() & MOD_MASK_GUI || isOneShotGui;



    switch (keycode) {
    case CLIL_THM:
        if (record->event.pressed) {
        if (record->tap.count > 0) {
            if ((xcase_state != 0 || caps_word_on)) {
                disable_xcase();
                disable_caps_word();
                if (host_keyboard_led_state().caps_lock) {
                    tap_code16(KC_CAPS);
                    }
                clear_mods();
                clear_locked_and_oneshot_mods();
                return PROCESS_RECORD_RETURN_FALSE;
            }
            else if (isCtrl || isShift ) {
                if (isCtrl) {
                    enable_xcase();
                }
                if (isShift) {
                    enable_caps_word();
                }
                clear_mods();
                clear_locked_and_oneshot_mods();
                return PROCESS_RECORD_RETURN_FALSE;
            } else if (isAlt || isGui ) {
                clear_mods();
                clear_locked_and_oneshot_mods();
                return PROCESS_RECORD_RETURN_FALSE;
            } else {
                add_oneshot_mods(MOD_LSFT);
            }
            return PROCESS_RECORD_RETURN_FALSE;
        }
        return PROCESS_RECORD_CONTINUE;
        }
    break;

    case CUIL_THM:
    case UIL_THM:
    case UIR_THM:
        if (record->event.pressed) {
            layer_on(_APPSWITCH);
            register_mods(MOD_MASK_GUI);
            dprintln("LUTHUM2");
            tap_code16(KC_TAB);
        } else {
            layer_off(_APPSWITCH);
            unregister_mods(MOD_MASK_GUI);
        }
        return PROCESS_RECORD_RETURN_FALSE;
    break;

    case UOR_THM:
    case UOL_THM:
        if (record->event.pressed) {
            start_leading();
            return PROCESS_RECORD_RETURN_FALSE;
        }
        return PROCESS_RECORD_RETURN_FALSE;
    break;

    case LUTHUM1:
        if (record->event.pressed) {
            if (record->tap.count > 0) {
                    tap_code16(LALT(KC_L));
        return PROCESS_RECORD_RETURN_FALSE;
                }
      return PROCESS_RECORD_CONTINUE;
            }
        break;

    case RUTHUM1:
        if (record->event.pressed) {
            if (record->tap.count > 0) {
                    tap_code16(LGUI(KC_H));
        return PROCESS_RECORD_RETURN_FALSE;
                }
      return PROCESS_RECORD_CONTINUE;
            }
        break;

    case XCTHUM:
    // case RUTHUM2:
        if (record->event.pressed) {
                dprintln("XCTHUM pressed");
                    if (isCtrl) {
                        tap_code16(KC_CAPS);
                        #ifdef HLC_TFT_DISPLAY
                        lcd_dirty = true;
                        #endif
                    } else {
                        switch (xcase_state) {
                            case XCASE_WAIT:
                                if (caps_word_on) {
                                    disable_xcase();
                                    disable_caps_word();
                                } else {
                                    enable_caps_word();
                                }
                                break;
                            case XCASE_ON:
                                disable_caps_word();
                                disable_xcase();
                                break;
                            default:
                                if (caps_word_on) {
                                    disable_caps_word();
                                } else {
                                    enable_xcase();
                                }
                                break;
                        }
                    }
            return PROCESS_RECORD_RETURN_FALSE;
        }
        break;

    case CRUTHUM2:
        if (record->event.pressed) {
            if (record->tap.count > 0) {
                dprintln("XCTHUM pressed");
                    if (isCtrl) {
                        tap_code16(KC_CAPS);
                        #ifdef HLC_TFT_DISPLAY
                        lcd_dirty = true;
                        #endif
                    } else {
                        switch (xcase_state) {
                            case XCASE_WAIT:
                                if (caps_word_on) {
                                    disable_xcase();
                                    disable_caps_word();
                                } else {
                                    enable_caps_word();
                                }
                                break;
                            case XCASE_ON:
                                disable_caps_word();
                                disable_xcase();
                                break;
                            default:
                                if (caps_word_on) {
                                    disable_caps_word();
                                } else {
                                    enable_xcase();
                                }
                                break;
                        }
                    }
            return PROCESS_RECORD_RETURN_FALSE;
            }
            return PROCESS_RECORD_CONTINUE;
        }
        break;

}
    return PROCESS_RECORD_CONTINUE;
}

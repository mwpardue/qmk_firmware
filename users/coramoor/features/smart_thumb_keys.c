#include QMK_KEYBOARD_H

#include "smart_thumb_keys.h"
#include "leader.h"
#ifdef CASEMODE_ENABLE
    #include "casemodes.h"
#endif

// extern os_t           os;
// extern user_config_t user_config;

uint8_t smart_mods = 0;
extern enum xcase_state xcase_state;
extern bool caps_word_on;
extern uint16_t idle_timer;

bool should_send_ctrl(bool isWindowsOrLinux, bool isOneShotShift) {
    return (isWindowsOrLinux && !isOneShotShift) || (!isWindowsOrLinux && isOneShotShift);
}

process_record_result_t process_smart_thumb_keys(uint16_t keycode, keyrecord_t *record) {
    bool isWindowsOrLinux    = user_config.os == WINDOWS || user_config.os == LINUX;
    bool isOneShotDefaultMod = (!isWindowsOrLinux && (get_oneshot_mods() & MOD_MASK_GUI)) ||
                               (isWindowsOrLinux && (get_oneshot_mods() & MOD_MASK_CTRL));
    bool isOneShotLockedShift = get_oneshot_locked_mods() & MOD_MASK_SHIFT;
    bool isOneShotShift       = get_oneshot_mods() & MOD_MASK_SHIFT || isOneShotLockedShift;
    bool isOneShotCtrl        = get_oneshot_mods() & MOD_MASK_CTRL || get_oneshot_locked_mods() & MOD_MASK_CTRL;
    bool isOneShotAlt         = get_oneshot_mods() & MOD_MASK_ALT || get_oneshot_locked_mods() & MOD_MASK_ALT;
    bool isOneShotGui         = get_oneshot_mods() & MOD_MASK_GUI || get_oneshot_locked_mods() & MOD_MASK_GUI;
    bool isAnyOneShotButShift = isOneShotCtrl || isOneShotAlt || isOneShotGui;
    bool isAnyOneShot         = isOneShotCtrl || isOneShotAlt || isOneShotGui || isOneShotShift;
    // bool isCtrl               = get_mods() & MOD_MASK_CTRL || isOneShotCtrl;
    // bool isShift               = get_mods() & MOD_MASK_SHIFT || isOneShotShift || isOneShotLockedShift;
    // bool isAlt               = get_mods() & MOD_MASK_ALT || isOneShotAlt;
    // bool isGui               = get_mods() & MOD_MASK_GUI || isOneShotGui;



    switch (keycode) {
          case CAP_MEH:
      if (record->event.pressed) {
        if (record->tap.count > 0) {
          if ((isAnyOneShot) || (host_keyboard_led_state().caps_lock) || (caps_word_on) || (xcase_state == (XCASE_ON || XCASE_WAIT))) {
            clear_locked_and_oneshot_mods();
            disable_caps_word();
            disable_xcase();
            dprintln("disable caps_word and xcase");
              if (host_keyboard_led_state().caps_lock) {
                tap_code16(KC_CAPS);
              }
          } else {
              if ((get_mods() & MOD_MASK_ALT) && (get_mods() & MOD_MASK_SHIFT)) {
                clear_mods();
                enable_xcase();
                enable_caps_word();
                dprintln("enable xcase and caps_word");
              } else if  (get_mods() & MOD_MASK_ALT) {
                clear_mods();
                enable_xcase();
                dprintln("enable xcase");
              } else if (get_mods() & MOD_MASK_SHIFT) {
                clear_mods();
                enable_xcase_with(OSM(MOD_LSFT));
                dprintln("enable xcase with OSM shift");
              } else if (get_mods() & MOD_MASK_CTRL) {
                tap_code16(KC_CAPS);
                dprintln("enable caps lock");
              } else if (!caps_word_on) {
                enable_caps_word();
                dprintln("enable caps_word");
              }
          return PROCESS_RECORD_RETURN_FALSE;
          }
          return PROCESS_RECORD_RETURN_FALSE;
        }
      return PROCESS_RECORD_CONTINUE;
      }
    break;

        case MOD_KEY:
    if (record->tap.count > 0) {
        if (record->event.pressed) {
            if (isAnyOneShotButShift || isOneShotLockedShift) {
                clear_locked_and_oneshot_mods();
            } else if (!isOneShotDefaultMod) {
                if (isOneShotShift) {
                    clear_locked_and_oneshot_mods();
                }
                if (should_send_ctrl(isWindowsOrLinux, isOneShotShift)) {
                    add_oneshot_mods(MOD_LCTL);
                } else {
                    add_oneshot_mods(MOD_LGUI);
                }
            }
            return PROCESS_RECORD_RETURN_FALSE;
        }
        return PROCESS_RECORD_CONTINUE;
    }
    break;

        // case CLOL_THM:
        //   if (record->event.pressed) {
        //     if (record->tap.count > 0) {
        //         if ((xcase_state != 0 || caps_word_on)) {
        //             disable_xcase();
        //             disable_caps_word();
        //             if (host_keyboard_led_state().caps_lock) {
        //                 tap_code16(KC_CAPS);
        //                 }
        //             clear_mods();
        //             clear_locked_and_oneshot_mods();
        //             return PROCESS_RECORD_RETURN_FALSE;
        //         }
        //         else if (isCtrl || isShift ) {
        //             if (isCtrl) {
        //                 enable_xcase();
        //             }
        //             if (isShift) {
        //                 enable_caps_word();
        //             }
        //             clear_mods();
        //             clear_locked_and_oneshot_mods();
        //             return PROCESS_RECORD_RETURN_FALSE;
        //         } else if (isAlt || isGui ) {
        //             clear_mods();
        //             clear_locked_and_oneshot_mods();
        //             return PROCESS_RECORD_RETURN_FALSE;
        //         } else {
        //             add_oneshot_mods(MOD_LSFT);
        //         }
        //       return PROCESS_RECORD_RETURN_FALSE;
        //     }
        //   return PROCESS_RECORD_CONTINUE;
        //   }
        // break;

    case CTL_CW:
    case SFT_CW:
    case GUI_CW:
      if (record->event.pressed) {
        if (record->tap.count > 0) {
            if (caps_word_on) {
                disable_caps_word();
            }
            else {
                enable_caps_word();
            }
        return PROCESS_RECORD_RETURN_FALSE;
        }
      return PROCESS_RECORD_CONTINUE;
      }
    break;

    case LUTHUM2:
    case CLUTHUM2:
        if (record->event.pressed) {
            if (record->tap.count > 0) {
                switch (user_config.os) {
                    case MACOS:
                        tap_code16(G(C(A(S(KC_P)))));
                        start_pass_leading();
                        break;
                    case LINUX:
                        start_pass_leading();
                        break;
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            return PROCESS_RECORD_CONTINUE;
        }
        break;

    case XCTHUM:
        if (record->event.pressed) {
            dprintln("XCTHUM pressed");
                if (xcase_state == XCASE_WAIT) {
                    if (caps_word_on) {
                        disable_caps_word();
                        disable_xcase();
                    } else {
                        dprintln("XCTHUM xcase_state wait");
                        enable_caps_word();
                    }
                } else if (xcase_state == XCASE_ON) {
                    dprintln("XCTHUM xcase_state on");
                    disable_caps_word();
                    disable_xcase();
                } else {
                    enable_xcase();
                    dprintln("XCTHUM else statement");
                }
                return PROCESS_RECORD_RETURN_FALSE;
        }
        break;

}

// } Remove quotes and fix curly brackets, if thumb keys don't work.
    return PROCESS_RECORD_CONTINUE;
}

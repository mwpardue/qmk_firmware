#include QMK_KEYBOARD_H

#include "smart_thumb_keys.h"
#ifdef CASEMODE_ENABLE
    #include "casemodes.h"
#endif
#ifdef OS_TOGGLE_ENABLE
    #include "features/os_toggle.h"
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
      return PROCESS_RECORD_RETURN_TRUE;
      }

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
        }
        return PROCESS_RECORD_RETURN_FALSE;
    }
    return PROCESS_RECORD_RETURN_TRUE;

    case RTHUM1:
        if (record->event.pressed) {
            if (record->tap.count > 0) {
                if ((isAnyOneShotButShift) || (host_keyboard_led_state().caps_lock) || (caps_word_on) || (xcase_state != 0)) {
                    clear_locked_and_oneshot_mods();
                    disable_caps_word();
                    disable_xcase();
                    dprintln("disable caps_word and xcase");
                      if (host_keyboard_led_state().caps_lock) {
                        dprintln("Disabling Caps Lock under RUTHUM2");
                        tap_code16(KC_CAPS);
                        }
                } else if ((get_mods() & MOD_MASK_SHIFT) || isOneShotShift) {
                    if (xcase_state == XCASE_WAIT) {
                        disable_xcase();
                        disable_caps_word();
                        dprintln("Disabled XCASE and capsword from XWAIT with shift");
                    } else if (xcase_state == XCASE_ON) {
                        disable_xcase();
                        disable_caps_word();
                        dprintln("Disabled XCASE and capsword from XON with shift");
                    } else {
                        enable_xcase();
                        enable_caps_word();
                        dprintln("Enabled XCASE and caps word with shift");
                    }
                } else {
                    if (xcase_state == XCASE_WAIT) {
                        disable_xcase();
                        disable_caps_word();
                        dprintln("Disabled XCASE without shift");
                    } else if (xcase_state == XCASE_ON) {
                        disable_xcase();
                        disable_caps_word();
                        dprintln("Disabled XCASE from XON without shift");
                    } else {
                        enable_xcase();
                        dprintln("Enabled XCASE without shift");
                    }
                }
                return PROCESS_RECORD_RETURN_FALSE;
            }
            return PROCESS_RECORD_CONTINUE;
        }
        break;

        // case CLUTHUM2:
        //   if (record->event.pressed) {
        //     if (record->tap.count > 0) {
        //       if ((isAnyOneShot) || (xcase_state != 0)) {
        //         clear_locked_and_oneshot_mods();
        //         disable_xcase();
        //         dprintln("disable xcase");
        //           if (caps_word_on) {
        //             disable_caps_word();
        //           } else if (host_keyboard_led_state().caps_lock) {
        //             dprintln("disable caps lock 1");
        //             tap_code16(KC_CAPS);
        //           }
        //       } else if (caps_word_on) {
        //         disable_caps_word();
        //         tap_code16(KC_CAPS);
        //         dprintln("enabling Caps Lock");
        //       } else if (host_keyboard_led_state().caps_lock) {
        //         tap_code16(KC_CAPS);
        //         dprintln("disabling caps lock 2");
        //       } else {
        //         enable_caps_word();
        //         dprintln("enabling caps word");
        //       // } else {
        //       //   add_oneshot_mods(MOD_LSFT);
        //       // return PROCESS_RECORD_RETURN_FALSE;
        //       }
        //       return PROCESS_RECORD_RETURN_FALSE;
        //     }
        //   return PROCESS_RECORD_CONTINUE;
        //   }
        // break;


        case LTHUM1:
            if (record->event.pressed) {
                if (record->tap.count > 0) {
                    if (isAnyOneShot) {
                        clear_locked_and_oneshot_mods();
                        dprintln("isAnyOneShotButShift");
                    } else if (caps_word_on) {
                        disable_caps_word();
                        tap_code16(KC_CAPS);
                        dprintln("caps_word_on");
                    } else if (host_keyboard_led_state().caps_lock) {
                        tap_code16(KC_CAPS);
                        dprintln("caps lock off");
                    } else {
                        enable_caps_word();
                        dprintln("enable_caps_word");
                    }
                    return PROCESS_RECORD_RETURN_FALSE;
                }
                return PROCESS_RECORD_CONTINUE;
            }
            break;

        //   if (record->event.pressed) {
        //     if (record->tap.count > 0) {
        //       if (isCtrl) {
        //         enable_caps_word();
        //       }
        //       else if ((isAnyOneShotButShift) || (xcase_state != 0)) {
        //         clear_locked_and_oneshot_mods();
        //         disable_xcase();
        //         dprintln("disable xcase");
        //           if (caps_word_on) {
        //             disable_caps_word();
        //           } else if (host_keyboard_led_state().caps_lock) {
        //             dprintln("disable caps lock 1");
        //             tap_code16(KC_CAPS);
        //           }
        //       } else if (caps_word_on) {
        //         disable_caps_word();
        //         // tap_code16(KC_CAPS);
        //         // dprintln("enabling Caps Lock");
        //       } else if (host_keyboard_led_state().caps_lock) {
        //         tap_code16(KC_CAPS);
        //         dprintln("disabling caps lock 2");
        //       } else if (isOneShotShift || isOneShotLockedShift) {
        //         clear_locked_and_oneshot_mods();
        //         enable_caps_word();
        //         dprintln("enabling caps word");
        //       } else {
        //         add_oneshot_mods(MOD_LSFT);
        //       return PROCESS_RECORD_RETURN_FALSE;
        //       }
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


    // case LOR_THM:
    //     if (record->event.pressed) {
    //         if (record->tap.count > 0) {
    //             if (get_mods() & MOD_MASK_CTRL) {
    //                 unregister_mods(MOD_MASK_CTRL);
    //                 tap_code16(KC_ENTER);
    //             }
    //             else {
    //                 unregister_mods(MOD_MASK_CTRL);
    //                 tap_code16(KC_SPACE);
    //             }
    //             return PROCESS_RECORD_RETURN_FALSE;
    //         }
    //         return PROCESS_RECORD_CONTINUE;
    //     }
    //     break;

    // case UOL_THM:
    //   if (record->event.pressed) {
    //     if (record->tap.count > 0) {
    //         if (get_mods() & MOD_MASK_SHIFT) {
    //             unregister_mods(MOD_MASK_SHIFT);
    //             SEND_STRING("@trueipsolutions.com");
    //         } else {
    //             SEND_STRING("trueipsolutions.com");
    //         }
    //         return PROCESS_RECORD_RETURN_FALSE;
    //     }
    //     return PROCESS_RECORD_CONTINUE;
    // }
    // break;

}

// } Remove quotes and fix curly brackets, if thumb keys don't work.
    return PROCESS_RECORD_CONTINUE;
}

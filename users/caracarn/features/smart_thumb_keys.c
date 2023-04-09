#include QMK_KEYBOARD_H

#include "smart_thumb_keys.h"
#ifdef CASEMODE_ENABLE
    #include "casemodes.h"
#endif

extern os_t           os;

uint8_t smart_mods = 0;
extern enum xcase_state xcase_state;
extern bool caps_word_on;
extern uint16_t idle_timer;

bool should_send_ctrl(bool isWindowsOrLinux, bool isOneShotShift) {
    return (isWindowsOrLinux && !isOneShotShift) || (!isWindowsOrLinux && isOneShotShift);
}

process_record_result_t process_smart_thumb_keys(uint16_t keycode, keyrecord_t *record) {
    bool isWindowsOrLinux    = os.type == WINDOWS || os.type == LINUX;
    bool isOneShotDefaultMod = (!isWindowsOrLinux && (get_oneshot_mods() & MOD_MASK_GUI)) ||
                               (isWindowsOrLinux && (get_oneshot_mods() & MOD_MASK_CTRL));
    bool isOneShotLockedShift = get_oneshot_locked_mods() & MOD_MASK_SHIFT;
    bool isOneShotShift       = get_oneshot_mods() & MOD_MASK_SHIFT || isOneShotLockedShift;
    bool isOneShotCtrl        = get_oneshot_mods() & MOD_MASK_CTRL || get_oneshot_locked_mods() & MOD_MASK_CTRL;
    bool isOneShotAlt         = get_oneshot_mods() & MOD_MASK_ALT || get_oneshot_locked_mods() & MOD_MASK_ALT;
    bool isOneShotGui         = get_oneshot_mods() & MOD_MASK_GUI || get_oneshot_locked_mods() & MOD_MASK_GUI;
    bool isAnyOneShotButShift = isOneShotCtrl || isOneShotAlt || isOneShotGui;
    bool isAnyOneShot         = isOneShotCtrl || isOneShotAlt || isOneShotGui || isOneShotShift;


    switch (keycode) {
        case FUN_XCS:
            if (record->tap.count > 0) {
                if (record->event.pressed) {
                    if (xcase_state == XCASE_WAIT && host_keyboard_led_state().caps_lock) {
                        disable_xcase();
                        disable_caps_word();
                        dprintln("Disabled XCASE and Caps Word");
                    }
                    else if (xcase_state == XCASE_WAIT) {
                        // enable_xcase();
                        enable_caps_word();
                        dprintln("XCASE WAIT, enabled Caps Word");
                    }
                    else if (xcase_state == XCASE_ON) {
                        disable_xcase();
                        disable_caps_word();
                        dprintln("Disable XCASE from ON state");
                    }
                    else {
                      if (get_mods() & MOD_MASK_SHIFT) {
                        enable_xcase_with(OSM(MOD_LSFT));
                      } else {
                        enable_xcase();
                        dprintln("Enabling XCASE to WAIT state");
                    }
                }
              }
                return PROCESS_RECORD_RETURN_FALSE;
            }

          case SFT_NUM:
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


          case SFT_ENT:
      if (record->event.pressed) {
        if (record->tap.count > 0) {
          if (get_mods() & MOD_MASK_CTRL) {
            unregister_mods(MOD_MASK_CTRL);
            tap_code16(KC_ENTER);
          } else {
            dprintln("That's enter now, dummy");
          return PROCESS_RECORD_RETURN_FALSE;
          }
          return PROCESS_RECORD_RETURN_FALSE;
        }
      return PROCESS_RECORD_RETURN_TRUE;
      }

      //     case CAP_SFT:
      // if (record->event.pressed) {
      //   if (record->tap.count > 0) {
      //     if ((isAnyOneShot) || (host_keyboard_led_state().caps_lock) || (caps_word_on) || (xcase_state == (XCASE_ON || XCASE_WAIT))) {
      //       clear_locked_and_oneshot_mods();
      //       disable_caps_word();
      //       disable_xcase();
      //       dprintln("disable caps_word and xcase");
      //         if (host_keyboard_led_state().caps_lock) {
      //           tap_code16(KC_CAPS);
      //         }
      //     } else {
      //         if (get_mods() & MOD_MASK_CTRL) {
      //           tap_code16(KC_CAPS);
      //           dprintln("enable caps lock");
      //         } else if (!caps_word_on) {
      //           enable_caps_word();
      //           dprintln("enable caps_word");
      //         }
      //     return PROCESS_RECORD_RETURN_FALSE;
      //     }
      //     return PROCESS_RECORD_RETURN_FALSE;
      //   }
      // return PROCESS_RECORD_RETURN_TRUE;
      // }
      //
              //     } else if ((caps_word_on) && (xcase_state == (XCASE_WAIT || XCASE_ON))) {
              //       disable_caps_word();
              //       disable_xcase();
              //     } else if 
              //
              //
              //
              //
              //       if (isAnyOneShotButShift || isOneShotLockedShift) {
              //         clear_locked_and_oneshot_mods();
              //       } else if (isOneShotShift) {
              //         clear_locked_and_oneshot_mods();
              //         enable_caps_word();
              //       } else if ((!caps_word_on) && host_keyboard_led_state().caps_lock) {
              //         tap_code16(KC_CAPS);
              //       } else if (caps_word_on) {
              //         clear_locked_and_oneshot_mods();
              //         disable_caps_word();
              //         disable_xcase();
              //       } else {
              //         add_oneshot_mods(MOD_MASK_SHIFT);
              //       }
              //   return PROCESS_RECORD_RETURN_FALSE;
              //   }
              //   return PROCESS_RECORD_RETURN_FALSE;
              //   }
              //   return PROCESS_RECORD_RETURN_TRUE;
              //   }
              // return PROCESS_RECORD_CONTINUE;

    case OPT_PST:
      if (record->tap.count > 0) {
        dprintln("OPT_PST tapped");
        if (record->event.pressed) {
          dprintln("OPT_PST pressed");
          tap_code16(G(KC_V));
        }
        return PROCESS_RECORD_RETURN_FALSE;
      }
      return PROCESS_RECORD_RETURN_TRUE;

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


}

// } Remove quotes and fix curly brackets, if thumb keys don't work.
    return PROCESS_RECORD_CONTINUE;
}

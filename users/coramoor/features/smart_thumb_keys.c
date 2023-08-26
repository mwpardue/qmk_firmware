#include QMK_KEYBOARD_H

#include "smart_thumb_keys.h"
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


    switch (keycode) {
        // case XCASE:
        case UIR_THM:
        if (record->tap.count > 0) {
            if (record->event.pressed) {
                if ((get_mods() & MOD_MASK_SHIFT) || isOneShotShift) {
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
            }
            return PROCESS_RECORD_RETURN_FALSE;
}

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

    case RUTHUM2:
        if (record->tap.count > 0) {
            if (record->event.pressed) {
                tap_code16(S(KC_MINS));
                }
            return PROCESS_RECORD_RETURN_FALSE;
            }

          case LIL_THM:
      if (record->event.pressed) {
        if (record->tap.count > 0) {
          if ((isAnyOneShotButShift) || (isOneShotLockedShift) || (host_keyboard_led_state().caps_lock) || (caps_word_on) || (xcase_state == (XCASE_ON || XCASE_WAIT))) {
            clear_locked_and_oneshot_mods();
            disable_caps_word();
            disable_xcase();
            dprintln("disable caps_word and xcase");
              if (host_keyboard_led_state().caps_lock) {
                tap_code16(KC_CAPS);
              }
          } else if (isOneShotShift) {
            del_oneshot_mods(MOD_LSFT);
            enable_caps_word();
          } else {
            add_oneshot_mods(MOD_LSFT);
          return PROCESS_RECORD_RETURN_FALSE;
          }
          return PROCESS_RECORD_RETURN_FALSE;
        }
      return PROCESS_RECORD_CONTINUE;
      }


}

// } Remove quotes and fix curly brackets, if thumb keys don't work.
    return PROCESS_RECORD_CONTINUE;
}

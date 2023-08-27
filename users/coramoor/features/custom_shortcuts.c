#include QMK_KEYBOARD_H

#include "custom_shortcuts.h"
#include "definitions/keycodes.h"

// extern os_t os;

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

#ifdef CUSTOM_LEADER_ENABLE
  #include "leader.h"
#endif

process_record_result_t process_custom_shortcuts(uint16_t keycode, keyrecord_t *record) {

    bool isMacOS = user_config.os == MACOS;
    bool isWindowsOrLinux = user_config.os == WINDOWS || user_config.os == LINUX;
    bool isOneShotShift = get_oneshot_mods() & MOD_MASK_SHIFT || get_oneshot_locked_mods() & MOD_MASK_SHIFT;
    bool isOneShotCtrl = get_oneshot_mods() & MOD_MASK_CTRL || get_oneshot_locked_mods() & MOD_MASK_CTRL;
    uint8_t smart_mods = 0;

    switch (keycode) {

        // Zoom shortcuts

        case SS_MODP:
            if (record->event.pressed) {
                if (should_send_ctrl(isWindowsOrLinux, isOneShotShift)) {
                    SEND_STRING(SS_LCTL("+"));
                } else {
                    SEND_STRING(SS_LGUI("+"));
                }
            }
            return PROCESS_RECORD_RETURN_FALSE;

        case SS_MODM:
            if (record->event.pressed) {
                if (should_send_ctrl(isWindowsOrLinux, isOneShotShift)) {
                    SEND_STRING(SS_LCTL("-"));
                } else {
                    SEND_STRING(SS_LGUI("-"));
                }
            }
            return PROCESS_RECORD_RETURN_FALSE;

        case QWERTY:
            if (record->event.pressed) {
                dprintf("Base layer changed to QWERTY\n");
                set_single_persistent_default_layer(_BASE);
            }
            return PROCESS_RECORD_RETURN_FALSE;

        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK_DH);
                dprintf("Base layer changed to COLEMAK\n");
            }
            return PROCESS_RECORD_RETURN_FALSE;

    #ifdef SMART_CASE_ENABLE
        case TG_KBAB:
            if (record->event.pressed) {
                if (has_smart_case(KEBAB_CASE) && has_smart_case(WORD_CASE)) {
                    disable_smart_case();
                } else if (has_smart_case(KEBAB_CASE)) {
                    set_smart_case(WORD_CASE);
                } else {
                    set_smart_case(KEBAB_CASE);
                }
            }
            return PROCESS_RECORD_RETURN_FALSE;

        case TG_SNAK:
            if (record->event.pressed) {
                if (has_smart_case(SNAKE_CASE) && has_smart_case(WORD_CASE)) {
                    disable_smart_case();
                } else if (has_smart_case(SNAKE_CASE)) {
                    set_smart_case(WORD_CASE);
                } else {
                    set_smart_case(SNAKE_CASE);
                }
            }
            return PROCESS_RECORD_RETURN_FALSE;

        case TG_CAML:
            if (record->event.pressed) {
                if (has_smart_case(CAMEL_CASE)) {
                    disable_smart_case();
                } else {
                    set_smart_case(CAMEL_CASE);
                }
            }
            return PROCESS_RECORD_RETURN_FALSE;
    #endif

        case NAV_LFT:
          if (record->event.pressed) {
            smart_mods = get_mods();
            if ((smart_mods & MOD_MASK_CTRL) || isOneShotCtrl) {
              unregister_mods(smart_mods);
              del_oneshot_mods(MOD_MASK_CTRL);
              tap_code16(G(KC_LBRC));
              register_mods(smart_mods);
            } else {
              tap_code16(C(S(KC_TAB)));
        }
          return PROCESS_RECORD_RETURN_FALSE;
      }
        return PROCESS_RECORD_RETURN_TRUE;


        case NAV_RGT:
          if (record->event.pressed) {
            smart_mods = get_mods();
            if ((smart_mods & MOD_MASK_CTRL) || isOneShotCtrl) {
              unregister_mods(smart_mods);
              del_oneshot_mods(MOD_MASK_CTRL);
              tap_code16(G(KC_RBRC));
              register_mods(smart_mods);
            } else {
              tap_code16(C(KC_TAB));
        }
          return PROCESS_RECORD_RETURN_FALSE;
      }
        return PROCESS_RECORD_RETURN_TRUE;

        // case ALT_RGT:
        //   if (record->tap.count > 0) {
        //     if (record->event.pressed) {
        //       tap_code16(C(KC_RIGHT));
        //     }
        //     return PROCESS_RECORD_RETURN_FALSE;
        //   }
        //   return PROCESS_RECORD_RETURN_TRUE;

        case LHM_AT:
          if (record->tap.count > 0) {
            if (record->event.pressed) {
              dprintln("KC_AT pressed");
              tap_code16(KC_AT);
            }
            return PROCESS_RECORD_RETURN_FALSE;
          }
          return PROCESS_RECORD_RETURN_TRUE;

        case LHM_BSL:
          if (record->tap.count > 0) {
            if (record->event.pressed) {
              dprintln("KC_AT pressed");
              tap_code16(KC_BSLS);
            }
            return PROCESS_RECORD_RETURN_FALSE;
          }
          return PROCESS_RECORD_RETURN_TRUE;

        case LHM_PIP:
          if (record->tap.count > 0) {
            if (record->event.pressed) {
              dprintln("KC_AT pressed");
              tap_code16(KC_PIPE);
            }
            return PROCESS_RECORD_RETURN_FALSE;
          }
          return PROCESS_RECORD_RETURN_TRUE;

        case LHM_UND:
          if (record->tap.count > 0) {
            if (record->event.pressed) {
              dprintln("KC_AT pressed");
              tap_code16(KC_UNDS);
            }
            return PROCESS_RECORD_RETURN_FALSE;
          }
          return PROCESS_RECORD_RETURN_TRUE;

#ifdef CUSTOM_LEADER_ENABLE
       case LEADER:
            if (record->event.pressed) {
                dprintln("calling start_leading from LEADER");
                start_leading();
                return PROCESS_RECORD_RETURN_FALSE;
            }
            return PROCESS_RECORD_RETURN_TRUE;
#endif

       case UOR_THM:
       case PASSPAL:
            if (record->event.pressed) {
                dprintln("PASSPAL pressed");
                if (record->tap.count > 0) {
                  dprintln("PASSPAL tapped");
                  tap_code16(C(A(G(S(KC_P)))));
                  add_oneshot_mods(MOD_LCTL);
                  return PROCESS_RECORD_RETURN_FALSE;
                  }
             return PROCESS_RECORD_CONTINUE;
             }
         return PROCESS_RECORD_RETURN_TRUE;

        case SFT_TTP:
            if (record->event.pressed) {
                sft_tapping_term = sft_tapping_term + 5;
                dprintf("Shift Tapping Term = %d\n", sft_tapping_term);
                return PROCESS_RECORD_RETURN_FALSE;
            }

        case SFT_TTM:
            if (record->event.pressed) {
                sft_tapping_term = sft_tapping_term - 5;
                dprintf("Shift Tapping Term = %d\n", sft_tapping_term);
                return PROCESS_RECORD_RETURN_FALSE;
            }

        case MDT_TTP:
            if (record->event.pressed) {
                modtap_tapping_term = modtap_tapping_term + 5;
                dprintf("Mod-Tap Tapping Term = %d\n", modtap_tapping_term);
                return PROCESS_RECORD_RETURN_FALSE;
            }

        case MDT_TTM:
            if (record->event.pressed) {
                modtap_tapping_term = modtap_tapping_term - 5;
                dprintf("Mod-Tap Tapping Term = %d\n", modtap_tapping_term);
                return PROCESS_RECORD_RETURN_FALSE;
            }

        case ACH_TTP:
            if (record->event.pressed) {
                achordion_tapping_term = achordion_tapping_term + 50;
                dprintf("Achordion Tapping Term = %d\n", achordion_tapping_term);
                return PROCESS_RECORD_RETURN_FALSE;
            }

        case ACH_TTM:
            if (record->event.pressed) {
                achordion_tapping_term = achordion_tapping_term - 50;
                dprintf("Achordion Tapping Term = %d\n", achordion_tapping_term);
                return PROCESS_RECORD_RETURN_FALSE;
            }

        case GQT_TTP:
            if (record->event.pressed) {
                gqt_tapping_term = gqt_tapping_term + 5;
                dprintf("GQT Tapping Term = %d\n", gqt_tapping_term);
                return PROCESS_RECORD_RETURN_FALSE;
            }

        case GQT_TTM:
            if (record->event.pressed) {
                gqt_tapping_term = gqt_tapping_term - 5;
                dprintf("GQT Tapping Term = %d\n", gqt_tapping_term);
                return PROCESS_RECORD_RETURN_FALSE;
            }

        case SGT_TTP:
            if (record->event.pressed) {
                sgqt_tapping_term = sgqt_tapping_term + 5;
                dprintf("SGQT Tapping Term = %d\n", sgqt_tapping_term);
                return PROCESS_RECORD_RETURN_FALSE;
            }

        case SGT_TTM:
            if (record->event.pressed) {
                sgqt_tapping_term = sgqt_tapping_term - 5;
                dprintf("SGQT Tapping Term = %d\n", sgqt_tapping_term);
                return PROCESS_RECORD_RETURN_FALSE;
            }

         case SEL_WRD:
            if (record->event.pressed) {
                if (isMacOS) {
                  tap_code16(A(KC_LEFT));
                  tap_code16(A(S(KC_RIGHT)));
                } else {
                    tap_code16(C(KC_LEFT));
                    tap_code16(C(S(KC_RIGHT)));
                }
            return PROCESS_RECORD_RETURN_FALSE;
            }

         case SEL_LIN:
            if (record->event.pressed) {
                if (isMacOS) {
                  tap_code16(G(KC_LEFT));
                  tap_code16(G(S(KC_RIGHT)));
                } else {
                    tap_code16(KC_HOME);
                    tap_code16(S(KC_END));
                }
            return PROCESS_RECORD_RETURN_FALSE;
            }

         case S_ARRNG:
            if (record->event.pressed) {
              tap_code16(C(A(G(S(KC_RBRC)))));
            return PROCESS_RECORD_RETURN_FALSE;
            }

         case DF_TOGG:
            if (record->event.pressed) {
              if (default_layer_state == 1 << _COLEMAK_DH) {
                dprintln("set to qwerty");
                set_single_persistent_default_layer(_BASE);
        } else {
                dprintln("set to colemak");
                set_single_persistent_default_layer(_COLEMAK_DH);
        }
            return PROCESS_RECORD_RETURN_FALSE;
            }

         case SM_SWIT:
            if (record->event.pressed) {
              register_mods(MOD_MASK_GUI);
              tap_code16(KC_TAB);
            } else {
              unregister_mods(MOD_MASK_GUI);
              }
            return PROCESS_RECORD_RETURN_FALSE;

        case TG_OS:
            if (record->event.pressed) {
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
            return PROCESS_RECORD_RETURN_FALSE;
            }

        case KIT_MOD:
            if (record->event.pressed) {
                register_mods(MOD_MASK_CS);
            } else {
                unregister_mods(MOD_MASK_CS);
            }

        return PROCESS_RECORD_RETURN_FALSE;

        case ADJ_LYR:
            if (record->event.pressed) {
                user_config.rgb_menu_selector = 0;
                layer_on(_ADJUST);
                return PROCESS_RECORD_RETURN_FALSE;
            }

    }
    return PROCESS_RECORD_CONTINUE;
}

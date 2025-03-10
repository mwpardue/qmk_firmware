#include QMK_KEYBOARD_H

#include "custom_shortcuts.h"
#include "coramoor_runtime.h"
#include "definitions/keycodes.h"
#include "features/qhelper.h"
#ifdef QMENU_ENABLE
#include "features/qpainter.h"
#endif

#ifdef CUSTOM_LEADER_ENABLE
  #include "leader.h"
#endif

#ifdef CASEMODE_ENABLE
    #include "casemodes.h"
#endif

extern enum xcase_state xcase_state;
extern bool caps_word_on;

process_record_result_t process_custom_shortcuts(uint16_t keycode, keyrecord_t *record) {

    bool isMacOS = user_config.menu.os == MACOS;
    bool isOneShotLockedShift = get_oneshot_locked_mods() & MOD_MASK_SHIFT;
    bool isOneShotLockedCtrl = get_oneshot_locked_mods() & MOD_MASK_CTRL;
    bool isOneShotLockedAlt = get_oneshot_locked_mods() & MOD_MASK_ALT;
    bool isOneShotLockedGui = get_oneshot_locked_mods() & MOD_MASK_GUI;
    bool isAnyOneShotLockedMod = isOneShotLockedShift || isOneShotLockedCtrl || isOneShotLockedAlt || isOneShotLockedGui;
    bool kbFeature = caps_word_on || xcase_state == XCASE_ON || xcase_state == XCASE_WAIT || isAnyOneShotLockedMod || is_leading() || host_keyboard_led_state().caps_lock || is_passing();

    switch (keycode) {

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

        case DF_LAYR:
            if (record->event.pressed) {
                switch (get_highest_layer(default_layer_state)) {
                    case _BASE:
                        set_single_persistent_default_layer(_COLEMAK_DH);
                        break;
                    case _COLEMAK_DH:
                        set_single_persistent_default_layer(_BASE);
                        break;
                    default:
                        set_single_persistent_default_layer(_BASE);
                        break;
                }
            }
            return PROCESS_RECORD_RETURN_FALSE;

       case PASSPAL:
        case LALT_PP:
        case RALT_PP:
            if (record->event.pressed) {
                if (record->tap.count > 0) {
                  start_pass_leading();
                    return PROCESS_RECORD_RETURN_FALSE;
                }
            return PROCESS_RECORD_CONTINUE;
            }
            break;

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

         // case CAPLOCK:
         //    if (record->event.pressed) {
         //        tap_code16(KC_CAPS);
         //        lcd_dirty = true;
         //    return PROCESS_RECORD_RETURN_FALSE;
         //    }
         //    break;
         //
         // case CAPWORD:
         //    if (record->event.pressed) {
         //        if (caps_word_on) {
         //            disable_caps_word();
         //            dprintln("CAPWORD disable caps word");
         //        } else {
         //            enable_caps_word();
         //            dprintln("CAPWORD enable caps word");
         //        }
         //    return PROCESS_RECORD_RETURN_FALSE;
         //    }
         //    break;
         //
         // case XCASE:
         //    if (record->event.pressed) {
         //        switch (xcase_state) {
         //            case XCASE_WAIT:
         //                disable_xcase();
         //                disable_caps_word();
         //                break;
         //            case XCASE_ON:
         //                disable_caps_word();
         //                disable_xcase();
         //                break;
         //            default:
         //                enable_xcase();
         //                break;
         //        }
         //    return PROCESS_RECORD_RETURN_FALSE;
         //    }
         //
         // case XCSTRG:
         //    if (record->event.pressed) {
         //        switch (xcase_state) {
         //            case XCASE_WAIT:
         //                disable_xcase();
         //                disable_caps_word();
         //                break;
         //            case XCASE_ON:
         //                disable_caps_word();
         //                disable_xcase();
         //                break;
         //            default:
         //                enable_xcase();
         //                enable_caps_word();
         //                break;
         //        }
         //    return PROCESS_RECORD_RETURN_FALSE;
         //    }

         case SM_SWIT: if (record->event.pressed) {
              layer_on(_APPSWITCH);
              register_mods(MOD_MASK_GUI);
              tap_code16(KC_TAB);
            } else {
              layer_off(_APPSWITCH);
              unregister_mods(MOD_MASK_GUI);
              }
            return PROCESS_RECORD_RETURN_FALSE;
            break;

        // case GUI_ESC:
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
            }
            return PROCESS_RECORD_RETURN_FALSE;
        break;

        case TG_OS:
            if (record->event.pressed) {
                switch (user_config.menu.os) {

                    case MACOS:
                        user_config.menu.os = WINDOWS;
                        SEND_STRING("win");
                        eeconfig_update_user_datablock(&user_config);
                        break;

                    case WINDOWS:
                        user_config.menu.os = LINUX;
                        SEND_STRING("lin");
                        eeconfig_update_user_datablock(&user_config);
                        break;

                    case LINUX:
                        user_config.menu.os = MACOS;
                        SEND_STRING("mac");
                        eeconfig_update_user_datablock(&user_config);
                        break;

                }
            return PROCESS_RECORD_RETURN_FALSE;
            }

        case ADJ_LYR:
            if (record->event.pressed) {
                #ifdef QMENU_ENABLE
                    user_config.menu.menu_selector = 1;
                    user_config.menu.submenu_selector = 1;
                    qp_clear(lcd_surface);
                #endif
                layer_on(_ADJUST);
                return PROCESS_RECORD_RETURN_FALSE;
            }
        return PROCESS_RECORD_RETURN_TRUE;

        case ADJ_EXT:
            if (record->event.pressed) {
                #ifdef HLC_TFT_DISPLAY
                    if (user_runtime_state.kb.write_to_eeprom) {
                        painter_sethsv(painter_get_hue(true), painter_get_sat(true), painter_get_val(true), true);
                        painter_sethsv(painter_get_hue(false), painter_get_sat(false), painter_get_val(false), false);
                        user_runtime_state.kb.write_to_eeprom = false;
                    }
                #endif
                layer_off(_ADJUST);
                return PROCESS_RECORD_RETURN_FALSE;
            }
        return PROCESS_RECORD_RETURN_TRUE;

    }
    return PROCESS_RECORD_CONTINUE;
}

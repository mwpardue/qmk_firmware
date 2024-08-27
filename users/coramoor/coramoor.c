#include "coramoor.h"
#ifdef RAW_ENABLE
    #include "raw_hid.h"
#endif
#include "trackball.h"

#ifdef CAPITALIZE_KEY_ENABLE
    #ifdef SMART_THUMB_KEYS_ENABLE
        #error Do not enable both Capitalize Key and Smart Thumb Key
    #endif
#endif

// static uint16_t next_keycode;
// static keyrecord_t next_record;

_Static_assert(sizeof(user_config_t) == sizeof(uint32_t), "user_config_t is oversize!");
_Static_assert(sizeof(kb_state_t) <= sizeof(uint32_t), "kb_state_t is oversize!");

void                       keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
    kb_state.raw = eeconfig_read_user();

#if defined(SPLIT_KEYBOARD) && defined(SPLIT_TRANSACTION_IDS_USER)
    keyboard_post_init_transport_sync();
#endif
}

__attribute__((weak)) void eeconfig_init_keymap(void) {}
void                       eeconfig_init_user(void) {
    user_config.raw              = 0;
    user_config.os = MACOS;
    user_config.auto_mouse_time = 300;
    set_auto_mouse_timeout(user_config.auto_mouse_time);
    eeconfig_update_user(user_config.raw);
    eeconfig_init_keymap();
}

void matrix_init_user(void) {
    // Enable or disable debugging
    debug_enable=true;
}

#ifdef RAW_ENABLE
void raw_hid_receive(uint8_t *data, uint8_t length) {
  raw_hid_send(data, length);
  // Your code goes here. data is the packet received from host.
}
#endif


// Matrix scan

__attribute__ ((weak)) void matrix_scan_keymap(void) {
}

void matrix_scan_user(void) {
#ifdef ACHORDION_ENABLE
    achordion_task();
#endif

#ifdef SMART_CASE_ENABLE
    check_disable_smart_case();
#endif

#ifdef CAPSLOCK_TIMER_ENABLE
    check_disable_capslock();
#endif

#ifdef CASEMODE_ENABLE
  caps_word_idle_timer();
#endif

#if LAYER_LOCK_IDLE_TIMEOUT > 0
    layer_lock_task();
#endif

#ifdef CAPSWORD_ENABLE
    caps_word_task();
#endif

#ifdef CUSTOM_ONESHOT_MODS_ENABLE
    check_oneshot_mods_timeout();
#endif

    matrix_scan_keymap();
}

#ifdef ACHORDION_ENABLE

uint16_t achordion_tapping_term = ACHORDION_TAPPING_TERM;

uint16_t get_achordion_tapping_term(void) {
    return achordion_tapping_term;
}

 bool achordion_chord(uint16_t tap_hold_keycode,
                      keyrecord_t* tap_hold_record,
                      uint16_t other_keycode,
                      keyrecord_t* other_record) {
  // Exceptionally consider the following chords as holds, even though they
  // are on the same hand in Dvorak.
  switch (tap_hold_keycode) {
    case LHM_V: //F   + W, Q
      if ((other_keycode == KC_W) || (other_keycode == KC_LEFT) || (other_keycode == KC_RIGHT) || (other_keycode == KC_DOWN) || (other_keycode == KC_UP) || (other_keycode == KC_Q) || (other_keycode == QK_GESC)) {return true;}
    case LHM_X:
      if ((other_keycode == LTHUM1 ) || (other_keycode == KC_LEFT) || (other_keycode == KC_RIGHT) || (other_keycode == KC_DOWN) || (other_keycode == KC_UP) || (other_keycode == LTHUM4)) {return true;}
    case LHM_Z:
      if ((other_keycode == LTHUM2) || (other_keycode == KC_LEFT) || (other_keycode == KC_RIGHT) || (other_keycode == KC_DOWN) || (other_keycode == KC_UP)) {return true;}
    case LHM_C:
      if ((other_keycode == LTHUM2) || (other_keycode == KC_LEFT) || (other_keycode == KC_RIGHT) || (other_keycode == KC_DOWN) || (other_keycode == KC_UP)) {return true;}
    case RHM_M:
      if ((other_keycode == KC_LEFT) || (other_keycode == KC_RIGHT) || (other_keycode == KC_DOWN) || (other_keycode == KC_UP)) {return true;}
    case RHM_COM:
      if ((other_keycode == KC_LEFT) || (other_keycode == KC_RIGHT) || (other_keycode == KC_DOWN) || (other_keycode == KC_UP)) {return true;}
    case RHM_DOT:
      if ((other_keycode == KC_LEFT) || (other_keycode == KC_RIGHT) || (other_keycode == KC_DOWN) || (other_keycode == KC_UP)) {return true;}
    case RHM_SLS:
      if ((other_keycode == KC_LEFT) || (other_keycode == KC_RIGHT) || (other_keycode == KC_DOWN) || (other_keycode == KC_UP)) {return true;}
    case LHM_T: //F   + W, Q
      if ((other_keycode == KC_W) || (other_keycode == KC_LEFT) || (other_keycode == KC_RIGHT) || (other_keycode == KC_DOWN) || (other_keycode == KC_UP) || (other_keycode == KC_Q) || (other_keycode == QK_GESC)) {return true;}
    case LHM_R:
      if ((other_keycode == LTHUM1 ) || (other_keycode == KC_LEFT) || (other_keycode == KC_RIGHT) || (other_keycode == KC_DOWN) || (other_keycode == KC_UP) || (other_keycode == LTHUM4)) {return true;}
    case LHM_A:
      if ((other_keycode == LTHUM2) || (other_keycode == KC_LEFT) || (other_keycode == KC_RIGHT) || (other_keycode == KC_DOWN) || (other_keycode == KC_UP)) {return true;}
    case LHM_S:
      if ((other_keycode == LTHUM2) || (other_keycode == KC_LEFT) || (other_keycode == KC_RIGHT) || (other_keycode == KC_DOWN) || (other_keycode == KC_UP)) {return true;}
    case RHM_N:
      if ((other_keycode == KC_LEFT) || (other_keycode == KC_RIGHT) || (other_keycode == KC_DOWN) || (other_keycode == KC_UP)) {return true;}
    case RHM_E:
      if ((other_keycode == KC_LEFT) || (other_keycode == KC_RIGHT) || (other_keycode == KC_DOWN) || (other_keycode == KC_UP)) {return true;}
    case RHM_I:
      if ((other_keycode == KC_LEFT) || (other_keycode == KC_RIGHT) || (other_keycode == KC_DOWN) || (other_keycode == KC_UP)) {return true;}
    case RHM_O:
      if ((other_keycode == KC_LEFT) || (other_keycode == KC_RIGHT) || (other_keycode == KC_DOWN) || (other_keycode == KC_UP)) {return true;}
    // case SFT_5: //Shift + XCS_SFT
    //   if (other_keycode == XCASE || other_keycode == XCS_SFT || other_keycode == (XCASE & 0xff)) {return true;}
      break;
  }

  // Also allow same-hand holds when the other key is in the rows below the
  // alphas. I need the `% (MATRIX_ROWS / 2)` because my keyboard is split.
  #ifdef SPLIT_KEYBOARD
    //if (tap_hold_keycode->event.key.row % (MATRIX_ROWS / 2) >= 4) { return true; }
  #endif
  // Otherwise, follow the opposite hands rule.
  return achordion_opposite_hands(tap_hold_record, other_record);
  dprintf("Achordion opposite hands\n");
}

  uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
   switch (tap_hold_keycode) {
    // case BSP_SYM:
    // case ENT_HYP:
    case SPC_HYP:
    case SFT_FUN:
    case LTHUM5:
    case LTHUM3:
    case LTHUM4:
    case LTHUM1:
    case LTHUM2:
    case RTHUM2:
    case RTHUM1:
    case RTHUM3:
    case HYP_TAB:
    case SFT_MIN:
    case CTL_QUO:
    case GUI_BSP:
    case ALT_MIN:
    case CTL_BSP:
    case CTL_TAB:
    case MED_Z:
    case SFT_Z:
    case SFT_QUE:
    case LHM_Z:
    case RHM_SLS:
    case RHM_O:
    case CTL_CW:
    case GUI_CW:
    case SFT_CW:
    case LHM_MNL:
    case LHM_MNR:
    case GUI_SLS:
       return 0;  // Bypass Achordion for these keys.
       dprintln("Bypassing achordion for timeout");
   }

   return get_achordion_tapping_term();  // Otherwise use a timeout of 800 ms.
   dprintln("Using achordion 800ms timeout");
 }
#endif

// Process record

bool use_default_xcase_separator(uint16_t keycode, const keyrecord_t *record) {
    // for example:
    switch (keycode) {
        case SP_CAP:
        case LTHUM4:
        case LTHUM2:
        case RTHUM3:
        case XCASE:
        case (XCASE & 0xff):
            return false;
         case KC_A ... KC_Z:
         case KC_1 ... KC_0:
          dprintf("default xcase separator from coramoor\n");
             return true;
         // case (XCASE & 0xff):
         // case XCASE:
         // case BSP_SYM:
         default:
            return false;
     }
    return false;
}

#ifdef DYNAMIC_MACRO_ENABLE
    bool is_dynamic_recording = false;

    void dynamic_macro_record_start_user(int8_t direction) {
        is_dynamic_recording = true;
    }

    void dynamic_macro_record_end_user(int8_t direction) {
        is_dynamic_recording = false;
    }
#endif

// Gloal quick-tap
// #ifdef QT_ENABLE

//     bool pre_process_record_user(uint16_t keycode, keyrecord_t *record) {
//     #define IS_HOMEROW(r) (r->event.key.row == 1 || r->event.key.row == 5)
//
//     static uint16_t prev_keycode;
//     if (record->event.pressed) {
//         // Store the previous keycode for instant tap decision
//         prev_keycode = next_keycode;
//         // Cache the next input for mod-tap decisions
//         next_keycode = keycode;
//         next_record  = *record;
//     }
//
//     // Match home row mod-tap keys when it is not preceded by a Layer key
//     if (IS_HOMEROW(record) && IS_QK_MOD_TAP(keycode) && !IS_QK_LAYER_TAP(prev_keycode) && (last_input_activity_elapsed() > COMBO_TERM)) {
//         dprintln("Inside pre_process_record_user function.");
//         // Tap the mod-tap key instantly when it follows a short interval
//         if (record->event.pressed && (last_input_activity_elapsed() < GQT_TAPPING_TERM)) {
//             record->keycode = keycode & 0xff;
//             action_tapping_process(*record);
//             dprintln("Registering tap action due to short interval");
//             return false;
//         } else { // Send the base keycode key up event
//             keyrecord_t base_record   = *record;
//             base_record.keycode       = keycode & 0xff;
//             base_record.event.pressed = false;
//             action_tapping_process(base_record);
//             dprintln("Registering tap action on long interval");
//         }
//     }
//     return true;
// }
// #endif

void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}

    bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record) {
        switch(keycode) {
            case DRGSCRL:
            case SNIPING:
            case PNTVOLM:
            case PNTCART:
            case PNTBROW:
            case PNTMON:
                return true;
            default:
                return false;
        }
        return  is_mouse_record_user(keycode, record);
    }

    layer_state_t layer_state_set_user(layer_state_t state) {
        pointing_mode_reset();
        switch(get_highest_layer(state)) {
            case _NAVIGATION:  // Navigation layer
                set_pointing_mode_id(PM_DRAG);
                break;
            case _MEDIA: // Media control layer
                set_pointing_mode_id(PM_VOL);
                break;
            case _NUMPAD:
                set_pointing_mode_id(PM_CARET);
                break;
        }
        #ifdef CHARYBDIS_POINTING
            if (get_highest_layer(state) == _NAVIGATION) {
                charybdis_set_pointer_dragscroll_enabled(true);
            } else {
                charybdis_set_pointer_dragscroll_enabled(false);
            }
        #endif //CHARYBDIS_POINTING
        return state;
    }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CUSTOM_LEADER_ENABLE
//   switch (process_custom_leader(keycode, record)) {
//         case PROCESS_RECORD_RETURN_TRUE:
//             return true;
//         case PROCESS_RECORD_RETURN_FALSE:
//             return false;
//         default:
//             break;
//     };
  if (!process_leader(keycode, record)) { return false; }
#endif

#ifdef COMBO_ENABLE
    // Process combos
    switch (process_combos(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

#ifdef ACHORDION_ENABLE
    if (!process_achordion(keycode, record)) { return false; }
#endif

#ifdef CAPSWORD_ENABLE
    if (!process_caps_word(keycode, record)) { return false; }
#endif

#ifdef LAYER_LOCK_ENABLE
      if (!process_layer_lock(keycode, record, LLOCK)) { return false; }
#endif

#ifdef GQT_ENABLE
  if (!process_global_quick_tap(keycode, record)) { return false; }
#endif

#ifdef SMART_THUMB_KEYS_ENABLE
  // Process smart thumb keys
  switch (process_smart_thumb_keys(keycode, record)) {
    case PROCESS_RECORD_RETURN_TRUE:
      return true;
    case PROCESS_RECORD_RETURN_FALSE:
      return false;
    default:
      break;
  };
#endif

#ifdef SMART_CASE_ENABLE
        // Process smart case
    switch (process_smart_case(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

#ifdef CASEMODE_ENABLE
    // Process case modes
    if (!process_case_modes(keycode, record)) { return false; }
#endif

#ifdef CAPSLOCK_TIMER_ENABLE
    // Extend capslock timer
     switch (process_capslock_timer_extension(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

#ifdef SECRETS_ENABLE
    // Process secrets
     switch (process_secrets(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

#ifdef WINDOW_SWAPPER_ENABLE
    // Process window swapper
    switch (process_window_swapper(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

#ifdef OLED_MENU_ENABLE
    // Process RGB Toggle Key
    switch (process_oled_menu_keys(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

#ifdef CUSTOM_SHIFT_ENABLE
    // Process custom_shift
   switch (process_custom_shift(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

#ifdef SHORTCUTS_ENABLE
    // Process custom_shortcuts
    switch (process_custom_shortcuts(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

#ifdef MACRO_ENABLE
    // Process macros
    switch (process_macros(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

#ifdef SELECT_WORD_ENABLE
    // Process select word
    switch (process_select_word(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

#ifdef EOS_ENABLE
    process_eos(keycode, record);
#endif

#ifdef DEFAULT_MOD_ENABLE
    // Process default modifier key
    switch (process_default_mod_key(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

#ifdef CAPITALIZE_KEY_ENABLE
     // Process capitalize key
    switch (process_capitalize_key(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

#ifdef OS_TOGGLE_ENABLE
    // Process OS toggle
    switch (process_os_toggle(keycode, record)) {
        case PROCESS_RECORD_RETURN_TRUE:
            return true;
        case PROCESS_RECORD_RETURN_FALSE:
            return false;
        default:
            break;
    };
#endif

  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    if (debug_enable) {
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
    };
#endif
    return true;
}

// Tap-hold configuration

#ifdef TAPHOLD_ENABLE
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    return get_hold_on_other_key_press_result(keycode);
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    return get_tapping_force_hold_result(keycode);
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    return get_permissive_hold_result(keycode);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    return get_tapping_term_result(keycode);
}
#endif

__attribute__((weak)) void housekeeping_task_keymap(void) {}
void housekeeping_task_user(void) {
#if defined(SPLIT_KEYBOARD) && defined(SPLIT_TRANSACTION_IDS_USER)
    housekeeping_task_transport_sync();
#endif
    housekeeping_task_keymap();
}

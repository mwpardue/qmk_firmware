#include "caracarn.h"
#ifdef RAW_ENABLE
    #include "raw_hid.h"
#endif

#ifdef CAPITALIZE_KEY_ENABLE
    #ifdef SMART_THUMB_KEYS_ENABLE
        #error Do not enable both Capitalize Key and Smart Thumb Key
    #endif
#endif

void keyboard_pre_init_user(void) {
  #ifdef CONVERT_TO_BONSAI_C4
    setPinOutput(PAL_LINE(GPIOB, 0));
    writePinHigh(PAL_LINE(GPIOB, 0));
  #endif
  #ifdef CONVERT_TO_HELIOS
    setPinInput(23U);
    setPinInput(21U);
  #endif
    // setPinInput(PAL_LINE(GPIOA, 9));
    // setPinOutput(B0);
    // writePinHigh(B0);
    user_config.raw = eeconfig_read_user();
    oled_clear();
}

void                       keyboard_post_init_user(void) {
#if defined(SPLIT_KEYBOARD) && defined(SPLIT_TRANSACTION_IDS_USER)
    keyboard_post_init_transport_sync();
    rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
#endif
}

__attribute__((weak)) void eeconfig_init_keymap(void) {}
void                       eeconfig_init_user(void) {
    user_config.raw              = 0;
    user_config.rgb_matrix_ledmap_active = false;
    user_config.rgb_matrix_heatmap_area = 40;
    user_config.rgb_matrix_heatmap_spread = 35;
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
 bool achordion_chord(uint16_t tap_hold_keycode,
                      keyrecord_t* tap_hold_record,
                      uint16_t other_keycode,
                      keyrecord_t* other_record) {
  // Exceptionally consider the following chords as holds, even though they
  // are on the same hand in Dvorak.
  switch (tap_hold_keycode) {
    case GUI_F: //F   + W, Q
      if (other_keycode == KC_W || other_keycode == KC_Q) {return true;}
    case CTL_S:
      if (other_keycode == SFT_NUM) {return true;}
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
     case FUN_XCS:
     case ESC_CTL:
     case ESC_MEH:
     case BSP_SYM:
     case SFT_BSP:
     case SPCSFT:
     case TAB_NAV:
     case ENT_NAV:
     case ENT_MEH:
     case ENT_HYP:
     case SPC_HYP:
     case SFT_NUM:
     case SPC_MAC:
     case SFT_FUN:
     case SPC_SYM:
     case TAB_MEH:
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
         case KC_A ... KC_Z:
         case KC_1 ... KC_0:
          dprintf("default xcase separator from caracarn\n");
             return true;
         // case (XCASE & 0xff):
         // case XCASE:
         case TAB_NAV:
         case ENT_NAV:
         case BSP_SYM:
         case SFT_BSP:
         case SFT_NUM:
         case SP_CAP:
         case ALT_M:
         case ALT_V:
         default:
            return false;
     }
    return false;
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

#ifdef GQT_ENABLE
  if (!process_global_quick_tap(keycode, record)) { return false; }
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


// #ifdef CASEMODE_ENABLE
//     // Process case modes
//     if (!process_case_modes(keycode, record)) { return false; }
// #endif

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

// #ifdef CASEMODE_ENABLE
//         // Process smart case
//     switch (process_case_modes(keycode, record)) {
//         case PROCESS_RECORD_RETURN_TRUE:
//             return true;
//         case PROCESS_RECORD_RETURN_FALSE:
//             return false;
//         default:
//             break;
//     };
// #endif

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

#ifdef RGB_MATRIX_ENABLED
    // Process RGB Toggle Key
    switch (process_rgb_matrix_keys(keycode, record)) {
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

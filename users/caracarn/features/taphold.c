#include QMK_KEYBOARD_H

#include "taphold.h"
#include "features/custom_shortcuts.h"

uint16_t get_tapping_term_result(uint16_t keycode) {
    switch (keycode) {
        case IL_THUM:
        case BSP_SYM:
        case OR_THUM:
        case ENT_HYP:
        case SPC_HYP:
        case ESC_MEH:
        case OL_THUM:
        case IR_THUM:
        case TD_SNIP:
        case TD_SSFL:
        case TAB_MEH:
            return g_tapping_term + 40;
        case TD_COPY:
        case TD_PAST:
        case FUN_XCS:
        case OSMLSFT:
        case OSMRSFT:
        case OSMLCTL:
        case OSMRCTL:
        case OSMLALT:
        case OSMRALT:
        case OSMLGUI:
        case OSMRGUI:
        case TD_MONL:
        case TD_MONM:
        case TD_MONR:
        case TD_MONB:
          return g_tapping_term + 100;
        case LHM_A:
        case LHM_S:
        case LHM_F:
        case RHM_SCN:
        case RHM_L:
        case RHM_J:
        case CLHM_R: 
        case CLHMT: 
        case CRHM_O: 
        case CRHM_I: 
        case CRHM_N: 
        // case CTL_A:
        // case ALT_S:
        // case LHM_F:
        // case RHM_J:
        // case ALT_L:
        // case CTL_QUO:
        // case RHM_L:
        // case LHM_S:
        // case ALT_V:
        // case ALT_M:
        // case CTL_SCN:
        // case CTL_D:
        // case CTL_K:
        // case LHM_A:
        // case RHM_SCN:
          return get_modtap_tapping_term();
        case RHM_K:
        case LHM_D:
        case CLHM_S: 
        // case SFT_A:
        case CRHM_E: 
        // case SFT_SCN:
            return get_sft_tapping_term();
        default:
            return g_tapping_term;
    }
}

bool get_tapping_force_hold_result(uint16_t keycode) {
    switch (keycode) {
        case BSP_SYM:
        case OR_THUM:
        case IL_THUM:
        case SPC_HYP:
        case ENT_HYP:
        case ESC_MEH:
        case IR_THUM:
        // case CTL_A:
        // case ALT_S:
        // case LHM_D:
        // case LHM_F:
        // case RHM_J:
        // case RHM_K:
        // case ALT_L:
        // case CTL_QUO:
        // case LHM_S:
        // case RHM_L:
        // case ALT_V:
        // case ALT_M:
        // case CTL_SCN:
        // case CTL_D:
        // case CTL_K:
        // case SFT_A:
        // case SFT_SCN:
        // case LHM_A:
        // case RHM_SCN:
        case LHM_A:
        case LHM_S:
        case LHM_F:
        case RHM_SCN:
        case RHM_L:
        case RHM_J:
        case CLHM_R: 
        case CLHMT: 
        case CRHM_O: 
        case CRHM_I: 
        case CRHM_N: 
        case RHM_K:
        case LHM_D:
        case CLHM_S: 
        case CRHM_E: 
            return false;
    }
    switch (keycode) {
        case QK_MOD_TAP...QK_MOD_TAP_MAX:
        case QK_LAYER_TAP...QK_LAYER_TAP_MAX:
        case QK_MOMENTARY...QK_MOMENTARY_MAX:
            return true;
        default:
            return false;
    }
}

bool get_hold_on_other_key_press_result(uint16_t keycode) {
    switch (keycode) {
        case IL_THUM:
        case BSP_SYM:
        case IR_THUM:
        case ENT_HYP:
        case SPC_HYP:
        case SPC_SYM:
        // case OL_THUM:
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            return false;
    }
}

bool get_permissive_hold_result(uint16_t keycode) {
    switch (keycode) {
        case BSP_SYM:
        case OR_THUM:
        case LHM_A:
        case LHM_S:
        case LHM_F:
        case RHM_SCN:
        case RHM_L:
        case RHM_J:
        case CLHM_R: 
        case CLHMT: 
        case CRHM_O: 
        case CRHM_I: 
        case CRHM_N: 
        case RHM_K:
        case LHM_D:
        case CLHM_S: 
        case CRHM_E: 
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}

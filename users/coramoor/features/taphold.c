#include QMK_KEYBOARD_H

#include "taphold.h"
#include "features/custom_shortcuts.h"
#include "features/oled_menu.h"

uint16_t get_tapping_term_result(uint16_t keycode) {
    switch (keycode) {
        // case BSP_SYM:
        // case ENT_HYP:
        case SPC_HYP:
        // case ESC_MEH:
        case LTHUM3:
        case LTHUM4:
        case LTHUM2:
        case RTHUM1:
        case LTHUM1:
        case RTHUM3:
        case SFT_MIN:
        case ALT_MIN:
        case SFT_QUO:
        // case SFT_ENT:
            return g_tapping_term + 40;
        case LTHUM6:
        case LTHUM5:
        case TD_COPY:
        case TD_PAST:
        case OSMLSFT:
        case OSMRSFT:
        case OSMLCTL:
        case OSMRCTL:
        case OSMLALT:
        case OSMRALT:
        case OSMLGUI:
        case OSMRGUI:
        // case TD_MONL:
        // case TD_MONU:
        // case TD_MONR:
        // case TD_MOND:
        case TD_SNIP:
        case TD_SSFL:
        case RTHUM2:
        case LHM_AT:
        case LHM_BSL:
        case LHM_UND:
        case LHM_PIP:
        case TD_QUOT:
        case CTL_BSP:
        case CTL_TAB:
        case CTL_QUO:
        case CTL_CW:
        case SFT_CW:
        case RHM_4:
        case RHM_5:
        case RHM_6:
        case RHM_CLN:
          return g_tapping_term + 100;
        case LHM_A:
        case LHM_S:
        case RHM_SCN:
        case RHM_L:
        case RHM_DOT:
        case LHM_X:
        case MED_Z:
        case RHM_M:
        case LHM_V:
        case LHM_F:
        case RHM_J:
        case LHM_C:
        case RHM_COM:
        // case RHM_K:
        // case LHM_D:
          return get_modtap_tapping_term();
        // case LHM_A:
        // case RHM_SCN:
        case LHM_Z:
        case RHM_SLS:
        case RHM_K:
        case LHM_D:
        case SFT_Z:
        case SFT_QUE:
            return get_sft_tapping_term();
        default:
            return g_tapping_term;
    }
}

bool get_tapping_force_hold_result(uint16_t keycode) {
    switch (keycode) {
        // case BSP_SYM:
        case SPC_HYP:
        // case ENT_HYP:
        // case ESC_MEH:
        case LTHUM3:
        case LTHUM4:
        case LTHUM1:
        case RTHUM2:
        case RTHUM1:
        case RTHUM3:
        case LHM_A:
        case LHM_S:
        case LHM_F:
        case RHM_SCN:
        case RHM_L:
        case RHM_J:
        case RHM_K:
        case LHM_D:
        case RHM_SLS:
        case RHM_DOT:
        case RHM_M:
        case LHM_Z:
        case LHM_X:
        case LHM_V:
        case LHM_C:
        case RHM_COM:
        // case CRTHUM2:
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
        // case BSP_SYM:
        // case ENT_HYP:
        case SPC_HYP:
        case LTHUM3:
        case LTHUM4:
        // case LTHUM1:
        case LTHUM2:
        case RTHUM1:
        case RTHUM3:
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            return false;
    }
}

bool get_permissive_hold_result(uint16_t keycode) {
    switch (keycode) {
        // case BSP_SYM:
        case LHM_A:
        case LHM_S:
        case LHM_F:
        case RHM_SCN:
        case RHM_L:
        case RHM_J:
        case RHM_K:
        case LHM_D:
        case RHM_SLS:
        case RHM_DOT:
        case RHM_M:
        case LHM_Z:
        case LHM_X:
        case LHM_V:
        case LHM_C:
        case RHM_COM:
        case SFT_MIN:
        case ALT_MIN:
        case SFT_QUO:
        case MED_Z:
        case SFT_Z:
        case SFT_QUE:
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}

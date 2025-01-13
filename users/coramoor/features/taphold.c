#include QMK_KEYBOARD_H

#include "taphold.h"
#include "features/custom_shortcuts.h"
#include "features/tapdance.h"

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

uint16_t get_tapping_term_result(uint16_t keycode) {
    switch (keycode) {
        case SPC_HYP:
        case LUTHUM1:
        case LUTHUM2:
        case LOL_THM:
        case LOR_THM:
        case LIL_THM:
        case CLIL_THM:
        case RUTHUM2:
        case RUTHUM1:
        case SFT_MIN:
        case ALT_MIN:
        case SFT_QUO:
            return g_tapping_term + 40;
        case UOR_THM:
        case UIR_THM:
        case UOL_THM:
        case UIL_THM:
        case OSMLSFT:
        case OSMRSFT:
        case OSMLCTL:
        case OSMRCTL:
        case OSMLALT:
        case OSMRALT:
        case OSMLGUI:
        case OSMRGUI:
        // case TD_SNIP:
        // case TD_SHOT:
        case TD_PAST:
        case TD_COPY:
        case LIR_THM:
        case LHM_AT:
        case LHM_BSL:
        case LHM_UND:
        case LHM_PIP:
        // case TD_QUOT:
        case CTL_QUO:
        case CLUTHUM2:
        case CLOL_THM:
        case CRUTHUM2:
        case CLIR_THM:
        case CLOR_THM:
        case CTL_CW:
        case SFT_CW:
        case RHM_CLN:
          return g_tapping_term + 100;
        case LHM_A:
        case LHM_R:
        case RHM_O:
        case RHM_I:
        case RHM_DOT:
        case LHM_X:
        case ASW_Z:
        case RHM_M:
        case LHM_V:
        case LHM_T:
        case RHM_N:
        case LHM_C:
        case RHM_COM:
        // case RHM_E:
        // case LHM_S:
          return get_modtap_tapping_term();
        // case LHM_A:
        // case RHM_O:
        case RHM_E:
        case RHM_K:
        case LHM_S:
        case LHM_Z:
        case RHM_SLS:
        case LQM_S:
        case SFT_Z:
        case SFT_QUE:
            return get_sft_tapping_term();
        default:
            return g_tapping_term;
    }
}

uint16_t get_quick_tap_term_result(uint16_t keycode) {
    switch (keycode) {
        case SPC_HYP:
        case LHM_A:
        case LHM_R:
        case LHM_T:
        case RHM_O:
        case RHM_I:
        case RHM_N:
        case RHM_E:
        case LHM_S:
        case LQM_S:
        case RHM_SLS:
        case RHM_DOT:
        case RHM_M:
        case LHM_Z:
        case LHM_X:
        case LHM_V:
        case LHM_C:
        case RHM_COM:
        case LIL_THM:
        case LOL_THM:
        case LIR_THM:
        case LOR_THM:
            return 0;
    }
    switch (keycode) {
        case QK_MOD_TAP...QK_MOD_TAP_MAX:
        case QK_LAYER_TAP...QK_LAYER_TAP_MAX:
        case QK_MOMENTARY...QK_MOMENTARY_MAX:
        case OSMLSFT:
        case OSMRSFT:
        case OSMLCTL:
        case OSMRCTL:
        case OSMLALT:
        case OSMRALT:
        case OSMLGUI:
        case OSMRGUI:
            return 175;
        default:
            return 0;
    }
}

bool get_hold_on_other_key_press_result(uint16_t keycode) {
    switch (keycode) {
        case SPC_HYP:
        case LUTHUM1:
        case LUTHUM2:
        case UIR_THM:
        case LOL_THM:
        case LOR_THM:
        case RUTHUM2:
        case RUTHUM1:
        case CLUTHUM2:
        case CRUTHUM2:
        case CLOR_THM:
        case CLOL_THM:
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            return false;
    }
}

bool get_permissive_hold_result(uint16_t keycode) {
    switch (keycode) {
        case LHM_A:
        case LHM_R:
        case LHM_T:
        case RHM_O:
        case RHM_I:
        case RHM_N:
        case RHM_E:
        case LHM_S:
        case LQM_S:
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
        case ASW_Z:
        case SFT_Z:
        case SFT_QUE:
        case CRUTHUM2:
        case CLUTHUM2:
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}

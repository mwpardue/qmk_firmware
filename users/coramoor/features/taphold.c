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

#ifdef ACHORDION_ENABLE
uint16_t achordion_tapping_term = ACHORDION_TAPPING_TERM;

uint16_t get_achordion_tapping_term(void) {
    return achordion_tapping_term;
}
#endif

#ifdef GQT_ENABLE
uint16_t gqt_tapping_term = GQT_TAPPING_TERM;

uint16_t get_gqt_tapping_term(void) {
    return gqt_tapping_term;
}

uint16_t sgqt_tapping_term = SGQT_TAPPING_TERM;

uint16_t sget_gqt_tapping_term(void) {
    return sgqt_tapping_term;
}
#endif

uint16_t get_tapping_term_result(uint16_t keycode) {
    switch (keycode) {
        // case SPC_HYP:
        case LUTHUM1:
        case LUTHUM2:
        case LOL_THM:
        case LOR_THM:
        case LIL_THM:
        case CLIL_THM:
        case RUTHUM2:
        case RUTHUM1:
            return g_tapping_term + 40;
        case UOR_THM:
        case UOL_THM:
        case TD_PAST:
        case TD_COPY:
        case LIR_THM:
        case CLUTHUM2:
        case CLOL_THM:
        case CRUTHUM2:
        case CLIR_THM:
        case CLOR_THM:
          return g_tapping_term + 100;
        case LHM_A:
        case LQM_S:
        case LHM_F:
        case RHM_J:
        case RHM_L:
        case RHM_SCN:
        case CTL_Z:
        case ALT_X:
        case GUI_C:
        case CTL_QUE:
        case ALT_DOT:
        case GUI_COM:
          return get_modtap_tapping_term();
        case RHM_K:
        case LHM_D:
            return get_sft_tapping_term();
        default:
            return g_tapping_term;
    }
}

uint16_t get_quick_tap_term_result(uint16_t keycode) {
    switch (keycode) {
        case LHM_A:
        case LQM_S:
        case LHM_F:
        case RHM_SCN:
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
        case LUTHUM1:
        case LUTHUM2:
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
        case LHM_D:
        case LHM_F:
        case RHM_J:
        case RHM_K:
        case RHM_L:
        case RHM_SCN:
        case LQM_S:
        case CRUTHUM2:
        case CLUTHUM2:
        case CTL_Z:
        case ALT_X:
        case GUI_C:
        case CTL_QUE:
        case ALT_DOT:
        case GUI_COM:
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}

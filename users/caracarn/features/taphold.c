#include QMK_KEYBOARD_H

#include "taphold.h"
#include "features/custom_shortcuts.h"

uint16_t get_tapping_term_result(uint16_t keycode) {
    switch (keycode) {
        case ENT_NAV:
        case BSP_SYM:
        case SFT_BSP:
        case ENT_HYP:
        case SPC_HYP:
        case ESC_MEH:
        case SFT_NUM:
        case SPC_MAC:
        case TD_SNIP:
        case TD_SSFL:
        case TD_COPY:
        case TD_PAST:
        case TAB_MEH:
            return g_tapping_term + 40;
        case FUN_XCS:
        case OSMLSFT:
        case OSMRSFT:
        case OSMLCTL:
        case OSMRCTL:
        case OSMLALT:
        case OSMRALT:
        case OSMLGUI:
        case OSMRGUI:
          return g_tapping_term + 100;
        case CTL_A:
        case ALT_S:
        case GUI_F:
        case GUI_J:
        case ALT_L:
        case CTL_QUO:
        case CTL_L:
        case CTL_S:
        case ALT_V:
        case ALT_M:
        case CTL_SCN:
        case CTL_D:
        case CTL_K:
          return get_modtap_tapping_term();
        case SFT_K:
        case SFT_D:
        case SFT_A:
        case SFT_SCN:
            return get_sft_tapping_term();
        default:
            return g_tapping_term;
    }
}

bool get_tapping_force_hold_result(uint16_t keycode) {
    switch (keycode) {
        case BSP_SYM:
        case SFT_BSP:
        case ENT_NAV:
        case SPC_HYP:
        case ENT_HYP:
        case ESC_MEH:
        case SPC_MAC:
        case CTL_A:
        case ALT_S:
        case SFT_D:
        case GUI_F:
        case GUI_J:
        case SFT_K:
        case ALT_L:
        case CTL_QUO:
        case CTL_S:
        case CTL_L:
        case ALT_V:
        case ALT_M:
        case CTL_SCN:
        case CTL_D:
        case CTL_K:
        case SFT_A:
        case SFT_SCN:
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
        case ENT_NAV:
        case BSP_SYM:
        case SFT_BSP:
        case ENT_HYP:
        case SPC_HYP:
        case SPC_SYM:
        case SFT_NUM:
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            return false;
    }
}

bool get_permissive_hold_result(uint16_t keycode) {
    switch (keycode) {
        case SPCSFT:
        case BSP_SYM:
        case SFT_BSP:
        case CTL_A:
        case ALT_S:
        case SFT_D:
        case GUI_F:
        case GUI_J:
        case SFT_K:
        case ALT_L:
        case CTL_QUO:
        case CTL_S:
        case CTL_L:
        case ALT_V:
        case ALT_M:
        case CTL_SCN:
        case SPC_SYM:
        case CTL_D:
        case CTL_K:
        case SFT_A:
        case SFT_SCN:
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}

#include "global_quick_tap.h"
#include "definitions/keycodes.h"

extern uint16_t gqt_tapping_term;

extern uint16_t sgqt_tapping_term;

static struct {
    uint16_t keycode;
    bool disabled;
    bool key_registered;
} gqt_state = {0, false, false};

void reset_global_quick_tap_state(void) {
    gqt_state.keycode = 0;
    gqt_state.disabled = false;
    gqt_state.key_registered = false;
}

static uint16_t prev_press_time = 0;


bool process_global_quick_tap(uint16_t keycode, keyrecord_t* record) {
    const bool is_physical_pos = (record->event.key.row < 254
                                && record->event.key.col < 254);
    if (record->event.pressed && is_physical_pos) {
        /* Any key down. Recording key press times */
        uint16_t time_diff = record->event.time - prev_press_time;
        prev_press_time = record->event.time;

        if (!gqt_state.disabled) {
            uint16_t quick_tap_ms = get_global_quick_tap_ms(keycode);
            if (quick_tap_ms > 0) {
                dprintf("Global-quick-tap: Last key press was %dms ago, global_quick_tap is %dms. ", time_diff, quick_tap_ms);
                if (quick_tap_ms > time_diff) {
                    dprintf("Disabling hold-tap for 0x%04X\n", keycode);
                    register_code16(QK_MOD_TAP_GET_TAP_KEYCODE(keycode));
                    gqt_state.key_registered = true;
                    return false;
                } else {
                    dprintf("Hold-taps and mod combos are allowed for key 0x%04X\n", keycode);
                    gqt_state.disabled = true;
                }
                gqt_state.keycode = keycode;
            }
        }
    } else {
        /* key up. Cleaning up global_quick_tap_state */
        if (keycode == gqt_state.keycode) {
            dprintf("Global-quick-tap: 0x%04X key released. ", keycode);
            if (gqt_state.disabled) {
                dprintf("Resuming global_quick_tap processing\n");
            } else if (gqt_state.key_registered) {
                dprintf("Unregistering key\n");
                unregister_code(QK_MOD_TAP_GET_TAP_KEYCODE(keycode));
            }
            reset_global_quick_tap_state();
        }
    }

    return true;
};

__attribute__((weak))
uint16_t get_global_quick_tap_ms(uint16_t keycode) {
    switch (keycode) {
        /* Example: KEYCODE will not be considered for hold-tap if the last key press was less than 150ms ago */
        /* case KEYCODE: */
        /*     return 150; */
        case LHM_A:
        case LHM_R:
        case LHM_T:
        case RHM_O:
        case RHM_I:
        case RHM_N:
        // case RHM_E:
        // case LHM_S:
          return gqt_tapping_term;
        case LQM_S:
        case RHM_E:
        case RHM_K:
        case LHM_S:
        // case RHM_O:
        // case LHM_A:
          return sgqt_tapping_term;
        case LHM_MNL:
        case LHM_MNR:
        default:
            return 0;  // global_quick_tap is not applied
    }
}

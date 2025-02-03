#include QMK_KEYBOARD_H

#include "tapdance.h"
// #include "secrets.h"
// #include "smart_case.h"
#include "transport_sync.h"
// #ifdef CUSTOM_LEADER_ENABLE
//     #include "features/leader.h"
// #endif

// extern os_t os;

// static uint8_t smart_mods;

static td_tap_t tap_state = {
    .state = TD_NONE
};


__attribute__ ((weak)) td_state_t dance_state(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
};


void td_copy(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            if (user_config.os == MACOS) {
                dprintln("Executing MACOS command");
                tap_code16(G(KC_C));
            } else if (user_config.os == LINUX) {
                dprintln("Executing LINUX command");
                tap_code16(C(S(KC_C)));
            } else {
                dprintln("Executing WINDOWS command");
                tap_code16(C(KC_C));
            }
            break;
        case TD_SINGLE_HOLD:
            if (user_config.os == MACOS) {
                dprintln("Executing MACOS command");
                tap_code16(G(KC_X));
            } else if (user_config.os == LINUX) {
                dprintln("Executing LINUX command");
                tap_code16(C(S(KC_C)));
            } else {
                dprintln("Executing WINDOWS command");
                tap_code16(C(KC_X));
            }
            break;
        default: break;
    }
};

void td_paste(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            if (user_config.os == MACOS) {
                dprintln("Executing MACOS command");
                tap_code16(G(KC_V));
            } else if (user_config.os == LINUX) {
                dprintln("Executing LINUX command");
                tap_code16(C(S(KC_V)));
            } else {
                dprintln("Executing WINDOWS command");
                tap_code16(C(KC_V));
            }
            break;
        case TD_SINGLE_HOLD:
            if (user_config.os == MACOS) {
                dprintln("Executing MACOS command");
                tap_code16(G(A(KC_V)));
            } else if (user_config.os == LINUX) {
                dprintln("Executing LINUX command");
                tap_code16(C(S(KC_V)));
            } else {
                dprintln("Executing WINDOWS command");
                tap_code16(C(KC_V));
            }
            break;
        case TD_DOUBLE_TAP:
            if (user_config.os == MACOS) {
                dprintln("Executing MACOS command");
                tap_code16(G(C(KC_V)));
            } else {
                dprintln("Executing WINDOWS command");
                tap_code16(G(C(KC_V)));
            }
            break;
        default: break;
    }
};

tap_dance_action_t tap_dance_actions[] = {
    [TDCOPY] = ACTION_TAP_DANCE_FN(td_copy),
    [TDPASTE] = ACTION_TAP_DANCE_FN(td_paste)
};

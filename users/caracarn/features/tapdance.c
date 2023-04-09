#include QMK_KEYBOARD_H

#include "tapdance.h"
#include "secrets.h"
#include "smart_case.h"

//extern os_t os;

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
}

// Quotes

void td_quotes(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            if (get_mods() & MOD_MASK_SHIFT) {
                del_mods(MOD_MASK_SHIFT);
                del_weak_mods(MOD_MASK_SHIFT);
                del_oneshot_mods(MOD_MASK_SHIFT);
                tap_code16(KC_SCLN);
            } else {
            tap_code16(KC_QUOT);
            };
            break;
        case TD_DOUBLE_TAP:
            if (get_mods() & MOD_MASK_SHIFT) {
                tap_code16(KC_COLN);
            } else {
            tap_code16(KC_DQUO);
            };
            break;
        default: break;
    }
}

void td_secret15(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            send_string(secrets[0]);
            break;
        case TD_DOUBLE_TAP:
            send_string(secrets[4]);
            break;
        default: break;
    }
}

void td_secret78(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            send_string(secrets[6]);
            break;
        case TD_DOUBLE_TAP:
            send_string(secrets[7]);
            break;
        default: break;
    }
}

void td_secret119(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            send_string(secrets[10]);
            break;
        case TD_DOUBLE_TAP:
            send_string(secrets[8]);
            break;
        default: break;
    }
}

void td_secret310(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            send_string(secrets[2]);
            break;
        case TD_DOUBLE_TAP:
            send_string(secrets[9]);
            break;
        default: break;
    }
}

void td_vimq(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(KC_ESC);
            send_string(":q!");
            break;
        case TD_DOUBLE_TAP:
            tap_code16(KC_ESC);
            send_string(":wq");
            break;
        default: break;
    }
}

void td_copy(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(G(KC_C));
            break;
        case TD_SINGLE_HOLD:
            tap_code16(G(KC_X));
            break;
        default: break;
    }
}

void td_paste(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(G(KC_V));
            break;
        case TD_SINGLE_HOLD:
            tap_code16(G(A(KC_V)));
            break;
        case TD_DOUBLE_TAP:
            tap_code16(G(C(KC_V)));
            break;
        default: break;
    }
}

void td_jumpleft(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(A(KC_LEFT));
            break;
        case TD_DOUBLE_TAP:
            tap_code16(G(KC_LEFT));
            break;
        default: break;
    }
}

void td_jumpright(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code16(A(KC_RIGHT));
            break;
        case TD_DOUBLE_TAP:
            tap_code16(G(KC_RIGHT));
            break;
        default: break;
    }
}

void td_screenshot_full(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
          tap_code16(LGUI(LSFT(LCTL(KC_3))));
          break;
        case TD_SINGLE_HOLD:
          tap_code16(LGUI(LSFT(KC_3)));
          break;
        default: break;
    }
}

void td_screenshot_snippet(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
          tap_code16(LGUI(LSFT(LCTL(KC_4))));
          break;
        case TD_SINGLE_HOLD:
          tap_code16(LGUI(LSFT(KC_4)));
          break;
        default: break;
    }
}

void td_monitor_left(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
          tap_code16(LALT(LSFT(LCTL(KC_4))));
          break;
        case TD_SINGLE_HOLD:
          tap_code16(LGUI(LALT(LSFT(LCTL(KC_4)))));
          break;
        default: break;
    }
}

void td_monitor_middle(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
          tap_code16(LALT(LSFT(LCTL(KC_5))));
          break;
        case TD_SINGLE_HOLD:
          tap_code16(LGUI(LALT(LSFT(LCTL(KC_5)))));
          break;
        default: break;
    }
}

void td_monitor_right(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
          tap_code16(LALT(LSFT(LCTL(KC_6))));
          break;
        case TD_SINGLE_HOLD:
          tap_code16(LGUI(LALT(LSFT(LCTL(KC_6)))));
          break;
        default: break;
    }
}

void td_monitor_bottom(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
          tap_code16(LALT(LSFT(LCTL(KC_1))));
          break;
        case TD_SINGLE_HOLD:
          tap_code16(LGUI(LALT(LSFT(LCTL(KC_1)))));
          break;
        default: break;
    }
}

void td_curly_braces(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
          tap_code16(KC_LCBR);
          break;
        case TD_SINGLE_HOLD:
          tap_code16(KC_LCBR);
          tap_code16(KC_RCBR);
          tap_code16(KC_LEFT);
          break;
        default: break;
    }
}

void td_square_brackets(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
          tap_code16(KC_LBRC);
          break;
        case TD_SINGLE_HOLD:
          tap_code16(KC_LBRC);
          tap_code16(KC_RBRC);
          tap_code16(KC_LEFT);
          break;
        default: break;
    }
}

void td_parentesis(tap_dance_state_t *state, void *user_data) {
    tap_state.state = dance_state(state);
    switch (tap_state.state) {
        case TD_SINGLE_TAP:
          tap_code16(KC_LPRN);
          break;
        case TD_SINGLE_HOLD:
          tap_code16(KC_LPRN);
          tap_code16(KC_RPRN);
          tap_code16(KC_LEFT);
          break;
        default: break;
    }
}
// Tap dance declarations

tap_dance_action_t tap_dance_actions[] = {
    [SEC1_5] = ACTION_TAP_DANCE_FN(td_secret15),
    [SEC7_8] = ACTION_TAP_DANCE_FN(td_secret78),
    [SEC11_9] = ACTION_TAP_DANCE_FN(td_secret119),
    [SEC3_10] = ACTION_TAP_DANCE_FN(td_secret310),
    [TDCOPY] = ACTION_TAP_DANCE_FN(td_copy),
    [TDPASTE] = ACTION_TAP_DANCE_FN(td_paste),
    [TDJLEFT] = ACTION_TAP_DANCE_FN(td_jumpleft),
    [TDJRIGHT] = ACTION_TAP_DANCE_FN(td_jumpright),
    [BRT_CUR] = ACTION_TAP_DANCE_FN(td_curly_braces),
    [BRT_SQR] = ACTION_TAP_DANCE_FN(td_square_brackets),
    [BRT_PAR] = ACTION_TAP_DANCE_FN(td_parentesis),
    // [BRT_ANG] = ACTION_TAP_DANCE_FN(td_angle_brackets),
    [SDB_QUO] = ACTION_TAP_DANCE_FN(td_quotes),
    [SS_FULL] = ACTION_TAP_DANCE_FN(td_screenshot_full),
    [VIMQ] = ACTION_TAP_DANCE_FN(td_vimq),
    [SS_SNIP] = ACTION_TAP_DANCE_FN(td_screenshot_snippet),
    [MONITOR_LEFT] = ACTION_TAP_DANCE_FN(td_monitor_left),
    [MONITOR_RIGHT] = ACTION_TAP_DANCE_FN(td_monitor_right),
    [MONITOR_MIDDLE] = ACTION_TAP_DANCE_FN(td_monitor_middle),
    [MONITOR_BOTTOM] = ACTION_TAP_DANCE_FN(td_monitor_bottom),
};

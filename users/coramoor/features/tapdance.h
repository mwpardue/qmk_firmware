#pragma once

#include QMK_KEYBOARD_H

#include "../definitions/keycodes.h"
/*#include "caps_word.h"*/
/*#include "smart_case.h"*/

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    td_state_t state;
    /*bool recording;*/
} td_tap_t;

enum {
    TDCOPY,
    TDPASTE
};

#define TD_COPY TD(TDCOPY)
#define TD_PAST TD(TDPASTE)

td_state_t dance_state(tap_dance_state_t *state);

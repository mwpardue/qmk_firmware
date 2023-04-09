#pragma once

#include QMK_KEYBOARD_H

#include "../definitions/keycodes.h"
#include "caps_word.h"
#include "smart_case.h"

enum {
    SEC1_5,
    SEC7_8,
    SEC11_9,
    SEC3_10,
    TDCOPY,
    TDPASTE,
    TDJLEFT,
    TDJRIGHT,
    BRT_CUR,
    BRT_SQR,
    BRT_PAR,
    // BRT_ANG,
    SDB_QUO,
    SS_FULL,
    VIMQ,
    SS_SNIP,
    MONITOR_LEFT,
    MONITOR_MIDDLE,
    MONITOR_RIGHT,
    MONITOR_BOTTOM
};

#define TD_S15 TD(SEC1_5)
#define TD_S78 TD(SEC7_8)
#define TD_S119 TD(SEC11_9)
#define TD_S310 TD(SEC3_10)
#define TD_COPY TD(TDCOPY)
#define TD_PAST TD(TDPASTE)
#define TD_JLFT TD(TDJLEFT)
#define TD_JRGT TD(TDJRIGHT)
#define TD_CURB TD(BRT_CUR)
#define TD_SQRB TD(BRT_SQR)
#define TD_PARB TD(BRT_PAR)
// #define TD_ANGB TD(BRT_ANG)
#define TD_QUOT TD(SDB_QUO)
#define TD_SSFL TD(SS_FULL)
#define TD_SNIP TD(SS_SNIP)
#define TD_VIMQ TD(VIMQ)
#define TD_MONL TD(MONITOR_LEFT)
#define TD_MONR TD(MONITOR_RIGHT)
#define TD_MONM TD(MONITOR_MIDDLE)
#define TD_MONB TD(MONITOR_BOTTOM)
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
    bool recording;
} td_tap_t;

td_state_t dance_state(tap_dance_state_t *state);

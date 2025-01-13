/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "coramoor.h"

#ifdef OLED_ENABLE
# include "oled.c"
#endif

const key_override_t dot_key_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_COLN);  // Shift . is :
const key_override_t comm_key_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_COMM, KC_SCLN); // Shift , is ;

const key_override_t *key_overrides[] = {
    &dot_key_override,
    &comm_key_override
};
// #include "features/tapdance.c"
// static td_tap_t tap_state = {
//     .state = TD_NONE
// };
//
// enum {
//     TDCOPY,
//     TDPASTE
// };
// #define TD_COPY TD(TDCOPY)
// #define TD_PAST TD(TDPASTE)
//
// __attribute__ ((weak)) td_state_t dance_state(tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
//         // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
//         else return TD_SINGLE_HOLD;
//     } else if (state->count == 2) {
//         // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
//         // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
//         // keystrokes of the key, and not the 'double tap' action/macro.
//         if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
//         else if (state->pressed) return TD_DOUBLE_HOLD;
//         else return TD_DOUBLE_TAP;
//     }
//
//     // Assumes no one is trying to type the same letter three times (at least not quickly).
//     // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
//     // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
//     if (state->count == 3) {
//         if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
//         else return TD_TRIPLE_HOLD;
//     } else return TD_UNKNOWN;
// };
// void td_copy(tap_dance_state_t *state, void *user_data) {
//     tap_state.state = dance_state(state);
//     switch (tap_state.state) {
//         case TD_SINGLE_TAP:
//             if (user_config.os == MACOS) {
//                 dprintln("Executing MACOS command");
//                 tap_code16(G(KC_C));
//             } else if (user_config.os == LINUX) {
//                 dprintln("Executing LINUX command");
//                 tap_code16(C(S(KC_C)));
//             } else {
//                 dprintln("Executing WINDOWS command");
//                 tap_code16(C(KC_C));
//             }
//             break;
//         case TD_SINGLE_HOLD:
//             if (user_config.os == MACOS) {
//                 dprintln("Executing MACOS command");
//                 tap_code16(G(KC_X));
//             } else if (user_config.os == LINUX) {
//                 dprintln("Executing LINUX command");
//                 tap_code16(C(S(KC_C)));
//             } else {
//                 dprintln("Executing WINDOWS command");
//                 tap_code16(C(KC_X));
//             }
//             break;
//         default: break;
//     }
// };
//
// void td_paste(tap_dance_state_t *state, void *user_data) {
//     tap_state.state = dance_state(state);
//     switch (tap_state.state) {
//         case TD_SINGLE_TAP:
//             if (user_config.os == MACOS) {
//                 dprintln("Executing MACOS command");
//                 tap_code16(G(KC_V));
//             } else if (user_config.os == LINUX) {
//                 dprintln("Executing LINUX command");
//                 tap_code16(C(S(KC_V)));
//             } else {
//                 dprintln("Executing WINDOWS command");
//                 tap_code16(C(KC_V));
//             }
//             break;
//         case TD_SINGLE_HOLD:
//             if (user_config.os == MACOS) {
//                 dprintln("Executing MACOS command");
//                 tap_code16(G(A(KC_V)));
//             } else if (user_config.os == LINUX) {
//                 dprintln("Executing LINUX command");
//                 tap_code16(C(S(KC_V)));
//             } else {
//                 dprintln("Executing WINDOWS command");
//                 tap_code16(C(KC_V));
//             }
//             break;
//         case TD_DOUBLE_TAP:
//             if (user_config.os == MACOS) {
//                 dprintln("Executing MACOS command");
//                 tap_code16(G(C(KC_V)));
//             } else {
//                 dprintln("Executing WINDOWS command");
//                 tap_code16(G(C(KC_V)));
//             }
//             break;
//         default: break;
//     }
// };
// tap_dance_action_t tap_dance_actions[] = {
//     [TDCOPY] = ACTION_TAP_DANCE_FN(td_copy),
//     [TDPASTE] = ACTION_TAP_DANCE_FN(td_paste)
// };
enum combos {
    CM_PARN,
    CM_CURB,
    CM_BRAC,
    CM_ESC,
    CM_CAPS,
    CM_CAP2,
    CM_LOGN,
    CM_LOG2,
    CM_PLAY,
    CM_MOND,
    CM_LEAD
};


const uint16_t PROGMEM parn_combo[] = {KC_LPRN, KC_RPRN, COMBO_END};
const uint16_t PROGMEM curb_combo[] = {KC_LCBR, KC_RCBR, COMBO_END};
const uint16_t PROGMEM brac_combo[] = {KC_LBRC, KC_RBRC, COMBO_END};
const uint16_t PROGMEM escape_combo[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM capsword_combo[] = {SFT_Z, SFT_QUE, COMBO_END};
const uint16_t PROGMEM capsword2_combo[] = {LHM_S, RHM_E, COMBO_END};
const uint16_t PROGMEM login_combo[] = {LIR_THM, RHM_E, RHM_I, COMBO_END};
const uint16_t PROGMEM login2_combo[] = {LIL_THM, LHM_R, LHM_S, COMBO_END};
const uint16_t PROGMEM play_combo[] = {KC_X, KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM mond_combo[] = {LUTHUM0, LUTHUM1, COMBO_END};
const uint16_t PROGMEM lead_combo[] = {KC_X, KC_C, COMBO_END};

combo_t key_combos[] = {
  [CM_PARN] = COMBO(parn_combo, SM_PAR),
  [CM_CURB] = COMBO(curb_combo, SM_CUR),
  [CM_BRAC] = COMBO(brac_combo, SM_BRC),
  [CM_ESC] = COMBO(escape_combo, SM_ESC),
  [CM_CAPS] = COMBO(capsword_combo, SM_CW),
  [CM_CAP2] = COMBO(capsword2_combo, SM_CW),
  [CM_LOGN] = COMBO(login_combo, SM_LOGN),
  [CM_LOG2] = COMBO(login2_combo, SM_LOGN),
  [CM_PLAY] = COMBO(play_combo, KC_MPLY),
  [CM_MOND] = COMBO(mond_combo, MON_D),
  [CM_LEAD] = COMBO(lead_combo, LEADER)
};

  const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
      [_BASE] =       { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
      [_NAVIGATION] = { ENCODER_CCW_CW(TAB_LFT, TAB_RGT)},
      [_VIM] =        { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
      [_COLEMAK_DH] = { ENCODER_CCW_CW(_______, _______)},
      [_HEX] =        { ENCODER_CCW_CW(_______, _______)},
      [_NUMPAD] =     { ENCODER_CCW_CW(_______, _______)},
      [_SYMBOL] =     { ENCODER_CCW_CW(TAB_LFT, TAB_RGT)},
      [_FUNCTION] =   { ENCODER_CCW_CW(_______, _______)},
      [_APPSWITCH] =  { ENCODER_CCW_CW(_______, _______)},
      [_ADJUST] =     { ENCODER_CCW_CW(MENU_MD, MENU_MU)},
  };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT(
  SM_ESC,  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_TAB,  LHM_A,  LQM_S,   LHM_D,   LHM_F,   KC_G,                                            KC_H,    RHM_J,   RHM_K,   RHM_L,   RHM_SCN, KC_ENT,
  PASSPAL, SFT_Z,  KC_X,    KC_C,    KC_V,    KC_B,    UIL_THM, UOL_THM,   UOR_THM,  UIR_THM,  KC_N,    KC_M,    KC_COMM, KC_DOT,  SFT_QUE, PASSPAL,
                            LUTHUM0, LUTHUM1, LUTHUM2, LIL_THM, LOL_THM,   LOR_THM,  LIR_THM,  RUTHUM2, RUTHUM1, KC_NO
),

[_GAMING] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                                           _______, _______, _______, _______, _______, _______,
  _______, LHM_A,   LHM_R,   LHM_S,   LHM_T,    _______,                                          _______, RHM_N,   RHM_E,   RHM_I,   RHM_O,   _______,
  _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______,  _______,  _______, _______, _______,
                             _______, _______, _______, _______, _______,     _______, _______, _______, _______, KC_NO
),

[_GAMENUM] = LAYOUT(
  KC_ESC,  KC_6,   KC_7,    KC_8,    KC_9,     KC_0,                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_TAB,  KC_1,   KC_2,    KC_3,    KC_4,     KC_5,                                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LCTL, KC_Z,   KC_X,    KC_C,    KC_V,     KC_B,    UIL_THM, UOL_THM,    UOR_THM, UIR_THM, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TOBAS,
                            _______, LUTHUM1,  KC_LSFT, KC_SPC,  LOL_THM,    LOR_THM, LIR_THM, RUTHUM2, RUTHUM1, KC_NO
),

[_COLEMAK_DH] = LAYOUT(
  SM_ESC,  KC_Q,   KC_W,    KC_F,    KC_P,    KC_B,                                            KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, KC_DEL,
  KC_TAB,  LHM_A,  LHM_R,   LHM_S,   LHM_T,   KC_G,                                            KC_M,    RHM_N,   RHM_E,   RHM_I,   RHM_O,   KC_ENT,
  PASSPAL, SFT_Z,  KC_X,    KC_C,    KC_D,    KC_V,    UIL_THM, UOL_THM,   UOR_THM,  UIR_THM,  KC_K,    KC_H,    KC_COMM, KC_DOT,  SFT_QUE, PASSPAL,
                            LUTHUM0, LUTHUM1, LUTHUM2, LIL_THM, LOL_THM,   LOR_THM,  LIR_THM,  RUTHUM2, RUTHUM1, KC_NO
),

[_NAVIGATION] = LAYOUT(
    _______, KC_BSPC, _______, EE_CLR, _______, _______, 		                                 KC_PGDN, SEL_LIN, SEL_WRD, KC_PGUP, _______, _______,
    _______, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, TD_COPY,                                        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, KC_ENT,
    QK_LLCK, MONUM,   KC_ENT,  TAB_LFT, TAB_RGT, TD_PAST, _______, _______,    _______, _______, _______, MON_L,   MON_R,   _______, _______, _______,
                               TAB_LFT, TAB_RGT, _______, _______, _______,    KC_ENT,  KC_SPC,  _______, _______, _______
),

[_NUMPAD] = LAYOUT(
  _______, KC_BSPC, KC_TAB,  _______, _______, _______,                                        KC_GRV,  KC_7,    KC_8,    KC_9,    KC_SLSH, _______,
  _______, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, _______,                                        KC_MINS, KC_4,    KC_5,    KC_6,    KC_COLN, KC_ENT,
  QK_LLCK, MOVIM,   _______, _______, _______, _______, _______, _______,    _______, _______, KC_EQL,  KC_1,    KC_2,    KC_3,    KC_DOT,  _______,
                             _______, _______, _______, _______, _______,    KC_ENT,  KC_0,    KC_DOT,  _______, KC_NO
),

[_SYMBOL] = LAYOUT(
  // _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, _______,                                        _______, _______, _______, _______, _______, _______,
  // _______, KC_AT,   KC_BSLS, KC_UNDS, TIPS,    KC_PIPE,                                        TD_COPY, OSMRGUI, OSMRSFT, OSMRALT, OSMRCTL, KC_QUOT,
  // _______, KC_LBRC, KC_RBRC, KC_LT,   KC_GT,   _______, _______, _______,    _______, _______, TD_PAST, KC_MPRV, KC_MPLY, KC_MNXT, _______, LLOCK,
  _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, _______,                                        KC_TILD, KC_AMPR, KC_ASTR, KC_LPRN, _______, _______,
  _______, KC_AT,   KC_BSLS, KC_UNDS, TIPS,    KC_PIPE,                                        KC_UNDS, KC_DLR,  KC_PERC, KC_CIRC, _______, _______,
  _______, KC_LBRC, KC_RBRC, KC_LT,   KC_GT,   _______, _______, _______,    _______, _______, KC_PLUS, KC_EXLM, KC_AT,   KC_HASH, _______, _______,
                             TAB_LFT, TAB_RGT, ALT_BSP, KC_BSPC, XCTHUM,     _______, _______, _______, _______, _______
),

[_VIM] = LAYOUT(
  _______, KC_BSPC, KC_TAB,  _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
  _______, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, _______,                                        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, KC_BSPC, XCTHUM,     _______, _______, _______, _______, _______
),

[_HEX] = LAYOUT(
  // _______, KC_TAB,  KC_D,    KC_E,    KC_F,    _______,                                        KC_PIPE, KC_7,    KC_8,    KC_9,    KC_TILD, _______,
  // _______, _______, KC_A,    KC_B,    KC_C,    _______,                                        KC_SLSH, KC_4,    KC_5,    KC_6,    KC_COLN, _______,
  // _______, KC_LSFT, TOBAS,   _______, _______, _______, _______, _______,    _______, _______, KC_MINS, KC_1,    KC_2,    KC_3,    SFT_DOT, _______,
  //                            _______, _______, KC_BSPC, KC_BSPC, _______,    _______,  KC_0,   _______, _______, _______
  _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                        _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, KC_BSPC, KC_BSPC, _______,    _______,  KC_0,   _______, _______, _______
),

[_FUNCTION] = LAYOUT( \
  TOADJ,   _______, _______, _______, _______, _______,                                         _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F13,\
  SM_LOGN, OSMLSFT, OSMLALT, OSMLCTL, OSMLGUI, _______,                                         _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,  KC_F14,\
  MACSLEP, _______, TOHEX,   _______, _______, _______, _______, _______,     _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F12,  KC_F15,\
                             _______, _______, _______, KC_DEL,  _______,     _______, _______, _______, _______, KC_NO \
),

[_APPSWITCH] = LAYOUT(
  _______, KC_BSPC, KC_Z,    _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
  _______, _______, _______, KC_LEFT, KC_RGHT, _______,                                        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, KC_X,    KC_Z,    _______, _______, _______,
                             _______, _______, _______, _______, _______,    _______, _______, _______, _______, KC_NO
),

  // KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  // _______, KC_LBRC, KC_RBRC, KC_MINS, KC_BSLS, TIPS,                                           _______, OSMRGUI, OSMRSFT, OSMRALT, OSMRCTL, _______,
  // _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, TIPS,    _______, _______,    _______, _______, KC_EQL,  _______, _______, _______, KC_DOT,  KC_ENT,
  //                            KC_NO,   _______, _______, _______, OSMLSFT,    _______, _______, _______, _______, KC_NO

[_ADJUST] = LAYOUT( \
  TOBAS,   TOBAS,   _______, EE_CLR,  QK_RBT,  _______,                                         _______, _______,  _______,  _______, _______, _______,  \
  _______, _______, _______, _______, _______, _______,                                         MENU_AD, MENU_MD,  MENU_MU,  MENU_AU, _______, _______,\
  _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______,  _______,  _______, _______, _______,\
                             _______, _______, _______, _______, _______,     _______, _______, _______, _______, KC_NO \
)
};

/* The default OLED and rotary encoder code can be found at the bottom of qmk_firmware/keyboards/splitkb/kyria/rev1/rev1.c
 * These default settings can be overriden by your own settings in your keymap.c
 * For your convenience, here's a copy of those settings so that you can uncomment them if you wish to apply your own modifications.
 * DO NOT edit the rev1.c file; instead override the weakly defined default functions by your own.
 */

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif

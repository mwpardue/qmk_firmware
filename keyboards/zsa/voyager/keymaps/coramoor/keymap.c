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

enum combos {
    CM_LMES,
    // CM_RMES,
    CM_CAPS,
    // CM_CAP2,
    CM_CAP3,
    // CM_MLOG,
    CM_MLG2,
    CM_PREV,
    CM_PLAY,
    CM_MOND,
    CM_NEXT,
    CM_HEX,
    CM_FUNC,
    CM_SLSH
};


const uint16_t PROGMEM mtlescape_combo[]    = {LQM_S,        LHM_D,               COMBO_END};
// const uint16_t PROGMEM mtrescape_combo[]    = {KC_P,        KC_I,               COMBO_END};
const uint16_t PROGMEM capsword_combo[]     = {LOL_THM,     LOR_THM,            COMBO_END};
// const uint16_t PROGMEM capsword2_combo[]    = {CTL_Z,       CTL_QUE,            COMBO_END};
const uint16_t PROGMEM capsword3_combo[]    = {RUTHUM0,     RUTHUM1,            COMBO_END};
// const uint16_t PROGMEM mtlogin_combo[]      = {LIR_THM,     KC_K,       KC_L,   COMBO_END};
const uint16_t PROGMEM mtlogin2_combo[]     = {LIL_THM,     LQM_S,      LHM_D,  COMBO_END};
const uint16_t PROGMEM play_combo[]         = {KC_X,        KC_C,       KC_V,   COMBO_END};
const uint16_t PROGMEM mnext_combo[]        = {KC_C,        KC_V,               COMBO_END};
const uint16_t PROGMEM mond_combo[]         = {MON_L,       MON_R,              COMBO_END};
const uint16_t PROGMEM mprev_combo[]        = {KC_X,        KC_C,               COMBO_END};
const uint16_t PROGMEM hex_combo[]          = {KC_X,        KC_DOT,             COMBO_END};
const uint16_t PROGMEM slash_combo[]        = {KC_COMMA,    KC_DOT,             COMBO_END};
const uint16_t PROGMEM function_combo[]     = {SM_ESC,      KC_EQL,             COMBO_END};

combo_t key_combos[] = {
  [CM_LMES] = COMBO(mtlescape_combo,    SM_ESC),
  // [CM_RMES] = COMBO(mtrescape_combo,    SM_ESC),
  [CM_CAPS] = COMBO(capsword_combo,     SM_CW),
  // [CM_CAP2] = COMBO(capsword2_combo,    KC_CAPS),
  [CM_CAP3] = COMBO(capsword3_combo,    KC_CAPS),
  // [CM_MLOG] = COMBO(mtlogin_combo,      SM_LOGN),
  [CM_MLG2] = COMBO(mtlogin2_combo,     SM_LOGN),
  [CM_PREV] = COMBO(mprev_combo,        KC_MPRV),
  [CM_PLAY] = COMBO(play_combo,         KC_MPLY),
  [CM_MOND] = COMBO(mond_combo,         MON_D),
  [CM_NEXT] = COMBO(mnext_combo,        KC_MNXT),
  [CM_HEX]  = COMBO(hex_combo,          TOHEX),
  [CM_FUNC] = COMBO(function_combo,     TOFUN),
  [CM_SLSH] = COMBO(slash_combo,        KC_SLSH)
};

// uint8_t combo_ref_from_layer(uint8_t_layer) {
//     switch (get_highest_layer(layer_state)) {
//         case _NAVIGATION:
//             return _NAVIGATION;
//         default:
//             return _BASE;
//     }
//     return layer;
// }

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
  '*', '*', '*', '*', '*', '*',                              '*', '*', '*', '*', '*', '*',
  '*', 'L', 'L', 'L', 'L', 'L',                              'R', 'R', 'R', 'R', 'R', '*',
  '*', 'L', 'L', 'L', 'L', 'L',                              'R', 'R', 'R', 'R', 'R', 'R',
  '*', 'L', 'L', 'L', 'L', 'L',                              'R', 'R', 'R', 'R', 'R', '*',
                                '*', '*',          '*', '*'
    );

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT(
  SM_ESC,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                                 KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
  KC_TAB,  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                                 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  SM_CW,   LHM_A,  LQM_S,   LHM_D,   LHM_F,   KC_G,                                                 KC_H,    RHM_J,   RHM_K,   RHM_L,   RHM_SCN, KC_QUOT,
  MEH_PP,  NUM_Z,  KC_X,    KC_C,    KC_V,    KC_B,                                                 KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MEH_PP,
                                                       LIL_THM, LOL_THM,          LOR_THM, LIR_THM
),

[_GAMING] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  _______, SFT_Z,   _______, _______, _______, _______,                                             _______, _______, _______, _______, SFT_QUE, _______,
                                                        _______, CLOL_THM,    CLOR_THM, _______
),

[_GAMENUM] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  KC_ESC,  KC_6,   KC_7,    KC_8,    KC_9,     KC_0,                                                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_TAB,  KC_1,   KC_2,    KC_3,    KC_4,     KC_5,                                                KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LCTL, KC_Z,   KC_X,    KC_C,    KC_V,     KC_B,                                                KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TOBAS,
                                                        KC_SPC,  LOL_THM,         LOR_THM, LIR_THM
),

[_COLEMAK_DH] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                                              _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                              _______, _______, _______, _______, _______, _______,
  NUM_BSP, KC_A,    KC_S,    KC_D,    KC_F,    _______,                                              _______, KC_J,    KC_K,    KC_L,    KC_SCLN, _______,
  _______, CTL_Z,   ALT_X,   _______, _______, _______,                                              _______, _______, _______, ALT_DOT, CTL_QUE, _______,
                                                        _______, _______,          _______, _______
),

[_NAVIGATION] = LAYOUT(
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                             KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, KC_BSPC, MON_L,   MON_D,   MON_R,   _______, 		                                    KC_HOME, SEL_LIN, SEL_WRD, KC_END,  _______, _______,
    XCASE,   OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, TAB_UP,                                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, TAB_UP,  _______,
    QK_LLCK, MONUM,   MC_SWRI, TD_COPY, TD_PAST, TAB_DWN,                                           _______, MON_L,   MON_D,   MON_R,   TAB_DWN, _______,
                                                          _______, _______,       KC_ENT,  KC_SPC
),

[_NUMPAD] = LAYOUT(
  KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                               KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  _______, KC_BSPC, KC_TAB,  _______, _______, _______,                                             KC_TILD, KC_7,    KC_8,    KC_9,    KC_COLN, KC_BSLS,
  _______, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, _______,                                             KC_MINS, KC_4,    KC_5,    KC_6,    KC_DOT,  KC_DQUO,
  QK_LLCK, MOVIM,   KC_CIRC, KC_PERC, KC_DLR,  _______,                                             KC_EQL,  KC_1,    KC_2,    KC_3,    KC_SLSH, _______,
                                                        _______, _______,         KC_ENT,  KC_0
),

[_SYMBOL] = LAYOUT(
  KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                               KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_GRV,  KC_CIRC, KC_DLR,  KC_LCBR, KC_RCBR, TIPS,                                                KC_GRV,  KC_AMPR, KC_ASTR, KC_LPRN, KC_GRV,  _______,
  _______, KC_AT,   KC_BSLS, KC_LPRN, KC_RPRN, KC_PIPE,                                             KC_UNDS, KC_DLR,  KC_PERC, KC_CIRC, _______, _______,
  _______, KC_PERC, KC_UNDS, KC_LBRC, KC_RBRC, KC_ASTR,                                             KC_PLUS, KC_EXLM, KC_AT,   KC_HASH, _______, _______,
                                                        KC_BSPC, _______,         _______, _______
),

[_VIM] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  _______, KC_BSPC, KC_TAB,  _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  _______, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, _______,                                             KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
                                                        KC_BSPC, _______,         _______, _______
),

[_HEX] = LAYOUT(
  TOBAS,   _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  TOBAS,   _______, _______, _______, _______, _______,                                             KC_TILD, KC_7,    KC_8,    KC_9,    KC_SLSH, _______,
  _______, _______, _______, _______, _______, _______,                                             KC_MINS, KC_4,    KC_5,    KC_6,    KC_COLN, _______,
  _______, _______, _______, _______, _______, _______,                                             KC_EQL,  KC_1,    KC_2,    KC_3,    KC_DOT,  _______,
                                                        _______, _______,         _______, KC_0
),

[_FUNCTION] = LAYOUT( \
  TOBAS,   _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  TOADJ,   DF_LAYR, TOBAS,   EE_CLR,  DB_TOGG, _______,                                             RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, RM_SPDU, KC_F13,\
  SM_LOGN, OSMLSFT, OSMLALT, OSMLCTL, OSMLGUI, _______,                                             RM_PREV, RM_HUED, RM_SATD, RM_VALD, RM_SPDD,  KC_F14,\
  _______, _______, TOHEX,   _______, _______, _______,                                             _______, KC_F1,   KC_F2,   KC_F3,   KC_F12,  KC_F15,\
                                                        KC_DEL,  _______,         _______, _______
),

[_APPSWITCH] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  _______, KC_BSPC, KC_Z,    _______, _______, _______,                                            _______, _______, _______, _______, _______, _______,
  _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,                                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  _______, _______, MC_SWRI, _______, _______, _______,                                            KC_N,    KC_M,    _______, _______, _______, _______,
                                                        _______, _______,        _______, _______
),

[_ADJUST] = LAYOUT( \
  ADJ_EXT, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  TOBAS,   TOBAS,   _______, EE_CLR,  QK_RBT,  _______,                                             _______, _______,  _______,  _______, _______, _______,  \
  TB_MENU, _______, _______, _______, _______, _______,                                             MENU_AD, MENU_MD,  MENU_MU,  MENU_AU, _______, _______,\
  _______, _______, _______, _______, _______, _______,                                             _______, _______,  _______,  _______, _______, _______,\
                                                        _______, _______,         _______, _______
)
};


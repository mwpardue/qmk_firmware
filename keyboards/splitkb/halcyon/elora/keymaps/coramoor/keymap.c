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

enum combos {
    CM_LMES,
    CM_RMES,
    CM_CAPS,
    CM_CAP2,
    CM_CAP3,
    CM_MLOG,
    CM_MLG2,
    CM_PREV,
    CM_PLAY,
    CM_MOND,
    CM_NEXT,
    CM_HEX,
    CM_SLSH
};


const uint16_t PROGMEM mtlescape_combo[]    = {KC_D,        KC_S,               COMBO_END};
const uint16_t PROGMEM mtrescape_combo[]    = {KC_L,        KC_K,               COMBO_END};
const uint16_t PROGMEM capsword_combo[]     = {LOL_THM,     LOR_THM,            COMBO_END};
const uint16_t PROGMEM capsword2_combo[]    = {LUTHUM0,     LUTHUM1,            COMBO_END};
const uint16_t PROGMEM capsword3_combo[]    = {RUTHUM0,     RUTHUM1,            COMBO_END};
const uint16_t PROGMEM mtlogin_combo[]      = {LIR_THM,     KC_K,       KC_L,   COMBO_END};
const uint16_t PROGMEM mtlogin2_combo[]     = {LIL_THM,     KC_D,       KC_S,   COMBO_END};
const uint16_t PROGMEM play_combo[]         = {ALT_X,       KC_C,       KC_V,   COMBO_END};
const uint16_t PROGMEM mnext_combo[]        = {KC_C,        KC_V,               COMBO_END};
const uint16_t PROGMEM mond_combo[]         = {MON_L,       MON_R,              COMBO_END};
const uint16_t PROGMEM mprev_combo[]        = {ALT_X,       KC_C,               COMBO_END};
const uint16_t PROGMEM hex_combo[]          = {ALT_X,       ALT_DOT,            COMBO_END};
const uint16_t PROGMEM slash_combo[]        = {KC_COMMA,    ALT_DOT,            COMBO_END};

combo_t key_combos[] = {
  [CM_LMES] = COMBO(mtlescape_combo,    SM_ESC),
  [CM_RMES] = COMBO(mtrescape_combo,    SM_ESC),
  [CM_CAPS] = COMBO(capsword_combo,     SM_CW),
  [CM_CAP2] = COMBO(capsword2_combo,    KC_CAPS),
  [CM_CAP3] = COMBO(capsword3_combo,    KC_CAPS),
  [CM_MLOG] = COMBO(mtlogin_combo,      SM_LOGN),
  [CM_MLG2] = COMBO(mtlogin2_combo,     SM_LOGN),
  [CM_PREV] = COMBO(mprev_combo,        KC_MPRV),
  [CM_PLAY] = COMBO(play_combo,         KC_MPLY),
  [CM_MOND] = COMBO(mond_combo,         MON_D),
  [CM_NEXT] = COMBO(mnext_combo,        KC_MNXT),
  [CM_HEX]  = COMBO(hex_combo,          TOHEX),
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

#define NOENC ENCODER_CCW_CW(_______, _______)

  const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
      [_BASE] =       { NOENC, NOENC, NOENC, ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
      [_GAMING] =     { NOENC, NOENC, NOENC, ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
      [_NAVIGATION] = { NOENC, NOENC, NOENC, ENCODER_CCW_CW(TAB_LFT, TAB_RGT)},
      [_VIM] =        { NOENC, NOENC, NOENC, ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
      [_COLEMAK_DH] = { NOENC, NOENC, NOENC, ENCODER_CCW_CW(_______, _______)},
      [_HEX] =        { NOENC, NOENC, NOENC, ENCODER_CCW_CW(_______, _______)},
      [_NUMPAD] =     { NOENC, NOENC, NOENC, ENCODER_CCW_CW(LGUI(KC_MINS), LGUI(KC_EQL))},
      [_SYMBOL] =     { NOENC, NOENC, NOENC, ENCODER_CCW_CW(TAB_LFT, TAB_RGT)},
      [_FUNCTION] =   { NOENC, NOENC, NOENC, ENCODER_CCW_CW(_______, _______)},
      [_APPSWITCH] =  { NOENC, NOENC, NOENC, ENCODER_CCW_CW(_______, _______)},
      [_ADJUST] =     { NOENC, NOENC, NOENC, ENCODER_CCW_CW(MENU_AD, MENU_AU)},
  };

const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_elora_hlc(
  '*', '*', '*', '*', '*', '*',                              '*', '*', '*', '*', '*', '*',
  '*', 'L', 'L', 'L', 'L', 'L',                              'R', 'R', 'R', 'R', 'R', '*',
  '*', 'L', 'L', 'L', 'L', 'L',                              'R', 'R', 'R', 'R', 'R', 'R',
  '*', 'L', 'L', 'L', 'L', 'L', '*', '*',          '*', '*', 'R', 'R', 'R', 'R', 'R', '*',
                 '*', '*', '*', '*', '*',          '*', '*', '*', '*', '*',
       '*', '*', '*', '*', '*',                         '*', '*', '*', '*', '*'
    );

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_elora_hlc(
  SM_ESC,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                                 KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
  KC_GRV,  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                                 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_TAB,  KC_A,   KC_S,    KC_D,    LHM_F,   KC_G,                                                 KC_H,    RHM_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  PASSPAL, CTL_Z,  ALT_X,   KC_C,    KC_V,    KC_B,    UIL_THM, UOL_THM,          UOR_THM, UIR_THM, KC_N,    KC_M,    KC_COMM, ALT_DOT, CTL_QUE, PASSPAL,
                            LUTHUM0, LUTHUM1, LUTHUM2, LIL_THM, LOL_THM,          LOR_THM, LIR_THM, RUTHUM2, RUTHUM1, RUTHUM0,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                       KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_GAMING] = LAYOUT_elora_hlc(
  _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  NUM_TAB, LHM_A,   LQM_S,   LHM_D,   LHM_F,   _______,                                             _______, RHM_J,   RHM_K,   RHM_L,   RHM_SCN, GUI_QUO,
  LALT_PP, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, RALT_PP,
                            _______, _______,  CLUTHUM2, _______, _______,        _______, _______, CRUTHUM2, _______, _______,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                    KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_GAMENUM] = LAYOUT_elora_hlc(
  _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  KC_ESC,  KC_6,   KC_7,    KC_8,    KC_9,     KC_0,                                                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_TAB,  KC_1,   KC_2,    KC_3,    KC_4,     KC_5,                                                KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LCTL, KC_Z,   KC_X,    KC_C,    KC_V,     KC_B,    UIL_THM, UOL_THM,         UOR_THM, UIR_THM, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TOBAS,
                            _______, LUTHUM1,  KC_LSFT, KC_SPC,  LOL_THM,         LOR_THM, LIR_THM, RUTHUM2, RUTHUM1, KC_NO,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                     KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_COLEMAK_DH] = LAYOUT_elora_hlc(
  _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  _______, LHM_A,  LQM_S,   LHM_D,   LHM_F,    _______,                                             _______, RHM_J,   RHM_K,   RHM_L,   RHM_SCN, KC_QUOT,
  _______, NUM_Z,  KC_X,    _______, _______,  _______, _______, _______,         _______, _______, _______, _______, _______,  KC_DOT, KC_SLSH, _______,
                            _______, _______,  _______, _______, _______,         _______, _______, _______, _______, _______,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                     KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_NAVIGATION] = LAYOUT_elora_hlc(
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                             KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, KC_BSPC, MON_L,   MON_D,   MON_R,   _______, 		                                    KC_HOME, SEL_WRD, SEL_LIN, KC_END,  KC_PGUP, _______,
    MC_SWRI, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, TAB_UP,                                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PGDN, _______,
    QK_LLCK, MONUM,   MC_SWRI, TD_COPY, TD_PAST, TAB_DWN, _______, _______,       _______, _______, _______, MON_L,   MON_D,   MON_R,   _______, _______,
                               DM_REC1, DM_PLY1, _______, _______, _______,       _______, KC_SPC,  _______, DM_REC1, DM_PLY1,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                   KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_NUMPAD] = LAYOUT_elora_hlc(
  KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                               KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  _______, KC_BSPC, KC_TAB,  _______, _______, _______,                                             KC_TILD, KC_7,    KC_8,    KC_9,    KC_COLN, KC_BSLS,
  _______, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, _______,                                             KC_MINS, KC_4,    KC_5,    KC_6,    KC_DOT,  KC_COLN,
  QK_LLCK, MOVIM,   KC_CIRC, KC_PERC, KC_DLR,  _______, _______, _______,         _______, _______, KC_EQL,  KC_1,    KC_2,    KC_3,    KC_SLSH, _______,
                             SPC_L,   SPC_R,   _______, _______, _______,         KC_ENT,  KC_0,    KC_DOT,  _______, KC_NO,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                     KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_SYMBOL] = LAYOUT_elora_hlc(
  KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                               KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_GRV,  KC_CIRC, KC_DLR,  KC_LCBR, KC_RCBR, TIPS,                                                _______, KC_AMPR, KC_ASTR, KC_LPRN, _______, _______,
  _______, KC_AT,   KC_BSLS, KC_LPRN, KC_RPRN, KC_PIPE,                                             KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, _______, _______,
  _______, KC_PERC, KC_UNDS, KC_LBRC, KC_RBRC, KC_ASTR, _______, _______,         _______, _______, KC_EXLM, KC_EXLM, KC_AT,   KC_HASH, _______, _______,
                             DM_REC1, DM_PLY1, _______, KC_BSPC, _______,         _______, _______, _______, DM_REC1, DM_PLY1,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                     KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_VIM] = LAYOUT_elora_hlc(
  _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  _______, KC_BSPC, KC_TAB,  _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  _______, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, _______,                                             KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, KC_BSPC, _______,         _______, _______, _______, _______, _______,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                     KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_HEX] = LAYOUT_elora_hlc(
  TOBAS,   _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  TOBAS,   _______, _______, _______, _______, _______,                                             KC_TILD, KC_7,    KC_8,    KC_9,    KC_SLSH, _______,
  _______, _______, _______, _______, _______, _______,                                             KC_MINS, KC_4,    KC_5,    KC_6,    KC_COLN, _______,
  _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, KC_EQL,  KC_1,    KC_2,    KC_3,    KC_DOT,  _______,
                             _______, _______, _______, _______, _______,         _______, KC_0,    KC_DOT,  _______, _______,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                     KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_FUNCTION] = LAYOUT_elora_hlc( \
  TOADJ,   DF_LAYR, TOBAS,   _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  TOADJ,   DF_LAYR, TOBAS,   EE_CLR,  DB_TOGG, _______,                                             _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F13,\
  SM_LOGN, OSMLSFT, OSMLALT, OSMLCTL, OSMLGUI, _______,                                             _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,  KC_F14,\
  _______, _______, TOHEX,   _______, _______, _______, _______, _______,         _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F12,  KC_F15,\
                             _______, _______, _______, KC_DEL,  _______,         _______, _______, _______, _______, KC_NO, \
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                    KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_APPSWITCH] = LAYOUT_elora_hlc(
  _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  _______, KC_BSPC, KC_Z,    _______, _______, _______,                                            _______, _______, _______, _______, _______, _______,
  _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,                                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  _______, _______, MC_SWRI, _______, _______, _______, _______, _______,        _______, _______, KC_N,    KC_M,    _______, _______, _______, _______,
                             _______, _______, _______, _______, _______,        _______, _______, _______, _______, KC_NO,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                    KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_ADJUST] = LAYOUT_elora_hlc( \
  ADJ_EXT, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  TOBAS,   TOBAS,   _______, EE_CLR,  QK_RBT,  _______,                                             _______, _______,  _______,  _______, _______, _______,  \
  TB_MENU, _______, _______, _______, _______, _______,                                             MENU_AD, MENU_MD,  MENU_MU,  MENU_AU, _______, _______,\
  _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______,  _______,  _______, _______, _______,\
                             _______, _______, TOBAS,   _______, _______,         _______, _______, _______, _______, KC_NO, \
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                    KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
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

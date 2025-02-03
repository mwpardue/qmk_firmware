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
    CM_PARN,
    CM_CURB,
    CM_BRAC,
    CM_LESC,
    CM_RESC,
    CM_LMES,
    CM_RMES,
    CM_CAPS,
    CM_CAP2,
    CM_MLOG,
    CM_MLG2,
    CM_LOGN,
    CM_LOG2,
    CM_PLAY,
    CM_MOND,
    CM_MON2,
    CM_LEAD,
    CM_LED2,
    CM_HEX
};


const uint16_t PROGMEM parn_combo[] = {KC_LPRN, KC_RPRN, COMBO_END};
const uint16_t PROGMEM curb_combo[] = {KC_LCBR, KC_RCBR, COMBO_END};
const uint16_t PROGMEM brac_combo[] = {KC_LBRC, KC_RBRC, COMBO_END};
const uint16_t PROGMEM lescape_combo[] = {KC_D, KC_S, COMBO_END};
const uint16_t PROGMEM rescape_combo[] = {KC_L, KC_K, COMBO_END};
const uint16_t PROGMEM mtlescape_combo[] = {LHM_D, LQM_S, COMBO_END};
const uint16_t PROGMEM mtrescape_combo[] = {RHM_L, RHM_K, COMBO_END};
const uint16_t PROGMEM capsword_combo[] = {SFT_Z, SFT_QUE, COMBO_END};
const uint16_t PROGMEM capsword2_combo[] = {LHM_D, RHM_K, COMBO_END};
const uint16_t PROGMEM mtlogin_combo[] = {LIR_THM, RHM_K, RHM_L, COMBO_END};
const uint16_t PROGMEM mtlogin2_combo[] = {LIL_THM, LHM_D, LQM_S, COMBO_END};
const uint16_t PROGMEM login_combo[] = {LIR_THM, KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM login2_combo[] = {LIL_THM, KC_D, KC_S, COMBO_END};
const uint16_t PROGMEM play_combo[] = {KC_X, KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM mond_combo[] = {LUTHUM0, LUTHUM1, COMBO_END};
const uint16_t PROGMEM mond2_combo[] = {MON_L, MON_R, COMBO_END};
const uint16_t PROGMEM lead_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM lead2_combo[] = {KC_COMMA, KC_DOT, COMBO_END};
const uint16_t PROGMEM hex_combo[] = {KC_X, KC_DOT, COMBO_END};

combo_t key_combos[] = {
  [CM_PARN] = COMBO(parn_combo, SM_PAR),
  [CM_CURB] = COMBO(curb_combo, SM_CUR),
  [CM_BRAC] = COMBO(brac_combo, SM_BRC),
  [CM_LESC] = COMBO(lescape_combo, SM_ESC),
  [CM_RESC] = COMBO(rescape_combo, SM_ESC),
  [CM_LMES] = COMBO(mtlescape_combo, SM_ESC),
  [CM_RMES] = COMBO(mtrescape_combo, SM_ESC),
  [CM_CAPS] = COMBO(capsword_combo, SM_CW),
  [CM_CAP2] = COMBO(capsword2_combo, SM_CW),
  [CM_MLOG] = COMBO(mtlogin_combo, SM_LOGN),
  [CM_MLG2] = COMBO(mtlogin2_combo, SM_LOGN),
  [CM_LOGN] = COMBO(login_combo, SM_LOGN),
  [CM_LOG2] = COMBO(login2_combo, SM_LOGN),
  [CM_PLAY] = COMBO(play_combo, KC_MPLY),
  [CM_MOND] = COMBO(mond_combo, MON_D),
  [CM_MON2] = COMBO(mond2_combo, MON_D),
  [CM_LEAD] = COMBO(lead_combo, LEADER),
  [CM_LED2] = COMBO(lead2_combo, LEADER),
  [CM_HEX] = COMBO(hex_combo, TOHEX)
};

#define NOENC ENCODER_CCW_CW(_______, _______)

  const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
      [_BASE] =       { NOENC, NOENC, NOENC, ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
      [_NAVIGATION] = { NOENC, NOENC, NOENC, ENCODER_CCW_CW(TAB_LFT, TAB_RGT)},
      [_VIM] =        { NOENC, NOENC, NOENC, ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
      [_COLEMAK_DH] = { NOENC, NOENC, NOENC, ENCODER_CCW_CW(_______, _______)},
      [_HEX] =        { NOENC, NOENC, NOENC, ENCODER_CCW_CW(_______, _______)},
      [_NUMPAD] =     { NOENC, NOENC, NOENC, ENCODER_CCW_CW(LGUI(KC_MINS), LGUI(KC_EQL))},
      [_SYMBOL] =     { NOENC, NOENC, NOENC, ENCODER_CCW_CW(TAB_LFT, TAB_RGT)},
      [_FUNCTION] =   { NOENC, NOENC, NOENC, ENCODER_CCW_CW(_______, _______)},
      [_APPSWITCH] =  { NOENC, NOENC, NOENC, ENCODER_CCW_CW(_______, _______)},
      [_ADJUST] =     { NOENC, NOENC, NOENC, ENCODER_CCW_CW(MENU_MD, MENU_MU)},
  };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT_split_3x6_5_hlc(
  SM_ESC,  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                                 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_TAB,  LHM_A,  LQM_S,   LHM_D,   LHM_F,   KC_G,                                                 KC_H,    RHM_J,   RHM_K,   RHM_L,   RHM_SCN, KC_QUOT,
  PASSPAL, SFT_Z,  KC_X,    KC_C,    KC_V,    KC_B,    UIL_THM, UOL_THM,          UOR_THM, UIR_THM, KC_N,    KC_M,    KC_COMM, KC_DOT,  SFT_QUE, PASSPAL,
                            LUTHUM0, LUTHUM1, LUTHUM2, LIL_THM, LOL_THM,          LOR_THM, LIR_THM, RUTHUM2, RUTHUM1, RUTHUM0,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                       KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_GAMING] = LAYOUT_split_3x6_5_hlc(
  _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  _______, LHM_A,   LHM_R,   LHM_S,   LHM_T,    _______,                                            _______, RHM_N,   RHM_E,   RHM_I,   RHM_O,   _______,
  _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______,  _______,  _______, _______, _______,
                             _______, _______, _______, _______, _______,         _______, _______, _______, _______, KC_NO,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                    KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_GAMENUM] = LAYOUT_split_3x6_5_hlc(
  KC_ESC,  KC_6,   KC_7,    KC_8,    KC_9,     KC_0,                                                KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_TAB,  KC_1,   KC_2,    KC_3,    KC_4,     KC_5,                                                KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LCTL, KC_Z,   KC_X,    KC_C,    KC_V,     KC_B,    UIL_THM, UOL_THM,         UOR_THM, UIR_THM, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TOBAS,
                            _______, LUTHUM1,  KC_LSFT, KC_SPC,  LOL_THM,         LOR_THM, LIR_THM, RUTHUM2, RUTHUM1, KC_NO,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                     KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_COLEMAK_DH] = LAYOUT_split_3x6_5_hlc(
  _______, _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  CTL_TAB, LSM_A,   LQM_S,   LSM_D,   LHM_F,   _______,                                             _______,   RHM_J,   RSM_K,   RHM_L, RSM_SCN, CTL_QUO,
  _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______,
                            _______, _______,  _______, _______, _______,         _______, _______, _______, _______, _______,
                            // _______, _______, CLUTHUM2, _______, _______,        CLOR_THM, _______, CRUTHUM2, _______, _______,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                     KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
  // SM_ESC,  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                                 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  // CTL_TAB, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                                                 KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, CTL_QUO,
  // PASSPAL, SFT_Z,  KC_X,    KC_C,    KC_V,    KC_B,     CUIL_THM, UOL_THM,         UOR_THM, UIR_THM, KC_N,    KC_M,    KC_COMM, KC_DOT,  SFT_QUE, PASSPAL,
  //                           LUTHUM0, LUTHUM1, CLUTHUM2, LIL_THM, LOL_THM,         CLOR_THM, LIR_THM, CRUTHUM2, RUTHUM1, KC_NO,
  //       KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                     KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_NAVIGATION] = LAYOUT_split_3x6_5_hlc(
    _______, KC_BSPC, MC_SWRI, TAB_LFT, TAB_RGT, _______, 		                                    KC_PGDN, SEL_WRD, SEL_LIN, KC_PGUP, _______, _______,
    _______, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, _______,                                           KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
    QK_LLCK, MONUM,   _______, TD_COPY, TD_PAST, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, _______,
                               TAB_LFT, TAB_RGT, _______, _______, _______,       KC_ENT,  KC_SPC,  _______, _______, _______,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                   KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_NUMPAD] = LAYOUT_split_3x6_5_hlc(
  _______, KC_BSPC, KC_TAB,  _______, _______, _______,                                             KC_TILD, KC_7,    KC_8,    KC_9,    KC_SLSH, _______,
  _______, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, _______,                                             KC_MINS, KC_4,    KC_5,    KC_6,    KC_COLN, _______,
  QK_LLCK, MOVIM,   _______, _______, _______, _______, _______, _______,         _______, _______, KC_EQL,  KC_1,    KC_2,    KC_3,    KC_DOT,  _______,
                             _______, _______, _______, _______, _______,         KC_ENT,  KC_0,    KC_DOT,  _______, KC_NO,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                     KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_SYMBOL] = LAYOUT_split_3x6_5_hlc(
  _______, KC_CIRC, KC_DLR,  KC_LCBR, KC_RCBR, TIPS,                                                KC_GRV,  KC_AMPR, KC_ASTR, KC_LPRN, _______, _______,
  _______, KC_AT,   KC_BSLS, KC_LPRN, KC_RPRN, KC_PIPE,                                             KC_UNDS, KC_DLR,  KC_PERC, KC_CIRC, _______, _______,
  _______, KC_HASH, KC_UNDS, KC_LBRC, KC_RBRC, KC_ASTR, _______, _______,         _______, _______, KC_PLUS, KC_EXLM, KC_AT,   KC_HASH, _______, _______,
                             TAB_LFT, TAB_RGT, _______, KC_BSPC, _______,         _______, _______, _______, _______, _______,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                     KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
  // _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, TIPS,                                                KC_GRV,  KC_AMPR, KC_ASTR, KC_LPRN, _______, _______,
  // _______, KC_AT,   KC_BSLS, KC_UNDS, KC_PIPE, _______,                                             KC_UNDS, KC_DLR,  KC_PERC, KC_CIRC, _______, _______,
  // _______, KC_LBRC, KC_RBRC, KC_LT,   KC_GT,   _______, _______, _______,         _______, _______, KC_PLUS, KC_EXLM, KC_AT,   KC_HASH, _______, _______,
  //                            TAB_LFT, TAB_RGT, _______, KC_BSPC, _______,         _______, _______, _______, _______, _______,
  //       KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                     KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_VIM] = LAYOUT_split_3x6_5_hlc(
  _______, KC_BSPC, KC_TAB,  _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  _______, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, _______,                                             KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, KC_BSPC, _______,         _______, _______, _______, _______, _______,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                     KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_HEX] = LAYOUT_split_3x6_5_hlc(
  TOBAS,   _______, _______, _______, _______, _______,                                             _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                             _______, OSMRGUI, OSMRSFT, OSMRALT, OSMRCTL, _______,
  _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, ALT_BSP, _______,         _______, _______, _______, _______, _______,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                     KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
  // TOBAS,   KC_TAB,  KC_D,    KC_E,    KC_F,    _______,                                             KC_PIPE, KC_7,    KC_8,    KC_9,    KC_TILD, _______,
  // _______, _______, KC_A,    KC_B,    KC_C,    _______,                                             KC_SLSH, KC_4,    KC_5,    KC_6,    KC_COLN, _______,
  // _______, KC_LSFT, TOBAS,   _______, _______, _______, _______, _______,         _______, _______, KC_MINS, KC_1,    KC_2,    KC_3,    SFT_DOT, _______,
  //                            _______, _______, _______, KC_BSPC, _______,         _______,  KC_0,   _______, _______, _______,
  //       KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                     KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_FUNCTION] = LAYOUT_split_3x6_5_hlc( \
  TOADJ,   DF_LAYR, TOBAS,   EE_CLR,  DB_TOGG, _______,                                             _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F13,\
  SM_LOGN, OSMLSFT, OSMLALT, OSMLCTL, OSMLGUI, _______,                                             _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,  KC_F14,\
  MACSLEP, _______, TOHEX,   _______, _______, _______, _______, _______,         _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F12,  KC_F15,\
                             _______, _______, _______, KC_DEL,  _______,         _______, _______, _______, _______, KC_NO, \
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                    KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_APPSWITCH] = LAYOUT_split_3x6_5_hlc(
  _______, KC_BSPC, KC_Z,    _______, _______, _______,                                            _______, _______, _______, _______, _______, _______,
  _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,                                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, KC_X,    KC_Z,    _______, _______, _______,
                             _______, _______, _______, _______, _______,        _______, _______, _______, _______, KC_NO,
        KC_MUTE, KC_NO,  KC_NO, KC_NO, KC_NO,                                                                    KC_MUTE, KC_NO, KC_NO, KC_NO, KC_NO
),

[_ADJUST] = LAYOUT_split_3x6_5_hlc( \
  TOBAS,   TOBAS,   _______, EE_CLR,  QK_RBT,  _______,                                             _______, _______,  _______,  _______, _______, _______,  \
  TB_MENU, _______, _______, _______, _______, _______,                                             MENU_AD, MENU_MD,  MENU_MU,  MENU_AU, _______, _______,\
  _______, _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______,  _______,  _______, _______, _______,\
                             _______, _______, _______, _______, _______,         _______, _______, _______, _______, KC_NO, \
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

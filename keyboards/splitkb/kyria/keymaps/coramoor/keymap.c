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
    CM_ESC,
    CM_PASS,
    CM_PAS2,
    CM_CAPS,
    CM_CAP2,
    CM_BOOT,
    CM_BOT2,
    CM_SLEP,
    CM_LOGN,
    CM_LOG2,
    CM_PLAY,
    CM_PLY2,
    CM_PREV,
    CM_NEXT,
    CM_NXT2,
    CM_OFUN,
    CM_OFN2,
    CM_CAP3,
    CM_SCLN,
    CM_SCN2
};


const uint16_t PROGMEM parn_combo[] = {KC_LPRN, KC_RPRN, COMBO_END};
const uint16_t PROGMEM curb_combo[] = {KC_LCBR, KC_RCBR, COMBO_END};
const uint16_t PROGMEM brac_combo[] = {KC_LBRC, KC_RBRC, COMBO_END};
const uint16_t PROGMEM escape_combo[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM leader_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM leader2_combo[] = {KC_U, KC_Y, COMBO_END};
const uint16_t PROGMEM capsword_combo[] = {SFT_Z, SFT_QUE, COMBO_END};
const uint16_t PROGMEM capsword2_combo[] = {LHM_S, RHM_E, COMBO_END};
const uint16_t PROGMEM qkboot_combo[] = {LOL_THM, KC_Q, KC_B, COMBO_END};
const uint16_t PROGMEM qkboot2_combo[] = {CLOL_THM, KC_Q, KC_B, COMBO_END};
const uint16_t PROGMEM sleep_combo[] = {LIL_THM, KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM login_combo[] = {LIL_THM, KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM login2_combo[] = {LIL_THM, LHM_R, LHM_S, COMBO_END};
const uint16_t PROGMEM play_combo[] = {LIL_THM, KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM play2_combo[] = {LIR_THM, KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM prev_combo[] = {LIR_THM, KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM next_combo[] = {LIR_THM, KC_DOT, SFT_QUE, COMBO_END};
const uint16_t PROGMEM next2_combo[] = {LIR_THM, KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM osfun_combo[] = {LIL_THM, LIR_THM, COMBO_END};
const uint16_t PROGMEM osfun2_combo[] = {LIL_THM, CLIR_THM, COMBO_END};
const uint16_t PROGMEM capsword3_combo[] = {KC_LSFT, SFT_DOT, COMBO_END};
const uint16_t PROGMEM semicolon_combo[] = {RHM_I, RHM_O, COMBO_END};
const uint16_t PROGMEM semicolon2_combo[] = {KC_I, KC_O, COMBO_END};

combo_t key_combos[] = {
  [CM_PARN] = COMBO(parn_combo, SM_PAR),
  [CM_CURB] = COMBO(curb_combo, SM_CUR),
  [CM_BRAC] = COMBO(brac_combo, SM_BRC),
  [CM_ESC] = COMBO(escape_combo, SM_ESC),
  [CM_PASS] = COMBO(leader_combo, LEADER),
  [CM_PAS2] = COMBO(leader2_combo, SM_ESC),
  [CM_CAPS] = COMBO(capsword_combo, SM_CW),
  [CM_CAP2] = COMBO(capsword2_combo, SM_CW),
  [CM_BOOT] = COMBO(qkboot_combo, QK_BOOT),
  [CM_BOT2] = COMBO(qkboot2_combo, QK_BOOT),
  [CM_SLEP] = COMBO(sleep_combo, MACSLEP),
  [CM_LOGN] = COMBO(login_combo, SM_LOGN),
  [CM_LOG2] = COMBO(login2_combo, SM_LOGN),
  [CM_PLAY] = COMBO(play_combo, KC_MPLY),
  [CM_PLY2] = COMBO(play2_combo, KC_MPLY),
  [CM_PREV] = COMBO(prev_combo, KC_MPRV),
  [CM_NEXT] = COMBO(next_combo, KC_MNXT),
  [CM_NXT2] = COMBO(next2_combo, KC_MNXT),
  [CM_OFUN] = COMBO(osfun_combo, OSL_FUN),
  [CM_OFN2] = COMBO(osfun2_combo, OSL_FUN),
  [CM_CAP3] = COMBO(capsword2_combo, SM_CW),
  [CM_SCLN] = COMBO(semicolon_combo, KC_COLN),
  [CM_SCN2] = COMBO(semicolon2_combo, KC_COLN)
};

  const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
      [_BASE] =       { ENCODER_CCW_CW(MOV_LFT, MOV_RGT),                  ENCODER_CCW_CW(KC_WH_U, KC_WH_D)  },
      [_NAVIGATION] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),                  ENCODER_CCW_CW(LGUI(KC_MINS), LGUI(KC_EQL)) },
      [_VIM] =        { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),                  ENCODER_CCW_CW(LGUI(KC_MINS), LGUI(KC_EQL)) },
      [_COLEMAK_DH] = { ENCODER_CCW_CW(_______, _______),                  ENCODER_CCW_CW(_______, _______) },
      [_HEX] =        { ENCODER_CCW_CW(_______, _______),                  ENCODER_CCW_CW(_______, _______) },
      [_NUMPAD] =     { ENCODER_CCW_CW(_______, _______),                  ENCODER_CCW_CW(_______, _______) },
      [_SYMBOL] =     { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),                  ENCODER_CCW_CW(LGUI(KC_MINS), LGUI(KC_EQL)) },
      [_FUNCTION] =   { ENCODER_CCW_CW(_______, _______),                  ENCODER_CCW_CW(_______, _______) },
      [_APPSWITCH] =  { ENCODER_CCW_CW(_______, _______),                  ENCODER_CCW_CW(_______, _______) },
      [_ADJUST] =     { ENCODER_CCW_CW(MENU_MD, MENU_MU),                  ENCODER_CCW_CW(MENU_AD, MENU_AU) },
  };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT(
  SM_ESC,  KC_Q,   KC_W,    KC_F,    KC_P,    KC_B,                                            KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, KC_MINS,
  KC_CAPS, LHM_A,  LHM_R,   LHM_S,   LHM_T,   KC_G,                                            KC_M,    RHM_N,   RHM_E,   RHM_I,   RHM_O,   KC_SCLN,
  KC_MINS, SFT_Z,  KC_X,    KC_C,    KC_D,    KC_V,    UIL_THM, UOL_THM,   UOR_THM,  UIR_THM,  KC_K,    KC_H,    KC_COMM, KC_DOT,  SFT_QUE, OSMRGUI,
                            KC_NO,   LUTHUM1, LUTHUM2, LIL_THM, LOL_THM,   LOR_THM,  LIR_THM,  RUTHUM2, RUTHUM1, KC_NO
),

[_GAMING] = LAYOUT(
  KC_ESC,  KC_Q,   KC_W,    KC_E,    KC_R,     KC_T,                                              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_TAB,  LHM_A,  LQM_S,   LHM_D,   LHM_F,    KC_G,                                              KC_H,    RHM_J,   RHM_K,   RHM_L,   RHM_SCN, KC_QUOT,
  KC_LCTL, KC_Z,   KC_X,    KC_C,    KC_V,     KC_B,    CUIL_THM, CUOL_THM,   CUOR_THM, CUIR_THM, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TOBAS,
                            KC_NO,   LUTHUM1,  LUGTHUM, LIL_THM,  LOL_THM,    LOR_THM,  LIR_THM,  RUTHUM2, RUTHUM1, KC_NO
),

[_GAMENUM] = LAYOUT(
  KC_ESC,  KC_6,   KC_7,    KC_8,    KC_9,     KC_0,                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_TAB,  KC_1,   KC_2,    KC_3,    KC_4,     KC_5,                                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LCTL, KC_Z,   KC_X,    KC_C,    KC_V,     KC_B,    UIL_THM, UOL_THM,    UOR_THM, UIR_THM, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TOBAS,
                            KC_NO,   LUTHUM1,  KC_LSFT, KC_SPC,  LOL_THM,    LOR_THM, LIR_THM, RUTHUM2, RUTHUM1, KC_NO
),

[_COLEMAK_DH] = LAYOUT(
  SM_ESC,  KC_Q,   KC_W,    KC_F,    KC_P,    KC_B,                                            KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, PASSPAL,
  CTL_BSP, KC_A,   KC_R,    KC_S,    KC_T,    KC_G,                                            KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    CTL_QUO,
  KC_MINS, SFT_Z,  KC_X,    KC_C,    KC_D,    KC_V,    UIL_THM, UOL_THM, CUOR_THM, CUIR_THM, KC_K,    KC_H,    KC_COMM, KC_DOT,  SFT_QUE, OSMRGUI,
                            KC_NO,   LUTHUM1, LUTHUM2, LIL_THM, LOL_THM, LOR_THM, LIR_THM, RUTHUM2, RUTHUM1, KC_NO
),

[_NAVIGATION] = LAYOUT(
    _______, KC_BSPC, MC_SWRI, MOV_LFT, MOV_RGT, _______, 		                                 KC_PGDN, SEL_LIN, SEL_WRD, KC_PGUP, _______, _______,
    KC_BSPC, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, _______,                                        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_SCLN, TD_QUOT,
    LLOCK,   MONUM,   KC_ENT,  TD_COPY, TD_PAST, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, KC_ENT,
                               KC_NO,   _______, _______, _______, _______,    KC_ENT,  KC_SPC,  _______, _______, _______
),

[_NUMPAD] = LAYOUT(
  _______, KC_BSPC, KC_TAB,  _______, _______, _______,                                        KC_GRV,  KC_7,    KC_8,    KC_9,    KC_SLSH, PASSPAL,
  KC_BSPC, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, _______,                                        KC_MINS, KC_4,    KC_5,    KC_6,    KC_COLN, KC_QUOT,
  LLOCK,   MOVIM,   _______, _______, _______, _______, _______, _______,    _______, _______, KC_EQL,  KC_1,    KC_2,    KC_3,    KC_DOT,  KC_ENT,
                             KC_NO,   _______, _______, _______, _______,    KC_ENT,  KC_0,    _______, _______, KC_NO
),

[_SYMBOL] = LAYOUT(
  _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, _______,                                        _______, _______, _______, _______, _______, _______,
  ALT_BSP, KC_AT,   KC_BSLS, KC_UNDS, KC_PIPE, TIPS,                                           _______, OSMRGUI, OSMRSFT, OSMRALT, OSMRCTL, KC_QUOT,
  _______, KC_LBRC, KC_RBRC, KC_LT,   KC_GT,   _______, _______, _______,    _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, LLOCK,
                             KC_NO,   _______, ALT_BSP, KC_BSPC, XCTHUM,     _______, _______, _______, _______, _______
),

[_VIM] = LAYOUT(
  _______, KC_BSPC, KC_TAB,  _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
  _______, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, _______,                                        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______,
                             KC_NO,   _______, _______, KC_BSPC, XCTHUM,     _______, _______, _______, _______, _______
),

[_HEX] = LAYOUT(
  _______, KC_TAB,  KC_D,    KC_E,    KC_F,    _______,                                        KC_PIPE, KC_7,    KC_8,    KC_9,    KC_TILD, _______,
  _______, _______, KC_A,    KC_B,    KC_C,    _______,                                        KC_SLSH, KC_4,    KC_5,    KC_6,    KC_COLN, _______,
  _______, KC_LSFT, TOBAS,   _______, _______, _______, _______, _______,    _______, _______, KC_MINS, KC_1,    KC_2,    KC_3,    SFT_DOT, _______,
                             KC_NO,   _______, KC_BSPC, KC_BSPC, _______,    _______,  KC_0,   _______, _______, _______
),

[_FUNCTION] = LAYOUT( \
  TOADJ,   _______, _______, _______, _______, _______,                                         _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F13,\
  SM_LOGN, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, _______,                                         _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,  KC_F14,\
  MACSLEP, _______, TOHEX,   _______, _______, _______, _______, _______,     _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F12,  KC_F15,\
                             KC_NO,   _______, _______, KC_DEL,  _______,     _______, _______, _______, _______, KC_NO \
),

[_APPSWITCH] = LAYOUT(
  _______, KC_BSPC, KC_Z,    _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                                        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, KC_X,    KC_Z,    _______, _______, _______,
                             KC_NO,   _______, _______, _______, _______,    _______, _______, _______, _______, KC_NO
),

  // KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  // _______, KC_LBRC, KC_RBRC, KC_MINS, KC_BSLS, TIPS,                                           _______, OSMRGUI, OSMRSFT, OSMRALT, OSMRCTL, _______,
  // _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, TIPS,    _______, _______,    _______, _______, KC_EQL,  _______, _______, _______, KC_DOT,  KC_ENT,
  //                            KC_NO,   _______, _______, _______, OSMLSFT,    _______, _______, _______, _______, KC_NO

[_ADJUST] = LAYOUT( \
  TOBAS,   TOBAS,   _______, EE_CLR,  QK_RBT,  _______,                                         _______, _______,  _______,  _______, _______, _______,  \
  _______, _______, _______, _______, _______, _______,                                         MENU_AD, MENU_MD,  MENU_MU,  MENU_AU, _______, _______,\
  _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______,  _______,  _______, _______, _______,\
                             KC_NO,   _______, _______, _______, _______,     _______, _______, _______, _______, KC_NO \
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

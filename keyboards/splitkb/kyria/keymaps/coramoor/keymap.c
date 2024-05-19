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

const uint16_t PROGMEM bootloader_combo[] = {LIL_THM, KC_Q, KC_T, COMBO_END};
const uint16_t PROGMEM bootloadercm_combo[] = {LIL_THM, KC_Q, KC_B, COMBO_END};
const uint16_t PROGMEM sleep_combo[] = {LIL_THM, KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM login_combo[] = {LIR_THM, KC_O, KC_P, COMBO_END};
// const uint16_t PROGMEM logincm_combo[] = {CLIR_THM, KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM parn_combo[] = {KC_LPRN, KC_RPRN, COMBO_END};
const uint16_t PROGMEM curb_combo[] = {KC_LCBR, KC_RCBR, COMBO_END};
const uint16_t PROGMEM brac_combo[] = {KC_LBRC, KC_RBRC, COMBO_END};
const uint16_t PROGMEM escape_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM escape2_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM mtescape_combo[] = {RHM_J, RHM_K, COMBO_END};
const uint16_t PROGMEM mtescape2_combo[] = {LHM_D, LHM_F, COMBO_END};
const uint16_t PROGMEM angb_combo[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM cw_combo[] = {LOL_THM, LOR_THM, COMBO_END};

combo_t key_combos[] = {
  COMBO(bootloader_combo, QK_BOOT),
  COMBO(bootloadercm_combo, QK_BOOT),
  COMBO(sleep_combo, MACSLEP),
  COMBO(login_combo, SM_LOGN),
  // COMBO(logincm_combo, SM_LOGN),
  COMBO(parn_combo, SM_PAR),
  COMBO(curb_combo, SM_CUR),
  COMBO(brac_combo, SM_BRC),
  COMBO(escape_combo, KC_ESC),
  COMBO(escape2_combo, KC_ESC),
  COMBO(mtescape_combo, KC_ESC),
  COMBO(mtescape2_combo, KC_ESC),
  COMBO(angb_combo, SM_ANG),
  COMBO(cw_combo, SM_CW)
};

  const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
      [_BASE] =       { ENCODER_CCW_CW(C(KC_H), C(KC_L)),                  ENCODER_CCW_CW(KC_MS_WH_DOWN, KC_MS_WH_UP)  },
      [_NAVIGATION] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN),        ENCODER_CCW_CW(LALT(KC_UP), LALT(KC_DOWN)) },
      [_MACROS] =     { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),                  ENCODER_CCW_CW(LGUI(KC_MINS), LGUI(KC_EQL)) },
      [_COLEMAK_DH] = { ENCODER_CCW_CW(_______, _______),                  ENCODER_CCW_CW(_______, _______) },
      [_HEX] =        { ENCODER_CCW_CW(_______, _______),                  ENCODER_CCW_CW(_______, _______) },
      [_NUMPAD] =     { ENCODER_CCW_CW(_______, _______),                  ENCODER_CCW_CW(_______, _______) },
      [_SYMBOL] =     { ENCODER_CCW_CW(_______, _______),                  ENCODER_CCW_CW(_______, _______) },
      [_FUNCTION] =   { ENCODER_CCW_CW(_______, _______),                  ENCODER_CCW_CW(_______, _______) },
      [_MEDIA] =      { ENCODER_CCW_CW(_______, _______),                  ENCODER_CCW_CW(_______, _______) },
      [_ADJUST] =     { ENCODER_CCW_CW(MENU_MD, MENU_MU),                  ENCODER_CCW_CW(MENU_AD, MENU_AU) },
  };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT(
  QK_GESC, KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    PASSPAL,
  KC_AT,   LHM_A,  LHM_S,   LHM_D,   LHM_F,   KC_G,                                            KC_H,    RHM_J,   RHM_K,   RHM_L,   RHM_SCN, KC_QUOT,
  KC_MINS, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,   CUIL_THM, CUOL_THM,  CUOR_THM, CUIR_THM, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_PIPE,
                            KC_NO,   LUTHUM1, CLUTHUM2, LIL_THM, LOL_THM,    LOR_THM, LIR_THM, RUTHUM2, RUTHUM1, KC_NO
),

[_GAMING] = LAYOUT(
  KC_ESC,  KC_Q,   KC_W,    KC_E,    KC_R,     KC_T,                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_TAB,  KC_A,   KC_S,    KC_D,    KC_F,     KC_G,                                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LCTL, KC_Z,   KC_X,    KC_C,    KC_V,     KC_B,    UIG_THM, UOL_THM,    UOR_THM, UIR_THM, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TOBAS,
                            KC_NO,   LUTHUM1,  LUGTHUM, LIG_THM, LOG_THM,    LOR_THM, LIR_THM, RUTHUM2, RUTHUM1, KC_NO
),

[_GAMENUM] = LAYOUT(
  KC_ESC,  KC_6,   KC_7,    KC_8,    KC_9,     KC_0,                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_TAB,  KC_1,   KC_2,    KC_3,    KC_4,     KC_5,                                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LCTL, KC_Z,   KC_X,    KC_C,    KC_V,     KC_B,    UIL_THM, UOL_THM,    UOR_THM, UIR_THM, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TOBAS,
                            KC_NO,   LUTHUM1,  KC_LSFT, KC_SPC,  LOL_THM,    LOR_THM, LIR_THM, RUTHUM2, RUTHUM1, KC_NO
),

[_COLEMAK_DH] = LAYOUT(
  QK_GESC, KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    PASSPAL,
  HYP_TAB, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, MEH_QUO,
  OSMLALT, LHM_Z,  LHM_X,    LHM_C,    LHM_V,    KC_B,    CUIL_THM, CUOL_THM,    CUOR_THM, CUIR_THM, KC_N,    RHM_M,    RHM_COM, RHM_DOT,  RHM_SLS, OSMHYPR,
                            KC_NO,   LUTHUM1, CLUTHUM2, LIL_THM, LOL_THM,    LOR_THM, LIR_THM, RUTHUM2, RUTHUM1, KC_NO

  // QK_GESC, KC_Q,   KC_W,    KC_F,    KC_P,    KC_B,                                           KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
  // CTL_CW,  KC_A,   KC_R,    KC_S,    KC_T,    KC_G,                                           KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    CTL_QUO,
  // ALT_MIN, LHM_Z,  KC_X,    KC_C,    KC_D,    KC_V,    UIL_THM, UOL_THM,    UOR_THM, UIR_THM, KC_K,    KC_H,    KC_COMM, KC_DOT,  RHM_SLS, ALT_ENT,
  //                           KC_NO,   LUTHUM1, LUTHUM2, LIL_THM, LOL_THM,    LOR_THM, LIR_THM, RUTHUM2, RUTHUM1, KC_NO
),

[_NAVIGATION] = LAYOUT(
    RMT_PLY, MC_SWAP, MOV_LFT, MC_SWRI, MOV_RGT, _______,  		                                 KC_HOME, _______,  SEL_LIN, KC_END,  _______, _______,
    _______, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, _______,                                        KC_LEFT, KC_DOWN,  KC_UP,   KC_RGHT, KC_SCLN, TD_QUOT,
    LLOCK,   _______, _______, TD_COPY, TD_PAST, _______, _______, _______,    _______, _______, _______, _______,  _______, _______, _______,  KC_ENT,
    KC_NO,   _______, _______, _______, _______,    _______, _______, KC_NO,   KC_NO,    KC_NO
),

[_NUMPAD] = LAYOUT(
  _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, TIPS,                                           KC_TILD, KC_7,    KC_8,    KC_9,    KC_SLSH, PASSPAL,
  _______, LHM_AT,  LHM_BSL, LHM_UND, LHM_PIP, KC_PIPE,                                        KC_MINS, KC_4,    KC_5,    KC_6,    KC_COLN, KC_QUOT,
  LLOCK,   _______, KC_LBRC, KC_RBRC, _______, _______, _______, _______,    _______, _______, KC_EQL,  KC_1,    KC_2,    KC_3,    KC_DOT,  KC_ENT,
                             KC_NO,   _______, _______, _______, _______,    _______, KC_0,    _______, _______, KC_NO
),

[_SYMBOL] = LAYOUT(
  _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, TIPS,                                           KC_GRV,  KC_AMPR, KC_ASTR, KC_LPRN, KC_SLSH, _______,
  _______, KC_AT,   KC_BSLS, KC_UNDS, KC_PIPE, KC_PIPE,                                        KC_UNDS, KC_DLR,  KC_PERC, KC_CIRC, KC_COLN, KC_QUOT,
  _______, KC_LBRC, KC_RBRC, _______, _______, _______, _______, _______,    _______, _______, KC_PLUS, KC_EXLM, KC_AT,   KC_HASH, KC_DOT,  LLOCK,
                             KC_NO,   _______, _______, KC_SPC,  KC_ENT,     _______, _______, _______, KC_NO,   KC_NO
),

[_MACROS] = LAYOUT(
  _______, _______, _______, DM_REC1, DM_REC2, _______,                                        _______, _______, _______, _______, _______, _______,
  SFT_MIN, _______, DM_RSTP, DM_PLY1, DM_PLY2, _______,                                        _______, OSMRGUI, OSMRSFT, OSMRALT, OSMRCTL, _______,
  _______, _______, _______, _______, _______, _______, KC_BTN1, KC_BTN2,    _______, _______, _______, _______, _______, _______, _______, _______,
                             KC_NO,   _______, _______, _______, _______,    _______, _______, KC_MUTE, KC_NO,    KC_NO
),

[_HEX] = LAYOUT(
  _______, KC_TAB,  _______, _______, _______, _______,                                        KC_PIPE, KC_7,    KC_8,    KC_9,    KC_TILD, _______,
  _______, _______, KC_SLSH, _______, _______, _______,                                        KC_UNDS, KC_4,    KC_5,    KC_6,    KC_COLN, _______,
  _______, TOBAS,   TOBAS,   _______, _______, _______, _______, _______,    _______, _______, KC_MINS, KC_1,    KC_2,    KC_3,    KC_DOT,  _______,
                             KC_NO,   _______, KC_BSPC, KC_BSPC, _______,    _______,  KC_0,   _______, KC_ENT, KC_NO
),

[_FUNCTION] = LAYOUT( \
  TOADJ,   _______, _______, _______, _______, _______,                                         _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F13,\
  _______, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, _______,                                         _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,  KC_F14,\
  _______, _______, TOHEX,   _______, _______, _______, _______, _______,     _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F12,  KC_F15,\
                             KC_NO,   _______, _______, CAD,     _______,     _______, _______, _______, _______, KC_NO \
),

[_MEDIA] = LAYOUT(
  KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  _______, KC_LBRC, KC_RBRC, KC_MINS, KC_BSLS, TIPS,                                           _______, OSMRGUI, OSMRSFT, OSMRALT, OSMRCTL, _______,
  _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, TIPS,    _______, _______,    _______, _______, KC_EQL,  _______, _______, _______, KC_DOT,  KC_ENT,
                             KC_NO,   _______, _______, _______, OSMLSFT,    _______, _______, _______, _______, KC_NO
),

  // _______, _______, _______, _______, _______,  _______,                                         APP_L,   APP_D,    APP_U,   APP_R, _______, _______,
  // _______, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI,  _______,                                         MON_L,   MON_D,    MON_U,   MON_R, _______, _______,
  // _______, _______, _______, _______, _______,  _______, OSMLSFT, _______,     _______, OSMRSFT, SPC_L,   SPC_D,    SPC_U,   SPC_R, _______, _______,
  //                            KC_NO,   _______, _______,  OSMLSFT, _______,     _______, _______, _______, _______, KC_NO

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

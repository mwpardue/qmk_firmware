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
const uint16_t PROGMEM logincm_combo[] = {LIR_THM, KC_Y, KC_SCLN, COMBO_END};
const uint16_t PROGMEM parn_combo[] = {KC_LPRN, KC_RPRN, COMBO_END};
const uint16_t PROGMEM curb_combo[] = {KC_LCBR, KC_RCBR, COMBO_END};
const uint16_t PROGMEM brac_combo[] = {KC_LBRC, KC_RBRC, COMBO_END};
const uint16_t PROGMEM escape_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM escape2_combo[] = {KC_D, KC_F, COMBO_END};

combo_t key_combos[] = {
  COMBO(bootloader_combo, QK_BOOT),
  COMBO(bootloadercm_combo, QK_BOOT),
  COMBO(sleep_combo, MACSLEP),
  COMBO(login_combo, SM_LOGN),
  COMBO(logincm_combo, SM_LOGN),
  COMBO(parn_combo, SM_PAR),
  COMBO(curb_combo, SM_CUR),
  COMBO(brac_combo, SM_BRC),
  COMBO(escape_combo, KC_ESC),
  COMBO(escape2_combo, KC_ESC)
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
      [_ADJUST] =     { ENCODER_CCW_CW(RENC_MDM, RENC_MDP),                ENCODER_CCW_CW(RENC_ADM, RENC_ADP) },
  };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT(
  QK_GESC, KC_Q,   KC_W,    KC_E,    KC_R,     KC_T,                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  ALT_TAB, KC_A,   KC_S,    KC_D,    KC_F,     KC_G,                                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KIT_MOD, KC_Z,   KC_X,    KC_C,    KC_V,     KC_B,    UIL_THM, UOL_THM,    UOR_THM, UIR_THM, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, OSMRGUI,
                            KC_NO,   LUTHUM1,  LUTHUM2, LIL_THM, LOL_THM,    LOR_THM, LIR_THM, RUTHUM2, RUTHUM1, KC_NO
),

[_GAMING] = LAYOUT(
  KC_ESC,  KC_Q,   KC_W,    KC_E,    KC_R,     KC_T,                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_TAB,  KC_A,   KC_S,    KC_D,    KC_F,     KC_G,                                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LCTL, KC_Z,   KC_X,    KC_C,    KC_V,     KC_B,    UIL_THM, UOL_THM,    UOR_THM, UIR_THM, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TOBAS,
                            KC_NO,   LUTHUM1,  MOGAMN,  KC_SPC,  KC_LSFT,    LOR_THM, LIR_THM, RUTHUM2, RUTHUM1, KC_NO
),

[_GAMENUM] = LAYOUT(
  KC_ESC,  KC_1,   KC_2,    KC_3,    KC_4,     KC_5,                                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_TAB,  KC_6,   KC_7,    KC_8,    KC_9,     KC_0,                                           KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LCTL, KC_Z,   KC_X,    KC_C,    KC_V,     KC_B,    UIL_THM, UOL_THM,    UOR_THM, UIR_THM, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TOBAS,
                            KC_NO,   LUTHUM1,  KC_LSFT, KC_SPC,  LOL_THM,    LOR_THM, LIR_THM, RUTHUM2, RUTHUM1, KC_NO
),

[_COLEMAK_DH] = LAYOUT(
  QK_GESC, KC_Q,   KC_W,    KC_F,    KC_P,    KC_B,                                           KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL,
  ALT_TAB, KC_A,   KC_R,    KC_S,    KC_T,    KC_G,                                           KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    TD_QUOT,
  KIT_MOD, KC_Z,   KC_X,    KC_C,    KC_D,    KC_V,    UIL_THM, UOL_THM,    UOR_THM, UIR_THM, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, OSMRGUI,
                            KC_NO,   LUTHUM1, LUTHUM2, LIL_THM, LOL_THM,    LOR_THM, LIR_THM, RUTHUM2, RUTHUM1, KC_NO
),

[_NAVIGATION] = LAYOUT(
  _______, MC_SWAP, MOV_LFT, MC_SWRI, MOV_RGT, TD_SSFL,  		                               WD_LEFT, SEL_WRD,  SEL_LIN, WD_RGHT, PASSPAL, _______,
  KC_TAB,  OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, TD_SNIP,                                        KC_LEFT, KC_DOWN,  KC_UP,   KC_RGHT, KC_SCLN, TD_QUOT,
  LLOCK,   KC_TAB,  XCASE,   TD_COPY, TD_PAST, _______, _______, _______,    _______, _______, _______, KC_HOME,  _______, _______, KC_END,  KC_ENT,
						     KC_NO,   KIT_RST, _______, _______, _______,    KC_ENT,  KC_SPC,  KC_NO,   KC_NO,    KC_NO
),

[_NUMPAD] = LAYOUT(
  _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, TIPS,                                           KC_TILD, KC_7,    KC_8,    KC_9,    KC_SLSH, PASSPAL,
  _______, LHM_AT,  LHM_BSL, LHM_UND, LHM_PIP, KC_PIPE,                                        KC_MINS, KC_4,    KC_5,    KC_6,    KC_COLN, TD_QUOT,
  LLOCK,   KC_LBRC, KC_RBRC, XCASE,   _______, LLOCK,   _______, _______,    _______, _______, KC_EQL,  KC_1,    KC_2,    KC_3,    KC_DOT,  KC_ENT,
                             KC_NO,   _______, _______, _______, _______,    KC_ENT,  KC_0,    TD_HTTP, ENT_HYP, KC_NO
),

[_SYMBOL] = LAYOUT(
  _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, TIPS,                                           KC_GRV,  KC_AMPR, KC_ASTR, KC_LPRN, KC_SLSH, _______,
  _______, KC_AT,   KC_BSLS, KC_UNDS, KC_PIPE, KC_PIPE,                                        KC_UNDS, KC_DLR,  KC_PERC, KC_CIRC, KC_COLN, TD_QUOT,
  _______, KC_LBRC, KC_RBRC, _______, _______, _______, _______, _______,    _______, _______, KC_PLUS, KC_EXLM, KC_AT,   KC_HASH, KC_DOT,  LLOCK,
                             KC_NO,   _______, _______, _______, _______,    _______, _______, _______, KC_NO,   KC_NO
),

[_MACROS] = LAYOUT(
  _______, _______, SCRN_L,  _______, SCRN_R,  _______,                                        _______, KC_MPRV,  KC_MPLY, KC_MNXT, PASSPAL, PASSPAL,
  _______, TD_MONL, TD_MONL, TD_MONM, TD_MONR, _______,                                        TD_HTTP, OSMRGUI,  OSMRSFT, OSMRALT, OSMRCTL, _______,
  _______, _______, MAX_SCR, TD_MONB, _______, _______, KC_BTN1, KC_BTN2,    _______, _______, _______, MAX_SCR,  _______, _______, _______, _______,
                             KC_NO,   _______, _______, MOFUN,   _______,    _______, _______, KC_MUTE, KC_NO,    KC_NO
),

[_HEX] = LAYOUT(
  _______, KC_TAB,  _______, _______, _______, _______,                                        KC_PIPE, KC_7,    KC_8,    KC_9,    KC_TILD, _______,
  _______, _______, KC_SLSH, _______, _______, _______,                                        KC_UNDS, KC_4,    KC_5,    KC_6,    KC_COLN, _______,
  _______, TOBAS,   TOBAS,   _______, _______, _______, _______, _______,    _______, _______, KC_MINS, KC_1,    KC_2,    KC_3,    KC_DOT,  _______,
                             KC_NO,   _______, KC_BSPC, KC_BSPC, _______,    _______,  KC_0,   KC_ENT,  KC_ENT, KC_NO
),

[_FUNCTION] = LAYOUT( \
  _______, TOADJ,   TOBAS,   TOCMK,   TOGAM,   CAD,                                             _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,\
  _______, _______, TG_OS,   DB_TOGG, _______, _______,                                         _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,  _______,\
  _______, _______, TOHEX,   DF_TOGG, _______, _______, _______, _______,     _______, _______, _______, KC_F1,   KC_F2,   KC_F3,   KC_F12,  _______,\
                             KC_NO,   _______, _______, _______, _______,     _______, _______, _______, _______, KC_NO \
),

[_MEDIA] = LAYOUT( \
  _______, _______, _______, _______, _______,  _______,                                        _______, _______, _______, _______, _______, _______,  \
  RGB_ALP, RGB_SPP, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,                                         RGB_CHG, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______,\
  RGB_ALM, RGB_SPM, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, _______, _______,     _______, _______, RGB_MOD, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,\
                             KC_NO,   _______, _______, _______, _______,     _______, _______, _______, _______, KC_NO \
),

[_ADJUST] = LAYOUT( \
  _______, TOBAS,   _______, EE_CLR,  QK_RBT,  _______,                                         RGB_ALM, RGB_ALP,  RGB_SPM,  RGB_SPP, _______, _______,  \
  ACH_TTP, SGT_TTP, MDT_TTP, SFT_TTP, GQT_TTP, DT_UP,                                           RGB_CHG, RGB_HUI,  RGB_SAI,  RGB_VAI, RGB_SPI, _______,\
  ACH_TTM, SGT_TTM, MDT_TTM, SFT_TTM, GQT_TTM, DT_DOWN, _______, _______,     _______, _______, RGB_MOD, RGB_HUD,  RGB_SAD,  RGB_VAD, RGB_SPD, _______,\
                             KC_NO,   ACH_TTM, _______, _______, _______,     _______, _______, _______, ACH_TTP, KC_NO \
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

/*
Copyright 2022 fgoodwin <fgoodwin@north-tech.net>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H
#include "coramoor.h"

#ifdef OLED_ENABLE
# include "oled.c"
#endif

const uint16_t PROGMEM bootloader_combo[] = {LTHUM1, KC_Q, KC_T, COMBO_END};
const uint16_t PROGMEM bootloadercm_combo[] = {LTHUM1, KC_Q, KC_B, COMBO_END};
const uint16_t PROGMEM sleep_combo[] = {LTHUM2, KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM login_combo[] = {LTHUM2, LHM_R, LHM_S, COMBO_END};
// const uint16_t PROGMEM logincm_combo[] = {CLIR_THM, KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM parn_combo[] = {KC_LPRN, KC_RPRN, COMBO_END};
const uint16_t PROGMEM curb_combo[] = {KC_LCBR, KC_RCBR, COMBO_END};
const uint16_t PROGMEM brac_combo[] = {KC_LBRC, KC_RBRC, COMBO_END};
const uint16_t PROGMEM mtescape2_combo[] = {LHM_S, LHM_T, COMBO_END};
const uint16_t PROGMEM angb_combo[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM cw_combo[] = {LTHUM2, RTHUM1, COMBO_END};
const uint16_t PROGMEM copy_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM paste_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM pastehistory_combo[] = {KC_X, KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM pw_combo[] = {RTHUM2, RHM_I, RHM_O, COMBO_END};
const uint16_t PROGMEM mon_combo[] = {LTHUM4, LTHUM5, COMBO_END};

combo_t key_combos[] = {
  COMBO(bootloader_combo, QK_BOOT),
  COMBO(bootloadercm_combo, QK_BOOT),
  COMBO(sleep_combo, MACSLEP),
  COMBO(login_combo, SM_LOGN),
  // COMBO(logincm_combo, SM_LOGN),
  COMBO(parn_combo, SM_PAR),
  COMBO(curb_combo, SM_CUR),
  COMBO(brac_combo, SM_BRC),
  COMBO(mtescape2_combo, KC_ESC),
  COMBO(angb_combo, SM_ANG),
  COMBO(cw_combo, SM_CW),
  COMBO(copy_combo, COPY),
  COMBO(paste_combo, PASTE),
  COMBO(pastehistory_combo, HPASTE),
  COMBO(pw_combo, PASSPAL),
  COMBO(mon_combo, MON_D)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT_split_5x6_63(
      QK_GESC, KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    PASSPAL,
      KC_GRV,  KC_Q,   KC_W,    KC_F,    KC_P,    KC_B,                                            KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, PASSPAL,
      SFT_MIN, LHM_A,  LHM_R,   LHM_S,   LHM_T,   KC_G,                                            KC_M,    RHM_N,   RHM_E,   RHM_I,   RHM_O,   SFT_QUO,
      TOADJ,   NUM_Z,  KC_X,    KC_C,    KC_D,    KC_V,                                            KC_K,    KC_H,    KC_COMM, KC_DOT,  SFT_QUE, MOFUN,
                       TAB_LFT, TAB_RGT,                                                                             KC_DOWN, KC_UP,
                                         LTHUM1,  LTHUM2,                                 RTHUM3,  RTHUM2,  RTHUM1,
                                         LTHUM3,  LTHUM4,
                                         LTHUM5
    ),

    [_MOUSE] = LAYOUT_split_5x6_63(
      _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, PNTBROW, _______,                                        _______, _______, _______, _______, _______, _______,
      _______, DRGSCRL, SNIPING, KC_BTN2, KC_BTN1, _______,                                        _______, KC_RGUI, KC_RSFT, KC_RALT, KC_RCTL, _______,
      _______, TGMOUSE, PNTMON,  PNTCART, PNTVOLM, _______,                                        _______, KC_BTN1, KC_BTN2, _______, _______, _______,
                       _______, _______,                                                                             _______, _______,
                                          _______, _______,                              KC_BTN1,  KC_BTN2, _______,
                                          _______, _______,
                                          _______
    ),

    [_GAMENUM] = LAYOUT_split_5x6_63(
      QK_GESC, KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_B,
      QK_GESC, KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    PASSPAL,
      KC_AT,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                                            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_MINS, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                                            KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_PIPE,
                       TAB_LFT, TAB_RGT,                                                                             _______, _______,
                                         _______, _______,                                _______, _______, _______,
                                         _______, _______,
                                         _______
    ),

    [_COLEMAK_DH] = LAYOUT_split_5x6_63(
      QK_GESC, KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_B,
      QK_GESC, KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                                            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    PASSPAL,
      KC_AT,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                                            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      TOADJ, LHM_Z,  LHM_X,   LHM_C,   LHM_V,   KC_B,                                            KC_N,    RHM_M,   RHM_COM, RHM_DOT, RHM_SLS, KC_PIPE,
                       TAB_LFT, TAB_RGT,                                                                             _______, _______,
                                         _______, _______,                                _______, _______, _______,
                                         _______, _______,
                                         _______
    ),

    [_NAVIGATION] = LAYOUT_split_5x6_63(
      QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_B,
      SM_LOGN, MC_SWAP, MOV_LFT, MC_SWRI, MOV_RGT, TD_SSFL,                                        KC_HOME, SEL_WRD, SEL_LIN, KC_END,  _______, _______,
      KC_BSPC, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, TD_SNIP,                                        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_SCLN, TD_QUOT,
      LLOCK,   _______, _______, TD_COPY, TD_PAST, _______,                                     _______, _______, _______, _______, _______, KC_ENT,
                       TAB_LFT,  TAB_RGT,                                                                            _______, _______,
                                         _______, _______,                                _______, _______, _______,
                                         _______, _______,
                                         _______

      // QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_B,
      // RMT_PLY, MC_SWAP, MOV_LFT, MC_SWRI, MOV_RGT, _______,  		                               KC_HOME, _______, SEL_LIN, KC_END,  _______, _______,
      // _______, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, _______,                                        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_SCLN, TD_QUOT,
      // LLOCK,   _______, _______, TD(TDCOPY), TD_PAST, _______,                                        _______, _______, _______, _______, _______, KC_ENT,
      //                  TAB_LFT, TAB_RGT,                                                                             KC_LBRC, KC_RBRC,
      //                                    LTHUM1,  LTHUM2,                                 RTHUM3,  RTHUM2,  RTHUM1,
      //                                    LTHUM3,  LTHUM4,
      //                                    LTHUM5,  LTHUM6
    ),

    [_NUMPAD] = LAYOUT_split_5x6_63(
      KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
      _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, TIPS,                                           KC_SLSH, KC_7,    KC_8,    KC_9,    KC_SLSH, PASSPAL,
      _______, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, KC_PIPE,                                        KC_MINS, KC_4,    KC_5,    KC_6,    KC_COLN, KC_QUOT,
      LLOCK,   _______, KC_LBRC, KC_RBRC, _______, _______,                                        KC_EQL,  KC_1,    KC_2,    KC_3,    KC_DOT,  KC_ENT,
                        TAB_LFT, TAB_RGT,                                                                            _______, _______,
                                         _______, _______,                                _______, KC_0,    _______,
                                         _______, TAB_RGT,
                                         TAB_LFT
    ),

    [_SYMBOL] = LAYOUT_split_5x6_63(
      KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
      _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, TIPS,                                           KC_GRV,  KC_AMPR, KC_ASTR, KC_LPRN, KC_SLSH, _______,
      _______, KC_AT,   KC_BSLS, KC_UNDS, KC_PIPE, KC_PIPE,                                        KC_UNDS, KC_DLR,  KC_PERC, KC_CIRC, KC_COLN, KC_QUOT,
      _______, KC_LBRC, KC_RBRC, _______, _______, _______,                                        KC_PLUS, KC_EXLM, KC_AT,   KC_HASH, KC_DOT,  LLOCK,
                        TAB_LFT, TAB_RGT,                                                                            KC_LBRC, KC_RBRC,
                                         _______, _______,                                _______, _______, _______,
                                         _______, TAB_RGT,
                                         TAB_LFT
    ),

    [_MACROS] = LAYOUT_split_5x6_63(
      QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_B,
      _______, _______, _______, DM_REC1, DM_REC2, _______,                                        _______, _______, _______, _______, _______, _______,
      SFT_MIN, _______, DM_RSTP, DM_PLY1, DM_PLY2, _______,                                        _______, OSMRGUI, OSMRSFT, OSMRALT, OSMRCTL, _______,
      _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
                        TAB_LFT, TAB_RGT,                                                                            KC_LBRC, KC_RBRC,
                                         _______, _______,                                _______, _______, _______,
                                         _______, _______,
                                         _______
    ),

    [_HEX] = LAYOUT_split_5x6_63(
      QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_B,
      _______, KC_TAB,  _______, _______, _______, _______,                                        KC_PIPE, KC_7,    KC_8,    KC_9,    KC_TILD, _______,
      _______, _______, KC_SLSH, _______, _______, _______,                                        KC_UNDS, KC_4,    KC_5,    KC_6,    KC_COLN, _______,
      _______, TOBAS,   TOBAS,   _______, _______, _______,                                        KC_MINS, KC_1,    KC_2,    KC_3,    KC_DOT,  _______,
                        TAB_LFT, TAB_RGT,                                                                            KC_LBRC, KC_RBRC,
                                         _______, _______,                                _______, _______, _______,
                                         _______, _______,
                                         _______
    ),

    [_FUNCTION] = LAYOUT_split_5x6_63( \
      QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_B,
      TOADJ,   _______, _______, _______, _______, _______,                                         _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F13,\
      _______, OSMLCTL, OSMLALT, OSMLSFT, OSMLGUI, _______,                                         _______, KC_F4,   KC_F5,   KC_F6,   KC_F11,  KC_F14,\
      _______, _______, TOHEX,   _______, _______, _______,                                         _______, KC_F1,   KC_F2,   KC_F3,   KC_F12,  KC_F15,\
                        TAB_LFT, TAB_RGT,                                                                            KC_LBRC, KC_RBRC,
                                         _______, _______,                                _______, _______, _______,
                                         _______, _______,
                                         _______
    ),

    [_MEDIA] = LAYOUT_split_5x6_63(
      QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_B,
      KC_TILD, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
      _______, KC_LBRC, KC_RBRC, KC_MINS, KC_BSLS, TIPS,                                           _______, OSMRGUI, OSMRSFT, OSMRALT, OSMRCTL, _______,
      _______, KC_LCBR, KC_RCBR, KC_LPRN, KC_RPRN, TIPS,                                           KC_EQL,  _______, _______, _______, KC_DOT,  KC_ENT,
                        TAB_LFT, TAB_RGT,                                                                            KC_LBRC, KC_RBRC,
                                         _______, _______,                                _______, _______, _______,
                                         _______, _______,
                                         _______
    ),

    [_ADJUST] = LAYOUT_split_5x6_63( \
      QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_B,
      TOBAS,   TOBAS,   _______, EE_CLR,  QK_RBT,  QK_BOOT,                                         _______, _______,  _______,  _______, _______, _______,  \
      _______, _______, _______, _______, _______, _______,                                         _______, _______,  _______,  _______, _______, _______,\
      TOBAS,   _______, _______, _______, _______, _______,                                         _______, _______,  _______,  _______, _______, _______,\
                        TAB_LFT, TAB_RGT,                                                                            KC_LBRC, KC_RBRC,
                                         _______, _______,                                _______, _______, _______,
                                         _______, _______,
                                         _______
    )
};

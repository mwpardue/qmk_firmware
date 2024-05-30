#pragma once

#include QMK_KEYBOARD_H
#include "../definitions/keycodes.h"
#include "process_record_result.h"

static const char * const secrets[] = {
  "Ad!ambf",
  "M@tthew6786",
  "L1fe-b4-D3@th!",
  "J0urn3y-b4-D3$tin@ti0n!",
  "Ad!ambf5",
  "Tit1n2sq",
  "Pdntspa12",
  "P@ssw0rd",
  "S1Blabsh",
  "L2C93vTy",
  "StQom2wt",
  "Nv_Str+"
};

#define KC_S1 KC_SECRET_1
#define KC_S2 KC_SECRET_2
#define KC_S4 KC_SECRET_4
#define KC_S5 KC_SECRET_5
#define KC_S6 KC_SECRET_6
#define KC_S12 KC_SECRET_12

process_record_result_t process_secrets(uint16_t keycode, keyrecord_t *record);

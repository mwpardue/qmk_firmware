#pragma once

#include QMK_KEYBOARD_H
#include "../definitions/keycodes.h"
#include "tapdance.h"

//process_record_result_t process_taphold(uint16_t keycode, keyrecord_t *record);
uint16_t get_tapping_term_result(uint16_t keycode);
bool get_hold_on_other_key_press_result(uint16_t keycode);
uint16_t get_quick_tap_term_result(uint16_t keycode);
bool get_permissive_hold_result(uint16_t keycode);
uint8_t rgb_matrix_get_heatmap_spread(void);
uint8_t rgb_matrix_get_area_limit(void);
uint16_t get_achordion_tapping_term(void);
uint16_t get_sft_tapping_term(void);
uint16_t get_modtap_tapping_term(void);
uint16_t get_achordion_tapping_term(void);
uint16_t get_gqt_tapping_term(void);
uint16_t sget_gqt_tapping_term(void);

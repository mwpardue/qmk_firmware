#pragma once

#include QMK_KEYBOARD_H
#include "../definitions/keycodes.h"
#include "process_record_result.h"
#include "quantum.h"


uint8_t rgb_matrix_get_heatmap_spread(void);
uint8_t rgb_matrix_get_area_limit(void);

typedef enum {
    RGBM_FLG,
    RGBM_MOD,
    RGBM_SPD,
    RGBM_HUE,
    RGBM_SAT,
    RGBM_VAL,
    RGBM_MAX
} rgb_menu_selector_t;

extern rgb_menu_selector_t rgb_menu_selector;

process_record_result_t process_rgb_matrix_keys(uint16_t keycode, keyrecord_t *record);

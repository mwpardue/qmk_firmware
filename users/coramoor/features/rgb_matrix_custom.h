#pragma once

#include "quantum.h"


void set_layer_rgb_matrix(uint8_t hue, uint8_t sat, uint8_t val, uint8_t led_min, uint8_t led_max);

bool rgb_matrix_indicators_keymap(void);

bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max);

void rgb_matrix_set_custom_indicators(uint8_t led_min, uint8_t led_max, int led_type, uint8_t hue, uint8_t sat, uint8_t val);

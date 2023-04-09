#pragma once

#include QMK_KEYBOARD_H
#include "../definitions/keycodes.h"
#include "process_record_result.h"
#include "os_toggle.h"
#include "smart_thumb_keys.h"

#ifndef DEFAULT_MOD_ENABLE
        bool should_send_ctrl(bool isWindowsOrLinux, bool isOneShotShift);
#endif

uint16_t get_sft_tapping_term(void);
uint16_t get_modtap_tapping_term(void);
uint16_t get_achordion_tapping_term(void);

process_record_result_t process_custom_shortcuts(uint16_t keycode, keyrecord_t *record);

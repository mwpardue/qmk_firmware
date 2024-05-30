#pragma once

#include QMK_KEYBOARD_H
#include "coramoor.h"
#include "quantum.h"
#include "../definitions/keycodes.h"
#include "process_record_result.h"

typedef enum {
    MENU_MIN,
    MENU_STT,
    MENU_TT,
    MENU_MT,
    MENU_AT,
    MENU_GQT,
    MENU_SGQT,
    MENU_DEFAULTLAYER,
    MENU_OSFLAG,
    MENU_DEBUG,
    MENU_EECLEAR,
    MENU_NKRO,
    MENU_BOOTLOADER,
    MENU_MAX
} oled_menu_selector_t;

extern oled_menu_selector_t oled_menu_selector;

bool check_menu(uint8_t menu_item);

uint8_t viewport_begin(void);

void menu_items(void);

void render_menu_item(const char *label, uint16_t property, uint8_t menu_item);

void render_bool_menu_item(const char *label, bool property, uint8_t menu_item);

process_record_result_t process_oled_menu_keys(uint16_t keycode, keyrecord_t *record);

uint16_t get_achordion_tapping_term(void);
uint16_t get_sft_tapping_term(void);
uint16_t get_modtap_tapping_term(void);
uint16_t get_achordion_tapping_term(void);
uint16_t get_gqt_tapping_term(void);
uint16_t sget_gqt_tapping_term(void);

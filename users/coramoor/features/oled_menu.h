#pragma once

#include QMK_KEYBOARD_H
#include "coramoor.h"
#include "quantum.h"

typedef enum {
    MENU_MIN,
    MENU_FLAGS,
    MENU_SPEED,
    MENU_HUE,
    MENU_SAT,
    MENU_VAL,
    MENU_RGBMODE,
    MENU_HMAREA,
    MENU_HMSPREAD,
    MENU_STT,
    MENU_TT,
    MENU_MT,
    MENU_AT,
    MENU_GQT,
    MENU_SGQT,
    MENU_OSFLAG,
    MENU_DEBUG,
    MENU_EECLEAR,
    MENU_MAX
} rgb_menu_selector_t;

extern rgb_menu_selector_t rgb_menu_selector;

static const char * const rmodes[] = {
    "               ",
    "SOLID",
    "BREATHING",
    "CYC LEFT/RIGHT",
    "CYC OUT/IN",
    "DUAL BEACON",
    "HUE BREATHING",
    "HUE PENDULUM",
    "HUE WAVE",
    "TYPING HEATMAP",
    "REACT SIMPLE",
    "REACTIVE NEXUS",
    "REACT M-NEXUS",
    "SPLASH",
    "MULTISPLASH",
    "SOLID SPLASH",
    "SOLID M-SPLASH"
};

bool check_menu(uint8_t menu_item);

uint8_t viewport_begin(void);

void menu_items(void);

void render_menu_item(const char *label, uint16_t property, uint8_t menu_item);

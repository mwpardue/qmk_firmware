#pragma once

#include QMK_KEYBOARD_H
#include "coramoor.h"
#include "quantum.h"

typedef enum {
    LIGHTING_HEADING,
    MENU_FLAGS,
    MENU_SPEED,
    MENU_HUE,
    MENU_SAT,
    MENU_VAL,
    MENU_RGBMODE,
    LIGHTING_END
} qmenu_lighting_t;

extern qmenu_lighting_t qmenu_lighting;

typedef enum {
    MODTAP_HEADING,
    MENU_STT,
    MENU_TT,
    MENU_MT,
    MENU_AT,
    MENU_GQT,
    MENU_SGQT,
    MODTAP_END
} qmenu_modtap_t;

extern qmenu_modtap_t qmenu_modtap;

typedef enum {
    KB_HEADING,
    MENU_DEFAULTLAYER,
    MENU_OSFLAG,
    MENU_DEBUG,
    MENU_EECLEAR,
    MENU_NKRO,
    MENU_BOOTLOADER,
    KB_END
} qmenu_kb_t;

extern qmenu_kb_t qmenu_kb;

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

typedef enum {
    SUBMENU_OFF,
    SUBMENU_LIGHTING,
    SUBMENU_MODTAP,
    SUBMENU_KB
} qsubmenu_t;

extern qsubmenu_t qsubmenu;

void render_menu(void);

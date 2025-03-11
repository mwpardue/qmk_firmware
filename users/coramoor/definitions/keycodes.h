#pragma once

#include "layers.h"

// Custom keycodes

enum {
    CUSTOM_KEYCODE_START = QK_USER,

#ifdef MACRO_ENABLE
    DDS,
    TIPS,
    FOPEN,
    VIMWQ,
    MVIMQ,
#endif

#ifdef SECRETS_ENABLE
    KC_SECRET_1,
    KC_SECRET_2,
    KC_SECRET_3,
    KC_SECRET_4,
    KC_SECRET_5,
    KC_SECRET_6,
    KC_SECRET_7,
    KC_SECRET_8,
    KC_SECRET_9,
    KC_SECRET_10,
    KC_SECRET_11,
    KC_SECRET_12,
#endif

#ifdef OS_TOGGLE_ENABLE
    TG_MAC, TG_WIN, TG_LIN,
#endif

#ifdef CAPITALIZE_KEY_ENABLE
    SP_CAP, CAP_KEY, SS_CAPS,
#endif

#ifdef DEFAULT_MOD_KEY_ENABLE
    SP_MOD, DEF_MOD,
#endif

#ifdef SMART_THUMB_KEYS_ENABLE
    XCASE, XCTHUM,
#endif

#ifdef SMART_CASE_ENABLE
    MC_CAPS, MC_WORD, MC_CAML, MC_SNAK, MC_KBAB,
#endif

#ifdef TAP_DANCE_ENABLE
    TD_COPY, TD_PAST,
#endif

#ifdef SHORTCUTS_ENABLE
    COLEMAK, QWERTY, DF_LAYR, GUI_ESC, PASSPAL, ADJ_EXT,
    SEL_WRD, SEL_LIN, CAP_MEH, SM_SWIT, TG_OS, ADJ_LYR,
#endif

#ifdef SELECT_WORD_ENABLE
    MC_SELW,
#endif

#ifdef WINDOW_SWAPPER_ENABLE
    MC_SWLE, MC_SWRI, MC_SWAP, MC_MODM, MC_MODP, SF_MODP,
#endif

#ifdef COMBO_ENABLE
    SM_LOGN, SM_ESC, SM_CW, SM_PAR, SM_CUR, SM_BRC, SM_ANG,
#endif

#ifdef LAYER_LOCK_ENABLE
    LLOCK,
#endif

#ifdef CUSTOM_LEADER_ENABLE
  LEADER,
#endif

#ifdef RGB_MATRIX_ENABLE
    RGB_CHG, RGB_MDT, TB_MENU, MENU_AD, MENU_MD, MENU_MU, MENU_AU,
#endif


    CUSTOM_KEYCODE_END
};

// Left thumb keys

    // Upper Left Thumb Keys
    #define UOL_THM KC_F17
    #define UIL_THM HYPR_T(KC_CIRC)

    // Lower Left Thumb Keys
    #define LUTHUM0 MON_L
    #define LUTHUM1 LT(_FUNCTION, KC_UP)
    #define LUTHUM2 LT(_NUMPAD, KC_UNDS)
    #define LIL_THM LT(_NAVIGATION, KC_BSPC)
    #define LOL_THM LSFT_T(KC_ENTER)

    // Alt Base Thumb Keys
    #define CLUTHUM2 LGUI_T(KC_CIRC)
    #define CLIL_THM LT(_NAVIGATION, KC_TAB)
    #define CLOL_THM LCTL_T(KC_ENTER)
    #define CUIL_THM KC_F20
    #define CUOL_THM MON_R

// Right thumb keys

    // Lower Right Thumb Keys
    #define RUTHUM0 TAB_RGT
    #define RUTHUM1 TAB_LFT
    #define RUTHUM2 RGUI_T(KC_PIPE)
    #define LOR_THM RSFT_T(KC_ENTER)
    #define LIR_THM LT(_SYMBOL, KC_SPACE)

    // Upper Right Thumb Keys
    #define UIR_THM HYPR_T(KC_DLR)
    #define UOR_THM KC_F16

    // Alt Base Thumb Keys
    #define CLOR_THM RCTL_T(KC_ENTER)
    #define CLIR_THM LT(_HEX, KC_SPACE)
    #define CUIR_THM OSMHYPR
    #define CUOR_THM OSMMEH
    #define CRUTHUM2 LGUI_T(KC_F21)

// Typing Layer Keys
#define CTL_Z LCTL_T(KC_Z)
#define SFT_Z LSFT_T(KC_Z)
#define CTL_QUE RCTL_T(KC_SLSH)
#define SFT_QUE RSFT_T(KC_SLSH)
#define GUI_C LGUI_T(KC_C)
#define GUI_COM RGUI_T(KC_COMM)
#define ALT_X LALT_T(KC_X)
#define GUI_X LGUI_T(KC_X)
#define ALT_DOT RALT_T(KC_DOT)
#define GUI_DOT RGUI_T(KC_DOT)

// Right thumb keys

// Gaming keys
#define UIG_THM LM(_GAMENUM, MOD_LCTL)
#define LUGTHUM LM(_GAMENUM, MOD_LSFT)
#define LOG_THM LT(_GAMENUM, KC_TAB)
#define LIG_THM LSFT_T(KC_SPACE)

// Mod-taps (QWERTY)

// Left Hand
#define LHM_A LCTL_T(KC_A)
#define LQM_S LALT_T(KC_S)
#define LHM_D LSFT_T(KC_D)
#define LHM_F LGUI_T(KC_F)
#define CTL_TAB LCTL_T(KC_TAB)
#define SFT_TAB LSFT_T(KC_TAB)
#define SFT_QUO RSFT_T(KC_QUOT)
#define CTL_QUO RCTL_T(KC_QUOT)
#define GUI_QUO RGUI_T(KC_QUOT)
#define GUI_TAB LGUI_T(KC_TAB)
#define GUI_ESC LGUI_T(SM_ESC)
#define CTL_MINS LCTL_T(KC_MINS)
#define SFT_DOT LSFT_T(KC_DOT)
#define LHM_Z LCTL_T(KC_Z)
#define LHM_X LALT_T(KC_X)
#define LHM_C LSFT_T(KC_C)
#define LHM_V LGUI_T(KC_V)
#define LSM_A LSFT_T(KC_A)
#define LSM_D LCTL_T(KC_D)

// Right Hand
#define RHM_SCN RCTL_T(KC_SCLN)
#define RHM_L   RALT_T(KC_L)
#define RHM_K   RSFT_T(KC_K)
#define RHM_J   RGUI_T(KC_J)
#define RHM_SLS RCTL_T(KC_SLSH)
#define RHM_DOT RALT_T(KC_DOT)
#define RHM_COM RSFT_T(KC_COMM)
#define RHM_M   RGUI_T(KC_M)
#define RSM_SCN LSFT_T(KC_SCLN)
#define RSM_K LCTL_T(KC_K)

// One-shot mods

#define OSMLSFT OSM(MOD_LSFT)
#define OSMRSFT OSM(MOD_RSFT)
#define OSMLCTL OSM(MOD_LCTL)
#define OSMLALT OSM(MOD_LALT)
#define OSMRALT OSM(MOD_RALT)
#define OSMLGUI OSM(MOD_LGUI)
#define OSMRGUI OSM(MOD_RGUI)
#define OSMRCTL OSM(MOD_RCTL)
#define OSMHYPR OSM(MOD_HYPR)
#define OSMMEH  OSM(MOD_MEH)

// Layer-taps

#define LALT_PP LALT_T(KC_F18)
#define RALT_PP RALT_T(KC_F19)
#define MONUM MO(_NUMPAD)
#define MOVIM MO(_VIM)
#define NUM_Z LT(_NUMPAD, KC_Z)
#define MON_L LALT(KC_H)
#define MON_R LALT(KC_L)
#define MON_U LALT(KC_K)
#define MON_D LALT(KC_J)
#define SPC_L LCTL(LALT(KC_H))
#define SPC_R LCTL(LALT(KC_L))
#define MOV_LFT LCTL(LSFT(KC_TAB))
#define MOV_RGT LCTL(KC_TAB)
#define TAB_LFT LGUI(KC_H)
#define TAB_RGT LGUI(KC_L)
#define TAB_UP LCTL(KC_K)
#define TAB_DWN LCTL(KC_J)
#define TOBAS TO(_BASE)
#define TOHEX TO(_HEX)
#define TOADJ ADJ_LYR

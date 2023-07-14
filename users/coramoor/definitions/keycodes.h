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
    CAP_KEY, SP_CAP, SP_MOD, DEF_MOD, XCASE, TS_CAP, SP_PST,
#endif

#ifdef SMART_CASE_ENABLE
    MC_CAPS, MC_WORD, MC_CAML, MC_SNAK, MC_KBAB,
#endif

#ifdef SHORTCUTS_ENABLE
    SS_MODP, SS_MODM, COLEMAK, QWERTY, TG_KBAB, TG_CAML, TG_SNAK, SM_PARN,
    SFT_TTP, SFT_TTM, BSP_WRD, BSP_LIN, T_CLOSE, SP_RGT, DF_TOGG,
    S_ARRNG, BROWSER_BACK, BROWSER_FORWARD, TAB_BACK, TAB_FORWARD, TMX_LDS,
    PASSPAL, TMX_VIS, NAV_LFT, NAV_RGT, SEL_WRD, SEL_LIN, VIM_TRE, TMX_VSP,
    TMX_HSP, MDT_TTP, MDT_TTM, ACH_TTM, ACH_TTP, SP_AT, CAP_MEH, SM_SWIT,
    TG_OS,
#endif

#ifdef SELECT_WORD_ENABLE
    MC_SELW,
#endif

#ifdef WINDOW_SWAPPER_ENABLE
    MC_SWLE, MC_SWRI, MC_SWAP, MC_MODM, MC_MODP, SF_MODP,
#endif

#ifdef COMBO_ENABLE
    SM_LOGN, SM_CW, SM_PAR, SM_CUR, SM_BRC,
#endif

#ifdef LAYER_LOCK_ENABLE
    LLOCK,
#endif

#ifdef CUSTOM_LEADER_ENABLE
  LEADER,
#endif

#ifdef RGB_MATRIX_ENABLED
    RGB_SPP, RGB_SPM, RGB_ALP, RGB_ALM, RGB_CHG, RGB_MDT,
#endif

    CUSTOM_KEYCODE_END
};

// Left thumb keys

#define LUTHUM1 LGUI_T(KC_ENTER)
#define LUTHUM2 LT(_NUMPAD, KC_MINS)
#define LOL_THM LSFT_T(KC_TAB)
#define LIL_THM LT(_NAVIGATION, KC_BSPC)
#define UIL_THM LGUI_T(SP_CAP)
#define UOL_THM LALT_T(KC_CAPS)

// Right thumb keys

#define RUTHUM1 LGUI_T(KC_TAB)
#define RUTHUM2 LT(_MACROS, KC_UNDS)
#define LIR_THM LCTL_T(KC_SPACE)
#define LOR_THM RSFT_T(KC_ENTER)
#define UIR_THM RALT_T(XCASE)
#define UOR_THM MEH_T(KC_TAB)

// Mod-taps (QWERTY)

// Left Hand
// #define ALT_A LALT_T(KC_A)
// #define CTL_A LCTL_T(KC_A)
// #define CTL_S LCTL_T(KC_S)
// #define ALT_S LALT_T(KC_S)
// #define SFT_D LSFT_T(KC_D)
// #define GUI_F LGUI_T(KC_F)

// #define LHM_A LALT_T(KC_A)
#define LHM_A LCTL_T(KC_A)
// #define LHM_S LCTL_T(KC_S)
#define LHM_S LALT_T(KC_S)
#define LHM_D LSFT_T(KC_D)
#define LHM_F LGUI_T(KC_F)

// Right Hand
// #define ALT_SCN LALT_T(KC_SCLN)
// #define CTL_SCN LCTL_T(KC_SCLN)
// #define CTL_L RCTL_T(KC_L)
// #define ALT_L RALT_T(KC_L)
// #define SFT_K RSFT_T(KC_K)
// #define GUI_J RGUI_T(KC_J)

// #define RHM_SCN LALT_T(KC_SCLN)
#define RHM_SCN LCTL_T(KC_SCLN)
// #define RHM_L RCTL_T(KC_L)
#define RHM_L RALT_T(KC_L)
#define RHM_K RSFT_T(KC_K)
#define RHM_J RGUI_T(KC_J)

//
//
// #define ALT_V LALT_T(KC_V)
// #define ALT_S LALT_T(KC_S)
// #define CTL_D LCTL_T(KC_D)
// #define CTL_QUO RCTL_T(KC_QUOT)
// #define ALT_M RALT_T(KC_M)
// #define ALT_L RALT_T(KC_L)
// #define CTL_K RCTL_T(KC_K)
// #define OPT_PST LALT_T(SP_PST)
// #define ALT_RGT LALT_T(SP_RGT)
// #define CTL_SCN LCTL_T(KC_SCLN)
// #define SFT_SCN LSFT_T(KC_SCLN)

// Mod-taps (COLEMAK-DH)

// Left Hand
#define CLHM_A LCTL_T(KC_A)
#define CLHM_R LALT_T(KC_R)
#define CLHM_S LSFT_T(KC_S)
#define CLHMT LGUI_T(KC_T)

// Right Hand
#define CRHM_O LCTL_T(KC_O)
#define CRHM_I LALT_T(KC_I)
#define CRHM_E LSFT_T(KC_E)
#define CRHM_N LGUI_T(KC_N)

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

#define MOD_KEY LSFT_T(SP_MOD)
#define MOD_SFT LSFT_T(SP_MOD)
#define BSP_SYM LT(_SYMBOL, KC_BSPC)
#define SFT_NUM LT(_NUMPAD, SP_CAP)
#define ENT_NUM LT(_NUMPAD, KC_ENTER)
#define BSP_GUI LGUI_T(KC_BSPC)
#define SFT_BSP LSFT_T(KC_BSPC)
#define MAC_BSP LT(_MACROS, KC_BSPC)
#define SFT_ENT LSFT_T(KC_ENTER)
#define SFT_FUN LT(_FUNCTION, SP_CAP)
#define BSP_NUM LT(_NUMPAD, KC_BSPC)
#define ENT_NAV LT(_NAVIGATION, KC_ENT)
#define TAB_NAV LT(_NAVIGATION, KC_TAB)
#define TAB_SFT LSFT_T(KC_TAB)
#define FUN_XCS LT(_FUNCTION, XCASE)
#define ESC_CTL LCTL_T(KC_ESC)
#define ENT_HYP HYPR_T(KC_ENT)
#define ENT_MEH MEH_T(KC_ENT)
#define CAP_MEH MEH_T(SP_CAP)
#define SPC_MEH MEH_T(KC_SPACE)
// #define TAB_MEH MEH_T(KC_TAB)
#define ENT_SYM LT(_SYMBOL, KC_ENT)
#define SPC_HYP HYPR_T(KC_SPACE)
#define MC_SWAP LGUI(KC_GRV)

// Layer transitions

#define MOFUN MO(_FUNCTION)
#define TOBAS TO(_BASE)
#define TONAV TO(_NAVIGATION)
#define MONAV MO(_NAVIGATION)
#define TOSYM TO(_SYMBOL)
#define TOMAC TO(_MACROS)
#define TOHEX TO(_HEX)
#define TOFUN TO(_FUNCTION)
#define TOADJ TO(_ADJUST)
#define TOCMK TO(_COLEMAK_DH)
#define OSL_MAC OSL(_MACROS)

// Custom Shortcuts

#define SS3 LGUI(LSFT(KC_3))
#define SS4 LGUI(LSFT(KC_4))
#define SELALL LGUI(KC_A)
#define CUT LGUI(KC_X)
#define COPY LGUI(KC_C)
// #define PASTE LGUI(KC_V)
#define SAVE LGUI(KC_S)
#define UNDO LGUI(KC_Z)
#define ESC_MEH MEH_T(KC_ESC)
#define ESC_CTL LCTL_T(KC_ESC)
#define SPC_CTL LCTL_T(KC_SPACE)
#define ENT_MAC LT(_MACROS, KC_ENT)
#define BSP_SYM LT(_SYMBOL, KC_BSPC)
#define DEL_SFT LSFT_T(KC_DEL)
#define DEL_NUM LT(_NUMPAD, KC_DEL)
#define BSP_CTL LCTL_T(KC_BSPC)
#define ESC_NUM LT(_NUMPAD, KC_ESC)
#define ESC_NAV LT(_NAVIGATION, KC_ESC)
// #define SPC_SYM LT(_SYMBOL, KC_SPACE)
#define SPCSFT LSFT_T(KC_SPC)
#define MACSLEP LSFT(LCTL(KC_KB_POWER))
#define MON_L LCTL(LALT(LSFT(KC_4)))
#define MON_M LCTL(LALT(LSFT(KC_5)))
#define MON_R LCTL(LALT(LSFT(KC_6)))
#define MON_BL LCTL(LALT(LSFT(KC_1)))
#define MAX_SCR LGUI(LCTL(LALT(LSFT(KC_M))))
#define MOV_LFT LCTL(KC_H)
#define MOV_RGT LCTL(KC_L)
#define TAB_LFT LCTL(LSFT(KC_TAB))
#define TAB_RGT LCTL(KC_TAB)
#define BRWS_FW LGUI(KC_RBRC)
#define BRWS_BK LGUI(KC_LBRC)
#define KM_HYPC LGUI(LCTL(LALT(LSFT(KC_C))))
#define GUI_KW LGUI(KC_W)
#define GUI_KR LGUI(KC_R)
#define GUI_KT LGUI(KC_T)
#define WD_LEFT LALT(KC_LEFT)
#define WD_RGHT LALT(KC_RIGHT)
#define LN_LEFT LGUI(KC_LEFT)
#define LN_RGHT LGUI(KC_RIGHT)
#define PG_UP LGUI(KC_UP)
#define PG_DOWN LGUI(KC_DOWN)
#define CAD LCTL(LALT(KC_DEL))
#define KIT_RST LGUI(KC_0)
#define LHM_AT LALT_T(SP_AT)
#define LHM_BSL LCTL_T(KC_BSLS)
#define LHM_UND LSFT_T(KC_UNDS)
#define LHM_PIP LGUI_T(KC_PIPE)
#define ALT_BSP LALT(KC_BSPC)
#define CTL_ESC LCTL_T(KC_ESC)

uint16_t extract_base_tapping_keycode(uint16_t keycode);

//#ifdef SMART_CASE_ENABLE
    bool is_key_on_tap(uint16_t keycode);
//#endif

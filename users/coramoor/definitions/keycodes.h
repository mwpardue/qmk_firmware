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
    CAP_KEY, SP_CAP, SP_MOD, DEF_MOD, XCASE, TS_CAP, SP_PST, XCTHUM,
#endif

#ifdef SMART_CASE_ENABLE
    MC_CAPS, MC_WORD, MC_CAML, MC_SNAK, MC_KBAB,
#endif

#ifdef TAP_DANCE_ENABLE
    TD_COPY, TD_PAST, TD_LEAD,
#endif

#ifdef SHORTCUTS_ENABLE
    SS_MODP, SS_MODM, COLEMAK, QWERTY, TG_KBAB, TG_CAML, TG_SNAK, SM_PARN,
    SFT_TTP, SFT_TTM, BSP_WRD, BSP_LIN, T_CLOSE, SP_RGT, DF_TOGG,
    S_ARRNG, BROWSER_BACK, BROWSER_FORWARD, TAB_BACK, TAB_FORWARD, TMX_LDS,
    PASSPAL, TMX_VIS, NAV_LFT, NAV_RGT, SEL_WRD, SEL_LIN, VIM_TRE, TMX_VSP,
    TMX_HSP, SP_AT, CAP_MEH, SM_SWIT, TG_OS, CG_MOD, ADJ_LYR, FUN_BSP, MACSLEP,
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
    RGB_SPP, RGB_SPM, RGB_ALP, RGB_ALM, RGB_CHG, RGB_MDT,
    MENU_AD, MENU_MD, MENU_MU, MENU_AU,
#endif


    CUSTOM_KEYCODE_END
};

// Left thumb keys

#define LUTHUM1 LT(_FUNCTION, KC_B)
#define LUTHUM2 MEH_T(PASSPAL)
#define LIL_THM LT(_NAVIGATION, KC_BSPC)
#define LOL_THM LT(_NUMPAD, KC_TAB)
#define UOL_THM TD_PAST
#define UIL_THM LEADER
#define ASW_Z LT(_APPSWITCH, KC_Z)

// Right thumb keys

#define RUTHUM1 LT(_FUNCTION, KC_T)
#define RUTHUM2 KC_ENT
// #define LOR_THM LT(_SYMBOL, KC_ENTER)
#define LOR_THM RCTL_T(KC_ENTER)
#define LIR_THM LT(_SYMBOL, KC_SPACE)
// #define LIR_THM RCTL_T(KC_SPACE)
#define UIR_THM PASSPAL
#define UOR_THM HYPR_T(KC_2)

#define CLUTHUM2 LT(_NUMPAD, PASSPAL)
#define CLIL_THM LT(_NAVIGATION, KC_TAB)
#define CLOL_THM LSFT_T(KC_TAB)
#define CLOR_THM RSFT_T(KC_ENTER)
// #define CLIR_THM LT(_SYMBOL, KC_SPACE)
#define CLIR_THM LT(_VIM, KC_SPACE)
#define CUIL_THM MON_L
#define CUIR_THM OSMHYPR
#define CUOR_THM OSMMEH
#define CUOL_THM MON_R
#define CRUTHUM2 LT(_NUMPAD, KC_Q)
#define NUM_Z LT(_NUMPAD, KC_Z)
#define GUI_SLS RGUI_T(KC_SLSH)
#define VIM_SLS LT(_VIM, KC_SLSH)
#define VIM_QUO LT(_VIM, KC_QUOTE)

#define SFT_CW LSFT_T(KC_Q)
#define CTL_CW LCTL_T(KC_Q)
#define GUI_CW LGUI_T(KC_Q)

#define RHM_4 RGUI_T(KC_4)
#define RHM_5 RSFT_T(KC_5)
#define RHM_6 RALT_T(KC_6)
#define RHM_CLN RCTL_T(KC_C)


// Right thumb keys

#define SFT_TAB SFT_T(KC_TAB)
#define MEH_QUO MEH_T(KC_QUOT)

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
#define SFT_Z LSFT_T(KC_Z)
#define SFT_QUE RSFT_T(KC_SLSH)
#define CTL_Z LCTL_T(KC_Z)
#define CTL_QUE RCTL_T(KC_SLSH)
#define SFT_DOT LSFT_T(KC_DOT)
#define LHM_Z LCTL_T(KC_Z)
#define LHM_X LALT_T(KC_X)
#define LHM_C LSFT_T(KC_C)
#define LHM_V LGUI_T(KC_V)

#define LHM_R LALT_T(KC_R)
#define LHM_S LSFT_T(KC_S)
#define LHM_T LGUI_T(KC_T)

// Right Hand
#define RHM_SCN RCTL_T(KC_SCLN)
#define RHM_L   RALT_T(KC_L)
#define RHM_K   RSFT_T(KC_K)
#define RHM_J   RGUI_T(KC_J)
#define RHM_SLS RCTL_T(KC_SLSH)
#define RHM_DOT RALT_T(KC_DOT)
#define RHM_COM RSFT_T(KC_COMM)
#define RHM_M   RGUI_T(KC_M)

#define RHM_O RCTL_T(KC_O)
#define RHM_I RALT_T(KC_I)
#define RHM_E RSFT_T(KC_E)
#define RHM_N RGUI_T(KC_N)

// Mod-taps (COLEMAK-DH)

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
// #define BSP_SYM LT(_SYMBOL, KC_BSPC)
#define SFT_NUM LT(_NUMPAD, SP_CAP)
#define ENT_NUM LT(_NUMPAD, KC_ENTER)
#define BSP_GUI LGUI_T(KC_BSPC)
#define SFT_BSP LSFT_T(KC_BSPC)
#define VIM_BSP LT(_VIM, KC_BSPC)
#define SFT_FUN LT(_FUNCTION, SP_CAP)
#define BSP_NUM LT(_NUMPAD, KC_BSPC)
#define ENT_NAV LT(_NAVIGATION, KC_ENT)
#define TAB_NAV LT(_NAVIGATION, KC_TAB)
// #define TAB_SFT LSFT_T(KC_TAB)
// #define ENT_HYP HYPR_T(KC_ENT)
#define CAP_MEH MEH_T(SP_CAP)
#define SPC_MEH MEH_T(KC_SPACE)
#define ENT_SYM LT(_SYMBOL, KC_ENT)
#define SPC_HYP HYPR_T(KC_SPACE)
#define MC_SWAP LGUI(KC_GRV)

// Layer transitions

#define MOFUN MO(_FUNCTION)
#define MONUM MO(_NUMPAD)
#define MOVIM MO(_VIM)
#define MOGAMN MO(_GAMENUM)
#define TOBAS TO(_BASE)
#define TONAV TO(_NAVIGATION)
#define MONAV MO(_NAVIGATION)
#define TOSYM TO(_SYMBOL)
#define TOVIM TO(_VIM)
#define TOHEX TO(_HEX)
#define TOFUN TO(_FUNCTION)
// #define TOADJ TO(_ADJUST)
#define TOADJ ADJ_LYR
#define TOCMK TO(_COLEMAK_DH)
#define TOGAM TO(_GAMING)
#define OSL_VIM OSL(_VIM)
#define OSL_FUN OSL(_FUNCTION)

// Custom Shortcuts

#define SS3 LGUI(LSFT(KC_3))
#define SS4 LGUI(LSFT(KC_4))
#define SELALL LGUI(KC_A)
#define CUT LGUI(KC_X)
#define COPY LGUI(KC_C)
#define SAVE LGUI(KC_S)
#define UNDO LGUI(KC_Z)
// #define ESC_MEH MEH_T(KC_ESC)
#define SPC_CTL LCTL_T(KC_SPACE)
#define ENT_VIM LT(_VIM, KC_ENT)
// #define BSP_SYM LT(_SYMBOL, KC_BSPC)
#define DEL_SFT LSFT_T(KC_DEL)
#define DEL_NUM LT(_NUMPAD, KC_DEL)
#define BSP_CTL LCTL_T(KC_BSPC)
#define ESC_NUM LT(_NUMPAD, KC_ESC)
#define ESC_NAV LT(_NAVIGATION, KC_ESC)
#define SPCSFT LSFT_T(KC_SPC)
// #define MACSLEP LSFT(LCTL(KC_KB_POWER))
// #define MACSLEP LGUI(LALT(KC_KB_POWER))
#define MON_L LALT(KC_H)
#define MON_R LALT(KC_L)
#define MON_U LALT(KC_K)
#define MON_D LALT(KC_J)
#define SPC_L LALT(LCTL((KC_H)))
#define SPC_R LALT(LCTL((KC_L)))
#define SPC_U LALT(LCTL((KC_K)))
#define SPC_D LALT(LCTL((KC_J)))
#define APP_L LCTL(LALT((KC_H)))
#define APP_R LCTL(LALT((KC_L)))
#define APP_U LCTL(LALT((KC_K)))
#define APP_D LCTL(LALT((KC_J)))
#define SCRN_L LCTL(LALT(LSFT(KC_H)))
#define SCRN_R LCTL(LALT(LSFT(KC_L)))
#define MAX_SCR LGUI(LCTL(LALT(LSFT(KC_M))))
#define MOV_LFT LCTL(LSFT(KC_TAB))
#define MOV_RGT LCTL(KC_TAB)
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
// #define LHM_AT LCTL_T(SP_AT)
// #define LHM_BSL LALT_T(KC_BSLS)
// #define LHM_UND LSFT_T(KC_U)
// #define LHM_PIP LGUI_T(KC_PIPE)
#define LHM_AT LCTL_T(SP_AT)
#define LHM_BSL LALT_T(KC_BSLS)
#define LHM_UND LSFT_T(KC_U)
#define LHM_PIP LGUI_T(KC_PIPE)
#define LHM_MNL LALT_T(KC_W)
#define LHM_MNR LGUI_T(KC_R)
#define ALT_BSP LALT(KC_BSPC)
#define ALT_MIN LALT_T(KC_MINS)
#define SFT_BSP LSFT_T(KC_BSPC)
#define CTL_BSP LCTL_T(KC_TAB)
#define GUI_BSP LGUI_T(KC_BSPC)
#define ALT_MIN LALT_T(KC_MINS)
#define SFT_MIN LSFT_T(KC_MINS)
#define GUI_MIN LGUI_T(KC_MINS)
#define ALT_ENT RALT_T(KC_ENT)
#define SFT_QUO RSFT_T(KC_QUOT)
#define CTL_QUO RCTL_T(KC_QUOT)
#define GUI_QUO RGUI_T(KC_QUOT)
#define HYP_TAB HYPR_T(KC_TAB)
#define RMT_PLY LGUI(LCTL(LALT(LSFT(KC_GRAVE))))
#define APP_SWI MEH(KC_W)
// #define SFT_ENT LSFT_T(KC_ENT)

// uint16_t extract_base_tapping_keycode(uint16_t keycode);
//
// //#ifdef SMART_CASE_ENABLE
//     bool is_key_on_tap(uint16_t keycode);
// //#endif

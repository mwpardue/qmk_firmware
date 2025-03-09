#pragma once

typedef union {
    uint32_t raw;
    struct {
    #ifdef CASEMODE_ENABLE
        uint8_t xcase_state :8;
        uint16_t llocked :8;
    #ifdef CUSTOM_LEADER_ENABLE
        uint8_t menu :8;
    #endif
        bool debug_enabled :1;
        bool caps_word_on :1;
    #endif
    } kb;
} user_runtime_state_t;

extern user_runtime_state_t user_runtime_state;

typedef union {
    uint8_t raw[64];
    struct {
        uint8_t menu_selector :8;
        uint8_t submenu_selector :8;
        uint8_t os :8;
    } menu;
} user_config_t;

extern user_config_t user_config;

typedef enum {
    OTHER,
    MACOS,
    WINDOWS,
    LINUX
} os_t;

extern os_t os;

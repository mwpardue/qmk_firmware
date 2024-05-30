#pragma once

// #include "coramoor.h"

typedef union {
    uint32_t raw;
    struct {
        uint8_t oled_menu_selector :8;
        uint8_t os :8;
    };
} user_runtime_config_t;

user_runtime_config_t user_state;

typedef union {
    uint32_t raw;
    struct {
    // #ifdef SMART_CASE_ENABLE
    //     uint8_t type :8;
    // #endif
    #ifdef CASEMODE_ENABLE
        uint8_t xcase_state :8;
        uint16_t llocked :8;
        bool caps_word_on :1;
        bool debug_enabled :1;
        bool is_dynamic_recording :1;
    #endif
        // uint8_t smart_case_types :8;
    };
} __attribute__((packed)) kb_state_t;

extern kb_state_t kb_state;

// typedef enum {
//     OTHER,
//     MACOS,
//     WINDOWS,
//     LINUX
// } os_t;

// extern os_t os;

typedef union {
    uint32_t raw;

    struct {
        uint8_t oled_menu_selector :8;
        uint8_t os :8;
    };


} __attribute__((packed)) user_config_t;

extern user_config_t user_config;

void keyboard_post_init_transport_sync(void);
void housekeeping_task_transport_sync(void);

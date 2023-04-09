#pragma once

// #include "caracarn.h"
#include "features/rgb_matrix_keys.h"
#include "features/rgb_matrix_ledmaps.h"

typedef union {
    uint32_t raw;
    struct {
        bool    rgb_matrix_ledmap_active  :1;
        bool    rgb_matrix_toggle :1;
        uint8_t rgb_matrix_heatmap_area :8;
        uint8_t rgb_matrix_heatmap_spread :8;
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
        bool caps_word_on :1;
    #endif
        // uint8_t smart_case_types :8;
    };
} kb_state_t;

extern kb_state_t kb_state;

typedef union {
    uint32_t raw;
    struct {
        bool    rgb_matrix_ledmap_active  :1;
        bool    rgb_matrix_toggle :1;
        uint8_t rgb_matrix_heatmap_area :8;
        uint8_t rgb_matrix_heatmap_spread :8;
    };
} user_config_t;

extern user_config_t user_config;

void keyboard_post_init_transport_sync(void);
void housekeeping_task_transport_sync(void);

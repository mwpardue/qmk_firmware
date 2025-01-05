#include "coramoor.h"
#include "features/transport_sync.h"
#include "transactions.h"
#include "features/rgb_matrix_keys.h"
#ifdef SMART_CASE_ENABLE
    #include "features/smart_case.h"
#endif
#ifdef CASEMODE_ENABLE
    #include "features/casemodes.h"
#endif
#ifdef OS_TOGGLE_ENABLE
    #include "features/os_toggle.h"
#endif

#ifdef CUSTOM_LEADER_ENABLE
    #include "features/leader.h"
#endif

#include <string.h>

uint32_t transport_user_state = 0;
uint32_t transport_kb_state = 0;

extern layer_state_t locked_layers;

user_runtime_config_t user_state;

kb_state_t kb_state;

user_config_t user_config;

#ifdef SMART_CASE_ENABLE
extern smart_case_t smart_case;
#endif

#ifdef CASEMODE_ENABLE
    extern enum xcase_state xcase_state;
    extern bool caps_word_on;
#endif

#ifdef DYNAMIC_MACRO_ENABLE
    extern bool is_dynamic_recording;
#endif

#ifdef CUSTOM_LEADER_ENABLE
    // extern bool leading;
    menu_t menu;
#endif

    // extern os_t os;

void user_state_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(transport_user_state)) {
        memcpy(&transport_user_state, initiator2target_buffer, initiator2target_buffer_size);
    }
}

void kb_state_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(transport_kb_state)) {
        memcpy(&transport_kb_state, initiator2target_buffer, initiator2target_buffer_size);
    }
}

void keyboard_post_init_transport_sync(void) {
    // Register keyboard state sync split transaction
    transaction_register_rpc(RPC_ID_USER_STATE_SYNC, user_state_sync);
    transaction_register_rpc(RPC_ID_KB_STATE_SYNC, kb_state_sync);
}

void user_transport_update(void) {
    if (is_keyboard_master()) {
        // user_state.rgb_matrix_hue = user_config.rgb_matrix_hue;
        // user_state.rgb_matrix_sat = user_config.rgb_matrix_sat;
        user_state.rgb_menu_selector = user_config.rgb_menu_selector;
        user_state.rgb_matrix_heatmap_area = user_config.rgb_matrix_heatmap_area;
        user_state.rgb_matrix_heatmap_spread = user_config.rgb_matrix_heatmap_spread;
        user_state.os = user_config.os;
        transport_user_state = user_state.raw;
    // #ifdef SMART_CASE_ENABLE
    //     kb_state.type = smart_case.type;
    // #endif
        kb_state.xcase_state = xcase_state;
        kb_state.llocked = locked_layers;
        kb_state.caps_word_on = caps_word_on;
        kb_state.debug_enabled = debug_enable;
        kb_state.is_dynamic_recording = is_dynamic_recording;
        // kb_state.leading = leading;
        kb_state.menu = menu.state;
        // kb_state.smart_case_types = smart_case_types;
        transport_kb_state = kb_state.raw;
    } else {
        user_state.raw       = transport_user_state;
        // user_config.rgb_matrix_hue = user_state.rgb_matrix_hue;
        // user_config.rgb_matrix_sat = user_state.rgb_matrix_sat;
        user_config.rgb_menu_selector = user_state.rgb_menu_selector;
        user_config.rgb_matrix_heatmap_area = user_state.rgb_matrix_heatmap_area;
        user_config.rgb_matrix_heatmap_spread = user_state.rgb_matrix_heatmap_spread;
        user_config.os = user_state.os;
        kb_state.raw = transport_kb_state;
    // #ifdef SMART_CASE_ENABLE
    //     smart_case.type = kb_state.type;
    // #endif
        xcase_state = kb_state.xcase_state;
        locked_layers = kb_state.llocked;
        caps_word_on = kb_state.caps_word_on;
        debug_enable = kb_state.debug_enabled;
        is_dynamic_recording = kb_state.is_dynamic_recording;
        // leading = kb_state.leading;
        menu.state = kb_state.menu;
        // smart_case_types = kb_state.smart_case_types;

    }
}

void user_transport_sync(void) {
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave
        // static uint32_t last_sync = 0;
        static uint32_t last_kb_state = 0, last_sync[2], last_user_state = 0;
        bool            needs_sync = false;

        // Check if the state values are different
        if (memcmp(&transport_user_state, &last_user_state, sizeof(transport_user_state))) {
            needs_sync = true;
            memcpy(&last_user_state, &transport_user_state, sizeof(transport_user_state));
        }
        // Send to slave every 500ms regardless of state change
        if (timer_elapsed32(last_sync[0]) > 250) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_USER_STATE_SYNC, sizeof(user_state), &user_state)) {
                last_sync[0] = timer_read32();
            }
            needs_sync = false;
        }

        // KB State Sync
        // Check if the state values are different
        if (memcmp(&transport_kb_state, &last_kb_state, sizeof(transport_kb_state))) {
            needs_sync = true;
            memcpy(&last_kb_state, &transport_kb_state, sizeof(transport_kb_state));
        }
        // Send to slave every 500ms regardless of state change
        if (timer_elapsed32(last_sync[1]) > 250) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_KB_STATE_SYNC, sizeof(kb_state), &kb_state)) {
                last_sync[1] = timer_read32();
            }
            needs_sync = false;
        }
    }
}

void housekeeping_task_transport_sync(void) {
    // Update kb_state so we can send to slave
    user_transport_update();

    // Data sync from master to slave
    user_transport_sync();
}

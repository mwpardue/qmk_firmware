#include QMK_KEYBOARD_H

#include <ctype.h>
#include "coramoor.h"
#include "features/qpainter.h"

extern uint16_t sft_tapping_term;

extern uint16_t modtap_tapping_term;

extern uint16_t achordion_tapping_term;

extern uint16_t gqt_tapping_term;

extern uint16_t sgqt_tapping_term;

__attribute__((unused)) int            start_index = 0;

__attribute__((unused)) uint32_t scroll_time = 1000;
//----------------------------------------------------------
// RGB Matrix naming
#include <rgb_matrix.h>

#if defined(RGB_MATRIX_EFFECT)
#    undef RGB_MATRIX_EFFECT
#endif // defined(RGB_MATRIX_EFFECT)

#define RGB_MATRIX_EFFECT(x) RGB_MATRIX_EFFECT_##x,
enum {
    RGB_MATRIX_EFFECT_NONE,
#include "rgb_matrix_effects.inc"
#undef RGB_MATRIX_EFFECT
#ifdef RGB_MATRIX_CUSTOM_KB
#    include "rgb_matrix_kb.inc"
#endif
#ifdef RGB_MATRIX_CUSTOM_USER
#    include "rgb_matrix_user.inc"
#endif
};

#define RGB_MATRIX_EFFECT(x)    \
    case RGB_MATRIX_EFFECT_##x: \
        return #x;
const char* rgb_matrix_name(uint8_t effect) {
    switch (effect) {
        case RGB_MATRIX_EFFECT_NONE:
            return "NONE";
#include "rgb_matrix_effects.inc"
#undef RGB_MATRIX_EFFECT
#ifdef RGB_MATRIX_CUSTOM_KB
#    include "rgb_matrix_kb.inc"
#endif
#ifdef RGB_MATRIX_CUSTOM_USER
#    include "rgb_matrix_user.inc"
#endif
        default:
            return "UNKNOWN";
    }
}

// GENERAL MENU FUNCTIONS

bool check_menu(uint8_t menu_item) {
    if (user_config.menu_selector == menu_item) {
        return true;
    } else {
        return false;
    }
}

#define MAX_LABEL_SIZE 16
#define MAX_PROP_SIZE 16

static char label[MAX_LABEL_SIZE];  // Static array to hold the string
static char prop[MAX_PROP_SIZE];  // Static array to hold the string

void set_prop(const char *new_value) {
    // Ensure the buffer is clean before copying new content
    memset(prop, 0, MAX_PROP_SIZE);

    // Safely copy the new string into the buffer
    strncpy(prop, new_value, MAX_PROP_SIZE - 1);

    // Explicitly set the last character to '\0' to ensure null termination
    prop[MAX_PROP_SIZE - 1] = '\0';
}

void set_label(const char *new_value) {
    // Ensure the buffer is clean before copying new content
    memset(label, 0, MAX_LABEL_SIZE);

    // Safely copy the new string into the buffer
    strncpy(label, new_value, MAX_LABEL_SIZE - 1);

    // Explicitly set the last character to '\0' to ensure null termination
    prop[MAX_LABEL_SIZE - 1] = '\0';
}

void render_menu_item(const char *label, uint16_t property, uint8_t menu_item) {

    char property_str[20];
    snprintf(property_str, sizeof(property_str), "%d", property);
    int16_t property_width = qp_textwidth(mononoki, property_str);

    if (check_menu(menu_item)) {
        qp_drawtext_recolor(lcd_surface, 0, (menu_item*(mononoki->line_height)+2), mononoki, label, HSV_WHITE, HSV_BLACK);
    } else {
        qp_drawtext_recolor(lcd_surface, 0, (menu_item*(mononoki->line_height)+2), mononoki, label, HSV_CYAN, HSV_BLACK);
    }
    qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - property_width), (menu_item*(mononoki->line_height)+2), mononoki, property_str, HSV_CYAN, HSV_BLACK);
}

void render_rgb_mode(const char *label, uint8_t menu_item) {
    __attribute__((unused)) static uint8_t mode;
    static char                            buf[41]     = {0};
    size_t                                 PROPERTY_LENGTH = 15;

    if (mode != rgb_matrix_get_mode()) {
        mode        = rgb_matrix_get_mode();
        start_index = 0;
        snprintf(buf, sizeof(buf), "%*s", PROPERTY_LENGTH, rgb_matrix_name(rgb_matrix_get_mode()));
        for (uint8_t i = 1; i < sizeof(buf); ++i) {
            if (buf[i] == 0)
                break;
            else if (buf[i] == '_')
                buf[i] = ' ';
        }
    }
    if (check_menu(menu_item)) {
        qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, buf))/2), (menu_item*(mononoki->line_height)+2), mononoki, buf, HSV_WHITE, HSV_BLACK);
    } else {
        qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, buf))/2), (menu_item*(mononoki->line_height)+2), mononoki, buf, HSV_CYAN, HSV_BLACK);
    }
}

void render_menu_line(const char *heading) {
    uint16_t left = ((LCD_WIDTH-qp_textwidth(bbt, heading))/2) - 2;
    uint16_t right = ((LCD_WIDTH-qp_textwidth(bbt, heading))/2)+(qp_textwidth(bbt, heading) + 2);
    uint16_t top = bbt->line_height + 1;
    uint16_t bottom = bbt->line_height + 2;

    qp_rect(lcd_surface, left, top, right, bottom, HSV_WHITE, true);
}

void render_menu_rgb(const char *heading, uint8_t sm_start, uint8_t sm_end) {
    render_menu_line(heading);
    for (uint8_t i = (sm_start); i < sm_end; i++) {
        switch(i) {
            case LIGHTING_HEADING:
                if (check_menu(LIGHTING_HEADING)) {
                    qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(bbt, heading))/2), 0, bbt, heading, HSV_WHITE, HSV_BLACK);
                } else {
                    qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(bbt, heading))/2), 0, bbt, heading, HSV_YELLOW, HSV_BLACK);
                }
                break;
            case MENU_FLAGS:
                set_label("FLAGS:");
                if (check_menu(MENU_FLAGS)) {
                    qp_drawtext_recolor(lcd_surface, 0, (i*(mononoki->line_height)+2), mononoki, label, HSV_WHITE, HSV_BLACK);
                } else {
                    qp_drawtext_recolor(lcd_surface, 0, (i*(mononoki->line_height)+2), mononoki, label, HSV_CYAN, HSV_BLACK);
                }
                    switch (rgb_matrix_get_flags()) {
                        case LED_FLAG_ALL: {
                            set_prop(" ALL");
                            qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - qp_textwidth(mononoki, prop)), (i*(mononoki->line_height)+2), mononoki, prop, HSV_CYAN, HSV_BLACK);
                        }
                        break;
                        case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                            set_prop(" KMI");
                            qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - qp_textwidth(mononoki, prop)), (i*(mononoki->line_height)+2), mononoki, prop, HSV_CYAN, HSV_BLACK);
                        }
                        break;
                        case LED_FLAG_UNDERGLOW: {
                            set_prop("  UG");
                            qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - qp_textwidth(mononoki, prop)), (i*(mononoki->line_height)+2), mononoki, prop, HSV_CYAN, HSV_BLACK);
                        }
                        break;
                        default: {
                            set_prop("NONE");
                            qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - qp_textwidth(mononoki, prop)), (i*(mononoki->line_height)+2), mononoki, prop, HSV_CYAN, HSV_BLACK);
                        }
                        break;
                    }
                    break;
            case MENU_SPEED:
                render_menu_item("SPEED:", rgb_matrix_get_speed(), i);
                break;
            case MENU_HUE:
                render_menu_item("HUE:", rgb_matrix_get_hue(), i);
                break;
            case MENU_SAT:
                render_menu_item("SAT:", rgb_matrix_get_sat(), i);
                break;
            case MENU_VAL:
                render_menu_item("VAL:", rgb_matrix_get_val(), i);
                break;
            case MENU_RGBMODE:
                render_rgb_mode("MODE: ", i);
                break;
         }
    }
}

void render_menu_modtap(const char *heading, uint8_t sm_start, uint8_t sm_end) {
    render_menu_line(heading);
    for (uint8_t i = (sm_start); i < sm_end; i++) {
        switch(i) {
            case MODTAP_HEADING:
                if (check_menu(MODTAP_HEADING)) {
                    qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(bbt, heading))/2), 0, bbt, heading, HSV_WHITE, HSV_BLACK);
                } else {
                    qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(bbt, heading))/2), 0, bbt, heading, HSV_YELLOW, HSV_BLACK);
                }
                break;
            case MENU_STT:
                render_menu_item("SHIFT:    ", sft_tapping_term, i);
                break;
            case MENU_TT:
                render_menu_item("DEFAULT:  ", g_tapping_term, i);
                break;
            case MENU_MT:
                render_menu_item("MOD TAP:  ", modtap_tapping_term, i);
                break;
            case MENU_AT:
                render_menu_item("ACHORDION:", achordion_tapping_term, i);
                break;
            case MENU_GQT:
                render_menu_item("GQT:      ", gqt_tapping_term, i);
                break;
            case MENU_SGQT:
                render_menu_item("SGQT:     ", sgqt_tapping_term, i);
                break;
         }
    }
}

void render_menu_kb(const char *heading, uint8_t sm_start, uint8_t sm_end) {
    render_menu_line(heading);
    for (uint8_t i = (sm_start); i < sm_end; i++) {
        switch(i) {
            case KB_HEADING:
                if (check_menu(KB_HEADING)) {
                    qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(bbt, heading))/2), 0, bbt, heading, HSV_WHITE, HSV_BLACK);
                } else {
                    qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(bbt, heading))/2), 0, bbt, heading, HSV_YELLOW, HSV_BLACK);
                }
                break;
            case MENU_DEFAULTLAYER:
                set_label("LAYER:");
                if (check_menu(MENU_DEFAULTLAYER)) {
                    qp_drawtext_recolor(lcd_surface, 0, (i*(mononoki->line_height)+2), mononoki, label, HSV_WHITE, HSV_BLACK);
                } else {
                    qp_drawtext_recolor(lcd_surface, 0, (i*(mononoki->line_height)+2), mononoki, label, HSV_CYAN, HSV_BLACK);
                }
                switch (get_highest_layer(default_layer_state)) {
                    case _BASE:
                        set_prop("   BASE");
                        qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - qp_textwidth(mononoki, prop)), (i*(mononoki->line_height)+2), mononoki, prop, HSV_CYAN, HSV_BLACK);
                        break;
                    case _COLEMAK_DH:
                        set_prop("    ALT");
                        qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - qp_textwidth(mononoki, prop)), (i*(mononoki->line_height)+2), mononoki, prop, HSV_CYAN, HSV_BLACK);
                        break;
                    case _GAMING:
                        set_prop(" GAMING");
                        qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - qp_textwidth(mononoki, prop)), (i*(mononoki->line_height)+2), mononoki, prop, HSV_CYAN, HSV_BLACK);
                        break;
                    default:
                        set_prop("  OTHER");
                        qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - qp_textwidth(mononoki, prop)), (i*(mononoki->line_height)+2), mononoki, prop, HSV_CYAN, HSV_BLACK);
                        break;
                }
                break;
            case MENU_OSFLAG:
                set_label("OS:");
                if (check_menu(MENU_OSFLAG)) {
                    qp_drawtext_recolor(lcd_surface, 0, (i*(mononoki->line_height)+2), mononoki, label, HSV_WHITE, HSV_BLACK);
                } else {
                    qp_drawtext_recolor(lcd_surface, 0, (i*(mononoki->line_height)+2), mononoki, label, HSV_CYAN, HSV_BLACK);
                }
                switch (user_config.os) {
                    case WINDOWS:
                        set_prop("WINDOWS");
                        qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - qp_textwidth(mononoki, prop)), (i*(mononoki->line_height)+2), mononoki, prop, HSV_CYAN, HSV_BLACK);
                        break;
                    case LINUX:
                        set_prop("  LINUX");
                        qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - qp_textwidth(mononoki, prop)), (i*(mononoki->line_height)+2), mononoki, prop, HSV_CYAN, HSV_BLACK);
                        break;
                    default:
                        set_prop("    MAC");
                        qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - qp_textwidth(mononoki, prop)), (i*(mononoki->line_height)+2), mononoki, prop, HSV_CYAN, HSV_BLACK);
                        break;
                }
                break;
            case MENU_DEBUG:
                set_label("DEBUG:");
                if (check_menu(MENU_DEBUG)) {
                    qp_drawtext_recolor(lcd_surface, 0, (i*(mononoki->line_height)+2), mononoki, label, HSV_WHITE, HSV_BLACK);
                } else {
                    qp_drawtext_recolor(lcd_surface, 0, (i*(mononoki->line_height)+2), mononoki, label, HSV_CYAN, HSV_BLACK);
                }
                if (kb_state.debug_enabled) {
                    set_prop(" ON");
                    qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - qp_textwidth(mononoki, prop)), (i*(mononoki->line_height)+2), mononoki, prop, HSV_CYAN, HSV_BLACK);
                } else {
                    set_prop("OFF");
                    qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - qp_textwidth(mononoki, prop)), (i*(mononoki->line_height)+2), mononoki, prop, HSV_CYAN, HSV_BLACK);
                }
                break;
            case MENU_EECLEAR:
                set_label("CLEAR EEPROM");
                if (check_menu(MENU_EECLEAR)) {
                    qp_drawtext_recolor(lcd_surface, 0, (i*(mononoki->line_height)+2), mononoki, label, HSV_WHITE, HSV_BLACK);
                } else {
                    qp_drawtext_recolor(lcd_surface, 0, (i*(mononoki->line_height)+2), mononoki, label, HSV_CYAN, HSV_BLACK);
                }
                break;
            case MENU_NKRO:
                set_label("NKRO:");
                if (check_menu(MENU_NKRO)) {
                    qp_drawtext_recolor(lcd_surface, 0, (i*(mononoki->line_height)+2), mononoki, label, HSV_WHITE, HSV_BLACK);
                } else {
                    qp_drawtext_recolor(lcd_surface, 0, (i*(mononoki->line_height)+2), mononoki, label, HSV_CYAN, HSV_BLACK);
                }
                if (keymap_config.nkro) {
                    set_prop(" ON");
                    qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - qp_textwidth(mononoki, prop)), (i*(mononoki->line_height)+2), mononoki, prop, HSV_CYAN, HSV_BLACK);
                } else {
                    set_prop("OFF");
                    qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - qp_textwidth(mononoki, prop)), (i*(mononoki->line_height)+2), mononoki, prop, HSV_CYAN, HSV_BLACK);
                }
                break;
            case MENU_BOOTLOADER:
                set_label("FLASH FIRMWARE");
                if (check_menu(MENU_BOOTLOADER)) {
                    qp_drawtext_recolor(lcd_surface, 0, (i*(mononoki->line_height)+2), mononoki, label, HSV_WHITE, HSV_BLACK);
                } else {
                    qp_drawtext_recolor(lcd_surface, 0, (i*(mononoki->line_height)+2), mononoki, label, HSV_CYAN, HSV_BLACK);
                }
                break;
            default:
            break;
        }
    }
}

void render_menu(void) {
    if (lcd_dirty) {
        switch (user_config.submenu_selector) {
            case SUBMENU_LIGHTING:
                render_menu_rgb("RGB CONFIG", LIGHTING_HEADING, LIGHTING_END);
                break;
            case SUBMENU_MODTAP:
                render_menu_modtap("MODTAP CONFIG", MODTAP_HEADING, MODTAP_END);
                break;
            case SUBMENU_KB:
                render_menu_kb("KB CONFIG", KB_HEADING, KB_END);
                break;
        }
    }
}

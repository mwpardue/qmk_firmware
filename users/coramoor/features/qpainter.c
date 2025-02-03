#include "halcyon_modules/hlc_tft_display/hlc_tft_display.h"
#include "qp_surface.h"
#include "features/mononoki.qff.h"
#include "features/kyria_logo-mono.qgf.h"
#include "../fonts/bigbluetermmono.qff.h"
#include "../images/glyphs.qgf.h"
#include "features/casemodes.h"
#include "features/leader.h"
#include "definitions/layers.h"
#include "features/qmenu.h"

extern bool caps_word_on;
extern enum xcase_state xcase_state;
bool lcd_dirty = false;

painter_font_handle_t mononoki, bbt;

painter_device_t lcd;
painter_device_t lcd_surface;
painter_image_handle_t  os_glyph,
                        command_glyph, ctrl_glyph, option_glyph, shift_glyph,
                        capslock_glyph, capsword_glyph, xcase_glyph, layer_border;

#define LCD_LINE_ONE LCD_HEIGHT - 14*(mononoki->line_height)
#define LCD_LINE_TWO LCD_HEIGHT - 13*(mononoki->line_height)
#define LCD_LINE_THREE LCD_HEIGHT - 12*(mononoki->line_height)
#define LCD_LINE_FOUR LCD_HEIGHT - 11*(mononoki->line_height)
#define LCD_LINE_FIVE LCD_HEIGHT - 10*(mononoki->line_height)
#define LCD_LINE_SIX LCD_HEIGHT - 9*(mononoki->line_height)
#define LCD_LINE_SEVEN LCD_HEIGHT - 8*(mononoki->line_height)
#define LCD_LINE_EIGHT LCD_HEIGHT - 7*(mononoki->line_height)
#define LCD_LINE_NINE LCD_HEIGHT - 6*(mononoki->line_height)
#define LCD_LINE_TEN LCD_HEIGHT - 5*(mononoki->line_height)
#define LCD_LINE_ELEVEN LCD_HEIGHT - 4*(mononoki->line_height)
#define LCD_LINE_TWELVE LCD_HEIGHT - 3*(mononoki->line_height)
#define LCD_LINE_THIRTEEN LCD_HEIGHT - 2*(mononoki->line_height)
#define LCD_LINE_FOURTEEN LCD_HEIGHT - 1*(mononoki->line_height)
#define LCD_LINE_FIFTEEN LCD_HEIGHT - mononoki->line_height

#define LCD_LAYER_LINE LCD_HEIGHT - 5*(mononoki->line_height)
#define LCD_MOD_LINE LCD_HEIGHT - (command_glyph->height+20)
#define LCD_STATUS_LINE os_glyph->height+40

#define HSV_INACTIVE 0, 0, 128
#define HSV_ACTIVE 0, 0, 255

void draw_layer(void) {
    if (lcd_dirty) {
        qp_drawimage_recolor(lcd_surface, ((LCD_WIDTH - (layer_border->width))/2), LCD_LAYER_LINE - 5, layer_border, HSV_WHITE, HSV_BLACK);
        dprintln("Drawing border");
        switch (get_highest_layer(layer_state|default_layer_state)) {
            case _BASE:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "BASE"))/2), LCD_LAYER_LINE, mononoki, "BASE", HSV_CYAN, HSV_BLACK);
                break;
            case _COLEMAK_DH:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "TYPING"))/2), LCD_LAYER_LINE, mononoki, "TYPING", HSV_CYAN, HSV_BLACK);
                break;
            case _GAMING:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "GAMING"))/2), LCD_LAYER_LINE, mononoki, "GAMING", HSV_CYAN, HSV_BLACK);
                break;
            case _GAMENUM:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "GAMENUM"))/2), LCD_LAYER_LINE, mononoki, "GAMENUM", HSV_CYAN, HSV_BLACK);
                break;
            case _HEX:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "HEX"))/2), LCD_LAYER_LINE, mononoki, "HEX", HSV_CYAN, HSV_BLACK);
                break;
            case _NAVIGATION:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "NAVIGATION"))/2), LCD_LAYER_LINE, mononoki, "NAVIGATION", HSV_CYAN, HSV_BLACK);
                break;
            case _NUMPAD:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "NUMPAD"))/2), LCD_LAYER_LINE, mononoki, "NUMPAD", HSV_CYAN, HSV_BLACK);
                break;
            case _SYMBOL:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "SYMBOL"))/2), LCD_LAYER_LINE, mononoki, "SYMBOL", HSV_CYAN, HSV_BLACK);
                break;
            case _VIM:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "VIM"))/2), LCD_LAYER_LINE, mononoki, "VIM", HSV_CYAN, HSV_BLACK);
                break;
            case _FUNCTION:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "FUNCTION"))/2), LCD_LAYER_LINE, mononoki, "FUNCTION", HSV_CYAN, HSV_BLACK);
                break;
            case _APPSWITCH:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "APPSWITCH"))/2), LCD_LAYER_LINE, mononoki, "APPSWITCH", HSV_CYAN, HSV_BLACK);
                break;
            case _ADJUST:
                qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, "ADJUST"))/2), LCD_LAYER_LINE, mononoki, "ADJUST", HSV_CYAN, HSV_BLACK);
                break;
        }
    }
}

void draw_header(void) {
    if (lcd_dirty) {
        qp_drawtext_recolor(lcd_surface, 10, (os_glyph->height-mononoki->line_height), mononoki, "Kyria", HSV_CYAN, HSV_BLACK);
        qp_drawtext_recolor(lcd_surface, 10, (os_glyph->height), mononoki, "rev 4.1", HSV_CYAN, HSV_BLACK);
    }
}

void draw_os(void) {
    static uint8_t last_os = 0;
    if (lcd_dirty || last_os != user_config.os) {
        if (last_os != user_config.os) {
            qp_close_image(os_glyph);
            switch(user_config.os) {
                case MACOS:
                    os_glyph = qp_load_image_mem(gfx_apple_glyph);
                break;
                case WINDOWS:
                    os_glyph = qp_load_image_mem(gfx_windows_glyph);
                break;
                case LINUX:
                    os_glyph = qp_load_image_mem(gfx_linux_glyph);
                break;
                default:
                    os_glyph = qp_load_image_mem(gfx_circle_x);
                break;
            }
            last_os = user_config.os;
        }
        switch(user_config.os) {
            case MACOS:
                qp_drawimage_recolor(lcd_surface, ((LCD_WIDTH - (os_glyph->width + 2))), 10, os_glyph, HSV_WHITE, HSV_BLACK);
            break;
            case WINDOWS:
                qp_drawimage_recolor(lcd_surface, ((LCD_WIDTH - (os_glyph->width + 2))), 10, os_glyph, HSV_BLUE, HSV_BLACK);
            break;
            case LINUX:
                qp_drawimage_recolor(lcd_surface, ((LCD_WIDTH - (os_glyph->width + 2))), 10, os_glyph, HSV_WHITE, HSV_BLACK);
            break;
            default:
                qp_drawimage_recolor(lcd_surface, ((LCD_WIDTH - (os_glyph->width + 2))), 10, os_glyph, HSV_RED, HSV_BLACK);
            break;
        }
    }
}

void draw_status(void) {
    if (lcd_dirty) {
        if (caps_word_on) {
            qp_drawimage_recolor(lcd_surface, 5, LCD_STATUS_LINE, capsword_glyph, HSV_ACTIVE, HSV_BLACK);
        } else if (host_keyboard_led_state().caps_lock) {
            qp_drawimage_recolor(lcd_surface, 5, LCD_STATUS_LINE, capsword_glyph, HSV_RED, HSV_BLACK);
        } else {
            qp_drawimage_recolor(lcd_surface, 5, LCD_STATUS_LINE, capsword_glyph, HSV_INACTIVE, HSV_BLACK);
        }

        switch(xcase_state) {
            case XCASE_ON:
                qp_drawimage_recolor(lcd_surface, (capsword_glyph->width + 10), LCD_STATUS_LINE, xcase_glyph, HSV_ACTIVE, HSV_BLACK);
            break;
            case XCASE_WAIT:
                qp_drawimage_recolor(lcd_surface, (capsword_glyph->width + 10), LCD_STATUS_LINE, xcase_glyph, HSV_YELLOW, HSV_BLACK);
            break;
            default:
                qp_drawimage_recolor(lcd_surface, (capsword_glyph->width + 10), LCD_STATUS_LINE, xcase_glyph, HSV_INACTIVE, HSV_BLACK);
            break;
        }

        qp_drawimage_recolor(lcd_surface, ((capsword_glyph->width*2) + 15), LCD_STATUS_LINE, capslock_glyph, HSV_INACTIVE, HSV_BLACK);
    }
}

void draw_mods(void) {
    static uint8_t                last_mods    = 0;
    uint8_t                       current_mods = get_mods() | get_weak_mods() | get_oneshot_mods();
    if (lcd_dirty || last_mods != current_mods) {
        last_mods = current_mods;
        if (last_mods & MOD_MASK_GUI) {
            qp_drawimage_recolor(lcd_surface, ((command_glyph->width*3)+20), LCD_MOD_LINE, command_glyph, HSV_ACTIVE, HSV_BLACK);
        } else {
            qp_drawimage_recolor(lcd_surface, ((command_glyph->width*3)+20), LCD_MOD_LINE, command_glyph, HSV_INACTIVE, HSV_BLACK);
        }

        if (last_mods & MOD_MASK_CTRL) {
            qp_drawimage_recolor(lcd_surface, (5), LCD_MOD_LINE, ctrl_glyph, HSV_ACTIVE, HSV_BLACK);
        } else {
            qp_drawimage_recolor(lcd_surface, (5), LCD_MOD_LINE, ctrl_glyph, HSV_INACTIVE, HSV_BLACK);
        }

        if (last_mods & MOD_MASK_ALT) {
            qp_drawimage_recolor(lcd_surface, (command_glyph->width+10), LCD_MOD_LINE, option_glyph, HSV_ACTIVE, HSV_BLACK);
        } else {
            qp_drawimage_recolor(lcd_surface, (command_glyph->width+10), LCD_MOD_LINE, option_glyph, HSV_INACTIVE, HSV_BLACK);
        }

        if (last_mods & MOD_MASK_SHIFT) {
            qp_drawimage_recolor(lcd_surface, ((command_glyph->width*2)+15), LCD_MOD_LINE, shift_glyph, HSV_ACTIVE, HSV_BLACK);
        } else {
            qp_drawimage_recolor(lcd_surface, ((command_glyph->width*2)+15), LCD_MOD_LINE, shift_glyph, HSV_INACTIVE, HSV_BLACK);
        }
    }
}


bool module_post_init_user(void) {
    os_glyph = qp_load_image_mem(gfx_circle_x);
    command_glyph = qp_load_image_mem(gfx_command_glyph);
    ctrl_glyph = qp_load_image_mem(gfx_ctrl_glyph);
    option_glyph = qp_load_image_mem(gfx_option_glyph);
    shift_glyph = qp_load_image_mem(gfx_shift_glyph);
    capsword_glyph = qp_load_image_mem(gfx_capsword);
    capslock_glyph = qp_load_image_mem(gfx_capslock);
    xcase_glyph = qp_load_image_mem(gfx_xcase);
    layer_border = qp_load_image_mem(gfx_layer_border);
    dprintln("Loading layer_border into memory");
    mononoki = qp_load_font_mem(font_mononoki);
    bbt = qp_load_font_mem(font_bigbluetermmono);
    lcd_dirty = true;
    draw_status();
    draw_os();
    draw_status();
    draw_layer();
    draw_mods();
    qp_surface_draw(lcd_surface, lcd, 0, 0, 0);
    qp_flush(lcd);
    return false;
}

void draw_leader_screen(void) {
    if (lcd_dirty) {
        static const char *leader1 =    "LEADING";
        static const char *leader2 =    "[DD]  Dyn Macro";
        static const char *leader3 =    "[SA]   Arr Apps";
        static const char *leader4 =    "[SS]  Scrn Snag";
        static const char *leader5 =    "[SC]  Scrn Clip";
        static const char *leader6 =    "[RR]   FW Flash";
        static const char *leader7 =    "[EC]  @caracarn";
        static const char *leader8 =    "[ET]    @trueip";

        uint16_t left = ((LCD_WIDTH-qp_textwidth(bbt, leader1))/2) - 2;
        uint16_t right = ((LCD_WIDTH-qp_textwidth(bbt, leader1))/2)+(qp_textwidth(bbt, leader1) + 2);
        uint16_t top = bbt->line_height + 1;
        uint16_t bottom = bbt->line_height + 2;

        qp_clear(lcd_surface);
        qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(bbt, leader1))/2), LCD_LINE_ONE, bbt, leader1, HSV_YELLOW, HSV_BLACK);
        qp_rect(lcd_surface, left, top, right, bottom, HSV_WHITE, true);
        qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, leader2))/2), LCD_LINE_TWO + 2, mononoki, leader2, HSV_CYAN, HSV_BLACK);
        qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, leader3))/2), LCD_LINE_THREE + 2, mononoki, leader3, HSV_CYAN, HSV_BLACK);
        qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, leader4))/2), LCD_LINE_FOUR + 2, mononoki, leader4, HSV_CYAN, HSV_BLACK);
        qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, leader5))/2), LCD_LINE_FIVE + 2, mononoki, leader5, HSV_CYAN, HSV_BLACK);
        qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, leader6))/2), LCD_LINE_SIX + 2, mononoki, leader6, HSV_CYAN, HSV_BLACK);
        qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, leader7))/2), LCD_LINE_SEVEN + 2, mononoki, leader7, HSV_CYAN, HSV_BLACK);
        qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, leader8))/2), LCD_LINE_EIGHT + 2, mononoki, leader8, HSV_CYAN, HSV_BLACK);
    }
}

void draw_pass_screen(void) {
    if (lcd_dirty) {
        static const char *pass1 = "PASS-KEYS";
        static const char *pass2 = "[A] Ad!|[B] LbD";
        static const char *pass3 = "[D] D!2|[I] T!P";
        static const char *pass4 = "[J] JbD|[L] L2c";
        static const char *pass5 = "[N] Nv_|[O] Pdn";
        static const char *pass6 = "[P] P@s|[Q] StQ";
        static const char *pass7 = "[R] IWR|[S] S1b";
        static const char *pass8 = "[T] Tit|[Y] Lab";

        uint16_t left = ((LCD_WIDTH-qp_textwidth(bbt, pass1))/2) - 2;
        uint16_t right = ((LCD_WIDTH-qp_textwidth(bbt, pass1))/2)+(qp_textwidth(bbt, pass1) + 2);
        uint16_t top = bbt->line_height + 1;
        uint16_t bottom = bbt->line_height + 2;

        // int16_t width = qp_textwidth(my_font, pass1);
        qp_clear(lcd_surface);
        qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(bbt, pass1))/2), LCD_LINE_ONE, bbt, pass1, HSV_YELLOW, HSV_BLACK);
        qp_rect(lcd_surface, left, top, right, bottom, HSV_WHITE, true);
        qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, pass2))/2), LCD_LINE_TWO + 2, mononoki, pass2, HSV_CYAN, HSV_BLACK);
        qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, pass3))/2), LCD_LINE_THREE + 2, mononoki, pass3, HSV_CYAN, HSV_BLACK);
        qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, pass4))/2), LCD_LINE_FOUR + 2, mononoki, pass4, HSV_CYAN, HSV_BLACK);
        qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, pass5))/2), LCD_LINE_FIVE + 2, mononoki, pass5, HSV_CYAN, HSV_BLACK);
        qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, pass6))/2), LCD_LINE_SIX + 2, mononoki, pass6, HSV_CYAN, HSV_BLACK);
        qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, pass7))/2), LCD_LINE_SEVEN + 2, mononoki, pass7, HSV_CYAN, HSV_BLACK);
        qp_drawtext_recolor(lcd_surface, ((LCD_WIDTH - qp_textwidth(mononoki, pass8))/2), LCD_LINE_EIGHT + 2, mononoki, pass8, HSV_CYAN, HSV_BLACK);
    }
}

void housekeeping_task_keymap(void) {
    static uint32_t last_draw = 0;
    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();
            if (get_highest_layer(layer_state | default_layer_state) == _ADJUST) {
                render_menu();
            } else if (is_passing()) {
                dprintln("QPAINTER is_passing");
                draw_pass_screen();
            }
            else if (is_leading()){
                draw_leader_screen();
            }
            else {
                if (lcd_dirty) {
                    dprintln("QPAINTER lcd_dirty");
                    qp_clear(lcd_surface);
                }
                draw_header();
                draw_status();
                draw_os();
                draw_status();
                draw_layer();
                draw_mods();
            }
            lcd_dirty = false;
            qp_surface_draw(lcd_surface, lcd, 0, 0, 0);
            qp_flush(lcd);
        // }
    }
}

bool display_module_housekeeping_task_user(bool second_display) {
    return false;
}

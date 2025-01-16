#include "halcyon_modules/hlc_tft_display/hlc_tft_display.h"
#include "qp_surface.h"
#include "features/mononoki.qff.h"
#include "features/casemodes.h"

static painter_font_handle_t my_font;

painter_device_t lcd;
painter_device_t lcd_surface;

bool module_post_init_user(void) {
    my_font = qp_load_font_mem(font_mononoki);
    static const char *text = "Hello from SplitKB!";
    int16_t width = qp_textwidth(my_font, text);
    qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - width), (LCD_HEIGHT - my_font->line_height), my_font, text, HSV_BLUE, HSV_BLACK);
    qp_surface_draw(lcd_surface, lcd, 0, 0, 0);
    return false;
}

void housekeeping_task_keymap(void) {
    static uint32_t last_draw = 0;
    static const char *caps = "CAPSWORD";
    int16_t width = qp_textwidth(my_font, caps);
    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();
        // Print CAPSWORD if caps word is active
        if (caps_word_enabled()) {
            qp_drawtext_recolor(lcd_surface, (LCD_WIDTH - width), (LCD_HEIGHT - 2*(my_font->line_height)), my_font, caps, HSV_RED, HSV_BLACK);
        } else {
            qp_surface_draw(lcd_surface, lcd, 0, 0, 0);
        }
        qp_flush(lcd_surface);
    }
}

bool display_module_housekeeping_task_user(bool second_display) {
    return false;
}

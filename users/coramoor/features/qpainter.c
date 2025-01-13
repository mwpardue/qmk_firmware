#include "halcyon_modules/hlc_tft_display/hlc_tft_display.h"
#include "qp_surface.h"
#include "mononoki.qff.h"

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

bool display_module_housekeeping_task_user(bool second_display) {
    return false;
}

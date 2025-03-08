#pragma once
#include "quantum.h"

extern bool lcd_dirty;
extern bool layer_dirty;
painter_font_handle_t mononoki, bbt;
painter_device_t lcd;
painter_device_t lcd_surface;

/*extern hsv_t sel_fg;*/
/*extern hsv_t sel_bg;*/
/**/
/*HSV sel_fg = {*/
/*    .h = 43,*/
/*    .s = 255,*/
/*    .v = 255,*/
/*};*/
/**/
/*HSV sel_bg = {*/
/*    .h = 0,*/
/*    .s = 0,*/
/*    .v = 0,*/
/*};*/

/*#define CLR_SEL_FG sel_fg.h, sel_fg.s, sel_fg.v*/
/*#define CLR_SEL_BG sel_bg.h, sel_bg.s, sel_bg.v*/

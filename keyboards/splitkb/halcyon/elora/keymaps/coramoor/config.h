/* Copyright 2022 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifndef CONFIG_USER_H
    #define CONFIG_USER_H
#endif

/* Select hand configuration */

#undef FORCE_NKRO
#define FORCE_NKRO

#define HALCYON_KEYBOARD

#define ELORA_KEYBOARD

#define CHORDAL_HOLD

#ifdef SMART_CASE_ENABLE
    #define CUSTOM_ONESHOT_TIMEOUT 2000
#endif

// #ifdef MOUSEKEY_ENABLE
//   #define MK_KINETIC_SPEED
// #endif

#ifdef COMBO_ENABLE
    #define COMBO_COUNT 11
#endif

#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_KEYPRESSES // reacts to keypresses
    #define RGB_MATRIX_TIMEOUT 180000 // number of ticks to wait until disabling effects
    #define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
    #define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
    #ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
        #undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
            #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
    #endif
    #define RGB_MATRIX_DEFAULT_VAL 150
    #define RGB_MATRIX_HUE_STEP 5
    #define RGB_MATRIX_SAT_STEP 5
    #define RGB_MATRIX_VAL_STEP 5
    #define RGB_MATRIX_SPD_STEP 10
    #ifdef RGB_MATRIX_DEFAULT_MODE
        #undef RGB_MATRIX_DEFAULT_MODE
    #endif
    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    #define RGB_MATRIX_DEFAULT_HUE 105
    /*#ifdef RGB_MATRIX_TYPING_HEATMAP_SPREAD*/
    /*    #undef RGB_MATRIX_TYPING_HEATMAP_SPREAD*/
    /*#endif*/
    /*#ifdef RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT*/
    /*    #undef RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT*/
    /*#endif*/
    /*#define RGB_MATRIX_TYPING_HEATMAP_SPREAD rgb_matrix_get_heatmap_spread()*/
    /*#define RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT rgb_matrix_get_heatmap_area_limit()*/

#define ENABLE_RGB_MATRIX_SOLID
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define ENABLE_RGB_MATRIX_DUAL_BEACON
#define ENABLE_RGB_MATRIX_HUE_BREATHING
#define ENABLE_RGB_MATRIX_HUE_PENDULUM
#define ENABLE_RGB_MATRIX_HUE_WAVE
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define ENABLE_RGB_MATRIX_SPLASH
#define ENABLE_RGB_MATRIX_MULTISPLASH
#define ENABLE_RGB_MATRIX_SOLID_SPLASH
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH



#undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#undef ENABLE_RGB_MATRIX_BAND_SAT
#undef ENABLE_RGB_MATRIX_BAND_VAL
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#undef ENABLE_RGB_MATRIX_CYCLE_ALL
#undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#undef ENABLE_RGB_MATRIX_RAINDROPS
#undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#undef ENABLE_RGB_MATRIX_PIXEL_FLOW
#undef ENABLE_RGB_MATRIX_PIXEL_RAIN
#undef ENABLE_RGB_MATRIX_DIGITAL_RAIN
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS



#define HSV_AQUA 93, 250, 200

#ifdef RGB_MATRIX_CUSTOM_ENABLED
    #define FUNCTION_UNDERGLOW HSV_RED
    #define HEX_UNDERGLOW HSV_PURPLE

    #define XCASE_ON_STRONG_INDICATOR HSV_PURPLE
    #define XCASE_WAIT_STRONG_INDICATOR HSV_GREEN
    #define XCASE_WAIT_INDICATOR HSV_YELLOW
    #define XCASE_ON_INDICATOR HSV_BLUE
    #define CAPS_LOCK_INDICATOR HSV_RED
    #define SHIFT_INDICATOR HSV_ORANGE
    #define CTRL_INDICATOR HSV_PINK
#endif //RGB_MATRIX_LEDMAPS_ENABLED

#endif

#   define SPLIT_LAYER_STATE_ENABLE
#   define SPLIT_LED_STATE_ENABLE
#   define SPLIT_MODS_ENABLE

#ifdef HLC_TFT_DISPLAY
    /*#define QUANTUM_PAINTER_NUM_IMAGES 10*/
    #define LCD_HEIGHT 240
    #define LCD_WIDTH 135
// 3 surfaces:
#define SURFACE_NUM_DEVICES 1
#define QUANTUM_PAINTER_DEBUG
#define QUANTUM_PAINTER_NUM_IMAGES 12
/*#undef ST7789_NUM_DEVICES*/
/*#define ST7789_NUM_DEVICES 1*/
#endif

#ifdef OLED_ENABLE
#   define OLED_FONT_H "keyboards/splitkb/kyria/keymaps/coramoor/glcdfont.c"
#   define OLED_TIMEOUT 60000
#   define SPLIT_OLED_ENABLE
#   define OLED_FONT_LSB
#endif


#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

//#define TAPPING_TERM 100
#define TAPPING_TERM 200
#define QUICK_TAP_TERM 0


// Frood settings for bootloader
// https://42keebs.eu/shop/parts/controllers/frood-rp2040-pro-micro-controller/
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED D5 // Specify an optional status LED by GPIO number which blinks when entering the bootloader

/* #ifdef RGBLIGHT_ENABLE */
/*     #define RGBLIGHT_EFFECT_BREATHING */
/*     #define RGBLIGHT_EFFECT_RAINBOW_MOOD */
/*     #define RGBLIGHT_EFFECT_RAINBOW_SWIRL */
/*     #define RGBLIGHT_EFFECT_SNAKE */
/*     #define RGBLIGHT_EFFECT_KNIGHT */
/*     #define RGBLIGHT_EFFECT_CHRISTMAS */
/*     #define RGBLIGHT_EFFECT_STATIC_GRADIENT */
/*     #define RGBLIGHT_EFFECT_RGB_TEST */
/*     #define RGBLIGHT_EFFECT_ALTERNATING */
/*     #define RGBLIGHT_EFFECT_TWINKLE */
/*     #define RGBLIGHT_LIMIT_VAL 120 */
/*     #define RGBLIGHT_HUE_STEP 10 */
/*     #define RGBLIGHT_SAT_STEP 17 */
/*     #define RGBLIGHT_VAL_STEP 17 */
/* #endif */

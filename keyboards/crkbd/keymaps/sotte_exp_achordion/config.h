#pragma once

// Select hand configuration
#define MASTER_LEFT

// https://getreuer.info/posts/keyboards/achordion/#relationship-between-achordion-and-chordal-hold
#define TAPPING_TERM 250
#define PERMISSIVE_HOLD
#define CHORDAL_HOLD

// #define QUICK_TAP_TERM_PER_KEY
// #define QUICK_TAP_TERM 0

// Double tat to activate CAPS
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

// Frood settings for bootloader
// https://42keebs.eu/shop/parts/controllers/frood-rp2040-pro-micro-controller/
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED D5 // Specify an optional status LED by GPIO number which blinks when entering the bootloader

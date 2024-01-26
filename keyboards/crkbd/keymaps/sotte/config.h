#pragma once

// Select hand configuration
#define MASTER_LEFT

#define TAPPING_TERM 200
#define QUICK_TAP_TERM 0

// Frood settings for bootloader
// https://42keebs.eu/shop/parts/controllers/frood-rp2040-pro-micro-controller/
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED D5 // Specify an optional status LED by GPIO number which blinks when entering the bootloader

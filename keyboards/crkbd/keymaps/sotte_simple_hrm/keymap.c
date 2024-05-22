// vim: ts=2:sw=2
/*
 * try home row mods on the bottom row.
 * potential problem: I have different shifted keys.
 */
#include QMK_KEYBOARD_H
#include "features/custom_shift_keys.h"
#include "features/oneshot.h"
#include "features/layer_lock.h"
#include "features/achordion.h"

enum layer_names {
  ALPHA_L,
  NAV_L,
  NUM_L,
  SYM_L,
};

enum keycodes {
  // one shot keycodes without timers
  OS_SHFT = SAFE_RANGE,
  OS_CTRL,
  OS_ALT,
  OS_GUI,
  // Misc
  LLOCK,
  // my special keys
  MY_COPY,
  MY_CUT,
  MY_PSTE,
};

// aliases - mostly to keep the format/style consistent
// one shot mods
#define OSM_SFT OSM(MOD_LSFT)
// layers
// #define LA_NAV  MO(NAV_L)
// #define LA_SYM  MO(SYM_L)
#define LA_NUM  MO(NUM_L)
// Layer tabs
#define SPC_NAV  LT(NAV_L, KC_SPC)
#define ESC_NAV  LT(NAV_L, KC_ESC)
#define ENT_SYM  LT(SYM_L, KC_ENT)
#define TAB_NUM  LT(NUM_L, KC_TAB)

// BOTTOM ROW MODS - LEFT
#define Z_BRM LALT_T(KC_Z)
#define X_BRM LGUI_T(KC_X)
#define C_BRM LCTL_T(KC_C)
#define V_BRM LSFT_T(KC_V)
// BOTTOM ROW MODS - RIGHT
#define M_BRM RSFT_T(KC_M)
#define COM_BRM RCTL_T(KC_COMM)
#define DOT_BRM RGUI_T(KC_DOT)
// I don't use this, as there are issuse with BRM and custom shift keys.
// But I don't use ALT that much anyways.
// #define UND_BRM LALT_T(KC_UNDS)


// ==============================================
// custom shift keys
// https://getreuer.info/posts/keyboards/custom-shift-keys/index.html
const custom_shift_key_t custom_shift_keys[] = {
  // {KC_DOT , KC_COMM},  // Shift . is ,
  {KC_COLN, KC_SCLN},  // Shift : is ;
  {KC_DQUO, KC_QUOT},  // Shift " is '
  {KC_UNDS, KC_MINS},  // Shift _ is -
  {KC_TILD, KC_GRV},   // Shift ~ is `
  {KC_EQL, KC_PLUS},   // Shift = is +
  {KC_LPRN, KC_LT},    // Shift ( is <
  {KC_RPRN, KC_GT},    // Shift ) is >
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

// ==============================================
// Custom key on hold
// https://getreuer.info/posts/keyboards/triggers/index.html#tap-vs.-long-press
#define PRN LT(1, KC_LPRN)

// ==============================================
// LAYOUT
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [ALPHA_L] = LAYOUT_split_3x6_3(
      XXXXXXX,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_COLN, XXXXXXX,
       LA_NUM,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                         KC_H,    KC_N,    KC_E,    KC_I,    KC_O, XXXXXXX,
      XXXXXXX,   Z_BRM,   X_BRM,   C_BRM,   V_BRM,    KC_B,                         KC_K,   M_BRM, COM_BRM, DOT_BRM, KC_UNDS, XXXXXXX,
                                          TAB_NUM, SPC_NAV,  ESC_NAV,   OSM_SFT, ENT_SYM,  KC_TAB
  ),
  [SYM_L] = LAYOUT_split_3x6_3(
      _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR,  KC_GRV, KC_QUES,   LLOCK,
      _______, KC_LCBR, KC_LBRC, KC_LPRN,  KC_EQL, KC_TILD,                      KC_QUOT, KC_DQUO, KC_RPRN, KC_RBRC, KC_RCBR, _______,
      _______, KC_SLSH, KC_ASTR, KC_PLUS, KC_MINS, KC_PIPE,                      KC_BSLS, KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT, _______,
                                          XXXXXXX, _______, _______,    _______, _______, _______
      //                                                                ^^^^^^^
  ),
  [NUM_L] = LAYOUT_split_3x6_3(
      _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_ASTR,    KC_7,    KC_8,    KC_9, KC_PLUS,   LLOCK,
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       KC_EQL,    KC_4,    KC_5,    KC_6, KC_MINS, _______,
      _______, KC_LALT, KC_LGUI, KC_LCTL, KC_LSFT, XXXXXXX,                         KC_0,    KC_1,    KC_2,    KC_3, KC_SLSH, _______,
                                          _______,  KC_SPC, XXXXXXX,    _______,  KC_SPC,  KC_DOT
      //                                  ^^^^^^^
  ),
  [NAV_L] = LAYOUT_split_3x6_3(
      _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_PSCR,                      KC_PGUP, KC_BSPC,   KC_UP,  KC_DEL,  KC_DEL,   LLOCK,
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_HOME, KC_LEFT, KC_DOWN,KC_RIGHT,  KC_END, _______,
      _______, KC_LALT, KC_LGUI, KC_LCTL, KC_LSFT, XXXXXXX,                      KC_PGDN,  KC_ENT,  KC_TAB,  QK_REP,  KC_APP, _______,
                                          _______, _______, _______,    XXXXXXX,  KC_SPC, XXXXXXX
      //                                           ^^^^^^^
  ),
};

// ==============================================
// Custom key on hold
// https://getreuer.info/posts/keyboards/triggers/index.html#tap-vs.-long-press

// Helper for implementing tap vs. long-press keys.
// Given a tap-hold key event, replaces the hold function with `long_press_keycode`.
static bool process_tap_or_long_press_key(keyrecord_t* record, uint16_t long_press_keycode) {
  if (record->tap.count == 0) {
    // Key is being held.
    if (record->event.pressed) {
      tap_code16(long_press_keycode);
    }
    return false;  // Skip default handling.
  }
  // Continue default handling.
  return true;
}

// ==============================================
// CORE
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_custom_shift_keys(keycode, record)) {
    return false;
  }
  if (!process_layer_lock(keycode, record, LLOCK)) {
    return false;
  }

  switch (keycode) {
    case PRN:  // Comma on tap, Ctrl+C on long press.
      return process_tap_or_long_press_key(record, KC_RPRN);
  };

  // update_oneshot(&os_sft_state, KC_LSFT, OS_SHFT, keycode, record);
  // update_oneshot(&os_ctl_state, KC_LCTL, OS_CTRL, keycode, record);
  // update_oneshot(&os_alt_state, KC_LALT, OS_ALT, keycode, record);
  // update_oneshot(&os_gui_state, KC_LGUI, OS_GUI, keycode, record);

  return true;
}

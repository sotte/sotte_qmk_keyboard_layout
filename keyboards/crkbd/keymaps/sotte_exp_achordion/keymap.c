// vim: ts=2:sw=2
/*
 * Goal: evaluate the typing streak feature achordiaon when using actua home row mods.
 *
 * Still need to figure out how to adjust the non-alpha layers assuming I can use smtd for the home row mods.
 */
#include QMK_KEYBOARD_H
#include "features/custom_shift_keys.h"
#include "features/layer_lock.h"
#include "features/achordion.h"

enum layer_names {
  _ALPHA,
  _NAV,
  _SYM,
  _NUM,
};

enum keycodes {
  // Misc
  LLOCK = SAFE_RANGE,
  // one shot keycodes without timers
  OS_SHFT,
  OS_CTRL,
  OS_ALT,
  OS_GUI,
  // my special keys
  MY_COPY,
  MY_CUT,
  MY_PSTE,
};

// ALIASES - mostly to keep the format/style consistent
// one shot mods
#define OSM_SFT  OSM(MOD_LSFT)

// HOME ROW MODS
// ALPHA LEFT
#define A_HRM    LALT_T(KC_A)
#define R_HRM    LGUI_T(KC_R)
#define S_HRM    LCTL_T(KC_S)
#define T_HRM    LSFT_T(KC_T)
// ALPHA RIGHT
#define N_HRM    RSFT_T(KC_N)
#define E_HRM    RCTL_T(KC_E)
#define I_HRM    RGUI_T(KC_I)
#define O_HRM    LALT_T(KC_O)
// SYM LEFT
#define QUES_HR  LALT_T(KC_QUES)
#define LBRC_HR  LGUI_T(KC_LBRC)
#define LPRN_HR  LCTL_T(KC_LPRN)
#define EQL_HR   LSFT_T(KC_EQL)
// SYM RIGHT
#define UNDS_HR  LSFT_T(KC_UNDS)
#define RPRN_HR  LCTL_T(KC_RPRN)
#define RBRC_HR  LGUI_T(KC_RBRC)
#define GRVE_HR  LALT_T(KC_GRAVE)

#define TAB_CTL  LCTL_T(KC_TAB)

// Layer taps and modifier taps
#define SPC_NAV  LT(_NAV, KC_SPC)
#define ENT_SYM  LT(_SYM, KC_ENT)

// Volume
#define VOL_MUT  KC_KB_MUTE
#define VOL_UP   KC_KB_VOLUME_UP
#define VOL_DWN  KC_KB_VOLUME_DOWN

// ==============================================
// ACHORDION
bool achordion_chord(
  uint16_t tap_hold_keycode,
  keyrecord_t* tap_hold_record,
  uint16_t other_keycode,
  keyrecord_t* other_record
) {
  // Thumb cluster is independent of the achordion logic; it should works for both sides.
  // I.e. when using the left thumb cluster, you can use buttons on the left,
  // and when using the right thumb cluster, you can use buttons on the right.
  if (tap_hold_record->event.key.row == 3) { return true; }
  if (tap_hold_record->event.key.row == 7) { return true; }
  // Also, ignore the leftmost column
  if (tap_hold_record->event.key.col == 0) { return true; }

  return achordion_opposite_hands(tap_hold_record, other_record);
}

void matrix_scan_user(void) {
  achordion_task();
}

// ==============================================
// CUSTOM SHIFT KEYS
// https://getreuer.info/posts/keyboards/custom-shift-keys/index.html
const custom_shift_key_t custom_shift_keys[] = {
  {KC_COLN, KC_SCLN},  // Shift : is ;
  {KC_DQUO, KC_QUOT},  // Shift " is '
  {KC_TILD, KC_GRV},   // Shift ~ is `
  {KC_EQL, KC_PLUS},   // Shift = is +
  // top symbol row maps to number row (shifted)
  {KC_EXLM, KC_1},
  {KC_AT, KC_2},
  {KC_HASH, KC_3},
  {KC_DLR, KC_4},
  {KC_PERC, KC_5},
  {KC_CIRC, KC_6},
  {KC_AMPR, KC_7},
  {KC_ASTR, KC_8},
  {KC_SLSH, KC_9},
  {KC_SCLN, KC_0},
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

// ==============================================
// Custom keycode for mod tap
// https://github.com/getreuer/qmk-keymap/discussions/69
#define MT_CKC(mapping, kc) \
  case mapping: \
    if (record->tap.count) { \
      if (record->event.pressed) { \
        register_code16(kc); \
      } else { \
        unregister_code16(kc); \
      } \
      return false; \
    } \
    break;


// ==============================================
// LAYOUT
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ALPHA] = LAYOUT_split_3x6_3(
    XXXXXXX,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_COLN, XXXXXXX,
    TAB_CTL,   A_HRM,   R_HRM,   S_HRM,   T_HRM,    KC_D,                         KC_H,   N_HRM,   E_HRM,   I_HRM,   O_HRM,  QK_REP,
    XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_DQUO, XXXXXXX,
                                         KC_ENT, SPC_NAV, KC_ESC,     OSM_SFT, ENT_SYM,  KC_TAB
  ),
  [_NAV] = LAYOUT_split_3x6_3(
    _______, KC_PSCR, KC_BSPC,   KC_UP,  KC_DEL, KC_PGUP,                       VOL_UP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   LLOCK,
    _______, KC_HOME, KC_LEFT, KC_DOWN,KC_RIGHT,  KC_END,                      VOL_MUT, KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT, _______,
    _______, XXXXXXX, XXXXXXX,  KC_TAB,  KC_ENT, KC_PGDN,                      VOL_DWN, XXXXXXX, XXXXXXX,  QK_REP,  KC_APP, _______,
                                        _______, _______, _______,    _______, _______, _______
    //                                           ^^^^^^^
  ),
  [_SYM] = LAYOUT_split_3x6_3(
    _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_SLSH, KC_COLN,   LLOCK,
    _______, QUES_HR, LBRC_HR, LPRN_HR,  EQL_HR, KC_PIPE,                      KC_TILD, UNDS_HR, RPRN_HR, RBRC_HR, GRVE_HR, _______,
    _______, KC_LALT,  KC_APP, KC_LCTL, KC_PLUS, KC_BSLS,                      XXXXXXX, KC_MINS, KC_COMM,  KC_DOT, KC_DQUO, _______,
                                        _______, _______, _______,    _______, _______, _______
    //                                                                         ^^^^^^^
  ),
  [_NUM] = LAYOUT_split_3x6_3(
    _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_ASTR,    KC_7,    KC_8,    KC_9, KC_PLUS,   LLOCK,
    _______, KC_QUES, KC_BSLS, KC_COMM,  KC_DOT,  KC_SPC,                       KC_EQL,    KC_4,    KC_5,    KC_6, KC_MINS, _______,
    _______, KC_LALT, KC_LGUI, KC_LCTL, KC_LSFT, XXXXXXX,                         KC_0,    KC_1,    KC_2,    KC_3, KC_SLSH, _______,
                                        _______, _______, _______,    _______, _______, _______
    //                                           ^^^^^^^                       ^^^^^^^
  ),
};

// ==============================================
//CORE
bool process_record_user(uint16_t keycode, keyrecord_t* record) {

  if (!process_achordion(keycode, record)) { return false; }

  if (!process_custom_shift_keys(keycode, record)) { return false; }

  if (!process_layer_lock(keycode, record, LLOCK)) { return false; }

  switch (keycode) {
    // hrm with non-basic keys
    MT_CKC(QUES_HR, KC_QUES)
    MT_CKC(UNDS_HR, KC_UNDS)
    MT_CKC(LPRN_HR, KC_LPRN)
    MT_CKC(RPRN_HR, KC_RPRN)
  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _SYM, _NAV, _NUM);
}

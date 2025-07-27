// vim: ts=2:sw=2
#include QMK_KEYBOARD_H
#include "features/custom_shift_keys.h"
#include "features/layer_lock.h"

// =============================================================================
enum layer_names {
  _ALPHA,
  _NAV,
  _SYM,
  _NUM,
  _NUM2,
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
  CKC_Z,
  CKC_X,
  CKC_C,
  CKC_V,
};

// ALIASES - mostly to keep the format/style consistent
#define OSM_SFT  OSM(MOD_LSFT)
#define TAB_CTL  LCTL_T(KC_TAB)
// Layer taps and modifier taps
#define SPC_NAV  LT(_NAV, KC_SPC)
#define ENT_SYM  LT(_SYM, KC_ENT)
#define ESC_NUM  LT(_NUM2, KC_ESC)
#define ESC_NAV  LT(_NAV, KC_ESC)

// HOME ROW MODS ON ALPHA
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
// HOME ROW MODS ON SYM
// SYM LEFT
#define QUES_HR  LALT_T(KC_QUES)
// no key for WIN yet
#define LPRN_HR  LCTL_T(KC_LPRN)
#define RPRN_HR  LSFT_T(KC_RPRN)
// SYM RIGHT
#define EQL_HR   LSFT_T(KC_EQL)
#define MINS_HR  LCTL_T(KC_MINS)
#define PLUS_HR  LGUI_T(KC_PLUS)
#define GRVE_HR  LALT_T(KC_GRAVE)

// Volume
#define VOL_MUT  KC_KB_MUTE
#define VOL_UP   KC_KB_VOLUME_UP
#define VOL_DWN  KC_KB_VOLUME_DOWN

// LONG PRESS KEYS
#define CKC_Z LT(0, KC_Z)
#define CKC_X LT(0, KC_X)
#define CKC_C LT(0, KC_C)
#define CKC_V LT(0, KC_V)

#define CKC_Q LT(0, KC_Q)
#define CKC_W LT(0, KC_W)
#define CKC_F LT(0, KC_F)
#define CKC_P LT(0, KC_P)
#define CKC_G LT(0, KC_G)
#define CKC_J LT(0, KC_J)
#define CKC_L LT(0, KC_L)
#define CKC_U LT(0, KC_U)
#define CKC_Y LT(0, KC_Y)
#define CKC_COLN LT(0, KC_COLN)

// =============================================================================
// chordal_hold_layout
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
  LAYOUT(
    '*', 'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R', '*',
    '*', 'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R', '*',
    '*', 'L', 'L', 'L', 'L', 'L',   'R', 'R', 'R', 'R', 'R', '*',
                   '*', 'R', '*',   '*', '*', '*'
  );

// =============================================================================
// CUSTOM SHIFT KEYS
// https://getreuer.info/posts/keyboards/custom-shift-keys/index.html
const custom_shift_key_t custom_shift_keys[] = {
  {KC_UNDS, KC_MINS},
  {KC_COLN, KC_SCLN},
  {KC_DQUO, KC_QUOT},
  {KC_TILD, KC_GRV},
  {KC_EQL, KC_PLUS},
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

// =============================================================================
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

#define LONG_PRESS(mapping, record, long_press_key) \
  case mapping: \
    if (record->tap.count == 0) { \
      if (record->event.pressed) { \
        tap_code16(long_press_key); \
      } \
      return false; \
    } \
    return true;


// =============================================================================
// FLOW TAP
uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t* record, uint16_t prev_keycode) {
  // https://docs.qmk.fm/tap_hold#flow-tap
  if (keycode == SPC_NAV) {
    return 0;  // Disable flow tap for space
  }
  return FLOW_TAP_TERM;
}

// =============================================================================
// LAYOUT
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ALPHA] = LAYOUT_split_3x6_3(
    XXXXXXX,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_COLN, XXXXXXX,
    TAB_CTL,   A_HRM,   R_HRM,   S_HRM,   T_HRM,    KC_D,                         KC_H,   N_HRM,   E_HRM,   I_HRM,   O_HRM, KC_QUOT,
    XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_UNDS, XXXXXXX,
                                         KC_ENT, SPC_NAV, ESC_NUM,    OSM_SFT, ENT_SYM,  KC_TAB
  ),
  [_NAV] = LAYOUT_split_3x6_3(
    _______, KC_PSCR, KC_BSPC,   KC_UP,  KC_DEL, KC_PGUP,                      KC_BRIU,  VOL_UP, XXXXXXX, XXXXXXX, XXXXXXX,   LLOCK,
    _______, KC_HOME, KC_LEFT, KC_DOWN,KC_RIGHT,  KC_END,                      VOL_MUT, KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT, _______,
    _______, XXXXXXX, XXXXXXX,  KC_TAB,  KC_ENT, KC_PGDN,                      KC_BRID, VOL_DWN, XXXXXXX,  QK_REP,  KC_APP, _______,
                                        _______, _______, _______,    _______, _______, _______
    //                                           ^^^^^^^
  ),
  [_SYM] = LAYOUT_split_3x6_3(
    _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_SLSH, KC_COLN,   LLOCK,
    _______, QUES_HR, KC_LGUI, LPRN_HR, RPRN_HR, KC_PIPE,                      KC_TILD,  EQL_HR, MINS_HR, PLUS_HR, GRVE_HR, KC_DQUO,
    _______, KC_QUES, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS,                      XXXXXXX,KC_GRAVE, KC_LABK, KC_RABK, KC_UNDS, _______,
                                        _______, _______, _______,    _______, _______, _______
    //                                                                         ^^^^^^^
  ),
  [_NUM] = LAYOUT_split_3x6_3(
    _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_ASTR,    KC_7,    KC_8,    KC_9, KC_PLUS,   LLOCK,
    _______, KC_LALT, KC_LGUI, KC_LCTL, KC_LSFT,  KC_SPC,                         KC_0,    KC_4,    KC_5,    KC_6, KC_MINS, KC_DQUO,
    _______, KC_LALT, KC_LGUI, KC_LCTL, KC_LSFT, XXXXXXX,                         KC_0,    KC_1,    KC_2,    KC_3, KC_SLSH, _______,
                                        _______, _______, _______,    _______, _______, _______
    //                                           ^^^^^^^                       ^^^^^^^
  ),
  [_NUM2] = LAYOUT_split_3x6_3(
    _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_5,    KC_6,    KC_7,    KC_8, _______,
    _______, KC_LALT, KC_LGUI, KC_LCTL, KC_LSFT,  KC_SPC,                         KC_0,    KC_1,    KC_2,    KC_3,    KC_4, KC_DQUO,
    _______, KC_LALT, KC_LGUI, KC_LCTL,  KC_SPC, XXXXXXX,                         KC_0,    KC_9, KC_COMM,  KC_DOT, KC_UNDS, _______,
                                        _______, _______, _______,    _______, _______, _______
    //                                                    ^^^^^^^
  )
};

// =============================================================================
//CORE
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_custom_shift_keys(keycode, record)) { return false; }

  if (!process_layer_lock(keycode, record, LLOCK)) { return false; }

  switch (keycode) {
    // hrm with non-basic keys
    MT_CKC(QUES_HR, KC_QUES)
    MT_CKC(LPRN_HR, KC_LPRN)
    MT_CKC(RPRN_HR, KC_RPRN)
    MT_CKC(PLUS_HR, KC_PLUS)

    // // long perss logic
    LONG_PRESS(CKC_Z, record, C(KC_Z))
    LONG_PRESS(CKC_X, record, C(KC_X))
    LONG_PRESS(CKC_C, record, C(KC_C))
    LONG_PRESS(CKC_V, record, C(KC_V))
  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _SYM, _NAV, _NUM);
}

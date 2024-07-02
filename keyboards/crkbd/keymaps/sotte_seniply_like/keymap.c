// vim: ts=2:sw=2
/*
 * try home row mods on the bottom row.
 * potential problem: I have different shifted keys.
 */
#include QMK_KEYBOARD_H
#include "features/custom_shift_keys.h"
#include "features/layer_lock.h"
// #include "features/oneshot.h"
// #include "features/achordion.h"

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

// aliases - mostly to keep the format/style consistent
// one shot mods
#define OSM_SFT  OSM(MOD_LSFT)
// layers
#define MO_NAV   MO(_NAV)
#define MO_SYM   MO(_SYM)
#define MO_NUM   MO(_NUM)
// Layer taps and modifier taps
#define SPC_NAV  LT(_NAV, KC_SPC)
#define ESC_NAV  LT(_NAV, KC_ESC)
#define ESC_NUM  LT(_NUM, KC_ESC)
#define ESC_CTR  MT(MOD_LCTL, KC_ESC)
#define ENT_SYM  LT(_SYM, KC_ENT)
#define TAB_NUM  LT(_NUM, KC_TAB)
// volume
#define VOL_MUT  KC_KB_MUTE
#define VOL_UP   KC_KB_VOLUME_UP
#define VOL_DWN  KC_KB_VOLUME_DOWN

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
// Tab or hold definitions
// https://getreuer.info/posts/keyboards/triggers/index.html#tap-vs.-long-press
#define TH_Q LT(0, KC_Q)
#define TH_W LT(0, KC_W)
#define TH_F LT(0, KC_F)
#define TH_P LT(0, KC_P)
#define TH_G LT(0, KC_G)
#define TH_J LT(0, KC_J)
#define TH_L LT(0, KC_L)
#define TH_U LT(0, KC_U)
#define TH_Y LT(0, KC_Y)

static bool process_tap_or_long_press_key(keyrecord_t* record, uint16_t long_press_keycode) {
  if (record->tap.count == 0) {  // Key is being held.
    if (record->event.pressed) {
      tap_code16(long_press_keycode);
    }
    return false;  // Skip default handling.
  }
  return true;  // Continue default handling.
}

// A macro to clean up the switch statement.
#define TH_CASE(tap_key, long_press_key) \
  case tap_key: return process_tap_or_long_press_key(record, long_press_key);



// ==============================================
// LAYOUT
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ALPHA] = LAYOUT_split_3x6_3(
      XXXXXXX,    TH_Q,    TH_W,    TH_F,    TH_P,    TH_G,                         TH_J,    TH_L,    TH_U,    TH_Y, KC_COLN, XXXXXXX,
      KC_LCTL,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                         KC_H,    KC_N,    KC_E,    KC_I,    KC_O,  QK_REP,
      XXXXXXX,   Z_BRM,   X_BRM,   C_BRM,   V_BRM,    KC_B,                         KC_K,   M_BRM, COM_BRM, DOT_BRM, KC_UNDS, XXXXXXX,
                                           KC_TAB, SPC_NAV, ESC_CTR,    OSM_SFT, ENT_SYM, _______
  ),
  [_NAV] = LAYOUT_split_3x6_3(
      _______, VOL_MUT, VOL_DWN,  VOL_UP, KC_PSCR, KC_PSCR,                      KC_PGUP, KC_BSPC,   KC_UP,  KC_DEL,  KC_DEL,   LLOCK,
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_SPC,                      KC_HOME, KC_LEFT, KC_DOWN,KC_RIGHT,  KC_END, _______,
      _______, KC_LALT, KC_LGUI, KC_LCTL, KC_LSFT, XXXXXXX,                      KC_PGDN,  KC_ENT,  KC_TAB,  QK_REP,  KC_APP, _______,
                                          _______, _______, _______,    _______, _______, _______
      //                                           ^^^^^^^
  ),
  [_SYM] = LAYOUT_split_3x6_3(
      _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_ASTR, KC_QUOT, KC_DQUO,  KC_GRV, KC_PLUS,   LLOCK,
      _______, KC_QUES, KC_BSLS, KC_COMM,  KC_DOT, KC_CIRC,                       KC_EQL, KC_LPRN, KC_LBRC, KC_LCBR, KC_MINS, _______,
      _______, KC_LALT, KC_LGUI, KC_LCTL, KC_LSFT, KC_AMPR,                      KC_TILD, KC_RPRN, KC_RBRC, KC_RCBR, KC_SLSH, _______,
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

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _NUM);
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

  // Tap vs. long press
  switch (keycode) {
    TH_CASE(TH_Q, KC_EXLM)
    TH_CASE(TH_W, KC_AT)
    TH_CASE(TH_F, KC_HASH)
    TH_CASE(TH_P, KC_DLR)
    TH_CASE(TH_G, KC_PERC)

    TH_CASE(TH_J, KC_CIRC)
    TH_CASE(TH_L, KC_AMPR)
    TH_CASE(TH_U, KC_ASTR)
    TH_CASE(TH_Y, KC_LPRN)
  }

  return true;
}

// vim: ts=2:sw=2
/*
 * Goal: evaluate the use of sm_td for home row mods ON the home row, not on the bottom row like I normally do.
 *
 * Still need to figure out how to adjust the non-alpha layers assuming I can use smtd for the home row mods.
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
  // SMTD keycodes begin
  SMTD_KEYCODES_BEGIN,
  // left home row
  CKC_A,
  CKC_R,
  CKC_S,
  CKC_T,
  // right home row
  CKC_N,
  CKC_E,
  CKC_I,
  CKC_O,
  SMTD_KEYCODES_END,
  // SMTD keycodes end
};

// include after enum def is a bit annoying
#include "features/sm_td.h"

// aliases - mostly to keep the format/style consistent
// one shot mods
#define OSM_SFT  OSM(MOD_LSFT)
// layers
#define MO_NAV   MO(_NAV)
#define MO_SYM   MO(_SYM)
#define MO_NUM   MO(_NUM)
// Layer taps and modifier taps
// TODO: check smtd in the future
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

// ==============================================
// CUSTOM SHIFT KEYS
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
// LAYOUT
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ALPHA] = LAYOUT_split_3x6_3(
    XXXXXXX,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_COLN, XXXXXXX,
    KC_LCTL,   CKC_A,   CKC_R,   CKC_S,   CKC_T,    KC_D,                         KC_H,   CKC_N,   CKC_E,   CKC_I,   CKC_O,  QK_REP,
    XXXXXXX,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_UNDS, XXXXXXX,
                                           KC_TAB, SPC_NAV, ESC_CTR,    OSM_SFT, ENT_SYM,  KC_TAB
  ),
  [_NAV] = LAYOUT_split_3x6_3(
    _______, VOL_MUT, VOL_DWN,  VOL_UP, KC_PSCR, KC_PSCR,                      KC_PGUP, KC_BSPC,   KC_UP,  KC_DEL,  KC_DEL,   LLOCK,
    _______, KC_LALT, KC_LGUI, KC_LCTL, KC_LSFT,  KC_SPC,                      KC_HOME, KC_LEFT, KC_DOWN,KC_RIGHT,  KC_END, _______,
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

// ==============================================
// SMTD
// https://github.com/stasmarkin/sm_td/
void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
  // States are one of the two:
  // - touch → tap
  // - touch → hold → release
  switch (keycode) {
    // left home row
    SMTD_MT(CKC_A, KC_A, KC_LALT)
    SMTD_MT(CKC_R, KC_R, KC_LGUI)
    SMTD_MT(CKC_S, KC_S, KC_LCTL)
    SMTD_MT(CKC_T, KC_T, KC_LSFT)
    // right home row
    SMTD_MT(CKC_N, KC_N, KC_LSFT)
    SMTD_MT(CKC_E, KC_E, KC_LCTL)
    SMTD_MT(CKC_I, KC_I, KC_LGUI)
    SMTD_MT(CKC_O, KC_O, KC_LALT)
  }
}

// uint32_t get_smtd_timeout(uint16_t keycode, smtd_timeout timeout) {
//     switch (keycode) {
//         case CKC_A:
//         case CKC_O:
//             if (timeout == SMTD_TIMEOUT_TAP) return 300;
//     }
//     return get_smtd_timeout_default(timeout);
// }

// ==============================================
// CORE
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_smtd(keycode, record)) {
    return false;
  }

  if (!process_custom_shift_keys(keycode, record)) {
    return false;
  }

  if (!process_layer_lock(keycode, record, LLOCK)) {
    return false;
  }

  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _SYM, _NAV, _NUM);
}

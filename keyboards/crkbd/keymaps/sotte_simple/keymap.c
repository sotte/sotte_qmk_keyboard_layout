// vim: ts=2:sw=2
/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H
#include "features/custom_shift_keys.h"
#include "features/oneshot.h"
#include "features/layer_lock.h"
// #include "features/achordion.h"

enum layer_names {
  ALPHA_L,
  NAV_L,
  SYM_L,
  NUM_L,
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
#define OSM_CTL OSM(MOD_LCTL)
#define OSM_GUI OSM(MOD_LGUI)
#define OSM_ALT OSM(MOD_LALT)
// Ctrl+Something
// TODO: rethink these
#define CTRL_C  LCTL(KC_C)
#define CTRL_D  LCTL(KC_D)
#define CTRL_F  LCTL(KC_F)
#define CTRL_Q  LCTL(KC_Q)
#define CTRL_T  LCTL(KC_T)
#define CTRL_V  LCTL(KC_V)
#define CTRL_W  LCTL(KC_W)
// layers
#define LA_NAV  MO(NAV_L)
#define LA_SYM  MO(SYM_L)
#define LA_NUM  MO(NUM_L)
// Layer tabs
// #define BSP_SYM  LT(SYM_L, KC_BSPC)
// #define DEL_FUNC LT(FUNC_L, KC_DEL)
// #define ENT_NUM  LT(NUM_ALT_L, KC_ENT)
// #define ESC_NAV  LT(NAV_L, KC_ESC)
// #define ESC_NUM  LT(NUM_L, KC_ESC)
// #define ESC_SYM  LT(SYM_L, KC_ESC)
#define SPC_NAV  LT(NAV_L, KC_SPC)
// #define SPC_SYM  LT(SYM_ALT_L, KC_SPC)
// #define SPC_NUM  LT(NUM_ALT_L, KC_SPC)
// #define TAB_MOU  LT(MOUSE_L, KC_TAB)
// #define CTRL_SYM LT(SYM_ALT_L, OSM)

// custom shift keys
const custom_shift_key_t custom_shift_keys[] = {
  // {KC_COMM, KC_QUES}, // Shift , is ?
  // {KC_DOT , KC_EXLM}, // Shift . is !
  // {KC_DQUO, KC_QUOT }, // Shift " is '
  {KC_COLN, KC_SCLN},  // Shift : is ;
  {KC_UNDS, KC_EQL},   // Shift _ is -
  {KC_MINS, KC_PLUS},  // Shift - is +
  {KC_TILD, KC_GRV},   // Shift ~ is
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [ALPHA_L] = LAYOUT_split_3x6_3(
       KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_COLN, KC_BSPC,
      OS_CTRL,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                         KC_H,    KC_N,    KC_E,    KC_I,    KC_O,  KC_ENT,
      OS_SHFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_QUOT,  QK_REP,
                                          XXXXXXX, SPC_NAV,  KC_ESC,    OSM_SFT,  LA_SYM, XXXXXXX
  ),
  // [SYM_L] = LAYOUT_split_3x6_3(
  //      KC_ESC, KC_TILD, KC_LCBR, KC_LBRC, KC_LPRN, KC_LABK,                      KC_RABK, KC_RPRN, KC_RBRC, KC_RCBR, KC_UNDS,   LLOCK,
  //     KC_LCTL, KC_MINS, KC_ASTR,  KC_EQL, KC_UNDS,  KC_DLR,                      KC_CIRC, OS_SHFT, OS_CTRL,  OS_GUI,  OS_ALT, _______,
  //     KC_LSFT, KC_PLUS, KC_PIPE,   KC_AT, KC_SLSH, KC_PERC,                      KC_HASH, KC_BSLS, KC_DQUO, KC_QUOT,  KC_GRV, _______,
  //                                         _______, _______, _______,    _______, _______, _______
  // ),
  [NAV_L] = LAYOUT_split_3x6_3(
       KC_ESC,  CTRL_Q,  CTRL_W,  CTRL_F,  CTRL_T, XXXXXXX,                      KC_PGUP, KC_BSPC,   KC_UP,  KC_DEL,  KC_DEL,   LLOCK,
      KC_LCTL,  OS_ALT,  OS_GUI, OS_CTRL, OS_SHFT,  CTRL_D,                      KC_HOME, KC_LEFT, KC_DOWN,KC_RIGHT,  KC_END, _______,
      KC_LSFT, XXXXXXX,  MY_CUT, MY_COPY, MY_PSTE, XXXXXXX,                      KC_PGDN,  KC_ENT,  KC_TAB,  QK_REP,  KC_APP, _______,
                                          _______, _______, _______,    _______, _______, _______
  ),
  [SYM_L] = LAYOUT_split_3x6_3(
       KC_ESC, KC_SLSH,    KC_7,    KC_8,    KC_9,    KC_0,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   LLOCK,
      KC_LCTL, KC_LBRC,    KC_4,    KC_5,    KC_6, KC_RBRC,                      XXXXXXX, OS_SHFT, OS_CTRL,  OS_GUI,  OS_ALT, _______,
      KC_LSFT, KC_BSLS,    KC_1,    KC_2,    KC_3, KC_TILD,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                                          _______, KC_UNDS, KC_MINS,    _______, _______, _______
  ),
};


// ==============================================
// callum oneshot configuration
bool is_oneshot_cancel_key(uint16_t keycode) {
  switch (keycode) {
  case KC_ESC:
  // case LA_SYM:
  // case LA_NAV:
    return true;
  default:
    return false;
  }
}
bool is_oneshot_ignored_key(uint16_t keycode) {
  switch (keycode) {
  case SPC_NAV:
  case LA_SYM:
  case LA_NAV:
  case KC_LSFT:
  case KC_LCTL:
  case OS_SHFT:
  case OS_CTRL:
  case OS_ALT:
  case OS_GUI:
    return true;
  default:
    return false;
  }
}
oneshot_state os_sft_state = os_up_unqueued;
oneshot_state os_ctl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_gui_state = os_up_unqueued;


bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_custom_shift_keys(keycode, record)) {
    return false;
  }
  if (!process_layer_lock(keycode, record, LLOCK)) {
    return false;
  }

  update_oneshot(&os_sft_state, KC_LSFT, OS_SHFT, keycode, record);
  update_oneshot(&os_ctl_state, KC_LCTL, OS_CTRL, keycode, record);
  update_oneshot(&os_alt_state, KC_LALT, OS_ALT, keycode, record);
  update_oneshot(&os_gui_state, KC_LGUI, OS_GUI, keycode, record);

  switch (keycode) {
  case MY_COPY:
    // Copy = Ctrl+Ins
    if (record->event.pressed) { tap_code16(LCTL(KC_INS));}
    return false;
  case MY_CUT:
    // Cut = Shift+Del
    if (record->event.pressed) { tap_code16(LSFT(KC_DEL)); }
    return false;
  case MY_PSTE:
    // Paste = Shift+Ins
    if (record->event.pressed) { tap_code16(LSFT(KC_INS)); }
    return false;
  }

  return true;
}

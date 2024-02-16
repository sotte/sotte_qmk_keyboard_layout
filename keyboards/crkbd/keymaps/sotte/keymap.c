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
// #include "features/achordion.h"

// Home row mods - currently not used
// Left-hand home row mods
// #define A_MTG LGUI_T(KC_A)
// #define R_MTA LALT_T(KC_R)
// #define S_MTC LCTL_T(KC_S)
// #define T_MTS LSFT_T(KC_T)
// Right-hand home row mods
// #define N_MTS RSFT_T(KC_N)
// #define E_MTC RCTL_T(KC_E)
// #define I_MTA LALT_T(KC_I)
// #define O_MTG RGUI_T(KC_O)

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
  {KC_COMM, KC_QUES}, // Shift , is ?
  {KC_DOT , KC_EXLM}, // Shift . is !
  {KC_UNDS, KC_MINS}, // Shift _ is -
  {KC_COLN, KC_SCLN}, // Shift : is ;
  // {KC_MINS, KC_EQL }, // Shift - is =
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /// ### TL;DR: Features
  ///
  /// - 4 layers: `ALPHA` (colemak), `NAV`, `SYM`, `NUM`.
  /// - Only uses 4 thumb keys.
  /// - Callum style one-shot modifiers for most modifiers,.
  ///   but especially useful for the modifiers on he home row in the `NAV` layer.
  ///   `⌥⌘⌃⇧` or alt/gui/ctrl/shift or AGSC.
  /// - [CAPS WORD](https://docs.qmk.fm/#/feature_caps_word) when tapping shift twice.
  /// - [Repeat key](https://docs.qmk.fm/#/feature_repeat_key) on right pinky bottom row
  /// - Different characters on some shifted keys: `,?`, `.!`, `_-`, and `:;`.
  /// - Copy, Cut, Paste keys (via `NAV` layer) that work in and outside of terminals.
  ///
  /// ### Thumb cluster and layers
  ///
  /// There are 4 layers and you use two thumb switches to select them.
  ///
  /// ```text
  /// ALPHA: ...  ...
  /// NAV:   ...  .■.
  /// SYM:   .■.  ...
  /// NUM:   .■.  .■.
  /// ```
  ///
  /// ### Legend for special keys
  ///
  /// - `•`: noop
  /// - `␣N`: space on tab, NAV layer on hold
  /// - `♦.`: Repeat last key (or combo)
  /// - `♦A`: application (context menu)
  /// - `♦T`: Ctrl-t / my tmux prefix
  /// - `♦S`: SYM layer on press
  /// - `♦9`: NUM layer on press
  /// - `♦⌥`: ALT one shot
  /// - `♦⌘`: GUI one shot
  /// - `♦⌃`: CTRL one shot
  /// - `♦⇧`: SHFT one shot
  /// - `♦x`: cut (works in and outside of terminals)
  /// - `♦c`: copy (works in and outside of terminals)
  /// - `♦v`: paste (works in and outside of terminals)
  ///
  /// ### ALPHA layer
  ///
  /// ```text
  /// ES qQ wW fF pP gG       jJ lL uU yY :; ⌫
  /// ♦⌃ aA rR sS tT dD       hH nN eE iI oO ↵
  /// ♦⇧ zZ xX cC vV bB       kK mM ,? .! _- ♦.
  ///             •  ␣N ES  ♦⇧ ♦S •
  /// ```
  ///
  /// This is almost a standard colemak layout.
  /// It contains different non-alpha characters (and different shifted versions)
  /// as the shifted versions are more common ([ref](https://getreuer.info/posts/keyboards/symbol-layer/index.html#symbol-character-frequencies))
  /// and useful than the original ones:
  ///
  [ALPHA_L] = LAYOUT_split_3x6_3(
       KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_COLN, KC_BSPC,
      OS_CTRL,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                         KC_H,    KC_N,    KC_E,    KC_I,    KC_O,  KC_ENT,
      OS_SHFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_UNDS,  QK_REP,
                                          XXXXXXX, SPC_NAV,  KC_ESC,    OSM_SFT,  LA_SYM, XXXXXXX
  ),
  /// ### NAV layer
  ///
  /// ```text
  /// ES ⌃q ⌃w ⌃f ♦T •        ↥  ⌫  ↑  ⌦  ⌦  ⌫
  /// ⌃  ♦⌥ ♦⌘ ♦⌃ ♦⇧ ⌃d       ⇤  ←  ↓  →  ⇥  ↵
  /// ⇧  •  ♦x ♦c ♦v •        ↧  ↵  ⭾  ♦3 ♦A ♦.
  ///             •  ■  ES ♦⇧ ♦9 •
  /// ```
  ///
  /// A fairly simple nav layer.
  ///
  /// Note: you can use AGCS on the left side to create complex arrow movements/selections
  /// and delete behavior.
  /// AGCS are callum style one-shot keys and can be used on other layers as well.
  ///
  [NAV_L] = LAYOUT_split_3x6_3(
       KC_ESC,  CTRL_Q,  CTRL_W,  CTRL_F,  CTRL_T, XXXXXXX,                      KC_PGUP, KC_BSPC,   KC_UP,  KC_DEL,  KC_DEL, _______,
      KC_LCTL,  OS_ALT,  OS_GUI, OS_CTRL, OS_SHFT,  CTRL_D,                      KC_HOME, KC_LEFT, KC_DOWN,KC_RIGHT,  KC_END, _______,
      KC_LSFT, XXXXXXX,  MY_CUT, MY_COPY, MY_PSTE, XXXXXXX,                      KC_PGDN,  KC_ENT,  KC_TAB,  QK_REP,  KC_APP, _______,
                                          _______, _______, _______,    _______, _______, _______
  ),
  /// ### SYMBOL layer
  ///
  /// ```text
  /// ES .  /  *  #  |        \  '  [  ]  :  ⌫
  /// ⌃  !  -  +  =  ~        ^  "  (  )  $  ↵
  /// ⇧  ,  <  >  %  &        @  `  {  }  _  ♦.
  ///             •  ␣9 ES ♦⇧ ■  •
  /// ```
  ///
  /// Inspired by [getreuer](https://getreuer.info/posts/keyboards/symbol-layer/index.html)
  /// and adjusted slightly.
  ///
  /// - `^$` mirror `HOME` and `END` on the `NAV` layer and are useful for vim movements.
  /// - Additional `.,` just because they are handy.
  /// - The location of `./` is handy for navigating directories.
  /// - ``' ` "`` in one column to ease memoization.
  ///
  [SYM_L] = LAYOUT_split_3x6_3(
       KC_ESC,  KC_DOT, KC_SLSH, KC_ASTR, KC_HASH, KC_PIPE,                      KC_BSLS, KC_QUOT, KC_LBRC, KC_RBRC, KC_COLN, _______,
      KC_LCTL, KC_EXLM, KC_MINS, KC_PLUS, KC_EQL,  KC_TILD,                      KC_CIRC,  KC_DQT, KC_LPRN, KC_RPRN,  KC_DLR, _______,
      KC_LSFT, KC_COMM, KC_LABK, KC_RABK, KC_PERC, KC_AMPR,                        KC_AT,  KC_GRV, KC_LCBR, KC_RCBR, KC_UNDS, _______,
                                          _______, _______, _______,    _______, _______, _______
  ),
  /// ### NUM layer
  ///
  /// ```text
  /// ES .  /  *  #  |        .  7  8  9  :  ⌫
  /// ⌃  !  -  +  =  ~        0  4  5  6  0  ↵
  /// ⇧  ,  <  >  %  &        ,  1  2  3  _  ♦.
  ///             •  ■  •  •  ■  •
  /// ```
  ///
  /// The right side is the real `NUM` layer.
  /// The left side mirrors the keys from the `SYM` layer which are quite useful for entering formulas.
  ///
  /// Issues:
  ///
  /// - `()` are not as easy to use as I would like.
  ///
  [NUM_L] = LAYOUT_split_3x6_3(
       KC_ESC,  KC_DOT, KC_SLSH, KC_ASTR, KC_HASH, KC_PIPE,                       KC_DOT,    KC_7,    KC_8,    KC_9, KC_COLN, _______,
      KC_LCTL, KC_EXLM, KC_MINS, KC_PLUS, KC_EQL,  KC_TILD,                         KC_0,    KC_4,    KC_5,    KC_6,    KC_0, _______,
      KC_LSFT, KC_COMM, KC_LABK, KC_RABK, KC_PERC, KC_AMPR,                      KC_COMM,    KC_1,    KC_2,    KC_3, KC_UNDS, _______,
                                          _______, _______, _______,    _______, _______, _______
  ),
  // ==============================================
  // ### WIP layers
  // ### NUM layer
  //
  // NOTE: WIP this symbol layer is being oberwritten by the next symbol layer.
  //
  // ```text
  // ES ~  -  +  9  •        •  8  *  /  : ♦1
  // ⌃  7  5  3  1  =        •  0  2  4  6 ♦2
  // ⇧  •  {  [  (  <        >  )  ]  }  _ •
  //             •  ■  •  •  ■  •
  // ```
  //
  // I'm describing NUM and SYM together here, because they go together really.
  //
  // The home row contains the numbers.
  // The strong fingers get the numbers which are more frequent.
  // 0123 are the most common ones,
  // [see details](https://getreuer.info/posts/keyboards/symbol-layer/index.html#my-symbol-layer).
  // The left has the uneven numbers, the right the even.
  //
  // Arithmetic operators are on strong fingers on the top row:
  // `-+` on the left, `*/` on the right.
  //
  // The bottom row contains all the different kinds of parenthesis.
  // Opening on the left, closing on the right.
  //
  // Some useful keys from the alpha layer bleed through: `:_`
  //
  // [NUM_L] = LAYOUT_split_3x6_3(
  //      KC_ESC, KC_TILD, KC_MINS, KC_PLUS,    KC_9, KC_PIPE,                     XXXXXXX,    KC_8, KC_ASTR, KC_SLSH, KC_COLN, XXXXXXX,
  //     KC_LCTL,    KC_7,    KC_5,    KC_3,    KC_1,  KC_EQL,                     XXXXXXX,    KC_0,    KC_2,    KC_4,    KC_6, XXXXXXX,
  //     KC_LSFT, XXXXXXX, KC_LCBR, KC_LBRC, KC_LPRN, KC_LABK,                     KC_RABK, KC_RPRN, KC_RBRC, KC_RCBR, KC_UNDS, XXXXXXX,
  //                                         XXXXXXX, _______, _______,   _______, _______, XXXXXXX
  // ),
  //
  //
  // ### SYMBOL layer
  //
  // NOTE: WIP this symbol layer is being oberwritten by the next symbol layer.
  //
  // ```text
  // ES ~  -  +  \  |        `  `  *  /  : ♦1
  // ⌃  &  %  #  !  =        '  "  @  $  ^ ♦2
  // ⇧  •  {  [  (  <        >  )  ]  }  _ •
  //             •  ␣  •  ■  •  •
  // ```
  //
  // Like the NUM layer, but the SYM layer
  //
  // - contains the symbols of the shifted numbers,
  // - contains the rest of the symbols.
  // [SYM_L] = LAYOUT_split_3x6_3(
  //      KC_ESC, KC_TILD, KC_MINS, KC_PLUS, KC_BSLS, KC_PIPE,                     KC_GRV,  KC_GRV, KC_ASTR, KC_SLSH, KC_COLN, XXXXXXX,
  //     KC_LCTL, KC_AMPR, KC_PERC, KC_HASH, KC_EXLM,  KC_EQL,                    KC_QUOT,  KC_DQT,   KC_AT,  KC_DLR, KC_CIRC, XXXXXXX,
  //     KC_LSFT, XXXXXXX, KC_LCBR, KC_LBRC, KC_LPRN, KC_LABK,                    KC_RABK, KC_RPRN, KC_RBRC, KC_RCBR, KC_UNDS, XXXXXXX,
  //                                         XXXXXXX,  KC_SPC, XXXXXXX,  _______, _______, XXXXXXX
  // ),
  //
  // ### WIP ALT SYMBOL layer
  // ```text
  // ~  `  '  "  !        .  .  .  .  :
  // \  {  [  (  [        .  S  C  A  G
  // |  }  ]  )  ]        .  #  <  >  _
  //          .  /  =  ■  .  .
  // ```
  // GACS are one-shot keys.
  //
  // [SYM_ALT_L] = LAYOUT_split_3x6_3(
  //      KC_ESC, KC_TILD,  KC_GRV, KC_QUOT, KC_DQUO, KC_EXLM,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  //     KC_LCTL, KC_BSLS, KC_LCBR, KC_LBRC, KC_LPRN, KC_LBRC,                      XXXXXXX, OSM_SFT, OSM_CTL, OSM_ALT, OSM_GUI, XXXXXXX,
  //     KC_LSFT, KC_PIPE, KC_RCBR, KC_RBRC, KC_RPRN, KC_RBRC,                      XXXXXXX, KC_HASH, KC_LABK, KC_RABK, KC_UNDS, XXXXXXX,
  //                                         _______, KC_SLSH,  KC_EQL,    _______, _______, XXXXXXX
  // ),
  //
  // ### WIP ALT NUM layer
  // ```text
  // 0  7& 8* 9( +        .  .  .  .  :
  // 0  4$ 5% 6^ -        .  S  C  A  G
  // 0  1! 2@ 3# *        .  .  ,  .  _
  //          .  /  =  .  ■  .
  // ```
  //
  // [NUM_ALT_L] = LAYOUT_split_3x6_3(
  //      KC_ESC,    KC_0,    KC_7,    KC_8,    KC_9, KC_PLUS,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_COLN, XXXXXXX,
  //     KC_LCTL,    KC_0,    KC_4,    KC_5,    KC_6, KC_MINS,                      XXXXXXX, OSM_SFT, OSM_CTL, OSM_ALT, OSM_GUI, XXXXXXX,
  //     KC_LSFT,    KC_0,    KC_1,    KC_2,    KC_3, KC_ASTR,                      XXXXXXX, XXXXXXX, KC_COMM,  KC_DOT, KC_UNDS, XXXXXXX,
  //                                         _______, _______, _______,    XXXXXXX, _______, _______
  // ),
  //
  // ### WIP ALT MOUSE layer
  // ```text
  // .  .  .  .  .        ↥  ⇤  ↑  ⇥  .
  // G  A  C  S  .        ↧  ←  ↓  →  .
  // .  .  .  .  .        .  .  .  .  .
  //          .  .  ■  M2 M1 M3
  // ```
  // Very similar to the NAV layer, just for the mouse.
  //
  // GACS are one-shot keys.
  //
  // TODO: improve the mouse settings
  // https://github.com/qmk/qmk_firmware/blob/master/docs/feature_mouse_keys.md#configuring-mouse-keys
  //
  // [MOUSE_L] = LAYOUT_split_3x6_3(
  //      KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, XXXXXXX, XXXXXXX,
  //     KC_LCTL, OSM_GUI, OSM_ALT, OSM_CTL, OSM_SFT, XXXXXXX,                      KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,
  //     KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //                                         XXXXXXX, XXXXXXX, _______,    KC_BTN2, KC_BTN1, KC_BTN3
  // ),
  //
  // ### WIP ALT FUNC layer
  // ```text
  // . F7 F8 F9 F12      .  .  .  .  :
  // . F4 F5 F6 F11      .  S  C  A  G
  // . F1 F2 F3 F10      .  .  ,  .  _
  //          .  .  .  .  .  ■
  // ```
  //
  // [FUNC_L] = LAYOUT_split_3x6_3(
  //      KC_TAB, XXXXXXX,   KC_F7,   KC_F8,   KC_F9,  KC_F12,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_COLN, XXXXXXX,
  //     KC_LCTL, XXXXXXX,   KC_F4,   KC_F5,   KC_F6,  KC_F11,                      XXXXXXX, OSM_SFT, OSM_CTL, OSM_ALT, OSM_GUI, XXXXXXX,
  //     KC_LSFT, XXXXXXX,   KC_F1,   KC_F3,   KC_F3,  KC_F10,                      XXXXXXX, KC_PSCR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //                                         XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, _______
  // ),
  //
  // ### WIP MEDIA layer
  // TODO implement me
  //
};

/// ### Symbols legend
///
/// ```text
/// ■ pressed thumb key
/// • noop
/// ↵ enter
/// ⌫ backspace
/// ⌦ del
/// ⭾ tab
/// ↥↧ page up/down
/// ⇤⇥ home/end
/// ←↑↓→ arrows
/// ⌥⌘⇧⌃ alt/gui/shift/ctrl also AGSC
/// ␣ space
/// ES ESC
/// Cc Ctrl+c, Cv Ctrl+v
/// ♦1 special feature 1; explained in the doc
/// ```
///



// ==============================================
// callum oneshot configuration
bool is_oneshot_cancel_key(uint16_t keycode) {
  switch (keycode) {
  case KC_ESC:
  case LA_SYM:
  case LA_NAV:
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


layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, SYM_L, NAV_L, NUM_L);
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_custom_shift_keys(keycode, record)) {
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

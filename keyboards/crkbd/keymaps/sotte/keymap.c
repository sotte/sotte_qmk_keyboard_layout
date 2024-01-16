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
// #include "features/achordion.h"

enum layer_names {
  ALPHA_L,
  NAV_L,
  SYM_L,
  NUM_L,
  // maybe later
  SYM_ALT_L,
  NUM_ALT_L,
  NUM_ALT2_L,
  MOUSE_L,
  FUNC_L,
};

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
//
// This can be the homerow if you use home row mods
// MO(NAV_L),   A_MTG,   R_MTA,   S_MTC,   T_MTS,    KC_D,                         KC_H,   N_MTS,   E_MTC,   I_MTA,   O_MTG, KC_QUOT,


// aliases - mostly to keep the format/style consistent
#define OSM_SFT OSM(MOD_LSFT)
#define OSM_CTL OSM(MOD_LCTL)
#define OSM_GUI OSM(MOD_LGUI)
#define OSM_ALT OSM(MOD_LALT)
#define CTRL_C  LCTL(KC_C)
#define CTRL_D  LCTL(KC_D)
#define CTRL_F  LCTL(KC_F)
#define CTRL_Q  LCTL(KC_Q)
#define CTRL_T  LCTL(KC_T)
#define CTRL_V  LCTL(KC_V)
#define CTRL_W  LCTL(KC_W)

// Layer tabs
#define BSP_SYM  LT(SYM_L, KC_BSPC)
#define DEL_FUNC LT(FUNC_L, KC_DEL)
#define ENT_NUM  LT(NUM_ALT_L, KC_ENT)
#define ESC_NAV  LT(NAV_L, KC_ESC)
#define ESC_NUM  LT(NUM_L, KC_ESC)
#define ESC_SYM  LT(SYM_L, KC_ESC)
#define SPC_NAV  LT(NAV_L, KC_SPC)
#define SPC_SYM  LT(SYM_ALT_L, KC_SPC)
#define SPC_NUM  LT(NUM_ALT_L, KC_SPC)
#define TAB_MOU  LT(MOUSE_L, KC_TAB)
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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /// ### Thumb cluster and layers
  ///
  /// I actually only use middle and inner thumb keys of the thumb cluster.
  ///
  /// ```text
  /// NAV: ...  .■.
  /// SYM: .■.  ...
  /// NUM: .■.  .■.
  /// ```
  ///
  /// ### ALPHA layer
  ///
  /// ```text
  /// ES qQ wW fF pP gG       jJ lL uU yY :; ♦1
  /// ⌃  aA rR sS tT dD       hH nN eE iI oO ♦3
  /// ♦⇧ zZ xX cC vV bB       kK mM ,? .! _- ♦2
  ///             •  ␣  ␛  ♦⇧ ⌫  •
  /// ```
  ///
  /// This is a almost standard colemak layout.
  /// It contains different non-alpha characters (and different shifted versions)
  /// as they are quite common ([ref](https://getreuer.info/posts/keyboards/symbol-layer/index.html#symbol-character-frequencies)):
  /// `,?`, `.!`, `_-`, and `:;`.
  ///
  /// Legend:
  ///
  /// - ♦1: Switch to ALPHA layer.
  /// - ♦2: Switch to NAV layer. Sometimes I just want to use the cursors for a while.
  /// - ♦3: Repeat last key (combo)
  /// - ♦⇧: One-shot shift
  [ALPHA_L] = LAYOUT_split_3x6_3(
       KC_ESC,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_COLN, TO(ALPHA_L),
      KC_LCTL,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                         KC_H,    KC_N,    KC_E,    KC_I,    KC_O, QK_REP,
      OSM_SFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_UNDS, TO(NAV_L),
                                          XXXXXXX, SPC_NAV, ESC_NUM,    OSM_SFT, BSP_SYM, XXXXXXX
  ),
  ///
  /// ### NAV layer
  ///
  /// ```text
  /// ES Cq Cw Cf ♦0 •        ↥  ⌫  ↑  ⌦  ⌦ ♦1
  /// ⌃  A  G  S  C  Cd       ⇤  ←  ↓  →  ⇥ ♦3
  /// ⇧  •  Cx Cc Cv •        ↧  ↵  ⭾  ♦3 • ♦2
  ///             •  ■  •  ⌦  ⌫  •
  /// ```
  ///
  /// A fairly simple nav layer.
  ///
  /// Note: you can use AGSC on the left side to create complex arrow movements/selections
  /// and delete behavior.
  /// AGSC are one-shot keys and can be used on other layers as well.
  ///
  /// Legend:
  ///
  /// - ♦1: Switch to ALPHA layer.
  /// - ♦2: Switch to NAV layer. Sometimes I just want to use the cursors for a while.
  /// - ♦3: Repeat last key (combo)
  /// - ♦4: Print screen
  [NAV_L] = LAYOUT_split_3x6_3(
       KC_ESC,  CTRL_Q,  CTRL_W,  CTRL_F, KC_PSCR, XXXXXXX,                      KC_PGUP, KC_BSPC,   KC_UP,  KC_DEL,  KC_DEL, TO(ALPHA_L),
      KC_LCTL, OSM_ALT, OSM_GUI, OSM_SFT, OSM_CTL,  CTRL_D,                      XXXXXXX, KC_LEFT, KC_DOWN,KC_RIGHT, XXXXXXX, QK_REP,
      KC_LSFT, XXXXXXX,  KC_CUT,  CTRL_C,  CTRL_V, XXXXXXX,                      KC_PGDN,  KC_ENT,  KC_TAB,  QK_REP, XXXXXXX, TO(NAV_L),
                                          _______, _______, XXXXXXX,     KC_DEL, KC_BSPC, XXXXXXX
  ),
  ///
  /// ### NUM layer
  ///
  /// NOTE: WIP this symbol layer is being oberwritten by the next symbol layer.
  ///
  /// ```text
  /// ES ~  -  +  9  •        •  8  *  /  : ♦1
  /// ⌃  7  5  3  1  =        •  0  2  4  6 ♦2
  /// ⇧  •  {  [  (  <        >  )  ]  }  _ •
  ///             •  ■  •  •  ■  •
  /// ```
  ///
  /// I'm describing NUM and SYM together here, because they go together really.
  ///
  /// The home row contains the numbers.
  /// The strong fingers get the numbers which are more frequent.
  /// 0123 are the most common ones,
  /// [see details](https://getreuer.info/posts/keyboards/symbol-layer/index.html#my-symbol-layer).
  /// The left has the uneven numbers, the right the even.
  ///
  /// Arithmetic operators are on strong fingers on the top row:
  /// `-+` on the left, `*/` on the right.
  ///
  /// The bottom row contains all the different kinds of parenthesis.
  /// Opening on the left, closing on the right.
  ///
  /// Some useful keys from the alpha layer bleed through: `:_`
  ///
  /// TODO: what should I do with the empyt keys?
  [NUM_L] = LAYOUT_split_3x6_3(
       KC_ESC, KC_TILD, KC_MINS, KC_PLUS,    KC_9, KC_PIPE,                     XXXXXXX,    KC_8, KC_ASTR, KC_SLSH, KC_COLN, XXXXXXX,
      KC_LCTL,    KC_7,    KC_5,    KC_3,    KC_1,  KC_EQL,                     XXXXXXX,    KC_0,    KC_2,    KC_4,    KC_6, XXXXXXX,
      KC_LSFT, XXXXXXX, KC_LCBR, KC_LBRC, KC_LPRN, KC_LABK,                     KC_RABK, KC_RPRN, KC_RBRC, KC_RCBR, KC_UNDS, XXXXXXX,
                                          XXXXXXX, _______, _______,   _______, _______, XXXXXXX
  ),
  ///
  /// ### NUM layer
  ///
  /// ```text
  /// ES •  /  *  #  |        .  7  8  9  : •
  /// ⌃  !  -  +  =  ~        0  4  5  6  0 •
  /// ⇧  •  <  >  %  &        ,  1  2  3  _ •
  ///             •  •  ■  (  )  •
  /// ```
  ///
  /// The right side is the real NUM layer.
  /// The left side is the symbol layer really,
  /// but is should making working with the num layer comfortable.
  ///
  [NUM_L] = LAYOUT_split_3x6_3(
       KC_ESC, XXXXXXX, KC_SLSH, KC_ASTR, KC_HASH, KC_PIPE,                    KC_COMM,    KC_7,    KC_8,    KC_9, KC_COLN, XXXXXXX,
      KC_LCTL, KC_EXLM, KC_MINS, KC_PLUS, KC_EQL,  KC_TILD,                       KC_0,    KC_4,    KC_5,    KC_8,    KC_0, XXXXXXX,
      KC_LSFT, XXXXXXX, KC_LABK, KC_RABK, KC_PERC, KC_AMPR,                     KC_DOT,    KC_1,    KC_2,    KC_3, KC_UNDS, XXXXXXX,
                                          XXXXXXX, XXXXXXX, _______,  KC_LPRN, KC_RPRN, XXXXXXX
  ),
  ///
  /// ### SYMBOL layer
  ///
  /// NOTE: WIP this symbol layer is being oberwritten by the next symbol layer.
  ///
  /// ```text
  /// ES ~  -  +  \  |        `  `  *  /  : ♦1
  /// ⌃  &  %  #  !  =        '  "  @  $  ^ ♦2
  /// ⇧  •  {  [  (  <        >  )  ]  }  _ •
  ///             •  •  •  ■  •  •
  /// ```
  ///
  /// Like the NUM layer, but the SYM layer
  ///
  /// - contains the symbols of the shifted numbers,
  /// - contains the rest of the symbols.
  [SYM_L] = LAYOUT_split_3x6_3(
       KC_ESC, KC_TILD, KC_MINS, KC_PLUS, KC_BSLS, KC_PIPE,                       KC_GRV,  KC_GRV, KC_ASTR, KC_SLSH, KC_COLN, XXXXXXX,
      KC_LCTL, KC_AMPR, KC_PERC, KC_HASH, KC_EXLM,  KC_EQL,                      KC_QUOT,  KC_DQT,   KC_AT,  KC_DLR, KC_CIRC, XXXXXXX,
      KC_LSFT, XXXXXXX, KC_LCBR, KC_LBRC, KC_LPRN, KC_LABK,                      KC_RABK, KC_RPRN, KC_RBRC, KC_RCBR, KC_UNDS, XXXXXXX,
                                          XXXXXXX,MO(NUM_L), XXXXXXX,  _______, _______, XXXXXXX
  ),
  ///
  /// ### SYMBOL layer
  ///
  /// ```text
  /// ES •  /  *  #  |        \  '  [  ]  : •
  /// ⌃  !  -  +  =  ~        ^  "  (  )  $ •
  /// ⇧  •  <  >  %  &        @  `  {  }  _ •
  ///             •  •  •  ■  •  •
  /// ```
  ///
  /// Inspired by getreuer:
  /// https://getreuer.info/posts/keyboards/symbol-layer/index.html
  ///
  [SYM_L] = LAYOUT_split_3x6_3(
       KC_ESC, XXXXXXX, KC_SLSH, KC_ASTR, KC_HASH, KC_PIPE,                     KC_BSLS, KC_QUOT, KC_LBRC, KC_RBRC, KC_COLN, XXXXXXX,
      KC_LCTL, KC_EXLM, KC_MINS, KC_PLUS, KC_EQL,  KC_TILD,                     KC_CIRC,  KC_DQT, KC_LPRN, KC_RPRN,  KC_DLR, XXXXXXX,
      KC_LSFT, XXXXXXX, KC_LABK, KC_RABK, KC_PERC, KC_AMPR,                       KC_AT,  KC_GRV, KC_LCBR, KC_RCBR, KC_UNDS, XXXXXXX,
                                          XXXXXXX,MO(NUM_L), XXXXXXX,  _______, _______, XXXXXXX
  ),
  // ==============================================
  // ### WIP layers
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

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  // if (!process_achordion(keycode, record)) { return false; }
  if (!process_custom_shift_keys(keycode, record)) { return false; }
  // Your macros ...
  return true;
}

// void matrix_scan_user(void) {
//   achordion_task();
// }

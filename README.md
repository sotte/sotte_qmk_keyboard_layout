# `sotte` keyboard layouts

This repo contains my keyboard layouts.
It is a qmk_userspace repo, see [README_qmk_userspace.md](README_qmk_userspace.md) for details.

## Corne with colemak layout

I use colemak with some modifications.
It is inspired by miryoku, getreuer, callum, seniply, and others.
See references below.

### Hardware

Corne V3 hotswap with Frood RP2040 V8 MCU, akko ocean blue switches, and random keycaps.
I got the board from [here](https://42keebs.eu/shop/kits/pro-micro-based/corne-cherry-v3-hotswap-split-ergo-40-kit/).

<!-- REPLACE_MARKER_START -->
### Thumb cluster and layers

```text
NAV: ...  .■.
SYM: .■.  ...
NUM: .■.  .■.
```

### Legend for special keys

- ♦.: Repeat last key (or combo)
- ♦⇧: One-shot shift
- ␣N: space on press, NAV layer on hold
- ♦T: Ctrl-t / my tmux prefix
- ♦S: SYM layer on press
- ♦9: NUM layer on press

### ALPHA layer

```text
ES qQ wW fF pP gG       jJ lL uU yY :; ⌫
⌃  aA rR sS tT dD       hH nN eE iI oO ↵
♦⇧ zZ xX cC vV bB       kK mM ,? .! _- ♦.
            •  ␣N ↵  ♦⇧ ♦S •
```

This is a almost standard colemak layout.
It contains different non-alpha characters (and different shifted versions)
as they are quite common ([ref](https://getreuer.info/posts/keyboards/symbol-layer/index.html#symbol-character-frequencies)):
`,?`, `.!`, `_-`, and `:;`.

### NAV layer

```text
ES Cq Cw Cf ♦T •        ↥  ⌫  ↑  ⌦  ⌦ ⌫
⌃  A  G  C  S  Cd       ⇤  ←  ↓  →  ⇥ ↵
⇧  •  Cx Cc Cv •        ↧  ↵  ⭾  ♦3 • ♦3
            •  ■  ↵  ♦⇧ ♦9 •
```

A fairly simple nav layer.

Note: you can use AGSC on the left side to create complex arrow movements/selections
and delete behavior.
AGCS are one-shot keys and can be used on other layers as well.

### SYMBOL layer

```text
ES .  /  *  #  |        \  '  [  ]  : •
⌃  !  -  +  =  ~        ^  "  (  )  $ •
⇧  ,  <  >  %  &        @  `  {  }  _ •
            •  ␣9 ↵  ♦⇧ ■  •
```

Inspired by getreuer:
https://getreuer.info/posts/keyboards/symbol-layer/index.html

### NUM layer

```text
ES .  /  *  #  |        .  7  8  9  : •
⌃  !  -  +  =  ~        0  4  5  6  0 •
⇧  ,  <  >  %  &        ,  1  2  3  _ •
            •  ■  •  •  ■  •
```

The right side is the real NUM layer.
The left side is the symbol layer really,
but is should making working with the num layer comfortable.

### Symbols legend

```text
■ pressed thumb key
• noop
↵ enter
⌫ backspace
⌦ del
⭾ tab
↥↧ page up/down
⇤⇥ home/end
←↑↓→ arrows
⌥⌘⇧⌃ alt/gui/shift/ctrl also AGSC
␣ space
ES ESC
Cc Ctrl+c, Cv Ctrl+v
♦1 special feature 1; explained in the doc
```

<!-- REPLACE_MARKER_END -->

## Usage

```bash
make compile
make flash

# helper to update the readme from the source code
# this is called automatically via make
./bin/update_readme.py
```

## References

- [Miryoku](https://github.com/manna-harbour/miryoku)
- [seniply](https://stevep99.github.io/seniply/)
- [callum](https://keymapdb.com/keymaps/callum_oakley/)
- [Designing a symbol layer](https://getreuer.info/posts/keyboards/symbol-layer/index.html)
- https://getreuer.info/posts/keyboards/custom-shift-keys/index.html
- https://getreuer.info/posts/keyboards/achordion/index.html
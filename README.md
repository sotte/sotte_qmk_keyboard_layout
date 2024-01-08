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
⌘⌥⌃⇧ gui/alt/ctrl/shift also GACS
␣ space
ES ESC
Cc Ctrl+c, Cv Ctrl+v
♦1 special feature 1; explained in the doc
```

### Thumb cluster and layers

I actually only use middle and inner thumb keys of the thumb cluster.

```text
NAV: ...  .■.
SYM: .■.  ...
NUM: .■.  .■.
```

### ALPHA layer

```text
ES qQ wW fF pP gG       jJ lL uU yY :; ♦1
⌃  aA rR sS tT dD       hH nN eE iI oO ♦2
♦⇧ zZ xX cC vV bB       kK mM ,? .! _- •
            •  ␣  ␛  ⇧  ⌫  •
```

This is a colemak layout.
But it contains different non-alpha characters and different shifted versions.
`.,_;!?` are quite common ([ref](https://getreuer.info/posts/keyboards/symbol-layer/index.html#symbol-character-frequencies)).

♦1: Switch to ALPHA layer.
♦2: Switch to NAV layer. Sometimes I just want to use the cursors for a while.
♦⇧: One-shot shift

### NAV layer

```text
ES Cq Cw Cf  •  •        ↥  ⇤  ↑  ⇥  ⌦ ♦1
⌃  G  A  C  S  Cd       ⌦  ←  ↓  →  ⌫ ♦2
⇧  •  Cx Cc Cv •        ↧  ↵  ⭾  •  • •
            •  ■  •  ⌫  •  •
```

A fairly simple nav layer.

Note: you can use GACS on the left side to create complex arrow movements/selections
and delete behavior.
GACS are one-shot keys and can be used on other layers as well.

TODO: WIP cut, copy, paste are on the left side. make this work in terminals too.

♦1: Switch to ALPHA layer.
♦2: Switch to NAV layer. Sometimes I just want to use the cursors for a while.

### NUM layer

```text
ES ~  -  +  9  •        •  8  *  /  : ♦1
⌃  7  5  3  1  =        •  0  2  4  6 ♦2
⇧  •  {  [  (  <        >  )  ]  }  _ •
            •  ■  •  •  ■  •
```

I'm describing NUM and SYM together here, because they go together really.

The home row contains the numbers.
The strong fingers get the numbers which are more frequent.
0123 are the most common ones,
[see details](https://getreuer.info/posts/keyboards/symbol-layer/index.html#my-symbol-layer).
The left has the uneven numbers, the right the even.

Arithmetic operators are on strong fingers on the top row:
`-+` on the left, `*/` on the right.

The bottom row contains all the different kinds of parenthesis.
Opening on the left, closing on the right.

Some useful keys from the alpha layer bleed through: `:_`

TODO: what should I do with the empyt keys?

### SYMBOL layer

```text
ES ~  -  +  \  |        `  `  *  /  : ♦1
⌃  &  %  #  !  =        '  "  @  $  ^ ♦2
⇧  •  {  [  (  <        >  )  ]  }  _ •
            •  •  •  ■  •  •
```

Like the NUM layer, but the SYM layer

- contains the symbols of the shifted numbers,
- contains the rest of the symbols.
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
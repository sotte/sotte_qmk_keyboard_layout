# SRC += features/achordion.c
SRC += features/custom_shift_keys.c
SRC += features/oneshot.c

CONVERT_TO=promicro_rp2040
MOUSEKEY_ENABLE = yes

# https://docs.qmk.fm/#/feature_caps_word
CAPS_WORD_ENABLE = yes

# https://docs.qmk.fm/#/feature_repeat_key
REPEAT_KEY_ENABLE = yes

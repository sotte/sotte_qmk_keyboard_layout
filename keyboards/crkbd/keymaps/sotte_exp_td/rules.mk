# https://getreuer.info/posts/keyboards/achordion/index.html
# SRC += features/achordion.c

# https://getreuer.info/posts/keyboards/custom-shift-keys/index.html
SRC += features/custom_shift_keys.c

# https://getreuer.info/posts/keyboards/layer-lock/index.html
SRC += features/layer_lock.c

SRC += features/oneshot.c

MOUSEKEY_ENABLE = yes

# https://docs.qmk.fm/#/feature_caps_word
CAPS_WORD_ENABLE = yes

# https://docs.qmk.fm/#/feature_repeat_key
REPEAT_KEY_ENABLE = yes

CONVERT_TO=promicro_rp2040

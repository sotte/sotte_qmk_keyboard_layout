# https://getreuer.info/posts/keyboards/custom-shift-keys/index.html
SRC += features/custom_shift_keys.c

# https://getreuer.info/posts/keyboards/layer-lock/index.html
SRC += features/layer_lock.c

MOUSEKEY_ENABLE = yes

# https://docs.qmk.fm/#/feature_caps_word
CAPS_WORD_ENABLE = yes

# https://docs.qmk.fm/#/feature_repeat_key
REPEAT_KEY_ENABLE = yes

CONVERT_TO=rp2040_ce

# DEFERRED_EXEC_ENABLE = yes

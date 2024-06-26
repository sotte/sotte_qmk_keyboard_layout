.SILENT:

MAKEFLAGS += --no-print-directory


README.md: keyboards/crkbd/keymaps/sotte/keymap.c
	./bin/update_readme.py

.PHONY: compile
compile: README.md
	make crkbd:sotte

.PHONY: flash
flash: README.md
	make crkbd:sotte:flash

.PHONY: flashc
flashc: README.md
	make crkbd:sotte_callum:flash

.PHONY: flashs
flashs: README.md
	make crkbd:sotte_simple:flash

.PHONY: flashhrm
flashhrm: README.md
	make crkbd:sotte_simple_hrm:flash

.PHONY: flashseniply
flashseniply: README.md
	make crkbd:sotte_seniply_like:flash

QMK_USERSPACE := $(patsubst %/,%,$(dir $(shell realpath "$(lastword $(MAKEFILE_LIST))")))
ifeq ($(QMK_USERSPACE),)
    QMK_USERSPACE := $(shell pwd)
endif

QMK_FIRMWARE_ROOT = $(shell qmk config -ro user.qmk_home | cut -d= -f2 | sed -e 's@^None$$@@g')
ifeq ($(QMK_FIRMWARE_ROOT),)
    $(error Cannot determine qmk_firmware location. `qmk config -ro user.qmk_home` is not set)
endif

%:
	+$(MAKE) -C $(QMK_FIRMWARE_ROOT) $(MAKECMDGOALS) QMK_USERSPACE=$(QMK_USERSPACE)

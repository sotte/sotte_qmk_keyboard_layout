.DEFAULT_GOAL:=help
SHELL:=/usr/bin/env bash
MAKEFLAGS += --no-print-directory


################################################################################
##@ LAYOUTS

achordion: bootstrap ## Compile achordion
	cd ~/coding/qmk_firmware/ && \
		bash util/docker_build.sh crkbd:sotte_exp_achordion
	xdg-open .
	@echo "Copy&Paste crkbd_rev1_sotte_exp_achordion.uf2 to your mounted keyboard"

# .PHONY: compile
# compile: README.md
# 	make crkbd:sotte
#
# .PHONY: flash
# flash: README.md
# 	make crkbd:sotte:flash
#
# .PHONY: flashc
# flashc: README.md
# 	make crkbd:sotte_callum:flash
#
# .PHONY: flashs
# flashs: README.md
# 	make crkbd:sotte_simple:flash
#
# .PHONY: flashhrm
# flashhrm: README.md
# 	make crkbd:sotte_simple_hrm:flash
#
# .PHONY: flashseniply
# flashseniply: README.md
# 	make crkbd:sotte_seniply_like:flash

################################################################################
##@ Helpers
.PHONY: bootstrap
bootstrap: ~/coding/qmk_firmware .venv/bin/qmk ## Bootstrap the development environment: clone qmk, install deps, configure

.PHONY: help
help:  ## Display this help
	@awk 'BEGIN {FS = ":.*##"; printf "\nUsage:\n  make \033[36m\033[0m\n"} /^[a-zA-Z_-]+:.*?##/ { printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2 } /^##@/ { printf "\n\033[1m%s\033[0m\n", substr($$0, 5) } ' $(MAKEFILE_LIST)

################################################################################
# Random targets
README.md: keyboards/crkbd/keymaps/sotte/keymap.c
	./bin/update_readme.py

~/coding/qmk_firmware:
	@echo "Cloning QMK firmware..."
	git clone git@github.com:qmk/qmk_firmware.git ~/coding/qmk_firmware

.venv:
	@echo "Creating Python virtual environment..."
	python3.13 -m venv .venv

.venv/bin/qmk: .venv
	@echo "Installing QMK..."
	.venv/bin/pip install qmk
	@echo "Configuring QMK overlay directory..."
	.venv/bin/qmk config user.overlay_dir=$(PWD)

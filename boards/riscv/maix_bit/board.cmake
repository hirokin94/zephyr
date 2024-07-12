# SPDX-License-Identifier: Apache-2.0

board_runner_args(openocd --cmd-pre-init "source [find target/k210.cfg]")

board_runner_args(openocd --cmd-load "k210-load")
board_runner_args(openocd --cmd-reset-halt "k210-reset-halt")
board_runner_args(openocd --cmd-post-verify "k210-post-verify")

include(${ZEPHYR_BASE}/boards/common/openocd.board.cmake)
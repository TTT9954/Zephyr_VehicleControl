#!/usr/bin/env bash
set -euo pipefail
BOARD="${1:-native_sim}"
west build -b "$BOARD" -d build . -p always

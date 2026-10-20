#!/usr/bin/env bash
set -euo pipefail
west twister -T tests -p native_sim --inline-logs

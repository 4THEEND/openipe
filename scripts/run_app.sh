#!/bin/bash

# Build the Verilator simulator and the given IPE application, then run the
# application on the simulator (loading the IPE bootcode as firmware).
#
# Usage: ./scripts/run_app.sh <app-name>
# where <app-name> is a directory under app/ (e.g. ipe-hello, ipe-hmac).
#
# Exits non-zero if the simulator fails or the application reports a failure.
# Note: the simulator halts with success on CPUOFF even when an ASSERT fails,
# so we additionally scan the output for a "FAIL" line.

set -e

APP="${1:?usage: $0 <app-name>}"

SIM_DIR=/openipe/core/sim/verilator

make -C "$SIM_DIR"
make -C "/openipe/app/$APP"

# Stream output live (line-buffered) while also capturing it for the FAIL check.
log=$(mktemp)
stdbuf -oL -eL "$SIM_DIR/build/ipe-sim" \
    --firmware "$SIM_DIR/build/bootcode.elf" \
    "/openipe/app/$APP/$APP.elf" 2>&1 | tee "$log"
ret=${PIPESTATUS[0]}

if [ "$ret" -ne 0 ] || grep -q "^FAIL" "$log"; then
    rm -f "$log"
    exit 1
fi
rm -f "$log"

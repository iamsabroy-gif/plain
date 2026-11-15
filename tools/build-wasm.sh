#!/bin/sh
# Builds the browser playground's interpreter: web/plain.wasm (and copies the step viewer next to it).
#
#   WASI_SDK=/path/to/wasi-sdk sh tools/build-wasm.sh
#
# Get the WASI SDK (34 or newer: it must include the "eh" C++ libraries, for exceptions) from
# https://github.com/WebAssembly/wasi-sdk/releases and unpack it anywhere.
set -e
cd "$(dirname "$0")/.."
[ -n "$WASI_SDK" ] || { echo "Set WASI_SDK to the folder where you unpacked the WASI SDK."; exit 1; }
[ -x "$WASI_SDK/bin/clang++" ] || { echo "$WASI_SDK/bin/clang++ not found."; exit 1; }
sh tools/embed.sh
"$WASI_SDK/bin/clang++" --target=wasm32-wasip1 --sysroot="$WASI_SDK/share/wasi-sysroot" \
    -std=c++17 -O2 -fwasm-exceptions -mllvm -wasm-use-legacy-eh=false -DPLAIN_WASM \
    -Wl,--strip-all -Wl,-z,stack-size=2097152 -Wl,--max-memory=1073741824 \
    -o web/plain.wasm src/main.cpp -lunwind
cp lib/viz/player.html web/player.html
ls -la web/plain.wasm

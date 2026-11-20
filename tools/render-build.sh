#!/bin/sh
# Builds the browser playground and the documentation site into site/, for hosting on Render
# (render.yaml runs this). It does what .github/workflows/pages.yml does for GitHub Pages.
#
#   sh tools/render-build.sh
#
# Needs: curl, tar, a C++ compiler, make and node (Render's build machines have all of these).
set -e
cd "$(dirname "$0")/.."

WASI_VERSION=34
if [ ! -x wasi-sdk/bin/clang++ ]; then
    echo "Getting the WASI SDK $WASI_VERSION ..."
    curl -fsSL -o wasi-sdk.tar.gz \
        "https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-$WASI_VERSION/wasi-sdk-$WASI_VERSION.0-x86_64-linux.tar.gz"
    mkdir -p wasi-sdk && tar -xzf wasi-sdk.tar.gz -C wasi-sdk --strip-components=1
    rm wasi-sdk.tar.gz
fi

echo "Building plain.wasm ..."
WASI_SDK="$PWD/wasi-sdk" sh tools/build-wasm.sh
node tests/wasm_test.js

echo "Building plain (the documentation reads the lessons and problems from it) ..."
make

echo "Packing the site ..."
rm -rf site && mkdir site
cp web/*.html web/*.js web/plain.wasm site/
node tools/build-docs.js site/docs
echo "Done: site/ is ready."

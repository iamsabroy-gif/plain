#!/bin/sh
# The library files are packed into src/libfiles.hpp; make sure that copy is current, and that plain lib works.
DIR=$(cd "$(dirname "$0")" && pwd)
PLAIN=${1:-"$DIR/../build/plain"}
case "$PLAIN" in /*) ;; *) PLAIN="$(pwd)/$PLAIN" ;; esac
WORK=$(mktemp -d)
sh "$DIR/../tools/embed.sh" "$WORK/libfiles.hpp"
cmp -s "$WORK/libfiles.hpp" "$DIR/../src/libfiles.hpp" || { echo "FAILED: src/libfiles.hpp is out of date - run: sh tools/embed.sh"; rm -rf "$WORK"; exit 1; }
"$PLAIN" lib stack | cmp -s - "$DIR/../lib/stack.plain" || { echo "FAILED: plain lib stack"; rm -rf "$WORK"; exit 1; }
(cd "$WORK" && "$PLAIN" lib queue --copy >/dev/null && [ -f queue.plain ]) || { echo "FAILED: plain lib --copy"; rm -rf "$WORK"; exit 1; }
rm -rf "$WORK"
echo "lib: ok"

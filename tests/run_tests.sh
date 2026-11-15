#!/bin/sh
# Runs every program in tests/cases and compares what it prints with the
# saved .expected file.   Usage: sh tests/run_tests.sh [path-to-plain]
DIR=$(cd "$(dirname "$0")" && pwd)
PLAIN=${1:-"$DIR/../build/plain"}
case "$PLAIN" in /*) ;; *) PLAIN="$(pwd)/$PLAIN" ;; esac
WORK=$(mktemp -d)
pass=0
fail=0
cd "$WORK" || exit 1
for file in "$DIR"/cases/*.plain; do
    name=$(basename "$file" .plain)
    input=/dev/null
    [ -f "$DIR/cases/$name.in" ] && input="$DIR/cases/$name.in"
    (cd "$DIR/cases" && cp "$name.plain" "$WORK/$name.plain")
    "$PLAIN" "$name.plain" "$DIR/fixtures" < "$input" > "$WORK/$name.actual" 2>&1
    if cmp -s "$WORK/$name.actual" "$DIR/cases/$name.expected"; then
        pass=$((pass + 1))
    else
        fail=$((fail + 1))
        echo "FAILED: $name"
        diff "$DIR/cases/$name.expected" "$WORK/$name.actual" | head -10
    fi
done
rm -rf "$WORK"
echo "$pass passed, $fail failed"
[ "$fail" -eq 0 ]

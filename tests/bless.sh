#!/bin/sh
# Rewrites the .expected file of the named test cases from what the program prints now.
# Review the diff with git before committing.   Usage: sh tests/bless.sh [plain] name...
DIR=$(cd "$(dirname "$0")" && pwd)
PLAIN="$DIR/../build/plain"
for name in "$@"; do
    input=/dev/null
    [ -f "$DIR/cases/$name.in" ] && input="$DIR/cases/$name.in"
    WORK=$(mktemp -d)
    cp "$DIR/cases/$name.plain" "$WORK/"
    (cd "$WORK" && "$PLAIN" "$name.plain" "$DIR/fixtures" < "$input" > "$DIR/cases/$name.expected" 2>&1)
    rm -rf "$WORK"
done

#!/bin/sh
# plain format: rewrites old spellings, is idempotent, and never changes what a program prints.
DIR=$(cd "$(dirname "$0")" && pwd)
PLAIN=${1:-"$DIR/../build/plain"}
case "$PLAIN" in /*) ;; *) PLAIN="$(pwd)/$PLAIN" ;; esac
WORK=$(mktemp -d)
fail=0
"$PLAIN" format --print "$DIR/format/ugly.plain" > "$WORK/ugly.out"
cmp -s "$WORK/ugly.out" "$DIR/format/ugly.expected" || { echo "FAILED: format/ugly"; diff "$DIR/format/ugly.expected" "$WORK/ugly.out" | head; fail=1; }
"$PLAIN" format --check "$DIR"/../lib/*.plain "$DIR"/../lib/problems/*.plain >/dev/null || { echo "FAILED: lib/ is not in the standard style - run: plain format lib/*.plain lib/problems/*.plain"; fail=1; }
cp "$WORK/ugly.out" "$WORK/again.plain"
"$PLAIN" format --check "$WORK/again.plain" >/dev/null || { echo "FAILED: format is not idempotent on ugly"; fail=1; }
for file in "$DIR"/cases/*.plain "$DIR"/../examples/*.plain "$DIR"/../lib/*.plain; do
    [ -f "$file" ] || continue
    name=$(basename "$file" .plain)
    cp "$file" "$WORK/$name.plain"
    "$PLAIN" format "$WORK/$name.plain" >/dev/null 2>&1
    "$PLAIN" format --check "$WORK/$name.plain" >/dev/null 2>&1 || { echo "FAILED: format twice changed $name"; fail=1; }
    case "$name" in network|threads|benchmark|files|report) continue ;; esac   # need network, timing or files
    input=/dev/null
    [ -f "$DIR/cases/$name.in" ] && input="$DIR/cases/$name.in"
    (cd "$(dirname "$file")" && "$PLAIN" "$file" "$DIR/fixtures" < "$input" > "$WORK/a.out" 2>&1)
    cp "$WORK/$name.plain" "$(dirname "$file")/.fmt_$name.plain"
    (cd "$(dirname "$file")" && "$PLAIN" ".fmt_$name.plain" "$DIR/fixtures" < "$input" > "$WORK/b.out" 2>&1)
    rm -f "$(dirname "$file")/.fmt_$name.plain"
    sed 's/\.fmt_//g' "$WORK/b.out" > "$WORK/b2.out"
    cmp -s "$WORK/a.out" "$WORK/b2.out" || { echo "FAILED: formatting changed the output of $name"; diff "$WORK/a.out" "$WORK/b2.out" | head -5; fail=1; }
done
rm -rf "$WORK"
[ $fail -eq 0 ] && echo "format: ok"
[ $fail -eq 0 ]

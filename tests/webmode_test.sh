#!/bin/sh
# The browser playground's interpreter is this same code built with -DPLAIN_WASM (no threads, no sockets,
# no packages). Build that variant natively and check it behaves like the normal one on everything
# except what it deliberately cannot do.
DIR=$(cd "$(dirname "$0")" && pwd)
WORK=$(mktemp -d)
c++ -O1 -std=c++17 -DPLAIN_WASM -o "$WORK/plain_web" "$DIR/../src/main.cpp" || { echo "FAILED: the web-mode build does not compile"; rm -rf "$WORK"; exit 1; }
fail=0
for file in "$DIR"/cases/*.plain; do
    name=$(basename "$file" .plain)
    case "$name" in network|threads) continue ;; esac
    input=/dev/null
    [ -f "$DIR/cases/$name.in" ] && input="$DIR/cases/$name.in"
    cp "$file" "$WORK/$name.plain"
    (cd "$WORK" && ./plain_web "$name.plain" "$DIR/fixtures" < "$input" > "$name.actual" 2>&1)
    cmp -s "$WORK/$name.actual" "$DIR/cases/$name.expected" || { echo "FAILED (web mode): $name"; diff "$DIR/cases/$name.expected" "$WORK/$name.actual" | head -5; fail=1; }
done
"$WORK/plain_web" -e 'start_task(action gives 1)' > "$WORK/t.out" 2>&1
grep -q 'web playground' "$WORK/t.out" || { echo "FAILED (web mode): tasks should be refused politely"; fail=1; }
"$WORK/plain_web" -e 'say http_get("http://example.com")' > "$WORK/n.out" 2>&1
grep -q 'web playground' "$WORK/n.out" || { echo "FAILED (web mode): networking should be refused politely"; fail=1; }
"$WORK/plain_web" visualize --json -e 'say 1' | grep -q '"steps"' || { echo "FAILED (web mode): visualize --json"; fail=1; }
rm -rf "$WORK"
[ $fail -eq 0 ] && echo "web mode: ok"
[ $fail -eq 0 ]

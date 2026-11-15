#!/bin/sh
# plain visualize writes one standalone page; plain count reports operation counts.
DIR=$(cd "$(dirname "$0")" && pwd)
PLAIN=${1:-"$DIR/../build/plain"}
case "$PLAIN" in /*) ;; *) PLAIN="$(pwd)/$PLAIN" ;; esac
WORK=$(mktemp -d)
fail=0
check() { grep -q "$2" "$1" || { echo "FAILED: $3 (missing: $2)"; fail=1; }; }
"$PLAIN" visualize "$DIR/viz/bubble.plain" -o "$WORK/bubble.html" > "$WORK/msg" || fail=1
check "$WORK/msg" "Recorded 70 steps" "bubble: step count"
check "$WORK/bubble.html" '"swaps":8' "bubble: swaps counted"
check "$WORK/bubble.html" '"comparisons":15' "bubble: comparisons counted"
check "$WORK/bubble.html" 'function renderBars' "bubble: the player is inside the page"
if grep -q 'src=\|<link\|@import\|fetch(\|XMLHttpRequest' "$WORK/bubble.html"; then echo "FAILED: the page must not load anything from outside"; fail=1; fi
"$PLAIN" visualize "$DIR/viz/fib.plain" -o "$WORK/fib.html" > /dev/null || fail=1
check "$WORK/fib.html" '"calls":9' "fib: calls counted"
"$PLAIN" visualize "$DIR/viz/graph.plain" -o "$WORK/graph.html" > /dev/null || fail=1
check "$WORK/graph.html" '"M":' "graph: maps are recorded"
# a program that fails still gives a page that shows where
printf 'set xs to [1, 2]\nsay xs[5]\n' > "$WORK/bad.plain"
"$PLAIN" visualize "$WORK/bad.plain" -o "$WORK/bad.html" > /dev/null 2>&1 && { echo "FAILED: visualize should exit 1 for a program that fails"; fail=1; }
check "$WORK/bad.html" 'no item 5' "bad: the error is in the page"
# counting
"$PLAIN" count "$DIR/viz/bubble.plain" > "$WORK/count.out" 2>&1
check "$WORK/count.out" 'comparisons *15' "count: comparisons"
check "$WORK/count.out" 'swaps *8 ' "count: swaps"
check "$WORK/count.out" 'bubble_sort x1' "count: calls by name"
# a runaway loop is stopped, and 'try' cannot swallow that
printf 'try\n    while true\n        set x to 1\n    end\non error problem\n    say "caught"\nend\n' > "$WORK/loop.plain"
"$PLAIN" visualize "$WORK/loop.plain" --budget 200000 -o "$WORK/loop.html" > "$WORK/loop.msg" 2>&1 && { echo "FAILED: a runaway loop should stop with an error"; fail=1; }
check "$WORK/loop.html" '"out":\[\]' "loop: 'try' must not catch the stop"
check "$WORK/loop.msg" "I stopped it" "loop: the stop is explained"
rm -rf "$WORK"
[ $fail -eq 0 ] && echo "visualize/count: ok"
[ $fail -eq 0 ]

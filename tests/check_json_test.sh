#!/bin/sh
# plain check --json: what editors use to underline a mistake as you type.
DIR=$(cd "$(dirname "$0")" && pwd)
PLAIN=${1:-"$DIR/../build/plain"}
case "$PLAIN" in /*) ;; *) PLAIN="$(pwd)/$PLAIN" ;; esac
W=$(mktemp -d)
trap 'rm -rf "$W"' EXIT
fail=0
has() { printf '%s' "$1" | grep -q "$2" || { echo "FAILED (check --json): $3 (got: $1)"; fail=1; }; }
out=$(printf 'say "hi"\n' | "$PLAIN" check --json -)
[ "$out" = '{"ok":true}' ] || { echo "FAILED (check --json): a good program: $out"; fail=1; }
out=$(printf 'set total to 0\ntotal = 5\n' | "$PLAIN" check --json -)
has "$out" '"ok":false' "a mistake is reported"
has "$out" '"line":2' "on the right line"
has "$out" '"incomplete":false' "as a mistake"
printf 'set total to 0\ntotal = 5\n' | "$PLAIN" check --json - >/dev/null && { echo "FAILED (check --json): exit status for a mistake"; fail=1; }
out=$(printf 'set x to 1\nif x is 1 then\n    say x\n' | "$PLAIN" check --json -)
has "$out" '"incomplete":true' "a block still open is marked incomplete"
has "$out" '"line":2' "on the line that opens it"
out=$(printf 'say "a \\"quote\\" and a\\ttab"\nsay nope(\n' | "$PLAIN" check --json -)
printf '%s' "$out" | python3 -c 'import json,sys; json.loads(sys.stdin.read())' 2>/dev/null || { echo "FAILED (check --json): the line is not valid JSON: $out"; fail=1; }
printf 'say 1\n' > "$W/ok.plain"
out=$("$PLAIN" check --json "$W/ok.plain")
[ "$out" = '{"ok":true}' ] || { echo "FAILED (check --json): from a file: $out"; fail=1; }
out=$("$PLAIN" check "$W/ok.plain")
has "$out" "No problems found" "plain check without --json is unchanged"
[ $fail -eq 0 ] && echo "check --json: ok"
[ $fail -eq 0 ]

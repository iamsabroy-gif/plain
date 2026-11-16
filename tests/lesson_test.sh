#!/bin/sh
# plain lesson: every reference solution passes, and a learner's wrong and right answers are told apart.
DIR=$(cd "$(dirname "$0")" && pwd)
PLAIN=${1:-"$DIR/../build/plain"}
case "$PLAIN" in /*) ;; *) PLAIN="$(pwd)/$PLAIN" ;; esac
W=$(mktemp -d)
trap 'rm -rf "$W"' EXIT
fail() { echo "FAILED (lessons): $1"; exit 1; }
"$PLAIN" lesson --selftest > "$W/self.txt" || { cat "$W/self.txt"; fail "selftest"; }
cd "$W" || exit 1
"$PLAIN" lesson 3 > /dev/null || fail "starting a lesson"
[ -f lesson3-1.plain ] || fail "the exercise file was not made"
"$PLAIN" lesson 3 > /dev/null && fail "an empty exercise passed"
printf 'say 1\nsay 2\nsay 3\nsay 4\nsay 5\nsay 6\nsay 7\nsay 8\nsay 9\nsay 10\n' >> lesson3-1.plain
"$PLAIN" lesson 3 | grep -q "using 'for'" || fail "ten says passed an exercise about loops"
printf 'for i from 1 to 10\n    say i\nend\n' > lesson3-1.plain
"$PLAIN" lesson 3 | grep -q "Well done" || fail "a right answer was refused"
[ -f lesson3-2.plain ] || fail "the next exercise was not made"
printf 'ask "Which table?" into n\nfor i from 1 to 5\n    say "{n} x {i} = {n + i}"\nend\n' >> lesson3-2.plain
"$PLAIN" lesson 3 | grep -q 'expected  "3 x 1 = 3"' || fail "a wrong answer did not show what was expected"
"$PLAIN" lesson | grep -q "1 of 4 exercises done" || fail "progress was not kept"
echo "lessons: ok"

#!/bin/sh
# plain practice: every reference solution passes every test, and the learner's flow works.
DIR=$(cd "$(dirname "$0")" && pwd)
PLAIN=${1:-"$DIR/../build/plain"}
case "$PLAIN" in /*) ;; *) PLAIN="$(pwd)/$PLAIN" ;; esac
WORK=$(mktemp -d)
fail=0
check() { grep -q "$2" "$1" || { echo "FAILED: $3 (missing: $2)"; fail=1; }; }
"$PLAIN" practice --selftest > "$WORK/self.out" 2>&1 || { cat "$WORK/self.out"; fail=1; }
check "$WORK/self.out" '^50 problems' "the bank has 50 problems"
cd "$WORK" || exit 1
"$PLAIN" practice > list.out
check list.out 'two-sum' "listing"
"$PLAIN" practice two-sum > start.out
[ -f two-sum.plain ] || { echo "FAILED: the starter file was not made"; fail=1; }
"$PLAIN" practice two-sum > run1.out 2>&1 && { echo "FAILED: the stub should not pass"; fail=1; }
check run1.out 'hidden test 1 of 4 failed' "hidden tests are reported without being shown"
if grep -q '\-1, -2, -3' run1.out; then echo "FAILED: a hidden test's data was shown"; fail=1; fi
"$PLAIN" practice two-sum --solution > gate.out
check gate.out 'Try the hints first' "the solution is held back"
"$PLAIN" practice two-sum --hint > h1.out; check h1.out 'Hint 1 of 3' "hint 1"
"$PLAIN" practice two-sum --hint > h2.out; check h2.out 'Hint 2 of 3' "hint 2"
"$PLAIN" practice two-sum --hint > h3.out; check h3.out 'Hint 3 of 3' "hint 3"
"$PLAIN" practice two-sum --solution > sol.out; check sol.out 'define two_sum with numbers, target' "the solution uses the learner's action name"
check sol.out 'How it works' "the solution is explained"
cat > two-sum.plain <<'EOT'
define two_sum with numbers, target
    set seen to {}
    for i from 1 to length of numbers
        if has_key(seen, target - numbers[i]) then
            give back [seen[target - numbers[i]], i]
        end
        set seen[numbers[i]] to i
    end
    give back []
end
EOT
"$PLAIN" practice two-sum > solved.out 2>&1 || { echo "FAILED: a right solution should pass"; cat solved.out; fail=1; }
check solved.out 'All tests passed' "pass message"
"$PLAIN" practice > list2.out; check list2.out 'solved' "solved is remembered"
# correct but slow: told so
cat > slow.plain <<'EOT'
define two_sum with numbers, target
    for i from 1 to length of numbers
        for j from i + 1 to length of numbers
            if numbers[i] + numbers[j] is target then
                give back [i, j]
            end
        end
    end
end
EOT
"$PLAIN" practice two-sum --file slow.plain > slow.out 2>&1; check slow.out 'much more work than it needs' "slow solutions are told"
# a loop that never ends is stopped
printf 'define two_sum with a, b\n    while true\n        set x to 1\n    end\nend\n' > loop.plain
"$PLAIN" practice two-sum --file loop.plain > loop.out 2>&1 && { echo "FAILED: a runaway loop must not pass"; fail=1; }
check loop.out 'I stopped checking' "runaway loops are stopped"
# naive fibonacci is correct but cannot do n = 50
printf 'define fibonacci with n\n    if n is less than 2 then\n        give back n\n    end\n    give back fibonacci(n - 1) + fibonacci(n - 2)\nend\n' > naive.plain
"$PLAIN" practice fibonacci --file naive.plain > naive.out 2>&1 && { echo "FAILED: naive fibonacci should not pass n = 50"; fail=1; }
check naive.out 'fibonacci(10)  gave  55' "naive fibonacci passes the small tests"
check naive.out 'far too big for the simplest recursion' "the slow hidden test is named"
# the advanced problems really do need the faster idea: the naive version is correct but is stopped on the big test
printf 'define climb_ways with n\n    if n is at most 2 then\n        give back n\n    end\n    give back climb_ways(n - 1) + climb_ways(n - 2)\nend\n' > climb.plain
"$PLAIN" practice climbing-stairs --file climb.plain > climb.out 2>&1 && { echo "FAILED: naive climbing stairs should not pass n = 45"; fail=1; }
check climb.out 'climb_ways(3)  gave  3' "naive climbing stairs passes the small tests"
check climb.out 'I stopped checking' "naive climbing stairs is stopped on the big test"
printf 'define fewest_coins with coins, amount\n    if amount is 0 then\n        give back 0\n    end\n    set best to -1\n    for each c in coins\n        if c is at most amount then\n            set sub to fewest_coins(coins, amount - c)\n            if sub is not -1 and (best is -1 or sub + 1 is less than best) then\n                set best to sub + 1\n            end\n        end\n    end\n    give back best\nend\n' > coins.plain
"$PLAIN" practice coin-change --file coins.plain > coins.out 2>&1 && { echo "FAILED: naive coin change should not pass the big amount"; fail=1; }
check coins.out 'fewest_coins(\[1\], 0)  gave  0' "naive coin change passes the small tests"
check coins.out 'I stopped checking' "naive coin change is stopped on the big test"
printf 'define two_sum with numbers, target\n    give back numbers[99]\nend\n' > err.plain
"$PLAIN" practice two-sum --file err.plain > err.out 2>&1; check err.out 'there is no item 99' "errors in the learner's code are explained"
"$PLAIN" practice nosuchthing > nope.out 2>&1; check nope.out 'There is no problem called' "unknown problem"
cd /
rm -rf "$WORK"
[ $fail -eq 0 ] && echo "practice: ok"
[ $fail -eq 0 ]

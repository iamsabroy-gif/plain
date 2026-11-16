#!/bin/sh
# Tests the package manager with a local folder and a local git repository.
# Usage: sh tests/pkg_test.sh [path-to-plain]
DIR=$(cd "$(dirname "$0")" && pwd)
PLAIN=${1:-"$DIR/../build/plain"}
case "$PLAIN" in /*) ;; *) PLAIN="$(pwd)/$PLAIN" ;; esac
W=$(mktemp -d)
trap 'rm -rf "$W"' EXIT
fail() { echo "FAILED (packages): $1"; exit 1; }
mkdir -p "$W/tools" "$W/greeter" "$W/app"
echo '{"name": "tools", "version": "0.3.0"}' > "$W/tools/plain.json"
printf 'define shout with s\n    give back uppercase(s) + "!"\nend\n' > "$W/tools/main.plain"
if command -v git >/dev/null 2>&1; then
    (cd "$W/tools" && git init -q && git add . && git -c user.email=t@t -c user.name=t commit -qm one) || fail "git setup"
    TOOLS="file://$W/tools"
else
    TOOLS="$W/tools"
fi
printf '{"name": "greeter", "version": "1.2.0", "main": "hello.plain", "dependencies": {"tools": "%s"}}\n' "$TOOLS" > "$W/greeter/plain.json"
printf 'use "tools"\ndefine greet with who\n    give back shout("hello, " + who)\nend\n' > "$W/greeter/hello.plain"
printf 'use "greeter"\nsay greet("plain")\n' > "$W/app/main.plain"
cd "$W/app" || exit 1
"$PLAIN" init demo > /dev/null || fail "init"
"$PLAIN" install ../greeter > /dev/null || fail "install"
[ -d plain_modules/tools ] || fail "dependency of a package was not installed"
grep -q '"greeter"' plain.json || fail "plain.json was not updated"
grep -q '"greeter"' plain.lock || fail "plain.lock was not written"
[ "$("$PLAIN" main.plain)" = "HELLO, PLAIN!" ] || fail "program using packages"
rm -rf plain_modules
"$PLAIN" install > /dev/null || fail "install from plain.json"
[ "$("$PLAIN" main.plain)" = "HELLO, PLAIN!" ] || fail "program after reinstall"
"$PLAIN" build main.plain -o built > /dev/null || fail "build"
mkdir ../elsewhere && cp built ../elsewhere/ && [ "$(cd ../elsewhere && ./built)" = "HELLO, PLAIN!" ] || fail "built program with packages"
"$PLAIN" remove greeter > /dev/null || fail "remove"
[ ! -d plain_modules/greeter ] || fail "remove left the package"
"$PLAIN" install "ext::sh -c touch $W/pwned" > /dev/null 2>&1 && fail "dangerous address accepted"
[ ! -e "$W/pwned" ] || fail "dangerous address ran a command"

# Version ranges and the registry: a package with tags v1.0.0, v1.2.0, v1.10.1 and v2.0.0.
if command -v git >/dev/null 2>&1; then
    mkdir -p "$W/colors" && cd "$W/colors" || exit 1
    git init -q
    for v in 1.0.0 1.2.0 1.10.1 2.0.0; do
        printf '{"name": "colors", "version": "%s"}\n' "$v" > plain.json
        printf 'define colors_version\n    give back "%s"\nend\n' "$v" > main.plain
        git add . && git -c user.email=t@t -c user.name=t commit -qm "v$v" && git tag "v$v"
    done
    printf '{"colors": {"spec": "file://%s/colors", "description": "Colour names for drawing"}}\n' "$W" > "$W/registry.json"
    export PLAIN_REGISTRY="$W/registry.json" PLAIN_SHARED_REGISTRY=off
    mkdir -p "$W/app2" && cd "$W/app2" || exit 1
    printf 'use "colors"\nsay colors_version()\n' > main.plain
    check_range() {
        rm -rf plain_modules plain.lock plain.json
        "$PLAIN" install "$1" > /dev/null || fail "install $1"
        got=$("$PLAIN" main.plain)
        [ "$got" = "$2" ] || fail "range $1 gave $got, expected $2"
    }
    check_range "colors#^1.2" 1.10.1
    check_range "colors#~1.2.0" 1.2.0
    check_range "colors#1.x" 1.10.1
    check_range "colors#>=1.0 <1.5" 1.2.0
    check_range "colors#^1.0 || ^2.0" 2.0.0
    check_range "colors#v1.0.0" 1.0.0
    check_range "colors" 2.0.0
    rm -rf plain_modules plain.lock plain.json
    "$PLAIN" install "colors#^3.0" > /dev/null 2>&1 && fail "a range nothing fits was accepted"
    "$PLAIN" search colour | grep -q "^colors " || fail "search by description"
    "$PLAIN" search nothing-like-this | grep -q "No packages found" || fail "search with no match"
fi
echo "packages: ok"

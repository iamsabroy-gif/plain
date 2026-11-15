#!/bin/sh
# The programs shown in the documentation must run and print what the page says.
DIR=$(cd "$(dirname "$0")" && pwd)
PLAIN=${1:-"$DIR/../build/plain"}
case "$PLAIN" in /*) ;; *) PLAIN="$(pwd)/$PLAIN" ;; esac
command -v python3 >/dev/null 2>&1 || { echo "docs: skipped (python3 not found)"; exit 0; }
python3 "$DIR/docs_check.py" "$PLAIN" "$DIR"/../docs/KIDS.md "$DIR"/../docs/DEVELOPER.md

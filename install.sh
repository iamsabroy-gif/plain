#!/bin/sh
# Builds Plain and installs the 'plain' command.
#   sh install.sh              pick a folder on your PATH automatically
#   sh install.sh /some/dir    install into /some/dir
set -e
cd "$(dirname "$0")"

if ! command -v c++ >/dev/null 2>&1; then
    echo "I need a C++ compiler to build Plain."
    echo "On a Mac, run:  xcode-select --install   and then run this script again."
    exit 1
fi

echo "Building Plain..."
mkdir -p build
c++ -O2 -std=c++17 -o build/plain src/main.cpp

echo "Testing..."
sh tests/run_tests.sh build/plain

target=$1
if [ -z "$target" ]; then
    for dir in "$(command -v brew >/dev/null 2>&1 && brew --prefix)/bin" /usr/local/bin "$HOME/.local/bin"; do
        [ "$dir" = "/bin" ] && continue
        if [ -d "$dir" ] && [ -w "$dir" ]; then
            target=$dir
            break
        fi
    done
fi
if [ -z "$target" ]; then
    target="$HOME/.local/bin"
    mkdir -p "$target"
fi

mkdir -p "$target"
cp build/plain "$target/plain"
chmod 755 "$target/plain"
echo "Installed: $target/plain"
case ":$PATH:" in
    *":$target:"*) echo "Try it:  plain examples/tour.plain" ;;
    *) echo "Add this line to your ~/.zshrc so the 'plain' command is found, then open a new Terminal window:"
       echo "  export PATH=\"$target:\$PATH\"" ;;
esac

#!/bin/sh
# Installs the 'plain' command. No compiler needed.
#
#   curl -fsSL https://raw.githubusercontent.com/iamsabroy-gif/plain/main/install.sh | sh
#
# It downloads a ready-made program for your computer (Mac or Linux), puts it in
# ~/.local/bin and makes sure that folder is on your PATH.
#
# Other ways to run it:
#   sh install.sh /some/folder    install into that folder
#   sh install.sh --build         build from this source folder instead (needs a C++ compiler)
set -e

REPO="${PLAIN_REPO:-iamsabroy-gif/plain}"
BASE="${PLAIN_DOWNLOAD_URL:-https://github.com/$REPO/releases/latest/download}"

say() { printf '%s\n' "$*"; }
die() { printf '\nSorry, I could not finish: %s\n' "$*" >&2; exit 1; }

mode=download
target=
for arg in "$@"; do
    case "$arg" in
        --build) mode=build ;;
        *) target=$arg ;;
    esac
done
[ -n "$target" ] || target="$HOME/.local/bin"

fetch() {  # fetch URL FILE
    if command -v curl >/dev/null 2>&1; then curl -fsSL "$1" -o "$2"
    elif command -v wget >/dev/null 2>&1; then wget -q "$1" -O "$2"
    else die "I need either 'curl' or 'wget' to download Plain, and found neither."; fi
}

work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT

if [ "$mode" = build ]; then
    here=$(cd "$(dirname "$0")" && pwd)
    [ -f "$here/src/main.cpp" ] || die "--build only works from a copy of the Plain source folder."
    command -v c++ >/dev/null 2>&1 || die "no C++ compiler found. Run this without --build to download a ready-made Plain instead."
    say "Building Plain..."
    mkdir -p "$here/build"
    c++ -O2 -std=c++17 -o "$here/build/plain" "$here/src/main.cpp"
    sh "$here/tests/run_tests.sh" "$here/build/plain"
    cp "$here/build/plain" "$work/plain"
else
    os=$(uname -s)
    cpu=$(uname -m)
    case "$os" in
        Darwin) os=macos ;;
        Linux) os=linux ;;
        *) die "this installer supports Mac and Linux. On Windows, install WSL (run 'wsl --install' in PowerShell) and run the same command inside it." ;;
    esac
    case "$cpu" in
        x86_64|amd64) cpu=x86_64 ;;
        arm64|aarch64) cpu=arm64 ;;
        *) die "there is no ready-made Plain for a '$cpu' computer yet. Build it from source: https://github.com/$REPO" ;;
    esac
    name="plain-$os-$cpu"
    say "Downloading Plain for $os ($cpu)..."
    fetch "$BASE/$name" "$work/plain" || die "the download failed. Check your internet connection, then run the command again."
    # check it arrived whole, when the computer has a tool for that
    if fetch "$BASE/$name.sha256" "$work/sum" 2>/dev/null; then
        want=$(cut -d' ' -f1 "$work/sum")
        if command -v sha256sum >/dev/null 2>&1; then got=$(sha256sum "$work/plain" | cut -d' ' -f1)
        elif command -v shasum >/dev/null 2>&1; then got=$(shasum -a 256 "$work/plain" | cut -d' ' -f1)
        else got=$want; fi
        [ "$got" = "$want" ] || die "the downloaded file is damaged. Run the command again."
    fi
fi

mkdir -p "$target"
cp "$work/plain" "$target/plain"
chmod 755 "$target/plain"
# a program downloaded on a Mac may carry a "from the internet" mark that stops it starting
command -v xattr >/dev/null 2>&1 && xattr -d com.apple.quarantine "$target/plain" 2>/dev/null || true
"$target/plain" --version >/dev/null 2>&1 || die "Plain was installed but will not start on this computer."

say "Installed: $target/plain  ($("$target/plain" --version))"

# make sure the folder is on the PATH, now and in new Terminal windows
case ":$PATH:" in
    *":$target:"*) say "Try it:   plain -e \"say 6 * 7\"" ;;
    *)
        line="export PATH=\"$target:\$PATH\""
        added=
        for rc in "$HOME/.zshrc" "$HOME/.bashrc" "$HOME/.profile"; do
            case "$rc" in
                */.zshrc) [ "$(basename "${SHELL:-}")" = zsh ] || [ -f "$rc" ] || continue ;;
                */.bashrc) [ "$(basename "${SHELL:-}")" = bash ] || [ -f "$rc" ] || continue ;;
            esac
            if ! grep -qsF "$line" "$rc"; then printf '\n# added by the Plain installer\n%s\n' "$line" >> "$rc"; fi
            added="$added $rc"
        done
        say "I added $target to your PATH in:$added"
        say "Close this Terminal window and open a new one, then try:   plain -e \"say 6 * 7\""
        ;;
esac

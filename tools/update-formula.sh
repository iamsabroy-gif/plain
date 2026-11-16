#!/bin/sh
# Points the Homebrew formula at a tagged release: sh tools/update-formula.sh v2.2.0
set -e
cd "$(dirname "$0")/.."
TAG=${1:?Give the release tag, like: sh tools/update-formula.sh v2.2.0}
URL="https://github.com/iamsabroy-gif/plain/archive/refs/tags/$TAG.tar.gz"
TMP=$(mktemp)
curl -fsSL "$URL" -o "$TMP" || { echo "Couldn't download $URL - is the tag pushed?"; exit 1; }
SHA=$( (shasum -a 256 "$TMP" 2>/dev/null || sha256sum "$TMP") | cut -d' ' -f1)
rm -f "$TMP"
F=packaging/homebrew/plain.rb
# Replace the release lines (the marker line, or the url/sha256 written last time).
awk -v url="$URL" -v sha="$SHA" '
  /# RELEASE/ || /^  url "/ { if (!done) { print "  url \"" url "\""; print "  sha256 \"" sha "\""; done = 1 } next }
  /^  sha256 "/ { next }
  { print }' "$F" > "$F.new" && mv "$F.new" "$F"
echo "Updated $F to $TAG ($SHA). Copy it to the tap: homebrew-plain/Formula/plain.rb"

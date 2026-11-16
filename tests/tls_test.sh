#!/bin/sh
# https without curl: a local TLS server with a made-up certificate is refused until it is trusted.
# Needs the openssl command and OpenSSL's library; skipped otherwise.
DIR=$(cd "$(dirname "$0")" && pwd)
PLAIN=${1:-"$DIR/../build/plain"}
case "$PLAIN" in /*) ;; *) PLAIN="$(pwd)/$PLAIN" ;; esac
command -v openssl >/dev/null 2>&1 || { echo "tls: skipped (no openssl command)"; exit 0; }
W=$(mktemp -d)
cleanup() { [ -n "$SERVER" ] && kill "$SERVER" 2>/dev/null; rm -rf "$W"; }
trap cleanup EXIT
fail() { echo "FAILED (tls): $1"; exit 1; }
openssl req -x509 -newkey rsa:2048 -nodes -keyout "$W/key.pem" -out "$W/cert.pem" -days 2 \
    -subj "/CN=localhost" -addext "subjectAltName=DNS:localhost" >/dev/null 2>&1 || { echo "tls: skipped (couldn't make a certificate)"; exit 0; }
PORT=$((20000 + $$ % 20000))
openssl s_server -quiet -accept "$PORT" -cert "$W/cert.pem" -key "$W/key.pem" -www >/dev/null 2>&1 &
SERVER=$!
sleep 1
printf 'try\n    set r to http_get("https://localhost:%s/")\n    say "status", r'"'"'s status\non error problem\n    say problem\nend\n' "$PORT" > "$W/get.plain"
export NO_PROXY=localhost no_proxy=localhost
out=$(SSL_CERT_FILE=/nonexistent "$PLAIN" "$W/get.plain")
case "$out" in
    *"can't be trusted"*) ;;
    *"Web requests need the 'curl'"*|*"I couldn't reach"*) echo "tls: skipped (no OpenSSL library: https uses curl)"; exit 0 ;;
    *) fail "an untrusted certificate was accepted: $out" ;;
esac
out=$(SSL_CERT_FILE="$W/cert.pem" "$PLAIN" "$W/get.plain")
[ "$out" = "status 200" ] || fail "a trusted certificate was refused: $out"
echo "tls: ok"

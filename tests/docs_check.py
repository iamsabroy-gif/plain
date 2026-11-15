#!/usr/bin/env python3
"""Runs the Plain programs shown in the documentation and checks that they print what the page says.

In a Markdown file:
    ```input        typed answers for the next program (optional)
    ```plain        a complete program that must run; the next ```output block must match what it prints
    ```plain-fails  a program that must stop with an error; the next ```output block must match the message
    ```output       what the program before it prints (stdout, then stderr)
    ```plain-nocheck  a fragment that is not run

Usage: docs_check.py path/to/plain file.md [file.md ...]
"""
import os, re, subprocess, sys, tempfile

def blocks(text):
    out, lines, i = [], text.split("\n"), 0
    while i < len(lines):
        m = re.match(r"^```([A-Za-z0-9_-]*)\s*$", lines[i])
        if m:
            kind, body, i = m.group(1), [], i + 1
            while i < len(lines) and not lines[i].startswith("```"):
                body.append(lines[i]); i += 1
            out.append((kind, "\n".join(body) + "\n"))
        i += 1
    return out

def clean(s):
    return "\n".join(l.rstrip() for l in s.strip("\n").split("\n")).strip("\n")

def main():
    plain, files = os.path.abspath(sys.argv[1]), sys.argv[2:]
    failures, ran = 0, 0
    work = tempfile.mkdtemp()
    for path in files:
        bs = blocks(open(path, encoding="utf-8").read())
        stdin = ""
        for n, (kind, body) in enumerate(bs):
            if kind == "input":
                stdin = body
                continue
            if kind not in ("plain", "plain-fails"):
                continue
            expected = bs[n + 1][1] if n + 1 < len(bs) and bs[n + 1][0] == "output" else None
            prog = os.path.join(work, "doc.plain")
            open(prog, "w", encoding="utf-8").write(body)
            try:
                r = subprocess.run([plain, "doc.plain"], cwd=work, input=stdin, capture_output=True, text=True, timeout=30)
            except subprocess.TimeoutExpired:
                print("FAILED: %s: block %d ran too long\n%s" % (path, n + 1, body)); failures += 1; stdin = ""; continue
            ran += 1
            got = clean(r.stdout + r.stderr)
            where = "%s (block %d)" % (path, n + 1)
            if kind == "plain" and r.returncode != 0:
                print("FAILED: %s should run but stopped:\n%s\n%s" % (where, body, got)); failures += 1
            elif kind == "plain-fails" and r.returncode == 0:
                print("FAILED: %s should stop with an error but ran:\n%s" % (where, body)); failures += 1
            elif expected is not None and clean(expected) != got:
                print("FAILED: %s prints something different from the page\n--- program\n%s--- the page says\n%s\n--- it prints\n%s" % (where, body, clean(expected), got)); failures += 1
            stdin = ""
    print("docs: %s (%d programs run)" % ("ok" if not failures else "%d problem(s)" % failures, ran))
    sys.exit(1 if failures else 0)

main()

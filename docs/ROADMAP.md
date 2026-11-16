# Plain roadmap

1.0.0: bytecode compiler and virtual machine, lists, maps, actions, `try` / `fail`,
`use`, built-in actions, interactive session, `plain check`, `plain build`, installer.

2.0.0: integers of any size and exact decimals, anonymous actions and closures,
classes with inheritance, tasks / channels / locks, a cycle collector, a web
client and server, a package manager with `plain.json` and `plain.lock`.

2.1.0: learning tools. A standard style and `plain format`; per-round loop variables
for closures; clearer reserved-word errors and errors that show the line and what to
try; the data-structure library written in Plain (`use "dsa"`, `plain lib`);
`plain visualize` (one standalone page that steps through a run and draws lists,
recursion, trees, linked lists and graphs); `plain count`, `growth` and `compare`;
`plain practice` with 30 problems (50 after the advanced set: dynamic programming, heaps,
tries, union-find, backtracking, intervals, weighted graphs); more data structures (trie, union-find,
ring buffer, LRU cache, Fenwick and segment trees, AVL tree, counter, O(1) deque); `plain check --beginner`; a watched copy of the
VM loop that costs nothing when it is not used.

2.2.0: simpler to learn, and the roadmap of 2.1. Text templates (`say "Hello {name}"`);
clearer mistakes (`x = 5`, `sort(xs)` alone, `define f(x)`, `1 < x < 9`, names from other
languages); an empty map is false and a `for` counter ends on its last value. `plain lesson`:
ten lessons with 31 checked exercises, also as a picture-led path in the playground, whose
editor now colours code and has clickable blocks, Tidy and saved programs. `# watch: xs as
bars` picks how a value is drawn; `plain visualize a.plain b.plain` steps two programs side by
side. A shared package index (`plain search`) and version ranges (`#^1.2`). https without curl
(OpenSSL loaded at run time, with certificate checks and proxies). A VS Code extension and a
Homebrew formula. Faster objects: method inline caches, small maps without hashing, and text
that remembers its hash (about 20% less work for method-heavy code).

2.3.0: apps. `use "web"` (routes with `:params`, forms, JSON, sessions, static files, safe
HTML and `fill` templates, error pages, `try_request` for testing) and `use "desktop"` (a
window of widgets drawn by the browser engine, with actions, timers and messages), both
written in Plain. Underneath: `tcp_listen(port, "localhost")`, `http_serve` with `idle` and
`done`, `open_url` (app windows) and `secure_token`.

What is left, and why:

1. **A check with real learners** that the drawings, lessons and error messages are understood.
   This needs people, not code: watch a few beginners use `plain lesson` and the playground.
2. **Publishing**: the VS Code extension to the Marketplace (`editors/vscode`), a
   `homebrew-plain` tap (see `packaging/homebrew/README.md`), and the first packages in
   `registry/index.json`. Each needs an account owner to do it once.
3. **The playground's wasm build in CI.** The page is tested with the native interpreter
   standing in (`tests/web_ui_test.js`); the Pages workflow builds the real `plain.wasm`.
4. **Windows networking** (sockets via Winsock, and https through Schannel or OpenSSL). It needs
   a Windows machine or CI job to build and test against. Until then, web and desktop apps
   run on Mac and Linux (and WSL), not in the Windows build.
4b. **Web servers for many visitors at once**: `http_serve` answers one request at a time.
5. **Tasks on several cores.** Every value is reference counted without atomics, and one lock
   keeps tasks taking turns. Running them in parallel needs per-task heaps (copying or moving
   values between tasks over channels) or atomic counts everywhere (slower for everyone).
   Worth doing only once a real program needs it.
6. **Direct-threaded dispatch.** Profiling showed the dispatch loop is not where the time goes
   (it was map lookups, now fixed); expect around 10% for a large, risky change.
7. **A real native compiler** (Plain to machine code instead of bundling the interpreter, as
   `plain build` does now). A big project: a typed middle layer, or emitting C for each action.

# How Plain works, tests, and releasing

## How it works

1. **Tokens** (`src/lexer.hpp`): the text is split into words, numbers, text and symbols.
2. **Bytecode** (`src/compiler.hpp`): a single-pass compiler turns the tokens into
   compact instructions for a stack machine. Variable names are resolved to
   numbered slots here, so nothing is looked up by name while running.
   Variables that closures use are captured as "upvalues".
3. **Virtual machine** (`src/vm.hpp`): a loop carries out the instructions.
   Values are 16 bytes; integers and floats are stored inline, with fast paths
   for them; everything else (text, lists, big integers, decimals, objects) is
   reference counted, and `src/tasks.hpp` has the cycle collector that frees
   what reference counting cannot.

4. **Watching** (`src/observe.hpp`): the main loop of the VM is compiled twice, as
   `executeT<false>` (the normal run, with no trace of any watching code) and
   `executeT<true>` (calls the hooks that count comparisons, swaps and calls and
   record a step for each source line). `plain count`, `visualize`, `growth`,
   `compare` and `practice` use the second copy, so they measure the same bytecode
   that really runs, and a normal run pays nothing.

Numbers are in `src/bigint.hpp` and `src/numeric.hpp`, the built-in actions in
`src/builtins.hpp` (networking included), tasks in `src/tasks.hpp`, the package
manager in `src/pkg.hpp`, the formatter in `src/format.hpp`, the learning commands in
`src/tools.hpp` and `src/practice.hpp`, and the command line in `src/main.cpp`.
The data-structure library, the practice problems and the two web pages live in
`lib/`; `sh tools/embed.sh` packs them into `src/libfiles.hpp` (done by `make`).
`plain --explain file.plain` prints the tokens and bytecode for any program.

## Tests

`make test` runs every program in `tests/cases` and compares its output with
the saved `.expected` file, then runs the package-manager, formatter, library,
visualizer/counting and practice tests (`tests/bless.sh name` re-saves an expected
file after you have checked the change).

## Limits

- Tasks run one at a time (see above); there is no parallel speed-up.
- `plain visualize` records at most 6,000 steps, shows at most 80 items of a list and
  600 values per variable, and the player folds the built-in library into the line
  that called it. Counts do not include the inside of `sort()` and other built-ins.
- `Unique` and graph node names must be text, numbers or true/false (map keys).
- Decimals do not mix with floats, and have no `sqrt`/`sin`; use `float(x)`.
- `plain build` copies this executable plus your source: the result is standalone,
  but it contains the interpreter, not machine code made from your program.
- `https` needs the `curl` program; Windows has no networking or `plain install` yet.
- macOS and Windows builds are made from the same portable C++17 code, but the
  tests so far ran on Linux only.

## The browser playground

`web/` is a static site: `index.html` (editor, Run, Watch it run, Count the work, examples,
share links), `worker.js` (runs the interpreter in a Web Worker, so a stuck program can be
stopped, and supplies the little "operating system" the interpreter needs) and
`plain.wasm` (the interpreter itself). "Watch it run" runs `plain visualize --json -e ...`
in the worker and gives the trace to the same player that `plain visualize` writes.

The interpreter is this same source built with `-DPLAIN_WASM` (set automatically for
WebAssembly): no threads, sockets, processes or package manager, so tasks, networking and
files are refused with a clear message. `sh tests/webmode_test.sh` builds that variant
natively and checks it against the test cases.

To build `plain.wasm` you need the [WASI SDK](https://github.com/WebAssembly/wasi-sdk/releases)
(version 34 or newer, which includes the exception-enabled C++ libraries):

```
WASI_SDK=/path/to/wasi-sdk sh tools/build-wasm.sh
node tests/wasm_test.js            # runs the same worker.js against plain.wasm in Node
cd web && python3 -m http.server   # then open http://localhost:8000 (workers need http, not file:)
```

The build uses WebAssembly's newer exception encoding (`-wasm-use-legacy-eh=false`, which is
what the SDK's own libraries use; a module can't mix the two). It needs Chrome or Edge 137+,
Firefox 131+ or Safari 18.4+; older browsers get a message saying so. The file is about 1.1 MB
(about 340 KB sent compressed).

`node tests/web_e2e.js` opens the real page in Chromium (needs Playwright) and uses it: run,
errors, `ask`, the library, Watch it run, Count, Stop on an endless loop, and phone width.
Output is sent from the worker in batches and the page stops a program that says more than
300,000 letters, so a runaway loop can't freeze the page.

`.github/workflows/pages.yml` builds and publishes it to GitHub Pages whenever `main`
changes. One-time setup for the repository owner: Settings, Pages, Source: "GitHub Actions".

## Releasing

The one-line installers (`install.sh`, `install.ps1`) download ready-made programs from
the latest GitHub release. `.github/workflows/release.yml` builds them for Mac, Linux
and Windows when a version tag is pushed:

```
git tag v2.1.0 && git push origin v2.1.0
```

Check the Actions tab afterwards, and try both installers on a clean machine.
Windows support has been less tested than Mac and Linux.

## Changing the library, problems or web pages

Files in `lib/` (the data structures, `lib/problems`, `lib/viz`) are packed into
`src/libfiles.hpp` by `sh tools/embed.sh` (`make` does this for you). A test fails if
the packed copy is out of date. `plain practice --selftest` checks every problem.

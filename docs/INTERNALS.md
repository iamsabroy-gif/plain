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

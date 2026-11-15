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
`plain practice` with 30 problems; `plain check --beginner`; a watched copy of the
VM loop that costs nothing when it is not used.

Candidates, largest effect first:

0. Learning tools next: more problems (dynamic programming, heaps, tries), a lesson
   runner that checks each lesson's exercises, side-by-side stepping of two
   solutions in one page, a `# watch:` that can pick how a value is drawn, and a
   check with real learners that the sorted-array and recursion-tree views are
   understood before more views are added.

1. A package registry (a hosted index, so `plain install name` works for everyone) and version ranges.
2. Text templates: `say "Hello {name}"`.
3. Tasks that run on several cores (needs per-task heaps or atomic reference counts instead of the global lock).
4. Native TLS, so `https` does not need `curl`; Windows networking.
5. Editor support: a VS Code extension with syntax colouring for `.plain` files.
6. A Homebrew formula, so installing is `brew install plain`.
7. Speed: direct-threaded dispatch, inline caches for method calls.
8. Compiling to a standalone native binary (rather than bundling the interpreter).

# Plain roadmap

1.0.0: bytecode compiler and virtual machine, lists, maps, actions, `try` / `fail`,
`use`, built-in actions, interactive session, `plain check`, `plain build`, installer.

2.0.0: integers of any size and exact decimals, anonymous actions and closures,
classes with inheritance, tasks / channels / locks, a cycle collector, a web
client and server, a package manager with `plain.json` and `plain.lock`.

Candidates, largest effect first:

1. A package registry (a hosted index, so `plain install name` works for everyone) and version ranges.
2. Text templates: `say "Hello {name}"`.
3. Tasks that run on several cores (needs per-task heaps or atomic reference counts instead of the global lock).
4. Native TLS, so `https` does not need `curl`; Windows networking.
5. Editor support: a VS Code extension with syntax colouring for `.plain` files.
6. A Homebrew formula, so installing is `brew install plain`.
7. Speed: direct-threaded dispatch, inline caches for method calls.
8. Compiling to a standalone native binary (rather than bundling the interpreter).

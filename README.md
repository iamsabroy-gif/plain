# Plain

A programming language that reads like English, made for learning to program and for
seeing how data structures and algorithms really work. Programs run on a fast
virtual machine inside one small `plain` command with no dependencies.

```
set fruits to ["mango", "banana", "lychee"]
add "guava" to fruits

for each fruit in fruits
    say "I like", fruit
end

define factorial with n
    if n is at most 1 then
        give back 1
    end
    give back n * factorial(n - 1)
end

say "5 factorial is", factorial(5)
```

## Install

You do not need a compiler. Paste one line.

**Mac and Linux** (in Terminal):

```
curl -fsSL https://raw.githubusercontent.com/iamsabroy-gif/plain/main/install.sh | sh
```

**Windows** (in PowerShell: press the Windows key, type `PowerShell`, press Enter):

```
irm https://raw.githubusercontent.com/iamsabroy-gif/plain/main/install.ps1 | iex
```

Then close the window, open a new one, and try `plain -e "say 6 * 7"`.
(Windows support is new. If it gives you trouble, `wsl --install` and use the Mac and
Linux line inside it.) To build it yourself you need a C++ compiler: `make`, then use
`./build/plain`.

## Try it without installing

The browser playground (`web/`) runs Plain right in a web page: type a program, press
Run, or press "Watch it run" to step through it. Once it is published (see
[docs/DEVELOPER.md](docs/DEVELOPER.md#the-browser-playground)) the address will be
`https://iamsabroy-gif.github.io/plain/`.

## Your first minute

```
plain -e "say 6 * 7"            # run one line
plain lesson 1                  # the first lesson, with exercises that are checked
plain                           # type lines and see results
plain examples/tour.plain       # a tour of the language
plain visualize examples/sorting.plain     # watch a sort run, in a web page
plain practice two-sum          # a problem with hidden tests and hints
```

A child? Start with [Plain for kids](docs/KIDS.md). New to programming? `plain lesson 1` starts
ten lessons whose exercises Plain checks for you ([docs/CORE.md](docs/CORE.md) has the map).

## Commands

| Command | What it does |
|---|---|
| `plain program.plain` | Run a program |
| `plain` | Interactive session |
| `plain check program.plain` | Look for mistakes without running (`--beginner` lists advanced features) |
| `plain format program.plain` | Rewrite it in the standard style |
| `plain lesson [number]` | Ten beginner lessons, each with exercises that Plain checks |
| `plain visualize program.plain` | Make one web page that steps through the run and draws lists, recursion, trees and graphs (give two programs to step them side by side) |
| `plain count program.plain` | Report comparisons, swaps and calls |
| `plain growth program.plain action …` | Show how the work grows as the data grows (O(n), O(n²) …) |
| `plain compare program.plain a b` | Run two actions on the same data, side by side |
| `plain practice [problem]` | 50 problems, from arrays to dynamic programming, with hidden tests, hints and solutions |
| `plain lib [name]` | The built-in stack, queue, heap, tree, graph …, and how each is built |
| `plain build program.plain -o app` | Make a standalone program that runs without Plain installed |
| `plain --explain program.plain` | Show the tokens and bytecode, then run |
| `plain init`, `install`, `update`, `remove`, `list`, `search` | Packages, from the [shared index](registry/README.md), git or a folder, with version ranges like `#^1.2` |

## Read more

| | |
|---|---|
| [docs/KIDS.md](docs/KIDS.md) | **Plain for kids**: a friendly first guide with challenges to try |
| [docs/CORE.md](docs/CORE.md) | The beginner core, a lesson map, and names you can't use |
| [docs/LANGUAGE.md](docs/LANGUAGE.md) | Values, instructions, expressions, numbers, built-in actions, errors, the standard style |
| [docs/LEARNING.md](docs/LEARNING.md) | `visualize`, `count`, `growth`, `compare`, `practice` and the data-structure library |
| [docs/ADVANCED.md](docs/ADVANCED.md) | Closures, classes, tasks, networking, packages |
| [docs/APPS.md](docs/APPS.md) | **Making apps**: web sites and APIs (`use "web"`), programs with a window (`use "desktop"`) |
| [docs/DEVELOPER.md](docs/DEVELOPER.md) | For contributors: how it works, how to add things, the trace format, tests, releasing, gotchas |
| [docs/ROADMAP.md](docs/ROADMAP.md) | What is done and what comes next |
| [docs/pdf/](docs/pdf/) | All of the above as PDFs: `Plain-documentation.pdf` (everything) and `Plain-for-kids.pdf` (bigger type) |

## Good to know

- Every error says what happened, on which line (and shows the line), and what to try.
- `plain format` rewrites old spellings (`==`, `item 2 of xs`, `print` …) into one
  standard style, and never changes what a program does.
- Tracing costs nothing when it is off: the virtual machine has a normal copy of its
  loop and a watched copy, and ordinary runs use the first.
- Text can hold values: `say "Hello {name}, you have {length of xs} items"`.
- Make web sites (`use "web"`) and programs with a window (`use "desktop"`): see
  [docs/APPS.md](docs/APPS.md) and `examples/web_notes.plain`, `examples/desktop_todo.plain`.
- Editor support: [editors/vscode](editors/vscode) (colours, run, format, mistakes underlined).
- Windows has no networking or `plain install` yet; tasks run one at a time.
  The full list is in [docs/DEVELOPER.md](docs/DEVELOPER.md#limits).

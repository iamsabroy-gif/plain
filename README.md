# Plain

A programming language that reads like English. Programs are compiled to
bytecode and run on a fast virtual machine, all inside one small `plain`
command with no dependencies.

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

You need a C++ compiler (on a Mac: `xcode-select --install`).

```
cd ~/projects/plain
sh install.sh
```

This builds Plain, runs the tests and copies the `plain` command to a folder
on your PATH. To build without installing, run `make` and use `./build/plain`.

## Use

| Command | What it does |
|---|---|
| `plain program.plain` | Run a program |
| `plain` | Interactive session: type a line, see the result |
| `plain check program.plain` | Look for mistakes without running |
| `plain build program.plain -o app` | Make a standalone program that runs without Plain installed |
| `plain --explain program.plain` | Show the tokens and the bytecode, then run |
| `plain -e "say 1 + 2"` | Run one line |

Try `plain examples/tour.plain`.

## The language

Each instruction goes on its own line. Blocks close with `end`. Lines that
start with `note:` and anything after `#` are comments.

### Values

| Kind | Examples |
|---|---|
| Integer | `42`, `-7`, `2 ^ 100` (any size; never overflows) |
| Float | `3.14`, `1e-3` (64-bit, fast) |
| Decimal | `19.99d`, `0.1d` (exact; for money) |
| Text | `"hello"` (use `\n` for a new line, `\"` for a quote) |
| True/false | `true`, `false` |
| Nothing | `nothing` |
| List | `[1, 2, 3]` (items are counted from 1) |
| Map | `{name: "Asha", age: 30}` |
| Action | `action with x gives x * 2` |
| Object | `new Account(100d)` |

### Instructions

| To do this | Write |
|---|---|
| Store a value | `set total to 0` |
| Show values | `say "Total is", total` (also `show`, `print`) |
| Ask for input | `ask "Your age?" into age` |
| Change a number | `increase total by 5`, `decrease total by 1` |
| Add to a list, number or text | `add "guava" to fruits` |
| Remove from a list or map | `remove "guava" from fruits` |
| Change a list item | `set item 1 of xs to 9` or `set xs[1] to 9` |
| Change a map entry | `set person's age to 31` or `set person["age"] to 31` |
| Decide | `if … then` / `otherwise if … then` / `otherwise` / `end` |
| Loop a number of times | `repeat 3 times` … `end` |
| Loop while true | `while count is less than 10` … `end` |
| Loop over a list, text or map | `for each fruit in fruits` … `end` |
| Count | `for i from 1 to 10` … `end`, or `for i from 10 to 1 by -1` |
| Leave a loop / next round | `stop`, `skip` |
| Define an action | `define area with w and h` … `give back w * h` … `end` |
| Call an action | `area(2, 3)` or `call greet with "Asha"` |
| Handle a problem | `try` … `on error problem` … `end` |
| Raise a problem | `fail with "Insufficient balance"` |
| Define a class | `class Dog extends Animal` … `init with name` … `define speak` … `end` |
| Load another file or package | `use "mathtools"` (a file next to this one, or an installed package) |

### Expressions

| Meaning | Write |
|---|---|
| Maths | `+ - * / % ^`, or `plus`, `minus`, `multiplied by`, `divided by`, `modulo` |
| Compare | `is`, `is not`, `is greater than`, `is less than`, `is at least`, `is at most`, or `== != < > <= >=` |
| Membership | `fruits contains "mango"`, `"mango" is in fruits`, `x is not in xs` |
| Logic | `and`, `or`, `not` |
| Size | `length of fruits` |
| Item | `item 2 of fruits`, `fruits[2]`, `person's name`, `person["name"]` |
| Join text | `"Hello, " + name` (text plus anything gives text) |

### Variables and actions

- A `set` at the top level creates a variable the whole program can see.
- Inside an action, `set` changes a variable of the action around it, or a
  top-level variable created above, if one has that name; otherwise it creates
  a variable that exists only inside that action.
- Actions can be called from anywhere in the file, even above their `define`.

### Numbers

| Kind | Written | Behaviour |
|---|---|---|
| Integer | `7`, `-3` | Exact, any size. `9223372036854775807 + 1` is `9223372036854775808`. |
| Float | `7.5`, `1e9` | 64-bit, fast, rounded like in most languages. |
| Decimal | `7.5d` | Exact base-10. `0.1d + 0.2d` is `0.3`. `+ - *` are exact; `/` keeps 28 significant digits. |

Integer and float mix freely (the answer is a float). A decimal mixes with
integers, but mixing it with a float is an error, because it would quietly lose
exactness. Choose with `integer(x)`, `float(x)`, `decimal(x)`. `quotient(a, b)`
divides rounding down; `fixed(x, 2)` gives text with exactly 2 digits after the point;
`round(x, 2)`, `floor`, `ceiling` and `whole` keep the kind of number.
`10 / 5` is the integer `2`; `10 / 4` is `2.5`.

### Anonymous actions and closures

```
set double to action with x gives x * 2
say map_each([1, 2, 3], double)            # [2, 4, 6]

define make_counter
    set count to 0
    define bump
        increase count by 1
        give back count
    end
    give back bump
end
set next to make_counter()
say next(), next()                         # 1 2
```

An action can be stored, passed and returned. It keeps the variables of the
action it was made in (one counter per `make_counter()` call). Loop counters are
one variable per loop, not one per round. `map_each`, `keep_if`, `find_first`,
`combine(items, start, action)` and `sort_by(items, action)` take actions.
A longer anonymous action can use a block: `action with a, b` … `give back …` … `end`.

### Classes and methods

```
class Animal
    init with name
        set me's name to name
    end
    define speak
        say me's name + " makes a sound"
    end
end

class Dog extends Animal
    init with name
        parent's init(name)
    end
    define speak
        say me's name + " barks"
    end
end

set rex to new Dog("Rex")
rex's speak()
say is_a(rex, Animal)            # true
```

`init` runs when an object is made. `me` is the object, `parent's name(...)`
calls the parent class's action. An object can define `to_text` (no values) to
say how it is shown by `say`. Fields are created by `set me's field to …`.

### Tasks, channels and locks

```
set results to channel()
define work with id
    send(results, id * 10)
end
set t to start_task(work, 4)
say receive(results)               # 40
wait_for(t)
```

`start_task(action, values…)` runs an action alongside the program;
`wait_for(task)` gives its answer (or its error). `channel()`, `send`, `receive`
(waits; `nothing` once the channel is closed and empty), `close_channel`, and
`lock()` with `acquire` / `release` / `try_acquire`. Tasks are real operating-system
threads that take turns running Plain code (a global interpreter lock, like Python),
so they overlap while waiting for files, the network or `wait`, but do not run
Plain code on several cores at once. Use a lock around a change that must not be
interleaved, such as `set counter to counter + 1`.

### Networking

| Action | What it does |
|---|---|
| `http_get(url [, headers])` | `{status, body, headers}`. `http://` is built in; `https://` needs the `curl` program. |
| `http_post(url, body [, headers])`, `http_request(method, url, body, headers)` | A list or map body is sent as JSON. |
| `tcp_listen(port)`, `tcp_port(server)`, `tcp_accept`, `tcp_connect(host, port)` | Plain TCP. A connection is a number. |
| `tcp_send`, `tcp_receive`, `tcp_receive_line`, `tcp_close` | |
| `http_serve(server, handler [, how_many])` | A small web server: `handler` gets `{method, path, query, headers, body}` and gives back text, a list/map (sent as JSON), or `{status, body, headers}`. |
| `url_encode`, `url_decode` | |

### Packages

A project can list what it needs in `plain.json`:

```
{ "name": "shop", "version": "1.0.0", "main": "main.plain",
  "dependencies": { "greeter": "someone/plain-greeter#v1.2.0", "tools": "../tools" } }
```

| Command | Does |
|---|---|
| `plain init` | Writes `plain.json`. |
| `plain install` | Installs everything `plain.json` lists, into `./plain_modules`, and writes `plain.lock`. |
| `plain install user/repo[#version]` | Also: a git address, or a folder. Added to `plain.json`. `--as name` picks the name, `--global` installs for every project. |
| `plain update [name]` | Fetches newer versions, ignoring `plain.lock`. |
| `plain remove name`, `plain list` | |

`plain.lock` pins each git package to the exact commit, so an install on another
computer gets the same code. In a program, `use "greeter"` loads the package's
`main` file (from its `plain.json`, or `main.plain`); `use "greeter/extra"` loads
another file of it. A package that needs other packages gets them installed too.
There is no central registry yet: `plain install name` looks the name up in a JSON
file you maintain (`~/.plain/registry.json` or `PLAIN_REGISTRY`).
`plain build` bundles the program and its packages into one executable.

### Built-in actions

| Area | Actions |
|---|---|
| Maths | `sqrt abs floor ceiling round(x, digits) power min max sum random(low, high) sin cos tan exp log pi() whole fraction` |
| Number kinds | `integer float decimal quotient fixed is_integer is_float is_decimal` |
| Text | `text number uppercase lowercase trim split join replace find starts_with ends_with slice` |
| Lists | `sort reverse range(from, to, step) first last insert(list, position, value) index_of slice copy` |
| Maps | `keys values has_key copy` |
| Actions on lists | `map_each keep_if find_first combine sort_by` |
| Objects | `is_a(object, Class)` |
| Memory | `collect_garbage()` frees groups of objects that only refer to each other (this also happens by itself) |
| JSON | `to_json(value [, indent])`, `from_json(text)` (whole numbers stay integers) |
| Files | `read_file read_lines write_file append_file file_exists delete_file` |
| System | `clock() time_now() date_text() wait(seconds) arguments() environment(name) exit(code) type_of(value)` |

### Error messages

Problems are reported as sentences, with a suggestion where possible:

```
Oops! Line 3: I don't know anything called 'totl'. Did you mean 'total'?
```

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

Numbers are in `src/bigint.hpp` and `src/numeric.hpp`, the built-in actions in
`src/builtins.hpp` (networking included), tasks in `src/tasks.hpp`, the package
manager in `src/pkg.hpp`, and the command line in `src/main.cpp`.
`plain --explain file.plain` prints the tokens and bytecode for any program.

## Tests

`make test` runs every program in `tests/cases` and compares its output with
the saved `.expected` file, then runs the package-manager test.

## Limits

- Tasks run one at a time (see above); there is no parallel speed-up.
- Decimals do not mix with floats, and have no `sqrt`/`sin`; use `float(x)`.
- `plain build` copies this executable plus your source: the result is standalone,
  but it contains the interpreter, not machine code made from your program.
- `https` needs the `curl` program; Windows has no networking or `plain install` yet.
- macOS and Windows builds are made from the same portable C++17 code, but the
  tests so far ran on Linux only.

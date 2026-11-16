# The Plain language

Everything a beginner needs. Classes, closures, tasks, networking and packages are in
[ADVANCED.md](ADVANCED.md); the fifteen-word starting point is in [CORE.md](CORE.md).
Each instruction goes on its own line. Blocks close with `end`. Lines that start with
`#` are comments.

## Values

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

## The standard style

There are often several ways to write the same thing. `plain format` rewrites a
program into one of them, and the documentation and examples use it:

| Meaning | Standard | Also accepted (and rewritten) |
|---|---|---|
| Compare | `is`, `is not`, `is less than`, `is greater than`, `is at most`, `is at least` | `== != < > <= >=`, `is equal to` |
| Logic | `and`, `or`, `not` | |
| Maths | `+ - * / % ^` | `plus`, `minus`, `multiplied by`, `divided by`, `modulo` |
| Item of a list | `xs[i]` | `item i of xs` |
| Entry of a map | `person's age` (fixed name), `scores[name]` (any other) | `person["age"]` |
| Membership | `xs contains x` | `x is in xs` |
| Show | `say` | `show`, `print` |
| Call an action | `greet("Asha")` | `call greet with "Asha"` |
| Comment | `# like this` | `note: like this` |

Four-space indents, one space around operators. `plain format file.plain` tidies in
place; `--check` only reports (exit status 1 if the file would change) and `--print`
shows the result. Formatting never changes what a program does. Lines it cannot
read are left as they are, with a warning.

## Instructions

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

## Expressions

| Meaning | Write |
|---|---|
| Maths | `+ - * / % ^`, or `plus`, `minus`, `multiplied by`, `divided by`, `modulo` |
| Compare | `is`, `is not`, `is greater than`, `is less than`, `is at least`, `is at most`, or `== != < > <= >=` |
| Membership | `fruits contains "mango"`, `"mango" is in fruits`, `x is not in xs` |
| Logic | `and`, `or`, `not` |
| Size | `length of fruits` |
| Item | `item 2 of fruits`, `fruits[2]`, `person's name`, `person["name"]` |
| Join text | `"Hello, " + name` (text plus anything gives text) |

## Variables and actions

- A `set` at the top level creates a variable the whole program can see.
- Inside an action, `set` changes a variable of the action around it, or a
  top-level variable created above, if one has that name; otherwise it creates
  a variable that exists only inside that action.
- Actions can be called from anywhere in the file, even above their `define`.
- After `for i from 1 to 10`, `i` is `10`: the last number the loop counted.
- `if` and `while` treat `false`, `nothing`, `0`, and an empty list, text or map as
  false; every other value is true.
- Built-in actions like `sort`, `reverse`, `uppercase` and `replace` give back a new
  value and leave the old one as it was, so keep the answer: `set xs to sort(xs)`.
  A line that calls one and throws the answer away is reported as a mistake.
- A reserved word (`item`, `times`, `length`, `action`, `to` …) can't be a name,
  and the error says what the word is for and suggests another name.

## Numbers

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

## Built-in actions

| Area | Actions |
|---|---|
| Maths | `sqrt abs floor ceiling round(x, digits) power min max sum random(low, high) sin cos tan exp log pi() whole fraction` |
| Number kinds | `integer float decimal quotient fixed is_integer is_float is_decimal` |
| Text | `text number uppercase lowercase trim split join replace find starts_with ends_with slice` |
| Lists | `sort reverse range(from, to, step) first last insert(list, position, value) pop(list) pop_at(list, position) index_of slice copy` |
| Maps | `keys values has_key copy` |
| Actions on lists | `map_each keep_if find_first combine sort_by` |
| Objects | `is_a(object, Class)` |
| Memory | `collect_garbage()` frees groups of objects that only refer to each other (this also happens by itself) |
| JSON | `to_json(value [, indent])`, `from_json(text)` (whole numbers stay integers) |
| Files | `read_file read_lines write_file append_file file_exists delete_file` |
| System | `clock() time_now() date_text() wait(seconds) arguments() environment(name) exit(code) type_of(value)` |

## Error messages

Problems are reported as sentences: what happened, on which line (shown with the
line itself), and what to try:

```
Oops! Line 3: I don't know anything called 'totl'. Did you mean 'total'?
     3 | say totl
```


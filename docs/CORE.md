# The beginner core

You can learn to program with fifteen words. Everything else in Plain is real and
stays available, but it is marked **advanced** and is not needed until lesson 8.

## The fifteen

| # | Write | To |
|---|---|---|
| 1 | `set x to 5` | keep a value |
| 2 | `say x` | show a value |
| 3 | `ask "Name?" into name` | get something typed in |
| 4 | `if … then` | decide |
| 5 | `otherwise` | the other case of an `if` |
| 6 | `end` | close any block |
| 7 | `repeat 3 times` | do something a number of times |
| 8 | `while …` | do something as long as it stays true |
| 9 | `for each x in list` | do something for every item |
| 10 | `for i from 1 to 10` | count |
| 11 | `define name with a, b` | make your own action |
| 12 | `give back x` | the answer of an action |
| 13 | `add x to list` | grow a list (and `remove x from list`) |
| 14 | `length of list` | how many items |
| 15 | lists `[1, 2, 3]` and maps `{name: "Asha"}` | keep many values together |

Plus: the comparisons `is`, `is not`, `is less than`, `is greater than`,
`is at most`, `is at least`; the logic words `and`, `or`, `not`; the maths
`+ - * / %`; items as `list[2]` and `person's name`; and the actions `sqrt`, `round`,
`sort`, `range`, `text`, `number`, `uppercase`, `split`, `join`.

`plain check --beginner program.plain` lists anything beyond this, so a lesson can
be checked against the core.

## Advanced (lesson 8 onwards)

Classes (`class`, `extends`, `new`, `me`, `parent`), anonymous actions (`action …
gives`), errors (`try`, `on error`, `fail with`), other files and packages (`use`,
`plain install`), tasks and channels, networking, files, JSON. The data-structure
library (`use "dsa"`) is written with classes, so using it is lesson 8; reading how
it is built (`plain lib stack`) is a good lesson 9.

## Lessons

Each lesson has exercises that Plain checks: `plain lesson 1` starts the first.

| Lesson | You learn | Try |
|---|---|---|
| 1 Values | `say`, `set`, numbers and text, `ask` | `plain -e "say 6 * 7"` |
| 2 Decisions | `if`, `otherwise`, comparisons, `and`/`or` | A number guessing check |
| 3 Loops | `repeat`, `while`, `for i from`, `for each` | Times tables; `plain visualize` any loop |
| 4 Lists | `[ ]`, `add`, `length of`, `list[i]`, `sort` | Biggest and smallest; `plain practice move-zeros` |
| 5 Actions | `define`, `give back`, calling | `plain practice is-palindrome` |
| 6 Maps and text | `{ }`, `person's name`, `split`, `join` | Word counts; `plain practice first-unique-char` |
| 7 Thinking in steps | an action that calls itself; searching and sorting by hand | `plain visualize examples/sorting.plain`, `plain practice sum-digits` |
| 8 Data structures | stack, queue, heap, tree, graph | `use "dsa"`; `plain practice valid-brackets` |
| 9 Cost | counting work, Big-O | `plain compare`, `plain growth` |
| 10 Under the hood | how a stack or a graph is built | `plain lib graph` |

## Four habits that make learning easier

1. **One way to write each thing.** Run `plain format file.plain` and your program
   comes out in the standard style (comparisons in words, `list[i]`, `say`).
2. **Read the error.** Every error says what happened, on which line (and shows the
   line), and what to try.
3. **Watch it run.** When a loop or a list does something unexpected, `plain visualize
   file.plain` and step through it.
4. **Count before you argue.** "Which is faster?" is answered by `plain count`
   and `plain compare`, not by guessing.

## Names that cannot be variables

Some words are part of Plain itself, so they can't also be names: `item`, `times`,
`length`, `set`, `to`, `from`, `by`, `of`, `in`, `end`, `back`, `each`, `add`,
`remove`, `at`, `most`, `least`, `less`, `greater`, `than`, `equal`, `contains`,
`new`, `me`, `parent`, `action`, `gives`, `class`, `extends` and the other words in
the instruction table. The error names the word, says what it is for, and
suggests another name (for `item`: `entry` or `thing`).

# Learning data structures and algorithms

Plain is built so that a learner can see what their own code does, with no drawing
code and no special syntax.

Plain is built so that a learner can see what their own code does, with no
drawing code and no special syntax.

```
plain visualize examples/sorting.plain       # writes sorting.html: open it in a browser
plain count     examples/sorting.plain       # comparisons, swaps, calls
plain compare   examples/sorting.plain bubble_sort merge_sort
plain growth    examples/sorting.plain bubble_sort merge_sort --html growth.html
plain practice  two-sum
```

**Visualize.** `plain visualize` runs the program once, recording every line that
runs, and writes **one standalone HTML file** (no server, nothing loaded from the
internet). The page has play, pause, step and a slider, shows the line that has
just run, and draws what the variables hold *from the values themselves*:

| Your program has | The page shows |
|---|---|
| A list of numbers | Bars. Items being compared are yellow; items that moved or changed are red. A variable named `i`, `j`, `low`, `mid` … that points into the list is drawn under its item |
| A list of anything else, a list of lists | Boxes, a grid |
| An action that calls itself | The call stack, and the tree of calls with each answer as it returns |
| Maps with `value` / `left` / `right` | A tree. With `value` / `next`, a linked chain. With `children`, a general tree |
| A map of lists whose items are its own keys | A graph. Nodes held by variables are ringed and named; other maps and lists of nodes (`seen`, `order`) tint them |
| `Stack`, `Queue`, `Heap` from the library | The live items only; a heap as a tree |

To see only some variables, add a comment line `# watch: xs, total`: comments
are not code, so the language does not change. Steps inside the built-in library
are folded into the line that called them (`--into-library` shows them). Very long
runs are cut at 6,000 steps (`--max-steps`).

**Count.** `plain count` reports comparisons (every `<`, `is`, `is at most` … that
ran), swaps (two list items trading places), list writes, calls and VM
instructions, so "which sort is better?" is answered with numbers instead of
seconds. The built-in `sort()` is a single step to Plain, so write the sort yourself
to study it.

**Growth and compare.** `plain growth file action …` runs each action (it must take
one value) on n = 10, 100, 1000 and 10000 items (`--sizes`; `--input` is `list`,
`sorted`, `reversed`, `number` or `text`; `--measure` is `instructions`,
`comparisons`, `swaps`, `writes` or `calls`) and says what curve the work follows, for
example "grows like O(n^2): 10x more data meant about 95x more work". A size that
would take more than 200 million steps is skipped and estimated from the smaller
sizes (hollow points in the chart). `--html chart.html` draws the curves, with a
straight/log switch. `plain compare file a b` runs actions on identical data, checks
that they give the same answer, and shows their work side by side.

**Practice.** `plain practice` lists 50 problems (arrays, strings, recursion,
sorting, searching, stacks, queues, trees, graphs, then dynamic programming, heaps, tries,
union-find, backtracking, intervals and weighted graphs). `plain practice two-sum` writes
`two-sum.plain` with the problem as comments; edit it and run the same command to
check it against examples and hidden tests. Hidden tests are reported by number
(and, for edge cases, by what they check) but never shown. `--hint` gives hints one
step at a time, `--solution` shows a reference solution with an explanation once you
have solved it or used the hints (`--give-up` to skip that). The result also compares
how much work your solution did with the reference's. Progress is kept in
`.plain-practice` in the folder. Each problem is a Plain file in `lib/problems`; its
reference solution is real code, and `plain practice --selftest` checks every
reference against every test.

## The data-structure library

`use "dsa"` (or one part: `use "stack"`) gives stack, queue, deque, heap, linked
list, tree and graph, and `plain lib stack` prints how each is built: every part is
**written in Plain** in `lib/`, so a student can read it. `plain lib stack --copy`
puts an editable copy next to your program, and your copy is used instead.

| Part | Names |
|---|---|
| `stack` | `new Stack()`: `push`, `pop`, `peek`, `is_empty`, `size` |
| `queue` | `new Queue()`: `enqueue`, `dequeue`, `front`, `is_empty`, `size` |
| `deque` | `new Deque()`: `push_front`, `push_back`, `pop_front`, `pop_back`, `peek_front`, `peek_back` |
| `unique` | `new Unique()` (a set; `set` is already a Plain word): `put`, `has`, `drop`, `items`, `combined_with`, `shared_with`, `without` |
| `heap` | `new Heap()`: `put`, `smallest`, `peek`; `new MaxHeap()`: `put`, `biggest`; `new PriorityQueue()`: `put(value, priority)`, `take` |
| `linkedlist` | `new LinkedList()`: `append`, `prepend`, `has`, `drop`, `reverse_in_place`, `to_list` |
| `tree` | `new Tree()` (a search tree): `put`, `has`, `smallest`, `biggest`, `height`, `in_order`, `pre_order`, `post_order`, `level_order` |
| `ringbuffer` | `new RingBuffer(capacity)`: `put`, `put_overwrite`, `take`, `peek`, `is_full`, `to_list` |
| `counter` | `new Counter()` (a multiset): `put`, `count_of`, `total`, `distinct`, `most_common(k)` |
| `avl` | `new AVLTree()` (a search tree that keeps itself balanced): `put`, `has`, `height`, `in_order`, `is_balanced` |
| `trie` | `new Trie()`: `put`, `has`, `starts_with`, `words_with_prefix` |
| `unionfind` | `new UnionFind(n)`: `connect`, `same_group`, `find_root`, `size_of`, `groups` |
| `lrucache` | `new LRUCache(capacity)`: `put`, `get_value`, `has`, `keys` (newest first) |
| `fenwick` | `new FenwickTree(n)`: `add_at`, `prefix_sum`, `range_sum` |
| `segmenttree` | `new SegmentTree(numbers, "sum" or "min")`: `update`, `query(a, b)` |
| `graph` | `new Graph()`, `new DirectedGraph()`: `add_edge`, `add_weighted_edge`, `neighbors`, `bfs`, `dfs`, `shortest_path`, `has_path`, `distances`, `topological_order` |

Methods are called as `pile's push(3)`. The tree and linked-list nodes are plain
maps, so `plain visualize` draws them.


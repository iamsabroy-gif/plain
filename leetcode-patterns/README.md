# LeetCode problems by algorithm pattern

All 4115 LeetCode problems (as of November 2026), each sorted into one algorithm pattern
and a sub-pattern, with the other patterns it touches listed as "also".

| File | What it is |
|---|---|
| [`PATTERNS.md`](PATTERNS.md) | Every problem, grouped by pattern then sub-pattern, with links. Read this on GitHub. |
| [`patterns.csv`](patterns.csv) | The same as a spreadsheet: id, title, difficulty, premium, pattern, sub-pattern, also, url, tags. |
| [`patterns.json`](patterns.json) | The same as JSON, for scripts. |
| [`web/`](web/) | A searchable page: pick a pattern, narrow by sub-pattern / difficulty / title. Serve it with `python3 -m http.server -d web`. |
| [`classify.py`](classify.py) | The rules that do the sorting. Run `python3 classify.py` to rebuild every file above. |
| [`data/problems.json`](data/problems.json) | Every problem with LeetCode's own topic tags, the input to `classify.py`. |

## How problems are placed

1. **Hand-checked** (~230 problems): the well-known interview problems (Blind 75, NeetCode 150, Grind 169),
   where LeetCode's tags point at the wrong teaching idea. Example: *Trapping Rain Water* is tagged
   with DP, stack and monotonic stack, but it is listed under Two Pointers.
2. **Rules** (~3,850): LeetCode's topic tags, checked from the most telling technique (KMP, union find,
   topological sort, segment tree...) down to the most generic (array, string). The first match is the main pattern.
3. **Title guess** (~40): brand-new problems LeetCode has not tagged yet. 13 could not be placed at all.

Rules are a strong first sort, not a proof: a problem tagged both DP and binary search may be best solved
either way. When you disagree, add the problem to `OVERRIDES` in `classify.py` and run it again.

## Patterns

| Pattern | Problems | Use it when |
|---|---:|---|
| Two Pointers | 142 | Sorted array or string; walk two indexes toward each other or in step. |
| Sliding Window | 153 | Best / count of contiguous subarrays or substrings under a condition. |
| Fast & Slow Pointers | 10 | Cycle detection, middle of a list, repeating sequences. |
| Prefix Sum & Difference Array | 127 | Many range-sum questions; subarray sums equal to K. |
| Hashing & Counting | 265 | Seen-before lookups, frequencies, grouping, anagrams. |
| Intervals & Sweep Line | 43 | Merge / insert / overlap of ranges, meeting rooms, events over time. |
| Binary Search | 181 | Sorted data, or 'smallest X that works' (search on the answer). |
| Stack | 57 | Matching brackets, parsing expressions, undo, nested structure. |
| Monotonic Stack / Queue | 83 | Next greater / smaller element, sliding-window max, histograms. |
| Linked List | 64 | Reverse, merge, reorder, remove nodes in place. |
| Tree Traversal (DFS / BFS) | 210 | Binary trees and BSTs: recursion, level order, paths, LCA. |
| Heap / Top-K / K-way Merge | 136 | Kth largest, top K frequent, running median, merge K sorted. |
| Graph & Grid Traversal (BFS / DFS) | 99 | Islands, flood fill, connected components, unweighted shortest path. |
| Topological Sort | 34 | Ordering with prerequisites; cycle check in a directed graph. |
| Union Find (Disjoint Set) | 69 | Merging groups, connectivity as edges arrive, redundant edges. |
| Shortest Path (Dijkstra / Bellman-Ford / Floyd) | 47 | Weighted graphs: cheapest / fastest route. |
| Advanced Graph | 36 | MST, Euler paths, strongly connected components, bipartite, flows, bridges. |
| Backtracking | 105 | Generate all subsets / permutations / combinations; N-Queens, Sudoku. |
| Dynamic Programming | 556 | Overlapping subproblems: count ways, min / max cost, best subsequence. |
| Greedy | 224 | A local best choice is provably globally best (often after sorting). |
| Trie | 42 | Prefix search, word dictionaries, bitwise-XOR maximisation. |
| Segment Tree / Fenwick Tree / Ordered Set | 102 | Range queries with updates, counting smaller elements. |
| String Matching & Hashing | 72 | KMP, Z-function, rolling hash, suffix arrays, Manacher. |
| Bit Manipulation | 118 | XOR tricks, bit counting, masks, powers of two. |
| Math & Number Theory | 343 | Primes, GCD, modular arithmetic, combinatorics, geometry, games. |
| Design (Data Structures) | 42 | Build a class: LRU cache, iterators, time-based stores. |
| Matrix & Simulation | 103 | Follow the rules step by step; spiral, rotate, game boards. |
| Sorting & Custom Ordering | 39 | Sort first, custom comparators, counting / bucket sort. |
| Arrays & Strings (Basics) | 182 | Direct scans, enumeration, string building. |
| Database (SQL / Pandas) | 338 | SQL queries and Pandas DataFrame problems. |
| JavaScript | 67 | Closures, promises, debounce, the '30 Days of JavaScript' set. |
| Concurrency | 9 | Threads, locks, semaphores. |
| Shell | 4 | Bash one-liners. |
| Not Tagged Yet | 13 | Very new problems LeetCode has not tagged; placed by title where possible. |

#!/usr/bin/env python3
"""Sort every LeetCode problem into one algorithm pattern.

Input : data/problems.json  (every problem with LeetCode's own topic tags)
Output: patterns.json, patterns.csv, PATTERNS.md

How a problem is placed
-----------------------
1. A hand-checked answer in OVERRIDES wins (the well-known interview problems,
   where LeetCode's tags point at the wrong idea).
2. Otherwise the RULES below run top to bottom and the first one that matches
   gives the main pattern. They go from the most telling technique (KMP, union
   find, topological sort ...) down to the most generic (array, string).
   A second, smaller step picks a sub-pattern inside the main one.
3. Every other pattern a problem's tags point at is kept as "also".

Run:  python3 classify.py
"""
import csv
import json
import os
import re
from collections import Counter, defaultdict

HERE = os.path.dirname(os.path.abspath(__file__))

# ---------------------------------------------------------------- patterns
# (key, name, one-line "use it when")
PATTERNS = [
    ("two-pointers", "Two Pointers", "Sorted array or string; walk two indexes toward each other or in step."),
    ("sliding-window", "Sliding Window", "Best / count of contiguous subarrays or substrings under a condition."),
    ("fast-slow", "Fast & Slow Pointers", "Cycle detection, middle of a list, repeating sequences."),
    ("prefix-sum", "Prefix Sum & Difference Array", "Many range-sum questions; subarray sums equal to K."),
    ("hashing", "Hashing & Counting", "Seen-before lookups, frequencies, grouping, anagrams."),
    ("intervals", "Intervals & Sweep Line", "Merge / insert / overlap of ranges, meeting rooms, events over time."),
    ("binary-search", "Binary Search", "Sorted data, or 'smallest X that works' (search on the answer)."),
    ("stack", "Stack", "Matching brackets, parsing expressions, undo, nested structure."),
    ("monotonic", "Monotonic Stack / Queue", "Next greater / smaller element, sliding-window max, histograms."),
    ("linked-list", "Linked List", "Reverse, merge, reorder, remove nodes in place."),
    ("tree", "Tree Traversal (DFS / BFS)", "Binary trees and BSTs: recursion, level order, paths, LCA."),
    ("heap", "Heap / Top-K / K-way Merge", "Kth largest, top K frequent, running median, merge K sorted."),
    ("graph", "Graph & Grid Traversal (BFS / DFS)", "Islands, flood fill, connected components, unweighted shortest path."),
    ("topo-sort", "Topological Sort", "Ordering with prerequisites; cycle check in a directed graph."),
    ("union-find", "Union Find (Disjoint Set)", "Merging groups, connectivity as edges arrive, redundant edges."),
    ("shortest-path", "Shortest Path (Dijkstra / Bellman-Ford / Floyd)", "Weighted graphs: cheapest / fastest route."),
    ("advanced-graph", "Advanced Graph", "MST, Euler paths, strongly connected components, bipartite, flows, bridges."),
    ("backtracking", "Backtracking", "Generate all subsets / permutations / combinations; N-Queens, Sudoku."),
    ("dp", "Dynamic Programming", "Overlapping subproblems: count ways, min / max cost, best subsequence."),
    ("greedy", "Greedy", "A local best choice is provably globally best (often after sorting)."),
    ("trie", "Trie", "Prefix search, word dictionaries, bitwise-XOR maximisation."),
    ("range-query", "Segment Tree / Fenwick Tree / Ordered Set", "Range queries with updates, counting smaller elements."),
    ("string-matching", "String Matching & Hashing", "KMP, Z-function, rolling hash, suffix arrays, Manacher."),
    ("bit", "Bit Manipulation", "XOR tricks, bit counting, masks, powers of two."),
    ("math", "Math & Number Theory", "Primes, GCD, modular arithmetic, combinatorics, geometry, games."),
    ("design", "Design (Data Structures)", "Build a class: LRU cache, iterators, time-based stores."),
    ("matrix-sim", "Matrix & Simulation", "Follow the rules step by step; spiral, rotate, game boards."),
    ("sorting", "Sorting & Custom Ordering", "Sort first, custom comparators, counting / bucket sort."),
    ("array-string", "Arrays & Strings (Basics)", "Direct scans, enumeration, string building."),
    ("database", "Database (SQL / Pandas)", "SQL queries and Pandas DataFrame problems."),
    ("javascript", "JavaScript", "Closures, promises, debounce, the '30 Days of JavaScript' set."),
    ("concurrency", "Concurrency", "Threads, locks, semaphores."),
    ("shell", "Shell", "Bash one-liners."),
    ("uncategorized", "Not Tagged Yet", "Very new problems LeetCode has not tagged; placed by title where possible."),
]
NAME = {k: n for k, n, _ in PATTERNS}
ORDER = {k: i for i, (k, _, _) in enumerate(PATTERNS)}


# --------------------------------------------------------- tag shorthands
STRING_MATCH = {"string-matching", "rolling-hash", "hash-function", "knuth-morris-pratt-algorithm", "z-algorithm",
                "suffix-array", "suffix-automaton", "suffix-tree", "manacher", "aho-corasick-algorithm",
                "boyer-moore-string-search-algorithm", "palindromic-tree", "lyndon-factorization",
                "lexicographically-minimal-string-rotation"}
SHORTEST = {"shortest-path", "dijkstra", "bellman-ford-algorithm", "floyd-warshall-algorithm", "0-1-bfs",
            "a-search", "heuristic-search", "k-shortest-path", "successive-shortest-path-algorithm"}
ADV_GRAPH = {"minimum-spanning-tree", "prims-algorithm", "kruskals-algorithm", "boruvkas-algorithm",
             "eulerian-circuit", "eulerian-path", "eulerian-graph", "semi-eulerian-graph",
             "strongly-connected-component", "kosarajus-algorithm", "tarjans-scc-algorithm", "biconnected-component",
             "bridge-graph", "articulation-point", "bipartite-graph", "graph-coloring", "flow-network",
             "maximum-flow", "minimum-cost-flow", "minimum-cut", "matching-graph", "maximum-matching",
             "perfect-matching", "hungarian-algorithm", "edmonds-karp-algorithm", "dinics-algorithm",
             "push-relabel-algorithm", "mpm-algorithm", "hamiltonian-path", "planar-graph"}
RANGE = {"segment-tree", "binary-indexed-tree", "sqrt-decomposition", "treap", "splay-tree", "sparse-table",
         "range-minimum-maximum-query", "persistent-data-structure", "li-chao-tree", "k-d-tree", "cartesian-tree"}
TREE = {"tree", "binary-tree", "binary-search-tree", "lowest-common-ancestor", "binary-lifting"}
GRAPH = {"graph", "depth-first-search", "breadth-first-search", "bidirectional-search", "directed-acyclic-graph"}
MATH = {"math", "number-theory", "combinatorics", "geometry", "game-theory", "brainteaser", "probability-and-statistics",
        "greatest-common-divisor", "euclidean-algorithm", "prime-factorization", "sieve-theory", "primality-test",
        "prime-number-sieve", "fermats-little-theorem", "least-common-multiple", "polygons", "zero-sum-game",
        "minimax-algorithm", "nim-game", "sprague-grundy-theorem", "impartial-game", "pigeonhole-principle",
        "inclusion-exclusion-principle", "linear-algebra", "bezouts-lemma", "extended-euclidean-algorithm",
        "eulers-totient-function", "eulers-theorem", "convex-hull", "newtons-method", "nearest-pair-of-points",
        "minimum-enclosing-circle", "triangulation", "randomized", "reservoir-sampling", "rejection-sampling"}
KNAPSACK = {"knapsack-problem", "0-1-knapsack", "complete-knapsack", "mixed-knapsack", "multiple-knapsack"}
SORT = {"sorting", "counting-sort", "bucket-sort", "radix-sort", "quickselect", "quicksort", "merge-sort",
        "bubble-sort", "tournament-sort", "timsort", "sort"}

INTERVAL_TITLE = re.compile(r"interval|meeting room|overlap|employee free time|my calendar|balloons with|"
                            r"car pooling|range module|skyline|rectangle area", re.I)


def _rules(t, title, cat, diff):
    """Yield (pattern, why) for every pattern this problem fits, most telling first."""
    if cat in ("database", "javascript", "concurrency", "shell"):
        yield cat, "category"
        return
    if "database" in t:
        yield "database", "tag"
        return
    if t & STRING_MATCH:
        yield "string-matching", "tag"
    if "trie" in t and not ({"dynamic-programming"} & t and "backtracking" not in t and "matrix" not in t):
        yield "trie", "tag"
    if t & ADV_GRAPH:
        yield "advanced-graph", "tag"
    if "topological-sort" in t:
        yield "topo-sort", "tag"
    if t & SHORTEST:
        yield "shortest-path", "tag"
    if "union-find" in t and not t & {"depth-first-search", "breadth-first-search"}:
        yield "union-find", "tag"
    if t & RANGE:
        yield "range-query", "tag"
    if t & {"monotonic-stack", "monotonic-queue"}:
        yield "monotonic", "tag"
    if INTERVAL_TITLE.search(title) or t & {"sweep-line", "line-sweep"}:
        yield "intervals", "title"
    if "design" in t and not t & {"prefix-sum", "heap-priority-queue", "stack", "queue", "trie", "union-find",
                                   "data-stream"} | RANGE:
        yield "design", "tag"
    if "backtracking" in t:
        yield "backtracking", "tag"
    if "linked-list" in t and "floyds-cycle-finding-algorithm" not in t:
        if "two-pointers" in t and re.search(r"cycle|middle|palindrom|intersection", title, re.I):
            yield "fast-slow", "tag"
        if "heap-priority-queue" not in t:
            yield "linked-list", "tag"
    if "floyds-cycle-finding-algorithm" in t or ("two-pointers" in t and re.search(r"happy|cycle|duplicate number",
                                                                                   title, re.I)):
        yield "fast-slow", "tag"
    if "sliding-window" in t:
        yield "sliding-window", "tag"
    if "dynamic-programming" in t or "memoization" in t or t & KNAPSACK \
            or "longest-increasing-subsequence" in t or "longest-common-subsequence" in t:
        yield "dp", "tag"
    if "heap-priority-queue" in t:
        yield "heap", "tag"
    if "linked-list" in t:
        yield "linked-list", "tag"
    if t & TREE:
        yield "tree", "tag"
    if "union-find" in t:
        yield "union-find", "tag"
    if t & GRAPH:
        yield "graph", "tag"
    if "binary-search" in t and not ("hash-table" in t and diff == "Easy"):
        yield "binary-search", "tag"
    if "two-pointers" in t:
        yield "two-pointers", "tag"
    if "design" in t:
        yield "design", "tag"
    if "stack" in t or "bracket-sequences" in t:
        yield "stack", "tag"
    if "prefix-sum" in t:
        yield "prefix-sum", "tag"
    if t & {"bit-manipulation", "bitmask"}:
        yield "bit", "tag"
    if "greedy" in t:
        yield "greedy", "tag"
    if t & MATH:
        yield "math", "tag"
    if t & {"hash-table", "counting", "boyer-moore-majority-vote-algorithm"}:
        yield "hashing", "tag"
    if "ordered-set" in t:
        yield "range-query", "tag"
    if t & SORT:
        yield "sorting", "tag"
    if t & {"simulation", "matrix", "interactive", "iterator"}:
        yield "matrix-sim", "tag"
    if "queue" in t:
        yield "stack", "tag"
    if t & {"array", "string", "enumeration", "recursion", "divide-and-conquer", "brute-force-search",
            "data-stream", "doubly-linked-list", "algorithm-x", "dancing-links", "meet-in-the-middle",
            "ternary-search", "hash-function"}:
        yield "array-string", "tag"


# Untagged (brand new) problems: a few title hints, else "Not Tagged Yet".
TITLE_HINTS = [
    (r"subarray|substring", "sliding-window"), (r"interval", "intervals"), (r"tree|subtree", "tree"),
    (r"grid|path", "graph"), (r"prime|fibonacci|divisible|digit", "math"), (r"design", "design"),
    (r"subset|subsequence|ways", "dp"),
]


def sub_pattern(p, t, title, diff):
    T = title.lower()
    if p == "dp":
        if "bitmask" in t: return "Bitmask DP"
        if "dp-on-trees" in t or t & TREE: return "Tree DP"
        if "game-theory" in t or t & {"zero-sum-game", "minimax-algorithm"}: return "Game DP"
        if t & KNAPSACK or re.search(r"coin|partition equal|target sum|ones and zeroes|last stone weight ii", T):
            return "Knapsack"
        if "longest-increasing-subsequence" in t or re.search(r"increasing subsequence|envelope", T):
            return "Longest Increasing Subsequence"
        if re.search(r"burst balloon|merge stones|cut a stick|matrix chain|strange printer|remove boxes", T):
            return "Interval DP"
        if re.search(r"\bdigit|numbers? with|count .*integers", T) and "math" in t: return "Digit / Counting DP"
        if "probability-and-statistics" in t: return "Probability DP"
        if "matrix" in t: return "Grid DP"
        if "graph" in t or "breadth-first-search" in t: return "DP on Graphs / DAGs"
        if "longest-common-subsequence" in t or ("string" in t and re.search(
                r"common|edit|distance|interleav|wildcard|regular|palindrom|distinct subseq", T)):
            return "String DP (LCS / Edit Distance / Palindromes)"
        if "string" in t: return "String DP (LCS / Edit Distance / Palindromes)"
        if "combinatorics" in t: return "Combinatorics / Counting DP"
        if "graph" in t or "breadth-first-search" in t: return "DP on Graphs / DAGs"
        if re.search(r"stock", T): return "State Machine DP (Stocks)"
        return "1-D / Sequence DP"
    if p == "graph":
        if "matrix" in t: return "Grid BFS / DFS"
        if "breadth-first-search" in t and "depth-first-search" not in t: return "Graph BFS"
        if "union-find" in t: return "Connected Components"
        return "Graph DFS / BFS"
    if p == "tree":
        if t & {"lowest-common-ancestor", "binary-lifting"} or "ancestor" in T: return "Lowest Common Ancestor"
        if "binary-search-tree" in t: return "Binary Search Tree"
        if re.search(r"serialize|construct|build|from (pre|in|post)order|create", T): return "Construct / Serialize"
        if "breadth-first-search" in t and "depth-first-search" not in t: return "Level Order (BFS)"
        if "path" in T: return "Root-to-Leaf / Path Sums"
        return "Tree DFS"
    if p == "binary-search":
        if "matrix" in t: return "Search in Matrix"
        if re.search(r"rotated", T): return "Rotated Array"
        if re.search(r"minimi|maximi|minimum|maximum|smallest|largest|least|capacity|speed|kth", T):
            return "Binary Search on the Answer"
        return "Classic Binary Search"
    if p == "heap":
        if re.search(r"median", T): return "Two Heaps"
        if re.search(r"merge|sorted lists|sorted arrays|smallest range|k pairs", T): return "K-way Merge"
        if re.search(r"\bk\b|kth|top|closest|frequent", T): return "Top-K Elements"
        if "greedy" in t: return "Greedy + Heap (Scheduling)"
        if "simulation" in t: return "Heap Simulation"
        return "Priority Queue"
    if p == "linked-list":
        if "revers" in T: return "In-place Reversal"
        if "merge" in T: return "Merge Lists"
        if re.search(r"remove|delete", T): return "Remove Nodes"
        return "List Manipulation"
    if p == "backtracking":
        if re.search(r"queen|sudoku", T): return "Constraint Search (N-Queens / Sudoku)"
        if "matrix" in t or re.search(r"word search|path", T): return "Grid Backtracking"
        if re.search(r"permut", T): return "Permutations"
        if re.search(r"subset|combination|partition", T): return "Subsets / Combinations"
        if "string" in t: return "String Generation"
        return "Search / Enumeration"
    if p == "math":
        if t & {"game-theory", "zero-sum-game", "minimax-algorithm", "nim-game", "sprague-grundy-theorem",
                "impartial-game"}: return "Game Theory"
        if t & {"geometry", "polygons", "convex-hull", "nearest-pair-of-points", "minimum-enclosing-circle",
                "triangulation"}: return "Geometry"
        if t & {"combinatorics", "inclusion-exclusion-principle", "pigeonhole-principle"}: return "Combinatorics"
        if t & {"number-theory", "greatest-common-divisor", "euclidean-algorithm", "prime-factorization",
                "sieve-theory", "primality-test", "prime-number-sieve", "least-common-multiple",
                "fermats-little-theorem", "eulers-totient-function"}: return "Number Theory (Primes / GCD / Mod)"
        if t & {"probability-and-statistics", "randomized", "reservoir-sampling", "rejection-sampling"}:
            return "Probability & Randomized"
        if "brainteaser" in t: return "Brainteaser"
        return "Arithmetic & Digits"
    if p == "shortest-path":
        if "dijkstra" in t: return "Dijkstra"
        if "bellman-ford-algorithm" in t: return "Bellman-Ford"
        if "floyd-warshall-algorithm" in t: return "Floyd-Warshall"
        if "0-1-bfs" in t: return "0-1 BFS"
        if t & {"a-search", "heuristic-search"}: return "A* Search"
        return "Weighted Shortest Path"
    if p == "advanced-graph":
        if t & {"minimum-spanning-tree", "prims-algorithm", "kruskals-algorithm", "boruvkas-algorithm"}:
            return "Minimum Spanning Tree"
        if t & {"eulerian-circuit", "eulerian-path", "eulerian-graph", "semi-eulerian-graph"}: return "Eulerian Path"
        if t & {"strongly-connected-component", "kosarajus-algorithm", "tarjans-scc-algorithm",
                "biconnected-component", "bridge-graph", "articulation-point"}: return "SCC / Bridges"
        if t & {"bipartite-graph", "graph-coloring"}: return "Bipartite / Coloring"
        if t & {"flow-network", "maximum-flow", "minimum-cost-flow", "minimum-cut", "matching-graph",
                "maximum-matching", "perfect-matching", "hungarian-algorithm"}: return "Flow / Matching"
        return "Other"
    if p == "string-matching":
        if "knuth-morris-pratt-algorithm" in t: return "KMP"
        if "z-algorithm" in t: return "Z-function"
        if t & {"suffix-array", "suffix-automaton", "suffix-tree"}: return "Suffix Structures"
        if "manacher" in t or "palindromic-tree" in t: return "Palindromes (Manacher)"
        if t & {"rolling-hash", "hash-function"}: return "Rolling Hash"
        return "String Matching"
    if p == "range-query":
        if "segment-tree" in t: return "Segment Tree"
        if "binary-indexed-tree" in t: return "Fenwick Tree (BIT)"
        if "ordered-set" in t: return "Ordered Set / Sorted Container"
        return "Other Range Structures"
    if p == "monotonic":
        return "Monotonic Queue" if "monotonic-queue" in t else "Monotonic Stack"
    if p == "sliding-window":
        if re.search(r"\bk\b|size k|length k|fixed", T): return "Fixed / K-bounded Window"
        return "Variable Window"
    if p == "two-pointers":
        if re.search(r"sum|pair|triplet|container|water", T): return "Pair / K-Sum"
        if re.search(r"palindrom|reverse", T): return "Opposite Ends"
        if re.search(r"remove|move|duplicate|merge|partition|sort colors", T): return "In-place Partition"
        return "Two Pointers"
    if p == "bit":
        if "bitmask" in t: return "Bitmask Enumeration"
        if re.search(r"xor", T): return "XOR Tricks"
        return "Bit Tricks"
    if p == "prefix-sum":
        if "matrix" in t: return "2-D Prefix Sum"
        if "hash-table" in t: return "Prefix Sum + Hash Map"
        return "Prefix Sum"
    if p == "union-find":
        return "Union Find"
    if p == "greedy":
        if t & SORT: return "Sort + Greedy"
        if "math" in t: return "Constructive / Math Greedy"
        if "string" in t: return "String Greedy"
        return "Greedy Choice"
    if p == "hashing":
        if re.search(r"anagram|group", T): return "Grouping by Key"
        if "counting" in t: return "Frequency Count"
        return "Hash Map / Set Lookup"
    if p == "stack":
        if "bracket-sequences" in t or re.search(r"parenthes|bracket", T): return "Bracket Matching"
        if re.search(r"calculator|expression|evaluat|parse|parsing", T): return "Expression Evaluation"
        if "queue" in t and "stack" not in t: return "Queue / Deque"
        return "Stack Simulation"
    if p == "trie":
        if t & {"bit-manipulation", "bitmask"}: return "Bitwise Trie"
        if t & {"depth-first-search", "backtracking"}: return "Trie + DFS"
        return "Prefix Trie"
    if p == "design":
        if "linked-list" in t or "doubly-linked-list" in t: return "Hash Map + Linked List"
        if "iterator" in t: return "Iterator"
        return "Class Design"
    if p == "sorting":
        if t & {"counting-sort", "bucket-sort", "radix-sort"}: return "Counting / Bucket Sort"
        if "quickselect" in t: return "Quickselect"
        return "Sort then Scan"
    if p == "matrix-sim":
        if "interactive" in t: return "Interactive"
        if "matrix" in t: return "Matrix"
        return "Simulation"
    if p == "array-string":
        if "divide-and-conquer" in t: return "Divide & Conquer"
        if "recursion" in t: return "Recursion"
        if "enumeration" in t: return "Brute-force Enumeration"
        if "string" in t: return "String Scan / Building"
        return "Array Scan"
    if p == "database":
        return {"Easy": "Easy queries", "Medium": "Medium queries", "Hard": "Hard queries"}.get(diff, "Queries")
    if p == "javascript":
        return "JavaScript"
    if p == "intervals":
        if t & {"sweep-line", "line-sweep"} or re.search(r"skyline|area|calendar|car pooling", T): return "Sweep Line"
        if "heap-priority-queue" in t: return "Intervals + Heap"
        if re.search(r"merge|insert", T): return "Merge / Insert"
        return "Overlap & Scheduling"
    if p == "topo-sort":
        return "Topological Order (Kahn's / DFS)"
    if p == "fast-slow":
        return "Cycle Detection" if re.search(r"cycle|happy|duplicate", T) else "Two Pointers on a List"
    if p in ("concurrency", "shell"):
        return NAME[p]
    return ""


# ------------------------------------------------------------- overrides
# Hand-checked answers for well-known problems (mostly Blind 75 / NeetCode 150 /
# Grind 169) where the tag order alone gives the wrong teaching pattern.
# slug -> (pattern, sub_pattern)
OVERRIDES = {
    # arrays & hashing
    "two-sum": ("hashing", "Complement Lookup"),
    "contains-duplicate": ("hashing", "Seen Set"),
    "valid-anagram": ("hashing", "Frequency Count"),
    "group-anagrams": ("hashing", "Grouping by Key"),
    "top-k-frequent-elements": ("heap", "Top-K Elements"),
    "product-of-array-except-self": ("prefix-sum", "Prefix / Suffix Products"),
    "longest-consecutive-sequence": ("hashing", "Seen Set"),
    "majority-element": ("hashing", "Boyer-Moore Voting"),
    "encode-and-decode-strings": ("array-string", "String Encoding"),
    "valid-sudoku": ("hashing", "Seen Set"),
    "first-missing-positive": ("array-string", "Cyclic Sort / Index as Hash"),
    "find-all-numbers-disappeared-in-an-array": ("array-string", "Cyclic Sort / Index as Hash"),
    "missing-number": ("bit", "XOR Tricks"),
    "set-matrix-zeroes": ("matrix-sim", "In-place Matrix"),
    "spiral-matrix": ("matrix-sim", "Spiral / Rotate"),
    "rotate-image": ("matrix-sim", "Spiral / Rotate"),
    "game-of-life": ("matrix-sim", "Board Simulation"),
    # two pointers
    "valid-palindrome": ("two-pointers", "Opposite Ends"),
    "two-sum-ii-input-array-is-sorted": ("two-pointers", "Pair / K-Sum"),
    "3sum": ("two-pointers", "Pair / K-Sum"),
    "3sum-closest": ("two-pointers", "Pair / K-Sum"),
    "4sum": ("two-pointers", "Pair / K-Sum"),
    "container-with-most-water": ("two-pointers", "Pair / K-Sum"),
    "trapping-rain-water": ("two-pointers", "Opposite Ends"),
    "sort-colors": ("two-pointers", "In-place Partition (Dutch Flag)"),
    "move-zeroes": ("two-pointers", "In-place Partition"),
    "remove-duplicates-from-sorted-array": ("two-pointers", "In-place Partition"),
    "merge-sorted-array": ("two-pointers", "Merge Two Sorted"),
    "squares-of-a-sorted-array": ("two-pointers", "Opposite Ends"),
    # fast & slow
    "linked-list-cycle": ("fast-slow", "Cycle Detection"),
    "linked-list-cycle-ii": ("fast-slow", "Cycle Detection"),
    "middle-of-the-linked-list": ("fast-slow", "Find Middle"),
    "happy-number": ("fast-slow", "Cycle Detection"),
    "find-the-duplicate-number": ("fast-slow", "Cycle Detection"),
    "palindrome-linked-list": ("fast-slow", "Find Middle"),
    # sliding window
    "best-time-to-buy-and-sell-stock": ("sliding-window", "Running Min / Max"),
    "longest-substring-without-repeating-characters": ("sliding-window", "Variable Window"),
    "longest-repeating-character-replacement": ("sliding-window", "Variable Window"),
    "permutation-in-string": ("sliding-window", "Fixed / K-bounded Window"),
    "minimum-window-substring": ("sliding-window", "Variable Window"),
    "sliding-window-maximum": ("monotonic", "Monotonic Queue"),
    "find-all-anagrams-in-a-string": ("sliding-window", "Fixed / K-bounded Window"),
    "minimum-size-subarray-sum": ("sliding-window", "Variable Window"),
    "fruit-into-baskets": ("sliding-window", "Variable Window"),
    "max-consecutive-ones-iii": ("sliding-window", "Variable Window"),
    "subarray-product-less-than-k": ("sliding-window", "Variable Window"),
    # prefix sum
    "subarray-sum-equals-k": ("prefix-sum", "Prefix Sum + Hash Map"),
    "continuous-subarray-sum": ("prefix-sum", "Prefix Sum + Hash Map"),
    "range-sum-query-immutable": ("prefix-sum", "Prefix Sum"),
    "range-sum-query-2d-immutable": ("prefix-sum", "2-D Prefix Sum"),
    "maximum-subarray": ("dp", "Kadane's Algorithm"),
    "maximum-product-subarray": ("dp", "Kadane's Algorithm"),
    # stack
    "valid-parentheses": ("stack", "Bracket Matching"),
    "min-stack": ("stack", "Stack Design"),
    "evaluate-reverse-polish-notation": ("stack", "Expression Evaluation"),
    "basic-calculator": ("stack", "Expression Evaluation"),
    "basic-calculator-ii": ("stack", "Expression Evaluation"),
    "decode-string": ("stack", "Nested Decoding"),
    "generate-parentheses": ("backtracking", "String Generation"),
    "daily-temperatures": ("monotonic", "Monotonic Stack"),
    "car-fleet": ("stack", "Sort + Stack"),
    "largest-rectangle-in-histogram": ("monotonic", "Monotonic Stack"),
    "asteroid-collision": ("stack", "Collision Simulation"),
    "implement-queue-using-stacks": ("stack", "Stack Design"),
    # binary search
    "binary-search": ("binary-search", "Classic Binary Search"),
    "search-a-2d-matrix": ("binary-search", "Search in Matrix"),
    "koko-eating-bananas": ("binary-search", "Binary Search on the Answer"),
    "find-minimum-in-rotated-sorted-array": ("binary-search", "Rotated Array"),
    "search-in-rotated-sorted-array": ("binary-search", "Rotated Array"),
    "time-based-key-value-store": ("binary-search", "Classic Binary Search"),
    "median-of-two-sorted-arrays": ("binary-search", "Partition Search"),
    "split-array-largest-sum": ("binary-search", "Binary Search on the Answer"),
    "capacity-to-ship-packages-within-d-days": ("binary-search", "Binary Search on the Answer"),
    "find-k-closest-elements": ("binary-search", "Classic Binary Search"),
    "first-bad-version": ("binary-search", "Classic Binary Search"),
    "find-peak-element": ("binary-search", "Classic Binary Search"),
    "kth-smallest-element-in-a-sorted-matrix": ("binary-search", "Search in Matrix"),
    "minimum-number-of-days-to-make-m-bouquets": ("binary-search", "Binary Search on the Answer"),
    # linked list
    "reverse-linked-list": ("linked-list", "In-place Reversal"),
    "merge-two-sorted-lists": ("linked-list", "Merge Lists"),
    "reorder-list": ("linked-list", "Find Middle + Reverse + Merge"),
    "remove-nth-node-from-end-of-list": ("linked-list", "Two Pointers on a List"),
    "copy-list-with-random-pointer": ("linked-list", "Clone with Hash Map"),
    "add-two-numbers": ("linked-list", "List Manipulation"),
    "lru-cache": ("design", "Hash Map + Doubly Linked List"),
    "lfu-cache": ("design", "Hash Map + Doubly Linked List"),
    "merge-k-sorted-lists": ("heap", "K-way Merge"),
    "reverse-nodes-in-k-group": ("linked-list", "In-place Reversal"),
    "intersection-of-two-linked-lists": ("fast-slow", "Two Pointers on a List"),
    # trees
    "invert-binary-tree": ("tree", "Tree DFS"),
    "maximum-depth-of-binary-tree": ("tree", "Tree DFS"),
    "diameter-of-binary-tree": ("tree", "Tree DFS"),
    "balanced-binary-tree": ("tree", "Tree DFS"),
    "same-tree": ("tree", "Tree DFS"),
    "subtree-of-another-tree": ("tree", "Tree DFS"),
    "lowest-common-ancestor-of-a-binary-search-tree": ("tree", "Lowest Common Ancestor"),
    "lowest-common-ancestor-of-a-binary-tree": ("tree", "Lowest Common Ancestor"),
    "binary-tree-level-order-traversal": ("tree", "Level Order (BFS)"),
    "binary-tree-right-side-view": ("tree", "Level Order (BFS)"),
    "count-good-nodes-in-binary-tree": ("tree", "Tree DFS"),
    "validate-binary-search-tree": ("tree", "Binary Search Tree"),
    "kth-smallest-element-in-a-bst": ("tree", "Binary Search Tree"),
    "construct-binary-tree-from-preorder-and-inorder-traversal": ("tree", "Construct / Serialize"),
    "binary-tree-maximum-path-sum": ("tree", "Root-to-Leaf / Path Sums"),
    "serialize-and-deserialize-binary-tree": ("tree", "Construct / Serialize"),
    "path-sum": ("tree", "Root-to-Leaf / Path Sums"),
    "path-sum-ii": ("tree", "Root-to-Leaf / Path Sums"),
    "path-sum-iii": ("tree", "Root-to-Leaf / Path Sums"),
    "symmetric-tree": ("tree", "Tree DFS"),
    "binary-tree-zigzag-level-order-traversal": ("tree", "Level Order (BFS)"),
    "house-robber-iii": ("dp", "Tree DP"),
    # heap
    "kth-largest-element-in-a-stream": ("heap", "Top-K Elements"),
    "last-stone-weight": ("heap", "Heap Simulation"),
    "k-closest-points-to-origin": ("heap", "Top-K Elements"),
    "kth-largest-element-in-an-array": ("heap", "Top-K Elements"),
    "task-scheduler": ("heap", "Greedy + Heap (Scheduling)"),
    "design-twitter": ("heap", "K-way Merge"),
    "find-median-from-data-stream": ("heap", "Two Heaps"),
    "sliding-window-median": ("heap", "Two Heaps"),
    "ipo": ("heap", "Two Heaps"),
    "smallest-range-covering-elements-from-k-lists": ("heap", "K-way Merge"),
    "find-k-pairs-with-smallest-sums": ("heap", "K-way Merge"),
    "reorganize-string": ("heap", "Greedy + Heap (Scheduling)"),
    # backtracking
    "subsets": ("backtracking", "Subsets / Combinations"),
    "subsets-ii": ("backtracking", "Subsets / Combinations"),
    "combination-sum": ("backtracking", "Subsets / Combinations"),
    "combination-sum-ii": ("backtracking", "Subsets / Combinations"),
    "permutations": ("backtracking", "Permutations"),
    "permutations-ii": ("backtracking", "Permutations"),
    "word-search": ("backtracking", "Grid Backtracking"),
    "palindrome-partitioning": ("backtracking", "Subsets / Combinations"),
    "letter-combinations-of-a-phone-number": ("backtracking", "String Generation"),
    "n-queens": ("backtracking", "Constraint Search (N-Queens / Sudoku)"),
    "sudoku-solver": ("backtracking", "Constraint Search (N-Queens / Sudoku)"),
    "partition-to-k-equal-sum-subsets": ("backtracking", "Subsets / Combinations"),
    # tries
    "implement-trie-prefix-tree": ("trie", "Trie Basics"),
    "design-add-and-search-words-data-structure": ("trie", "Trie + DFS"),
    "word-search-ii": ("trie", "Trie + Grid Backtracking"),
    "maximum-xor-of-two-numbers-in-an-array": ("trie", "Bitwise Trie"),
    # graphs
    "number-of-islands": ("graph", "Grid BFS / DFS"),
    "max-area-of-island": ("graph", "Grid BFS / DFS"),
    "clone-graph": ("graph", "Graph DFS / BFS"),
    "walls-and-gates": ("graph", "Multi-source BFS"),
    "rotting-oranges": ("graph", "Multi-source BFS"),
    "01-matrix": ("graph", "Multi-source BFS"),
    "pacific-atlantic-water-flow": ("graph", "Grid BFS / DFS"),
    "surrounded-regions": ("graph", "Grid BFS / DFS"),
    "course-schedule": ("topo-sort", "Cycle Detection / Kahn's"),
    "course-schedule-ii": ("topo-sort", "Cycle Detection / Kahn's"),
    "alien-dictionary": ("topo-sort", "Ordering from Constraints"),
    "graph-valid-tree": ("union-find", "Union Find"),
    "number-of-connected-components-in-an-undirected-graph": ("union-find", "Union Find"),
    "number-of-provinces": ("union-find", "Union Find"),
    "redundant-connection": ("union-find", "Union Find"),
    "accounts-merge": ("union-find", "Union Find"),
    "longest-increasing-path-in-a-matrix": ("dp", "Grid DP (DFS + Memo)"),
    "word-ladder": ("graph", "Graph BFS"),
    "open-the-lock": ("graph", "Graph BFS"),
    "shortest-path-in-binary-matrix": ("graph", "Grid BFS / DFS"),
    "is-graph-bipartite": ("advanced-graph", "Bipartite / Coloring"),
    "reconstruct-itinerary": ("advanced-graph", "Eulerian Path"),
    "min-cost-to-connect-all-points": ("advanced-graph", "Minimum Spanning Tree"),
    "network-delay-time": ("shortest-path", "Dijkstra"),
    "swim-in-rising-water": ("shortest-path", "Dijkstra"),
    "cheapest-flights-within-k-stops": ("shortest-path", "Bellman-Ford"),
    "path-with-minimum-effort": ("shortest-path", "Dijkstra"),
    "critical-connections-in-a-network": ("advanced-graph", "SCC / Bridges"),
    # dynamic programming
    "climbing-stairs": ("dp", "1-D / Sequence DP"),
    "min-cost-climbing-stairs": ("dp", "1-D / Sequence DP"),
    "house-robber": ("dp", "1-D / Sequence DP"),
    "house-robber-ii": ("dp", "1-D / Sequence DP"),
    "longest-palindromic-substring": ("dp", "String DP (LCS / Edit Distance / Palindromes)"),
    "palindromic-substrings": ("dp", "String DP (LCS / Edit Distance / Palindromes)"),
    "decode-ways": ("dp", "1-D / Sequence DP"),
    "coin-change": ("dp", "Knapsack"),
    "coin-change-ii": ("dp", "Knapsack"),
    "word-break": ("dp", "1-D / Sequence DP"),
    "word-break-ii": ("backtracking", "String Generation"),
    "longest-increasing-subsequence": ("dp", "Longest Increasing Subsequence"),
    "russian-doll-envelopes": ("dp", "Longest Increasing Subsequence"),
    "partition-equal-subset-sum": ("dp", "Knapsack"),
    "target-sum": ("dp", "Knapsack"),
    "unique-paths": ("dp", "Grid DP"),
    "unique-paths-ii": ("dp", "Grid DP"),
    "minimum-path-sum": ("dp", "Grid DP"),
    "longest-common-subsequence": ("dp", "String DP (LCS / Edit Distance / Palindromes)"),
    "edit-distance": ("dp", "String DP (LCS / Edit Distance / Palindromes)"),
    "interleaving-string": ("dp", "String DP (LCS / Edit Distance / Palindromes)"),
    "distinct-subsequences": ("dp", "String DP (LCS / Edit Distance / Palindromes)"),
    "regular-expression-matching": ("dp", "String DP (LCS / Edit Distance / Palindromes)"),
    "wildcard-matching": ("dp", "String DP (LCS / Edit Distance / Palindromes)"),
    "burst-balloons": ("dp", "Interval DP"),
    "best-time-to-buy-and-sell-stock-with-cooldown": ("dp", "State Machine DP (Stocks)"),
    "best-time-to-buy-and-sell-stock-iii": ("dp", "State Machine DP (Stocks)"),
    "best-time-to-buy-and-sell-stock-iv": ("dp", "State Machine DP (Stocks)"),
    "maximal-square": ("dp", "Grid DP"),
    "counting-bits": ("bit", "Bit Tricks"),
    # greedy
    "jump-game": ("greedy", "Reachability"),
    "jump-game-ii": ("greedy", "Reachability"),
    "gas-station": ("greedy", "Running Balance"),
    "hand-of-straights": ("greedy", "Sort + Greedy"),
    "merge-triplets-to-form-target-triplet": ("greedy", "Greedy Choice"),
    "partition-labels": ("greedy", "Last Occurrence"),
    "valid-parenthesis-string": ("greedy", "Range of Balances"),
    "candy": ("greedy", "Two Passes"),
    "best-time-to-buy-and-sell-stock-ii": ("greedy", "Greedy Choice"),
    # intervals
    "insert-interval": ("intervals", "Merge / Insert"),
    "merge-intervals": ("intervals", "Merge / Insert"),
    "non-overlapping-intervals": ("intervals", "Interval Scheduling (Greedy)"),
    "meeting-rooms": ("intervals", "Overlap Check"),
    "meeting-rooms-ii": ("intervals", "Rooms Needed (Heap / Sweep)"),
    "minimum-interval-to-include-each-query": ("intervals", "Intervals + Heap"),
    "minimum-number-of-arrows-to-burst-balloons": ("intervals", "Interval Scheduling (Greedy)"),
    "the-skyline-problem": ("intervals", "Sweep Line + Heap"),
    "car-pooling": ("intervals", "Sweep Line / Difference Array"),
    # math & bits
    "single-number": ("bit", "XOR Tricks"),
    "number-of-1-bits": ("bit", "Bit Tricks"),
    "reverse-bits": ("bit", "Bit Tricks"),
    "sum-of-two-integers": ("bit", "Bit Arithmetic"),
    "reverse-integer": ("math", "Arithmetic & Digits"),
    "powx-n": ("math", "Fast Exponentiation"),
    "multiply-strings": ("math", "Big-number Arithmetic"),
    "detect-squares": ("hashing", "Frequency Count"),
    "plus-one": ("math", "Arithmetic & Digits"),
    "count-primes": ("math", "Number Theory (Primes / GCD / Mod)"),
    # design
    "insert-delete-getrandom-o1": ("design", "Hash Map + Array"),
}

# ------------------------------------------------------------------- main


def classify(p):
    t = set(p["tags"])
    hits = []
    for pat, _why in _rules(t, p["title"], p["category"], p["difficulty"]):
        if pat not in hits:
            hits.append(pat)
    if not hits:
        for rx, pat in TITLE_HINTS:
            if re.search(rx, p["title"], re.I):
                hits = [pat]
                break
        main, how = (hits[0], "title-guess") if hits else ("uncategorized", "none")
        sub = "Guessed from title (no tags yet)" if hits else ""
        return main, sub, [], how
    main, how = hits[0], "rules"
    sub = sub_pattern(main, t, p["title"], p["difficulty"])
    if p["slug"] in OVERRIDES:
        main, sub = OVERRIDES[p["slug"]]
        how = "hand-checked"
    also = [h for h in hits if h not in (main, "array-string")][:4]
    return main, sub, also, how


def main():
    problems = json.load(open(os.path.join(HERE, "data", "problems.json")))
    missing = set(OVERRIDES) - {p["slug"] for p in problems}
    if missing:
        print("warning: overrides for unknown slugs:", sorted(missing))
    rows = []
    for p in problems:
        m, s, also, how = classify(p)
        rows.append({"id": p["id"], "title": p["title"], "slug": p["slug"], "difficulty": p["difficulty"],
                     "paid": p["paid"], "pattern": m, "pattern_name": NAME[m], "sub_pattern": s,
                     "also": also, "how": how, "tags": p["tags"]})

    json.dump({"patterns": [{"key": k, "name": n, "when": w} for k, n, w in PATTERNS], "problems": rows},
              open(os.path.join(HERE, "patterns.json"), "w"), separators=(",", ":"))

    with open(os.path.join(HERE, "patterns.csv"), "w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["id", "title", "difficulty", "premium", "pattern", "sub_pattern", "also", "how", "url", "tags"])
        for r in rows:
            w.writerow([r["id"], r["title"], r["difficulty"], "yes" if r["paid"] else "", r["pattern_name"],
                        r["sub_pattern"], "; ".join(NAME[a] for a in r["also"]), r["how"],
                        f"https://leetcode.com/problems/{r['slug']}/", " ".join(r["tags"])])

    write_markdown(rows)
    c = Counter(r["pattern"] for r in rows)
    for k, _, _ in PATTERNS:
        print(f"{c[k]:5}  {NAME[k]}")
    print(f"{len(rows):5}  total;", Counter(r["how"] for r in rows))


def write_markdown(rows):
    by = defaultdict(lambda: defaultdict(list))
    for r in rows:
        by[r["pattern"]][r["sub_pattern"] or "General"].append(r)
    diff_icon = {"Easy": "🟢", "Medium": "🟡", "Hard": "🔴"}
    out = ["# Every LeetCode problem, sorted by algorithm pattern", "",
           f"{len(rows)} problems, each placed in one main pattern (and a sub-pattern). "
           "Made by `classify.py` from LeetCode's own topic tags plus hand-checked answers for the well-known "
           "interview problems. 🔒 = Premium. 🟢 Easy 🟡 Medium 🔴 Hard.", "",
           "| Pattern | Problems | Use it when |", "|---|---:|---|"]
    for k, n, w in PATTERNS:
        cnt = sum(len(v) for v in by[k].values())
        if cnt:
            anchor = re.sub(r"[^a-z0-9 -]", "", n.lower()).replace(" ", "-")
            out.append(f"| [{n}](#{anchor}) | {cnt} | {w} |")
    out.append("")
    for k, n, w in PATTERNS:
        if not by[k]:
            continue
        cnt = sum(len(v) for v in by[k].values())
        out += [f"## {n}", "", f"*{w}* — {cnt} problems", ""]
        for sub, items in sorted(by[k].items(), key=lambda kv: -len(kv[1])):
            out += [f"<details><summary><b>{sub}</b> ({len(items)})</summary>", ""]
            for r in sorted(items, key=lambda r: r["id"]):
                lock = " 🔒" if r["paid"] else ""
                out.append(f"- {diff_icon.get(r['difficulty'], '')} [{r['id']}. {r['title']}]"
                           f"(https://leetcode.com/problems/{r['slug']}/){lock}")
            out += ["", "</details>", ""]
    open(os.path.join(HERE, "PATTERNS.md"), "w").write("\n".join(out))


if __name__ == "__main__":
    main()

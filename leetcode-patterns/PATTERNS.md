# Every LeetCode problem, sorted by algorithm pattern

4115 problems, each placed in one main pattern (and a sub-pattern). Made by `classify.py` from LeetCode's own topic tags plus hand-checked answers for the well-known interview problems. 🔒 = Premium. 🟢 Easy 🟡 Medium 🔴 Hard.

| Pattern | Problems | Use it when |
|---|---:|---|
| [Two Pointers](#two-pointers) | 142 | Sorted array or string; walk two indexes toward each other or in step. |
| [Sliding Window](#sliding-window) | 153 | Best / count of contiguous subarrays or substrings under a condition. |
| [Fast & Slow Pointers](#fast--slow-pointers) | 10 | Cycle detection, middle of a list, repeating sequences. |
| [Prefix Sum & Difference Array](#prefix-sum--difference-array) | 127 | Many range-sum questions; subarray sums equal to K. |
| [Hashing & Counting](#hashing--counting) | 265 | Seen-before lookups, frequencies, grouping, anagrams. |
| [Intervals & Sweep Line](#intervals--sweep-line) | 43 | Merge / insert / overlap of ranges, meeting rooms, events over time. |
| [Binary Search](#binary-search) | 181 | Sorted data, or 'smallest X that works' (search on the answer). |
| [Stack](#stack) | 57 | Matching brackets, parsing expressions, undo, nested structure. |
| [Monotonic Stack / Queue](#monotonic-stack--queue) | 83 | Next greater / smaller element, sliding-window max, histograms. |
| [Linked List](#linked-list) | 64 | Reverse, merge, reorder, remove nodes in place. |
| [Tree Traversal (DFS / BFS)](#tree-traversal-dfs--bfs) | 210 | Binary trees and BSTs: recursion, level order, paths, LCA. |
| [Heap / Top-K / K-way Merge](#heap--top-k--k-way-merge) | 136 | Kth largest, top K frequent, running median, merge K sorted. |
| [Graph & Grid Traversal (BFS / DFS)](#graph--grid-traversal-bfs--dfs) | 99 | Islands, flood fill, connected components, unweighted shortest path. |
| [Topological Sort](#topological-sort) | 34 | Ordering with prerequisites; cycle check in a directed graph. |
| [Union Find (Disjoint Set)](#union-find-disjoint-set) | 69 | Merging groups, connectivity as edges arrive, redundant edges. |
| [Shortest Path (Dijkstra / Bellman-Ford / Floyd)](#shortest-path-dijkstra--bellman-ford--floyd) | 47 | Weighted graphs: cheapest / fastest route. |
| [Advanced Graph](#advanced-graph) | 36 | MST, Euler paths, strongly connected components, bipartite, flows, bridges. |
| [Backtracking](#backtracking) | 105 | Generate all subsets / permutations / combinations; N-Queens, Sudoku. |
| [Dynamic Programming](#dynamic-programming) | 556 | Overlapping subproblems: count ways, min / max cost, best subsequence. |
| [Greedy](#greedy) | 224 | A local best choice is provably globally best (often after sorting). |
| [Trie](#trie) | 42 | Prefix search, word dictionaries, bitwise-XOR maximisation. |
| [Segment Tree / Fenwick Tree / Ordered Set](#segment-tree--fenwick-tree--ordered-set) | 102 | Range queries with updates, counting smaller elements. |
| [String Matching & Hashing](#string-matching--hashing) | 72 | KMP, Z-function, rolling hash, suffix arrays, Manacher. |
| [Bit Manipulation](#bit-manipulation) | 118 | XOR tricks, bit counting, masks, powers of two. |
| [Math & Number Theory](#math--number-theory) | 343 | Primes, GCD, modular arithmetic, combinatorics, geometry, games. |
| [Design (Data Structures)](#design-data-structures) | 42 | Build a class: LRU cache, iterators, time-based stores. |
| [Matrix & Simulation](#matrix--simulation) | 103 | Follow the rules step by step; spiral, rotate, game boards. |
| [Sorting & Custom Ordering](#sorting--custom-ordering) | 39 | Sort first, custom comparators, counting / bucket sort. |
| [Arrays & Strings (Basics)](#arrays--strings-basics) | 182 | Direct scans, enumeration, string building. |
| [Database (SQL / Pandas)](#database-sql--pandas) | 338 | SQL queries and Pandas DataFrame problems. |
| [JavaScript](#javascript) | 67 | Closures, promises, debounce, the '30 Days of JavaScript' set. |
| [Concurrency](#concurrency) | 9 | Threads, locks, semaphores. |
| [Shell](#shell) | 4 | Bash one-liners. |
| [Not Tagged Yet](#not-tagged-yet) | 13 | Very new problems LeetCode has not tagged; placed by title where possible. |

## Two Pointers

*Sorted array or string; walk two indexes toward each other or in step.* — 142 problems

<details><summary><b>Two Pointers</b> (85)</summary>

- 🟡 [31. Next Permutation](https://leetcode.com/problems/next-permutation/)
- 🟡 [161. One Edit Distance](https://leetcode.com/problems/one-edit-distance/) 🔒
- 🟡 [165. Compare Version Numbers](https://leetcode.com/problems/compare-version-numbers/)
- 🟡 [189. Rotate Array](https://leetcode.com/problems/rotate-array/)
- 🟡 [244. Shortest Word Distance II](https://leetcode.com/problems/shortest-word-distance-ii/) 🔒
- 🟢 [246. Strobogrammatic Number](https://leetcode.com/problems/strobogrammatic-number/) 🔒
- 🟡 [251. Flatten 2D Vector](https://leetcode.com/problems/flatten-2d-vector/) 🔒
- 🟢 [349. Intersection of Two Arrays](https://leetcode.com/problems/intersection-of-two-arrays/)
- 🟢 [350. Intersection of Two Arrays II](https://leetcode.com/problems/intersection-of-two-arrays-ii/)
- 🟡 [360. Sort Transformed Array](https://leetcode.com/problems/sort-transformed-array/) 🔒
- 🟢 [408. Valid Word Abbreviation](https://leetcode.com/problems/valid-word-abbreviation/) 🔒
- 🟡 [443. String Compression](https://leetcode.com/problems/string-compression/)
- 🟢 [455. Assign Cookies](https://leetcode.com/problems/assign-cookies/)
- 🟡 [481. Magical String](https://leetcode.com/problems/magical-string/)
- 🟡 [522. Longest Uncommon Subsequence II](https://leetcode.com/problems/longest-uncommon-subsequence-ii/)
- 🟡 [524. Longest Word in Dictionary through Deleting](https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/)
- 🟡 [556. Next Greater Element III](https://leetcode.com/problems/next-greater-element-iii/)
- 🟢 [696. Count Binary Substrings](https://leetcode.com/problems/count-binary-substrings/)
- 🟡 [723. Candy Crush](https://leetcode.com/problems/candy-crush/) 🔒
- 🟡 [777. Swap Adjacent in LR String](https://leetcode.com/problems/swap-adjacent-in-lr-string/)
- 🟡 [795. Number of Subarrays with Bounded Maximum](https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/)
- 🟡 [809. Expressive Words](https://leetcode.com/problems/expressive-words/)
- 🟢 [821. Shortest Distance to a Character](https://leetcode.com/problems/shortest-distance-to-a-character/)
- 🟢 [832. Flipping an Image](https://leetcode.com/problems/flipping-an-image/)
- 🟢 [844. Backspace String Compare](https://leetcode.com/problems/backspace-string-compare/)
- 🟡 [870. Advantage Shuffle](https://leetcode.com/problems/advantage-shuffle/)
- 🟡 [881. Boats to Save People](https://leetcode.com/problems/boats-to-save-people/)
- 🟢 [905. Sort Array By Parity](https://leetcode.com/problems/sort-array-by-parity/)
- 🟢 [922. Sort Array By Parity II](https://leetcode.com/problems/sort-array-by-parity-ii/)
- 🟢 [925. Long Pressed Name](https://leetcode.com/problems/long-pressed-name/)
- 🟢 [942. DI String Match](https://leetcode.com/problems/di-string-match/)
- 🟡 [948. Bag of Tokens](https://leetcode.com/problems/bag-of-tokens/)
- 🟡 [969. Pancake Sorting](https://leetcode.com/problems/pancake-sorting/)
- 🟡 [1229. Meeting Scheduler](https://leetcode.com/problems/meeting-scheduler/) 🔒
- 🟢 [1346. Check If N and Its Double Exist](https://leetcode.com/problems/check-if-n-and-its-double-exist/)
- 🟡 [1471. The k Strongest Values in an Array](https://leetcode.com/problems/the-k-strongest-values-in-an-array/)
- 🟡 [1570. Dot Product of Two Sparse Vectors](https://leetcode.com/problems/dot-product-of-two-sparse-vectors/) 🔒
- 🟡 [1577. Number of Ways Where Square of Number Is Equal to Product of Two Numbers](https://leetcode.com/problems/number-of-ways-where-square-of-number-is-equal-to-product-of-two-numbers/)
- 🟡 [1750. Minimum Length of String After Deleting Similar Ends](https://leetcode.com/problems/minimum-length-of-string-after-deleting-similar-ends/)
- 🟡 [1813. Sentence Similarity III](https://leetcode.com/problems/sentence-similarity-iii/)
- 🟢 [1826. Faulty Sensor](https://leetcode.com/problems/faulty-sensor/) 🔒
- 🟡 [1850. Minimum Adjacent Swaps to Reach the Kth Smallest Number](https://leetcode.com/problems/minimum-adjacent-swaps-to-reach-the-kth-smallest-number/)
- 🟡 [1861. Rotating the Box](https://leetcode.com/problems/rotating-the-box/)
- 🟡 [1868. Product of Two Run-Length Encoded Arrays](https://leetcode.com/problems/product-of-two-run-length-encoded-arrays/) 🔒
- 🟢 [1961. Check If String Is a Prefix of Array](https://leetcode.com/problems/check-if-string-is-a-prefix-of-array/)
- 🟡 [1963. Minimum Number of Swaps to Make the String Balanced](https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-string-balanced/)
- 🟡 [1989. Maximum Number of People That Can Be Caught in Tag](https://leetcode.com/problems/maximum-number-of-people-that-can-be-caught-in-tag/) 🔒
- 🟡 [2109. Adding Spaces to a String](https://leetcode.com/problems/adding-spaces-to-a-string/)
- 🔴 [2122. Recover the Original Array](https://leetcode.com/problems/recover-the-original-array/)
- 🟡 [2149. Rearrange Array Elements by Sign](https://leetcode.com/problems/rearrange-array-elements-by-sign/)
- 🟢 [2200. Find All K-Distant Indices in an Array](https://leetcode.com/problems/find-all-k-distant-indices-in-an-array/)
- 🟡 [2410. Maximum Matching of Players With Trainers](https://leetcode.com/problems/maximum-matching-of-players-with-trainers/)
- 🟢 [2441. Largest Positive Integer That Exists With Its Negative](https://leetcode.com/problems/largest-positive-integer-that-exists-with-its-negative/)
- 🟢 [2460. Apply Operations to an Array](https://leetcode.com/problems/apply-operations-to-an-array/)
- 🟢 [2465. Number of Distinct Averages](https://leetcode.com/problems/number-of-distinct-averages/)
- 🟡 [2486. Append Characters to String to Make Subsequence](https://leetcode.com/problems/append-characters-to-string-to-make-subsequence/)
- 🟡 [2491. Divide Players Into Teams of Equal Skill](https://leetcode.com/problems/divide-players-into-teams-of-equal-skill/)
- 🟢 [2511. Maximum Enemy Forts That Can Be Captured](https://leetcode.com/problems/maximum-enemy-forts-that-can-be-captured/)
- 🟢 [2540. Minimum Common Value](https://leetcode.com/problems/minimum-common-value/)
- 🟢 [2562. Find the Array Concatenation Value](https://leetcode.com/problems/find-the-array-concatenation-value/)
- 🟡 [2592. Maximize Greatness of an Array](https://leetcode.com/problems/maximize-greatness-of-an-array/)
- 🟡 [2825. Make String a Subsequence Using Cyclic Increments](https://leetcode.com/problems/make-string-a-subsequence-using-cyclic-increments/)
- 🔴 [2868. The Wording Game](https://leetcode.com/problems/the-wording-game/) 🔒
- 🟢 [2903. Find Indices With Index and Value Difference I](https://leetcode.com/problems/find-indices-with-index-and-value-difference-i/)
- 🟡 [2905. Find Indices With Index and Value Difference II](https://leetcode.com/problems/find-indices-with-index-and-value-difference-ii/)
- 🟡 [2938. Separate Black and White Balls](https://leetcode.com/problems/separate-black-and-white-balls/)
- 🟢 [3069. Distribute Elements Into Two Arrays I](https://leetcode.com/problems/distribute-elements-into-two-arrays-i/)
- 🟡 [3132. Find the Integer Added to Array II](https://leetcode.com/problems/find-the-integer-added-to-array-ii/)
- 🟢 [3194. Minimum Average of Smallest and Largest Elements](https://leetcode.com/problems/minimum-average-of-smallest-and-largest-elements/)
- 🟡 [3400. Maximum Number of Matching Indices After Right Shifts](https://leetcode.com/problems/maximum-number-of-matching-indices-after-right-shifts/) 🔒
- 🟡 [3403. Find the Lexicographically Largest String From the Box I](https://leetcode.com/problems/find-the-lexicographically-largest-string-from-the-box-i/)
- 🔴 [3406. Find the Lexicographically Largest String From the Box II](https://leetcode.com/problems/find-the-lexicographically-largest-string-from-the-box-ii/) 🔒
- 🟡 [3460. Longest Common Prefix After at Most One Removal](https://leetcode.com/problems/longest-common-prefix-after-at-most-one-removal/) 🔒
- 🟡 [3584. Maximum Product of First and Last Elements of a Subsequence](https://leetcode.com/problems/maximum-product-of-first-and-last-elements-of-a-subsequence/)
- 🟢 [3643. Flip Square Submatrix Vertically](https://leetcode.com/problems/flip-square-submatrix-vertically/)
- 🟢 [3667. Sort Array By Absolute Value](https://leetcode.com/problems/sort-array-by-absolute-value/) 🔒
- 🟡 [3730. Maximum Calories Burnt from Jumps](https://leetcode.com/problems/maximum-calories-burnt-from-jumps/) 🔒
- 🟢 [3884. First Matching Character From Both Ends](https://leetcode.com/problems/first-matching-character-from-both-ends/)
- 🟢 [3940. Limit Occurrences in Sorted Array](https://leetcode.com/problems/limit-occurrences-in-sorted-array/)
- 🟡 [3983. Subsequence After One Replacement](https://leetcode.com/problems/subsequence-after-one-replacement/)
- 🟡 [3998. Transform Binary String Using Subsequence Sort](https://leetcode.com/problems/transform-binary-string-using-subsequence-sort/)
- 🔴 [3999. Minimum Number of String Groups Through Transformations](https://leetcode.com/problems/minimum-number-of-string-groups-through-transformations/)
- 🟡 [4001. Aggregate Two Time Series](https://leetcode.com/problems/aggregate-two-time-series/)
- 🟡 [4014. Minimum Total Price After Applying Discounts](https://leetcode.com/problems/minimum-total-price-after-applying-discounts/)
- 🟡 [4026. Maximum Gap Between Stations](https://leetcode.com/problems/maximum-gap-between-stations/)

</details>

<details><summary><b>Opposite Ends</b> (29)</summary>

- 🔴 [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)
- 🟢 [125. Valid Palindrome](https://leetcode.com/problems/valid-palindrome/)
- 🟡 [151. Reverse Words in a String](https://leetcode.com/problems/reverse-words-in-a-string/)
- 🟡 [186. Reverse Words in a String II](https://leetcode.com/problems/reverse-words-in-a-string-ii/) 🔒
- 🟢 [344. Reverse String](https://leetcode.com/problems/reverse-string/)
- 🟢 [345. Reverse Vowels of a String](https://leetcode.com/problems/reverse-vowels-of-a-string/)
- 🟢 [541. Reverse String II](https://leetcode.com/problems/reverse-string-ii/)
- 🟢 [557. Reverse Words in a String III](https://leetcode.com/problems/reverse-words-in-a-string-iii/)
- 🟢 [680. Valid Palindrome II](https://leetcode.com/problems/valid-palindrome-ii/)
- 🟢 [917. Reverse Only Letters](https://leetcode.com/problems/reverse-only-letters/)
- 🟢 [977. Squares of a Sorted Array](https://leetcode.com/problems/squares-of-a-sorted-array/)
- 🟢 [1332. Remove Palindromic Subsequences](https://leetcode.com/problems/remove-palindromic-subsequences/)
- 🟡 [1616. Split Two Strings to Make Palindrome](https://leetcode.com/problems/split-two-strings-to-make-palindrome/)
- 🔴 [1842. Next Palindrome Using Same Digits](https://leetcode.com/problems/next-palindrome-using-same-digits/) 🔒
- 🟢 [2000. Reverse Prefix of Word](https://leetcode.com/problems/reverse-prefix-of-word/)
- 🟢 [2108. Find First Palindromic String in the Array](https://leetcode.com/problems/find-first-palindromic-string-in-the-array/)
- 🟡 [2330. Valid Palindrome IV](https://leetcode.com/problems/valid-palindrome-iv/) 🔒
- 🟡 [2396. Strictly Palindromic Number](https://leetcode.com/problems/strictly-palindromic-number/)
- 🟡 [2422. Merge Operations to Turn Array Into a Palindrome](https://leetcode.com/problems/merge-operations-to-turn-array-into-a-palindrome/) 🔒
- 🟢 [2697. Lexicographically Smallest Palindrome](https://leetcode.com/problems/lexicographically-smallest-palindrome/)
- 🟡 [3239. Minimum Number of Flips to Make Binary Grid Palindromic I](https://leetcode.com/problems/minimum-number-of-flips-to-make-binary-grid-palindromic-i/)
- 🟡 [3240. Minimum Number of Flips to Make Binary Grid Palindromic II](https://leetcode.com/problems/minimum-number-of-flips-to-make-binary-grid-palindromic-ii/)
- 🔴 [3734. Lexicographically Smallest Palindromic Permutation Greater Than Target](https://leetcode.com/problems/lexicographically-smallest-palindromic-permutation-greater-than-target/)
- 🟢 [3750. Minimum Number of Flips to Reverse Binary String](https://leetcode.com/problems/minimum-number-of-flips-to-reverse-binary-string/)
- 🟡 [3775. Reverse Words With Same Vowel Count](https://leetcode.com/problems/reverse-words-with-same-vowel-count/)
- 🟢 [3794. Reverse String Prefix](https://leetcode.com/problems/reverse-string-prefix/)
- 🟢 [3823. Reverse Letters Then Special Characters in a String](https://leetcode.com/problems/reverse-letters-then-special-characters-in-a-string/)
- 🟡 [3865. Reverse K Subarrays](https://leetcode.com/problems/reverse-k-subarrays/) 🔒
- 🟢 [4030. Check ASCII Palindromic](https://leetcode.com/problems/check-ascii-palindromic/)

</details>

<details><summary><b>Pair / K-Sum</b> (16)</summary>

- 🟡 [11. Container With Most Water](https://leetcode.com/problems/container-with-most-water/)
- 🟡 [15. 3Sum](https://leetcode.com/problems/3sum/)
- 🟡 [16. 3Sum Closest](https://leetcode.com/problems/3sum-closest/)
- 🟡 [18. 4Sum](https://leetcode.com/problems/4sum/)
- 🟡 [167. Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/)
- 🟢 [170. Two Sum III - Data structure design](https://leetcode.com/problems/two-sum-iii-data-structure-design/) 🔒
- 🟡 [923. 3Sum With Multiplicity](https://leetcode.com/problems/3sum-with-multiplicity/)
- 🟡 [1679. Max Number of K-Sum Pairs](https://leetcode.com/problems/max-number-of-k-sum-pairs/)
- 🟡 [1877. Minimize Maximum Pair Sum in Array](https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/)
- 🟡 [2105. Watering Plants II](https://leetcode.com/problems/watering-plants-ii/)
- 🟢 [2367. Number of Arithmetic Triplets](https://leetcode.com/problems/number-of-arithmetic-triplets/)
- 🟢 [2570. Merge Two 2D Arrays by Summing Values](https://leetcode.com/problems/merge-two-2d-arrays-by-summing-values/)
- 🟡 [3649. Number of Perfect Pairs](https://leetcode.com/problems/number-of-perfect-pairs/)
- 🟡 [3752. Lexicographically Smallest Negated Permutation that Sums to Target](https://leetcode.com/problems/lexicographically-smallest-negated-permutation-that-sums-to-target/)
- 🟡 [3867. Sum of GCD of Formed Pairs](https://leetcode.com/problems/sum-of-gcd-of-formed-pairs/)
- 🟢 [3992. Rearrange String to Avoid Character Pair](https://leetcode.com/problems/rearrange-string-to-avoid-character-pair/)

</details>

<details><summary><b>In-place Partition</b> (10)</summary>

- 🟢 [26. Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/)
- 🟢 [27. Remove Element](https://leetcode.com/problems/remove-element/)
- 🟡 [80. Remove Duplicates from Sorted Array II](https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/)
- 🟢 [283. Move Zeroes](https://leetcode.com/problems/move-zeroes/)
- 🟢 [1089. Duplicate Zeros](https://leetcode.com/problems/duplicate-zeros/)
- 🟡 [1754. Largest Merge Of Two Strings](https://leetcode.com/problems/largest-merge-of-two-strings/)
- 🟢 [1768. Merge Strings Alternately](https://leetcode.com/problems/merge-strings-alternately/)
- 🟡 [2161. Partition Array According to Given Pivot](https://leetcode.com/problems/partition-array-according-to-given-pivot/)
- 🟡 [2337. Move Pieces to Obtain a String](https://leetcode.com/problems/move-pieces-to-obtain-a-string/)
- 🟢 [3936. Minimum Swaps to Move Zeros to End](https://leetcode.com/problems/minimum-swaps-to-move-zeros-to-end/)

</details>

<details><summary><b>In-place Partition (Dutch Flag)</b> (1)</summary>

- 🟡 [75. Sort Colors](https://leetcode.com/problems/sort-colors/)

</details>

<details><summary><b>Merge Two Sorted</b> (1)</summary>

- 🟢 [88. Merge Sorted Array](https://leetcode.com/problems/merge-sorted-array/)

</details>

## Sliding Window

*Best / count of contiguous subarrays or substrings under a condition.* — 153 problems

<details><summary><b>Variable Window</b> (101)</summary>

- 🟡 [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)
- 🔴 [30. Substring with Concatenation of All Words](https://leetcode.com/problems/substring-with-concatenation-of-all-words/)
- 🔴 [76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)
- 🟡 [159. Longest Substring with At Most Two Distinct Characters](https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/) 🔒
- 🟡 [209. Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/)
- 🟢 [219. Contains Duplicate II](https://leetcode.com/problems/contains-duplicate-ii/)
- 🔴 [220. Contains Duplicate III](https://leetcode.com/problems/contains-duplicate-iii/)
- 🟡 [413. Arithmetic Slices](https://leetcode.com/problems/arithmetic-slices/)
- 🟡 [424. Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/)
- 🟡 [487. Max Consecutive Ones II](https://leetcode.com/problems/max-consecutive-ones-ii/) 🔒
- 🟢 [594. Longest Harmonious Subsequence](https://leetcode.com/problems/longest-harmonious-subsequence/)
- 🟢 [643. Maximum Average Subarray I](https://leetcode.com/problems/maximum-average-subarray-i/)
- 🟡 [713. Subarray Product Less Than K](https://leetcode.com/problems/subarray-product-less-than-k/)
- 🔴 [727. Minimum Window Subsequence](https://leetcode.com/problems/minimum-window-subsequence/) 🔒
- 🟡 [837. New 21 Game](https://leetcode.com/problems/new-21-game/)
- 🟡 [904. Fruit Into Baskets](https://leetcode.com/problems/fruit-into-baskets/)
- 🟡 [930. Binary Subarrays With Sum](https://leetcode.com/problems/binary-subarrays-with-sum/)
- 🟡 [978. Longest Turbulent Subarray](https://leetcode.com/problems/longest-turbulent-subarray/)
- 🟡 [1004. Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/)
- 🟡 [1016. Binary String With Substrings Representing 1 To N](https://leetcode.com/problems/binary-string-with-substrings-representing-1-to-n/)
- 🟡 [1040. Moving Stones Until Consecutive II](https://leetcode.com/problems/moving-stones-until-consecutive-ii/)
- 🟡 [1052. Grumpy Bookstore Owner](https://leetcode.com/problems/grumpy-bookstore-owner/)
- 🟡 [1151. Minimum Swaps to Group All 1's Together](https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together/) 🔒
- 🟡 [1156. Swap For Longest Repeated Character Substring](https://leetcode.com/problems/swap-for-longest-repeated-character-substring/)
- 🟢 [1176. Diet Plan Performance](https://leetcode.com/problems/diet-plan-performance/) 🔒
- 🟡 [1208. Get Equal Substrings Within Budget](https://leetcode.com/problems/get-equal-substrings-within-budget/)
- 🟡 [1234. Replace the Substring for Balanced String](https://leetcode.com/problems/replace-the-substring-for-balanced-string/)
- 🟡 [1248. Count Number of Nice Subarrays](https://leetcode.com/problems/count-number-of-nice-subarrays/)
- 🟡 [1297. Maximum Number of Occurrences of a Substring](https://leetcode.com/problems/maximum-number-of-occurrences-of-a-substring/)
- 🟡 [1358. Number of Substrings Containing All Three Characters](https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/)
- 🟡 [1423. Maximum Points You Can Obtain from Cards](https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/)
- 🟡 [1456. Maximum Number of Vowels in a Substring of Given Length](https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/)
- 🟡 [1493. Longest Subarray of 1's After Deleting One Element](https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/)
- 🔴 [1610. Maximum Number of Visible Points](https://leetcode.com/problems/maximum-number-of-visible-points/)
- 🟢 [1652. Defuse the Bomb](https://leetcode.com/problems/defuse-the-bomb/)
- 🟡 [1658. Minimum Operations to Reduce X to Zero](https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/)
- 🟡 [1695. Maximum Erasure Value](https://leetcode.com/problems/maximum-erasure-value/)
- 🟢 [1763. Longest Nice Substring](https://leetcode.com/problems/longest-nice-substring/)
- 🟡 [1838. Frequency of the Most Frequent Element](https://leetcode.com/problems/frequency-of-the-most-frequent-element/)
- 🟡 [1839. Longest Substring Of All Vowels in Order](https://leetcode.com/problems/longest-substring-of-all-vowels-in-order/)
- 🟡 [1852. Distinct Numbers in Each Subarray](https://leetcode.com/problems/distinct-numbers-in-each-subarray/) 🔒
- 🟡 [1871. Jump Game VII](https://leetcode.com/problems/jump-game-vii/)
- 🟢 [1876. Substrings of Size Three with Distinct Characters](https://leetcode.com/problems/substrings-of-size-three-with-distinct-characters/)
- 🟡 [1888. Minimum Number of Flips to Make the Binary String Alternating](https://leetcode.com/problems/minimum-number-of-flips-to-make-the-binary-string-alternating/)
- 🟡 [1918. Kth Smallest Subarray Sum](https://leetcode.com/problems/kth-smallest-subarray-sum/) 🔒
- 🔴 [2009. Minimum Number of Operations to Make Array Continuous](https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/)
- 🟡 [2024. Maximize the Confusion of an Exam](https://leetcode.com/problems/maximize-the-confusion-of-an-exam/)
- 🟡 [2067. Number of Equal Count Substrings](https://leetcode.com/problems/number-of-equal-count-substrings/) 🔒
- 🟡 [2110. Number of Smooth Descent Periods of a Stock](https://leetcode.com/problems/number-of-smooth-descent-periods-of-a-stock/)
- 🟡 [2134. Minimum Swaps to Group All 1's Together II](https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/)
- 🟡 [2260. Minimum Consecutive Cards to Pick Up](https://leetcode.com/problems/minimum-consecutive-cards-to-pick-up/)
- 🟡 [2271. Maximum White Tiles Covered by a Carpet](https://leetcode.com/problems/maximum-white-tiles-covered-by-a-carpet/)
- 🟡 [2401. Longest Nice Subarray](https://leetcode.com/problems/longest-nice-subarray/)
- 🟡 [2411. Smallest Subarrays With Maximum Bitwise OR](https://leetcode.com/problems/smallest-subarrays-with-maximum-bitwise-or/)
- 🔴 [2524. Maximum Frequency Score of a Subarray](https://leetcode.com/problems/maximum-frequency-score-of-a-subarray/) 🔒
- 🔴 [2528. Maximize the Minimum Powered City](https://leetcode.com/problems/maximize-the-minimum-powered-city/)
- 🟡 [2537. Count the Number of Good Subarrays](https://leetcode.com/problems/count-the-number-of-good-subarrays/)
- 🟡 [2555. Maximize Win From Two Segments](https://leetcode.com/problems/maximize-win-from-two-segments/)
- 🟡 [2653. Sliding Subarray Beauty](https://leetcode.com/problems/sliding-subarray-beauty/)
- 🟡 [2730. Find the Longest Semi-Repetitive Substring](https://leetcode.com/problems/find-the-longest-semi-repetitive-substring/)
- 🟡 [2743. Count Substrings Without Repeating Character](https://leetcode.com/problems/count-substrings-without-repeating-character/) 🔒
- 🟡 [2747. Count Zero Request Servers](https://leetcode.com/problems/count-zero-request-servers/)
- 🟢 [2760. Longest Even Odd Subarray With Threshold](https://leetcode.com/problems/longest-even-odd-subarray-with-threshold/)
- 🟡 [2779. Maximum Beauty of an Array After Applying Operation](https://leetcode.com/problems/maximum-beauty-of-an-array-after-applying-operation/)
- 🔴 [2781. Length of the Longest Valid Substring](https://leetcode.com/problems/length-of-the-longest-valid-substring/)
- 🟡 [2799. Count Complete Subarrays in an Array](https://leetcode.com/problems/count-complete-subarrays-in-an-array/)
- 🟡 [2831. Find the Longest Equal Subarray](https://leetcode.com/problems/find-the-longest-equal-subarray/)
- 🟡 [2841. Maximum Sum of Almost Unique Subarray](https://leetcode.com/problems/maximum-sum-of-almost-unique-subarray/)
- 🟡 [2875. Minimum Size Subarray in Infinite Array](https://leetcode.com/problems/minimum-size-subarray-in-infinite-array/)
- 🔴 [2902. Count of Sub-Multisets With Bounded Sum](https://leetcode.com/problems/count-of-sub-multisets-with-bounded-sum/)
- 🟡 [2904. Shortest and Lexicographically Smallest Beautiful String](https://leetcode.com/problems/shortest-and-lexicographically-smallest-beautiful-string/)
- 🔴 [2953. Count Complete Substrings](https://leetcode.com/problems/count-complete-substrings/)
- 🔴 [2968. Apply Operations to Maximize Frequency Score](https://leetcode.com/problems/apply-operations-to-maximize-frequency-score/)
- 🟡 [2981. Find Longest Special Substring That Occurs Thrice I](https://leetcode.com/problems/find-longest-special-substring-that-occurs-thrice-i/)
- 🟡 [2982. Find Longest Special Substring That Occurs Thrice II](https://leetcode.com/problems/find-longest-special-substring-that-occurs-thrice-ii/)
- 🔴 [3013. Divide an Array Into Subarrays With Minimum Cost II](https://leetcode.com/problems/divide-an-array-into-subarrays-with-minimum-cost-ii/)
- 🟢 [3090. Maximum Length Substring With Two Occurrences](https://leetcode.com/problems/maximum-length-substring-with-two-occurrences/)
- 🔴 [3134. Find the Median of the Uniqueness Array](https://leetcode.com/problems/find-the-median-of-the-uniqueness-array/)
- 🟡 [3191. Minimum Operations to Make Binary Array Elements Equal to One I](https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-i/)
- 🟢 [3206. Alternating Groups I](https://leetcode.com/problems/alternating-groups-i/)
- 🟡 [3208. Alternating Groups II](https://leetcode.com/problems/alternating-groups-ii/)
- 🟡 [3297. Count Substrings That Can Be Rearranged to Contain a String I](https://leetcode.com/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-i/)
- 🔴 [3298. Count Substrings That Can Be Rearranged to Contain a String II](https://leetcode.com/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-ii/)
- 🟡 [3346. Maximum Frequency of an Element After Performing Operations I](https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-i/)
- 🔴 [3347. Maximum Frequency of an Element After Performing Operations II](https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-ii/)
- 🟢 [3364. Minimum Positive Sum Subarray ](https://leetcode.com/problems/minimum-positive-sum-subarray/)
- 🟢 [3411. Maximum Subarray With Equal Products](https://leetcode.com/problems/maximum-subarray-with-equal-products/)
- 🟡 [3422. Minimum Operations to Make Subarray Elements Equal](https://leetcode.com/problems/minimum-operations-to-make-subarray-elements-equal/) 🔒
- 🟡 [3439. Reschedule Meetings for Maximum Free Time I](https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-i/)
- 🔴 [3445. Maximum Difference Between Even and Odd Frequency II](https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-ii/)
- 🟡 [3634. Minimum Removals to Balance Array](https://leetcode.com/problems/minimum-removals-to-balance-array/)
- 🟡 [3641. Longest Semi-Repeating Subarray](https://leetcode.com/problems/longest-semi-repeating-subarray/) 🔒
- 🟡 [3652. Best Time to Buy and Sell Stock using Strategy](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-using-strategy/)
- 🟡 [3672. Sum of Weighted Modes in Subarrays](https://leetcode.com/problems/sum-of-weighted-modes-in-subarrays/) 🔒
- 🟡 [3679.  Minimum Discards to Balance Inventory](https://leetcode.com/problems/minimum-discards-to-balance-inventory/)
- 🟡 [3694. Distinct Points Reachable After Substring Removal](https://leetcode.com/problems/distinct-points-reachable-after-substring-removal/)
- 🟡 [3851. Maximum Requests Without Violating the Limit](https://leetcode.com/problems/maximum-requests-without-violating-the-limit/) 🔒
- 🟡 [3969. Valid Subarrays With Matching Sum Digits I](https://leetcode.com/problems/valid-subarrays-with-matching-sum-digits-i/)
- 🔴 [3972. Valid Subarrays With Matching Sum Digits II](https://leetcode.com/problems/valid-subarrays-with-matching-sum-digits-ii/) 🔒
- 🟡 [4044. Count Good Cyclic Rotations](https://leetcode.com/problems/count-good-cyclic-rotations/)
- 🟡 [4067. Longest Subarray With Restricted Pair Sums](https://leetcode.com/problems/longest-subarray-with-restricted-pair-sums/)

</details>

<details><summary><b>Fixed / K-bounded Window</b> (40)</summary>

- 🟡 [340. Longest Substring with At Most K Distinct Characters](https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/) 🔒
- 🟡 [395. Longest Substring with At Least K Repeating Characters](https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/)
- 🟡 [438. Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string/)
- 🟡 [567. Permutation in String](https://leetcode.com/problems/permutation-in-string/)
- 🔴 [992. Subarrays with K Different Integers](https://leetcode.com/problems/subarrays-with-k-different-integers/)
- 🔴 [995. Minimum Number of K Consecutive Bit Flips](https://leetcode.com/problems/minimum-number-of-k-consecutive-bit-flips/)
- 🟡 [1100. Find K-Length Substrings With No Repeated Characters](https://leetcode.com/problems/find-k-length-substrings-with-no-repeated-characters/) 🔒
- 🟡 [1343. Number of Sub-arrays of Size K and Average Greater than or Equal to Threshold](https://leetcode.com/problems/number-of-sub-arrays-of-size-k-and-average-greater-than-or-equal-to-threshold/)
- 🔴 [1703. Minimum Adjacent Swaps for K Consecutive Ones](https://leetcode.com/problems/minimum-adjacent-swaps-for-k-consecutive-ones/)
- 🔴 [1956. Minimum Time For K Virus Variants to Spread](https://leetcode.com/problems/minimum-time-for-k-virus-variants-to-spread/) 🔒
- 🟢 [1984. Minimum Difference Between Highest and Lowest of K Scores](https://leetcode.com/problems/minimum-difference-between-highest-and-lowest-of-k-scores/)
- 🟡 [2090. K Radius Subarray Averages](https://leetcode.com/problems/k-radius-subarray-averages/)
- 🔴 [2106. Maximum Fruits Harvested After at Most K Steps](https://leetcode.com/problems/maximum-fruits-harvested-after-at-most-k-steps/)
- 🟡 [2107. Number of Unique Flavors After Sharing K Candies](https://leetcode.com/problems/number-of-unique-flavors-after-sharing-k-candies/) 🔒
- 🟢 [2269. Find the K-Beauty of a Number](https://leetcode.com/problems/find-the-k-beauty-of-a-number/)
- 🔴 [2302. Count Subarrays With Score Less Than K](https://leetcode.com/problems/count-subarrays-with-score-less-than-k/)
- 🟢 [2379. Minimum Recolors to Get K Consecutive Black Blocks](https://leetcode.com/problems/minimum-recolors-to-get-k-consecutive-black-blocks/)
- 🟡 [2461. Maximum Sum of Distinct Subarrays With Length K](https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/)
- 🟡 [2516. Take K of Each Character From Left and Right](https://leetcode.com/problems/take-k-of-each-character-from-left-and-right/)
- 🟡 [2958. Length of Longest Subarray With at Most K Frequency](https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency/)
- 🟡 [2962. Count Subarrays Where Max Element Appears at Least K Times](https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/)
- 🔴 [3086. Minimum Moves to Pick K Ones](https://leetcode.com/problems/minimum-moves-to-pick-k-ones/)
- 🟢 [3095. Shortest Subarray With OR at Least K I](https://leetcode.com/problems/shortest-subarray-with-or-at-least-k-i/)
- 🟡 [3097. Shortest Subarray With OR at Least K II](https://leetcode.com/problems/shortest-subarray-with-or-at-least-k-ii/)
- 🟡 [3254. Find the Power of K-Size Subarrays I](https://leetcode.com/problems/find-the-power-of-k-size-subarrays-i/)
- 🟡 [3255. Find the Power of K-Size Subarrays II](https://leetcode.com/problems/find-the-power-of-k-size-subarrays-ii/)
- 🟢 [3258. Count Substrings That Satisfy K-Constraint I](https://leetcode.com/problems/count-substrings-that-satisfy-k-constraint-i/)
- 🔴 [3261. Count Substrings That Satisfy K-Constraint II](https://leetcode.com/problems/count-substrings-that-satisfy-k-constraint-ii/)
- 🟡 [3305. Count of Substrings Containing Every Vowel and K Consonants I](https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-i/)
- 🟡 [3306. Count of Substrings Containing Every Vowel and K Consonants II](https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/)
- 🟢 [3318. Find X-Sum of All K-Long Subarrays I](https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-i/)
- 🔴 [3321. Find X-Sum of All K-Long Subarrays II](https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-ii/)
- 🟡 [3325. Count Substrings With K-Frequency Characters I](https://leetcode.com/problems/count-substrings-with-k-frequency-characters-i/)
- 🔴 [3329. Count Substrings With K-Frequency Characters II](https://leetcode.com/problems/count-substrings-with-k-frequency-characters-ii/) 🔒
- 🟡 [3413. Maximum Coins From K Consecutive Bags](https://leetcode.com/problems/maximum-coins-from-k-consecutive-bags/)
- 🔴 [3505. Minimum Operations to Make Elements Within K Subarrays Equal](https://leetcode.com/problems/minimum-operations-to-make-elements-within-k-subarrays-equal/)
- 🟡 [3795. Minimum Subarray Length With Distinct Sum At Least K](https://leetcode.com/problems/minimum-subarray-length-with-distinct-sum-at-least-k/)
- 🔴 [3859. Count Subarrays With K Distinct Integers](https://leetcode.com/problems/count-subarrays-with-k-distinct-integers/)
- 🟡 [4032. Longest Subarray With at Most K Distinct Prime Factors](https://leetcode.com/problems/longest-subarray-with-at-most-k-distinct-prime-factors/)
- 🟢 [4043. Count Rotations With Exactly K Equal Adjacent Pairs](https://leetcode.com/problems/count-rotations-with-exactly-k-equal-adjacent-pairs/)

</details>

<details><summary><b>Guessed from title (no tags yet)</b> (11)</summary>

- 🟡 [4072. Maximum Alternating Subarray Sum With One Deletion](https://leetcode.com/problems/maximum-alternating-subarray-sum-with-one-deletion/)
- 🟡 [4075. Longest Resilient Subarray I](https://leetcode.com/problems/longest-resilient-subarray-i/)
- 🟡 [4076. Longest Resilient Subarray II](https://leetcode.com/problems/longest-resilient-subarray-ii/)
- 🟡 [4087. Maximum Subarray Sum of Fixed Length After at Most K Swaps](https://leetcode.com/problems/maximum-subarray-sum-of-fixed-length-after-at-most-k-swaps/) 🔒
- 🟡 [4089. Count Subarrays With Loose Bounds](https://leetcode.com/problems/count-subarrays-with-loose-bounds/)
- 🟡 [4090. Count Magical Substring Pairs I](https://leetcode.com/problems/count-magical-substring-pairs-i/)
- 🔴 [4091. Count Magical Substring Pairs II](https://leetcode.com/problems/count-magical-substring-pairs-ii/)
- 🟡 [4094. Count Frequency Staircase Subarrays I](https://leetcode.com/problems/count-frequency-staircase-subarrays-i/)
- 🔴 [4095. Count Frequency Staircase Subarrays II](https://leetcode.com/problems/count-frequency-staircase-subarrays-ii/)
- 🟢 [4111. Count Consistent Subarrays I](https://leetcode.com/problems/count-consistent-subarrays-i/)
- 🔴 [4114. Count Consistent Subarrays II](https://leetcode.com/problems/count-consistent-subarrays-ii/)

</details>

<details><summary><b>Running Min / Max</b> (1)</summary>

- 🟢 [121. Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/)

</details>

## Fast & Slow Pointers

*Cycle detection, middle of a list, repeating sequences.* — 10 problems

<details><summary><b>Cycle Detection</b> (4)</summary>

- 🟢 [141. Linked List Cycle](https://leetcode.com/problems/linked-list-cycle/)
- 🟡 [142. Linked List Cycle II](https://leetcode.com/problems/linked-list-cycle-ii/)
- 🟢 [202. Happy Number](https://leetcode.com/problems/happy-number/)
- 🟡 [287. Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/)

</details>

<details><summary><b>Two Pointers on a List</b> (4)</summary>

- 🟢 [160. Intersection of Two Linked Lists](https://leetcode.com/problems/intersection-of-two-linked-lists/)
- 🟡 [457. Circular Array Loop](https://leetcode.com/problems/circular-array-loop/)
- 🟡 [957. Prison Cells After N Days](https://leetcode.com/problems/prison-cells-after-n-days/)
- 🟡 [2095. Delete the Middle Node of a Linked List](https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/)

</details>

<details><summary><b>Find Middle</b> (2)</summary>

- 🟢 [234. Palindrome Linked List](https://leetcode.com/problems/palindrome-linked-list/)
- 🟢 [876. Middle of the Linked List](https://leetcode.com/problems/middle-of-the-linked-list/)

</details>

## Prefix Sum & Difference Array

*Many range-sum questions; subarray sums equal to K.* — 127 problems

<details><summary><b>Prefix Sum</b> (69)</summary>

- 🟢 [303. Range Sum Query - Immutable](https://leetcode.com/problems/range-sum-query-immutable/)
- 🟡 [370. Range Addition](https://leetcode.com/problems/range-addition/) 🔒
- 🟢 [724. Find Pivot Index](https://leetcode.com/problems/find-pivot-index/)
- 🔴 [798. Smallest Rotation with Highest Score](https://leetcode.com/problems/smallest-rotation-with-highest-score/)
- 🟡 [848. Shifting Letters](https://leetcode.com/problems/shifting-letters/)
- 🟡 [1109. Corporate Flight Bookings](https://leetcode.com/problems/corporate-flight-bookings/)
- 🟡 [1310. XOR Queries of a Subarray](https://leetcode.com/problems/xor-queries-of-a-subarray/)
- 🟢 [1413. Minimum Value to Get Positive Step by Step Sum](https://leetcode.com/problems/minimum-value-to-get-positive-step-by-step-sum/)
- 🟢 [1422. Maximum Score After Splitting a String](https://leetcode.com/problems/maximum-score-after-splitting-a-string/)
- 🟢 [1480. Running Sum of 1d Array](https://leetcode.com/problems/running-sum-of-1d-array/)
- 🟢 [1588. Sum of All Odd Length Subarrays](https://leetcode.com/problems/sum-of-all-odd-length-subarrays/)
- 🟡 [1589. Maximum Sum Obtained of Any Permutation](https://leetcode.com/problems/maximum-sum-obtained-of-any-permutation/)
- 🟡 [1664. Ways to Make a Fair Array](https://leetcode.com/problems/ways-to-make-a-fair-array/)
- 🟡 [1685. Sum of Absolute Differences in a Sorted Array](https://leetcode.com/problems/sum-of-absolute-differences-in-a-sorted-array/)
- 🟢 [1732. Find the Highest Altitude](https://leetcode.com/problems/find-the-highest-altitude/)
- 🟡 [1744. Can You Eat Your Favorite Candy on Your Favorite Day?](https://leetcode.com/problems/can-you-eat-your-favorite-candy-on-your-favorite-day/)
- 🟡 [1769. Minimum Number of Operations to Move All Balls to Each Box](https://leetcode.com/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/)
- 🟡 [1829. Maximum XOR for Each Query](https://leetcode.com/problems/maximum-xor-for-each-query/)
- 🟢 [1854. Maximum Population Year](https://leetcode.com/problems/maximum-population-year/)
- 🟡 [1906. Minimum Absolute Difference Queries](https://leetcode.com/problems/minimum-absolute-difference-queries/)
- 🟢 [1991. Find the Middle Index in Array](https://leetcode.com/problems/find-the-middle-index-in-array/)
- 🟡 [2021. Brightest Position on Street](https://leetcode.com/problems/brightest-position-on-street/) 🔒
- 🟡 [2145. Count the Hidden Sequences](https://leetcode.com/problems/count-the-hidden-sequences/)
- 🟡 [2171. Removing Minimum Number of Magic Beans](https://leetcode.com/problems/removing-minimum-number-of-magic-beans/)
- 🟡 [2207. Maximize Number of Subsequences in a String](https://leetcode.com/problems/maximize-number-of-subsequences-in-a-string/)
- 🟡 [2219. Maximum Sum Score of Array](https://leetcode.com/problems/maximum-sum-score-of-array/) 🔒
- 🟡 [2237. Count Positions on Street With Required Brightness](https://leetcode.com/problems/count-positions-on-street-with-required-brightness/) 🔒
- 🟡 [2256. Minimum Average Difference](https://leetcode.com/problems/minimum-average-difference/)
- 🟡 [2270. Number of Ways to Split Array](https://leetcode.com/problems/number-of-ways-to-split-array/)
- 🟡 [2381. Shifting Letters II](https://leetcode.com/problems/shifting-letters-ii/)
- 🟡 [2391. Minimum Amount of Time to Collect Garbage](https://leetcode.com/problems/minimum-amount-of-time-to-collect-garbage/)
- 🟡 [2438. Range Product Queries of Powers](https://leetcode.com/problems/range-product-queries-of-powers/)
- 🟡 [2483. Minimum Penalty for a Shop](https://leetcode.com/problems/minimum-penalty-for-a-shop/)
- 🟢 [2485. Find the Pivot Integer](https://leetcode.com/problems/find-the-pivot-integer/)
- 🟡 [2505. Bitwise OR of All Subsequence Sums](https://leetcode.com/problems/bitwise-or-of-all-subsequence-sums/) 🔒
- 🟡 [2559. Count Vowel Strings in Ranges](https://leetcode.com/problems/count-vowel-strings-in-ranges/)
- 🟢 [2574. Left and Right Sum Differences](https://leetcode.com/problems/left-and-right-sum-differences/)
- 🟡 [2587. Rearrange Array to Maximize Prefix Score](https://leetcode.com/problems/rearrange-array-to-maximize-prefix-score/)
- 🟡 [2640. Find the Score of All Prefixes of an Array](https://leetcode.com/problems/find-the-score-of-all-prefixes-of-an-array/)
- 🟡 [2680. Maximum OR](https://leetcode.com/problems/maximum-or/)
- 🟡 [2731. Movement of Robots](https://leetcode.com/problems/movement-of-robots/)
- 🟡 [2772. Apply Operations to Make All Array Elements Equal to Zero](https://leetcode.com/problems/apply-operations-to-make-all-array-elements-equal-to-zero/)
- 🟢 [2873. Maximum Value of an Ordered Triplet I](https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-i/)
- 🟡 [2874. Maximum Value of an Ordered Triplet II](https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-ii/)
- 🟡 [2909. Minimum Sum of Mountain Triplets II](https://leetcode.com/problems/minimum-sum-of-mountain-triplets-ii/)
- 🟡 [2971. Find Polygon With the Largest Perimeter](https://leetcode.com/problems/find-polygon-with-the-largest-perimeter/)
- 🟢 [3028. Ant on the Boundary](https://leetcode.com/problems/ant-on-the-boundary/)
- 🟡 [3096. Minimum Levels to Gain More Points](https://leetcode.com/problems/minimum-levels-to-gain-more-points/)
- 🟡 [3179. Find the N-th Value After K Seconds](https://leetcode.com/problems/find-the-n-th-value-after-k-seconds/)
- 🟢 [3354. Make Array Elements Equal to Zero](https://leetcode.com/problems/make-array-elements-equal-to-zero/)
- 🟡 [3355. Zero Array Transformation I](https://leetcode.com/problems/zero-array-transformation-i/)
- 🟡 [3361. Shift Distance Between Two Strings](https://leetcode.com/problems/shift-distance-between-two-strings/)
- 🟢 [3427. Sum of Variable Length Subarrays](https://leetcode.com/problems/sum-of-variable-length-subarrays/)
- 🟢 [3432. Count Partitions with Even Sum Difference](https://leetcode.com/problems/count-partitions-with-even-sum-difference/)
- 🟡 [3494. Find the Minimum Amount of Time to Brew Potions](https://leetcode.com/problems/find-the-minimum-amount-of-time-to-brew-potions/)
- 🟡 [3511. Make a Positive Array](https://leetcode.com/problems/make-a-positive-array/) 🔒
- 🟡 [3540. Minimum Time to Visit All Houses](https://leetcode.com/problems/minimum-time-to-visit-all-houses/) 🔒
- 🟡 [3653. XOR After Range Multiplication Queries I](https://leetcode.com/problems/xor-after-range-multiplication-queries-i/)
- 🔴 [3655. XOR After Range Multiplication Queries II](https://leetcode.com/problems/xor-after-range-multiplication-queries-ii/)
- 🟡 [3698. Split Array With Minimum Difference](https://leetcode.com/problems/split-array-with-minimum-difference/)
- 🟢 [3707. Equal Score Substrings](https://leetcode.com/problems/equal-score-substrings/)
- 🟡 [3756. Concatenate Non-Zero Digits and Multiply by Sum II](https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-ii/)
- 🟡 [3788. Maximum Score of a Split](https://leetcode.com/problems/maximum-score-of-a-split/)
- 🟡 [3862. Find the Smallest Balanced Index](https://leetcode.com/problems/find-the-smallest-balanced-index/)
- 🔴 [3864. Minimum Cost to Partition a Binary String](https://leetcode.com/problems/minimum-cost-to-partition-a-binary-string/)
- 🟢 [3903. Smallest Stable Index I](https://leetcode.com/problems/smallest-stable-index-i/)
- 🟡 [3904. Smallest Stable Index II](https://leetcode.com/problems/smallest-stable-index-ii/)
- 🟡 [3919. Minimum Cost to Move Between Indices](https://leetcode.com/problems/minimum-cost-to-move-between-indices/)
- 🟡 [3964. Minimum Lights to Illuminate a Road](https://leetcode.com/problems/minimum-lights-to-illuminate-a-road/)

</details>

<details><summary><b>Prefix Sum + Hash Map</b> (41)</summary>

- 🟡 [325. Maximum Size Subarray Sum Equals k](https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/) 🔒
- 🟡 [523. Continuous Subarray Sum](https://leetcode.com/problems/continuous-subarray-sum/)
- 🟡 [525. Contiguous Array](https://leetcode.com/problems/contiguous-array/)
- 🔴 [548. Split Array with Equal Sum](https://leetcode.com/problems/split-array-with-equal-sum/) 🔒
- 🟡 [560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/)
- 🟡 [974. Subarray Sums Divisible by K](https://leetcode.com/problems/subarray-sums-divisible-by-k/)
- 🟡 [1177. Can Make Palindrome from Substring](https://leetcode.com/problems/can-make-palindrome-from-substring/)
- 🟡 [1371. Find the Longest Substring Containing Vowels in Even Counts](https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/)
- 🟡 [1442. Count Triplets That Can Form Two Arrays of Equal XOR](https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/)
- 🟡 [1590. Make Sum Divisible by P](https://leetcode.com/problems/make-sum-divisible-by-p/)
- 🟡 [1674. Minimum Moves to Make Array Complementary](https://leetcode.com/problems/minimum-moves-to-make-array-complementary/)
- 🟡 [1737. Change Minimum Characters to Satisfy One of Three Conditions](https://leetcode.com/problems/change-minimum-characters-to-satisfy-one-of-three-conditions/)
- 🔴 [1788. Maximize the Beauty of the Garden](https://leetcode.com/problems/maximize-the-beauty-of-the-garden/) 🔒
- 🟢 [1893. Check if All the Integers in a Range Are Covered](https://leetcode.com/problems/check-if-all-the-integers-in-a-range-are-covered/)
- 🟡 [1915. Number of Wonderful Substrings](https://leetcode.com/problems/number-of-wonderful-substrings/)
- 🟡 [1930. Unique Length-3 Palindromic Subsequences](https://leetcode.com/problems/unique-length-3-palindromic-subsequences/)
- 🟡 [1943. Describe the Painting](https://leetcode.com/problems/describe-the-painting/)
- 🟡 [1983. Widest Pair of Indices With Equal Range Sum](https://leetcode.com/problems/widest-pair-of-indices-with-equal-range-sum/) 🔒
- 🔴 [2025. Maximum Number of Ways to Partition an Array](https://leetcode.com/problems/maximum-number-of-ways-to-partition-an-array/)
- 🟡 [2083. Substrings That Begin and End With the Same Letter](https://leetcode.com/problems/substrings-that-begin-and-end-with-the-same-letter/) 🔒
- 🔴 [2488. Count Subarrays With Median K](https://leetcode.com/problems/count-subarrays-with-median-k/)
- 🟡 [2489. Number of Substrings With Fixed Ratio](https://leetcode.com/problems/number-of-substrings-with-fixed-ratio/) 🔒
- 🟡 [2588. Count the Number of Beautiful Subarrays](https://leetcode.com/problems/count-the-number-of-beautiful-subarrays/)
- 🟡 [2615. Sum of Distances](https://leetcode.com/problems/sum-of-distances/)
- 🟡 [2845. Count of Interesting Subarrays](https://leetcode.com/problems/count-of-interesting-subarrays/)
- 🟢 [2848. Points That Intersect With Cars](https://leetcode.com/problems/points-that-intersect-with-cars/)
- 🟡 [2947. Count Beautiful Substrings I](https://leetcode.com/problems/count-beautiful-substrings-i/)
- 🔴 [2949. Count Beautiful Substrings II](https://leetcode.com/problems/count-beautiful-substrings-ii/)
- 🟡 [2950. Number of Divisible Substrings](https://leetcode.com/problems/number-of-divisible-substrings/) 🔒
- 🟡 [2955. Number of Same-End Substrings](https://leetcode.com/problems/number-of-same-end-substrings/) 🔒
- 🔴 [2983. Palindrome Rearrangement Queries](https://leetcode.com/problems/palindrome-rearrangement-queries/)
- 🟡 [3026. Maximum Good Subarray Sum](https://leetcode.com/problems/maximum-good-subarray-sum/)
- 🟡 [3224. Minimum Array Changes to Make Differences Equal](https://leetcode.com/problems/minimum-array-changes-to-make-differences-equal/)
- 🔴 [3279. Maximum Total Area Occupied by Pistons](https://leetcode.com/problems/maximum-total-area-occupied-by-pistons/) 🔒
- 🟡 [3381. Maximum Subarray Sum With Length Divisible by K](https://leetcode.com/problems/maximum-subarray-sum-with-length-divisible-by-k/)
- 🟡 [3714. Longest Balanced Substring II](https://leetcode.com/problems/longest-balanced-substring-ii/)
- 🟡 [3728. Stable Subarrays With Equal Boundary and Interior Sum](https://leetcode.com/problems/stable-subarrays-with-equal-boundary-and-interior-sum/)
- 🔴 [3729. Count Distinct Subarrays Divisible by K in Sorted Array](https://leetcode.com/problems/count-distinct-subarrays-divisible-by-k-in-sorted-array/)
- 🟡 [3755. Find Maximum Balanced XOR Subarray Length](https://leetcode.com/problems/find-maximum-balanced-xor-subarray-length/)
- 🟡 [3900. Longest Balanced Substring After One Swap](https://leetcode.com/problems/longest-balanced-substring-after-one-swap/)
- 🟡 [4063. Longest Subarray Divisible by K with At Most One Negation I](https://leetcode.com/problems/longest-subarray-divisible-by-k-with-at-most-one-negation-i/)

</details>

<details><summary><b>2-D Prefix Sum</b> (16)</summary>

- 🟡 [304. Range Sum Query 2D - Immutable](https://leetcode.com/problems/range-sum-query-2d-immutable/)
- 🔴 [1074. Number of Submatrices That Sum to Target](https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/)
- 🟡 [1314. Matrix Block Sum](https://leetcode.com/problems/matrix-block-sum/)
- 🟡 [1895. Largest Magic Square](https://leetcode.com/problems/largest-magic-square/)
- 🟡 [2017. Grid Game](https://leetcode.com/problems/grid-game/)
- 🔴 [2132. Stamping the Grid](https://leetcode.com/problems/stamping-the-grid/)
- 🟡 [2245. Maximum Trailing Zeros in a Cornered Path](https://leetcode.com/problems/maximum-trailing-zeros-in-a-cornered-path/)
- 🟡 [2428. Maximum Sum of an Hourglass](https://leetcode.com/problems/maximum-sum-of-an-hourglass/)
- 🟡 [2536. Increment Submatrices by One](https://leetcode.com/problems/increment-submatrices-by-one/)
- 🟡 [2906. Construct Product Matrix](https://leetcode.com/problems/construct-product-matrix/)
- 🟡 [3070. Count Submatrices with Top-Left Element and Sum Less Than k](https://leetcode.com/problems/count-submatrices-with-top-left-element-and-sum-less-than-k/)
- 🟡 [3212. Count Submatrices With Equal Frequency of X and Y](https://leetcode.com/problems/count-submatrices-with-equal-frequency-of-x-and-y/)
- 🟡 [3546. Equal Sum Grid Partition I](https://leetcode.com/problems/equal-sum-grid-partition-i/)
- 🔴 [3548. Equal Sum Grid Partition II](https://leetcode.com/problems/equal-sum-grid-partition-ii/)
- 🔴 [3888. Minimum Operations to Make All Grid Elements Equal](https://leetcode.com/problems/minimum-operations-to-make-all-grid-elements-equal/) 🔒
- 🟡 [3933. Largest Local Values in a Matrix II](https://leetcode.com/problems/largest-local-values-in-a-matrix-ii/)

</details>

<details><summary><b>Prefix / Suffix Products</b> (1)</summary>

- 🟡 [238. Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/)

</details>

## Hashing & Counting

*Seen-before lookups, frequencies, grouping, anagrams.* — 265 problems

<details><summary><b>Hash Map / Set Lookup</b> (153)</summary>

- 🟢 [205. Isomorphic Strings](https://leetcode.com/problems/isomorphic-strings/)
- 🟢 [290. Word Pattern](https://leetcode.com/problems/word-pattern/)
- 🟡 [442. Find All Duplicates in an Array](https://leetcode.com/problems/find-all-duplicates-in-an-array/)
- 🟡 [454. 4Sum II](https://leetcode.com/problems/4sum-ii/)
- 🟢 [500. Keyboard Row](https://leetcode.com/problems/keyboard-row/)
- 🟡 [531. Lonely Pixel I](https://leetcode.com/problems/lonely-pixel-i/) 🔒
- 🟡 [533. Lonely Pixel II](https://leetcode.com/problems/lonely-pixel-ii/) 🔒
- 🟡 [554. Brick Wall](https://leetcode.com/problems/brick-wall/)
- 🟢 [575. Distribute Candies](https://leetcode.com/problems/distribute-candies/)
- 🟢 [599. Minimum Index Sum of Two Lists](https://leetcode.com/problems/minimum-index-sum-of-two-lists/)
- 🟡 [609. Find Duplicate File in System](https://leetcode.com/problems/find-duplicate-file-in-system/)
- 🟢 [697. Degree of an Array](https://leetcode.com/problems/degree-of-an-array/)
- 🟢 [734. Sentence Similarity](https://leetcode.com/problems/sentence-similarity/) 🔒
- 🟢 [748. Shortest Completing Word](https://leetcode.com/problems/shortest-completing-word/)
- 🟢 [771. Jewels and Stones](https://leetcode.com/problems/jewels-and-stones/)
- 🟡 [791. Custom Sort String](https://leetcode.com/problems/custom-sort-string/)
- 🟢 [804. Unique Morse Code Words](https://leetcode.com/problems/unique-morse-code-words/)
- 🟡 [822. Card Flipping Game](https://leetcode.com/problems/card-flipping-game/)
- 🟡 [833. Find And Replace in String](https://leetcode.com/problems/find-and-replace-in-string/)
- 🟢 [859. Buddy Strings](https://leetcode.com/problems/buddy-strings/)
- 🟡 [874. Walking Robot Simulation](https://leetcode.com/problems/walking-robot-simulation/)
- 🟢 [888. Fair Candy Swap](https://leetcode.com/problems/fair-candy-swap/)
- 🟡 [890. Find and Replace Pattern](https://leetcode.com/problems/find-and-replace-pattern/)
- 🟡 [916. Word Subsets](https://leetcode.com/problems/word-subsets/)
- 🟢 [929. Unique Email Addresses](https://leetcode.com/problems/unique-email-addresses/)
- 🟢 [953. Verifying an Alien Dictionary](https://leetcode.com/problems/verifying-an-alien-dictionary/)
- 🟡 [966. Vowel Spellchecker](https://leetcode.com/problems/vowel-spellchecker/)
- 🔴 [1001. Grid Illumination](https://leetcode.com/problems/grid-illumination/)
- 🟢 [1002. Find Common Characters](https://leetcode.com/problems/find-common-characters/)
- 🟡 [1072. Flip Columns For Maximum Number of Equal Rows](https://leetcode.com/problems/flip-columns-for-maximum-number-of-equal-rows/)
- 🟢 [1122. Relative Sort Array](https://leetcode.com/problems/relative-sort-array/)
- 🟢 [1133. Largest Unique Number](https://leetcode.com/problems/largest-unique-number/) 🔒
- 🟡 [1138. Alphabet Board Path](https://leetcode.com/problems/alphabet-board-path/)
- 🟡 [1152. Analyze User Website Visit Pattern](https://leetcode.com/problems/analyze-user-website-visit-pattern/) 🔒
- 🟢 [1165. Single-Row Keyboard](https://leetcode.com/problems/single-row-keyboard/) 🔒
- 🟡 [1169. Invalid Transactions](https://leetcode.com/problems/invalid-transactions/)
- 🟡 [1181. Before and After Puzzle](https://leetcode.com/problems/before-and-after-puzzle/) 🔒
- 🟢 [1207. Unique Number of Occurrences](https://leetcode.com/problems/unique-number-of-occurrences/)
- 🔴 [1224. Maximum Equal Frequency](https://leetcode.com/problems/maximum-equal-frequency/)
- 🟢 [1275. Find Winner on a Tic Tac Toe Game](https://leetcode.com/problems/find-winner-on-a-tic-tac-toe-game/)
- 🟢 [1331. Rank Transform of an Array](https://leetcode.com/problems/rank-transform-of-an-array/)
- 🟢 [1365. How Many Numbers Are Smaller Than the Current Number](https://leetcode.com/problems/how-many-numbers-are-smaller-than-the-current-number/)
- 🟡 [1410. HTML Entity Parser](https://leetcode.com/problems/html-entity-parser/)
- 🟡 [1418. Display Table of Food Orders in a Restaurant](https://leetcode.com/problems/display-table-of-food-orders-in-a-restaurant/)
- 🟢 [1426. Counting Elements](https://leetcode.com/problems/counting-elements/) 🔒
- 🟢 [1436. Destination City](https://leetcode.com/problems/destination-city/)
- 🟡 [1452. People Whose List of Favorite Companies Is Not a Subset of Another List](https://leetcode.com/problems/people-whose-list-of-favorite-companies-is-not-a-subset-of-another-list/)
- 🟢 [1460. Make Two Arrays Equal by Reversing Subarrays](https://leetcode.com/problems/make-two-arrays-equal-by-reversing-subarrays/)
- 🟡 [1487. Making File Names Unique](https://leetcode.com/problems/making-file-names-unique/)
- 🟢 [1496. Path Crossing](https://leetcode.com/problems/path-crossing/)
- 🟡 [1540. Can Convert String in K Moves](https://leetcode.com/problems/can-convert-string-in-k-moves/)
- 🟡 [1604. Alert Using Same Key-Card Three or More Times in a One Hour Period](https://leetcode.com/problems/alert-using-same-key-card-three-or-more-times-in-a-one-hour-period/)
- 🟢 [1624. Largest Substring Between Two Equal Characters](https://leetcode.com/problems/largest-substring-between-two-equal-characters/)
- 🟡 [1630. Arithmetic Subarrays](https://leetcode.com/problems/arithmetic-subarrays/)
- 🟢 [1636. Sort Array by Increasing Frequency](https://leetcode.com/problems/sort-array-by-increasing-frequency/)
- 🟢 [1640. Check Array Formation Through Concatenation](https://leetcode.com/problems/check-array-formation-through-concatenation/)
- 🟡 [1711. Count Good Meals](https://leetcode.com/problems/count-good-meals/)
- 🟡 [1772. Sort Features by Popularity](https://leetcode.com/problems/sort-features-by-popularity/) 🔒
- 🟢 [1796. Second Largest Digit in a String](https://leetcode.com/problems/second-largest-digit-in-a-string/)
- 🟢 [1805. Number of Different Integers in a String](https://leetcode.com/problems/number-of-different-integers-in-a-string/)
- 🟡 [1807. Evaluate the Bracket Pairs of a String](https://leetcode.com/problems/evaluate-the-bracket-pairs-of-a-string/)
- 🟡 [1817. Finding the Users Active Minutes](https://leetcode.com/problems/finding-the-users-active-minutes/)
- 🟢 [1832. Check if the Sentence Is Pangram](https://leetcode.com/problems/check-if-the-sentence-is-pangram/)
- 🟢 [1935. Maximum Number of Words You Can Type](https://leetcode.com/problems/maximum-number-of-words-you-can-type/)
- 🟢 [1995. Count Special Quadruplets](https://leetcode.com/problems/count-special-quadruplets/)
- 🟢 [2062. Count Vowel Substrings of a String](https://leetcode.com/problems/count-vowel-substrings-of-a-string/)
- 🟢 [2094. Finding 3-Digit Even Numbers](https://leetcode.com/problems/finding-3-digit-even-numbers/)
- 🟢 [2103. Rings and Rods](https://leetcode.com/problems/rings-and-rods/)
- 🟢 [2133. Check if Every Row and Column Contains All Numbers](https://leetcode.com/problems/check-if-every-row-and-column-contains-all-numbers/)
- 🟢 [2154. Keep Multiplying Found Values by Two](https://leetcode.com/problems/keep-multiplying-found-values-by-two/)
- 🟡 [2201. Count Artifacts That Can Be Extracted](https://leetcode.com/problems/count-artifacts-that-can-be-extracted/)
- 🟢 [2215. Find the Difference of Two Arrays](https://leetcode.com/problems/find-the-difference-of-two-arrays/)
- 🟢 [2229. Check if an Array Is Consecutive](https://leetcode.com/problems/check-if-an-array-is-consecutive/) 🔒
- 🟡 [2295. Replace Elements in an Array](https://leetcode.com/problems/replace-elements-in-an-array/)
- 🟢 [2309. Greatest English Letter in Upper and Lower Case](https://leetcode.com/problems/greatest-english-letter-in-upper-and-lower-case/)
- 🟢 [2325. Decode the Message](https://leetcode.com/problems/decode-the-message/)
- 🟡 [2352. Equal Row and Column Pairs](https://leetcode.com/problems/equal-row-and-column-pairs/)
- 🟢 [2363. Merge Similar Items](https://leetcode.com/problems/merge-similar-items/)
- 🟡 [2365. Task Scheduler II](https://leetcode.com/problems/task-scheduler-ii/)
- 🟢 [2395. Find Subarrays With Equal Sum](https://leetcode.com/problems/find-subarrays-with-equal-sum/)
- 🟢 [2399. Check Distances Between Same Letters](https://leetcode.com/problems/check-distances-between-same-letters/)
- 🟢 [2418. Sort the People](https://leetcode.com/problems/sort-the-people/)
- 🟢 [2451. Odd String Difference](https://leetcode.com/problems/odd-string-difference/)
- 🔴 [2459. Sort Array by Moving Items to Empty Space](https://leetcode.com/problems/sort-array-by-moving-items-to-empty-space/) 🔒
- 🟢 [2475. Number of Unequal Triplets in Array](https://leetcode.com/problems/number-of-unequal-triplets-in-array/)
- 🟢 [2605. Form Smallest Number From Two Digit Arrays](https://leetcode.com/problems/form-smallest-number-from-two-digit-arrays/)
- 🟡 [2610. Convert an Array Into a 2D Array With Conditions](https://leetcode.com/problems/convert-an-array-into-a-2d-array-with-conditions/)
- 🟡 [2661. First Completely Painted Row or Column](https://leetcode.com/problems/first-completely-painted-row-or-column/)
- 🟢 [2670. Find the Distinct Difference Array](https://leetcode.com/problems/find-the-distinct-difference-array/)
- 🟢 [2682. Find the Losers of the Circular Game](https://leetcode.com/problems/find-the-losers-of-the-circular-game/)
- 🟡 [2711. Difference of Number of Distinct Values on Diagonals](https://leetcode.com/problems/difference-of-number-of-distinct-values-on-diagonals/)
- 🟢 [2716. Minimize String Length](https://leetcode.com/problems/minimize-string-length/)
- 🟡 [2718. Sum of Matrix After Queries](https://leetcode.com/problems/sum-of-matrix-after-queries/)
- 🟢 [2744. Find Maximum Number of String Pairs](https://leetcode.com/problems/find-maximum-number-of-string-pairs/)
- 🔴 [2763. Sum of Imbalance Numbers of All Subarrays](https://leetcode.com/problems/sum-of-imbalance-numbers-of-all-subarrays/)
- 🟡 [2766. Relocate Marbles](https://leetcode.com/problems/relocate-marbles/)
- 🟡 [2768. Number of Black Blocks](https://leetcode.com/problems/number-of-black-blocks/)
- 🟡 [2780. Minimum Index of a Valid Split](https://leetcode.com/problems/minimum-index-of-a-valid-split/)
- 🟢 [2784. Check if Array is Good](https://leetcode.com/problems/check-if-array-is-good/)
- 🟡 [2808. Minimum Seconds to Equalize a Circular Array](https://leetcode.com/problems/minimum-seconds-to-equalize-a-circular-array/)
- 🟢 [2815. Max Pair Sum in an Array](https://leetcode.com/problems/max-pair-sum-in-an-array/)
- 🟡 [2840. Check if Strings Can be Made Equal With Operations II](https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-ii/)
- 🟡 [2898. Maximum Linear Stock Score](https://leetcode.com/problems/maximum-linear-stock-score/) 🔒
- 🟡 [2933. High-Access Employees](https://leetcode.com/problems/high-access-employees/)
- 🟢 [2956. Find Common Elements Between Two Arrays](https://leetcode.com/problems/find-common-elements-between-two-arrays/)
- 🟡 [2964. Number of Divisible Triplet Sums](https://leetcode.com/problems/number-of-divisible-triplet-sums/) 🔒
- 🟡 [2975. Maximum Square Area by Removing Fences From a Field](https://leetcode.com/problems/maximum-square-area-by-removing-fences-from-a-field/)
- 🟢 [2996. Smallest Missing Integer Greater Than Sequential Prefix Sum](https://leetcode.com/problems/smallest-missing-integer-greater-than-sequential-prefix-sum/)
- 🟡 [3020. Find the Maximum Number of Elements in Subset](https://leetcode.com/problems/find-the-maximum-number-of-elements-in-subset/)
- 🟡 [3078. Match Alphanumerical Pattern in Matrix I](https://leetcode.com/problems/match-alphanumerical-pattern-in-matrix-i/) 🔒
- 🟢 [3083. Existence of a Substring in a String and Its Reverse](https://leetcode.com/problems/existence-of-a-substring-in-a-string-and-its-reverse/)
- 🔴 [3104. Find Longest Self-Contained Substring](https://leetcode.com/problems/find-longest-self-contained-substring/) 🔒
- 🟢 [3120. Count the Number of Special Characters I](https://leetcode.com/problems/count-the-number-of-special-characters-i/)
- 🟡 [3121. Count the Number of Special Characters II](https://leetcode.com/problems/count-the-number-of-special-characters-ii/)
- 🟢 [3146. Permutation Difference between Two Strings](https://leetcode.com/problems/permutation-difference-between-two-strings/)
- 🟡 [3159. Find Occurrences of an Element in an Array](https://leetcode.com/problems/find-occurrences-of-an-element-in-an-array/)
- 🟡 [3160. Find the Number of Distinct Colors Among the Balls](https://leetcode.com/problems/find-the-number-of-distinct-colors-among-the-balls/)
- 🟢 [3162. Find the Number of Good Pairs I](https://leetcode.com/problems/find-the-number-of-good-pairs-i/)
- 🟡 [3164. Find the Number of Good Pairs II](https://leetcode.com/problems/find-the-number-of-good-pairs-ii/)
- 🟡 [3237. Alt and Tab Simulation](https://leetcode.com/problems/alt-and-tab-simulation/) 🔒
- 🟡 [3295. Report Spam Message](https://leetcode.com/problems/report-spam-message/)
- 🟡 [3365. Rearrange K Substrings to Form Target String](https://leetcode.com/problems/rearrange-k-substrings-to-form-target-string/)
- 🟢 [3375. Minimum Operations to Make Array Values Equal to K](https://leetcode.com/problems/minimum-operations-to-make-array-values-equal-to-k/)
- 🟢 [3396. Minimum Number of Operations to Make Elements in Array Distinct](https://leetcode.com/problems/minimum-number-of-operations-to-make-elements-in-array-distinct/)
- 🟡 [3431. Minimum Unlocked Indices to Sort Nums](https://leetcode.com/problems/minimum-unlocked-indices-to-sort-nums/) 🔒
- 🟢 [3450. Maximum Students on a Single Bench](https://leetcode.com/problems/maximum-students-on-a-single-bench/) 🔒
- 🟢 [3471. Find the Largest Almost Missing Integer](https://leetcode.com/problems/find-the-largest-almost-missing-integer/)
- 🟢 [3483. Unique 3-Digit Even Numbers](https://leetcode.com/problems/unique-3-digit-even-numbers/)
- 🟡 [3522. Calculate Score After Performing Instructions](https://leetcode.com/problems/calculate-score-after-performing-instructions/)
- 🟡 [3531. Count Covered Buildings](https://leetcode.com/problems/count-covered-buildings/)
- 🟡 [3551. Minimum Swaps to Sort by Digit Sum](https://leetcode.com/problems/minimum-swaps-to-sort-by-digit-sum/)
- 🟢 [3606. Coupon Code Validator](https://leetcode.com/problems/coupon-code-validator/)
- 🟢 [3668. Restore Finishing Order](https://leetcode.com/problems/restore-finishing-order/)
- 🟢 [3678. Smallest Absent Positive Greater Than Average](https://leetcode.com/problems/smallest-absent-positive-greater-than-average/)
- 🟡 [3682. Minimum Index Sum of Common Elements](https://leetcode.com/problems/minimum-index-sum-of-common-elements/) 🔒
- 🟢 [3718. Smallest Missing Multiple of K](https://leetcode.com/problems/smallest-missing-multiple-of-k/)
- 🟢 [3731. Find Missing Elements](https://leetcode.com/problems/find-missing-elements/)
- 🟢 [3740. Minimum Distance Between Three Equal Elements I](https://leetcode.com/problems/minimum-distance-between-three-equal-elements-i/)
- 🟡 [3741. Minimum Distance Between Three Equal Elements II](https://leetcode.com/problems/minimum-distance-between-three-equal-elements-ii/)
- 🟡 [3760. Maximum Substrings With Distinct Start](https://leetcode.com/problems/maximum-substrings-with-distinct-start/)
- 🟡 [3779. Minimum Number of Operations to Have Distinct Elements](https://leetcode.com/problems/minimum-number-of-operations-to-have-distinct-elements/)
- 🟡 [3784. Minimum Deletion Cost to Make All Characters Equal](https://leetcode.com/problems/minimum-deletion-cost-to-make-all-characters-equal/)
- 🟢 [3803. Count Residue Prefixes](https://leetcode.com/problems/count-residue-prefixes/)
- 🟡 [3804. Number of Centered Subarrays](https://leetcode.com/problems/number-of-centered-subarrays/)
- 🟢 [3842. Toggle Light Bulbs](https://leetcode.com/problems/toggle-light-bulbs/)
- 🟡 [3846. Total Distance to Type a String Using One Finger](https://leetcode.com/problems/total-distance-to-type-a-string-using-one-finger/) 🔒
- 🟡 [3853. Merge Close Characters](https://leetcode.com/problems/merge-close-characters/)
- 🟡 [3923. Minimum Generations to Target Point](https://leetcode.com/problems/minimum-generations-to-target-point/)
- 🟡 [3941. Password Strength](https://leetcode.com/problems/password-strength/)
- 🟡 [4019. Merge Close Characters II](https://leetcode.com/problems/merge-close-characters-ii/) 🔒
- 🟢 [4048. Count Values With Equally Spaced Occurrences I](https://leetcode.com/problems/count-values-with-equally-spaced-occurrences-i/)
- 🟡 [4049. Count Values With Equally Spaced Occurrences II](https://leetcode.com/problems/count-values-with-equally-spaced-occurrences-ii/)
- 🟡 [4104. Count Valid Substrings II](https://leetcode.com/problems/count-valid-substrings-ii/)

</details>

<details><summary><b>Frequency Count</b> (95)</summary>

- 🟡 [229. Majority Element II](https://leetcode.com/problems/majority-element-ii/)
- 🟢 [242. Valid Anagram](https://leetcode.com/problems/valid-anagram/)
- 🟡 [299. Bulls and Cows](https://leetcode.com/problems/bulls-and-cows/)
- 🟢 [383. Ransom Note](https://leetcode.com/problems/ransom-note/)
- 🟢 [387. First Unique Character in a String](https://leetcode.com/problems/first-unique-character-in-a-string/)
- 🟡 [811. Subdomain Visit Count](https://leetcode.com/problems/subdomain-visit-count/)
- 🟢 [819. Most Common Word](https://leetcode.com/problems/most-common-word/)
- 🟢 [884. Uncommon Words from Two Sentences](https://leetcode.com/problems/uncommon-words-from-two-sentences/)
- 🟡 [1010. Pairs of Songs With Total Durations Divisible by 60](https://leetcode.com/problems/pairs-of-songs-with-total-durations-divisible-by-60/)
- 🔴 [1121. Divide Array Into Increasing Sequences](https://leetcode.com/problems/divide-array-into-increasing-sequences/) 🔒
- 🟢 [1128. Number of Equivalent Domino Pairs](https://leetcode.com/problems/number-of-equivalent-domino-pairs/)
- 🟢 [1160. Find Words That Can Be Formed by Characters](https://leetcode.com/problems/find-words-that-can-be-formed-by-characters/)
- 🟢 [1189. Maximum Number of Balloons](https://leetcode.com/problems/maximum-number-of-balloons/)
- 🟢 [1213. Intersection of Three Sorted Arrays](https://leetcode.com/problems/intersection-of-three-sorted-arrays/) 🔒
- 🟡 [1366. Rank Teams by Votes](https://leetcode.com/problems/rank-teams-by-votes/)
- 🟢 [1370. Increasing Decreasing String](https://leetcode.com/problems/increasing-decreasing-string/)
- 🟢 [1394. Find Lucky Integer in an Array](https://leetcode.com/problems/find-lucky-integer-in-an-array/)
- 🟡 [1419. Minimum Number of Frogs Croaking](https://leetcode.com/problems/minimum-number-of-frogs-croaking/)
- 🟡 [1497. Check If Array Pairs Are Divisible by k](https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/)
- 🟡 [1657. Determine if Two Strings Are Close](https://leetcode.com/problems/determine-if-two-strings-are-close/)
- 🟢 [1704. Determine if String Halves Are Alike](https://leetcode.com/problems/determine-if-string-halves-are-alike/)
- 🟡 [1726. Tuple with Same Product](https://leetcode.com/problems/tuple-with-same-product/)
- 🟢 [1748. Sum of Unique Elements](https://leetcode.com/problems/sum-of-unique-elements/)
- 🟡 [1781. Sum of Beauty of All Substrings](https://leetcode.com/problems/sum-of-beauty-of-all-substrings/)
- 🟢 [1790. Check if One String Swap Can Make Strings Equal](https://leetcode.com/problems/check-if-one-string-swap-can-make-strings-equal/)
- 🟢 [1897. Redistribute Characters to Make All Strings Equal](https://leetcode.com/problems/redistribute-characters-to-make-all-strings-equal/)
- 🟡 [1940. Longest Common Subsequence Between Sorted Arrays](https://leetcode.com/problems/longest-common-subsequence-between-sorted-arrays/) 🔒
- 🟢 [1941. Check if All Characters Have Equal Number of Occurrences](https://leetcode.com/problems/check-if-all-characters-have-equal-number-of-occurrences/)
- 🔴 [1982. Find Array Given Subset Sums](https://leetcode.com/problems/find-array-given-subset-sums/)
- 🟢 [2006. Count Number of Pairs With Absolute Difference K](https://leetcode.com/problems/count-number-of-pairs-with-absolute-difference-k/)
- 🟡 [2013. Detect Squares](https://leetcode.com/problems/detect-squares/)
- 🟡 [2023. Number of Pairs of Strings With Concatenation Equal to Target](https://leetcode.com/problems/number-of-pairs-of-strings-with-concatenation-equal-to-target/)
- 🟢 [2053. Kth Distinct String in an Array](https://leetcode.com/problems/kth-distinct-string-in-an-array/)
- 🟢 [2068. Check Whether Two Strings are Almost Equivalent](https://leetcode.com/problems/check-whether-two-strings-are-almost-equivalent/)
- 🟢 [2085. Count Common Words With One Occurrence](https://leetcode.com/problems/count-common-words-with-one-occurrence/)
- 🟢 [2148. Count Elements With Strictly Smaller and Greater Elements ](https://leetcode.com/problems/count-elements-with-strictly-smaller-and-greater-elements/)
- 🟡 [2150. Find All Lonely Numbers in the Array](https://leetcode.com/problems/find-all-lonely-numbers-in-the-array/)
- 🟢 [2190. Most Frequent Number Following Key In an Array](https://leetcode.com/problems/most-frequent-number-following-key-in-an-array/)
- 🟡 [2198. Number of Single Divisor Triplets](https://leetcode.com/problems/number-of-single-divisor-triplets/) 🔒
- 🟡 [2225. Find Players With Zero or One Losses](https://leetcode.com/problems/find-players-with-zero-or-one-losses/)
- 🟢 [2248. Intersection of Multiple Arrays](https://leetcode.com/problems/intersection-of-multiple-arrays/)
- 🟢 [2283. Check if Number Has Equal Digit Count and Digit Value](https://leetcode.com/problems/check-if-number-has-equal-digit-count-and-digit-value/)
- 🟡 [2284. Sender With Largest Word Count](https://leetcode.com/problems/sender-with-largest-word-count/)
- 🟢 [2287. Rearrange Characters to Make Target String](https://leetcode.com/problems/rearrange-characters-to-make-target-string/)
- 🟢 [2341. Maximum Number of Pairs in Array](https://leetcode.com/problems/maximum-number-of-pairs-in-array/)
- 🟢 [2347. Best Poker Hand](https://leetcode.com/problems/best-poker-hand/)
- 🟢 [2404. Most Frequent Even Element](https://leetcode.com/problems/most-frequent-even-element/)
- 🟢 [2423. Remove Letter To Equalize Frequency](https://leetcode.com/problems/remove-letter-to-equalize-frequency/)
- 🟡 [2453. Destroy Sequential Targets](https://leetcode.com/problems/destroy-sequential-targets/)
- 🟡 [2531. Make Number of Distinct Characters Equal](https://leetcode.com/problems/make-number-of-distinct-characters-equal/)
- 🟢 [2586. Count the Number of Vowel Strings in Range](https://leetcode.com/problems/count-the-number-of-vowel-strings-in-range/)
- 🟢 [2833. Furthest Point From Origin](https://leetcode.com/problems/furthest-point-from-origin/)
- 🟢 [2960. Count Tested Devices After Test Operations](https://leetcode.com/problems/count-tested-devices-after-test-operations/)
- 🟢 [3005. Count Elements With Maximum Frequency](https://leetcode.com/problems/count-elements-with-maximum-frequency/)
- 🟡 [3039. Apply Operations to Make String Empty](https://leetcode.com/problems/apply-operations-to-make-string-empty/)
- 🟢 [3046. Split the Array](https://leetcode.com/problems/split-the-array/)
- 🟡 [3071. Minimum Operations to Write the Letter Y on a Grid](https://leetcode.com/problems/minimum-operations-to-write-the-letter-y-on-a-grid/)
- 🟡 [3137. Minimum Number of Operations to Make Word K-Periodic](https://leetcode.com/problems/minimum-number-of-operations-to-make-word-k-periodic/)
- 🟡 [3167. Better Compression of String](https://leetcode.com/problems/better-compression-of-string/) 🔒
- 🟢 [3184. Count Pairs That Form a Complete Day I](https://leetcode.com/problems/count-pairs-that-form-a-complete-day-i/)
- 🟡 [3185. Count Pairs That Form a Complete Day II](https://leetcode.com/problems/count-pairs-that-form-a-complete-day-ii/)
- 🟡 [3223. Minimum Length of String After Operations](https://leetcode.com/problems/minimum-length-of-string-after-operations/)
- 🟢 [3238. Find the Number of Winning Players](https://leetcode.com/problems/find-the-number-of-winning-players/)
- 🟡 [3265. Count Almost Equal Pairs I](https://leetcode.com/problems/count-almost-equal-pairs-i/)
- 🔴 [3267. Count Almost Equal Pairs II](https://leetcode.com/problems/count-almost-equal-pairs-ii/)
- 🟡 [3371. Identify the Largest Outlier in an Array](https://leetcode.com/problems/identify-the-largest-outlier-in-an-array/)
- 🟢 [3438. Find Valid Pair of Adjacent Digits in String](https://leetcode.com/problems/find-valid-pair-of-adjacent-digits-in-string/)
- 🟢 [3442. Maximum Difference Between Even and Odd Frequency I](https://leetcode.com/problems/maximum-difference-between-even-and-odd-frequency-i/)
- 🟢 [3467. Transform Array by Parity](https://leetcode.com/problems/transform-array-by-parity/)
- 🟡 [3527. Find the Most Common Response](https://leetcode.com/problems/find-the-most-common-response/)
- 🟢 [3541. Find Most Frequent Vowel and Consonant](https://leetcode.com/problems/find-most-frequent-vowel-and-consonant/)
- 🟢 [3581. Count Odd Letters from Number](https://leetcode.com/problems/count-odd-letters-from-number/) 🔒
- 🟡 [3583. Count Special Triplets](https://leetcode.com/problems/count-special-triplets/)
- 🟢 [3662. Filter Characters by Frequency](https://leetcode.com/problems/filter-characters-by-frequency/) 🔒
- 🟡 [3664. Two-Letter Card Game](https://leetcode.com/problems/two-letter-card-game/)
- 🟢 [3692. Majority Frequency Characters](https://leetcode.com/problems/majority-frequency-characters/)
- 🟢 [3712. Sum of Elements With Frequency Divisible by K](https://leetcode.com/problems/sum-of-elements-with-frequency-divisible-by-k/)
- 🟡 [3713. Longest Balanced Substring I](https://leetcode.com/problems/longest-balanced-substring-i/)
- 🟡 [3773. Maximum Number of Equal Length Runs](https://leetcode.com/problems/maximum-number-of-equal-length-runs/) 🔒
- 🟡 [3837. Delayed Count of Equal Elements](https://leetcode.com/problems/delayed-count-of-equal-elements/) 🔒
- 🟡 [3843. First Element with Unique Frequency](https://leetcode.com/problems/first-element-with-unique-frequency/)
- 🟢 [3852. Smallest Pair With Different Frequencies](https://leetcode.com/problems/smallest-pair-with-different-frequencies/)
- 🟢 [3866. First Unique Even Element](https://leetcode.com/problems/first-unique-even-element/)
- 🟡 [3889. Mirror Frequency Distance](https://leetcode.com/problems/mirror-frequency-distance/)
- 🟡 [3890. Integers With Multiple Sum of Two Cubes](https://leetcode.com/problems/integers-with-multiple-sum-of-two-cubes/)
- 🟡 [3913. Sort Vowels by Frequency](https://leetcode.com/problems/sort-vowels-by-frequency/)
- 🟡 [3926. Count Valid Word Occurrences](https://leetcode.com/problems/count-valid-word-occurrences/)
- 🔴 [3943. Number of Pairs After Increment](https://leetcode.com/problems/number-of-pairs-after-increment/)
- 🟡 [3960. Frequency Balance Subarray](https://leetcode.com/problems/frequency-balance-subarray/)
- 🟢 [3978. Unique Middle Element](https://leetcode.com/problems/unique-middle-element/)
- 🟢 [4006. Count Valid Prefixes](https://leetcode.com/problems/count-valid-prefixes/)
- 🔴 [4007. Widest Possible Fence](https://leetcode.com/problems/widest-possible-fence/)
- 🟢 [4038. Count Integers Appearing in a Single Block](https://leetcode.com/problems/count-integers-appearing-in-a-single-block/)
- 🟡 [4066. Maximum Equal Adjacent Pairs After at Most One Replacement](https://leetcode.com/problems/maximum-equal-adjacent-pairs-after-at-most-one-replacement/)
- 🟡 [4107. Count Valid Suffix Sorts I](https://leetcode.com/problems/count-valid-suffix-sorts-i/)

</details>

<details><summary><b>Grouping by Key</b> (12)</summary>

- 🟡 [49. Group Anagrams](https://leetcode.com/problems/group-anagrams/)
- 🟡 [249. Group Shifted Strings](https://leetcode.com/problems/group-shifted-strings/) 🔒
- 🟢 [760. Find Anagram Mappings](https://leetcode.com/problems/find-anagram-mappings/) 🔒
- 🟡 [893. Groups of Special-Equivalent Strings](https://leetcode.com/problems/groups-of-special-equivalent-strings/)
- 🟡 [1347. Minimum Number of Steps to Make Two Strings Anagram](https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram/)
- 🟡 [2186. Minimum Number of Steps to Make Two Strings Anagram II](https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram-ii/)
- 🟢 [2273. Find Resultant Array After Removing Anagrams](https://leetcode.com/problems/find-resultant-array-after-removing-anagrams/)
- 🟡 [3138. Minimum Length of Anagram Concatenation](https://leetcode.com/problems/minimum-length-of-anagram-concatenation/)
- 🟡 [3447. Assign Elements to Groups with Constraints](https://leetcode.com/problems/assign-elements-to-groups-with-constraints/)
- 🟡 [3659. Partition Array Into K-Distinct Groups](https://leetcode.com/problems/partition-array-into-k-distinct-groups/)
- 🟡 [3839. Number of Prefix Connected Groups](https://leetcode.com/problems/number-of-prefix-connected-groups/)
- 🟡 [3860. Unique Email Groups](https://leetcode.com/problems/unique-email-groups/) 🔒

</details>

<details><summary><b>Seen Set</b> (3)</summary>

- 🟡 [36. Valid Sudoku](https://leetcode.com/problems/valid-sudoku/)
- 🟡 [128. Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence/)
- 🟢 [217. Contains Duplicate](https://leetcode.com/problems/contains-duplicate/)

</details>

<details><summary><b>Complement Lookup</b> (1)</summary>

- 🟢 [1. Two Sum](https://leetcode.com/problems/two-sum/)

</details>

<details><summary><b>Boyer-Moore Voting</b> (1)</summary>

- 🟢 [169. Majority Element](https://leetcode.com/problems/majority-element/)

</details>

## Intervals & Sweep Line

*Merge / insert / overlap of ranges, meeting rooms, events over time.* — 43 problems

<details><summary><b>Overlap & Scheduling</b> (24)</summary>

- 🟡 [436. Find Right Interval](https://leetcode.com/problems/find-right-interval/)
- 🟡 [497. Random Point in Non-overlapping Rectangles](https://leetcode.com/problems/random-point-in-non-overlapping-rectangles/)
- 🔴 [689. Maximum Sum of 3 Non-Overlapping Subarrays](https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/)
- 🟡 [835. Image Overlap](https://leetcode.com/problems/image-overlap/)
- 🟢 [836. Rectangle Overlap](https://leetcode.com/problems/rectangle-overlap/)
- 🟡 [915. Partition Array into Disjoint Intervals](https://leetcode.com/problems/partition-array-into-disjoint-intervals/)
- 🟡 [1031. Maximum Sum of Two Non-Overlapping Subarrays](https://leetcode.com/problems/maximum-sum-of-two-non-overlapping-subarrays/)
- 🟡 [1272. Remove Interval](https://leetcode.com/problems/remove-interval/) 🔒
- 🟡 [1288. Remove Covered Intervals](https://leetcode.com/problems/remove-covered-intervals/)
- 🟡 [1401. Circle and Rectangle Overlapping](https://leetcode.com/problems/circle-and-rectangle-overlapping/)
- 🟡 [1477. Find Two Non-overlapping Sub-arrays Each With Target Sum](https://leetcode.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/)
- 🔴 [1520. Maximum Number of Non-Overlapping Substrings](https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/)
- 🟢 [1523. Count Odd Numbers in an Interval Range](https://leetcode.com/problems/count-odd-numbers-in-an-interval-range/)
- 🟡 [1546. Maximum Number of Non-Overlapping Subarrays With Sum Equals Target](https://leetcode.com/problems/maximum-number-of-non-overlapping-subarrays-with-sum-equals-target/)
- 🟡 [1621. Number of Sets of K Non-Overlapping Line Segments](https://leetcode.com/problems/number-of-sets-of-k-non-overlapping-line-segments/)
- 🟡 [2121. Intervals Between Identical Elements](https://leetcode.com/problems/intervals-between-identical-elements/)
- 🔴 [2472. Maximum Number of Non-overlapping Palindrome Substrings](https://leetcode.com/problems/maximum-number-of-non-overlapping-palindrome-substrings/)
- 🟡 [2580. Count Ways to Group Overlapping Ranges](https://leetcode.com/problems/count-ways-to-group-overlapping-ranges/)
- 🔴 [3414. Maximum Score of Non-overlapping Intervals](https://leetcode.com/problems/maximum-score-of-non-overlapping-intervals/)
- 🟡 [3893. Maximum Team Size with Overlapping Intervals](https://leetcode.com/problems/maximum-team-size-with-overlapping-intervals/) 🔒
- 🟡 [3975. Filter Occupied Intervals](https://leetcode.com/problems/filter-occupied-intervals/)
- 🟢 [4056. Number of Intersecting Interval Pairs I](https://leetcode.com/problems/number-of-intersecting-interval-pairs-i/)
- 🟡 [4057. Number of Intersecting Interval Pairs II](https://leetcode.com/problems/number-of-intersecting-interval-pairs-ii/)
- 🔴 [4086. Minimum Interval Selection to Cover Target Intervals](https://leetcode.com/problems/minimum-interval-selection-to-cover-target-intervals/)

</details>

<details><summary><b>Sweep Line</b> (6)</summary>

- 🟡 [223. Rectangle Area](https://leetcode.com/problems/rectangle-area/)
- 🔴 [391. Perfect Rectangle](https://leetcode.com/problems/perfect-rectangle/)
- 🔴 [759. Employee Free Time](https://leetcode.com/problems/employee-free-time/) 🔒
- 🟡 [807. Max Increase to Keep City Skyline](https://leetcode.com/problems/max-increase-to-keep-city-skyline/)
- 🟡 [986. Interval List Intersections](https://leetcode.com/problems/interval-list-intersections/)
- 🟡 [4016. Maximum Area of Two Non-Overlapping Square Submatrices](https://leetcode.com/problems/maximum-area-of-two-non-overlapping-square-submatrices/)

</details>

<details><summary><b>Intervals + Heap</b> (4)</summary>

- 🔴 [1851. Minimum Interval to Include Each Query](https://leetcode.com/problems/minimum-interval-to-include-each-query/)
- 🟡 [2054. Two Best Non-Overlapping Events](https://leetcode.com/problems/two-best-non-overlapping-events/)
- 🔴 [2402. Meeting Rooms III](https://leetcode.com/problems/meeting-rooms-iii/)
- 🟡 [2406. Divide Intervals Into Minimum Number of Groups](https://leetcode.com/problems/divide-intervals-into-minimum-number-of-groups/)

</details>

<details><summary><b>Merge / Insert</b> (3)</summary>

- 🟡 [56. Merge Intervals](https://leetcode.com/problems/merge-intervals/)
- 🟡 [57. Insert Interval](https://leetcode.com/problems/insert-interval/)
- 🟡 [3323. Minimize Connected Groups by Inserting Interval](https://leetcode.com/problems/minimize-connected-groups-by-inserting-interval/) 🔒

</details>

<details><summary><b>Interval Scheduling (Greedy)</b> (2)</summary>

- 🟡 [435. Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/)
- 🟡 [452. Minimum Number of Arrows to Burst Balloons](https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/)

</details>

<details><summary><b>Sweep Line + Heap</b> (1)</summary>

- 🔴 [218. The Skyline Problem](https://leetcode.com/problems/the-skyline-problem/)

</details>

<details><summary><b>Overlap Check</b> (1)</summary>

- 🟢 [252. Meeting Rooms](https://leetcode.com/problems/meeting-rooms/) 🔒

</details>

<details><summary><b>Rooms Needed (Heap / Sweep)</b> (1)</summary>

- 🟡 [253. Meeting Rooms II](https://leetcode.com/problems/meeting-rooms-ii/) 🔒

</details>

<details><summary><b>Sweep Line / Difference Array</b> (1)</summary>

- 🟡 [1094. Car Pooling](https://leetcode.com/problems/car-pooling/)

</details>

## Binary Search

*Sorted data, or 'smallest X that works' (search on the answer).* — 181 problems

<details><summary><b>Classic Binary Search</b> (92)</summary>

- 🟡 [34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)
- 🟢 [35. Search Insert Position](https://leetcode.com/problems/search-insert-position/)
- 🟢 [69. Sqrt(x)](https://leetcode.com/problems/sqrtx/)
- 🟡 [162. Find Peak Element](https://leetcode.com/problems/find-peak-element/)
- 🟡 [259. 3Sum Smaller](https://leetcode.com/problems/3sum-smaller/) 🔒
- 🟡 [275. H-Index II](https://leetcode.com/problems/h-index-ii/)
- 🟢 [278. First Bad Version](https://leetcode.com/problems/first-bad-version/)
- 🟡 [362. Design Hit Counter](https://leetcode.com/problems/design-hit-counter/) 🔒
- 🟢 [367. Valid Perfect Square](https://leetcode.com/problems/valid-perfect-square/)
- 🟢 [374. Guess Number Higher or Lower](https://leetcode.com/problems/guess-number-higher-or-lower/)
- 🟡 [400. Nth Digit](https://leetcode.com/problems/nth-digit/)
- 🟢 [441. Arranging Coins](https://leetcode.com/problems/arranging-coins/)
- 🟡 [475. Heaters](https://leetcode.com/problems/heaters/)
- 🟡 [528. Random Pick with Weight](https://leetcode.com/problems/random-pick-with-weight/)
- 🟡 [532. K-diff Pairs in an Array](https://leetcode.com/problems/k-diff-pairs-in-an-array/)
- 🟡 [540. Single Element in a Sorted Array](https://leetcode.com/problems/single-element-in-a-sorted-array/)
- 🟡 [611. Valid Triangle Number](https://leetcode.com/problems/valid-triangle-number/)
- 🟡 [633. Sum of Square Numbers](https://leetcode.com/problems/sum-of-square-numbers/)
- 🟡 [658. Find K Closest Elements](https://leetcode.com/problems/find-k-closest-elements/)
- 🟡 [702. Search in a Sorted Array of Unknown Size](https://leetcode.com/problems/search-in-a-sorted-array-of-unknown-size/) 🔒
- 🟢 [704. Binary Search](https://leetcode.com/problems/binary-search/)
- 🔴 [710. Random Pick with Blacklist](https://leetcode.com/problems/random-pick-with-blacklist/)
- 🟡 [754. Reach a Number](https://leetcode.com/problems/reach-a-number/)
- 🔴 [793. Preimage Size of Factorial Zeroes Function](https://leetcode.com/problems/preimage-size-of-factorial-zeroes-function/)
- 🟡 [825. Friends Of Appropriate Ages](https://leetcode.com/problems/friends-of-appropriate-ages/)
- 🟡 [826. Most Profit Assigning Work](https://leetcode.com/problems/most-profit-assigning-work/)
- 🟡 [852. Peak Index in a Mountain Array](https://leetcode.com/problems/peak-index-in-a-mountain-array/)
- 🔴 [878. Nth Magical Number](https://leetcode.com/problems/nth-magical-number/)
- 🟡 [911. Online Election](https://leetcode.com/problems/online-election/)
- 🟡 [981. Time Based Key-Value Store](https://leetcode.com/problems/time-based-key-value-store/)
- 🟡 [1055. Shortest Way to Form String](https://leetcode.com/problems/shortest-way-to-form-string/) 🔒
- 🟡 [1060. Missing Element in Sorted Array](https://leetcode.com/problems/missing-element-in-sorted-array/) 🔒
- 🟢 [1064. Fixed Point](https://leetcode.com/problems/fixed-point/) 🔒
- 🔴 [1095. Find in Mountain Array](https://leetcode.com/problems/find-in-mountain-array/)
- 🟢 [1099. Two Sum Less Than K](https://leetcode.com/problems/two-sum-less-than-k/) 🔒
- 🟢 [1150. Check If a Number Is Majority Element in a Sorted Array](https://leetcode.com/problems/check-if-a-number-is-majority-element-in-a-sorted-array/) 🔒
- 🟡 [1201. Ugly Number III](https://leetcode.com/problems/ugly-number-iii/)
- 🔴 [1231. Divide Chocolate](https://leetcode.com/problems/divide-chocolate/) 🔒
- 🟡 [1237. Find Positive Integer Solution for a Given Equation](https://leetcode.com/problems/find-positive-integer-solution-for-a-given-equation/)
- 🟡 [1300. Sum of Mutated Array Closest to Target](https://leetcode.com/problems/sum-of-mutated-array-closest-to-target/)
- 🟡 [1348. Tweet Counts Per Frequency](https://leetcode.com/problems/tweet-counts-per-frequency/)
- 🟢 [1385. Find the Distance Value Between Two Arrays](https://leetcode.com/problems/find-the-distance-value-between-two-arrays/)
- 🟡 [1498. Number of Subsequences That Satisfy the Given Sum Condition](https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/)
- 🟡 [1508. Range Sum of Sorted Subarray Sums](https://leetcode.com/problems/range-sum-of-sorted-subarray-sums/)
- 🟡 [1533. Find the Index of the Large Integer](https://leetcode.com/problems/find-the-index-of-the-large-integer/) 🔒
- 🟡 [1552. Magnetic Force Between Two Balls](https://leetcode.com/problems/magnetic-force-between-two-balls/)
- 🟡 [1562. Find Latest Group of Size M](https://leetcode.com/problems/find-latest-group-of-size-m/)
- 🟢 [1608. Special Array With X Elements Greater Than or Equal X](https://leetcode.com/problems/special-array-with-x-elements-greater-than-or-equal-x/)
- 🟡 [1712. Ways to Split Array Into Three Subarrays](https://leetcode.com/problems/ways-to-split-array-into-three-subarrays/)
- 🔴 [1739. Building Boxes](https://leetcode.com/problems/building-boxes/)
- 🔴 [1847. Closest Room](https://leetcode.com/problems/closest-room/)
- 🔴 [1862. Sum of Floored Pairs](https://leetcode.com/problems/sum-of-floored-pairs/)
- 🟡 [1885. Count Pairs in Two Arrays](https://leetcode.com/problems/count-pairs-in-two-arrays/) 🔒
- 🟡 [1891. Cutting Ribbons](https://leetcode.com/problems/cutting-ribbons/) 🔒
- 🟡 [1894. Find the Student that Will Replace the Chalk](https://leetcode.com/problems/find-the-student-that-will-replace-the-chalk/)
- 🟡 [2055. Plates Between Candles](https://leetcode.com/problems/plates-between-candles/)
- 🟡 [2070. Most Beautiful Item for Each Query](https://leetcode.com/problems/most-beautiful-item-for-each-query/)
- 🟢 [2089. Find Target Indices After Sorting Array](https://leetcode.com/problems/find-target-indices-after-sorting-array/)
- 🟡 [2137. Pour Water Between Buckets to Make Water Levels Equal](https://leetcode.com/problems/pour-water-between-buckets-to-make-water-levels-equal/) 🔒
- 🔴 [2251. Number of Flowers in Full Bloom](https://leetcode.com/problems/number-of-flowers-in-full-bloom/)
- 🟡 [2300. Successful Pairs of Spells and Potions](https://leetcode.com/problems/successful-pairs-of-spells-and-potions/)
- 🟡 [2332. The Latest Time to Catch a Bus](https://leetcode.com/problems/the-latest-time-to-catch-a-bus/)
- 🔴 [2354. Number of Excellent Pairs](https://leetcode.com/problems/number-of-excellent-pairs/)
- 🟢 [2389. Longest Subsequence With Limited Sum](https://leetcode.com/problems/longest-subsequence-with-limited-sum/)
- 🟡 [2498. Frog Jump II](https://leetcode.com/problems/frog-jump-ii/)
- 🟡 [2563. Count the Number of Fair Pairs](https://leetcode.com/problems/count-the-number-of-fair-pairs/)
- 🟡 [2601. Prime Subtraction Operation](https://leetcode.com/problems/prime-subtraction-operation/)
- 🟢 [2824. Count Pairs Whose Sum is Less than Target](https://leetcode.com/problems/count-pairs-whose-sum-is-less-than-target/)
- 🟡 [2936. Number of Equal Numbers Blocks](https://leetcode.com/problems/number-of-equal-numbers-blocks/) 🔒
- 🟢 [2970. Count the Number of Incremovable Subarrays I](https://leetcode.com/problems/count-the-number-of-incremovable-subarrays-i/)
- 🔴 [2972. Count the Number of Incremovable Subarrays II](https://leetcode.com/problems/count-the-number-of-incremovable-subarrays-ii/)
- 🟡 [3048. Earliest Second to Mark Indices I](https://leetcode.com/problems/earliest-second-to-mark-indices-i/)
- 🔴 [3145. Find Products of Elements of Big Array](https://leetcode.com/problems/find-products-of-elements-of-big-array/)
- 🟡 [3152. Special Array II](https://leetcode.com/problems/special-array-ii/)
- 🔴 [3312. Sorted GCD Pair Queries](https://leetcode.com/problems/sorted-gcd-pair-queries/)
- 🟡 [3350. Adjacent Increasing Subarrays Detection II](https://leetcode.com/problems/adjacent-increasing-subarrays-detection-ii/)
- 🟡 [3356. Zero Array Transformation II](https://leetcode.com/problems/zero-array-transformation-ii/)
- 🟡 [3453. Separate Squares I](https://leetcode.com/problems/separate-squares-i/)
- 🟡 [3488. Closest Equal Element Queries](https://leetcode.com/problems/closest-equal-element-queries/)
- 🟡 [3508. Implement Router](https://leetcode.com/problems/implement-router/)
- 🟢 [3633. Earliest Finish Time for Land and Water Rides I](https://leetcode.com/problems/earliest-finish-time-for-land-and-water-rides-i/)
- 🟡 [3635. Earliest Finish Time for Land and Water Rides II](https://leetcode.com/problems/earliest-finish-time-for-land-and-water-rides-ii/)
- 🔴 [3636. Threshold Majority Queries](https://leetcode.com/problems/threshold-majority-queries/)
- 🟡 [3709. Design Exam Scores Tracker](https://leetcode.com/problems/design-exam-scores-tracker/)
- 🔴 [3748. Count Stable Subarrays](https://leetcode.com/problems/count-stable-subarrays/)
- 🟡 [3771. Total Score of Dungeon Runs](https://leetcode.com/problems/total-score-of-dungeon-runs/)
- 🟡 [3825. Longest Strictly Increasing Subsequence With Non-Zero Bitwise AND](https://leetcode.com/problems/longest-strictly-increasing-subsequence-with-non-zero-bitwise-and/)
- 🟡 [3932. Count K-th Roots in a Range](https://leetcode.com/problems/count-k-th-roots-in-a-range/)
- 🟡 [4012. Count of Unfinished Tasks After Each Shift](https://leetcode.com/problems/count-of-unfinished-tasks-after-each-shift/)
- 🟡 [4022. K-th Digit in Infinite String](https://leetcode.com/problems/k-th-digit-in-infinite-string/)
- 🟡 [4031. Find All Numbers Disappeared in an Array II](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array-ii/)
- 🔴 [4064. Longest Subarray Divisible by K with At Most One Negation II](https://leetcode.com/problems/longest-subarray-divisible-by-k-with-at-most-one-negation-ii/)

</details>

<details><summary><b>Binary Search on the Answer</b> (74)</summary>

- 🔴 [410. Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/)
- 🔴 [483. Smallest Good Base](https://leetcode.com/problems/smallest-good-base/)
- 🔴 [644. Maximum Average Subarray II](https://leetcode.com/problems/maximum-average-subarray-ii/) 🔒
- 🔴 [668. Kth Smallest Number in Multiplication Table](https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/)
- 🔴 [719. Find K-th Smallest Pair Distance](https://leetcode.com/problems/find-k-th-smallest-pair-distance/)
- 🟢 [744. Find Smallest Letter Greater Than Target](https://leetcode.com/problems/find-smallest-letter-greater-than-target/)
- 🔴 [774. Minimize Max Distance to Gas Station](https://leetcode.com/problems/minimize-max-distance-to-gas-station/) 🔒
- 🟡 [875. Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/)
- 🟡 [1011. Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/)
- 🟡 [1170. Compare Strings by Frequency of the Smallest Character](https://leetcode.com/problems/compare-strings-by-frequency-of-the-smallest-character/)
- 🟡 [1283. Find the Smallest Divisor Given a Threshold](https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/)
- 🟡 [1482. Minimum Number of Days to Make m Bouquets](https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/)
- 🟢 [1539. Kth Missing Positive Number](https://leetcode.com/problems/kth-missing-positive-number/)
- 🟡 [1618. Maximum Font to Fit a Sentence in a Screen](https://leetcode.com/problems/maximum-font-to-fit-a-sentence-in-a-screen/) 🔒
- 🟡 [1760. Minimum Limit of Balls in a Bag](https://leetcode.com/problems/minimum-limit-of-balls-in-a-bag/)
- 🟡 [1802. Maximum Value at a Given Index in a Bounded Array](https://leetcode.com/problems/maximum-value-at-a-given-index-in-a-bounded-array/)
- 🟡 [1818. Minimum Absolute Sum Difference](https://leetcode.com/problems/minimum-absolute-sum-difference/)
- 🟡 [1855. Maximum Distance Between a Pair of Values](https://leetcode.com/problems/maximum-distance-between-a-pair-of-values/)
- 🟡 [1870. Minimum Speed to Arrive on Time](https://leetcode.com/problems/minimum-speed-to-arrive-on-time/)
- 🔴 [1889. Minimum Space Wasted From Packaging](https://leetcode.com/problems/minimum-space-wasted-from-packaging/)
- 🟡 [1898. Maximum Number of Removable Characters](https://leetcode.com/problems/maximum-number-of-removable-characters/)
- 🟡 [1954. Minimum Garden Perimeter to Collect Enough Apples](https://leetcode.com/problems/minimum-garden-perimeter-to-collect-enough-apples/)
- 🔴 [2040. Kth Smallest Product of Two Sorted Arrays](https://leetcode.com/problems/kth-smallest-product-of-two-sorted-arrays/)
- 🟡 [2064. Minimized Maximum of Products Distributed to Any Store](https://leetcode.com/problems/minimized-maximum-of-products-distributed-to-any-store/)
- 🔴 [2141. Maximum Running Time of N Computers](https://leetcode.com/problems/maximum-running-time-of-n-computers/)
- 🟡 [2187. Minimum Time to Complete Trips](https://leetcode.com/problems/minimum-time-to-complete-trips/)
- 🟡 [2226. Maximum Candies Allocated to K Children](https://leetcode.com/problems/maximum-candies-allocated-to-k-children/)
- 🔴 [2234. Maximum Total Beauty of the Gardens](https://leetcode.com/problems/maximum-total-beauty-of-the-gardens/)
- 🟡 [2358. Maximum Number of Groups Entering a Competition](https://leetcode.com/problems/maximum-number-of-groups-entering-a-competition/)
- 🔴 [2448. Minimum Cost to Make Array Equal](https://leetcode.com/problems/minimum-cost-to-make-array-equal/)
- 🟡 [2513. Minimize the Maximum of Two Arrays](https://leetcode.com/problems/minimize-the-maximum-of-two-arrays/)
- 🟡 [2517. Maximum Tastiness of Candy Basket](https://leetcode.com/problems/maximum-tastiness-of-candy-basket/)
- 🟢 [2529. Maximum Count of Positive Integer and Negative Integer](https://leetcode.com/problems/maximum-count-of-positive-integer-and-negative-integer/)
- 🟡 [2554. Maximum Number of Integers to Choose From a Range I](https://leetcode.com/problems/maximum-number-of-integers-to-choose-from-a-range-i/)
- 🟡 [2557. Maximum Number of Integers to Choose From a Range II](https://leetcode.com/problems/maximum-number-of-integers-to-choose-from-a-range-ii/) 🔒
- 🔴 [2565. Subsequence With the Minimum Score](https://leetcode.com/problems/subsequence-with-the-minimum-score/)
- 🟡 [2576. Find the Maximum Number of Marked Indices](https://leetcode.com/problems/find-the-maximum-number-of-marked-indices/)
- 🔴 [2589. Minimum Time to Complete All Tasks](https://leetcode.com/problems/minimum-time-to-complete-all-tasks/)
- 🟡 [2594. Minimum Time to Repair Cars](https://leetcode.com/problems/minimum-time-to-repair-cars/)
- 🟡 [2602. Minimum Operations to Make All Array Elements Equal](https://leetcode.com/problems/minimum-operations-to-make-all-array-elements-equal/)
- 🔴 [2604. Minimum Time to Eat All Grains](https://leetcode.com/problems/minimum-time-to-eat-all-grains/) 🔒
- 🔴 [2702. Minimum Operations to Make Numbers Non-positive](https://leetcode.com/problems/minimum-operations-to-make-numbers-non-positive/) 🔒
- 🔴 [2790. Maximum Number of Groups With Increasing Length](https://leetcode.com/problems/maximum-number-of-groups-with-increasing-length/)
- 🟡 [2817. Minimum Absolute Difference Between Elements With Constraint](https://leetcode.com/problems/minimum-absolute-difference-between-elements-with-constraint/)
- 🔴 [2819. Minimum Relative Loss After Buying Chocolates](https://leetcode.com/problems/minimum-relative-loss-after-buying-chocolates/) 🔒
- 🟡 [2838. Maximum Coins Heroes Can Collect](https://leetcode.com/problems/maximum-coins-heroes-can-collect/) 🔒
- 🟡 [2856. Minimum Array Length After Pair Removals](https://leetcode.com/problems/minimum-array-length-after-pair-removals/)
- 🟡 [2861. Maximum Number of Alloys](https://leetcode.com/problems/maximum-number-of-alloys/)
- 🔴 [2941. Maximum GCD-Sum of a Subarray](https://leetcode.com/problems/maximum-gcd-sum-of-a-subarray/) 🔒
- 🟡 [2967. Minimum Cost to Make Array Equalindromic](https://leetcode.com/problems/minimum-cost-to-make-array-equalindromic/)
- 🔴 [3116. Kth Smallest Amount With Single Denomination Combination](https://leetcode.com/problems/kth-smallest-amount-with-single-denomination-combination/)
- 🟡 [3143. Maximum Points Inside the Square](https://leetcode.com/problems/maximum-points-inside-the-square/)
- 🟡 [3155. Maximum Number of Upgradable Servers](https://leetcode.com/problems/maximum-number-of-upgradable-servers/) 🔒
- 🔴 [3231. Minimum Number of Increasing Subsequence to Be Removed](https://leetcode.com/problems/minimum-number-of-increasing-subsequence-to-be-removed/) 🔒
- 🟡 [3281. Maximize Score of Numbers in Ranges](https://leetcode.com/problems/maximize-score-of-numbers-in-ranges/)
- 🟡 [3344. Maximum Sized Array](https://leetcode.com/problems/maximum-sized-array/) 🔒
- 🔴 [3357. Minimize the Maximum Adjacent Element Difference](https://leetcode.com/problems/minimize-the-maximum-adjacent-element-difference/)
- 🔴 [3398. Smallest Substring With Identical Characters I](https://leetcode.com/problems/smallest-substring-with-identical-characters-i/)
- 🔴 [3399. Smallest Substring With Identical Characters II](https://leetcode.com/problems/smallest-substring-with-identical-characters-ii/)
- 🔴 [3449. Maximize the Minimum Game Score](https://leetcode.com/problems/maximize-the-minimum-game-score/)
- 🔴 [3464. Maximize the Distance Between Points on a Square](https://leetcode.com/problems/maximize-the-distance-between-points-on-a-square/)
- 🟡 [3639. Minimum Time to Activate String](https://leetcode.com/problems/minimum-time-to-activate-string/)
- 🟡 [3722. Lexicographically Smallest String After Reverse](https://leetcode.com/problems/lexicographically-smallest-string-after-reverse/)
- 🟡 [3733. Minimum Time to Complete All Deliveries](https://leetcode.com/problems/minimum-time-to-complete-all-deliveries/)
- 🟡 [3759. Count Elements With at Least K Greater Values](https://leetcode.com/problems/count-elements-with-at-least-k-greater-values/)
- 🟡 [3766. Minimum Operations to Make Binary Palindrome](https://leetcode.com/problems/minimum-operations-to-make-binary-palindrome/)
- 🟡 [3814. Maximum Capacity Within Budget](https://leetcode.com/problems/maximum-capacity-within-budget/)
- 🟡 [3824. Minimum K to Reduce Array Within Limit](https://leetcode.com/problems/minimum-k-to-reduce-array-within-limit/)
- 🟡 [3896. Minimum Operations to Transform Array into Alternating Prime](https://leetcode.com/problems/minimum-operations-to-transform-array-into-alternating-prime/)
- 🔴 [3911. K-th Smallest Remaining Even Integer in Subarray Queries](https://leetcode.com/problems/k-th-smallest-remaining-even-integer-in-subarray-queries/)
- 🔴 [3920. Maximize Fixed Points After Deletions](https://leetcode.com/problems/maximize-fixed-points-after-deletions/)
- 🔴 [3971. Maximum Total Value](https://leetcode.com/problems/maximum-total-value/)
- 🟡 [4008. Minimum Initial Strength to Defeat All Monsters](https://leetcode.com/problems/minimum-initial-strength-to-defeat-all-monsters/)
- 🟡 [4053. Minimum Operations to Make Every Element Palindromic](https://leetcode.com/problems/minimum-operations-to-make-every-element-palindromic/)

</details>

<details><summary><b>Search in Matrix</b> (10)</summary>

- 🟡 [74. Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/)
- 🟡 [240. Search a 2D Matrix II](https://leetcode.com/problems/search-a-2d-matrix-ii/)
- 🔴 [363. Max Sum of Rectangle No Larger Than K](https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/)
- 🟡 [378. Kth Smallest Element in a Sorted Matrix](https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/)
- 🟡 [1198. Find Smallest Common Element in All Rows](https://leetcode.com/problems/find-smallest-common-element-in-all-rows/) 🔒
- 🟡 [1292. Maximum Side Length of a Square with Sum Less than or Equal to Threshold](https://leetcode.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/)
- 🟢 [1351. Count Negative Numbers in a Sorted Matrix](https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/)
- 🟡 [1428. Leftmost Column with at Least a One](https://leetcode.com/problems/leftmost-column-with-at-least-a-one/) 🔒
- 🟡 [1901. Find a Peak Element II](https://leetcode.com/problems/find-a-peak-element-ii/)
- 🟡 [2387. Median of a Row Wise Sorted Matrix](https://leetcode.com/problems/median-of-a-row-wise-sorted-matrix/) 🔒

</details>

<details><summary><b>Rotated Array</b> (4)</summary>

- 🟡 [33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)
- 🟡 [81. Search in Rotated Sorted Array II](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/)
- 🟡 [153. Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/)
- 🔴 [154. Find Minimum in Rotated Sorted Array II](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/)

</details>

<details><summary><b>Partition Search</b> (1)</summary>

- 🔴 [4. Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/)

</details>

## Stack

*Matching brackets, parsing expressions, undo, nested structure.* — 57 problems

<details><summary><b>Stack Simulation</b> (33)</summary>

- 🟡 [71. Simplify Path](https://leetcode.com/problems/simplify-path/)
- 🟡 [484. Find Permutation](https://leetcode.com/problems/find-permutation/) 🔒
- 🔴 [591. Tag Validator](https://leetcode.com/problems/tag-validator/)
- 🟡 [636. Exclusive Time of Functions](https://leetcode.com/problems/exclusive-time-of-functions/)
- 🟢 [682. Baseball Game](https://leetcode.com/problems/baseball-game/)
- 🔴 [726. Number of Atoms](https://leetcode.com/problems/number-of-atoms/)
- 🟡 [880. Decoded String at Index](https://leetcode.com/problems/decoded-string-at-index/)
- 🔴 [936. Stamping The Sequence](https://leetcode.com/problems/stamping-the-sequence/)
- 🟡 [946. Validate Stack Sequences](https://leetcode.com/problems/validate-stack-sequences/)
- 🟡 [1003. Check If Word Is Valid After Substitutions](https://leetcode.com/problems/check-if-word-is-valid-after-substitutions/)
- 🟡 [1006. Clumsy Factorial](https://leetcode.com/problems/clumsy-factorial/)
- 🟢 [1047. Remove All Adjacent Duplicates In String](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/)
- 🟡 [1209. Remove All Adjacent Duplicates in String II](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string-ii/)
- 🟡 [1441. Build an Array With Stack Operations](https://leetcode.com/problems/build-an-array-with-stack-operations/)
- 🟢 [1544. Make The String Great](https://leetcode.com/problems/make-the-string-great/)
- 🟢 [1598. Crawler Log Folder](https://leetcode.com/problems/crawler-log-folder/)
- 🟢 [1700. Number of Students Unable to Eat Lunch](https://leetcode.com/problems/number-of-students-unable-to-eat-lunch/)
- 🟡 [1717. Maximum Score From Removing Substrings](https://leetcode.com/problems/maximum-score-from-removing-substrings/)
- 🟡 [1910. Remove All Occurrences of a Substring](https://leetcode.com/problems/remove-all-occurrences-of-a-substring/)
- 🔴 [2197. Replace Non-Coprime Numbers in Array](https://leetcode.com/problems/replace-non-coprime-numbers-in-array/)
- 🟡 [2211. Count Collisions on a Road](https://leetcode.com/problems/count-collisions-on-a-road/)
- 🟡 [2216. Minimum Deletions to Make Array Beautiful](https://leetcode.com/problems/minimum-deletions-to-make-array-beautiful/)
- 🟡 [2390. Removing Stars From a String](https://leetcode.com/problems/removing-stars-from-a-string/)
- 🟡 [2434. Using a Robot to Print the Lexicographically Smallest String](https://leetcode.com/problems/using-a-robot-to-print-the-lexicographically-smallest-string/)
- 🟢 [2696. Minimum String Length After Removing Substrings](https://leetcode.com/problems/minimum-string-length-after-removing-substrings/)
- 🔴 [2751. Robot Collisions](https://leetcode.com/problems/robot-collisions/)
- 🟢 [3174. Clear Digits](https://leetcode.com/problems/clear-digits/)
- 🟡 [3412. Find Mirror Score of a String](https://leetcode.com/problems/find-mirror-score-of-a-string/)
- 🟡 [3561. Resulting String After Adjacent Removals](https://leetcode.com/problems/resulting-string-after-adjacent-removals/)
- 🟡 [3703. Remove K-Balanced Substrings](https://leetcode.com/problems/remove-k-balanced-substrings/)
- 🟡 [3746. Minimum String Length After Balanced Removals](https://leetcode.com/problems/minimum-string-length-after-balanced-removals/)
- 🟡 [3834. Merge Adjacent Equal Elements](https://leetcode.com/problems/merge-adjacent-equal-elements/)
- 🟡 [4103. Remove Elements by Type and Color](https://leetcode.com/problems/remove-elements-by-type-and-color/)

</details>

<details><summary><b>Bracket Matching</b> (10)</summary>

- 🟢 [20. Valid Parentheses](https://leetcode.com/problems/valid-parentheses/)
- 🟡 [856. Score of Parentheses](https://leetcode.com/problems/score-of-parentheses/)
- 🟡 [921. Minimum Add to Make Parentheses Valid](https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/)
- 🟢 [1021. Remove Outermost Parentheses](https://leetcode.com/problems/remove-outermost-parentheses/)
- 🟡 [1111. Maximum Nesting Depth of Two Valid Parentheses Strings](https://leetcode.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings/)
- 🟡 [1190. Reverse Substrings Between Each Pair of Parentheses](https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/)
- 🟡 [1249. Minimum Remove to Make Valid Parentheses](https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/)
- 🟡 [1541. Minimum Insertions to Balance a Parentheses String](https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/)
- 🟢 [1614. Maximum Nesting Depth of the Parentheses](https://leetcode.com/problems/maximum-nesting-depth-of-the-parentheses/)
- 🟡 [2116. Check if a Parentheses String Can Be Valid](https://leetcode.com/problems/check-if-a-parentheses-string-can-be-valid/)

</details>

<details><summary><b>Expression Evaluation</b> (9)</summary>

- 🟡 [150. Evaluate Reverse Polish Notation](https://leetcode.com/problems/evaluate-reverse-polish-notation/)
- 🔴 [224. Basic Calculator](https://leetcode.com/problems/basic-calculator/)
- 🟡 [227. Basic Calculator II](https://leetcode.com/problems/basic-calculator-ii/)
- 🟡 [439. Ternary Expression Parser](https://leetcode.com/problems/ternary-expression-parser/) 🔒
- 🔴 [736. Parse Lisp Expression](https://leetcode.com/problems/parse-lisp-expression/)
- 🔴 [770. Basic Calculator IV](https://leetcode.com/problems/basic-calculator-iv/)
- 🔴 [772. Basic Calculator III](https://leetcode.com/problems/basic-calculator-iii/) 🔒
- 🔴 [1106. Parsing A Boolean Expression](https://leetcode.com/problems/parsing-a-boolean-expression/)
- 🔴 [3749. Evaluate Valid Expressions](https://leetcode.com/problems/evaluate-valid-expressions/) 🔒

</details>

<details><summary><b>Stack Design</b> (2)</summary>

- 🟡 [155. Min Stack](https://leetcode.com/problems/min-stack/)
- 🟢 [232. Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/)

</details>

<details><summary><b>Nested Decoding</b> (1)</summary>

- 🟡 [394. Decode String](https://leetcode.com/problems/decode-string/)

</details>

<details><summary><b>Collision Simulation</b> (1)</summary>

- 🟡 [735. Asteroid Collision](https://leetcode.com/problems/asteroid-collision/)

</details>

<details><summary><b>Sort + Stack</b> (1)</summary>

- 🟡 [853. Car Fleet](https://leetcode.com/problems/car-fleet/)

</details>

## Monotonic Stack / Queue

*Next greater / smaller element, sliding-window max, histograms.* — 83 problems

<details><summary><b>Monotonic Stack</b> (62)</summary>

- 🔴 [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)
- 🔴 [85. Maximal Rectangle](https://leetcode.com/problems/maximal-rectangle/)
- 🟡 [255. Verify Preorder Sequence in Binary Search Tree](https://leetcode.com/problems/verify-preorder-sequence-in-binary-search-tree/) 🔒
- 🟡 [316. Remove Duplicate Letters](https://leetcode.com/problems/remove-duplicate-letters/)
- 🔴 [321. Create Maximum Number](https://leetcode.com/problems/create-maximum-number/)
- 🟡 [402. Remove K Digits](https://leetcode.com/problems/remove-k-digits/)
- 🟡 [456. 132 Pattern](https://leetcode.com/problems/132-pattern/)
- 🟢 [496. Next Greater Element I](https://leetcode.com/problems/next-greater-element-i/)
- 🟡 [503. Next Greater Element II](https://leetcode.com/problems/next-greater-element-ii/)
- 🟡 [581. Shortest Unsorted Continuous Subarray](https://leetcode.com/problems/shortest-unsorted-continuous-subarray/)
- 🟡 [739. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/)
- 🔴 [768. Max Chunks To Make Sorted II](https://leetcode.com/problems/max-chunks-to-make-sorted-ii/)
- 🟡 [769. Max Chunks To Make Sorted](https://leetcode.com/problems/max-chunks-to-make-sorted/)
- 🟡 [901. Online Stock Span](https://leetcode.com/problems/online-stock-span/)
- 🟡 [907. Sum of Subarray Minimums](https://leetcode.com/problems/sum-of-subarray-minimums/)
- 🟡 [962. Maximum Width Ramp](https://leetcode.com/problems/maximum-width-ramp/)
- 🔴 [975. Odd Even Jump](https://leetcode.com/problems/odd-even-jump/)
- 🟡 [1008. Construct Binary Search Tree from Preorder Traversal](https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/)
- 🟡 [1019. Next Greater Node In Linked List](https://leetcode.com/problems/next-greater-node-in-linked-list/)
- 🔴 [1063. Number of Valid Subarrays](https://leetcode.com/problems/number-of-valid-subarrays/) 🔒
- 🟡 [1081. Smallest Subsequence of Distinct Characters](https://leetcode.com/problems/smallest-subsequence-of-distinct-characters/)
- 🟡 [1124. Longest Well-Performing Interval](https://leetcode.com/problems/longest-well-performing-interval/)
- 🟢 [1475. Final Prices With a Special Discount in a Shop](https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/)
- 🟡 [1504. Count Submatrices With All Ones](https://leetcode.com/problems/count-submatrices-with-all-ones/)
- 🔴 [1526. Minimum Number of Increments on Subarrays to Form a Target Array](https://leetcode.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/)
- 🟡 [1574. Shortest Subarray to be Removed to Make Array Sorted](https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/)
- 🟡 [1673. Find the Most Competitive Subsequence](https://leetcode.com/problems/find-the-most-competitive-subsequence/)
- 🟡 [1762. Buildings With an Ocean View](https://leetcode.com/problems/buildings-with-an-ocean-view/) 🔒
- 🔴 [1776. Car Fleet II](https://leetcode.com/problems/car-fleet-ii/)
- 🔴 [1944. Number of Visible People in a Queue](https://leetcode.com/problems/number-of-visible-people-in-a-queue/)
- 🟡 [1966. Binary Searchable Numbers in an Unsorted Array](https://leetcode.com/problems/binary-searchable-numbers-in-an-unsorted-array/) 🔒
- 🟡 [1996. The Number of Weak Characters in the Game](https://leetcode.com/problems/the-number-of-weak-characters-in-the-game/)
- 🔴 [2030. Smallest K-Length Subsequence With Occurrences of a Letter](https://leetcode.com/problems/smallest-k-length-subsequence-with-occurrences-of-a-letter/)
- 🟡 [2104. Sum of Subarray Ranges](https://leetcode.com/problems/sum-of-subarray-ranges/)
- 🔴 [2281. Sum of Total Strength of Wizards](https://leetcode.com/problems/sum-of-total-strength-of-wizards/)
- 🟡 [2282. Number of People That Can Be Seen in a Grid](https://leetcode.com/problems/number-of-people-that-can-be-seen-in-a-grid/) 🔒
- 🟡 [2289. Steps to Make Array Non-decreasing](https://leetcode.com/problems/steps-to-make-array-non-decreasing/)
- 🟡 [2345. Finding the Number of Visible Mountains](https://leetcode.com/problems/finding-the-number-of-visible-mountains/) 🔒
- 🔴 [2355. Maximum Number of Books You Can Take](https://leetcode.com/problems/maximum-number-of-books-you-can-take/) 🔒
- 🔴 [2454. Next Greater Element IV](https://leetcode.com/problems/next-greater-element-iv/)
- 🟡 [2487. Remove Nodes From Linked List](https://leetcode.com/problems/remove-nodes-from-linked-list/)
- 🔴 [2617. Minimum Number of Visited Cells in a Grid](https://leetcode.com/problems/minimum-number-of-visited-cells-in-a-grid/)
- 🔴 [2818. Apply Operations to Maximize Score](https://leetcode.com/problems/apply-operations-to-maximize-score/)
- 🟡 [2832. Maximal Range That Each Element Is Maximum in It](https://leetcode.com/problems/maximal-range-that-each-element-is-maximum-in-it/) 🔒
- 🟡 [2863. Maximum Length of Semi-Decreasing Subarrays](https://leetcode.com/problems/maximum-length-of-semi-decreasing-subarrays/) 🔒
- 🟡 [2865. Beautiful Towers I](https://leetcode.com/problems/beautiful-towers-i/)
- 🟡 [2866. Beautiful Towers II](https://leetcode.com/problems/beautiful-towers-ii/)
- 🔴 [3113. Find the Number of Subarrays Where Boundary Elements Are Maximum](https://leetcode.com/problems/find-the-number-of-subarrays-where-boundary-elements-are-maximum/)
- 🟡 [3205. Maximum Array Hopping Score I](https://leetcode.com/problems/maximum-array-hopping-score-i/) 🔒
- 🟡 [3221. Maximum Array Hopping Score II](https://leetcode.com/problems/maximum-array-hopping-score-ii/) 🔒
- 🔴 [3229. Minimum Operations to Make Array Equal to Target](https://leetcode.com/problems/minimum-operations-to-make-array-equal-to-target/)
- 🔴 [3359. Find Sorted Submatrices With Maximum Element at Most K](https://leetcode.com/problems/find-sorted-submatrices-with-maximum-element-at-most-k/) 🔒
- 🔴 [3430. Maximum and Minimum Sums of at Most Size K Subarrays](https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-size-k-subarrays/)
- 🟡 [3523. Make Array Non-decreasing](https://leetcode.com/problems/make-array-non-decreasing/)
- 🟡 [3542. Minimum Operations to Convert All Elements to Zero](https://leetcode.com/problems/minimum-operations-to-convert-all-elements-to-zero/)
- 🟡 [3555. Smallest Subarray to Sort in Every Sliding Window](https://leetcode.com/problems/smallest-subarray-to-sort-in-every-sliding-window/) 🔒
- 🟡 [3638. Maximum Balanced Shipments](https://leetcode.com/problems/maximum-balanced-shipments/)
- 🟡 [3676. Count Bowl Subarrays](https://leetcode.com/problems/count-bowl-subarrays/)
- 🔴 [3816. Lexicographically Smallest String After Deleting Duplicate Characters](https://leetcode.com/problems/lexicographically-smallest-string-after-deleting-duplicate-characters/)
- 🔴 [3878. Count Good Subarrays](https://leetcode.com/problems/count-good-subarrays/)
- 🟡 [4045. Count Robot Groups](https://leetcode.com/problems/count-robot-groups/)
- 🟡 [4054. Count Shadow Pairs I](https://leetcode.com/problems/count-shadow-pairs-i/)

</details>

<details><summary><b>Monotonic Queue</b> (21)</summary>

- 🔴 [239. Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)
- 🔴 [862. Shortest Subarray with Sum at Least K](https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/)
- 🟡 [918. Maximum Sum Circular Subarray](https://leetcode.com/problems/maximum-sum-circular-subarray/)
- 🔴 [1425. Constrained Subsequence Sum](https://leetcode.com/problems/constrained-subsequence-sum/)
- 🟡 [1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit](https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/)
- 🔴 [1499. Max Value of Equation](https://leetcode.com/problems/max-value-of-equation/)
- 🟡 [1696. Jump Game VI](https://leetcode.com/problems/jump-game-vi/)
- 🔴 [2071. Maximum Number of Tasks You Can Assign](https://leetcode.com/problems/maximum-number-of-tasks-you-can-assign/)
- 🔴 [2398. Maximum Number of Robots Within Budget](https://leetcode.com/problems/maximum-number-of-robots-within-budget/)
- 🔴 [2444. Count Subarrays With Fixed Bounds](https://leetcode.com/problems/count-subarrays-with-fixed-bounds/)
- 🟡 [2762. Continuous Subarrays](https://leetcode.com/problems/continuous-subarrays/)
- 🟡 [2944. Minimum Number of Coins for Fruits](https://leetcode.com/problems/minimum-number-of-coins-for-fruits/)
- 🔴 [2945. Find Maximum Non-decreasing Array Length](https://leetcode.com/problems/find-maximum-non-decreasing-array-length/)
- 🔴 [2969. Minimum Number of Coins for Fruits II](https://leetcode.com/problems/minimum-number-of-coins-for-fruits-ii/) 🔒
- 🟡 [3578. Count Partitions With Max-Min Difference at Most K](https://leetcode.com/problems/count-partitions-with-max-min-difference-at-most-k/)
- 🟡 [3589. Count Prime-Gap Balanced Subarrays](https://leetcode.com/problems/count-prime-gap-balanced-subarrays/)
- 🔴 [3826. Minimum Partition Score](https://leetcode.com/problems/minimum-partition-score/)
- 🟡 [3835. Count Subarrays With Cost Less Than or Equal to K](https://leetcode.com/problems/count-subarrays-with-cost-less-than-or-equal-to-k/)
- 🔴 [3929. Minimum Partition Score II](https://leetcode.com/problems/minimum-partition-score-ii/) 🔒
- 🔴 [3956. Maximum Sum of M Non-Overlapping Subarrays I](https://leetcode.com/problems/maximum-sum-of-m-non-overlapping-subarrays-i/)
- 🔴 [3957. Maximum Sum of M Non-Overlapping Subarrays II](https://leetcode.com/problems/maximum-sum-of-m-non-overlapping-subarrays-ii/)

</details>

## Linked List

*Reverse, merge, reorder, remove nodes in place.* — 64 problems

<details><summary><b>List Manipulation</b> (45)</summary>

- 🟡 [2. Add Two Numbers](https://leetcode.com/problems/add-two-numbers/)
- 🟡 [24. Swap Nodes in Pairs](https://leetcode.com/problems/swap-nodes-in-pairs/)
- 🟡 [61. Rotate List](https://leetcode.com/problems/rotate-list/)
- 🟡 [86. Partition List](https://leetcode.com/problems/partition-list/)
- 🟡 [109. Convert Sorted List to Binary Search Tree](https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/)
- 🟡 [114. Flatten Binary Tree to Linked List](https://leetcode.com/problems/flatten-binary-tree-to-linked-list/)
- 🟡 [116. Populating Next Right Pointers in Each Node](https://leetcode.com/problems/populating-next-right-pointers-in-each-node/)
- 🟡 [117. Populating Next Right Pointers in Each Node II](https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/)
- 🟡 [147. Insertion Sort List](https://leetcode.com/problems/insertion-sort-list/)
- 🟡 [148. Sort List](https://leetcode.com/problems/sort-list/)
- 🟡 [328. Odd Even Linked List](https://leetcode.com/problems/odd-even-linked-list/)
- 🟡 [369. Plus One Linked List](https://leetcode.com/problems/plus-one-linked-list/) 🔒
- 🟡 [379. Design Phone Directory](https://leetcode.com/problems/design-phone-directory/) 🔒
- 🟡 [382. Linked List Random Node](https://leetcode.com/problems/linked-list-random-node/)
- 🟡 [426. Convert Binary Search Tree to Sorted Doubly Linked List](https://leetcode.com/problems/convert-binary-search-tree-to-sorted-doubly-linked-list/) 🔒
- 🟡 [430. Flatten a Multilevel Doubly Linked List](https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/)
- 🔴 [432. All O`one Data Structure](https://leetcode.com/problems/all-oone-data-structure/)
- 🟡 [445. Add Two Numbers II](https://leetcode.com/problems/add-two-numbers-ii/)
- 🟡 [622. Design Circular Queue](https://leetcode.com/problems/design-circular-queue/)
- 🟡 [641. Design Circular Deque](https://leetcode.com/problems/design-circular-deque/)
- 🟡 [707. Design Linked List](https://leetcode.com/problems/design-linked-list/)
- 🟡 [708. Insert into a Sorted Circular Linked List](https://leetcode.com/problems/insert-into-a-sorted-circular-linked-list/) 🔒
- 🔴 [716. Max Stack](https://leetcode.com/problems/max-stack/) 🔒
- 🟡 [725. Split Linked List in Parts](https://leetcode.com/problems/split-linked-list-in-parts/)
- 🟡 [817. Linked List Components](https://leetcode.com/problems/linked-list-components/)
- 🔴 [1206. Design Skiplist](https://leetcode.com/problems/design-skiplist/)
- 🟢 [1290. Convert Binary Number in a Linked List to Integer](https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/)
- 🟡 [1367. Linked List in Binary Tree](https://leetcode.com/problems/linked-list-in-binary-tree/)
- 🟡 [1472. Design Browser History](https://leetcode.com/problems/design-browser-history/)
- 🟡 [1634. Add Two Polynomials Represented as Linked Lists](https://leetcode.com/problems/add-two-polynomials-represented-as-linked-lists/) 🔒
- 🟡 [1670. Design Front Middle Back Queue](https://leetcode.com/problems/design-front-middle-back-queue/)
- 🟡 [1721. Swapping Nodes in a Linked List](https://leetcode.com/problems/swapping-nodes-in-a-linked-list/)
- 🟡 [1797. Design Authentication Manager](https://leetcode.com/problems/design-authentication-manager/)
- 🟡 [2046. Sort Linked List Already Sorted Using Absolute Values](https://leetcode.com/problems/sort-linked-list-already-sorted-using-absolute-values/) 🔒
- 🟡 [2058. Find the Minimum and Maximum Number of Nodes Between Critical Points](https://leetcode.com/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/)
- 🟡 [2130. Maximum Twin Sum of a Linked List](https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/)
- 🔴 [2296. Design a Text Editor](https://leetcode.com/problems/design-a-text-editor/)
- 🟡 [2326. Spiral Matrix IV](https://leetcode.com/problems/spiral-matrix-iv/)
- 🟡 [2674. Split a Circular Linked List](https://leetcode.com/problems/split-a-circular-linked-list/) 🔒
- 🟡 [2807. Insert Greatest Common Divisors in Linked List](https://leetcode.com/problems/insert-greatest-common-divisors-in-linked-list/)
- 🟡 [2816. Double a Number Represented as a Linked List](https://leetcode.com/problems/double-a-number-represented-as-a-linked-list/)
- 🟢 [3062. Winner of the Linked List Game](https://leetcode.com/problems/winner-of-the-linked-list-game/) 🔒
- 🟢 [3063. Linked List Frequency](https://leetcode.com/problems/linked-list-frequency/) 🔒
- 🟢 [3263. Convert Doubly Linked List to Array I](https://leetcode.com/problems/convert-doubly-linked-list-to-array-i/) 🔒
- 🟡 [3294. Convert Doubly Linked List to Array II](https://leetcode.com/problems/convert-doubly-linked-list-to-array-ii/) 🔒

</details>

<details><summary><b>Remove Nodes</b> (8)</summary>

- 🟡 [82. Remove Duplicates from Sorted List II](https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/)
- 🟢 [83. Remove Duplicates from Sorted List](https://leetcode.com/problems/remove-duplicates-from-sorted-list/)
- 🟢 [203. Remove Linked List Elements](https://leetcode.com/problems/remove-linked-list-elements/)
- 🟡 [237. Delete Node in a Linked List](https://leetcode.com/problems/delete-node-in-a-linked-list/)
- 🟡 [1171. Remove Zero Sum Consecutive Nodes from Linked List](https://leetcode.com/problems/remove-zero-sum-consecutive-nodes-from-linked-list/)
- 🟢 [1474. Delete N Nodes After M Nodes of a Linked List](https://leetcode.com/problems/delete-n-nodes-after-m-nodes-of-a-linked-list/) 🔒
- 🟡 [1836. Remove Duplicates From an Unsorted Linked List](https://leetcode.com/problems/remove-duplicates-from-an-unsorted-linked-list/) 🔒
- 🟡 [3217. Delete Nodes From Linked List Present in Array](https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array/)

</details>

<details><summary><b>In-place Reversal</b> (5)</summary>

- 🔴 [25. Reverse Nodes in k-Group](https://leetcode.com/problems/reverse-nodes-in-k-group/)
- 🟡 [92. Reverse Linked List II](https://leetcode.com/problems/reverse-linked-list-ii/)
- 🟢 [206. Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/)
- 🟡 [1265. Print Immutable Linked List in Reverse](https://leetcode.com/problems/print-immutable-linked-list-in-reverse/) 🔒
- 🟡 [2074. Reverse Nodes in Even Length Groups](https://leetcode.com/problems/reverse-nodes-in-even-length-groups/)

</details>

<details><summary><b>Merge Lists</b> (3)</summary>

- 🟢 [21. Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/)
- 🟡 [1669. Merge In Between Linked Lists](https://leetcode.com/problems/merge-in-between-linked-lists/)
- 🟡 [2181. Merge Nodes in Between Zeros](https://leetcode.com/problems/merge-nodes-in-between-zeros/)

</details>

<details><summary><b>Two Pointers on a List</b> (1)</summary>

- 🟡 [19. Remove Nth Node From End of List](https://leetcode.com/problems/remove-nth-node-from-end-of-list/)

</details>

<details><summary><b>Clone with Hash Map</b> (1)</summary>

- 🟡 [138. Copy List with Random Pointer](https://leetcode.com/problems/copy-list-with-random-pointer/)

</details>

<details><summary><b>Find Middle + Reverse + Merge</b> (1)</summary>

- 🟡 [143. Reorder List](https://leetcode.com/problems/reorder-list/)

</details>

## Tree Traversal (DFS / BFS)

*Binary trees and BSTs: recursion, level order, paths, LCA.* — 210 problems

<details><summary><b>Tree DFS</b> (117)</summary>

- 🟢 [94. Binary Tree Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/)
- 🟢 [100. Same Tree](https://leetcode.com/problems/same-tree/)
- 🟢 [101. Symmetric Tree](https://leetcode.com/problems/symmetric-tree/)
- 🟢 [104. Maximum Depth of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/)
- 🟢 [110. Balanced Binary Tree](https://leetcode.com/problems/balanced-binary-tree/)
- 🟢 [111. Minimum Depth of Binary Tree](https://leetcode.com/problems/minimum-depth-of-binary-tree/)
- 🟡 [129. Sum Root to Leaf Numbers](https://leetcode.com/problems/sum-root-to-leaf-numbers/)
- 🟢 [144. Binary Tree Preorder Traversal](https://leetcode.com/problems/binary-tree-preorder-traversal/)
- 🟢 [145. Binary Tree Postorder Traversal](https://leetcode.com/problems/binary-tree-postorder-traversal/)
- 🟡 [156. Binary Tree Upside Down](https://leetcode.com/problems/binary-tree-upside-down/) 🔒
- 🟡 [222. Count Complete Tree Nodes](https://leetcode.com/problems/count-complete-tree-nodes/)
- 🟢 [226. Invert Binary Tree](https://leetcode.com/problems/invert-binary-tree/)
- 🟡 [250. Count Univalue Subtrees](https://leetcode.com/problems/count-univalue-subtrees/) 🔒
- 🟡 [298. Binary Tree Longest Consecutive Sequence](https://leetcode.com/problems/binary-tree-longest-consecutive-sequence/) 🔒
- 🟡 [314. Binary Tree Vertical Order Traversal](https://leetcode.com/problems/binary-tree-vertical-order-traversal/) 🔒
- 🟡 [331. Verify Preorder Serialization of a Binary Tree](https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/)
- 🟡 [341. Flatten Nested List Iterator](https://leetcode.com/problems/flatten-nested-list-iterator/)
- 🟡 [366. Find Leaves of Binary Tree](https://leetcode.com/problems/find-leaves-of-binary-tree/) 🔒
- 🟢 [404. Sum of Left Leaves](https://leetcode.com/problems/sum-of-left-leaves/)
- 🔴 [431. Encode N-ary Tree to Binary Tree](https://leetcode.com/problems/encode-n-ary-tree-to-binary-tree/) 🔒
- 🟡 [508. Most Frequent Subtree Sum](https://leetcode.com/problems/most-frequent-subtree-sum/)
- 🟡 [513. Find Bottom Left Tree Value](https://leetcode.com/problems/find-bottom-left-tree-value/)
- 🟡 [515. Find Largest Value in Each Tree Row](https://leetcode.com/problems/find-largest-value-in-each-tree-row/)
- 🟢 [543. Diameter of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/)
- 🟡 [545. Boundary of Binary Tree](https://leetcode.com/problems/boundary-of-binary-tree/) 🔒
- 🟡 [549. Binary Tree Longest Consecutive Sequence II](https://leetcode.com/problems/binary-tree-longest-consecutive-sequence-ii/) 🔒
- 🟡 [558. Logical OR of Two Binary Grids Represented as Quad-Trees](https://leetcode.com/problems/logical-or-of-two-binary-grids-represented-as-quad-trees/)
- 🟢 [559. Maximum Depth of N-ary Tree](https://leetcode.com/problems/maximum-depth-of-n-ary-tree/)
- 🟢 [563. Binary Tree Tilt](https://leetcode.com/problems/binary-tree-tilt/)
- 🟢 [572. Subtree of Another Tree](https://leetcode.com/problems/subtree-of-another-tree/)
- 🟡 [582. Kill Process](https://leetcode.com/problems/kill-process/) 🔒
- 🟢 [589. N-ary Tree Preorder Traversal](https://leetcode.com/problems/n-ary-tree-preorder-traversal/)
- 🟢 [590. N-ary Tree Postorder Traversal](https://leetcode.com/problems/n-ary-tree-postorder-traversal/)
- 🟢 [617. Merge Two Binary Trees](https://leetcode.com/problems/merge-two-binary-trees/)
- 🟡 [623. Add One Row to Tree](https://leetcode.com/problems/add-one-row-to-tree/)
- 🟢 [637. Average of Levels in Binary Tree](https://leetcode.com/problems/average-of-levels-in-binary-tree/)
- 🟡 [652. Find Duplicate Subtrees](https://leetcode.com/problems/find-duplicate-subtrees/)
- 🟡 [655. Print Binary Tree](https://leetcode.com/problems/print-binary-tree/)
- 🟡 [662. Maximum Width of Binary Tree](https://leetcode.com/problems/maximum-width-of-binary-tree/)
- 🟡 [663. Equal Tree Partition](https://leetcode.com/problems/equal-tree-partition/) 🔒
- 🟢 [671. Second Minimum Node In a Binary Tree](https://leetcode.com/problems/second-minimum-node-in-a-binary-tree/)
- 🟡 [690. Employee Importance](https://leetcode.com/problems/employee-importance/)
- 🟡 [742. Closest Leaf in a Binary Tree](https://leetcode.com/problems/closest-leaf-in-a-binary-tree/) 🔒
- 🟡 [814. Binary Tree Pruning](https://leetcode.com/problems/binary-tree-pruning/)
- 🟡 [863. All Nodes Distance K in Binary Tree](https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/)
- 🟢 [872. Leaf-Similar Trees](https://leetcode.com/problems/leaf-similar-trees/)
- 🟡 [951. Flip Equivalent Binary Trees](https://leetcode.com/problems/flip-equivalent-binary-trees/)
- 🟢 [965. Univalued Binary Tree](https://leetcode.com/problems/univalued-binary-tree/)
- 🟡 [971. Flip Binary Tree To Match Preorder Traversal](https://leetcode.com/problems/flip-binary-tree-to-match-preorder-traversal/)
- 🟡 [979. Distribute Coins in Binary Tree](https://leetcode.com/problems/distribute-coins-in-binary-tree/)
- 🔴 [987. Vertical Order Traversal of a Binary Tree](https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/)
- 🟢 [993. Cousins in Binary Tree](https://leetcode.com/problems/cousins-in-binary-tree/)
- 🟡 [998. Maximum Binary Tree II](https://leetcode.com/problems/maximum-binary-tree-ii/)
- 🟢 [1022. Sum of Root To Leaf Binary Numbers](https://leetcode.com/problems/sum-of-root-to-leaf-binary-numbers/)
- 🟡 [1110. Delete Nodes And Return Forest](https://leetcode.com/problems/delete-nodes-and-return-forest/)
- 🟡 [1120. Maximum Average Subtree](https://leetcode.com/problems/maximum-average-subtree/) 🔒
- 🟡 [1145. Binary Tree Coloring Game](https://leetcode.com/problems/binary-tree-coloring-game/)
- 🟡 [1161. Maximum Level Sum of a Binary Tree](https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/)
- 🟡 [1261. Find Elements in a Contaminated Binary Tree](https://leetcode.com/problems/find-elements-in-a-contaminated-binary-tree/)
- 🟡 [1273. Delete Tree Nodes](https://leetcode.com/problems/delete-tree-nodes/) 🔒
- 🟡 [1302. Deepest Leaves Sum](https://leetcode.com/problems/deepest-leaves-sum/)
- 🟡 [1315. Sum of Nodes with Even-Valued Grandparent](https://leetcode.com/problems/sum-of-nodes-with-even-valued-grandparent/)
- 🟡 [1325. Delete Leaves With a Given Value](https://leetcode.com/problems/delete-leaves-with-a-given-value/)
- 🟡 [1339. Maximum Product of Splitted Binary Tree](https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/)
- 🟡 [1361. Validate Binary Tree Nodes](https://leetcode.com/problems/validate-binary-tree-nodes/)
- 🟡 [1376. Time Needed to Inform All Employees](https://leetcode.com/problems/time-needed-to-inform-all-employees/)
- 🔴 [1377. Frog Position After T Seconds](https://leetcode.com/problems/frog-position-after-t-seconds/)
- 🟢 [1379. Find a Corresponding Node of a Binary Tree in a Clone of That Tree](https://leetcode.com/problems/find-a-corresponding-node-of-a-binary-tree-in-a-clone-of-that-tree/)
- 🟡 [1443. Minimum Time to Collect All Apples in a Tree](https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/)
- 🟡 [1448. Count Good Nodes in Binary Tree](https://leetcode.com/problems/count-good-nodes-in-binary-tree/)
- 🟢 [1469. Find All The Lonely Nodes](https://leetcode.com/problems/find-all-the-lonely-nodes/) 🔒
- 🟡 [1485. Clone Binary Tree With Random Pointer](https://leetcode.com/problems/clone-binary-tree-with-random-pointer/) 🔒
- 🟡 [1490. Clone N-ary Tree](https://leetcode.com/problems/clone-n-ary-tree/) 🔒
- 🟡 [1506. Find Root of N-Ary Tree](https://leetcode.com/problems/find-root-of-n-ary-tree/) 🔒
- 🔴 [1516. Move Sub-Tree of N-Ary Tree](https://leetcode.com/problems/move-sub-tree-of-n-ary-tree/) 🔒
- 🟡 [1519. Number of Nodes in the Sub-Tree With the Same Label](https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/)
- 🟡 [1522. Diameter of N-Ary Tree](https://leetcode.com/problems/diameter-of-n-ary-tree/) 🔒
- 🟡 [1530. Number of Good Leaf Nodes Pairs](https://leetcode.com/problems/number-of-good-leaf-nodes-pairs/)
- 🟡 [1600. Throne Inheritance](https://leetcode.com/problems/throne-inheritance/)
- 🟡 [1612. Check If Two Expression Trees are Equivalent](https://leetcode.com/problems/check-if-two-expression-trees-are-equivalent/) 🔒
- 🟡 [1628. Design an Expression Tree With Evaluate Function](https://leetcode.com/problems/design-an-expression-tree-with-evaluate-function/) 🔒
- 🟡 [1660. Correct a Binary Tree](https://leetcode.com/problems/correct-a-binary-tree/) 🔒
- 🟡 [1666. Change the Root of a Binary Tree](https://leetcode.com/problems/change-the-root-of-a-binary-tree/) 🔒
- 🔴 [1766. Tree of Coprimes](https://leetcode.com/problems/tree-of-coprimes/)
- 🟡 [1973. Count Nodes Equal to Sum of Descendants](https://leetcode.com/problems/count-nodes-equal-to-sum-of-descendants/) 🔒
- 🟡 [1993. Operations on Tree](https://leetcode.com/problems/operations-on-tree/)
- 🟡 [2049. Count Nodes With the Highest Score](https://leetcode.com/problems/count-nodes-with-the-highest-score/)
- 🟢 [2236. Root Equals Sum of Children](https://leetcode.com/problems/root-equals-sum-of-children/)
- 🟡 [2265. Count Nodes Equal to Average of Subtree](https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/)
- 🔴 [2322. Minimum Score After Removals on a Tree](https://leetcode.com/problems/minimum-score-after-removals-on-a-tree/)
- 🟢 [2331. Evaluate Boolean Binary Tree](https://leetcode.com/problems/evaluate-boolean-binary-tree/)
- 🟡 [2368. Reachable Nodes With Restrictions](https://leetcode.com/problems/reachable-nodes-with-restrictions/)
- 🟡 [2385. Amount of Time for Binary Tree to Be Infected](https://leetcode.com/problems/amount-of-time-for-binary-tree-to-be-infected/)
- 🟡 [2415. Reverse Odd Levels of Binary Tree](https://leetcode.com/problems/reverse-odd-levels-of-binary-tree/)
- 🟡 [2445. Number of Nodes With Value One](https://leetcode.com/problems/number-of-nodes-with-value-one/) 🔒
- 🔴 [2458. Height of Binary Tree After Subtree Removal Queries](https://leetcode.com/problems/height-of-binary-tree-after-subtree-removal-queries/)
- 🟡 [2477. Minimum Fuel Cost to Report to the Capital](https://leetcode.com/problems/minimum-fuel-cost-to-report-to-the-capital/)
- 🟡 [2641. Cousins in Binary Tree II](https://leetcode.com/problems/cousins-in-binary-tree-ii/)
- 🟢 [2689. Extract Kth Character From The Rope Tree](https://leetcode.com/problems/extract-kth-character-from-the-rope-tree/) 🔒
- 🟡 [2764. Is Array a Preorder of Some ‌Binary Tree](https://leetcode.com/problems/is-array-a-preorder-of-some-binary-tree/) 🔒
- 🟡 [2773. Height of Special Binary Tree](https://leetcode.com/problems/height-of-special-binary-tree/) 🔒
- 🔴 [2792. Count Nodes That Are Great Enough](https://leetcode.com/problems/count-nodes-that-are-great-enough/) 🔒
- 🔴 [2872. Maximum Number of K-Divisible Components](https://leetcode.com/problems/maximum-number-of-k-divisible-components/)
- 🟡 [3067. Count Pairs of Connectable Servers in a Weighted Tree Network](https://leetcode.com/problems/count-pairs-of-connectable-servers-in-a-weighted-tree-network/)
- 🟡 [3157. Find the Level of Tree with Minimum Sum](https://leetcode.com/problems/find-the-level-of-tree-with-minimum-sum/) 🔒
- 🔴 [3203. Find Minimum Diameter After Merging Two Trees](https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/)
- 🟡 [3249. Count the Number of Good Nodes](https://leetcode.com/problems/count-the-number-of-good-nodes/)
- 🔴 [3313. Find the Last Marked Nodes in Tree](https://leetcode.com/problems/find-the-last-marked-nodes-in-tree/) 🔒
- 🟡 [3319. K-th Largest Perfect Subtree Size in Binary Tree](https://leetcode.com/problems/k-th-largest-perfect-subtree-size-in-binary-tree/)
- 🟡 [3331. Find Subtree Sizes After Changes](https://leetcode.com/problems/find-subtree-sizes-after-changes/)
- 🟡 [3372. Maximize the Number of Target Nodes After Connecting Trees I](https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-i/)
- 🔴 [3373. Maximize the Number of Target Nodes After Connecting Trees II](https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-ii/)
- 🟡 [3558. Number of Ways to Assign Edge Weights I](https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-i/)
- 🔴 [3786. Total Sum of Interaction Cost in Tree Groups](https://leetcode.com/problems/total-sum-of-interaction-cost-in-tree-groups/)
- 🟡 [3997. Count Dominant Nodes in a Binary Tree](https://leetcode.com/problems/count-dominant-nodes-in-a-binary-tree/)
- 🟡 [4015. Weighted Sum of a Tree](https://leetcode.com/problems/weighted-sum-of-a-tree/)
- 🔴 [4018. Total Sum of Interaction Cost in Tree Groups II](https://leetcode.com/problems/total-sum-of-interaction-cost-in-tree-groups-ii/) 🔒

</details>

<details><summary><b>Binary Search Tree</b> (31)</summary>

- 🟡 [98. Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/)
- 🟡 [99. Recover Binary Search Tree](https://leetcode.com/problems/recover-binary-search-tree/)
- 🟢 [108. Convert Sorted Array to Binary Search Tree](https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/)
- 🟡 [173. Binary Search Tree Iterator](https://leetcode.com/problems/binary-search-tree-iterator/)
- 🟡 [230. Kth Smallest Element in a BST](https://leetcode.com/problems/kth-smallest-element-in-a-bst/)
- 🟢 [270. Closest Binary Search Tree Value](https://leetcode.com/problems/closest-binary-search-tree-value/) 🔒
- 🟡 [285. Inorder Successor in BST](https://leetcode.com/problems/inorder-successor-in-bst/) 🔒
- 🟡 [449. Serialize and Deserialize BST](https://leetcode.com/problems/serialize-and-deserialize-bst/)
- 🟡 [450. Delete Node in a BST](https://leetcode.com/problems/delete-node-in-a-bst/)
- 🟢 [501. Find Mode in Binary Search Tree](https://leetcode.com/problems/find-mode-in-binary-search-tree/)
- 🟡 [510. Inorder Successor in BST II](https://leetcode.com/problems/inorder-successor-in-bst-ii/) 🔒
- 🟢 [530. Minimum Absolute Difference in BST](https://leetcode.com/problems/minimum-absolute-difference-in-bst/)
- 🟡 [538. Convert BST to Greater Tree](https://leetcode.com/problems/convert-bst-to-greater-tree/)
- 🟢 [653. Two Sum IV - Input is a BST](https://leetcode.com/problems/two-sum-iv-input-is-a-bst/)
- 🟡 [669. Trim a Binary Search Tree](https://leetcode.com/problems/trim-a-binary-search-tree/)
- 🟢 [700. Search in a Binary Search Tree](https://leetcode.com/problems/search-in-a-binary-search-tree/)
- 🟡 [701. Insert into a Binary Search Tree](https://leetcode.com/problems/insert-into-a-binary-search-tree/)
- 🟡 [776. Split BST](https://leetcode.com/problems/split-bst/) 🔒
- 🟢 [783. Minimum Distance Between BST Nodes](https://leetcode.com/problems/minimum-distance-between-bst-nodes/)
- 🟢 [897. Increasing Order Search Tree](https://leetcode.com/problems/increasing-order-search-tree/)
- 🟢 [938. Range Sum of BST](https://leetcode.com/problems/range-sum-of-bst/)
- 🟡 [1038. Binary Search Tree to Greater Sum Tree](https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/)
- 🟡 [1214. Two Sum BSTs](https://leetcode.com/problems/two-sum-bsts/) 🔒
- 🟡 [1305. All Elements in Two Binary Search Trees](https://leetcode.com/problems/all-elements-in-two-binary-search-trees/)
- 🟡 [1382. Balance a Binary Search Tree](https://leetcode.com/problems/balance-a-binary-search-tree/)
- 🟡 [1586. Binary Search Tree Iterator II](https://leetcode.com/problems/binary-search-tree-iterator-ii/) 🔒
- 🟡 [1902. Depth of BST Given Insertion Order](https://leetcode.com/problems/depth-of-bst-given-insertion-order/) 🔒
- 🔴 [1932. Merge BSTs to Create Single BST](https://leetcode.com/problems/merge-bsts-to-create-single-bst/)
- 🟡 [2476. Closest Nodes Queries in a Binary Search Tree](https://leetcode.com/problems/closest-nodes-queries-in-a-binary-search-tree/)
- 🔴 [3526. Range XOR Queries with Subarray Reversals](https://leetcode.com/problems/range-xor-queries-with-subarray-reversals/) 🔒
- 🟡 [3831. Median of a Binary Search Tree Level](https://leetcode.com/problems/median-of-a-binary-search-tree-level/) 🔒

</details>

<details><summary><b>Root-to-Leaf / Path Sums</b> (17)</summary>

- 🟢 [112. Path Sum](https://leetcode.com/problems/path-sum/)
- 🟡 [113. Path Sum II](https://leetcode.com/problems/path-sum-ii/)
- 🔴 [124. Binary Tree Maximum Path Sum](https://leetcode.com/problems/binary-tree-maximum-path-sum/)
- 🟡 [437. Path Sum III](https://leetcode.com/problems/path-sum-iii/)
- 🟡 [666. Path Sum IV](https://leetcode.com/problems/path-sum-iv/) 🔒
- 🟡 [687. Longest Univalue Path](https://leetcode.com/problems/longest-univalue-path/)
- 🟡 [1080. Insufficient Nodes in Root to Leaf Paths](https://leetcode.com/problems/insufficient-nodes-in-root-to-leaf-paths/)
- 🟡 [1104. Path In Zigzag Labelled Binary Tree](https://leetcode.com/problems/path-in-zigzag-labelled-binary-tree/)
- 🟡 [1430. Check If a String Is a Valid Sequence from Root to Leaves Path in a Binary Tree](https://leetcode.com/problems/check-if-a-string-is-a-valid-sequence-from-root-to-leaves-path-in-a-binary-tree/) 🔒
- 🟡 [1457. Pseudo-Palindromic Paths in a Binary Tree](https://leetcode.com/problems/pseudo-palindromic-paths-in-a-binary-tree/)
- 🔴 [2277. Closest Node to Path in Tree](https://leetcode.com/problems/closest-node-to-path-in-tree/) 🔒
- 🟡 [2467. Most Profitable Path in a Tree](https://leetcode.com/problems/most-profitable-path-in-a-tree/)
- 🔴 [2791. Count Paths That Can Form a Palindrome in a Tree](https://leetcode.com/problems/count-paths-that-can-form-a-palindrome-in-a-tree/)
- 🔴 [3425. Longest Special Path](https://leetcode.com/problems/longest-special-path/)
- 🔴 [3486. Longest Special Path II](https://leetcode.com/problems/longest-special-path-ii/)
- 🔴 [3590. Kth Smallest Path XOR Sum](https://leetcode.com/problems/kth-smallest-path-xor-sum/)
- 🟡 [3879. Maximum Distinct Path Sum in a Binary Tree](https://leetcode.com/problems/maximum-distinct-path-sum-in-a-binary-tree/) 🔒

</details>

<details><summary><b>Level Order (BFS)</b> (14)</summary>

- 🟡 [102. Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/)
- 🟡 [103. Binary Tree Zigzag Level Order Traversal](https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/)
- 🟡 [107. Binary Tree Level Order Traversal II](https://leetcode.com/problems/binary-tree-level-order-traversal-ii/)
- 🟡 [199. Binary Tree Right Side View](https://leetcode.com/problems/binary-tree-right-side-view/)
- 🟡 [429. N-ary Tree Level Order Traversal](https://leetcode.com/problems/n-ary-tree-level-order-traversal/)
- 🟡 [919. Complete Binary Tree Inserter](https://leetcode.com/problems/complete-binary-tree-inserter/)
- 🟡 [958. Check Completeness of a Binary Tree](https://leetcode.com/problems/check-completeness-of-a-binary-tree/)
- 🟡 [1602. Find Nearest Right Node in Binary Tree](https://leetcode.com/problems/find-nearest-right-node-in-binary-tree/) 🔒
- 🟡 [1609. Even Odd Tree](https://leetcode.com/problems/even-odd-tree/)
- 🟡 [2471. Minimum Number of Operations to Sort a Binary Tree by Level](https://leetcode.com/problems/minimum-number-of-operations-to-sort-a-binary-tree-by-level/)
- 🟡 [2583. Kth Largest Sum in a Binary Tree](https://leetcode.com/problems/kth-largest-sum-in-a-binary-tree/)
- 🟡 [3787. Find Diameter Endpoints of a Tree](https://leetcode.com/problems/find-diameter-endpoints-of-a-tree/) 🔒
- 🟡 [3820. Pythagorean Distance Nodes in a Tree](https://leetcode.com/problems/pythagorean-distance-nodes-in-a-tree/)
- 🟡 [3902. Zigzag Level Sum of Binary Tree](https://leetcode.com/problems/zigzag-level-sum-of-binary-tree/) 🔒

</details>

<details><summary><b>Construct / Serialize</b> (13)</summary>

- 🟡 [105. Construct Binary Tree from Preorder and Inorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)
- 🟡 [106. Construct Binary Tree from Inorder and Postorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/)
- 🔴 [297. Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/)
- 🟡 [427. Construct Quad Tree](https://leetcode.com/problems/construct-quad-tree/)
- 🔴 [428. Serialize and Deserialize N-ary Tree](https://leetcode.com/problems/serialize-and-deserialize-n-ary-tree/) 🔒
- 🟡 [536. Construct Binary Tree from String](https://leetcode.com/problems/construct-binary-tree-from-string/) 🔒
- 🟡 [606. Construct String from Binary Tree](https://leetcode.com/problems/construct-string-from-binary-tree/)
- 🟡 [889. Construct Binary Tree from Preorder and Postorder Traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/)
- 🔴 [1028. Recover a Tree From Preorder Traversal](https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/)
- 🔴 [1597. Build Binary Expression Tree From Infix Expression](https://leetcode.com/problems/build-binary-expression-tree-from-infix-expression/) 🔒
- 🔴 [1719. Number Of Ways To Reconstruct A Tree](https://leetcode.com/problems/number-of-ways-to-reconstruct-a-tree/)
- 🟡 [2196. Create Binary Tree From Descriptions](https://leetcode.com/problems/create-binary-tree-from-descriptions/)
- 🔴 [2440. Create Components With Same Value](https://leetcode.com/problems/create-components-with-same-value/)

</details>

<details><summary><b>Lowest Common Ancestor</b> (13)</summary>

- 🟡 [235. Lowest Common Ancestor of a Binary Search Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/)
- 🟡 [236. Lowest Common Ancestor of a Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/)
- 🟡 [865. Smallest Subtree with all the Deepest Nodes](https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/)
- 🟡 [1026. Maximum Difference Between Node and Ancestor](https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/)
- 🟡 [1123. Lowest Common Ancestor of Deepest Leaves](https://leetcode.com/problems/lowest-common-ancestor-of-deepest-leaves/)
- 🟡 [1257. Smallest Common Region](https://leetcode.com/problems/smallest-common-region/) 🔒
- 🟡 [1644. Lowest Common Ancestor of a Binary Tree II](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-ii/) 🔒
- 🟡 [1650. Lowest Common Ancestor of a Binary Tree III](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iii/) 🔒
- 🟡 [1676. Lowest Common Ancestor of a Binary Tree IV](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iv/) 🔒
- 🟡 [1740. Find Distance in a Binary Tree](https://leetcode.com/problems/find-distance-in-a-binary-tree/) 🔒
- 🟡 [2096. Step-By-Step Directions From a Binary Tree Node to Another](https://leetcode.com/problems/step-by-step-directions-from-a-binary-tree-node-to-another/)
- 🔴 [2509. Cycle Length Queries in a Tree](https://leetcode.com/problems/cycle-length-queries-in-a-tree/)
- 🔴 [3715. Sum of Perfect Square Ancestors](https://leetcode.com/problems/sum-of-perfect-square-ancestors/)

</details>

<details><summary><b>Guessed from title (no tags yet)</b> (5)</summary>

- 🔴 [2753. Count Houses in a Circular Street II](https://leetcode.com/problems/count-houses-in-a-circular-street-ii/) 🔒
- 🔴 [4077. Minimize Inversions in a Prefix Tree](https://leetcode.com/problems/minimize-inversions-in-a-prefix-tree/)
- 🔴 [4082. Minimum Operations to Stabilize a Binary Tree](https://leetcode.com/problems/minimum-operations-to-stabilize-a-binary-tree/) 🔒
- 🟡 [4085. Find Root of a Colored Tree](https://leetcode.com/problems/find-root-of-a-colored-tree/)
- 🟡 [4112. Maximize Score After Zeroing Subtrees](https://leetcode.com/problems/maximize-score-after-zeroing-subtrees/)

</details>

## Heap / Top-K / K-way Merge

*Kth largest, top K frequent, running median, merge K sorted.* — 136 problems

<details><summary><b>Greedy + Heap (Scheduling)</b> (48)</summary>

- 🔴 [420. Strong Password Checker](https://leetcode.com/problems/strong-password-checker/)
- 🟡 [621. Task Scheduler](https://leetcode.com/problems/task-scheduler/)
- 🔴 [630. Course Schedule III](https://leetcode.com/problems/course-schedule-iii/)
- 🟡 [659. Split Array into Consecutive Subsequences](https://leetcode.com/problems/split-array-into-consecutive-subsequences/)
- 🟡 [767. Reorganize String](https://leetcode.com/problems/reorganize-string/)
- 🟡 [1054. Distant Barcodes](https://leetcode.com/problems/distant-barcodes/)
- 🟡 [1167. Minimum Cost to Connect Sticks](https://leetcode.com/problems/minimum-cost-to-connect-sticks/) 🔒
- 🔴 [1183. Maximum Number of Ones](https://leetcode.com/problems/maximum-number-of-ones/) 🔒
- 🔴 [1199. Minimum Time to Build Blocks](https://leetcode.com/problems/minimum-time-to-build-blocks/) 🔒
- 🟡 [1338. Reduce Array Size to The Half](https://leetcode.com/problems/reduce-array-size-to-the-half/)
- 🟡 [1353. Maximum Number of Events That Can Be Attended](https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/)
- 🔴 [1383. Maximum Performance of a Team](https://leetcode.com/problems/maximum-performance-of-a-team/)
- 🟡 [1405. Longest Happy String](https://leetcode.com/problems/longest-happy-string/)
- 🟡 [1488. Avoid Flood in The City](https://leetcode.com/problems/avoid-flood-in-the-city/)
- 🟡 [1642. Furthest Building You Can Reach](https://leetcode.com/problems/furthest-building-you-can-reach/)
- 🟡 [1648. Sell Diminishing-Valued Colored Balls](https://leetcode.com/problems/sell-diminishing-valued-colored-balls/)
- 🔴 [1675. Minimize Deviation in Array](https://leetcode.com/problems/minimize-deviation-in-array/)
- 🟡 [1686. Stone Game VI](https://leetcode.com/problems/stone-game-vi/)
- 🟡 [1705. Maximum Number of Eaten Apples](https://leetcode.com/problems/maximum-number-of-eaten-apples/)
- 🟡 [1753. Maximum Score From Removing Stones](https://leetcode.com/problems/maximum-score-from-removing-stones/)
- 🟡 [1792. Maximum Average Pass Ratio](https://leetcode.com/problems/maximum-average-pass-ratio/)
- 🟡 [1962. Remove Stones to Minimize the Total](https://leetcode.com/problems/remove-stones-to-minimize-the-total/)
- 🟡 [2182. Construct String With Repeat Limit](https://leetcode.com/problems/construct-string-with-repeat-limit/)
- 🟡 [2208. Minimum Operations to Halve Array Sum](https://leetcode.com/problems/minimum-operations-to-halve-array-sum/)
- 🟡 [2285. Maximum Total Importance of Roads](https://leetcode.com/problems/maximum-total-importance-of-roads/)
- 🟡 [2333. Minimum Sum of Squared Difference](https://leetcode.com/problems/minimum-sum-of-squared-difference/)
- 🟢 [2335. Minimum Amount of Time to Fill Cups](https://leetcode.com/problems/minimum-amount-of-time-to-fill-cups/)
- 🟢 [2357. Make Array Zero by Subtracting Equal Amounts](https://leetcode.com/problems/make-array-zero-by-subtracting-equal-amounts/)
- 🟡 [2497. Maximum Star Sum of a Graph](https://leetcode.com/problems/maximum-star-sum-of-a-graph/)
- 🟡 [2542. Maximum Subsequence Score](https://leetcode.com/problems/maximum-subsequence-score/)
- 🔴 [2551. Put Marbles in Bags](https://leetcode.com/problems/put-marbles-in-bags/)
- 🟡 [2599. Make the Prefix Sum Non-negative](https://leetcode.com/problems/make-the-prefix-sum-non-negative/) 🔒
- 🟡 [2611. Mice and Cheese](https://leetcode.com/problems/mice-and-cheese/)
- 🔴 [2931. Maximum Spending After Buying Items](https://leetcode.com/problems/maximum-spending-after-buying-items/)
- 🔴 [3049. Earliest Second to Mark Indices II](https://leetcode.com/problems/earliest-second-to-mark-indices-ii/)
- 🟡 [3081. Replace Question Marks in String to Minimize Its Value](https://leetcode.com/problems/replace-question-marks-in-string-to-minimize-its-value/)
- 🟡 [3170. Lexicographically Minimum String After Removing Stars](https://leetcode.com/problems/lexicographically-minimum-string-after-removing-stars/)
- 🟡 [3296. Minimum Number of Seconds to Make Mountain Height Zero](https://leetcode.com/problems/minimum-number-of-seconds-to-make-mountain-height-zero/)
- 🟡 [3362. Zero Array Transformation III](https://leetcode.com/problems/zero-array-transformation-iii/)
- 🟡 [3476. Maximize Profit from Task Assignment](https://leetcode.com/problems/maximize-profit-from-task-assignment/) 🔒
- 🔴 [3506. Find Time Required to Eliminate Bacterial Strains](https://leetcode.com/problems/find-time-required-to-eliminate-bacterial-strains/) 🔒
- 🟡 [3572. Maximize Y‑Sum by Picking a Triplet of Distinct X‑Values](https://leetcode.com/problems/maximize-ysum-by-picking-a-triplet-of-distinct-xvalues/)
- 🟡 [3645. Maximum Total from Optimal Activation Order](https://leetcode.com/problems/maximum-total-from-optimal-activation-order/)
- 🟡 [3711. Maximum Transactions Without Negative Balance](https://leetcode.com/problems/maximum-transactions-without-negative-balance/) 🔒
- 🟡 [3763. Maximum Total Sum with Threshold Constraints](https://leetcode.com/problems/maximum-total-sum-with-threshold-constraints/) 🔒
- 🟡 [3780. Maximum Sum of Three Numbers Divisible by Three](https://leetcode.com/problems/maximum-sum-of-three-numbers-divisible-by-three/)
- 🟡 [3781. Maximum Score After Binary Swaps](https://leetcode.com/problems/maximum-score-after-binary-swaps/)
- 🟡 [3947. Maximum Number of Items From Sale II](https://leetcode.com/problems/maximum-number-of-items-from-sale-ii/)

</details>

<details><summary><b>Priority Queue</b> (39)</summary>

- 🔴 [407. Trapping Rain Water II](https://leetcode.com/problems/trapping-rain-water-ii/)
- 🟡 [451. Sort Characters By Frequency](https://leetcode.com/problems/sort-characters-by-frequency/)
- 🟢 [506. Relative Ranks](https://leetcode.com/problems/relative-ranks/)
- 🔴 [675. Cut Off Trees for Golf Event](https://leetcode.com/problems/cut-off-trees-for-golf-event/)
- 🟡 [855. Exam Room](https://leetcode.com/problems/exam-room/)
- 🟡 [912. Sort an Array](https://leetcode.com/problems/sort-an-array/)
- 🟡 [1057. Campus Bikes](https://leetcode.com/problems/campus-bikes/) 🔒
- 🟢 [1086. High Five](https://leetcode.com/problems/high-five/) 🔒
- 🔴 [1172. Dinner Plate Stacks](https://leetcode.com/problems/dinner-plate-stacks/)
- 🔴 [1263. Minimum Moves to Move a Box to Their Target Location](https://leetcode.com/problems/minimum-moves-to-move-a-box-to-their-target-location/)
- 🔴 [1354. Construct Target Array With Multiple Sums](https://leetcode.com/problems/construct-target-array-with-multiple-sums/)
- 🟡 [1424. Diagonal Traverse II](https://leetcode.com/problems/diagonal-traverse-ii/)
- 🟢 [1464. Maximum Product of Two Elements in an Array](https://leetcode.com/problems/maximum-product-of-two-elements-in-an-array/)
- 🟡 [1500. Design a File Sharing System](https://leetcode.com/problems/design-a-file-sharing-system/) 🔒
- 🟡 [1834. Single-Threaded CPU](https://leetcode.com/problems/single-threaded-cpu/)
- 🟡 [1845. Seat Reservation Manager](https://leetcode.com/problems/seat-reservation-manager/)
- 🟡 [1878. Get Biggest Three Rhombus Sums in a Grid](https://leetcode.com/problems/get-biggest-three-rhombus-sums-in-a-grid/)
- 🟡 [1882. Process Tasks Using Servers](https://leetcode.com/problems/process-tasks-using-servers/)
- 🔴 [1912. Design Movie Rental System](https://leetcode.com/problems/design-movie-rental-system/)
- 🟡 [1942. The Number of the Smallest Unoccupied Chair](https://leetcode.com/problems/the-number-of-the-smallest-unoccupied-chair/)
- 🟡 [2015. Average Height of Buildings in Each Segment](https://leetcode.com/problems/average-height-of-buildings-in-each-segment/) 🔒
- 🟡 [2034. Stock Price Fluctuation ](https://leetcode.com/problems/stock-price-fluctuation/)
- 🔴 [2102. Sequentially Ordinal Rank Tracker](https://leetcode.com/problems/sequentially-ordinal-rank-tracker/)
- 🟢 [2231. Largest Number After Digit Swaps by Parity](https://leetcode.com/problems/largest-number-after-digit-swaps-by-parity/)
- 🔴 [2254. Design Video Sharing Platform](https://leetcode.com/problems/design-video-sharing-platform/) 🔒
- 🟡 [2336. Smallest Number in Infinite Set](https://leetcode.com/problems/smallest-number-in-infinite-set/)
- 🟡 [2342. Max Sum of a Pair With Equal Sum of Digits](https://leetcode.com/problems/max-sum-of-a-pair-with-equal-sum-of-digits/)
- 🔴 [2344. Minimum Deletions to Make Array Divisible](https://leetcode.com/problems/minimum-deletions-to-make-array-divisible/)
- 🟡 [2349. Design a Number Container System](https://leetcode.com/problems/design-a-number-container-system/)
- 🟡 [2353. Design a Food Rating System](https://leetcode.com/problems/design-a-food-rating-system/)
- 🟡 [2456. Most Popular Video Creator](https://leetcode.com/problems/most-popular-video-creator/)
- 🔴 [2503. Maximum Number of Points From Grid Queries](https://leetcode.com/problems/maximum-number-of-points-from-grid-queries/)
- 🟡 [2812. Find the Safest Path in a Grid](https://leetcode.com/problems/find-the-safest-path-in-a-grid/)
- 🔴 [3369. Design an Array Statistics Tracker ](https://leetcode.com/problems/design-an-array-statistics-tracker/) 🔒
- 🟡 [3391. Design a 3D Binary Matrix with Efficient Layer Tracking](https://leetcode.com/problems/design-a-3d-binary-matrix-with-efficient-layer-tracking/) 🔒
- 🟡 [3408. Design Task Manager](https://leetcode.com/problems/design-task-manager/)
- 🟡 [3607. Power Grid Maintenance](https://leetcode.com/problems/power-grid-maintenance/)
- 🟡 [3815. Design Auction System](https://leetcode.com/problems/design-auction-system/)
- 🟡 [3885. Design Event Manager](https://leetcode.com/problems/design-event-manager/)

</details>

<details><summary><b>Top-K Elements</b> (28)</summary>

- 🟡 [215. Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/)
- 🔴 [272. Closest Binary Search Tree Value II](https://leetcode.com/problems/closest-binary-search-tree-value-ii/) 🔒
- 🟡 [347. Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/)
- 🔴 [358. Rearrange String k Distance Apart](https://leetcode.com/problems/rearrange-string-k-distance-apart/) 🔒
- 🟢 [703. Kth Largest Element in a Stream](https://leetcode.com/problems/kth-largest-element-in-a-stream/)
- 🟡 [786. K-th Smallest Prime Fraction](https://leetcode.com/problems/k-th-smallest-prime-fraction/)
- 🔴 [857. Minimum Cost to Hire K Workers](https://leetcode.com/problems/minimum-cost-to-hire-k-workers/)
- 🟡 [973. K Closest Points to Origin](https://leetcode.com/problems/k-closest-points-to-origin/)
- 🟢 [1337. The K Weakest Rows in a Matrix](https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix/)
- 🔴 [1439. Find the Kth Smallest Sum of a Matrix With Sorted Rows](https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/)
- 🟡 [1738. Find Kth Largest XOR Coordinate Value](https://leetcode.com/problems/find-kth-largest-xor-coordinate-value/)
- 🟡 [1985. Find the Kth Largest Integer in the Array](https://leetcode.com/problems/find-the-kth-largest-integer-in-the-array/)
- 🟢 [2099. Find Subsequence of Length K With the Largest Sum](https://leetcode.com/problems/find-subsequence-of-length-k-with-the-largest-sum/)
- 🟡 [2146. K Highest Ranked Items Within a Price Range](https://leetcode.com/problems/k-highest-ranked-items-within-a-price-range/)
- 🟡 [2233. Maximum Product After K Increments](https://leetcode.com/problems/maximum-product-after-k-increments/)
- 🟡 [2343. Query Kth Smallest Trimmed Number](https://leetcode.com/problems/query-kth-smallest-trimmed-number/)
- 🔴 [2386. Find the K-Sum of an Array](https://leetcode.com/problems/find-the-k-sum-of-an-array/)
- 🟡 [2462. Total Cost to Hire K Workers](https://leetcode.com/problems/total-cost-to-hire-k-workers/)
- 🟡 [2512. Reward Top K Students](https://leetcode.com/problems/reward-top-k-students/)
- 🟡 [2530. Maximal Score After Applying K Operations](https://leetcode.com/problems/maximal-score-after-applying-k-operations/)
- 🔴 [2813. Maximum Elegance of a K-Length Subsequence](https://leetcode.com/problems/maximum-elegance-of-a-k-length-subsequence/)
- 🟡 [3092. Most Frequent IDs](https://leetcode.com/problems/most-frequent-ids/)
- 🟢 [3264. Final Array State After K Multiplication Operations I](https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-i/)
- 🔴 [3266. Final Array State After K Multiplication Operations II](https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-ii/)
- 🟡 [3275. K-th Nearest Obstacle Queries](https://leetcode.com/problems/k-th-nearest-obstacle-queries/)
- 🟡 [3462. Maximum Sum With at Most K Elements](https://leetcode.com/problems/maximum-sum-with-at-most-k-elements/)
- 🟡 [3478. Choose K Elements With Maximum Sum](https://leetcode.com/problems/choose-k-elements-with-maximum-sum/)
- 🟡 [3767. Maximize Points After Choosing K Tasks](https://leetcode.com/problems/maximize-points-after-choosing-k-tasks/)

</details>

<details><summary><b>Heap Simulation</b> (14)</summary>

- 🟢 [1046. Last Stone Weight](https://leetcode.com/problems/last-stone-weight/)
- 🔴 [1606. Find Servers That Handled Most Number of Requests](https://leetcode.com/problems/find-servers-that-handled-most-number-of-requests/)
- 🟡 [1801. Number of Orders in the Backlog](https://leetcode.com/problems/number-of-orders-in-the-backlog/)
- 🟢 [2500. Delete Greatest Value in Each Row](https://leetcode.com/problems/delete-greatest-value-in-each-row/)
- 🔴 [2532. Time to Cross a Bridge](https://leetcode.com/problems/time-to-cross-a-bridge/)
- 🟢 [2558. Take Gifts From the Richest Pile](https://leetcode.com/problems/take-gifts-from-the-richest-pile/)
- 🟡 [2593. Find Score of an Array After Marking All Elements](https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements/)
- 🟡 [2679. Sum in a Matrix](https://leetcode.com/problems/sum-in-a-matrix/)
- 🟢 [2974. Minimum Number Game](https://leetcode.com/problems/minimum-number-game/)
- 🟡 [3066. Minimum Operations to Exceed Threshold Value II](https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-ii/)
- 🟡 [3080. Mark Elements on Array by Performing Queries](https://leetcode.com/problems/mark-elements-on-array-by-performing-queries/)
- 🟢 [3507. Minimum Pair Removal to Sort Array I](https://leetcode.com/problems/minimum-pair-removal-to-sort-array-i/)
- 🔴 [3510. Minimum Pair Removal to Sort Array II](https://leetcode.com/problems/minimum-pair-removal-to-sort-array-ii/)
- 🟢 [4065. Rearrange Array by Removing Distinct Values](https://leetcode.com/problems/rearrange-array-by-removing-distinct-values/)

</details>

<details><summary><b>K-way Merge</b> (4)</summary>

- 🔴 [23. Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/)
- 🟡 [355. Design Twitter](https://leetcode.com/problems/design-twitter/)
- 🟡 [373. Find K Pairs with Smallest Sums](https://leetcode.com/problems/find-k-pairs-with-smallest-sums/)
- 🔴 [632. Smallest Range Covering Elements from K Lists](https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/)

</details>

<details><summary><b>Two Heaps</b> (3)</summary>

- 🔴 [295. Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/)
- 🔴 [480. Sliding Window Median](https://leetcode.com/problems/sliding-window-median/)
- 🔴 [502. IPO](https://leetcode.com/problems/ipo/)

</details>

## Graph & Grid Traversal (BFS / DFS)

*Islands, flood fill, connected components, unweighted shortest path.* — 99 problems

<details><summary><b>Graph DFS / BFS</b> (38)</summary>

- 🟡 [133. Clone Graph](https://leetcode.com/problems/clone-graph/)
- 🟡 [277. Find the Celebrity](https://leetcode.com/problems/find-the-celebrity/) 🔒
- 🟡 [339. Nested List Weight Sum](https://leetcode.com/problems/nested-list-weight-sum/) 🔒
- 🟡 [364. Nested List Weight Sum II](https://leetcode.com/problems/nested-list-weight-sum-ii/) 🔒
- 🟡 [365. Water and Jug Problem](https://leetcode.com/problems/water-and-jug-problem/)
- 🟡 [385. Mini Parser](https://leetcode.com/problems/mini-parser/)
- 🟡 [388. Longest Absolute File Path](https://leetcode.com/problems/longest-absolute-file-path/)
- 🟡 [565. Array Nesting](https://leetcode.com/problems/array-nesting/)
- 🟡 [672. Bulb Switcher II](https://leetcode.com/problems/bulb-switcher-ii/)
- 🟡 [841. Keys and Rooms](https://leetcode.com/problems/keys-and-rooms/)
- 🟢 [997. Find the Town Judge](https://leetcode.com/problems/find-the-town-judge/)
- 🔴 [1036. Escape a Large Maze](https://leetcode.com/problems/escape-a-large-maze/)
- 🔴 [1153. String Transforms Into Another String](https://leetcode.com/problems/string-transforms-into-another-string/) 🔒
- 🟡 [1236. Web Crawler](https://leetcode.com/problems/web-crawler/) 🔒
- 🟡 [1306. Jump Game III](https://leetcode.com/problems/jump-game-iii/)
- 🟡 [1466. Reorder Routes to Make All Paths Lead to the City Zero](https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/)
- 🟡 [1557. Minimum Number of Vertices to Reach All Nodes](https://leetcode.com/problems/minimum-number-of-vertices-to-reach-all-nodes/)
- 🟡 [1615. Maximal Network Rank](https://leetcode.com/problems/maximal-network-rank/)
- 🟡 [1625. Lexicographically Smallest String After Applying Operations](https://leetcode.com/problems/lexicographically-smallest-string-after-applying-operations/)
- 🟡 [1743. Restore the Array From Adjacent Pairs](https://leetcode.com/problems/restore-the-array-from-adjacent-pairs/)
- 🔴 [1761. Minimum Degree of a Connected Trio in a Graph](https://leetcode.com/problems/minimum-degree-of-a-connected-trio-in-a-graph/)
- 🔴 [1782. Count Pairs Of Nodes](https://leetcode.com/problems/count-pairs-of-nodes/)
- 🟢 [1791. Find Center of Star Graph](https://leetcode.com/problems/find-center-of-star-graph/)
- 🟡 [2077. Paths in Maze That Lead to Same Room](https://leetcode.com/problems/paths-in-maze-that-lead-to-same-room/) 🔒
- 🟡 [2101. Detonate the Maximum Bombs](https://leetcode.com/problems/detonate-the-maximum-bombs/)
- 🔴 [2242. Maximum Score of a Node Sequence](https://leetcode.com/problems/maximum-score-of-a-node-sequence/)
- 🟡 [2359. Find Closest Node to Given Two Nodes](https://leetcode.com/problems/find-closest-node-to-given-two-nodes/)
- 🟡 [2374. Node With Highest Edge Score](https://leetcode.com/problems/node-with-highest-edge-score/)
- 🔴 [2508. Add Edges to Make Degrees of All Nodes Even](https://leetcode.com/problems/add-edges-to-make-degrees-of-all-nodes-even/)
- 🟡 [2924. Find Champion II](https://leetcode.com/problems/find-champion-ii/)
- 🔴 [3017. Count the Number of Houses at a Certain Distance II](https://leetcode.com/problems/count-the-number-of-houses-at-a-certain-distance-ii/)
- 🔴 [3244. Shortest Distance After Road Addition Queries II](https://leetcode.com/problems/shortest-distance-after-road-addition-queries-ii/)
- 🟡 [3310. Remove Methods From Project](https://leetcode.com/problems/remove-methods-from-project/)
- 🟡 [3387. Maximize Amount After Two Days of Conversions](https://leetcode.com/problems/maximize-amount-after-two-days-of-conversions/)
- 🟡 [3528. Unit Conversion I](https://leetcode.com/problems/unit-conversion-i/)
- 🟡 [3535. Unit Conversion II](https://leetcode.com/problems/unit-conversion-ii/) 🔒
- 🔴 [3547. Maximum Sum of Edge Values in a Graph](https://leetcode.com/problems/maximum-sum-of-edge-values-in-a-graph/)
- 🟡 [3656. Determine if a Simple Graph Exists](https://leetcode.com/problems/determine-if-a-simple-graph-exists/) 🔒

</details>

<details><summary><b>Grid BFS / DFS</b> (34)</summary>

- 🟡 [130. Surrounded Regions](https://leetcode.com/problems/surrounded-regions/)
- 🟡 [200. Number of Islands](https://leetcode.com/problems/number-of-islands/)
- 🔴 [302. Smallest Rectangle Enclosing Black Pixels](https://leetcode.com/problems/smallest-rectangle-enclosing-black-pixels/) 🔒
- 🔴 [317. Shortest Distance from All Buildings](https://leetcode.com/problems/shortest-distance-from-all-buildings/) 🔒
- 🟡 [417. Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/)
- 🟡 [419. Battleships in a Board](https://leetcode.com/problems/battleships-in-a-board/)
- 🟢 [463. Island Perimeter](https://leetcode.com/problems/island-perimeter/)
- 🟡 [490. The Maze](https://leetcode.com/problems/the-maze/) 🔒
- 🟡 [529. Minesweeper](https://leetcode.com/problems/minesweeper/)
- 🟡 [695. Max Area of Island](https://leetcode.com/problems/max-area-of-island/)
- 🟢 [733. Flood Fill](https://leetcode.com/problems/flood-fill/)
- 🔴 [749. Contain Virus](https://leetcode.com/problems/contain-virus/)
- 🔴 [864. Shortest Path to Get All Keys](https://leetcode.com/problems/shortest-path-to-get-all-keys/)
- 🟡 [909. Snakes and Ladders](https://leetcode.com/problems/snakes-and-ladders/)
- 🟡 [934. Shortest Bridge](https://leetcode.com/problems/shortest-bridge/)
- 🟡 [1034. Coloring A Border](https://leetcode.com/problems/coloring-a-border/)
- 🟡 [1091. Shortest Path in Binary Matrix](https://leetcode.com/problems/shortest-path-in-binary-matrix/)
- 🔴 [1210. Minimum Moves to Reach Target with Rotations](https://leetcode.com/problems/minimum-moves-to-reach-target-with-rotations/)
- 🔴 [1284. Minimum Number of Flips to Convert Binary Matrix to Zero Matrix](https://leetcode.com/problems/minimum-number-of-flips-to-convert-binary-matrix-to-zero-matrix/)
- 🔴 [1293. Shortest Path in a Grid with Obstacles Elimination](https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/)
- 🟡 [1730. Shortest Path to Get Food](https://leetcode.com/problems/shortest-path-to-get-food/) 🔒
- 🟡 [1765. Map of Highest Peak](https://leetcode.com/problems/map-of-highest-peak/)
- 🟡 [1778. Shortest Path in a Hidden Grid](https://leetcode.com/problems/shortest-path-in-a-hidden-grid/) 🔒
- 🟡 [1926. Nearest Exit from Entrance in Maze](https://leetcode.com/problems/nearest-exit-from-entrance-in-maze/)
- 🟡 [1992. Find All Groups of Farmland](https://leetcode.com/problems/find-all-groups-of-farmland/)
- 🟡 [2174. Remove All Ones With Row and Column Flips II](https://leetcode.com/problems/remove-all-ones-with-row-and-column-flips-ii/) 🔒
- 🔴 [2258. Escape the Spreading Fire](https://leetcode.com/problems/escape-the-spreading-fire/)
- 🟡 [2596. Check Knight Tour Configuration](https://leetcode.com/problems/check-knight-tour-configuration/)
- 🔴 [2814. Minimum Time Takes to Reach Destination Without Drowning](https://leetcode.com/problems/minimum-time-takes-to-reach-destination-without-drowning/) 🔒
- 🔴 [3311. Construct 2D Grid Matching Graph Layout](https://leetcode.com/problems/construct-2d-grid-matching-graph-layout/)
- 🟡 [3552. Grid Teleportation Traversal](https://leetcode.com/problems/grid-teleportation-traversal/)
- 🟡 [3568. Minimum Moves to Clean the Classroom](https://leetcode.com/problems/minimum-moves-to-clean-the-classroom/)
- 🟢 [3898. Find the Degree of Each Vertex](https://leetcode.com/problems/find-the-degree-of-each-vertex/)
- 🟡 [3905. Multi Source Flood Fill](https://leetcode.com/problems/multi-source-flood-fill/)

</details>

<details><summary><b>Graph BFS</b> (22)</summary>

- 🔴 [127. Word Ladder](https://leetcode.com/problems/word-ladder/)
- 🟡 [433. Minimum Genetic Mutation](https://leetcode.com/problems/minimum-genetic-mutation/)
- 🟡 [752. Open the Lock](https://leetcode.com/problems/open-the-lock/)
- 🔴 [815. Bus Routes](https://leetcode.com/problems/bus-routes/)
- 🔴 [854. K-Similar Strings](https://leetcode.com/problems/k-similar-strings/)
- 🟡 [1129. Shortest Path with Alternating Colors](https://leetcode.com/problems/shortest-path-with-alternating-colors/)
- 🔴 [1298. Maximum Candies You Can Get from Boxes](https://leetcode.com/problems/maximum-candies-you-can-get-from-boxes/)
- 🟡 [1311. Get Watched Videos by Your Friends](https://leetcode.com/problems/get-watched-videos-by-your-friends/)
- 🔴 [1345. Jump Game IV](https://leetcode.com/problems/jump-game-iv/)
- 🟡 [1654. Minimum Jumps to Reach Home](https://leetcode.com/problems/minimum-jumps-to-reach-home/)
- 🟡 [2039. The Time When the Network Becomes Idle](https://leetcode.com/problems/the-time-when-the-network-becomes-idle/)
- 🟡 [2059. Minimum Operations to Convert Number](https://leetcode.com/problems/minimum-operations-to-convert-number/)
- 🔴 [2608. Shortest Cycle in a Graph](https://leetcode.com/problems/shortest-cycle-in-a-graph/)
- 🟡 [3015. Count the Number of Houses at a Certain Distance I](https://leetcode.com/problems/count-the-number-of-houses-at-a-certain-distance-i/)
- 🔴 [3141. Maximum Hamming Distances](https://leetcode.com/problems/maximum-hamming-distances/) 🔒
- 🟡 [3243. Shortest Distance After Road Addition Queries I](https://leetcode.com/problems/shortest-distance-after-road-addition-queries-i/)
- 🔴 [3283. Maximum Number of Moves to Kill All Pawns](https://leetcode.com/problems/maximum-number-of-moves-to-kill-all-pawns/)
- 🔴 [3385. Minimum Time to Break Locks II](https://leetcode.com/problems/minimum-time-to-break-locks-ii/) 🔒
- 🟡 [3629. Minimum Jumps to Reach End via Prime Teleportation](https://leetcode.com/problems/minimum-jumps-to-reach-end-via-prime-teleportation/)
- 🟡 [3690. Split and Merge Array Transformation](https://leetcode.com/problems/split-and-merge-array-transformation/)
- 🟡 [3807. Minimum Cost to Repair Edges to Traverse a Graph](https://leetcode.com/problems/minimum-cost-to-repair-edges-to-traverse-a-graph/) 🔒
- 🔴 [3924. Minimum Threshold Path With Limited Heavy Edges](https://leetcode.com/problems/minimum-threshold-path-with-limited-heavy-edges/)

</details>

<details><summary><b>Multi-source BFS</b> (3)</summary>

- 🟡 [286. Walls and Gates](https://leetcode.com/problems/walls-and-gates/) 🔒
- 🟡 [542. 01 Matrix](https://leetcode.com/problems/01-matrix/)
- 🟡 [994. Rotting Oranges](https://leetcode.com/problems/rotting-oranges/)

</details>

<details><summary><b>Guessed from title (no tags yet)</b> (2)</summary>

- 🟢 [3963. Create Grid With Exactly One Path](https://leetcode.com/problems/create-grid-with-exactly-one-path/)
- 🟡 [4084. Last Visited Cell in a Directional Grid](https://leetcode.com/problems/last-visited-cell-in-a-directional-grid/)

</details>

## Topological Sort

*Ordering with prerequisites; cycle check in a directed graph.* — 34 problems

<details><summary><b>Topological Order (Kahn's / DFS)</b> (31)</summary>

- 🟡 [310. Minimum Height Trees](https://leetcode.com/problems/minimum-height-trees/)
- 🟡 [444. Sequence Reconstruction](https://leetcode.com/problems/sequence-reconstruction/) 🔒
- 🔴 [631. Design Excel Sum Formula](https://leetcode.com/problems/design-excel-sum-formula/) 🔒
- 🟡 [851. Loud and Rich](https://leetcode.com/problems/loud-and-rich/)
- 🔴 [913. Cat and Mouse](https://leetcode.com/problems/cat-and-mouse/)
- 🟡 [1136. Parallel Courses](https://leetcode.com/problems/parallel-courses/) 🔒
- 🔴 [1203. Sort Items by Groups Respecting Dependencies](https://leetcode.com/problems/sort-items-by-groups-respecting-dependencies/)
- 🟡 [1245. Tree Diameter](https://leetcode.com/problems/tree-diameter/) 🔒
- 🟡 [1462. Course Schedule IV](https://leetcode.com/problems/course-schedule-iv/)
- 🔴 [1591. Strange Printer II](https://leetcode.com/problems/strange-printer-ii/)
- 🔴 [1632. Rank Transform of a Matrix](https://leetcode.com/problems/rank-transform-of-a-matrix/)
- 🔴 [1728. Cat and Mouse II](https://leetcode.com/problems/cat-and-mouse-ii/)
- 🟡 [1786. Number of Restricted Paths From First to Last Node](https://leetcode.com/problems/number-of-restricted-paths-from-first-to-last-node/)
- 🔴 [1857. Largest Color Value in a Directed Graph](https://leetcode.com/problems/largest-color-value-in-a-directed-graph/)
- 🔴 [1916. Count Ways to Build Rooms in an Ant Colony](https://leetcode.com/problems/count-ways-to-build-rooms-in-an-ant-colony/)
- 🟡 [1976. Number of Ways to Arrive at Destination](https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/)
- 🔴 [2050. Parallel Courses III](https://leetcode.com/problems/parallel-courses-iii/)
- 🟡 [2115. Find All Possible Recipes from Given Supplies](https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies/)
- 🟡 [2192. All Ancestors of a Node in a Directed Acyclic Graph](https://leetcode.com/problems/all-ancestors-of-a-node-in-a-directed-acyclic-graph/)
- 🔴 [2204. Distance to a Cycle in Undirected Graph](https://leetcode.com/problems/distance-to-a-cycle-in-undirected-graph/) 🔒
- 🔴 [2246. Longest Path With Different Adjacent Characters](https://leetcode.com/problems/longest-path-with-different-adjacent-characters/)
- 🔴 [2328. Number of Increasing Paths in a Grid](https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/)
- 🔴 [2371. Minimize Maximum Value in a Grid](https://leetcode.com/problems/minimize-maximum-value-in-a-grid/) 🔒
- 🔴 [2392. Build a Matrix With Conditions](https://leetcode.com/problems/build-a-matrix-with-conditions/)
- 🔴 [2603. Collect Coins in a Tree](https://leetcode.com/problems/collect-coins-in-a-tree/)
- 🔴 [3383. Minimum Runes to Add to Cast Spell](https://leetcode.com/problems/minimum-runes-to-add-to-cast-spell/) 🔒
- 🔴 [3435. Frequencies of Shortest Supersequences](https://leetcode.com/problems/frequencies-of-shortest-supersequences/)
- 🟡 [3481. Apply Substitutions](https://leetcode.com/problems/apply-substitutions/) 🔒
- 🔴 [3530. Maximum Profit from Valid Topological Order in DAG](https://leetcode.com/problems/maximum-profit-from-valid-topological-order-in-dag/)
- 🔴 [3620. Network Recovery Pathways](https://leetcode.com/problems/network-recovery-pathways/)
- 🔴 [3812. Minimum Edge Toggles on a Tree](https://leetcode.com/problems/minimum-edge-toggles-on-a-tree/)

</details>

<details><summary><b>Cycle Detection / Kahn's</b> (2)</summary>

- 🟡 [207. Course Schedule](https://leetcode.com/problems/course-schedule/)
- 🟡 [210. Course Schedule II](https://leetcode.com/problems/course-schedule-ii/)

</details>

<details><summary><b>Ordering from Constraints</b> (1)</summary>

- 🔴 [269. Alien Dictionary](https://leetcode.com/problems/alien-dictionary/) 🔒

</details>

## Union Find (Disjoint Set)

*Merging groups, connectivity as edges arrive, redundant edges.* — 69 problems

<details><summary><b>Union Find</b> (69)</summary>

- 🟡 [261. Graph Valid Tree](https://leetcode.com/problems/graph-valid-tree/) 🔒
- 🔴 [305. Number of Islands II](https://leetcode.com/problems/number-of-islands-ii/) 🔒
- 🟡 [323. Number of Connected Components in an Undirected Graph](https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/) 🔒
- 🔴 [352. Data Stream as Disjoint Intervals](https://leetcode.com/problems/data-stream-as-disjoint-intervals/)
- 🟡 [547. Number of Provinces](https://leetcode.com/problems/number-of-provinces/)
- 🟡 [684. Redundant Connection](https://leetcode.com/problems/redundant-connection/)
- 🔴 [685. Redundant Connection II](https://leetcode.com/problems/redundant-connection-ii/)
- 🟡 [721. Accounts Merge](https://leetcode.com/problems/accounts-merge/)
- 🟡 [737. Sentence Similarity II](https://leetcode.com/problems/sentence-similarity-ii/) 🔒
- 🔴 [765. Couples Holding Hands](https://leetcode.com/problems/couples-holding-hands/)
- 🔴 [803. Bricks Falling When Hit](https://leetcode.com/problems/bricks-falling-when-hit/)
- 🔴 [827. Making A Large Island](https://leetcode.com/problems/making-a-large-island/)
- 🔴 [839. Similar String Groups](https://leetcode.com/problems/similar-string-groups/)
- 🔴 [924. Minimize Malware Spread](https://leetcode.com/problems/minimize-malware-spread/)
- 🔴 [928. Minimize Malware Spread II](https://leetcode.com/problems/minimize-malware-spread-ii/)
- 🔴 [952. Largest Component Size by Common Factor](https://leetcode.com/problems/largest-component-size-by-common-factor/)
- 🟡 [990. Satisfiability of Equality Equations](https://leetcode.com/problems/satisfiability-of-equality-equations/)
- 🟡 [1020. Number of Enclaves](https://leetcode.com/problems/number-of-enclaves/)
- 🟡 [1061. Lexicographically Smallest Equivalent String](https://leetcode.com/problems/lexicographically-smallest-equivalent-string/)
- 🟡 [1101. The Earliest Moment When Everyone Become Friends](https://leetcode.com/problems/the-earliest-moment-when-everyone-become-friends/) 🔒
- 🟡 [1202. Smallest String With Swaps](https://leetcode.com/problems/smallest-string-with-swaps/)
- 🟡 [1254. Number of Closed Islands](https://leetcode.com/problems/number-of-closed-islands/)
- 🟡 [1258. Synonymous Sentences](https://leetcode.com/problems/synonymous-sentences/) 🔒
- 🟡 [1267. Count Servers that Communicate](https://leetcode.com/problems/count-servers-that-communicate/)
- 🟡 [1319. Number of Operations to Make Network Connected](https://leetcode.com/problems/number-of-operations-to-make-network-connected/)
- 🟡 [1391. Check if There is a Valid Path in a Grid](https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/)
- 🟡 [1559. Detect Cycles in 2D Grid](https://leetcode.com/problems/detect-cycles-in-2d-grid/)
- 🔴 [1569. Number of Ways to Reorder Array to Get Same BST](https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/)
- 🔴 [1579. Remove Max Number of Edges to Keep Graph Fully Traversable](https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/)
- 🔴 [1627. Graph Connectivity With Threshold](https://leetcode.com/problems/graph-connectivity-with-threshold/)
- 🔴 [1697. Checking Existence of Edge Length Limited Paths](https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/)
- 🟡 [1722. Minimize Hamming Distance After Swap Operations](https://leetcode.com/problems/minimize-hamming-distance-after-swap-operations/)
- 🟡 [1905. Count Sub Islands](https://leetcode.com/problems/count-sub-islands/)
- 🔴 [1970. Last Day Where You Can Still Cross](https://leetcode.com/problems/last-day-where-you-can-still-cross/)
- 🟢 [1971. Find if Path Exists in Graph](https://leetcode.com/problems/find-if-path-exists-in-graph/)
- 🔴 [1998. GCD Sort of an Array](https://leetcode.com/problems/gcd-sort-of-an-array/)
- 🔴 [2076. Process Restricted Friend Requests](https://leetcode.com/problems/process-restricted-friend-requests/)
- 🔴 [2092. Find All People With Secret](https://leetcode.com/problems/find-all-people-with-secret/)
- 🔴 [2157. Groups of Strings](https://leetcode.com/problems/groups-of-strings/)
- 🔴 [2307. Check for Contradictions in Equations](https://leetcode.com/problems/check-for-contradictions-in-equations/) 🔒
- 🟡 [2316. Count Unreachable Pairs of Nodes in an Undirected Graph](https://leetcode.com/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/)
- 🔴 [2334. Subarray With Elements Greater Than Varying Threshold](https://leetcode.com/problems/subarray-with-elements-greater-than-varying-threshold/)
- 🔴 [2382. Maximum Segment Sum After Removals](https://leetcode.com/problems/maximum-segment-sum-after-removals/)
- 🔴 [2421. Number of Good Paths](https://leetcode.com/problems/number-of-good-paths/)
- 🟡 [2424. Longest Uploaded Prefix](https://leetcode.com/problems/longest-uploaded-prefix/)
- 🟡 [2492. Minimum Score of a Path Between Two Cities](https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities/)
- 🔴 [2493. Divide Nodes Into the Maximum Number of Groups](https://leetcode.com/problems/divide-nodes-into-the-maximum-number-of-groups/)
- 🔴 [2573. Find the String with LCP](https://leetcode.com/problems/find-the-string-with-lcp/)
- 🔴 [2612. Minimum Reverse Operations](https://leetcode.com/problems/minimum-reverse-operations/)
- 🟡 [2658. Maximum Number of Fish in a Grid](https://leetcode.com/problems/maximum-number-of-fish-in-a-grid/)
- 🟡 [2685. Count the Number of Complete Components](https://leetcode.com/problems/count-the-number-of-complete-components/)
- 🔴 [2709. Greatest Common Divisor Traversal](https://leetcode.com/problems/greatest-common-divisor-traversal/)
- 🟡 [2782. Number of Unique Categories](https://leetcode.com/problems/number-of-unique-categories/) 🔒
- 🟡 [2852. Sum of Remoteness of All Cells](https://leetcode.com/problems/sum-of-remoteness-of-all-cells/) 🔒
- 🟡 [2948. Make Lexicographically Smallest Array by Swapping Elements](https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/)
- 🔴 [3108. Minimum Cost Walk in Weighted Graph](https://leetcode.com/problems/minimum-cost-walk-in-weighted-graph/)
- 🔴 [3235. Check if the Rectangle Corner Is Reachable](https://leetcode.com/problems/check-if-the-rectangle-corner-is-reachable/)
- 🔴 [3378. Count Connected Components in LCM Graph](https://leetcode.com/problems/count-connected-components-in-lcm-graph/)
- 🟡 [3493. Properties Graph](https://leetcode.com/problems/properties-graph/)
- 🟡 [3532. Path Existence Queries in a Graph I](https://leetcode.com/problems/path-existence-queries-in-a-graph-i/)
- 🟡 [3608. Minimum Time for K Connected Components](https://leetcode.com/problems/minimum-time-for-k-connected-components/)
- 🟡 [3613. Minimize Maximum Component Cost](https://leetcode.com/problems/minimize-maximum-component-cost/)
- 🟡 [3619. Count Islands With Total Value Divisible by K](https://leetcode.com/problems/count-islands-with-total-value-divisible-by-k/)
- 🔴 [3666. Minimum Operations to Equalize Binary String](https://leetcode.com/problems/minimum-operations-to-equalize-binary-string/)
- 🔴 [3695. Maximize Alternating Sum Using Swaps](https://leetcode.com/problems/maximize-alternating-sum-using-swaps/)
- 🔴 [3710. Maximum Partition Factor](https://leetcode.com/problems/maximum-partition-factor/)
- 🔴 [3873. Maximum Points Activated with One Addition](https://leetcode.com/problems/maximum-points-activated-with-one-addition/)
- 🔴 [3887. Incremental Even-Weighted Cycle Queries](https://leetcode.com/problems/incremental-even-weighted-cycle-queries/)
- 🔴 [3910. Count Connected Subgraphs with Even Node Sum](https://leetcode.com/problems/count-connected-subgraphs-with-even-node-sum/)

</details>

## Shortest Path (Dijkstra / Bellman-Ford / Floyd)

*Weighted graphs: cheapest / fastest route.* — 47 problems

<details><summary><b>Weighted Shortest Path</b> (28)</summary>

- 🟡 [1810. Minimum Path Cost in a Hidden Grid](https://leetcode.com/problems/minimum-path-cost-in-a-hidden-grid/) 🔒
- 🔴 [2203. Minimum Weighted Subgraph With the Required Paths](https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths/)
- 🟡 [2297. Jump Game VIII](https://leetcode.com/problems/jump-game-viii/) 🔒
- 🟡 [2473. Minimum Cost to Buy Apples](https://leetcode.com/problems/minimum-cost-to-buy-apples/) 🔒
- 🔴 [2577. Minimum Time to Visit a Cell In a Grid](https://leetcode.com/problems/minimum-time-to-visit-a-cell-in-a-grid/)
- 🔴 [2642. Design Graph With Shortest Path Calculator](https://leetcode.com/problems/design-graph-with-shortest-path-calculator/)
- 🟡 [2662. Minimum Cost of a Path With Special Roads](https://leetcode.com/problems/minimum-cost-of-a-path-with-special-roads/)
- 🔴 [2699. Modify Graph Edge Weights](https://leetcode.com/problems/modify-graph-edge-weights/)
- 🔴 [2714. Find Shortest Path with K Hops](https://leetcode.com/problems/find-shortest-path-with-k-hops/) 🔒
- 🟡 [2737. Find the Closest Marked Node](https://leetcode.com/problems/find-the-closest-marked-node/) 🔒
- 🔴 [2959. Number of Possible Sets of Closing Branches](https://leetcode.com/problems/number-of-possible-sets-of-closing-branches/)
- 🟡 [2976. Minimum Cost to Convert String I](https://leetcode.com/problems/minimum-cost-to-convert-string-i/)
- 🔴 [2977. Minimum Cost to Convert String II](https://leetcode.com/problems/minimum-cost-to-convert-string-ii/)
- 🟡 [3112. Minimum Time to Visit Disappearing Nodes](https://leetcode.com/problems/minimum-time-to-visit-disappearing-nodes/)
- 🔴 [3123. Find Edges in Shortest Paths](https://leetcode.com/problems/find-edges-in-shortest-paths/)
- 🟡 [3286. Find a Safe Walk Through a Grid](https://leetcode.com/problems/find-a-safe-walk-through-a-grid/)
- 🟡 [3341. Find Minimum Time to Reach Last Room I](https://leetcode.com/problems/find-minimum-time-to-reach-last-room-i/)
- 🟡 [3342. Find Minimum Time to Reach Last Room II](https://leetcode.com/problems/find-minimum-time-to-reach-last-room-ii/)
- 🟡 [3377. Digit Operations to Make Two Integers Equal](https://leetcode.com/problems/digit-operations-to-make-two-integers-equal/)
- 🟡 [3419. Minimize the Maximum Edge Weight of Graph](https://leetcode.com/problems/minimize-the-maximum-edge-weight-of-graph/)
- 🔴 [3594. Minimum Time to Transport All Individuals](https://leetcode.com/problems/minimum-time-to-transport-all-individuals/)
- 🟡 [3604. Minimum Time to Reach Destination in Directed Graph](https://leetcode.com/problems/minimum-time-to-reach-destination-in-directed-graph/)
- 🟡 [3650. Minimum Cost Path with Edge Reversals](https://leetcode.com/problems/minimum-cost-path-with-edge-reversals/)
- 🔴 [3928. Minimum Cost to Buy Apples II](https://leetcode.com/problems/minimum-cost-to-buy-apples-ii/)
- 🟡 [3970. Shortest Path With At Most K Consecutive Identical Characters](https://leetcode.com/problems/shortest-path-with-at-most-k-consecutive-identical-characters/)
- 🔴 [3977. Minimum Time to Reach Target With Limited Power](https://leetcode.com/problems/minimum-time-to-reach-target-with-limited-power/)
- 🔴 [4003. Minimum Cost Path with Alternating Directions III](https://leetcode.com/problems/minimum-cost-path-with-alternating-directions-iii/)
- 🔴 [4046. Minimum Cost Path With At Most K Turns](https://leetcode.com/problems/minimum-cost-path-with-at-most-k-turns/)

</details>

<details><summary><b>Dijkstra</b> (14)</summary>

- 🔴 [499. The Maze III](https://leetcode.com/problems/the-maze-iii/) 🔒
- 🟡 [505. The Maze II](https://leetcode.com/problems/the-maze-ii/) 🔒
- 🟡 [743. Network Delay Time](https://leetcode.com/problems/network-delay-time/)
- 🔴 [778. Swim in Rising Water](https://leetcode.com/problems/swim-in-rising-water/)
- 🔴 [882. Reachable Nodes In Subdivided Graph](https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/)
- 🟡 [1102. Path With Maximum Minimum Value](https://leetcode.com/problems/path-with-maximum-minimum-value/) 🔒
- 🟡 [1334. Find the City With the Smallest Number of Neighbors at a Threshold Distance](https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/)
- 🔴 [1368. Minimum Cost to Make at Least One Valid Path in a Grid](https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/)
- 🟡 [1514. Path with Maximum Probability](https://leetcode.com/problems/path-with-maximum-probability/)
- 🟡 [1631. Path With Minimum Effort](https://leetcode.com/problems/path-with-minimum-effort/)
- 🔴 [1928. Minimum Cost to Reach Destination in Time](https://leetcode.com/problems/minimum-cost-to-reach-destination-in-time/)
- 🔴 [2045. Second Minimum Time to Reach Destination](https://leetcode.com/problems/second-minimum-time-to-reach-destination/)
- 🟡 [2093. Minimum Cost to Reach City With Discounts](https://leetcode.com/problems/minimum-cost-to-reach-city-with-discounts/) 🔒
- 🔴 [2290. Minimum Obstacle Removal to Reach Corner](https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/)

</details>

<details><summary><b>A* Search</b> (3)</summary>

- 🔴 [773. Sliding Puzzle](https://leetcode.com/problems/sliding-puzzle/)
- 🔴 [818. Race Car](https://leetcode.com/problems/race-car/)
- 🟡 [1197. Minimum Knight Moves](https://leetcode.com/problems/minimum-knight-moves/) 🔒

</details>

<details><summary><b>Bellman-Ford</b> (2)</summary>

- 🟡 [399. Evaluate Division](https://leetcode.com/problems/evaluate-division/)
- 🟡 [787. Cheapest Flights Within K Stops](https://leetcode.com/problems/cheapest-flights-within-k-stops/)

</details>

## Advanced Graph

*MST, Euler paths, strongly connected components, bipartite, flows, bridges.* — 36 problems

<details><summary><b>Bipartite / Coloring</b> (13)</summary>

- 🟡 [785. Is Graph Bipartite?](https://leetcode.com/problems/is-graph-bipartite/)
- 🟡 [886. Possible Bipartition](https://leetcode.com/problems/possible-bipartition/)
- 🟡 [947. Most Stones Removed with Same Row or Column](https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/)
- 🟡 [1042. Flower Planting With No Adjacent](https://leetcode.com/problems/flower-planting-with-no-adjacent/)
- 🟡 [1066. Campus Bikes II](https://leetcode.com/problems/campus-bikes-ii/) 🔒
- 🔴 [1349. Maximum Students Taking Exam](https://leetcode.com/problems/maximum-students-taking-exam/)
- 🔴 [1411. Number of Ways to Paint N × 3 Grid](https://leetcode.com/problems/number-of-ways-to-paint-n-3-grid/)
- 🔴 [1434. Number of Ways to Wear Different Hats to Each Other](https://leetcode.com/problems/number-of-ways-to-wear-different-hats-to-each-other/)
- 🔴 [1595. Minimum Cost to Connect Two Groups of Points](https://leetcode.com/problems/minimum-cost-to-connect-two-groups-of-points/)
- 🟡 [1820. Maximum Number of Accepted Invitations](https://leetcode.com/problems/maximum-number-of-accepted-invitations/) 🔒
- 🔴 [1879. Minimum XOR Sum of Two Arrays](https://leetcode.com/problems/minimum-xor-sum-of-two-arrays/)
- 🔴 [1931. Painting a Grid With Three Different Colors](https://leetcode.com/problems/painting-a-grid-with-three-different-colors/)
- 🟡 [1947. Maximum Compatibility Score Sum](https://leetcode.com/problems/maximum-compatibility-score-sum/)

</details>

<details><summary><b>SCC / Bridges</b> (7)</summary>

- 🟡 [802. Find Eventual Safe States](https://leetcode.com/problems/find-eventual-safe-states/)
- 🟡 [1059. All Paths from Source Lead to Destination](https://leetcode.com/problems/all-paths-from-source-lead-to-destination/) 🔒
- 🔴 [1192. Critical Connections in a Network](https://leetcode.com/problems/critical-connections-in-a-network/)
- 🔴 [1568. Minimum Number of Days to Disconnect Island](https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/)
- 🔴 [2127. Maximum Employees to Be Invited to a Meeting](https://leetcode.com/problems/maximum-employees-to-be-invited-to-a-meeting/)
- 🔴 [2360. Longest Cycle in a Graph](https://leetcode.com/problems/longest-cycle-in-a-graph/)
- 🔴 [2876. Count Visited Nodes in a Directed Graph](https://leetcode.com/problems/count-visited-nodes-in-a-directed-graph/)

</details>

<details><summary><b>Minimum Spanning Tree</b> (6)</summary>

- 🟡 [1135. Connecting Cities With Minimum Cost](https://leetcode.com/problems/connecting-cities-with-minimum-cost/) 🔒
- 🔴 [1168. Optimize Water Distribution in a Village](https://leetcode.com/problems/optimize-water-distribution-in-a-village/) 🔒
- 🔴 [1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/)
- 🟡 [1584. Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/)
- 🔴 [1724. Checking Existence of Edge Length Limited Paths II](https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths-ii/) 🔒
- 🔴 [3600. Maximize Spanning Tree Stability with Upgrades](https://leetcode.com/problems/maximize-spanning-tree-stability-with-upgrades/)

</details>

<details><summary><b>Flow / Matching</b> (4)</summary>

- 🟡 [1029. Two City Scheduling](https://leetcode.com/problems/two-city-scheduling/)
- 🟡 [1605. Find Valid Matrix Given Row and Column Sums](https://leetcode.com/problems/find-valid-matrix-given-row-and-column-sums/)
- 🔴 [2123. Minimum Operations to Remove Adjacent Ones in Matrix](https://leetcode.com/problems/minimum-operations-to-remove-adjacent-ones-in-matrix/) 🔒
- 🔴 [4004. Minimum Moves to Balance Circular Array II](https://leetcode.com/problems/minimum-moves-to-balance-circular-array-ii/) 🔒

</details>

<details><summary><b>Eulerian Path</b> (3)</summary>

- 🔴 [332. Reconstruct Itinerary](https://leetcode.com/problems/reconstruct-itinerary/)
- 🔴 [753. Cracking the Safe](https://leetcode.com/problems/cracking-the-safe/)
- 🔴 [2097. Valid Arrangement of Pairs](https://leetcode.com/problems/valid-arrangement-of-pairs/)

</details>

<details><summary><b>Other</b> (3)</summary>

- 🔴 [943. Find the Shortest Superstring](https://leetcode.com/problems/find-the-shortest-superstring/)
- 🟡 [959. Regions Cut By Slashes](https://leetcode.com/problems/regions-cut-by-slashes/)
- 🔴 [980. Unique Paths III](https://leetcode.com/problems/unique-paths-iii/)

</details>

## Backtracking

*Generate all subsets / permutations / combinations; N-Queens, Sudoku.* — 105 problems

<details><summary><b>Search / Enumeration</b> (37)</summary>

- 🟡 [89. Gray Code](https://leetcode.com/problems/gray-code/)
- 🟡 [95. Unique Binary Search Trees II](https://leetcode.com/problems/unique-binary-search-trees-ii/)
- 🟡 [294. Flip Game II](https://leetcode.com/problems/flip-game-ii/) 🔒
- 🟡 [351. Android Unlock Patterns](https://leetcode.com/problems/android-unlock-patterns/) 🔒
- 🟡 [357. Count Numbers with Unique Digits](https://leetcode.com/problems/count-numbers-with-unique-digits/)
- 🟢 [401. Binary Watch](https://leetcode.com/problems/binary-watch/)
- 🔴 [465. Optimal Account Balancing](https://leetcode.com/problems/optimal-account-balancing/) 🔒
- 🟡 [473. Matchsticks to Square](https://leetcode.com/problems/matchsticks-to-square/)
- 🔴 [489. Robot Room Cleaner](https://leetcode.com/problems/robot-room-cleaner/) 🔒
- 🟡 [491. Non-decreasing Subsequences](https://leetcode.com/problems/non-decreasing-subsequences/)
- 🟡 [526. Beautiful Arrangement](https://leetcode.com/problems/beautiful-arrangement/)
- 🟡 [638. Shopping Offers](https://leetcode.com/problems/shopping-offers/)
- 🔴 [679. 24 Game](https://leetcode.com/problems/24-game/)
- 🟡 [967. Numbers With Same Consecutive Differences](https://leetcode.com/problems/numbers-with-same-consecutive-differences/)
- 🔴 [996. Number of Squareful Arrays](https://leetcode.com/problems/number-of-squareful-arrays/)
- 🔴 [1088. Confusing Number II](https://leetcode.com/problems/confusing-number-ii/) 🔒
- 🟡 [1215. Stepping Numbers](https://leetcode.com/problems/stepping-numbers/) 🔒
- 🔴 [1240. Tiling a Rectangle with the Fewest Squares](https://leetcode.com/problems/tiling-a-rectangle-with-the-fewest-squares/)
- 🔴 [1467. Probability of a Two Boxes Having The Same Number of Distinct Balls](https://leetcode.com/problems/probability-of-a-two-boxes-having-the-same-number-of-distinct-balls/)
- 🔴 [1601. Maximum Number of Achievable Transfer Requests](https://leetcode.com/problems/maximum-number-of-achievable-transfer-requests/)
- 🔴 [1655. Distribute Repeating Integers](https://leetcode.com/problems/distribute-repeating-integers/)
- 🟡 [1718. Construct the Lexicographically Largest Valid Sequence](https://leetcode.com/problems/construct-the-lexicographically-largest-valid-sequence/)
- 🔴 [1723. Find Minimum Time to Finish All Jobs](https://leetcode.com/problems/find-minimum-time-to-finish-all-jobs/)
- 🟡 [1774. Closest Dessert Cost](https://leetcode.com/problems/closest-dessert-cost/)
- 🔴 [1799. Maximize Score After N Operations](https://leetcode.com/problems/maximize-score-after-n-operations/)
- 🟡 [1986. Minimum Number of Work Sessions to Finish the Tasks](https://leetcode.com/problems/minimum-number-of-work-sessions-to-finish-the-tasks/)
- 🟡 [2048. Next Greater Numerically Balanced Number](https://leetcode.com/problems/next-greater-numerically-balanced-number/)
- 🔴 [2151. Maximum Good People Based on Statements](https://leetcode.com/problems/maximum-good-people-based-on-statements/)
- 🟡 [2152. Minimum Number of Lines to Cover Points](https://leetcode.com/problems/minimum-number-of-lines-to-cover-points/) 🔒
- 🟡 [2178. Maximum Split of Positive Even Integers](https://leetcode.com/problems/maximum-split-of-positive-even-integers/)
- 🟡 [2212. Maximum Points in an Archery Competition](https://leetcode.com/problems/maximum-points-in-an-archery-competition/)
- 🟡 [2305. Fair Distribution of Cookies](https://leetcode.com/problems/fair-distribution-of-cookies/)
- 🟡 [2698. Find the Punishment Number of an Integer](https://leetcode.com/problems/find-the-punishment-number-of-an-integer/)
- 🟡 [2708. Maximum Strength of a Group](https://leetcode.com/problems/maximum-strength-of-a-group/)
- 🟡 [3376. Minimum Time to Break Locks I](https://leetcode.com/problems/minimum-time-to-break-locks-i/)
- 🔴 [3646. Next Special Palindrome Number](https://leetcode.com/problems/next-special-palindrome-number/)
- 🟡 [3669. Balanced K-Factor Decomposition](https://leetcode.com/problems/balanced-k-factor-decomposition/)

</details>

<details><summary><b>String Generation</b> (35)</summary>

- 🟡 [17. Letter Combinations of a Phone Number](https://leetcode.com/problems/letter-combinations-of-a-phone-number/)
- 🟡 [22. Generate Parentheses](https://leetcode.com/problems/generate-parentheses/)
- 🟡 [93. Restore IP Addresses](https://leetcode.com/problems/restore-ip-addresses/)
- 🔴 [126. Word Ladder II](https://leetcode.com/problems/word-ladder-ii/)
- 🔴 [140. Word Break II](https://leetcode.com/problems/word-break-ii/)
- 🔴 [282. Expression Add Operators](https://leetcode.com/problems/expression-add-operators/)
- 🟡 [291. Word Pattern II](https://leetcode.com/problems/word-pattern-ii/) 🔒
- 🔴 [301. Remove Invalid Parentheses](https://leetcode.com/problems/remove-invalid-parentheses/)
- 🟡 [306. Additive Number](https://leetcode.com/problems/additive-number/)
- 🟡 [320. Generalized Abbreviation](https://leetcode.com/problems/generalized-abbreviation/) 🔒
- 🔴 [411. Minimum Unique Word Abbreviation](https://leetcode.com/problems/minimum-unique-word-abbreviation/) 🔒
- 🟡 [681. Next Closest Time](https://leetcode.com/problems/next-closest-time/) 🔒
- 🔴 [691. Stickers to Spell Word](https://leetcode.com/problems/stickers-to-spell-word/)
- 🟡 [756. Pyramid Transition Matrix](https://leetcode.com/problems/pyramid-transition-matrix/)
- 🟡 [816. Ambiguous Coordinates](https://leetcode.com/problems/ambiguous-coordinates/)
- 🟡 [842. Split Array into Fibonacci Sequence](https://leetcode.com/problems/split-array-into-fibonacci-sequence/)
- 🟡 [949. Largest Time for Given Digits](https://leetcode.com/problems/largest-time-for-given-digits/)
- 🟡 [988. Smallest String Starting From Leaf](https://leetcode.com/problems/smallest-string-starting-from-leaf/)
- 🟡 [1079. Letter Tile Possibilities](https://leetcode.com/problems/letter-tile-possibilities/)
- 🟡 [1087. Brace Expansion](https://leetcode.com/problems/brace-expansion/) 🔒
- 🔴 [1096. Brace Expansion II](https://leetcode.com/problems/brace-expansion-ii/)
- 🟡 [1239. Maximum Length of a Concatenated String with Unique Characters](https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/)
- 🔴 [1255. Maximum Score Words Formed by Letters](https://leetcode.com/problems/maximum-score-words-formed-by-letters/)
- 🔴 [1307. Verbal Arithmetic Puzzle](https://leetcode.com/problems/verbal-arithmetic-puzzle/)
- 🟡 [1415. The k-th Lexicographical String of All Happy Strings of Length n](https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/)
- 🟡 [1593. Split a String Into the Max Number of Unique Substrings](https://leetcode.com/problems/split-a-string-into-the-max-number-of-unique-substrings/)
- 🟡 [1849. Splitting a String Into Descending Consecutive Values](https://leetcode.com/problems/splitting-a-string-into-descending-consecutive-values/)
- 🟡 [1980. Find Unique Binary String](https://leetcode.com/problems/find-unique-binary-string/)
- 🟡 [2002. Maximum Product of the Length of Two Palindromic Subsequences](https://leetcode.com/problems/maximum-product-of-the-length-of-two-palindromic-subsequences/)
- 🔴 [2014. Longest Subsequence Repeated k Times](https://leetcode.com/problems/longest-subsequence-repeated-k-times/)
- 🟡 [2375. Construct Smallest Number From DI String](https://leetcode.com/problems/construct-smallest-number-from-di-string/)
- 🟡 [3211. Generate Binary Strings Without Adjacent Zeros](https://leetcode.com/problems/generate-binary-strings-without-adjacent-zeros/)
- 🔴 [3348. Smallest Divisible Digit Product II](https://leetcode.com/problems/smallest-divisible-digit-product-ii/)
- 🟡 [3799. Word Squares II](https://leetcode.com/problems/word-squares-ii/)
- 🟡 [3955. Valid Binary Strings With Cost Limit](https://leetcode.com/problems/valid-binary-strings-with-cost-limit/)

</details>

<details><summary><b>Subsets / Combinations</b> (15)</summary>

- 🟡 [39. Combination Sum](https://leetcode.com/problems/combination-sum/)
- 🟡 [40. Combination Sum II](https://leetcode.com/problems/combination-sum-ii/)
- 🟡 [77. Combinations](https://leetcode.com/problems/combinations/)
- 🟡 [78. Subsets](https://leetcode.com/problems/subsets/)
- 🟡 [90. Subsets II](https://leetcode.com/problems/subsets-ii/)
- 🟡 [131. Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning/)
- 🟡 [216. Combination Sum III](https://leetcode.com/problems/combination-sum-iii/)
- 🟡 [254. Factor Combinations](https://leetcode.com/problems/factor-combinations/) 🔒
- 🟡 [698. Partition to K Equal Sum Subsets](https://leetcode.com/problems/partition-to-k-equal-sum-subsets/)
- 🟡 [1286. Iterator for Combination](https://leetcode.com/problems/iterator-for-combination/)
- 🟢 [1863. Sum of All Subset XOR Totals](https://leetcode.com/problems/sum-of-all-subset-xor-totals/)
- 🟡 [2044. Count Number of Maximum Bitwise-OR Subsets](https://leetcode.com/problems/count-number-of-maximum-bitwise-or-subsets/)
- 🔴 [2056. Number of Valid Move Combinations On Chessboard](https://leetcode.com/problems/number-of-valid-move-combinations-on-chessboard/)
- 🟡 [2597. The Number of Beautiful Subsets](https://leetcode.com/problems/the-number-of-beautiful-subsets/)
- 🟡 [2767. Partition String Into Minimum Beautiful Substrings](https://leetcode.com/problems/partition-string-into-minimum-beautiful-substrings/)

</details>

<details><summary><b>Grid Backtracking</b> (8)</summary>

- 🟡 [79. Word Search](https://leetcode.com/problems/word-search/)
- 🟢 [257. Binary Tree Paths](https://leetcode.com/problems/binary-tree-paths/)
- 🟡 [797. All Paths From Source to Target](https://leetcode.com/problems/all-paths-from-source-to-target/)
- 🟡 [1219. Path with Maximum Gold](https://leetcode.com/problems/path-with-maximum-gold/)
- 🔴 [2065. Maximum Path Quality of a Graph](https://leetcode.com/problems/maximum-path-quality-of-a-graph/)
- 🟡 [2397. Maximum Rows Covered by Columns](https://leetcode.com/problems/maximum-rows-covered-by-columns/)
- 🟡 [2664. The Knight’s Tour](https://leetcode.com/problems/the-knights-tour/) 🔒
- 🟡 [2850. Minimum Moves to Spread Stones Over Grid](https://leetcode.com/problems/minimum-moves-to-spread-stones-over-grid/)

</details>

<details><summary><b>Permutations</b> (7)</summary>

- 🟡 [46. Permutations](https://leetcode.com/problems/permutations/)
- 🟡 [47. Permutations II](https://leetcode.com/problems/permutations-ii/)
- 🟡 [267. Palindrome Permutation II](https://leetcode.com/problems/palindrome-permutation-ii/) 🔒
- 🟡 [784. Letter Case Permutation](https://leetcode.com/problems/letter-case-permutation/)
- 🟡 [1238. Circular Permutation in Binary Representation](https://leetcode.com/problems/circular-permutation-in-binary-representation/)
- 🟡 [2992. Number of Self-Divisible Permutations](https://leetcode.com/problems/number-of-self-divisible-permutations/) 🔒
- 🟡 [3437. Permutations III](https://leetcode.com/problems/permutations-iii/) 🔒

</details>

<details><summary><b>Constraint Search (N-Queens / Sudoku)</b> (3)</summary>

- 🔴 [37. Sudoku Solver](https://leetcode.com/problems/sudoku-solver/)
- 🔴 [51. N-Queens](https://leetcode.com/problems/n-queens/)
- 🔴 [52. N-Queens II](https://leetcode.com/problems/n-queens-ii/)

</details>

## Dynamic Programming

*Overlapping subproblems: count ways, min / max cost, best subsequence.* — 556 problems

<details><summary><b>1-D / Sequence DP</b> (234)</summary>

- 🟢 [70. Climbing Stairs](https://leetcode.com/problems/climbing-stairs/)
- 🟡 [91. Decode Ways](https://leetcode.com/problems/decode-ways/)
- 🟢 [118. Pascal's Triangle](https://leetcode.com/problems/pascals-triangle/)
- 🟢 [119. Pascal's Triangle II](https://leetcode.com/problems/pascals-triangle-ii/)
- 🟡 [120. Triangle](https://leetcode.com/problems/triangle/)
- 🟡 [139. Word Break](https://leetcode.com/problems/word-break/)
- 🟡 [198. House Robber](https://leetcode.com/problems/house-robber/)
- 🟡 [213. House Robber II](https://leetcode.com/problems/house-robber-ii/)
- 🟡 [256. Paint House](https://leetcode.com/problems/paint-house/) 🔒
- 🟡 [264. Ugly Number II](https://leetcode.com/problems/ugly-number-ii/)
- 🔴 [265. Paint House II](https://leetcode.com/problems/paint-house-ii/) 🔒
- 🟡 [276. Paint Fence](https://leetcode.com/problems/paint-fence/) 🔒
- 🟡 [313. Super Ugly Number](https://leetcode.com/problems/super-ugly-number/)
- 🟡 [343. Integer Break](https://leetcode.com/problems/integer-break/)
- 🟡 [368. Largest Divisible Subset](https://leetcode.com/problems/largest-divisible-subset/)
- 🟡 [376. Wiggle Subsequence](https://leetcode.com/problems/wiggle-subsequence/)
- 🟡 [377. Combination Sum IV](https://leetcode.com/problems/combination-sum-iv/)
- 🟡 [396. Rotate Function](https://leetcode.com/problems/rotate-function/)
- 🟡 [397. Integer Replacement](https://leetcode.com/problems/integer-replacement/)
- 🔴 [403. Frog Jump](https://leetcode.com/problems/frog-jump/)
- 🔴 [446. Arithmetic Slices II - Subsequence](https://leetcode.com/problems/arithmetic-slices-ii-subsequence/)
- 🟢 [509. Fibonacci Number](https://leetcode.com/problems/fibonacci-number/)
- 🔴 [552. Student Attendance Record II](https://leetcode.com/problems/student-attendance-record-ii/)
- 🟡 [553. Optimal Division](https://leetcode.com/problems/optimal-division/)
- 🟡 [576. Out of Boundary Paths](https://leetcode.com/problems/out-of-boundary-paths/)
- 🔴 [600. Non-negative Integers without Consecutive Ones](https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/)
- 🔴 [629. K Inverse Pairs Array](https://leetcode.com/problems/k-inverse-pairs-array/)
- 🟡 [650. 2 Keys Keyboard](https://leetcode.com/problems/2-keys-keyboard/)
- 🟡 [651. 4 Keys Keyboard](https://leetcode.com/problems/4-keys-keyboard/) 🔒
- 🟡 [688. Knight Probability in Chessboard](https://leetcode.com/problems/knight-probability-in-chessboard/)
- 🟡 [740. Delete and Earn](https://leetcode.com/problems/delete-and-earn/)
- 🟢 [746. Min Cost Climbing Stairs](https://leetcode.com/problems/min-cost-climbing-stairs/)
- 🟡 [764. Largest Plus Sign](https://leetcode.com/problems/largest-plus-sign/)
- 🟡 [790. Domino and Tromino Tiling](https://leetcode.com/problems/domino-and-tromino-tiling/)
- 🟡 [799. Champagne Tower](https://leetcode.com/problems/champagne-tower/)
- 🔴 [801. Minimum Swaps To Make Sequences Increasing](https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/)
- 🟡 [813. Largest Sum of Averages](https://leetcode.com/problems/largest-sum-of-averages/)
- 🟡 [823. Binary Trees With Factors](https://leetcode.com/problems/binary-trees-with-factors/)
- 🟡 [845. Longest Mountain in Array](https://leetcode.com/problems/longest-mountain-in-array/)
- 🔴 [871. Minimum Number of Refueling Stops](https://leetcode.com/problems/minimum-number-of-refueling-stops/)
- 🟡 [873. Length of Longest Fibonacci Subsequence](https://leetcode.com/problems/length-of-longest-fibonacci-subsequence/)
- 🔴 [887. Super Egg Drop](https://leetcode.com/problems/super-egg-drop/)
- 🟡 [898. Bitwise ORs of Subarrays](https://leetcode.com/problems/bitwise-ors-of-subarrays/)
- 🟡 [935. Knight Dialer](https://leetcode.com/problems/knight-dialer/)
- 🔴 [964. Least Operators to Express Number](https://leetcode.com/problems/least-operators-to-express-number/)
- 🟡 [983. Minimum Cost For Tickets](https://leetcode.com/problems/minimum-cost-for-tickets/)
- 🟡 [1014. Best Sightseeing Pair](https://leetcode.com/problems/best-sightseeing-pair/)
- 🟡 [1024. Video Stitching](https://leetcode.com/problems/video-stitching/)
- 🟡 [1027. Longest Arithmetic Subsequence](https://leetcode.com/problems/longest-arithmetic-subsequence/)
- 🟡 [1039. Minimum Score Triangulation of Polygon](https://leetcode.com/problems/minimum-score-triangulation-of-polygon/)
- 🟡 [1043. Partition Array for Maximum Sum](https://leetcode.com/problems/partition-array-for-maximum-sum/)
- 🟡 [1105. Filling Bookcase Shelves](https://leetcode.com/problems/filling-bookcase-shelves/)
- 🟢 [1137. N-th Tribonacci Number](https://leetcode.com/problems/n-th-tribonacci-number/)
- 🟡 [1182. Shortest Distance to Target Color](https://leetcode.com/problems/shortest-distance-to-target-color/) 🔒
- 🟡 [1186. Maximum Subarray Sum with One Deletion](https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/)
- 🟡 [1191. K-Concatenation Maximum Sum](https://leetcode.com/problems/k-concatenation-maximum-sum/)
- 🟡 [1218. Longest Arithmetic Subsequence of Given Difference](https://leetcode.com/problems/longest-arithmetic-subsequence-of-given-difference/)
- 🔴 [1220. Count Vowels Permutation](https://leetcode.com/problems/count-vowels-permutation/)
- 🔴 [1223. Dice Roll Simulation](https://leetcode.com/problems/dice-roll-simulation/)
- 🔴 [1235. Maximum Profit in Job Scheduling](https://leetcode.com/problems/maximum-profit-in-job-scheduling/)
- 🔴 [1246. Palindrome Removal](https://leetcode.com/problems/palindrome-removal/) 🔒
- 🔴 [1259. Handshakes That Don't Cross](https://leetcode.com/problems/handshakes-that-dont-cross/) 🔒
- 🟡 [1262. Greatest Sum Divisible by Three](https://leetcode.com/problems/greatest-sum-divisible-by-three/)
- 🔴 [1269. Number of Ways to Stay in the Same Place After Some Steps](https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/)
- 🔴 [1326. Minimum Number of Taps to Open to Water a Garden](https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/)
- 🔴 [1335. Minimum Difficulty of a Job Schedule](https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/)
- 🔴 [1340. Jump Game V](https://leetcode.com/problems/jump-game-v/)
- 🔴 [1363. Largest Multiple of Three](https://leetcode.com/problems/largest-multiple-of-three/)
- 🟡 [1387. Sort Integers by The Power Value](https://leetcode.com/problems/sort-integers-by-the-power-value/)
- 🔴 [1388. Pizza With 3n Slices](https://leetcode.com/problems/pizza-with-3n-slices/)
- 🔴 [1402. Reducing Dishes](https://leetcode.com/problems/reducing-dishes/)
- 🔴 [1420. Build Array Where You Can Find The Maximum Exactly K Comparisons](https://leetcode.com/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/)
- 🔴 [1473. Paint House III](https://leetcode.com/problems/paint-house-iii/)
- 🔴 [1478. Allocate Mailboxes](https://leetcode.com/problems/allocate-mailboxes/)
- 🟡 [1524. Number of Sub-arrays With Odd Sum](https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/)
- 🔴 [1537. Get the Maximum Score](https://leetcode.com/problems/get-the-maximum-score/)
- 🔴 [1553. Minimum Number of Days to Eat N Oranges](https://leetcode.com/problems/minimum-number-of-days-to-eat-n-oranges/)
- 🟡 [1567. Maximum Length of Subarray With Positive Product](https://leetcode.com/problems/maximum-length-of-subarray-with-positive-product/)
- 🔴 [1575. Count All Possible Routes](https://leetcode.com/problems/count-all-possible-routes/)
- 🔴 [1611. Minimum One Bit Operations to Make Integers Zero](https://leetcode.com/problems/minimum-one-bit-operations-to-make-integers-zero/)
- 🔴 [1671. Minimum Number of Removals to Make Mountain Array](https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/)
- 🔴 [1691. Maximum Height by Stacking Cuboids ](https://leetcode.com/problems/maximum-height-by-stacking-cuboids/)
- 🔴 [1692. Count Ways to Distribute Candies](https://leetcode.com/problems/count-ways-to-distribute-candies/) 🔒
- 🟡 [1746. Maximum Subarray Sum After One Operation](https://leetcode.com/problems/maximum-subarray-sum-after-one-operation/) 🔒
- 🟡 [1749. Maximum Absolute Sum of Any Subarray](https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/)
- 🔴 [1751. Maximum Number of Events That Can Be Attended II](https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii/)
- 🔴 [1770. Maximum Score from Performing Multiplication Operations](https://leetcode.com/problems/maximum-score-from-performing-multiplication-operations/)
- 🔴 [1787. Make the XOR of All Segments Equal to Zero](https://leetcode.com/problems/make-the-xor-of-all-segments-equal-to-zero/)
- 🟡 [1824. Minimum Sideway Jumps](https://leetcode.com/problems/minimum-sideway-jumps/)
- 🔴 [1883. Minimum Skips to Arrive at Meeting On Time](https://leetcode.com/problems/minimum-skips-to-arrive-at-meeting-on-time/)
- 🟡 [1884. Egg Drop With 2 Eggs and N Floors](https://leetcode.com/problems/egg-drop-with-2-eggs-and-n-floors/)
- 🔴 [1900. The Earliest and Latest Rounds Where Players Compete](https://leetcode.com/problems/the-earliest-and-latest-rounds-where-players-compete/)
- 🟡 [1911. Maximum Alternating Subsequence Sum](https://leetcode.com/problems/maximum-alternating-subsequence-sum/)
- 🔴 [1955. Count Number of Special Subsequences](https://leetcode.com/problems/count-number-of-special-subsequences/)
- 🟡 [1959. Minimum Total Space Wasted With K Resizing Operations](https://leetcode.com/problems/minimum-total-space-wasted-with-k-resizing-operations/)
- 🟡 [1997. First Day Where You Have Been in All the Rooms](https://leetcode.com/problems/first-day-where-you-have-been-in-all-the-rooms/)
- 🟡 [2008. Maximum Earnings From Taxi](https://leetcode.com/problems/maximum-earnings-from-taxi/)
- 🟡 [2036. Maximum Alternating Subarray Sum](https://leetcode.com/problems/maximum-alternating-subarray-sum/) 🔒
- 🟡 [2100. Find Good Days to Rob the Bank](https://leetcode.com/problems/find-good-days-to-rob-the-bank/)
- 🟡 [2140. Solving Questions With Brainpower](https://leetcode.com/problems/solving-questions-with-brainpower/)
- 🔴 [2143. Choose Numbers From Two Arrays in Range](https://leetcode.com/problems/choose-numbers-from-two-arrays-in-range/) 🔒
- 🔴 [2163. Minimum Difference in Sums After Removal of Elements](https://leetcode.com/problems/minimum-difference-in-sums-after-removal-of-elements/)
- 🔴 [2188. Minimum Time to Finish the Race](https://leetcode.com/problems/minimum-time-to-finish-the-race/)
- 🟡 [2189. Number of Ways to Build House of Cards](https://leetcode.com/problems/number-of-ways-to-build-house-of-cards/) 🔒
- 🔴 [2263. Make Array Non-decreasing or Non-increasing](https://leetcode.com/problems/make-array-non-decreasing-or-non-increasing/) 🔒
- 🔴 [2312. Selling Pieces of Wood](https://leetcode.com/problems/selling-pieces-of-wood/)
- 🔴 [2318. Number of Distinct Roll Sequences](https://leetcode.com/problems/number-of-distinct-roll-sequences/)
- 🟡 [2320. Count Number of Ways to Place Houses](https://leetcode.com/problems/count-number-of-ways-to-place-houses/)
- 🔴 [2321. Maximum Score Of Spliced Array](https://leetcode.com/problems/maximum-score-of-spliced-array/)
- 🟡 [2327. Number of People Aware of a Secret](https://leetcode.com/problems/number-of-people-aware-of-a-secret/)
- 🔴 [2361. Minimum Costs Using the Train Line](https://leetcode.com/problems/minimum-costs-using-the-train-line/) 🔒
- 🟡 [2369. Check if There is a Valid Partition For The Array](https://leetcode.com/problems/check-if-there-is-a-valid-partition-for-the-array/)
- 🟡 [2393. Count Strictly Increasing Subarrays](https://leetcode.com/problems/count-strictly-increasing-subarrays/) 🔒
- 🟡 [2420. Find All Good Indices](https://leetcode.com/problems/find-all-good-indices/)
- 🟡 [2431. Maximize Total Tastiness of Purchased Fruits](https://leetcode.com/problems/maximize-total-tastiness-of-purchased-fruits/) 🔒
- 🟡 [2436. Minimum Split Into Subarrays With GCD Greater Than One](https://leetcode.com/problems/minimum-split-into-subarrays-with-gcd-greater-than-one/) 🔒
- 🟡 [2439. Minimize Maximum of Array](https://leetcode.com/problems/minimize-maximum-of-array/)
- 🔴 [2463. Minimum Total Distance Traveled](https://leetcode.com/problems/minimum-total-distance-traveled/)
- 🟡 [2464. Minimum Subarrays in a Valid Split](https://leetcode.com/problems/minimum-subarrays-in-a-valid-split/) 🔒
- 🟡 [2466. Count Ways To Build Good Strings](https://leetcode.com/problems/count-ways-to-build-good-strings/)
- 🟡 [2495. Number of Subarrays Having Even Product](https://leetcode.com/problems/number-of-subarrays-having-even-product/) 🔒
- 🟡 [2501. Longest Square Streak in an Array](https://leetcode.com/problems/longest-square-streak-in-an-array/)
- 🔴 [2518. Number of Great Partitions](https://leetcode.com/problems/number-of-great-partitions/)
- 🟡 [2533. Number of Good Binary Strings](https://leetcode.com/problems/number-of-good-binary-strings/) 🔒
- 🔴 [2547. Minimum Cost to Split an Array](https://leetcode.com/problems/minimum-cost-to-split-an-array/)
- 🟡 [2560. House Robber IV](https://leetcode.com/problems/house-robber-iv/)
- 🟡 [2571. Minimum Operations to Reduce an Integer to 0](https://leetcode.com/problems/minimum-operations-to-reduce-an-integer-to-0/)
- 🟡 [2616. Minimize the Maximum Difference of Pairs](https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/)
- 🔴 [2681. Power of Heroes](https://leetcode.com/problems/power-of-heroes/)
- 🔴 [2742. Painting the Walls](https://leetcode.com/problems/painting-the-walls/)
- 🟡 [2745. Construct the Longest New String](https://leetcode.com/problems/construct-the-longest-new-string/)
- 🟡 [2750. Ways to Split Array Into Good Subarrays](https://leetcode.com/problems/ways-to-split-array-into-good-subarrays/)
- 🟡 [2770. Maximum Number of Jumps to Reach the Last Index](https://leetcode.com/problems/maximum-number-of-jumps-to-reach-the-last-index/)
- 🟡 [2771. Longest Non-decreasing Subarray From Two Arrays](https://leetcode.com/problems/longest-non-decreasing-subarray-from-two-arrays/)
- 🟡 [2786. Visit Array Positions to Maximize Score](https://leetcode.com/problems/visit-array-positions-to-maximize-score/)
- 🟡 [2787. Ways to Express an Integer as Sum of Powers](https://leetcode.com/problems/ways-to-express-an-integer-as-sum-of-powers/)
- 🔴 [2809. Minimum Time to Make Array Sum At Most x](https://leetcode.com/problems/minimum-time-to-make-array-sum-at-most-x/)
- 🟡 [2811. Check if it is Possible to Split Array](https://leetcode.com/problems/check-if-it-is-possible-to-split-array/)
- 🟡 [2826. Sorting Three Groups](https://leetcode.com/problems/sorting-three-groups/)
- 🔴 [2827. Number of Beautiful Integers in the Range](https://leetcode.com/problems/number-of-beautiful-integers-in-the-range/)
- 🟡 [2830. Maximize the Profit as the Salesman](https://leetcode.com/problems/maximize-the-profit-as-the-salesman/)
- 🔴 [2836. Maximize Value of Function in a Ball Passing Game](https://leetcode.com/problems/maximize-value-of-function-in-a-ball-passing-game/)
- 🟡 [2892. Minimizing Array After Replacing Pairs With Their Product](https://leetcode.com/problems/minimizing-array-after-replacing-pairs-with-their-product/) 🔒
- 🟡 [2919. Minimum Increment Operations to Make Array Beautiful](https://leetcode.com/problems/minimum-increment-operations-to-make-array-beautiful/)
- 🟡 [2979. Most Expensive Item That Can Not Be Bought](https://leetcode.com/problems/most-expensive-item-that-can-not-be-bought/) 🔒
- 🟡 [3007. Maximum Number That Sum of the Prices Is Less Than or Equal to K](https://leetcode.com/problems/maximum-number-that-sum-of-the-prices-is-less-than-or-equal-to-k/)
- 🔴 [3018. Maximum Number of Removal Queries That Can Be Processed I](https://leetcode.com/problems/maximum-number-of-removal-queries-that-can-be-processed-i/) 🔒
- 🟡 [3040. Maximum Number of Operations With the Same Score II](https://leetcode.com/problems/maximum-number-of-operations-with-the-same-score-ii/)
- 🔴 [3041. Maximize Consecutive Elements in an Array After Modification](https://leetcode.com/problems/maximize-consecutive-elements-in-an-array-after-modification/)
- 🔴 [3077. Maximum Strength of K Disjoint Subarrays](https://leetcode.com/problems/maximum-strength-of-k-disjoint-subarrays/)
- 🔴 [3098. Find the Sum of Subsequence Powers](https://leetcode.com/problems/find-the-sum-of-subsequence-powers/)
- 🟡 [3129. Find All Possible Stable Binary Arrays I](https://leetcode.com/problems/find-all-possible-stable-binary-arrays-i/)
- 🔴 [3130. Find All Possible Stable Binary Arrays II](https://leetcode.com/problems/find-all-possible-stable-binary-arrays-ii/)
- 🟡 [3147. Taking Maximum Energy From the Mystic Dungeon](https://leetcode.com/problems/taking-maximum-energy-from-the-mystic-dungeon/)
- 🟡 [3176. Find the Maximum Length of a Good Subsequence I](https://leetcode.com/problems/find-the-maximum-length-of-a-good-subsequence-i/)
- 🔴 [3177. Find the Maximum Length of a Good Subsequence II](https://leetcode.com/problems/find-the-maximum-length-of-a-good-subsequence-ii/)
- 🟡 [3180. Maximum Total Reward Using Operations I](https://leetcode.com/problems/maximum-total-reward-using-operations-i/)
- 🔴 [3181. Maximum Total Reward Using Operations II](https://leetcode.com/problems/maximum-total-reward-using-operations-ii/)
- 🟡 [3186. Maximum Total Damage With Spell Casting](https://leetcode.com/problems/maximum-total-damage-with-spell-casting/)
- 🟡 [3192. Minimum Operations to Make Binary Array Elements Equal to One II](https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-ii/)
- 🔴 [3193. Count the Number of Inversions](https://leetcode.com/problems/count-the-number-of-inversions/)
- 🟡 [3196. Maximize Total Cost of Alternating Subarrays](https://leetcode.com/problems/maximize-total-cost-of-alternating-subarrays/)
- 🟡 [3201. Find the Maximum Length of Valid Subsequence I](https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-i/)
- 🟡 [3202. Find the Maximum Length of Valid Subsequence II](https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-ii/)
- 🟡 [3218. Minimum Cost for Cutting Cake I](https://leetcode.com/problems/minimum-cost-for-cutting-cake-i/)
- 🟡 [3259. Maximum Energy Boost From Two Drinks](https://leetcode.com/problems/maximum-energy-boost-from-two-drinks/)
- 🔴 [3269. Constructing Two Increasing Arrays](https://leetcode.com/problems/constructing-two-increasing-arrays/) 🔒
- 🔴 [3277. Maximum XOR Score Subarray Queries](https://leetcode.com/problems/maximum-xor-score-subarray-queries/)
- 🟡 [3284. Sum of Consecutive Subarrays](https://leetcode.com/problems/sum-of-consecutive-subarrays/) 🔒
- 🔴 [3287. Find the Maximum Sequence Value of Array](https://leetcode.com/problems/find-the-maximum-sequence-value-of-array/)
- 🟡 [3290. Maximum Multiplication Score](https://leetcode.com/problems/maximum-multiplication-score/)
- 🔴 [3299. Sum of Consecutive Subsequences](https://leetcode.com/problems/sum-of-consecutive-subsequences/) 🔒
- 🔴 [3336. Find the Number of Subsequences With Equal GCD](https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd/)
- 🟡 [3339. Find the Number of K-Even Arrays](https://leetcode.com/problems/find-the-number-of-k-even-arrays/) 🔒
- 🔴 [3351. Sum of Good Subsequences](https://leetcode.com/problems/sum-of-good-subsequences/)
- 🟡 [3366. Minimum Array Sum](https://leetcode.com/problems/minimum-array-sum/)
- 🟡 [3388. Count Beautiful Splits in an Array](https://leetcode.com/problems/count-beautiful-splits-in-an-array/)
- 🟡 [3409. Longest Subsequence With Decreasing Adjacent Difference](https://leetcode.com/problems/longest-subsequence-with-decreasing-adjacent-difference/)
- 🟡 [3429. Paint House IV](https://leetcode.com/problems/paint-house-iv/)
- 🟡 [3434. Maximum Frequency After Subarray Operation](https://leetcode.com/problems/maximum-frequency-after-subarray-operation/)
- 🟡 [3469. Find Minimum Cost to Remove Array Elements](https://leetcode.com/problems/find-minimum-cost-to-remove-array-elements/)
- 🟡 [3473. Sum of K Subarrays With Length at Least M](https://leetcode.com/problems/sum-of-k-subarrays-with-length-at-least-m/)
- 🟡 [3489. Zero Array Transformation IV](https://leetcode.com/problems/zero-array-transformation-iv/)
- 🔴 [3490. Count Beautiful Numbers](https://leetcode.com/problems/count-beautiful-numbers/)
- 🔴 [3509. Maximum Product of Subsequences With an Alternating Sum Equal to K](https://leetcode.com/problems/maximum-product-of-subsequences-with-an-alternating-sum-equal-to-k/)
- 🟡 [3524. Find X Value of Array I](https://leetcode.com/problems/find-x-value-of-array-i/)
- 🔴 [3538. Merge Operations for Minimum Travel Time](https://leetcode.com/problems/merge-operations-for-minimum-travel-time/)
- 🟡 [3599. Partition Array to Minimize XOR](https://leetcode.com/problems/partition-array-to-minimize-xor/)
- 🟡 [3610. Minimum Number of Primes to Sum to Target](https://leetcode.com/problems/minimum-number-of-primes-to-sum-to-target/) 🔒
- 🔴 [3640. Trionic Array II](https://leetcode.com/problems/trionic-array-ii/)
- 🟡 [3647. Maximum Weight in Two Bags](https://leetcode.com/problems/maximum-weight-in-two-bags/) 🔒
- 🟡 [3654. Minimum Sum After Divisible Sum Deletions](https://leetcode.com/problems/minimum-sum-after-divisible-sum-deletions/)
- 🟡 [3660. Jump Game IX](https://leetcode.com/problems/jump-game-ix/)
- 🔴 [3661. Maximum Walls Destroyed by Robots](https://leetcode.com/problems/maximum-walls-destroyed-by-robots/)
- 🟡 [3670. Maximum Product of Two Integers With No Common Bits](https://leetcode.com/problems/maximum-product-of-two-integers-with-no-common-bits/)
- 🟡 [3685. Subsequence Sum After Capping Elements](https://leetcode.com/problems/subsequence-sum-after-capping-elements/)
- 🔴 [3686. Number of Stable Subsequences](https://leetcode.com/problems/number-of-stable-subsequences/)
- 🟡 [3693. Climbing Stairs II](https://leetcode.com/problems/climbing-stairs-ii/)
- 🔴 [3699. Number of ZigZag Arrays I](https://leetcode.com/problems/number-of-zigzag-arrays-i/)
- 🔴 [3700. Number of ZigZag Arrays II](https://leetcode.com/problems/number-of-zigzag-arrays-ii/)
- 🔴 [3704. Count No-Zero Pairs That Sum to N](https://leetcode.com/problems/count-no-zero-pairs-that-sum-to-n/)
- 🟡 [3717. Minimum Operations to Make the Array Beautiful](https://leetcode.com/problems/minimum-operations-to-make-the-array-beautiful/) 🔒
- 🟡 [3738. Longest Non-Decreasing Subarray After Replacing at Most One Element](https://leetcode.com/problems/longest-non-decreasing-subarray-after-replacing-at-most-one-element/)
- 🔴 [3743. Maximize Cyclic Partition Score](https://leetcode.com/problems/maximize-cyclic-partition-score/)
- 🟡 [3751. Total Waviness of Numbers in Range I](https://leetcode.com/problems/total-waviness-of-numbers-in-range-i/)
- 🔴 [3753. Total Waviness of Numbers in Range II](https://leetcode.com/problems/total-waviness-of-numbers-in-range-ii/)
- 🔴 [3791. Number of Balanced Integers in a Range](https://leetcode.com/problems/number-of-balanced-integers-in-a-range/)
- 🔴 [3801. Minimum Cost to Merge Sorted Lists](https://leetcode.com/problems/minimum-cost-to-merge-sorted-lists/)
- 🟡 [3811. Number of Alternating XOR Partitions](https://leetcode.com/problems/number-of-alternating-xor-partitions/)
- 🔴 [3830. Longest Alternating Subarray After Removing At Most One Element](https://leetcode.com/problems/longest-alternating-subarray-after-removing-at-most-one-element/)
- 🔴 [3836. Maximum Score Using Exactly K Pairs](https://leetcode.com/problems/maximum-score-using-exactly-k-pairs/)
- 🟡 [3840. House Robber V](https://leetcode.com/problems/house-robber-v/)
- 🔴 [3850. Count Sequences to K](https://leetcode.com/problems/count-sequences-to-k/)
- 🟡 [3857. Minimum Cost to Split into Ones](https://leetcode.com/problems/minimum-cost-to-split-into-ones/)
- 🔴 [3869. Count Fancy Numbers in a Range](https://leetcode.com/problems/count-fancy-numbers-in-a-range/)
- 🟡 [3877. Minimum Removals to Achieve Target XOR](https://leetcode.com/problems/minimum-removals-to-achieve-target-xor/)
- 🔴 [3883. Count Non Decreasing Arrays With Given Digit Sums](https://leetcode.com/problems/count-non-decreasing-arrays-with-given-digit-sums/)
- 🟡 [3891. Minimum Increase to Maximize Special Indices](https://leetcode.com/problems/minimum-increase-to-maximize-special-indices/)
- 🔴 [3892. Minimum Operations to Achieve At Least K Peaks](https://leetcode.com/problems/minimum-operations-to-achieve-at-least-k-peaks/)
- 🔴 [3906. Count Good Integers on a Grid Path](https://leetcode.com/problems/count-good-integers-on-a-grid-path/)
- 🔴 [3916. Number of ZigZag Arrays III](https://leetcode.com/problems/number-of-zigzag-arrays-iii/) 🔒
- 🟡 [3946. Maximum Number of Items From Sale I](https://leetcode.com/problems/maximum-number-of-items-from-sale-i/)
- 🟢 [3954. Sum of Compatible Numbers in Range I](https://leetcode.com/problems/sum-of-compatible-numbers-in-range-i/)
- 🟡 [3976. Maximum Subarray Sum After Multiplier](https://leetcode.com/problems/maximum-subarray-sum-after-multiplier/)
- 🟡 [3984. Divisible Game](https://leetcode.com/problems/divisible-game/)
- 🔴 [4009. Minimum Possible Maximum Waiting Time](https://leetcode.com/problems/minimum-possible-maximum-waiting-time/)
- 🔴 [4023. Elevator Requests II](https://leetcode.com/problems/elevator-requests-ii/)
- 🟡 [4040. Minimum Operations to Form Subset Sum I](https://leetcode.com/problems/minimum-operations-to-form-subset-sum-i/)
- 🔴 [4041. Minimum Operations to Form Subset Sum II](https://leetcode.com/problems/minimum-operations-to-form-subset-sum-ii/)
- 🔴 [4047. Minimum Operations to Make XOR of All Elements Zero](https://leetcode.com/problems/minimum-operations-to-make-xor-of-all-elements-zero/) 🔒
- 🟡 [4050. Minimum Days to Score Exactly N Points](https://leetcode.com/problems/minimum-days-to-score-exactly-n-points/)
- 🟡 [4058. Maximum Pulse Value After One Subarray Rotation](https://leetcode.com/problems/maximum-pulse-value-after-one-subarray-rotation/)
- 🔴 [4068. Maximize Meeting Earnings with Idle Gaps](https://leetcode.com/problems/maximize-meeting-earnings-with-idle-gaps/)
- 🟡 [4110. Find the Maximum Length of Valid Subsequence III](https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-iii/) 🔒

</details>

<details><summary><b>String DP (LCS / Edit Distance / Palindromes)</b> (106)</summary>

- 🟡 [5. Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/)
- 🔴 [10. Regular Expression Matching](https://leetcode.com/problems/regular-expression-matching/)
- 🔴 [32. Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses/)
- 🔴 [44. Wildcard Matching](https://leetcode.com/problems/wildcard-matching/)
- 🟡 [72. Edit Distance](https://leetcode.com/problems/edit-distance/)
- 🔴 [87. Scramble String](https://leetcode.com/problems/scramble-string/)
- 🟡 [97. Interleaving String](https://leetcode.com/problems/interleaving-string/)
- 🔴 [115. Distinct Subsequences](https://leetcode.com/problems/distinct-subsequences/)
- 🔴 [132. Palindrome Partitioning II](https://leetcode.com/problems/palindrome-partitioning-ii/)
- 🟡 [241. Different Ways to Add Parentheses](https://leetcode.com/problems/different-ways-to-add-parentheses/)
- 🟢 [392. Is Subsequence](https://leetcode.com/problems/is-subsequence/)
- 🟡 [418. Sentence Screen Fitting](https://leetcode.com/problems/sentence-screen-fitting/) 🔒
- 🔴 [466. Count The Repetitions](https://leetcode.com/problems/count-the-repetitions/)
- 🟡 [467. Unique Substrings in Wraparound String](https://leetcode.com/problems/unique-substrings-in-wraparound-string/)
- 🔴 [471. Encode String with Shortest Length](https://leetcode.com/problems/encode-string-with-shortest-length/) 🔒
- 🔴 [472. Concatenated Words](https://leetcode.com/problems/concatenated-words/)
- 🟡 [516. Longest Palindromic Subsequence](https://leetcode.com/problems/longest-palindromic-subsequence/)
- 🟡 [583. Delete Operation for Two Strings](https://leetcode.com/problems/delete-operation-for-two-strings/)
- 🔴 [639. Decode Ways II](https://leetcode.com/problems/decode-ways-ii/)
- 🟡 [647. Palindromic Substrings](https://leetcode.com/problems/palindromic-substrings/)
- 🟡 [712. Minimum ASCII Delete Sum for Two Strings](https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/)
- 🔴 [730. Count Different Palindromic Subsequences](https://leetcode.com/problems/count-different-palindromic-subsequences/)
- 🟡 [792. Number of Matching Subsequences](https://leetcode.com/problems/number-of-matching-subsequences/)
- 🔴 [828. Count Unique Characters of All Substrings of a Given String](https://leetcode.com/problems/count-unique-characters-of-all-substrings-of-a-given-string/)
- 🟡 [838. Push Dominoes](https://leetcode.com/problems/push-dominoes/)
- 🔴 [903. Valid Permutations for DI Sequence](https://leetcode.com/problems/valid-permutations-for-di-sequence/)
- 🟡 [926. Flip String to Monotone Increasing](https://leetcode.com/problems/flip-string-to-monotone-increasing/)
- 🔴 [940. Distinct Subsequences II](https://leetcode.com/problems/distinct-subsequences-ii/)
- 🔴 [960. Delete Columns to Make Sorted III](https://leetcode.com/problems/delete-columns-to-make-sorted-iii/)
- 🟡 [1035. Uncrossed Lines](https://leetcode.com/problems/uncrossed-lines/)
- 🟡 [1048. Longest String Chain](https://leetcode.com/problems/longest-string-chain/)
- 🔴 [1092. Shortest Common Supersequence ](https://leetcode.com/problems/shortest-common-supersequence/)
- 🟡 [1143. Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/)
- 🔴 [1216. Valid Palindrome III](https://leetcode.com/problems/valid-palindrome-iii/) 🔒
- 🔴 [1278. Palindrome Partitioning III](https://leetcode.com/problems/palindrome-partitioning-iii/)
- 🔴 [1312. Minimum Insertion Steps to Make a String Palindrome](https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/)
- 🔴 [1320. Minimum Distance to Type a Word Using Two Fingers](https://leetcode.com/problems/minimum-distance-to-type-a-word-using-two-fingers/)
- 🔴 [1416. Restore The Array](https://leetcode.com/problems/restore-the-array/)
- 🔴 [1458. Max Dot Product of Two Subsequences](https://leetcode.com/problems/max-dot-product-of-two-subsequences/)
- 🟡 [1525. Number of Good Ways to Split a String](https://leetcode.com/problems/number-of-good-ways-to-split-a-string/)
- 🔴 [1531. String Compression II](https://leetcode.com/problems/string-compression-ii/)
- 🟡 [1578. Minimum Time to Make Rope Colorful](https://leetcode.com/problems/minimum-time-to-make-rope-colorful/)
- 🟡 [1638. Count Substrings That Differ by One Character](https://leetcode.com/problems/count-substrings-that-differ-by-one-character/)
- 🔴 [1639. Number of Ways to Form a Target String Given a Dictionary](https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/)
- 🟡 [1653. Minimum Deletions to Make String Balanced](https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/)
- 🟡 [1682. Longest Palindromic Subsequence II](https://leetcode.com/problems/longest-palindromic-subsequence-ii/) 🔒
- 🔴 [1745. Palindrome Partitioning IV](https://leetcode.com/problems/palindrome-partitioning-iv/)
- 🔴 [1771. Maximize Palindrome Length From Subsequences](https://leetcode.com/problems/maximize-palindrome-length-from-subsequences/)
- 🔴 [1896. Minimum Cost to Change the Final Value of Expression](https://leetcode.com/problems/minimum-cost-to-change-the-final-value-of-expression/)
- 🔴 [1977. Number of Ways to Separate Numbers](https://leetcode.com/problems/number-of-ways-to-separate-numbers/)
- 🔴 [1987. Number of Unique Good Subsequences](https://leetcode.com/problems/number-of-unique-good-subsequences/)
- 🔴 [2019. The Score of Students Solving Math Expression](https://leetcode.com/problems/the-score-of-students-solving-math-expression/)
- 🟡 [2052. Minimum Cost to Separate Sentence Into Rows](https://leetcode.com/problems/minimum-cost-to-separate-sentence-into-rows/) 🔒
- 🔴 [2060. Check if an Original String Exists Given Two Encoded Strings](https://leetcode.com/problems/check-if-an-original-string-exists-given-two-encoded-strings/)
- 🟡 [2063. Vowels of All Substrings](https://leetcode.com/problems/vowels-of-all-substrings/)
- 🟡 [2086. Minimum Number of Food Buckets to Feed the Hamsters](https://leetcode.com/problems/minimum-number-of-food-buckets-to-feed-the-hamsters/)
- 🔴 [2147. Number of Ways to Divide a Long Corridor](https://leetcode.com/problems/number-of-ways-to-divide-a-long-corridor/)
- 🔴 [2167. Minimum Time to Remove All Cars Containing Illegal Goods](https://leetcode.com/problems/minimum-time-to-remove-all-cars-containing-illegal-goods/)
- 🔴 [2209. Minimum White Tiles After Covering With Carpets](https://leetcode.com/problems/minimum-white-tiles-after-covering-with-carpets/)
- 🟡 [2222. Number of Ways to Select Buildings](https://leetcode.com/problems/number-of-ways-to-select-buildings/)
- 🔴 [2262. Total Appeal of A String](https://leetcode.com/problems/total-appeal-of-a-string/)
- 🟡 [2266. Count Number of Texts](https://leetcode.com/problems/count-number-of-texts/)
- 🔴 [2272. Substring With Largest Variance](https://leetcode.com/problems/substring-with-largest-variance/)
- 🟡 [2311. Longest Binary Subsequence Less Than or Equal to K](https://leetcode.com/problems/longest-binary-subsequence-less-than-or-equal-to-k/)
- 🟡 [2370. Longest Ideal Subsequence](https://leetcode.com/problems/longest-ideal-subsequence/)
- 🟡 [2380. Time Needed to Rearrange a Binary String](https://leetcode.com/problems/time-needed-to-rearrange-a-binary-string/)
- 🔴 [2478. Number of Beautiful Partitions](https://leetcode.com/problems/number-of-beautiful-partitions/)
- 🔴 [2484. Count Palindromic Subsequences](https://leetcode.com/problems/count-palindromic-subsequences/)
- 🟡 [2522. Partition String Into Substrings With Values at Most K](https://leetcode.com/problems/partition-string-into-substrings-with-values-at-most-k/)
- 🟡 [2606. Find the Substring With Maximum Cost](https://leetcode.com/problems/find-the-substring-with-maximum-cost/)
- 🟡 [2645. Minimum Additions to Make Valid String](https://leetcode.com/problems/minimum-additions-to-make-valid-string/)
- 🟡 [2707. Extra Characters in a String](https://leetcode.com/problems/extra-characters-in-a-string/)
- 🟡 [2712. Minimum Cost to Make All Characters Equal](https://leetcode.com/problems/minimum-cost-to-make-all-characters-equal/)
- 🟡 [2746. Decremental String Concatenation](https://leetcode.com/problems/decremental-string-concatenation/)
- 🔴 [2801. Count Stepping Numbers in Range](https://leetcode.com/problems/count-stepping-numbers-in-range/)
- 🟡 [2896. Apply Operations to Make Two Strings Equal](https://leetcode.com/problems/apply-operations-to-make-two-strings-equal/)
- 🟢 [2900. Longest Unequal Adjacent Groups Subsequence I](https://leetcode.com/problems/longest-unequal-adjacent-groups-subsequence-i/)
- 🟡 [2901. Longest Unequal Adjacent Groups Subsequence II](https://leetcode.com/problems/longest-unequal-adjacent-groups-subsequence-ii/)
- 🔴 [2911. Minimum Changes to Make K Semi-palindromes](https://leetcode.com/problems/minimum-changes-to-make-k-semi-palindromes/)
- 🟡 [2957. Remove Adjacent Almost-Equal Characters](https://leetcode.com/problems/remove-adjacent-almost-equal-characters/)
- 🟡 [3144. Minimum Substring Partition of Equal Character Frequency](https://leetcode.com/problems/minimum-substring-partition-of-equal-character-frequency/)
- 🔴 [3260. Find the Largest Palindrome Divisible by K](https://leetcode.com/problems/find-the-largest-palindrome-divisible-by-k/)
- 🟡 [3302. Find the Lexicographically Smallest Valid Sequence](https://leetcode.com/problems/find-the-lexicographically-smallest-valid-sequence/)
- 🟡 [3316. Find Maximum Removals From Source String](https://leetcode.com/problems/find-maximum-removals-from-source-string/)
- 🔴 [3320. Count The Number of Winning Sequences](https://leetcode.com/problems/count-the-number-of-winning-sequences/)
- 🔴 [3333. Find the Original Typed String II](https://leetcode.com/problems/find-the-original-typed-string-ii/)
- 🟡 [3335. Total Characters in String After Transformations I](https://leetcode.com/problems/total-characters-in-string-after-transformations-i/)
- 🔴 [3337. Total Characters in String After Transformations II](https://leetcode.com/problems/total-characters-in-string-after-transformations-ii/)
- 🔴 [3343. Count Number of Balanced Permutations](https://leetcode.com/problems/count-number-of-balanced-permutations/)
- 🔴 [3352. Count K-Reducible Numbers Less Than N](https://leetcode.com/problems/count-k-reducible-numbers-less-than-n/)
- 🔴 [3389. Minimum Operations to Make Character Frequencies Equal](https://leetcode.com/problems/minimum-operations-to-make-character-frequencies-equal/)
- 🔴 [3441. Minimum Cost Good Caption](https://leetcode.com/problems/minimum-cost-good-caption/)
- 🔴 [3448. Count Substrings Divisible By Last Digit](https://leetcode.com/problems/count-substrings-divisible-by-last-digit/)
- 🟡 [3458. Select K Disjoint Special Substrings](https://leetcode.com/problems/select-k-disjoint-special-substrings/)
- 🟡 [3472. Longest Palindromic Subsequence After at Most K Operations](https://leetcode.com/problems/longest-palindromic-subsequence-after-at-most-k-operations/)
- 🟡 [3503. Longest Palindrome After Substring Concatenation I](https://leetcode.com/problems/longest-palindrome-after-substring-concatenation-i/)
- 🔴 [3504. Longest Palindrome After Substring Concatenation II](https://leetcode.com/problems/longest-palindrome-after-substring-concatenation-ii/)
- 🟡 [3557. Find Maximum Number of Non Intersecting Substrings](https://leetcode.com/problems/find-maximum-number-of-non-intersecting-substrings/)
- 🔴 [3563. Lexicographically Smallest String After Adjacent Removals](https://leetcode.com/problems/lexicographically-smallest-string-after-adjacent-removals/)
- 🔴 [3579. Minimum Steps to Convert String with Operations](https://leetcode.com/problems/minimum-steps-to-convert-string-with-operations/)
- 🟡 [3628. Maximum Number of Subsequences After One Inserting](https://leetcode.com/problems/maximum-number-of-subsequences-after-one-inserting/)
- 🟡 [3844. Longest Almost-Palindromic Substring](https://leetcode.com/problems/longest-almost-palindromic-substring/)
- 🟡 [3952. Maximum Total Value of Covered Indices](https://leetcode.com/problems/maximum-total-value-of-covered-indices/)
- 🟡 [3980. Minimum Operations to Transform Binary String](https://leetcode.com/problems/minimum-operations-to-transform-binary-string/)
- 🔴 [3981. Count Distinct Ways to Form Target from Two Strings](https://leetcode.com/problems/count-distinct-ways-to-form-target-from-two-strings/)
- 🔴 [3995. Minimum Cost to Convert String III](https://leetcode.com/problems/minimum-cost-to-convert-string-iii/)

</details>

<details><summary><b>Grid DP</b> (47)</summary>

- 🟡 [62. Unique Paths](https://leetcode.com/problems/unique-paths/)
- 🟡 [63. Unique Paths II](https://leetcode.com/problems/unique-paths-ii/)
- 🟡 [64. Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/)
- 🔴 [174. Dungeon Game](https://leetcode.com/problems/dungeon-game/)
- 🟡 [221. Maximal Square](https://leetcode.com/problems/maximal-square/)
- 🟡 [361. Bomb Enemy](https://leetcode.com/problems/bomb-enemy/) 🔒
- 🟡 [562. Longest Line of Consecutive One in Matrix](https://leetcode.com/problems/longest-line-of-consecutive-one-in-matrix/) 🔒
- 🔴 [568. Maximum Vacation Days](https://leetcode.com/problems/maximum-vacation-days/) 🔒
- 🔴 [741. Cherry Pickup](https://leetcode.com/problems/cherry-pickup/)
- 🟡 [750. Number Of Corner Rectangles](https://leetcode.com/problems/number-of-corner-rectangles/) 🔒
- 🟡 [931. Minimum Falling Path Sum](https://leetcode.com/problems/minimum-falling-path-sum/)
- 🟡 [1139. Largest 1-Bordered Square](https://leetcode.com/problems/largest-1-bordered-square/)
- 🟡 [1162. As Far from Land as Possible](https://leetcode.com/problems/as-far-from-land-as-possible/)
- 🟡 [1277. Count Square Submatrices with All Ones](https://leetcode.com/problems/count-square-submatrices-with-all-ones/)
- 🔴 [1289. Minimum Falling Path Sum II](https://leetcode.com/problems/minimum-falling-path-sum-ii/)
- 🔴 [1301. Number of Paths with Max Score](https://leetcode.com/problems/number-of-paths-with-max-score/)
- 🔴 [1444. Number of Ways of Cutting a Pizza](https://leetcode.com/problems/number-of-ways-of-cutting-a-pizza/)
- 🔴 [1463. Cherry Pickup II](https://leetcode.com/problems/cherry-pickup-ii/)
- 🟡 [1594. Maximum Non Negative Product in a Matrix](https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/)
- 🟡 [1937. Maximum Number of Points with Cost](https://leetcode.com/problems/maximum-number-of-points-with-cost/)
- 🟡 [1981. Minimize the Difference Between Target and Chosen Elements](https://leetcode.com/problems/minimize-the-difference-between-target-and-chosen-elements/)
- 🔴 [2088. Count Fertile Pyramids in a Land](https://leetcode.com/problems/count-fertile-pyramids-in-a-land/)
- 🔴 [2267.  Check if There Is a Valid Parentheses String Path](https://leetcode.com/problems/check-if-there-is-a-valid-parentheses-string-path/)
- 🟡 [2304. Minimum Path Cost in a Grid](https://leetcode.com/problems/minimum-path-cost-in-a-grid/)
- 🔴 [2435. Paths in Matrix Whose Sum Is Divisible by K](https://leetcode.com/problems/paths-in-matrix-whose-sum-is-divisible-by-k/)
- 🟡 [2510. Check if There is a Path With Equal Number of 0's And 1's](https://leetcode.com/problems/check-if-there-is-a-path-with-equal-number-of-0s-and-1s/) 🔒
- 🟡 [2556. Disconnect Path in a Binary Matrix by at Most One Flip](https://leetcode.com/problems/disconnect-path-in-a-binary-matrix-by-at-most-one-flip/)
- 🟡 [2684. Maximum Number of Moves in a Grid](https://leetcode.com/problems/maximum-number-of-moves-in-a-grid/)
- 🔴 [2713. Maximum Strictly Increasing Cells in a Matrix](https://leetcode.com/problems/maximum-strictly-increasing-cells-in-a-matrix/)
- 🟡 [3122. Minimum Number of Operations to Satisfy Conditions](https://leetcode.com/problems/minimum-number-of-operations-to-satisfy-conditions/)
- 🟡 [3148. Maximum Difference Score in a Grid](https://leetcode.com/problems/maximum-difference-score-in-a-grid/)
- 🔴 [3225. Maximum Score From Grid Operations](https://leetcode.com/problems/maximum-score-from-grid-operations/)
- 🔴 [3256. Maximum Value Sum by Placing Three Rooks I](https://leetcode.com/problems/maximum-value-sum-by-placing-three-rooks-i/)
- 🔴 [3257. Maximum Value Sum by Placing Three Rooks II](https://leetcode.com/problems/maximum-value-sum-by-placing-three-rooks-ii/)
- 🟡 [3332. Maximum Points Tourist Can Earn](https://leetcode.com/problems/maximum-points-tourist-can-earn/)
- 🔴 [3363. Find the Maximum Number of Fruits Collected](https://leetcode.com/problems/find-the-maximum-number-of-fruits-collected/)
- 🟡 [3393. Count Paths With the Given XOR Value](https://leetcode.com/problems/count-paths-with-the-given-xor-value/)
- 🟡 [3418. Maximum Amount of Money Robot Can Earn](https://leetcode.com/problems/maximum-amount-of-money-robot-can-earn/)
- 🔴 [3459. Length of Longest V-Shaped Diagonal Segment](https://leetcode.com/problems/length-of-longest-v-shaped-diagonal-segment/)
- 🟡 [3603. Minimum Cost Path with Alternating Directions II](https://leetcode.com/problems/minimum-cost-path-with-alternating-directions-ii/)
- 🔴 [3651. Minimum Cost Path with Teleportations](https://leetcode.com/problems/minimum-cost-path-with-teleportations/)
- 🟡 [3665. Twisted Mirror Path Count](https://leetcode.com/problems/twisted-mirror-path-count/)
- 🟡 [3742. Maximum Path Score in a Grid](https://leetcode.com/problems/maximum-path-score-in-a-grid/)
- 🔴 [3797. Count Routes to Climb a Rectangular Grid](https://leetcode.com/problems/count-routes-to-climb-a-rectangular-grid/)
- 🟡 [3882. Minimum XOR Path in a Grid](https://leetcode.com/problems/minimum-xor-path-in-a-grid/)
- 🟡 [3938. Maximum Path Intersection Sum in a Grid](https://leetcode.com/problems/maximum-path-intersection-sum-in-a-grid/)
- 🔴 [3989. Maximum Consistent Columns in a Grid](https://leetcode.com/problems/maximum-consistent-columns-in-a-grid/)

</details>

<details><summary><b>Tree DP</b> (40)</summary>

- 🟡 [96. Unique Binary Search Trees](https://leetcode.com/problems/unique-binary-search-trees/)
- 🟡 [333. Largest BST Subtree](https://leetcode.com/problems/largest-bst-subtree/) 🔒
- 🟡 [337. House Robber III](https://leetcode.com/problems/house-robber-iii/)
- 🔴 [834. Sum of Distances in Tree](https://leetcode.com/problems/sum-of-distances-in-tree/)
- 🟡 [894. All Possible Full Binary Trees](https://leetcode.com/problems/all-possible-full-binary-trees/)
- 🔴 [968. Binary Tree Cameras](https://leetcode.com/problems/binary-tree-cameras/)
- 🟡 [1372. Longest ZigZag Path in a Binary Tree](https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree/)
- 🔴 [1373. Maximum Sum BST in Binary Tree](https://leetcode.com/problems/maximum-sum-bst-in-binary-tree/)
- 🔴 [1483. Kth Ancestor of a Tree Node](https://leetcode.com/problems/kth-ancestor-of-a-tree-node/)
- 🔴 [2003. Smallest Missing Genetic Value in Each Subtree](https://leetcode.com/problems/smallest-missing-genetic-value-in-each-subtree/)
- 🔴 [2005. Subtree Removal Game with Fibonacci Tree](https://leetcode.com/problems/subtree-removal-game-with-fibonacci-tree/) 🔒
- 🔴 [2313. Minimum Flips in Binary Tree to Get Result](https://leetcode.com/problems/minimum-flips-in-binary-tree-to-get-result/) 🔒
- 🟡 [2378. Choose Edges to Maximize Score in a Tree](https://leetcode.com/problems/choose-edges-to-maximize-score-in-a-tree/) 🔒
- 🔴 [2538. Difference Between Maximum and Minimum Price Sum](https://leetcode.com/problems/difference-between-maximum-and-minimum-price-sum/)
- 🔴 [2581. Count Number of Possible Root Nodes](https://leetcode.com/problems/count-number-of-possible-root-nodes/)
- 🔴 [2646. Minimize the Total Price of the Trips](https://leetcode.com/problems/minimize-the-total-price-of-the-trips/)
- 🟡 [2673. Make Costs of Paths Equal in a Binary Tree](https://leetcode.com/problems/make-costs-of-paths-equal-in-a-binary-tree/)
- 🔴 [2846. Minimum Edge Weight Equilibrium Queries in a Tree](https://leetcode.com/problems/minimum-edge-weight-equilibrium-queries-in-a-tree/)
- 🔴 [2867. Count Valid Paths in a Tree](https://leetcode.com/problems/count-valid-paths-in-a-tree/)
- 🔴 [2920. Maximum Points After Collecting Coins From All Nodes](https://leetcode.com/problems/maximum-points-after-collecting-coins-from-all-nodes/)
- 🟡 [2925. Maximum Score After Applying Operations on a Tree](https://leetcode.com/problems/maximum-score-after-applying-operations-on-a-tree/)
- 🔴 [2973. Find Number of Coins to Place in Tree Nodes](https://leetcode.com/problems/find-number-of-coins-to-place-in-tree-nodes/)
- 🟡 [3004. Maximum Subtree of the Same Color](https://leetcode.com/problems/maximum-subtree-of-the-same-color/) 🔒
- 🔴 [3068. Find the Maximum Sum of Node Values](https://leetcode.com/problems/find-the-maximum-sum-of-node-values/)
- 🔴 [3241. Time Taken to Mark All Nodes](https://leetcode.com/problems/time-taken-to-mark-all-nodes/)
- 🔴 [3367. Maximize Sum of Weights after Edge Removals](https://leetcode.com/problems/maximize-sum-of-weights-after-edge-removals/)
- 🔴 [3544. Subtree Inversion Sum](https://leetcode.com/problems/subtree-inversion-sum/)
- 🔴 [3553. Minimum Weighted Subgraph With the Required Paths II](https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths-ii/)
- 🔴 [3559. Number of Ways to Assign Edge Weights II](https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-ii/)
- 🔴 [3562. Maximum Profit from Trading Stocks with Discounts](https://leetcode.com/problems/maximum-profit-from-trading-stocks-with-discounts/)
- 🔴 [3585. Find Weighted Median Node in Tree](https://leetcode.com/problems/find-weighted-median-node-in-tree/)
- 🟡 [3593. Minimum Increments to Equalize Leaf Paths](https://leetcode.com/problems/minimum-increments-to-equalize-leaf-paths/)
- 🔴 [3772. Maximum Subgraph Score in a Tree](https://leetcode.com/problems/maximum-subgraph-score-in-a-tree/)
- 🔴 [3939. Count Non Adjacent Subsets in a Rooted Tree](https://leetcode.com/problems/count-non-adjacent-subsets-in-a-rooted-tree/)
- 🔴 [3949. Subtree Inversion Sum II](https://leetcode.com/problems/subtree-inversion-sum-ii/) 🔒
- 🟡 [3965. Finish Time of Tasks I](https://leetcode.com/problems/finish-time-of-tasks-i/)
- 🔴 [3967. Finish Time of Tasks II](https://leetcode.com/problems/finish-time-of-tasks-ii/) 🔒
- 🔴 [3973. Distinct Gate Paths to LCA](https://leetcode.com/problems/distinct-gate-paths-to-lca/) 🔒
- 🔴 [4100. Minimum Cost Path With Even XOR Parity](https://leetcode.com/problems/minimum-cost-path-with-even-xor-parity/)
- 🟡 [4108. Minimum Cost to Make Red Nodes Connected](https://leetcode.com/problems/minimum-cost-to-make-red-nodes-connected/)

</details>

<details><summary><b>Bitmask DP</b> (27)</summary>

- 🟡 [464. Can I Win](https://leetcode.com/problems/can-i-win/)
- 🔴 [805. Split Array With Same Average](https://leetcode.com/problems/split-array-with-same-average/)
- 🔴 [847. Shortest Path Visiting All Nodes](https://leetcode.com/problems/shortest-path-visiting-all-nodes/)
- 🔴 [1125. Smallest Sufficient Team](https://leetcode.com/problems/smallest-sufficient-team/)
- 🔴 [1494. Parallel Courses II](https://leetcode.com/problems/parallel-courses-ii/)
- 🔴 [1617. Count Subtrees With Max Distance Between Cities](https://leetcode.com/problems/count-subtrees-with-max-distance-between-cities/)
- 🔴 [1659. Maximize Grid Happiness](https://leetcode.com/problems/maximize-grid-happiness/)
- 🔴 [1681. Minimum Incompatibility](https://leetcode.com/problems/minimum-incompatibility/)
- 🔴 [1755. Closest Subsequence Sum](https://leetcode.com/problems/closest-subsequence-sum/)
- 🔴 [1815. Maximum Number of Groups Getting Fresh Donuts](https://leetcode.com/problems/maximum-number-of-groups-getting-fresh-donuts/)
- 🔴 [1994. The Number of Good Subsets](https://leetcode.com/problems/the-number-of-good-subsets/)
- 🔴 [2035. Partition Array Into Two Arrays to Minimize Sum Difference](https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/)
- 🔴 [2172. Maximum AND Sum of Array](https://leetcode.com/problems/maximum-and-sum-of-array/)
- 🟡 [2184. Number of Ways to Build Sturdy Brick Wall](https://leetcode.com/problems/number-of-ways-to-build-sturdy-brick-wall/) 🔒
- 🔴 [2247. Maximum Cost of Trip With K Highways](https://leetcode.com/problems/maximum-cost-of-trip-with-k-highways/) 🔒
- 🔴 [2403. Minimum Time to Kill All Monsters](https://leetcode.com/problems/minimum-time-to-kill-all-monsters/) 🔒
- 🟡 [2572. Count the Number of Square-Free Subsets](https://leetcode.com/problems/count-the-number-of-square-free-subsets/)
- 🟡 [2741. Special Permutations](https://leetcode.com/problems/special-permutations/)
- 🔴 [3003. Maximize the Number of Partitions After Operations](https://leetcode.com/problems/maximize-the-number-of-partitions-after-operations/)
- 🔴 [3149. Find the Minimum Cost Array Permutation](https://leetcode.com/problems/find-the-minimum-cost-array-permutation/)
- 🔴 [3276. Select Cells in Grid With Maximum Score](https://leetcode.com/problems/select-cells-in-grid-with-maximum-score/)
- 🔴 [3444. Minimum Increments for Target Multiples in an Array](https://leetcode.com/problems/minimum-increments-for-target-multiples-in-an-array/)
- 🔴 [3533. Concatenated Divisibility](https://leetcode.com/problems/concatenated-divisibility/)
- 🔴 [3539. Find Sum of Array Product of Magical Sequences](https://leetcode.com/problems/find-sum-of-array-product-of-magical-sequences/)
- 🔴 [3575. Maximum Good Subtree Score](https://leetcode.com/problems/maximum-good-subtree-score/)
- 🔴 [3615. Longest Palindromic Path in Graph](https://leetcode.com/problems/longest-palindromic-path-in-graph/)
- 🔴 [4027. Elevator Requests III](https://leetcode.com/problems/elevator-requests-iii/)

</details>

<details><summary><b>Combinatorics / Counting DP</b> (21)</summary>

- 🔴 [458. Poor Pigs](https://leetcode.com/problems/poor-pigs/)
- 🟡 [634. Find the Derangement of An Array](https://leetcode.com/problems/find-the-derangement-of-an-array/) 🔒
- 🔴 [920. Number of Music Playlists](https://leetcode.com/problems/number-of-music-playlists/)
- 🔴 [1359. Count All Valid Pickup and Delivery Options](https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/)
- 🟡 [1641. Count Sorted Vowel Strings](https://leetcode.com/problems/count-sorted-vowel-strings/)
- 🔴 [1643. Kth Smallest Instructions](https://leetcode.com/problems/kth-smallest-instructions/)
- 🔴 [1735. Count Ways to Make Array With Product](https://leetcode.com/problems/count-ways-to-make-array-with-product/)
- 🔴 [1866. Number of Ways to Rearrange Sticks With K Sticks Visible](https://leetcode.com/problems/number-of-ways-to-rearrange-sticks-with-k-sticks-visible/)
- 🔴 [2338. Count the Number of Ideal Arrays](https://leetcode.com/problems/count-the-number-of-ideal-arrays/)
- 🟡 [2400. Number of Ways to Reach a Position After Exactly k Steps](https://leetcode.com/problems/number-of-ways-to-reach-a-position-after-exactly-k-steps/)
- 🟡 [2638. Count the Number of K-Free Subsets](https://leetcode.com/problems/count-the-number-of-k-free-subsets/) 🔒
- 🔴 [2912. Number of Ways to Reach Destination in the Grid](https://leetcode.com/problems/number-of-ways-to-reach-destination-in-the-grid/) 🔒
- 🟡 [2930. Number of Strings Which Can Be Rearranged to Contain Substring](https://leetcode.com/problems/number-of-strings-which-can-be-rearranged-to-contain-substring/)
- 🔴 [3154. Find Number of Ways to Reach the K-th Stair](https://leetcode.com/problems/find-number-of-ways-to-reach-the-k-th-stair/)
- 🟡 [3247. Number of Subsequences with Odd Sum](https://leetcode.com/problems/number-of-subsequences-with-odd-sum/) 🔒
- 🔴 [3250. Find the Count of Monotonic Pairs I](https://leetcode.com/problems/find-the-count-of-monotonic-pairs-i/)
- 🔴 [3251. Find the Count of Monotonic Pairs II](https://leetcode.com/problems/find-the-count-of-monotonic-pairs-ii/)
- 🔴 [3317. Find the Number of Possible Ways for an Event](https://leetcode.com/problems/find-the-number-of-possible-ways-for-an-event/)
- 🟡 [3428. Maximum and Minimum Sums of at Most Size K Subsequences](https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-size-k-subsequences/)
- 🔴 [3621. Number of Integers With Popcount-Depth Equal to K I](https://leetcode.com/problems/number-of-integers-with-popcount-depth-equal-to-k-i/)
- 🔴 [3757. Number of Effective Subsequences](https://leetcode.com/problems/number-of-effective-subsequences/)

</details>

<details><summary><b>Knapsack</b> (20)</summary>

- 🟡 [279. Perfect Squares](https://leetcode.com/problems/perfect-squares/)
- 🟡 [322. Coin Change](https://leetcode.com/problems/coin-change/)
- 🟡 [416. Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/)
- 🟡 [474. Ones and Zeroes](https://leetcode.com/problems/ones-and-zeroes/)
- 🟡 [494. Target Sum](https://leetcode.com/problems/target-sum/)
- 🟡 [518. Coin Change II](https://leetcode.com/problems/coin-change-ii/)
- 🔴 [656. Coin Path](https://leetcode.com/problems/coin-path/) 🔒
- 🔴 [879. Profitable Schemes](https://leetcode.com/problems/profitable-schemes/)
- 🔴 [956. Tallest Billboard](https://leetcode.com/problems/tallest-billboard/)
- 🟡 [1049. Last Stone Weight II](https://leetcode.com/problems/last-stone-weight-ii/)
- 🟡 [1155. Number of Dice Rolls With Target Sum](https://leetcode.com/problems/number-of-dice-rolls-with-target-sum/)
- 🟡 [1230. Toss Strange Coins](https://leetcode.com/problems/toss-strange-coins/) 🔒
- 🔴 [1449. Form Largest Integer With Digits That Add up to Target](https://leetcode.com/problems/form-largest-integer-with-digits-that-add-up-to-target/)
- 🔴 [2218. Maximum Value of K Coins From Piles](https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/)
- 🔴 [2585. Number of Ways to Earn Points](https://leetcode.com/problems/number-of-ways-to-earn-points/)
- 🟡 [2915. Length of the Longest Subsequence That Sums to Target](https://leetcode.com/problems/length-of-the-longest-subsequence-that-sums-to-target/)
- 🔴 [3082. Find the Sum of the Power of All Subsequences](https://leetcode.com/problems/find-the-sum-of-the-power-of-all-subsequences/)
- 🟡 [3183. The Number of Ways to Make the Sum](https://leetcode.com/problems/the-number-of-ways-to-make-the-sum/) 🔒
- 🟡 [3466. Maximum Coin Collection ](https://leetcode.com/problems/maximum-coin-collection/) 🔒
- 🟡 [3592. Inverse Coin Change](https://leetcode.com/problems/inverse-coin-change/)

</details>

<details><summary><b>Digit / Counting DP</b> (15)</summary>

- 🔴 [233. Number of Digit One](https://leetcode.com/problems/number-of-digit-one/)
- 🟡 [788. Rotated Digits](https://leetcode.com/problems/rotated-digits/)
- 🔴 [902. Numbers At Most N Given Digit Set](https://leetcode.com/problems/numbers-at-most-n-given-digit-set/)
- 🔴 [1012. Numbers With Repeated Digits](https://leetcode.com/problems/numbers-with-repeated-digits/)
- 🔴 [1067. Digit Count in Range](https://leetcode.com/problems/digit-count-in-range/) 🔒
- 🟡 [2310. Sum of Numbers With Units Digit K](https://leetcode.com/problems/sum-of-numbers-with-units-digit-k/)
- 🔴 [2376. Count Special Integers](https://leetcode.com/problems/count-special-integers/)
- 🔴 [2719. Count of Integers](https://leetcode.com/problems/count-of-integers/)
- 🔴 [2999. Count the Number of Powerful Integers](https://leetcode.com/problems/count-the-number-of-powerful-integers/)
- 🟢 [3032. Count Numbers With Unique Digits II](https://leetcode.com/problems/count-numbers-with-unique-digits-ii/) 🔒
- 🔴 [3519. Count Numbers with Non-Decreasing Digits ](https://leetcode.com/problems/count-numbers-with-non-decreasing-digits/)
- 🔴 [3725. Count Ways to Choose Coprime Integers from Rows](https://leetcode.com/problems/count-ways-to-choose-coprime-integers-from-rows/)
- 🟡 [3747. Count Distinct Integers After Removing Zeros](https://leetcode.com/problems/count-distinct-integers-after-removing-zeros/)
- 🔴 [3966. Count Good Integers in a Range](https://leetcode.com/problems/count-good-integers-in-a-range/)
- 🔴 [4060. Count Evenly Good Integers](https://leetcode.com/problems/count-evenly-good-integers/) 🔒

</details>

<details><summary><b>Game DP</b> (11)</summary>

- 🟡 [375. Guess Number Higher or Lower II](https://leetcode.com/problems/guess-number-higher-or-lower-ii/)
- 🟡 [486. Predict the Winner](https://leetcode.com/problems/predict-the-winner/)
- 🟡 [877. Stone Game](https://leetcode.com/problems/stone-game/)
- 🟢 [1025. Divisor Game](https://leetcode.com/problems/divisor-game/)
- 🟡 [1140. Stone Game II](https://leetcode.com/problems/stone-game-ii/)
- 🔴 [1406. Stone Game III](https://leetcode.com/problems/stone-game-iii/)
- 🔴 [1510. Stone Game IV](https://leetcode.com/problems/stone-game-iv/)
- 🔴 [1563. Stone Game V](https://leetcode.com/problems/stone-game-v/)
- 🟡 [1690. Stone Game VII](https://leetcode.com/problems/stone-game-vii/)
- 🔴 [1872. Stone Game VIII](https://leetcode.com/problems/stone-game-viii/)
- 🟡 [1908. Game of Nim](https://leetcode.com/problems/game-of-nim/) 🔒

</details>

<details><summary><b>Longest Increasing Subsequence</b> (10)</summary>

- 🟡 [300. Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/)
- 🟡 [334. Increasing Triplet Subsequence](https://leetcode.com/problems/increasing-triplet-subsequence/)
- 🔴 [354. Russian Doll Envelopes](https://leetcode.com/problems/russian-doll-envelopes/)
- 🟡 [646. Maximum Length of Pair Chain](https://leetcode.com/problems/maximum-length-of-pair-chain/)
- 🟢 [944. Delete Columns to Make Sorted](https://leetcode.com/problems/delete-columns-to-make-sorted/)
- 🔴 [1187. Make Array Strictly Increasing](https://leetcode.com/problems/make-array-strictly-increasing/)
- 🟡 [1626. Best Team With No Conflicts](https://leetcode.com/problems/best-team-with-no-conflicts/)
- 🔴 [1713. Minimum Operations to Make a Subsequence](https://leetcode.com/problems/minimum-operations-to-make-a-subsequence/)
- 🔴 [2111. Minimum Operations to Make the Array K-Increasing](https://leetcode.com/problems/minimum-operations-to-make-the-array-k-increasing/)
- 🔴 [3288. Length of the Longest Increasing Path](https://leetcode.com/problems/length-of-the-longest-increasing-path/)

</details>

<details><summary><b>State Machine DP (Stocks)</b> (7)</summary>

- 🔴 [123. Best Time to Buy and Sell Stock III](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/)
- 🔴 [188. Best Time to Buy and Sell Stock IV](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/)
- 🟡 [309. Best Time to Buy and Sell Stock with Cooldown](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)
- 🟡 [714. Best Time to Buy and Sell Stock with Transaction Fee](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/)
- 🟡 [2291. Maximum Profit From Trading Stocks](https://leetcode.com/problems/maximum-profit-from-trading-stocks/) 🔒
- 🟡 [3573. Best Time to Buy and Sell Stock V](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-v/)
- 🟡 [4069. Best Time to Buy and Sell Stock with Cooldown II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown-ii/) 🔒

</details>

<details><summary><b>DP on Graphs / DAGs</b> (7)</summary>

- 🔴 [488. Zuma Game](https://leetcode.com/problems/zuma-game/)
- 🔴 [514. Freedom Trail](https://leetcode.com/problems/freedom-trail/)
- 🔴 [1548. The Most Similar Path in a Graph](https://leetcode.com/problems/the-most-similar-path-in-a-graph/) 🔒
- 🔴 [2858. Minimum Edge Reversals So Every Node Is Reachable](https://leetcode.com/problems/minimum-edge-reversals-so-every-node-is-reachable/)
- 🟡 [2998. Minimum Number of Operations to Make X and Y Equal](https://leetcode.com/problems/minimum-number-of-operations-to-make-x-and-y-equal/)
- 🔴 [3534. Path Existence Queries in a Graph II](https://leetcode.com/problems/path-existence-queries-in-a-graph-ii/)
- 🟡 [3543. Maximum Weighted K-Edge Path](https://leetcode.com/problems/maximum-weighted-k-edge-path/)

</details>

<details><summary><b>Interval DP</b> (5)</summary>

- 🔴 [312. Burst Balloons](https://leetcode.com/problems/burst-balloons/)
- 🔴 [546. Remove Boxes](https://leetcode.com/problems/remove-boxes/)
- 🔴 [664. Strange Printer](https://leetcode.com/problems/strange-printer/)
- 🔴 [1000. Minimum Cost to Merge Stones](https://leetcode.com/problems/minimum-cost-to-merge-stones/)
- 🔴 [1547. Minimum Cost to Cut a Stick](https://leetcode.com/problems/minimum-cost-to-cut-a-stick/)

</details>

<details><summary><b>Kadane's Algorithm</b> (2)</summary>

- 🟡 [53. Maximum Subarray](https://leetcode.com/problems/maximum-subarray/)
- 🟡 [152. Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/)

</details>

<details><summary><b>Probability DP</b> (2)</summary>

- 🟡 [808. Soup Servings](https://leetcode.com/problems/soup-servings/)
- 🟡 [1227. Airplane Seat Assignment Probability](https://leetcode.com/problems/airplane-seat-assignment-probability/)

</details>

<details><summary><b>Grid DP (DFS + Memo)</b> (1)</summary>

- 🔴 [329. Longest Increasing Path in a Matrix](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/)

</details>

<details><summary><b>Guessed from title (no tags yet)</b> (1)</summary>

- 🔴 [3802. Number of Ways to Paint Sheets](https://leetcode.com/problems/number-of-ways-to-paint-sheets/) 🔒

</details>

## Greedy

*A local best choice is provably globally best (often after sorting).* — 224 problems

<details><summary><b>Sort + Greedy</b> (85)</summary>

- 🟡 [179. Largest Number](https://leetcode.com/problems/largest-number/)
- 🟡 [280. Wiggle Sort](https://leetcode.com/problems/wiggle-sort/) 🔒
- 🟡 [324. Wiggle Sort II](https://leetcode.com/problems/wiggle-sort-ii/)
- 🟢 [561. Array Partition](https://leetcode.com/problems/array-partition/)
- 🔴 [757. Set Intersection Size At Least Two](https://leetcode.com/problems/set-intersection-size-at-least-two/)
- 🟡 [846. Hand of Straights](https://leetcode.com/problems/hand-of-straights/)
- 🟡 [910. Smallest Range II](https://leetcode.com/problems/smallest-range-ii/)
- 🟡 [945. Minimum Increment to Make Array Unique](https://leetcode.com/problems/minimum-increment-to-make-array-unique/)
- 🟡 [954. Array of Doubled Pairs](https://leetcode.com/problems/array-of-doubled-pairs/)
- 🟢 [976. Largest Perimeter Triangle](https://leetcode.com/problems/largest-perimeter-triangle/)
- 🟢 [1005. Maximize Sum Of Array After K Negations](https://leetcode.com/problems/maximize-sum-of-array-after-k-negations/)
- 🟡 [1058. Minimize Rounding Error to Meet Target](https://leetcode.com/problems/minimize-rounding-error-to-meet-target/) 🔒
- 🟡 [1090. Largest Values From Labels](https://leetcode.com/problems/largest-values-from-labels/)
- 🟢 [1196. How Many Apples Can You Put into the Basket](https://leetcode.com/problems/how-many-apples-can-you-put-into-the-basket/) 🔒
- 🟡 [1296. Divide Array in Sets of K Consecutive Numbers](https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/)
- 🟢 [1403. Minimum Subsequence in Non-Increasing Order](https://leetcode.com/problems/minimum-subsequence-in-non-increasing-order/)
- 🟡 [1433. Check If a String Can Break Another String](https://leetcode.com/problems/check-if-a-string-can-break-another-string/)
- 🟡 [1465. Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts](https://leetcode.com/problems/maximum-area-of-a-piece-of-cake-after-horizontal-and-vertical-cuts/)
- 🟡 [1481. Least Number of Unique Integers after K Removals](https://leetcode.com/problems/least-number-of-unique-integers-after-k-removals/)
- 🟡 [1509. Minimum Difference Between Largest and Smallest Value in Three Moves](https://leetcode.com/problems/minimum-difference-between-largest-and-smallest-value-in-three-moves/)
- 🟡 [1561. Maximum Number of Coins You Can Get](https://leetcode.com/problems/maximum-number-of-coins-you-can-get/)
- 🟡 [1564. Put Boxes Into the Warehouse I](https://leetcode.com/problems/put-boxes-into-the-warehouse-i/) 🔒
- 🟡 [1580. Put Boxes Into the Warehouse II](https://leetcode.com/problems/put-boxes-into-the-warehouse-ii/) 🔒
- 🔴 [1585. Check If String Is Transformable With Substring Sort Operations](https://leetcode.com/problems/check-if-string-is-transformable-with-substring-sort-operations/)
- 🟡 [1647. Minimum Deletions to Make Character Frequencies Unique](https://leetcode.com/problems/minimum-deletions-to-make-character-frequencies-unique/)
- 🔴 [1665. Minimum Initial Energy to Finish Tasks](https://leetcode.com/problems/minimum-initial-energy-to-finish-tasks/)
- 🟢 [1710. Maximum Units on a Truck](https://leetcode.com/problems/maximum-units-on-a-truck/)
- 🟡 [1727. Largest Submatrix With Rearrangements](https://leetcode.com/problems/largest-submatrix-with-rearrangements/)
- 🟡 [1798. Maximum Number of Consecutive Values You Can Make](https://leetcode.com/problems/maximum-number-of-consecutive-values-you-can-make/)
- 🟡 [1833. Maximum Ice Cream Bars](https://leetcode.com/problems/maximum-ice-cream-bars/)
- 🟡 [1846. Maximum Element After Decreasing and Rearranging](https://leetcode.com/problems/maximum-element-after-decreasing-and-rearranging/)
- 🟡 [1874. Minimize Product Sum of Two Arrays](https://leetcode.com/problems/minimize-product-sum-of-two-arrays/) 🔒
- 🟡 [1921. Eliminate Maximum Number of Monsters](https://leetcode.com/problems/eliminate-maximum-number-of-monsters/)
- 🟡 [1968. Array With Elements Not Equal to Average of Neighbors](https://leetcode.com/problems/array-with-elements-not-equal-to-average-of-neighbors/)
- 🟡 [2007. Find Original Array From Doubled Array](https://leetcode.com/problems/find-original-array-from-doubled-array/)
- 🟢 [2037. Minimum Number of Moves to Seat Everyone](https://leetcode.com/problems/minimum-number-of-moves-to-seat-everyone/)
- 🟡 [2098. Subsequence of Size K With the Largest Even Sum](https://leetcode.com/problems/subsequence-of-size-k-with-the-largest-even-sum/) 🔒
- 🟡 [2126. Destroying Asteroids](https://leetcode.com/problems/destroying-asteroids/)
- 🔴 [2136. Earliest Possible Day of Full Bloom](https://leetcode.com/problems/earliest-possible-day-of-full-bloom/)
- 🟢 [2144. Minimum Cost of Buying Candies With Discount](https://leetcode.com/problems/minimum-cost-of-buying-candies-with-discount/)
- 🟢 [2160. Minimum Sum of Four Digit Number After Splitting Digits](https://leetcode.com/problems/minimum-sum-of-four-digit-number-after-splitting-digits/)
- 🟡 [2195. Append K Integers With Minimal Sum](https://leetcode.com/problems/append-k-integers-with-minimal-sum/)
- 🟡 [2268. Minimum Number of Keypresses](https://leetcode.com/problems/minimum-number-of-keypresses/) 🔒
- 🟡 [2279. Maximum Bags With Full Capacity of Rocks](https://leetcode.com/problems/maximum-bags-with-full-capacity-of-rocks/)
- 🟡 [2294. Partition Array Such That Maximum Difference Is K](https://leetcode.com/problems/partition-array-such-that-maximum-difference-is-k/)
- 🟡 [2323. Find Minimum Time to Finish All Jobs II](https://leetcode.com/problems/find-minimum-time-to-finish-all-jobs-ii/) 🔒
- 🔴 [2412. Minimum Money Required Before Transactions](https://leetcode.com/problems/minimum-money-required-before-transactions/)
- 🔴 [2449. Minimum Number of Operations to Make Arrays Similar](https://leetcode.com/problems/minimum-number-of-operations-to-make-arrays-similar/)
- 🟡 [2548. Maximum Price to Fill a Bag](https://leetcode.com/problems/maximum-price-to-fill-a-bag/) 🔒
- 🔴 [2561. Rearranging Fruits](https://leetcode.com/problems/rearranging-fruits/)
- 🟡 [2567. Minimum Score by Changing Two Elements](https://leetcode.com/problems/minimum-score-by-changing-two-elements/)
- 🟢 [2578. Split With Minimum Sum](https://leetcode.com/problems/split-with-minimum-sum/)
- 🟡 [2607. Make K-Subarray Sums Equal](https://leetcode.com/problems/make-k-subarray-sums-equal/)
- 🟢 [2706. Buy Two Chocolates](https://leetcode.com/problems/buy-two-chocolates/)
- 🔴 [2842. Count K-Subsequences of a String With Maximum Beauty](https://leetcode.com/problems/count-k-subsequences-of-a-string-with-maximum-beauty/)
- 🟡 [2895. Minimum Processing Time](https://leetcode.com/problems/minimum-processing-time/)
- 🟡 [2952. Minimum Number of Coins to be Added](https://leetcode.com/problems/minimum-number-of-coins-to-be-added/)
- 🟡 [2966. Divide Array Into Arrays With Max Difference](https://leetcode.com/problems/divide-array-into-arrays-with-max-difference/)
- 🟡 [3016. Minimum Number of Pushes to Type Word II](https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-ii/)
- 🟡 [3035. Maximum Palindromes After Operations](https://leetcode.com/problems/maximum-palindromes-after-operations/)
- 🟢 [3074. Apple Redistribution into Boxes](https://leetcode.com/problems/apple-redistribution-into-boxes/)
- 🟡 [3075. Maximize Happiness of Selected Children](https://leetcode.com/problems/maximize-happiness-of-selected-children/)
- 🟡 [3085. Minimum Deletions to Make String K-Special](https://leetcode.com/problems/minimum-deletions-to-make-string-k-special/)
- 🔴 [3088. Make String Anti-palindrome](https://leetcode.com/problems/make-string-anti-palindrome/) 🔒
- 🟡 [3107. Minimum Operations to Make Median of Array Equal to K](https://leetcode.com/problems/minimum-operations-to-make-median-of-array-equal-to-k/)
- 🟡 [3111. Minimum Rectangles to Cover Points](https://leetcode.com/problems/minimum-rectangles-to-cover-points/)
- 🟡 [3119. Maximum Number of Potholes That Can Be Fixed](https://leetcode.com/problems/maximum-number-of-potholes-that-can-be-fixed/) 🔒
- 🟡 [3125. Maximum Number That Makes Result of Bitwise AND Zero](https://leetcode.com/problems/maximum-number-that-makes-result-of-bitwise-and-zero/) 🔒
- 🟡 [3189. Minimum Moves to Get a Peaceful Board](https://leetcode.com/problems/minimum-moves-to-get-a-peaceful-board/) 🔒
- 🔴 [3219. Minimum Cost for Cutting Cake II](https://leetcode.com/problems/minimum-cost-for-cutting-cake-ii/)
- 🔴 [3273. Minimum Amount of Damage Dealt to Bob](https://leetcode.com/problems/minimum-amount-of-damage-dealt-to-bob/)
- 🟡 [3301. Maximize the Total Height of Unique Towers](https://leetcode.com/problems/maximize-the-total-height-of-unique-towers/)
- 🟡 [3397. Maximum Number of Distinct Elements After Operations](https://leetcode.com/problems/maximum-number-of-distinct-elements-after-operations/)
- 🟡 [3424. Minimum Cost to Make Arrays Identical](https://leetcode.com/problems/minimum-cost-to-make-arrays-identical/)
- 🟡 [3457. Eat Pizzas!](https://leetcode.com/problems/eat-pizzas/)
- 🟢 [3545. Minimum Deletions for At Most K Distinct Characters](https://leetcode.com/problems/minimum-deletions-for-at-most-k-distinct-characters/)
- 🟡 [3627. Maximum Median Sum of Subsequences of Size 3](https://leetcode.com/problems/maximum-median-sum-of-subsequences-of-size-3/)
- 🟢 [3684. Maximize Sum of At Most K Distinct Elements](https://leetcode.com/problems/maximize-sum-of-at-most-k-distinct-elements/)
- 🟡 [3727. Maximum Alternating Sum of Squares](https://leetcode.com/problems/maximum-alternating-sum-of-squares/)
- 🟡 [3732. Maximum Product of Three Elements After One Replacement](https://leetcode.com/problems/maximum-product-of-three-elements-after-one-replacement/)
- 🟢 [3745. Maximize Expression of Three Elements](https://leetcode.com/problems/maximize-expression-of-three-elements/)
- 🟡 [3776. Minimum Moves to Balance Circular Array](https://leetcode.com/problems/minimum-moves-to-balance-circular-array/)
- 🔴 [3897. Maximum Value of Concatenated Binary Segments](https://leetcode.com/problems/maximum-value-of-concatenated-binary-segments/)
- 🟡 [3961. Maximize Sum of Device Ratings](https://leetcode.com/problems/maximize-sum-of-device-ratings/)
- 🟡 [3974. Maximum Total Sum of K Selected Elements](https://leetcode.com/problems/maximum-total-sum-of-k-selected-elements/)

</details>

<details><summary><b>Greedy Choice</b> (59)</summary>

- 🟡 [122. Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/)
- 🔴 [330. Patching Array](https://leetcode.com/problems/patching-array/)
- 🔴 [517. Super Washing Machines](https://leetcode.com/problems/super-washing-machines/)
- 🟢 [605. Can Place Flowers](https://leetcode.com/problems/can-place-flowers/)
- 🟡 [624. Maximum Distance in Arrays](https://leetcode.com/problems/maximum-distance-in-arrays/)
- 🟢 [860. Lemonade Change](https://leetcode.com/problems/lemonade-change/)
- 🟡 [1007. Minimum Domino Rotations For Equal Row](https://leetcode.com/problems/minimum-domino-rotations-for-equal-row/)
- 🟢 [1013. Partition Array Into Three Parts With Equal Sum](https://leetcode.com/problems/partition-array-into-three-parts-with-equal-sum/)
- 🟡 [1053. Previous Permutation With One Swap](https://leetcode.com/problems/previous-permutation-with-one-swap/)
- 🟡 [1144. Decrease Elements To Make Array Zigzag](https://leetcode.com/problems/decrease-elements-to-make-array-zigzag/)
- 🟡 [1253. Reconstruct a 2-Row Binary Matrix](https://leetcode.com/problems/reconstruct-a-2-row-binary-matrix/)
- 🟡 [1282. Group the People Given the Group Size They Belong To](https://leetcode.com/problems/group-the-people-given-the-group-size-they-belong-to/)
- 🟡 [1536. Minimum Swaps to Arrange a Binary Grid](https://leetcode.com/problems/minimum-swaps-to-arrange-a-binary-grid/)
- 🟢 [1708. Largest Subarray Length K](https://leetcode.com/problems/largest-subarray-length-k/) 🔒
- 🟡 [1733. Minimum Number of People to Teach](https://leetcode.com/problems/minimum-number-of-people-to-teach/)
- 🟡 [1775. Equal Sum Arrays With Minimum Number of Operations](https://leetcode.com/problems/equal-sum-arrays-with-minimum-number-of-operations/)
- 🟡 [1785. Minimum Elements to Add to Form a Given Sum](https://leetcode.com/problems/minimum-elements-to-add-to-form-a-given-sum/)
- 🟢 [1827. Minimum Operations to Make the Array Increasing](https://leetcode.com/problems/minimum-operations-to-make-the-array-increasing/)
- 🟡 [1899. Merge Triplets to Form Target Triplet](https://leetcode.com/problems/merge-triplets-to-form-target-triplet/)
- 🟡 [1936. Add Minimum Number of Rungs](https://leetcode.com/problems/add-minimum-number-of-rungs/)
- 🟡 [1953. Maximum Number of Weeks for Which You Can Work](https://leetcode.com/problems/maximum-number-of-weeks-for-which-you-can-work/)
- 🟡 [1975. Maximum Matrix Sum](https://leetcode.com/problems/maximum-matrix-sum/)
- 🟢 [2078. Two Furthest Houses With Different Colors](https://leetcode.com/problems/two-furthest-houses-with-different-colors/)
- 🟡 [2087. Minimum Cost Homecoming of a Robot in a Grid](https://leetcode.com/problems/minimum-cost-homecoming-of-a-robot-in-a-grid/)
- 🟡 [2091. Removing Minimum and Maximum From Array](https://leetcode.com/problems/removing-minimum-and-maximum-from-array/)
- 🟡 [2170. Minimum Operations to Make the Array Alternating](https://leetcode.com/problems/minimum-operations-to-make-the-array-alternating/)
- 🟡 [2202. Maximize the Topmost Element After K Moves](https://leetcode.com/problems/maximize-the-topmost-element-after-k-moves/)
- 🟡 [2214. Minimum Health to Beat Game](https://leetcode.com/problems/minimum-health-to-beat-game/) 🔒
- 🟡 [2244. Minimum Rounds to Complete All Tasks](https://leetcode.com/problems/minimum-rounds-to-complete-all-tasks/)
- 🟡 [2340. Minimum Adjacent Swaps to Make a Valid Array](https://leetcode.com/problems/minimum-adjacent-swaps-to-make-a-valid-array/) 🔒
- 🔴 [2350. Shortest Impossible Sequence of Rolls](https://leetcode.com/problems/shortest-impossible-sequence-of-rolls/)
- 🟢 [2383. Minimum Hours of Training to Win a Competition](https://leetcode.com/problems/minimum-hours-of-training-to-win-a-competition/)
- 🔴 [2499. Minimum Total Cost to Make Arrays Unequal](https://leetcode.com/problems/minimum-total-cost-to-make-arrays-unequal/)
- 🟢 [2656. Maximum Sum With Exactly K Elements ](https://leetcode.com/problems/maximum-sum-with-exactly-k-elements/)
- 🟡 [2789. Largest Element in an Array after Merge Operations](https://leetcode.com/problems/largest-element-in-an-array-after-merge-operations/)
- 🟡 [2870. Minimum Number of Operations to Make Array Empty](https://leetcode.com/problems/minimum-number-of-operations-to-make-array-empty/)
- 🟡 [2910. Minimum Number of Groups to Create a Valid Assignment](https://leetcode.com/problems/minimum-number-of-groups-to-create-a-valid-assignment/)
- 🟡 [2918. Minimum Equal Sum of Two Arrays After Replacing Zeros](https://leetcode.com/problems/minimum-equal-sum-of-two-arrays-after-replacing-zeros/)
- 🟡 [3002. Maximum Size of a Set After Removals](https://leetcode.com/problems/maximum-size-of-a-set-after-removals/)
- 🔴 [3139. Minimum Cost to Equalize Array](https://leetcode.com/problems/minimum-cost-to-equalize-array/)
- 🟡 [3207. Maximum Points After Enemy Battles](https://leetcode.com/problems/maximum-points-after-enemy-battles/)
- 🟡 [3282. Reach End of Array With Max Score](https://leetcode.com/problems/reach-end-of-array-with-max-score/)
- 🟢 [3402. Minimum Operations to Make Columns Strictly Increasing](https://leetcode.com/problems/minimum-operations-to-make-columns-strictly-increasing/)
- 🟡 [3440. Reschedule Meetings for Maximum Free Time II](https://leetcode.com/problems/reschedule-meetings-for-maximum-free-time-ii/)
- 🟢 [3487. Maximum Unique Subarray Sum After Deletion](https://leetcode.com/problems/maximum-unique-subarray-sum-after-deletion/)
- 🟡 [3496. Maximize Score After Pair Deletions](https://leetcode.com/problems/maximize-score-after-pair-deletions/) 🔒
- 🟡 [3576. Transform Array to All Equal Elements](https://leetcode.com/problems/transform-array-to-all-equal-elements/)
- 🟡 [3587. Minimum Adjacent Swaps to Alternate Parity](https://leetcode.com/problems/minimum-adjacent-swaps-to-alternate-parity/)
- 🟡 [3689. Maximum Total Subarray Value I](https://leetcode.com/problems/maximum-total-subarray-value-i/)
- 🟡 [3724. Minimum Operations to Transform Array](https://leetcode.com/problems/minimum-operations-to-transform-array/)
- 🔴 [3785. Minimum Swaps to Avoid Forbidden Values](https://leetcode.com/problems/minimum-swaps-to-avoid-forbidden-values/)
- 🟡 [3796. Find Maximum Value in a Constrained Sequence](https://leetcode.com/problems/find-maximum-value-in-a-constrained-sequence/)
- 🟡 [3810. Minimum Operations to Reach Target Array](https://leetcode.com/problems/minimum-operations-to-reach-target-array/)
- 🟡 [3854. Minimum Operations to Make Array Parity Alternating](https://leetcode.com/problems/minimum-operations-to-make-array-parity-alternating/)
- 🟡 [3868. Minimum Cost to Equalize Arrays Using Swaps](https://leetcode.com/problems/minimum-cost-to-equalize-arrays-using-swaps/)
- 🟡 [3914. Minimum Operations to Make Array Non Decreasing](https://leetcode.com/problems/minimum-operations-to-make-array-non-decreasing/)
- 🔴 [3948. Lexicographically Maximum MEX Array](https://leetcode.com/problems/lexicographically-maximum-mex-array/)
- 🟡 [3994. Minimum Adjacent Swaps to Partition Array](https://leetcode.com/problems/minimum-adjacent-swaps-to-partition-array/)
- 🟡 [4025. Minimize the Maximum Waiting Time at Synchronized Traffic Lights](https://leetcode.com/problems/minimize-the-maximum-waiting-time-at-synchronized-traffic-lights/)

</details>

<details><summary><b>Constructive / Math Greedy</b> (41)</summary>

- 🟡 [625. Minimum Factorization](https://leetcode.com/problems/minimum-factorization/) 🔒
- 🟡 [670. Maximum Swap](https://leetcode.com/problems/maximum-swap/)
- 🟡 [738. Monotone Increasing Digits](https://leetcode.com/problems/monotone-increasing-digits/)
- 🟡 [781. Rabbits in Forest](https://leetcode.com/problems/rabbits-in-forest/)
- 🟡 [991. Broken Calculator](https://leetcode.com/problems/broken-calculator/)
- 🟢 [1217. Minimum Cost to Move Chips to The Same Position](https://leetcode.com/problems/minimum-cost-to-move-chips-to-the-same-position/)
- 🟡 [1247. Minimum Swaps to Make Strings Equal](https://leetcode.com/problems/minimum-swaps-to-make-strings-equal/)
- 🟢 [1323. Maximum 69 Number](https://leetcode.com/problems/maximum-69-number/)
- 🔴 [1330. Reverse Subarray To Maximize Array Value](https://leetcode.com/problems/reverse-subarray-to-maximize-array-value/)
- 🟡 [1414. Find the Minimum Number of Fibonacci Numbers Whose Sum Is K](https://leetcode.com/problems/find-the-minimum-number-of-fibonacci-numbers-whose-sum-is-k/)
- 🟡 [1432. Max Difference You Can Get From Changing an Integer](https://leetcode.com/problems/max-difference-you-can-get-from-changing-an-integer/)
- 🟢 [1903. Largest Odd Number in String](https://leetcode.com/problems/largest-odd-number-in-string/)
- 🟡 [1927. Sum Game](https://leetcode.com/problems/sum-game/)
- 🟡 [1969. Minimum Non-Zero Product of the Array Elements](https://leetcode.com/problems/minimum-non-zero-product-of-the-array-elements/)
- 🟡 [2029. Stone Game IX](https://leetcode.com/problems/stone-game-ix/)
- 🟡 [2038. Remove Colored Pieces if Both Neighbors are the Same Color](https://leetcode.com/problems/remove-colored-pieces-if-both-neighbors-are-the-same-color/)
- 🟡 [2139. Minimum Moves to Reach Target Score](https://leetcode.com/problems/minimum-moves-to-reach-target-score/)
- 🔴 [2366. Minimum Replacements to Sort the Array](https://leetcode.com/problems/minimum-replacements-to-sort-the-array/)
- 🟡 [2457. Minimum Addition to Make Integer Beautiful](https://leetcode.com/problems/minimum-addition-to-make-integer-beautiful/)
- 🟡 [2541. Minimum Operations to Make Array Equal II](https://leetcode.com/problems/minimum-operations-to-make-array-equal-ii/)
- 🟢 [2566. Maximum Difference by Remapping a Digit](https://leetcode.com/problems/maximum-difference-by-remapping-a-digit/)
- 🟢 [2591. Distribute Money to Maximum Children](https://leetcode.com/problems/distribute-money-to-maximum-children/)
- 🟡 [2598. Smallest Missing Non-negative Integer After Operations](https://leetcode.com/problems/smallest-missing-non-negative-integer-after-operations/)
- 🟢 [2600. K Items With the Maximum Sum](https://leetcode.com/problems/k-items-with-the-maximum-sum/)
- 🟡 [2829. Determine the Minimum Sum of a k-avoiding Array](https://leetcode.com/problems/determine-the-minimum-sum-of-a-k-avoiding-array/)
- 🟡 [2834. Find the Minimum Possible Sum of a Beautiful Array](https://leetcode.com/problems/find-the-minimum-possible-sum-of-a-beautiful-array/)
- 🟡 [2844. Minimum Operations to Make a Special Number](https://leetcode.com/problems/minimum-operations-to-make-a-special-number/)
- 🟡 [2847. Smallest Number With Given Digit Product](https://leetcode.com/problems/smallest-number-with-given-digit-product/) 🔒
- 🟢 [2864. Maximum Odd Binary Number](https://leetcode.com/problems/maximum-odd-binary-number/)
- 🟡 [3012. Minimize Length of Array Using Operations](https://leetcode.com/problems/minimize-length-of-array-using-operations/)
- 🟢 [3014. Minimum Number of Pushes to Type Word I](https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-i/)
- 🟡 [3091. Apply Operations to Make Sum of Array Greater Than or Equal to k](https://leetcode.com/problems/apply-operations-to-make-sum-of-array-greater-than-or-equal-to-k/)
- 🟡 [3326. Minimum Division Operations to Make Array Non Decreasing](https://leetcode.com/problems/minimum-division-operations-to-make-array-non-decreasing/)
- 🟡 [3588. Find Maximum Area of a Triangle](https://leetcode.com/problems/find-maximum-area-of-a-triangle/)
- 🟡 [3680. Generate Schedule](https://leetcode.com/problems/generate-schedule/)
- 🟡 [3723. Maximize Sum of Squares of Digits](https://leetcode.com/problems/maximize-sum-of-squares-of-digits/)
- 🟡 [3789. Minimum Cost to Acquire Required Items](https://leetcode.com/problems/minimum-cost-to-acquire-required-items/)
- 🟡 [3927. Minimize Array Sum Using Divisible Replacements](https://leetcode.com/problems/minimize-array-sum-using-divisible-replacements/)
- 🟡 [3993. Maximum Value of an Alternating Sequence](https://leetcode.com/problems/maximum-value-of-an-alternating-sequence/)
- 🟢 [4000. Largest Integer With Given Digit Sum](https://leetcode.com/problems/largest-integer-with-given-digit-sum/)
- 🟡 [4098. Minimize the Maximum Value of GCD-Connected Array](https://leetcode.com/problems/minimize-the-maximum-value-of-gcd-connected-array/)

</details>

<details><summary><b>String Greedy</b> (33)</summary>

- 🟢 [409. Longest Palindrome](https://leetcode.com/problems/longest-palindrome/)
- 🟡 [555. Split Concatenated Strings](https://leetcode.com/problems/split-concatenated-strings/) 🔒
- 🟡 [649. Dota2 Senate](https://leetcode.com/problems/dota2-senate/)
- 🟡 [955. Delete Columns to Make Sorted II](https://leetcode.com/problems/delete-columns-to-make-sorted-ii/)
- 🟡 [984. String Without AAA or BBB](https://leetcode.com/problems/string-without-aaa-or-bbb/)
- 🟢 [1221. Split a String in Balanced Strings](https://leetcode.com/problems/split-a-string-in-balanced-strings/)
- 🟡 [1328. Break a Palindrome](https://leetcode.com/problems/break-a-palindrome/)
- 🟡 [1400. Construct K Palindrome Strings](https://leetcode.com/problems/construct-k-palindrome-strings/)
- 🟡 [1529. Minimum Suffix Flips](https://leetcode.com/problems/minimum-suffix-flips/)
- 🟡 [1663. Smallest String With A Given Numeric Value](https://leetcode.com/problems/smallest-string-with-a-given-numeric-value/)
- 🟡 [1689. Partitioning Into Minimum Number Of Deci-Binary Numbers](https://leetcode.com/problems/partitioning-into-minimum-number-of-deci-binary-numbers/)
- 🟡 [1702. Maximum Binary String After Change](https://leetcode.com/problems/maximum-binary-string-after-change/)
- 🟢 [1736. Latest Time by Replacing Hidden Digits](https://leetcode.com/problems/latest-time-by-replacing-hidden-digits/)
- 🟡 [1794. Count Pairs of Equal Substrings With Minimum Difference](https://leetcode.com/problems/count-pairs-of-equal-substrings-with-minimum-difference/) 🔒
- 🟡 [1864. Minimum Number of Swaps to Make the Binary String Alternating](https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-binary-string-alternating/)
- 🟡 [1881. Maximum Value after Insertion](https://leetcode.com/problems/maximum-value-after-insertion/)
- 🟡 [1946. Largest Number After Mutating Substring](https://leetcode.com/problems/largest-number-after-mutating-substring/)
- 🟢 [1974. Minimum Time to Type Word Using Special Typewriter](https://leetcode.com/problems/minimum-time-to-type-word-using-special-typewriter/)
- 🟢 [2027. Minimum Moves to Convert String](https://leetcode.com/problems/minimum-moves-to-convert-string/)
- 🟡 [2131. Longest Palindrome by Concatenating Two Letter Words](https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/)
- 🟢 [2224. Minimum Number of Operations to Convert Time](https://leetcode.com/problems/minimum-number-of-operations-to-convert-time/)
- 🟢 [2259. Remove Digit From Number to Maximize Result](https://leetcode.com/problems/remove-digit-from-number-to-maximize-result/)
- 🟡 [2384. Largest Palindromic Number](https://leetcode.com/problems/largest-palindromic-number/)
- 🟡 [2405. Optimal Partition of String](https://leetcode.com/problems/optimal-partition-of-string/)
- 🔴 [2663. Lexicographically Smallest Beautiful String](https://leetcode.com/problems/lexicographically-smallest-beautiful-string/)
- 🟡 [2734. Lexicographically Smallest String After Substring Operation](https://leetcode.com/problems/lexicographically-smallest-string-after-substring-operation/)
- 🟡 [2800. Shortest String That Contains Three Strings](https://leetcode.com/problems/shortest-string-that-contains-three-strings/)
- 🟡 [3106. Lexicographically Smallest String After Operations With Constraint](https://leetcode.com/problems/lexicographically-smallest-string-after-operations-with-constraint/)
- 🟢 [3216. Lexicographically Smallest String After a Swap](https://leetcode.com/problems/lexicographically-smallest-string-after-a-swap/)
- 🟡 [3228. Maximum Number of Operations to Move Ones to the End](https://leetcode.com/problems/maximum-number-of-operations-to-move-ones-to-the-end/)
- 🟡 [3675. Minimum Operations to Transform String](https://leetcode.com/problems/minimum-operations-to-transform-string/)
- 🟡 [3720. Lexicographically Smallest Permutation Greater Than Target](https://leetcode.com/problems/lexicographically-smallest-permutation-greater-than-target/)
- 🟡 [3800. Minimum Cost to Make Two Binary Strings Equal](https://leetcode.com/problems/minimum-cost-to-make-two-binary-strings-equal/)

</details>

<details><summary><b>Reachability</b> (2)</summary>

- 🟡 [45. Jump Game II](https://leetcode.com/problems/jump-game-ii/)
- 🟡 [55. Jump Game](https://leetcode.com/problems/jump-game/)

</details>

<details><summary><b>Running Balance</b> (1)</summary>

- 🟡 [134. Gas Station](https://leetcode.com/problems/gas-station/)

</details>

<details><summary><b>Two Passes</b> (1)</summary>

- 🔴 [135. Candy](https://leetcode.com/problems/candy/)

</details>

<details><summary><b>Range of Balances</b> (1)</summary>

- 🟡 [678. Valid Parenthesis String](https://leetcode.com/problems/valid-parenthesis-string/)

</details>

<details><summary><b>Last Occurrence</b> (1)</summary>

- 🟡 [763. Partition Labels](https://leetcode.com/problems/partition-labels/)

</details>

## Trie

*Prefix search, word dictionaries, bitwise-XOR maximisation.* — 42 problems

<details><summary><b>Prefix Trie</b> (23)</summary>

- 🟢 [14. Longest Common Prefix](https://leetcode.com/problems/longest-common-prefix/)
- 🔴 [440. K-th Smallest in Lexicographical Order](https://leetcode.com/problems/k-th-smallest-in-lexicographical-order/)
- 🔴 [527. Word Abbreviation](https://leetcode.com/problems/word-abbreviation/) 🔒
- 🔴 [588. Design In-Memory File System](https://leetcode.com/problems/design-in-memory-file-system/) 🔒
- 🟡 [648. Replace Words](https://leetcode.com/problems/replace-words/)
- 🟡 [677. Map Sum Pairs](https://leetcode.com/problems/map-sum-pairs/)
- 🟡 [692. Top K Frequent Words](https://leetcode.com/problems/top-k-frequent-words/)
- 🟡 [720. Longest Word in Dictionary](https://leetcode.com/problems/longest-word-in-dictionary/)
- 🔴 [745. Prefix and Suffix Search](https://leetcode.com/problems/prefix-and-suffix-search/)
- 🟡 [820. Short Encoding of Words](https://leetcode.com/problems/short-encoding-of-words/)
- 🟡 [1166. Design File System](https://leetcode.com/problems/design-file-system/) 🔒
- 🟡 [1268. Search Suggestions System](https://leetcode.com/problems/search-suggestions-system/)
- 🟡 [1804. Implement Trie II (Prefix Tree)](https://leetcode.com/problems/implement-trie-ii-prefix-tree/) 🔒
- 🔴 [2227. Encrypt and Decrypt Strings](https://leetcode.com/problems/encrypt-and-decrypt-strings/)
- 🔴 [2416. Sum of Prefix Scores of Strings](https://leetcode.com/problems/sum-of-prefix-scores-of-strings/)
- 🟡 [2452. Words Within Two Edits of Dictionary](https://leetcode.com/problems/words-within-two-edits-of-dictionary/)
- 🟡 [3043. Find the Length of the Longest Common Prefix](https://leetcode.com/problems/find-the-length-of-the-longest-common-prefix/)
- 🟡 [3076. Shortest Uncommon Substring in an Array](https://leetcode.com/problems/shortest-uncommon-substring-in-an-array/)
- 🔴 [3093. Longest Common Suffix Queries](https://leetcode.com/problems/longest-common-suffix-queries/)
- 🔴 [3485. Longest Common Prefix of K Strings After Removal](https://leetcode.com/problems/longest-common-prefix-of-k-strings-after-removal/)
- 🟢 [3491. Phone Number Prefix](https://leetcode.com/problems/phone-number-prefix/) 🔒
- 🟡 [3597. Partition String ](https://leetcode.com/problems/partition-string/)
- 🟡 [3758. Convert Number Words to Digits](https://leetcode.com/problems/convert-number-words-to-digits/) 🔒

</details>

<details><summary><b>Bitwise Trie</b> (9)</summary>

- 🟡 [421. Maximum XOR of Two Numbers in an Array](https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/)
- 🔴 [1178. Number of Valid Words for Each Puzzle](https://leetcode.com/problems/number-of-valid-words-for-each-puzzle/)
- 🔴 [1707. Maximum XOR With an Element From Array](https://leetcode.com/problems/maximum-xor-with-an-element-from-array/)
- 🔴 [1803. Count Pairs With XOR in a Range](https://leetcode.com/problems/count-pairs-with-xor-in-a-range/)
- 🔴 [1938. Maximum Genetic Difference Query](https://leetcode.com/problems/maximum-genetic-difference-query/)
- 🟢 [2932. Maximum Strong Pair XOR I](https://leetcode.com/problems/maximum-strong-pair-xor-i/)
- 🔴 [2935. Maximum Strong Pair XOR II](https://leetcode.com/problems/maximum-strong-pair-xor-ii/)
- 🔴 [3632. Subarrays with XOR at Least K](https://leetcode.com/problems/subarrays-with-xor-at-least-k/) 🔒
- 🔴 [3845. Maximum Subarray XOR with Bounded Range](https://leetcode.com/problems/maximum-subarray-xor-with-bounded-range/)

</details>

<details><summary><b>Trie + DFS</b> (8)</summary>

- 🟡 [211. Design Add and Search Words Data Structure](https://leetcode.com/problems/design-add-and-search-words-data-structure/)
- 🟡 [386. Lexicographical Numbers](https://leetcode.com/problems/lexicographical-numbers/)
- 🔴 [425. Word Squares](https://leetcode.com/problems/word-squares/) 🔒
- 🔴 [642. Design Search Autocomplete System](https://leetcode.com/problems/design-search-autocomplete-system/) 🔒
- 🟡 [676. Implement Magic Dictionary](https://leetcode.com/problems/implement-magic-dictionary/)
- 🟡 [1233. Remove Sub-Folders from the Filesystem](https://leetcode.com/problems/remove-sub-folders-from-the-filesystem/)
- 🟡 [1858. Longest Word With All Prefixes](https://leetcode.com/problems/longest-word-with-all-prefixes/) 🔒
- 🔴 [2479. Maximum XOR of Two Non-Overlapping Subtrees](https://leetcode.com/problems/maximum-xor-of-two-non-overlapping-subtrees/) 🔒

</details>

<details><summary><b>Trie Basics</b> (1)</summary>

- 🟡 [208. Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/)

</details>

<details><summary><b>Trie + Grid Backtracking</b> (1)</summary>

- 🔴 [212. Word Search II](https://leetcode.com/problems/word-search-ii/)

</details>

## Segment Tree / Fenwick Tree / Ordered Set

*Range queries with updates, counting smaller elements.* — 102 problems

<details><summary><b>Segment Tree</b> (82)</summary>

- 🟡 [307. Range Sum Query - Mutable](https://leetcode.com/problems/range-sum-query-mutable/)
- 🟡 [308. Range Sum Query 2D - Mutable](https://leetcode.com/problems/range-sum-query-2d-mutable/) 🔒
- 🔴 [315. Count of Smaller Numbers After Self](https://leetcode.com/problems/count-of-smaller-numbers-after-self/)
- 🔴 [327. Count of Range Sum](https://leetcode.com/problems/count-of-range-sum/)
- 🟡 [406. Queue Reconstruction by Height](https://leetcode.com/problems/queue-reconstruction-by-height/)
- 🔴 [493. Reverse Pairs](https://leetcode.com/problems/reverse-pairs/)
- 🟡 [673. Number of Longest Increasing Subsequence](https://leetcode.com/problems/number-of-longest-increasing-subsequence/)
- 🔴 [683. K Empty Slots](https://leetcode.com/problems/k-empty-slots/) 🔒
- 🔴 [699. Falling Squares](https://leetcode.com/problems/falling-squares/)
- 🔴 [715. Range Module](https://leetcode.com/problems/range-module/)
- 🟡 [729. My Calendar I](https://leetcode.com/problems/my-calendar-i/)
- 🟡 [731. My Calendar II](https://leetcode.com/problems/my-calendar-ii/)
- 🔴 [732. My Calendar III](https://leetcode.com/problems/my-calendar-iii/)
- 🔴 [850. Rectangle Area II](https://leetcode.com/problems/rectangle-area-ii/)
- 🔴 [1157. Online Majority Element In Subarray](https://leetcode.com/problems/online-majority-element-in-subarray/)
- 🟡 [1395. Count Number of Teams](https://leetcode.com/problems/count-number-of-teams/)
- 🔴 [1505. Minimum Possible Integer After at Most K Adjacent Swaps On Digits](https://leetcode.com/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/)
- 🔴 [1521. Find a Value of a Mysterious Function Closest to Target](https://leetcode.com/problems/find-a-value-of-a-mysterious-function-closest-to-target/)
- 🔴 [1622. Fancy Sequence](https://leetcode.com/problems/fancy-sequence/)
- 🔴 [1649. Create Sorted Array through Instructions](https://leetcode.com/problems/create-sorted-array-through-instructions/)
- 🔴 [1687. Delivering Boxes from Storage to Ports](https://leetcode.com/problems/delivering-boxes-from-storage-to-ports/)
- 🟡 [2031. Count Subarrays With More Ones Than Zeros](https://leetcode.com/problems/count-subarrays-with-more-ones-than-zeros/) 🔒
- 🟡 [2080. Range Frequency Queries](https://leetcode.com/problems/range-frequency-queries/)
- 🔴 [2158. Amount of New Area Painted Each Day](https://leetcode.com/problems/amount-of-new-area-painted-each-day/) 🔒
- 🔴 [2179. Count Good Triplets in an Array](https://leetcode.com/problems/count-good-triplets-in-an-array/)
- 🔴 [2213. Longest Substring of One Repeating Character](https://leetcode.com/problems/longest-substring-of-one-repeating-character/)
- 🔴 [2276. Count Integers in Intervals](https://leetcode.com/problems/count-integers-in-intervals/)
- 🔴 [2286. Booking Concert Tickets in Groups](https://leetcode.com/problems/booking-concert-tickets-in-groups/)
- 🔴 [2407. Longest Increasing Subsequence II](https://leetcode.com/problems/longest-increasing-subsequence-ii/)
- 🔴 [2426. Number of Pairs Satisfying Inequality](https://leetcode.com/problems/number-of-pairs-satisfying-inequality/)
- 🔴 [2519. Count the Number of K-Big Indices](https://leetcode.com/problems/count-the-number-of-k-big-indices/) 🔒
- 🔴 [2569. Handling Sum Queries After Update](https://leetcode.com/problems/handling-sum-queries-after-update/)
- 🔴 [2659. Make Array Empty](https://leetcode.com/problems/make-array-empty/)
- 🔴 [2736. Maximum Sum Queries](https://leetcode.com/problems/maximum-sum-queries/)
- 🟡 [2907. Maximum Profitable Triplets With Increasing Prices I](https://leetcode.com/problems/maximum-profitable-triplets-with-increasing-prices-i/) 🔒
- 🟢 [2913. Subarrays Distinct Element Sum of Squares I](https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-i/)
- 🔴 [2916. Subarrays Distinct Element Sum of Squares II](https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-ii/)
- 🔴 [2921. Maximum Profitable Triplets With Increasing Prices II](https://leetcode.com/problems/maximum-profitable-triplets-with-increasing-prices-ii/) 🔒
- 🔴 [2926. Maximum Balanced Subsequence Sum](https://leetcode.com/problems/maximum-balanced-subsequence-sum/)
- 🔴 [2940. Find Building Where Alice and Bob Can Meet](https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/)
- 🔴 [3072. Distribute Elements Into Two Arrays II](https://leetcode.com/problems/distribute-elements-into-two-arrays-ii/)
- 🟡 [3109. Find the Index of Permutation](https://leetcode.com/problems/find-the-index-of-permutation/) 🔒
- 🔴 [3117. Minimum Sum of Values by Dividing Array](https://leetcode.com/problems/minimum-sum-of-values-by-dividing-array/)
- 🔴 [3161. Block Placement Queries](https://leetcode.com/problems/block-placement-queries/)
- 🔴 [3165. Maximum Sum of Subsequence With Non-adjacent Elements](https://leetcode.com/problems/maximum-sum-of-subsequence-with-non-adjacent-elements/)
- 🔴 [3171. Find Subarray With Bitwise OR Closest to K](https://leetcode.com/problems/find-subarray-with-bitwise-or-closest-to-k/)
- 🔴 [3187. Peaks in Array](https://leetcode.com/problems/peaks-in-array/)
- 🔴 [3209. Number of Subarrays With AND Value of K](https://leetcode.com/problems/number-of-subarrays-with-and-value-of-k/)
- 🟡 [3380. Maximum Area Rectangle With Point Constraints I](https://leetcode.com/problems/maximum-area-rectangle-with-point-constraints-i/)
- 🔴 [3382. Maximum Area Rectangle With Point Constraints II](https://leetcode.com/problems/maximum-area-rectangle-with-point-constraints-ii/)
- 🔴 [3410. Maximize Subarray Sum After Removing All Occurrences of One Element](https://leetcode.com/problems/maximize-subarray-sum-after-removing-all-occurrences-of-one-element/)
- 🔴 [3420. Count Non-Decreasing Subarrays After K Operations](https://leetcode.com/problems/count-non-decreasing-subarrays-after-k-operations/)
- 🔴 [3454. Separate Squares II](https://leetcode.com/problems/separate-squares-ii/)
- 🟢 [3477. Fruits Into Baskets II](https://leetcode.com/problems/fruits-into-baskets-ii/)
- 🟡 [3479. Fruits Into Baskets III](https://leetcode.com/problems/fruits-into-baskets-iii/)
- 🔴 [3480. Maximize Subarrays After Removing One Conflicting Pair](https://leetcode.com/problems/maximize-subarrays-after-removing-one-conflicting-pair/)
- 🔴 [3501. Maximize Active Section with Trade II](https://leetcode.com/problems/maximize-active-section-with-trade-ii/)
- 🔴 [3515. Shortest Path in a Weighted Tree](https://leetcode.com/problems/shortest-path-in-a-weighted-tree/)
- 🟡 [3520. Minimum Threshold for Inversion Pairs Count](https://leetcode.com/problems/minimum-threshold-for-inversion-pairs-count/) 🔒
- 🔴 [3525. Find X Value of Array II](https://leetcode.com/problems/find-x-value-of-array-ii/)
- 🔴 [3569. Maximize Count of Distinct Primes After Split](https://leetcode.com/problems/maximize-count-of-distinct-primes-after-split/)
- 🔴 [3605. Minimum Stability Factor of Array](https://leetcode.com/problems/minimum-stability-factor-of-array/)
- 🔴 [3624. Number of Integers With Popcount-Depth Equal to K II](https://leetcode.com/problems/number-of-integers-with-popcount-depth-equal-to-k-ii/)
- 🔴 [3691. Maximum Total Subarray Value II](https://leetcode.com/problems/maximum-total-subarray-value-ii/)
- 🟡 [3719. Longest Balanced Subarray I](https://leetcode.com/problems/longest-balanced-subarray-i/)
- 🔴 [3721. Longest Balanced Subarray II](https://leetcode.com/problems/longest-balanced-subarray-ii/)
- 🟡 [3737. Count Subarrays With Majority Element I](https://leetcode.com/problems/count-subarrays-with-majority-element-i/)
- 🔴 [3739. Count Subarrays With Majority Element II](https://leetcode.com/problems/count-subarrays-with-majority-element-ii/)
- 🔴 [3762. Minimum Operations to Equalize Subarrays](https://leetcode.com/problems/minimum-operations-to-equalize-subarrays/)
- 🔴 [3768. Minimum Inversion Count in Subarrays of Fixed Length](https://leetcode.com/problems/minimum-inversion-count-in-subarrays-of-fixed-length/)
- 🔴 [3777. Minimum Deletions to Make Alternating Substring](https://leetcode.com/problems/minimum-deletions-to-make-alternating-substring/)
- 🔴 [3841. Palindromic Path Queries in a Tree](https://leetcode.com/problems/palindromic-path-queries-in-a-tree/)
- 🔴 [3901. Good Subsequence Queries](https://leetcode.com/problems/good-subsequence-queries/)
- 🔴 [3915. Maximum Sum of Alternating Subsequence With Distance at Least K](https://leetcode.com/problems/maximum-sum-of-alternating-subsequence-with-distance-at-least-k/)
- 🔴 [3930. Power Update After K-th Largest Insertion II](https://leetcode.com/problems/power-update-after-k-th-largest-insertion-ii/) 🔒
- 🟡 [3935. Power Update After K-th Largest Insertion I](https://leetcode.com/problems/power-update-after-k-th-largest-insertion-i/) 🔒
- 🟡 [4011. Count Subarrays With Even Odd Ratio I](https://leetcode.com/problems/count-subarrays-with-even-odd-ratio-i/)
- 🔴 [4013. Count Subarrays With Even Odd Ratio II](https://leetcode.com/problems/count-subarrays-with-even-odd-ratio-ii/)
- 🔴 [4017. Peaks in Array II](https://leetcode.com/problems/peaks-in-array-ii/)
- 🔴 [4051. Count Subarrays with Distant Sums](https://leetcode.com/problems/count-subarrays-with-distant-sums/)
- 🔴 [4055. Count Shadow Pairs II](https://leetcode.com/problems/count-shadow-pairs-ii/)
- 🟡 [4099. Minimum Operations to Sort With Locked Indices](https://leetcode.com/problems/minimum-operations-to-sort-with-locked-indices/)

</details>

<details><summary><b>Other Range Structures</b> (9)</summary>

- 🟡 [654. Maximum Binary Tree](https://leetcode.com/problems/maximum-binary-tree/)
- 🟡 [1130. Minimum Cost Tree From Leaf Values](https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/)
- 🟡 [1146. Snapshot Array](https://leetcode.com/problems/snapshot-array/)
- 🔴 [1714. Sum Of Special Evenly-Spaced Elements In Array](https://leetcode.com/problems/sum-of-special-evenly-spaced-elements-in-array/) 🔒
- 🟡 [1756. Design Most Recently Used Queue](https://leetcode.com/problems/design-most-recently-used-queue/) 🔒
- 🔴 [1793. Maximum Score of a Good Subarray](https://leetcode.com/problems/maximum-score-of-a-good-subarray/)
- 🟡 [1856. Maximum Subarray Min-Product](https://leetcode.com/problems/maximum-subarray-min-product/)
- 🟡 [1950. Maximum of Minimum Values in All Subarrays](https://leetcode.com/problems/maximum-of-minimum-values-in-all-subarrays/) 🔒
- 🔴 [3500. Minimum Cost to Divide Array Into Subarrays](https://leetcode.com/problems/minimum-cost-to-divide-array-into-subarrays/)

</details>

<details><summary><b>Fenwick Tree (BIT)</b> (9)</summary>

- 🟡 [1409. Queries on a Permutation With Key](https://leetcode.com/problems/queries-on-a-permutation-with-key/)
- 🔴 [1964. Find the Longest Valid Obstacle Course at Each Position](https://leetcode.com/problems/find-the-longest-valid-obstacle-course-at-each-position/)
- 🔴 [2193. Minimum Number of Moves to Make Palindrome](https://leetcode.com/problems/minimum-number-of-moves-to-make-palindrome/)
- 🟡 [2250. Count Number of Rectangles Containing Each Point](https://leetcode.com/problems/count-number-of-rectangles-containing-each-point/)
- 🔴 [2552. Count Increasing Quadruplets](https://leetcode.com/problems/count-increasing-quadruplets/)
- 🔴 [3009. Maximum Number of Intersections on the Chart](https://leetcode.com/problems/maximum-number-of-intersections-on-the-chart/) 🔒
- 🔴 [3245. Alternating Groups III](https://leetcode.com/problems/alternating-groups-iii/)
- 🔴 [3671. Sum of Beautiful Subsequences](https://leetcode.com/problems/sum-of-beautiful-subsequences/)
- 🔴 [3962. Maximum Subarray Sum After at Most K Swaps](https://leetcode.com/problems/maximum-subarray-sum-after-at-most-k-swaps/)

</details>

<details><summary><b>Ordered Set / Sorted Container</b> (2)</summary>

- 🔴 [1825. Finding MK Average](https://leetcode.com/problems/finding-mk-average/)
- 🟡 [3073. Maximum Increasing Triplet Value](https://leetcode.com/problems/maximum-increasing-triplet-value/) 🔒

</details>

## String Matching & Hashing

*KMP, Z-function, rolling hash, suffix arrays, Manacher.* — 72 problems

<details><summary><b>Rolling Hash</b> (32)</summary>

- 🔴 [336. Palindrome Pairs](https://leetcode.com/problems/palindrome-pairs/)
- 🟡 [535. Encode and Decode TinyURL](https://leetcode.com/problems/encode-and-decode-tinyurl/)
- 🟡 [694. Number of Distinct Islands](https://leetcode.com/problems/number-of-distinct-islands/) 🔒
- 🟢 [705. Design HashSet](https://leetcode.com/problems/design-hashset/)
- 🟢 [706. Design HashMap](https://leetcode.com/problems/design-hashmap/)
- 🔴 [711. Number of Distinct Islands II](https://leetcode.com/problems/number-of-distinct-islands-ii/) 🔒
- 🟡 [718. Maximum Length of Repeated Subarray](https://leetcode.com/problems/maximum-length-of-repeated-subarray/)
- 🔴 [1147. Longest Chunked Palindrome Decomposition](https://leetcode.com/problems/longest-chunked-palindrome-decomposition/)
- 🟡 [1461. Check If a String Contains All Binary Codes of Size K](https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/)
- 🟡 [1554. Strings Differ by One Character](https://leetcode.com/problems/strings-differ-by-one-character/) 🔒
- 🔴 [1948. Delete Duplicate Folders in System](https://leetcode.com/problems/delete-duplicate-folders-in-system/)
- 🔴 [2156. Find Substring With Given Hash Value](https://leetcode.com/problems/find-substring-with-given-hash-value/)
- 🟡 [2168. Unique Substrings With Equal Digit Frequency](https://leetcode.com/problems/unique-substrings-with-equal-digit-frequency/) 🔒
- 🟡 [2261. K Divisible Elements Subarrays](https://leetcode.com/problems/k-divisible-elements-subarrays/)
- 🔴 [2430. Maximum Deletions on a String](https://leetcode.com/problems/maximum-deletions-on-a-string/)
- 🟡 [3023. Find Pattern in Infinite Stream I](https://leetcode.com/problems/find-pattern-in-infinite-stream-i/) 🔒
- 🟡 [3029. Minimum Time to Revert Word to Initial State I](https://leetcode.com/problems/minimum-time-to-revert-word-to-initial-state-i/)
- 🔴 [3031. Minimum Time to Revert Word to Initial State II](https://leetcode.com/problems/minimum-time-to-revert-word-to-initial-state-ii/)
- 🟡 [3034. Number of Subarrays That Match a Pattern I](https://leetcode.com/problems/number-of-subarrays-that-match-a-pattern-i/)
- 🔴 [3036. Number of Subarrays That Match a Pattern II](https://leetcode.com/problems/number-of-subarrays-that-match-a-pattern-ii/)
- 🔴 [3037. Find Pattern in Infinite Stream II](https://leetcode.com/problems/find-pattern-in-infinite-stream-ii/) 🔒
- 🟢 [3042. Count Prefix and Suffix Pairs I](https://leetcode.com/problems/count-prefix-and-suffix-pairs-i/)
- 🟡 [3135. Equalize Strings by Adding or Removing Characters at Ends](https://leetcode.com/problems/equalize-strings-by-adding-or-removing-characters-at-ends/) 🔒
- 🟡 [3291. Minimum Number of Valid Strings to Form Target I](https://leetcode.com/problems/minimum-number-of-valid-strings-to-form-target-i/)
- 🔴 [3292. Minimum Number of Valid Strings to Form Target II](https://leetcode.com/problems/minimum-number-of-valid-strings-to-form-target-ii/)
- 🔴 [3327. Check if DFS Strings Are Palindromes](https://leetcode.com/problems/check-if-dfs-strings-are-palindromes/)
- 🟡 [3529. Count Cells in Overlapping Horizontal and Vertical Substrings](https://leetcode.com/problems/count-cells-in-overlapping-horizontal-and-vertical-substrings/)
- 🔴 [3985. Palindromic Subarray Sum](https://leetcode.com/problems/palindromic-subarray-sum/)
- 🟡 [3991. Sort Array Using Prefix Reversals](https://leetcode.com/problems/sort-array-using-prefix-reversals/) 🔒
- 🔴 [4033. Valid K-Unique Subarrays I](https://leetcode.com/problems/valid-k-unique-subarrays-i/)
- 🔴 [4042. Valid K-Unique Subarrays II](https://leetcode.com/problems/valid-k-unique-subarrays-ii/) 🔒
- 🔴 [4109. Count Valid Suffix Sorts II](https://leetcode.com/problems/count-valid-suffix-sorts-ii/)

</details>

<details><summary><b>String Matching</b> (19)</summary>

- 🟡 [616. Add Bold Tag in String](https://leetcode.com/problems/add-bold-tag-in-string/) 🔒
- 🟡 [758. Bold Words in String](https://leetcode.com/problems/bold-words-in-string/) 🔒
- 🟢 [796. Rotate String](https://leetcode.com/problems/rotate-string/)
- 🔴 [899. Orderly Queue](https://leetcode.com/problems/orderly-queue/)
- 🟡 [1023. Camelcase Matching](https://leetcode.com/problems/camelcase-matching/)
- 🔴 [1032. Stream of Characters](https://leetcode.com/problems/stream-of-characters/)
- 🟢 [1065. Index Pairs of a String](https://leetcode.com/problems/index-pairs-of-a-string/) 🔒
- 🔴 [1163. Last Substring in Lexicographical Order](https://leetcode.com/problems/last-substring-in-lexicographical-order/)
- 🔴 [1397. Find All Good Strings](https://leetcode.com/problems/find-all-good-strings/)
- 🟢 [1408. String Matching in an Array](https://leetcode.com/problems/string-matching-in-an-array/)
- 🟢 [1455. Check If a Word Occurs As a Prefix of Any Word in a Sentence](https://leetcode.com/problems/check-if-a-word-occurs-as-a-prefix-of-any-word-in-a-sentence/)
- 🟢 [1668. Maximum Repeating Substring](https://leetcode.com/problems/maximum-repeating-substring/)
- 🟢 [2185. Counting Words With a Given Prefix](https://leetcode.com/problems/counting-words-with-a-given-prefix/)
- 🔴 [2301. Match Substring After Replacement](https://leetcode.com/problems/match-substring-after-replacement/)
- 🔴 [2851. String Transformation](https://leetcode.com/problems/string-transformation/)
- 🟢 [3407. Substring Matching Pattern](https://leetcode.com/problems/substring-matching-pattern/)
- 🔴 [3455. Shortest Matching Substring](https://leetcode.com/problems/shortest-matching-substring/)
- 🔴 [3474. Lexicographically Smallest Generated String](https://leetcode.com/problems/lexicographically-smallest-generated-string/)
- 🔴 [4105. Repeated String Match II](https://leetcode.com/problems/repeated-string-match-ii/)

</details>

<details><summary><b>KMP</b> (10)</summary>

- 🟢 [28. Find the Index of the First Occurrence in a String](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/)
- 🔴 [214. Shortest Palindrome](https://leetcode.com/problems/shortest-palindrome/)
- 🟢 [459. Repeated Substring Pattern](https://leetcode.com/problems/repeated-substring-pattern/)
- 🟡 [686. Repeated String Match](https://leetcode.com/problems/repeated-string-match/)
- 🔴 [1392. Longest Happy Prefix](https://leetcode.com/problems/longest-happy-prefix/)
- 🟡 [1764. Form Array by Concatenating Subarrays of Another Array](https://leetcode.com/problems/form-array-by-concatenating-subarrays-of-another-array/)
- 🔴 [2223. Sum of Scores of Built Strings](https://leetcode.com/problems/sum-of-scores-of-built-strings/)
- 🟡 [3006. Find Beautiful Indices in the Given Array I](https://leetcode.com/problems/find-beautiful-indices-in-the-given-array-i/)
- 🔴 [3008. Find Beautiful Indices in the Given Array II](https://leetcode.com/problems/find-beautiful-indices-in-the-given-array-ii/)
- 🔴 [3303. Find the Occurrence of First Almost Equal Substring](https://leetcode.com/problems/find-the-occurrence-of-first-almost-equal-substring/)

</details>

<details><summary><b>Suffix Structures</b> (7)</summary>

- 🟡 [1062. Longest Repeating Substring](https://leetcode.com/problems/longest-repeating-substring/) 🔒
- 🔴 [1316. Distinct Echo Substrings](https://leetcode.com/problems/distinct-echo-substrings/)
- 🟡 [1698. Number of Distinct Substrings in a String](https://leetcode.com/problems/number-of-distinct-substrings-in-a-string/) 🔒
- 🔴 [1923. Longest Common Subpath](https://leetcode.com/problems/longest-common-subpath/)
- 🔴 [3213. Construct String with Minimum Cost](https://leetcode.com/problems/construct-string-with-minimum-cost/)
- 🔴 [3735. Lexicographically Smallest String After Reverse II](https://leetcode.com/problems/lexicographically-smallest-string-after-reverse-ii/) 🔒
- 🔴 [3934. Smallest Unique Subarray](https://leetcode.com/problems/smallest-unique-subarray/)

</details>

<details><summary><b>Z-function</b> (3)</summary>

- 🟡 [187. Repeated DNA Sequences](https://leetcode.com/problems/repeated-dna-sequences/)
- 🔴 [1044. Longest Duplicate Substring](https://leetcode.com/problems/longest-duplicate-substring/)
- 🔴 [3045. Count Prefix and Suffix Pairs II](https://leetcode.com/problems/count-prefix-and-suffix-pairs-ii/)

</details>

<details><summary><b>Palindromes (Manacher)</b> (1)</summary>

- 🔴 [1960. Maximum Product of the Length of Two Palindromic Substrings](https://leetcode.com/problems/maximum-product-of-the-length-of-two-palindromic-substrings/)

</details>

## Bit Manipulation

*XOR tricks, bit counting, masks, powers of two.* — 118 problems

<details><summary><b>Bit Tricks</b> (92)</summary>

- 🟡 [29. Divide Two Integers](https://leetcode.com/problems/divide-two-integers/)
- 🟢 [67. Add Binary](https://leetcode.com/problems/add-binary/)
- 🟡 [137. Single Number II](https://leetcode.com/problems/single-number-ii/)
- 🟢 [190. Reverse Bits](https://leetcode.com/problems/reverse-bits/)
- 🟢 [191. Number of 1 Bits](https://leetcode.com/problems/number-of-1-bits/)
- 🟡 [201. Bitwise AND of Numbers Range](https://leetcode.com/problems/bitwise-and-of-numbers-range/)
- 🟢 [231. Power of Two](https://leetcode.com/problems/power-of-two/)
- 🟡 [260. Single Number III](https://leetcode.com/problems/single-number-iii/)
- 🟢 [266. Palindrome Permutation](https://leetcode.com/problems/palindrome-permutation/) 🔒
- 🟡 [318. Maximum Product of Word Lengths](https://leetcode.com/problems/maximum-product-of-word-lengths/)
- 🟢 [338. Counting Bits](https://leetcode.com/problems/counting-bits/)
- 🟢 [342. Power of Four](https://leetcode.com/problems/power-of-four/)
- 🟢 [389. Find the Difference](https://leetcode.com/problems/find-the-difference/)
- 🟡 [393. UTF-8 Validation](https://leetcode.com/problems/utf-8-validation/)
- 🟢 [405. Convert a Number to Hexadecimal](https://leetcode.com/problems/convert-a-number-to-hexadecimal/)
- 🟢 [461. Hamming Distance](https://leetcode.com/problems/hamming-distance/)
- 🟢 [476. Number Complement](https://leetcode.com/problems/number-complement/)
- 🟡 [477. Total Hamming Distance](https://leetcode.com/problems/total-hamming-distance/)
- 🟢 [645. Set Mismatch](https://leetcode.com/problems/set-mismatch/)
- 🟢 [693. Binary Number with Alternating Bits](https://leetcode.com/problems/binary-number-with-alternating-bits/)
- 🟡 [751. IP to CIDR](https://leetcode.com/problems/ip-to-cidr/) 🔒
- 🟢 [762. Prime Number of Set Bits in Binary Representation](https://leetcode.com/problems/prime-number-of-set-bits-in-binary-representation/)
- 🟡 [779. K-th Symbol in Grammar](https://leetcode.com/problems/k-th-symbol-in-grammar/)
- 🔴 [782. Transform to Chessboard](https://leetcode.com/problems/transform-to-chessboard/)
- 🟡 [861. Score After Flipping Matrix](https://leetcode.com/problems/score-after-flipping-matrix/)
- 🟢 [868. Binary Gap](https://leetcode.com/problems/binary-gap/)
- 🔴 [982. Triples with Bitwise AND Equal To Zero](https://leetcode.com/problems/triples-with-bitwise-and-equal-to-zero/)
- 🟢 [1009. Complement of Base 10 Integer](https://leetcode.com/problems/complement-of-base-10-integer/)
- 🟢 [1018. Binary Prefix Divisible By 5](https://leetcode.com/problems/binary-prefix-divisible-by-5/)
- 🟡 [1256. Encode Number](https://leetcode.com/problems/encode-number/) 🔒
- 🟡 [1318. Minimum Flips to Make a OR b Equal to c](https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/)
- 🟢 [1342. Number of Steps to Reduce a Number to Zero](https://leetcode.com/problems/number-of-steps-to-reduce-a-number-to-zero/)
- 🟢 [1356. Sort Integers by The Number of 1 Bits](https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/)
- 🟡 [1386. Cinema Seat Allocation](https://leetcode.com/problems/cinema-seat-allocation/)
- 🟡 [1404. Number of Steps to Reduce a Number in Binary Representation to One](https://leetcode.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one/)
- 🔴 [1542. Find Longest Awesome Substring](https://leetcode.com/problems/find-longest-awesome-substring/)
- 🟡 [1558. Minimum Numbers of Function Calls to Make Target Array](https://leetcode.com/problems/minimum-numbers-of-function-calls-to-make-target-array/)
- 🟡 [1680. Concatenation of Consecutive Binary Numbers](https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/)
- 🟢 [1684. Count the Number of Consistent Strings](https://leetcode.com/problems/count-the-number-of-consistent-strings/)
- 🟢 [2032. Two Out of Three](https://leetcode.com/problems/two-out-of-three/)
- 🟡 [2128. Remove All Ones With Row and Column Flips](https://leetcode.com/problems/remove-all-ones-with-row-and-column-flips/) 🔒
- 🟡 [2135. Count Words Obtained After Adding a Letter](https://leetcode.com/problems/count-words-obtained-after-adding-a-letter/)
- 🟢 [2206. Divide Array Into Equal Pairs](https://leetcode.com/problems/divide-array-into-equal-pairs/)
- 🟢 [2220. Minimum Bit Flips to Convert Number](https://leetcode.com/problems/minimum-bit-flips-to-convert-number/)
- 🟡 [2275. Largest Combination With Bitwise AND Greater Than Zero](https://leetcode.com/problems/largest-combination-with-bitwise-and-greater-than-zero/)
- 🔴 [2306. Naming a Company](https://leetcode.com/problems/naming-a-company/)
- 🟢 [2351. First Letter to Appear Twice](https://leetcode.com/problems/first-letter-to-appear-twice/)
- 🟡 [2419. Longest Subarray With Maximum Bitwise AND](https://leetcode.com/problems/longest-subarray-with-maximum-bitwise-and/)
- 🟢 [2506. Count Pairs Of Similar Strings](https://leetcode.com/problems/count-pairs-of-similar-strings/)
- 🟡 [2546. Apply Bitwise Operations to Make Strings Equal](https://leetcode.com/problems/apply-bitwise-operations-to-make-strings-equal/)
- 🟡 [2568. Minimum Impossible OR](https://leetcode.com/problems/minimum-impossible-or/)
- 🟢 [2595. Number of Even and Odd Bits](https://leetcode.com/problems/number-of-even-and-odd-bits/)
- 🟡 [2657. Find the Prefix Common Array of Two Arrays](https://leetcode.com/problems/find-the-prefix-common-array-of-two-arrays/)
- 🔴 [2732. Find a Good Subset of the Matrix](https://leetcode.com/problems/find-a-good-subset-of-the-matrix/)
- 🟡 [2749. Minimum Operations to Make the Integer Zero](https://leetcode.com/problems/minimum-operations-to-make-the-integer-zero/)
- 🟡 [2802. Find The K-th Lucky Number](https://leetcode.com/problems/find-the-k-th-lucky-number/) 🔒
- 🔴 [2835. Minimum Operations to Form Subsequence With Target Sum](https://leetcode.com/problems/minimum-operations-to-form-subsequence-with-target-sum/)
- 🟡 [2857. Count Pairs of Points With Distance k](https://leetcode.com/problems/count-pairs-of-points-with-distance-k/)
- 🟢 [2859. Sum of Values at Indices With K Set Bits](https://leetcode.com/problems/sum-of-values-at-indices-with-k-set-bits/)
- 🟢 [2869. Minimum Operations to Collect Elements](https://leetcode.com/problems/minimum-operations-to-collect-elements/)
- 🟡 [2871. Split Array Into Maximum Number of Subarrays](https://leetcode.com/problems/split-array-into-maximum-number-of-subarrays/)
- 🔴 [2897. Apply Operations on Array to Maximize Sum of Squares](https://leetcode.com/problems/apply-operations-on-array-to-maximize-sum-of-squares/)
- 🟢 [2917. Find the K-or of an Array](https://leetcode.com/problems/find-the-k-or-of-an-array/)
- 🟢 [2980. Check if Bitwise OR Has Trailing Zeros](https://leetcode.com/problems/check-if-bitwise-or-has-trailing-zeros/)
- 🟡 [3011. Find if Array Can Be Sorted](https://leetcode.com/problems/find-if-array-can-be-sorted/)
- 🔴 [3022. Minimize OR of Remaining Elements Using Operations](https://leetcode.com/problems/minimize-or-of-remaining-elements-using-operations/)
- 🟡 [3064. Guess the Number Using Bitwise Questions I](https://leetcode.com/problems/guess-the-number-using-bitwise-questions-i/) 🔒
- 🟡 [3094. Guess the Number Using Bitwise Questions II](https://leetcode.com/problems/guess-the-number-using-bitwise-questions-ii/) 🔒
- 🟡 [3133. Minimum Array End](https://leetcode.com/problems/minimum-array-end/)
- 🟢 [3173. Bitwise OR of Adjacent Elements](https://leetcode.com/problems/bitwise-or-of-adjacent-elements/) 🔒
- 🟢 [3226. Number of Bit Changes to Make Two Integers Equal](https://leetcode.com/problems/number-of-bit-changes-to-make-two-integers-equal/)
- 🟢 [3304. Find the K-th Character in String Game I](https://leetcode.com/problems/find-the-k-th-character-in-string-game-i/)
- 🔴 [3307. Find the K-th Character in String Game II](https://leetcode.com/problems/find-the-k-th-character-in-string-game-ii/)
- 🟡 [3309. Maximum Possible Number by Binary Concatenation](https://leetcode.com/problems/maximum-possible-number-by-binary-concatenation/)
- 🟢 [3314. Construct the Minimum Bitwise Array I](https://leetcode.com/problems/construct-the-minimum-bitwise-array-i/)
- 🟡 [3315. Construct the Minimum Bitwise Array II](https://leetcode.com/problems/construct-the-minimum-bitwise-array-ii/)
- 🟢 [3370. Smallest Number With All Set Bits](https://leetcode.com/problems/smallest-number-with-all-set-bits/)
- 🔴 [3495. Minimum Operations to Make Array Elements Zero](https://leetcode.com/problems/minimum-operations-to-make-array-elements-zero/)
- 🟡 [3566. Partition Array into Two Equal Product Subsets](https://leetcode.com/problems/partition-array-into-two-equal-product-subsets/)
- 🟡 [3595. Once Twice](https://leetcode.com/problems/once-twice/) 🔒
- 🟡 [3644. Maximum K to Sort a Permutation](https://leetcode.com/problems/maximum-k-to-sort-a-permutation/)
- 🟢 [3674. Minimum Operations to Equalize Array](https://leetcode.com/problems/minimum-operations-to-equalize-array/)
- 🔴 [3677. Count Binary Palindromic Numbers](https://leetcode.com/problems/count-binary-palindromic-numbers/)
- 🟢 [3688. Bitwise OR of Even Numbers in an Array](https://leetcode.com/problems/bitwise-or-of-even-numbers-in-an-array/)
- 🔴 [3806. Maximum Bitwise AND After Increment Operations](https://leetcode.com/problems/maximum-bitwise-and-after-increment-operations/)
- 🔴 [3821. Find Nth Smallest Integer With K One Bits](https://leetcode.com/problems/find-nth-smallest-integer-with-k-one-bits/)
- 🟢 [3827. Count Monobit Integers](https://leetcode.com/problems/count-monobit-integers/)
- 🟡 [3858. Minimum Bitwise OR From Grid](https://leetcode.com/problems/minimum-bitwise-or-from-grid/)
- 🟢 [3950. Exactly One Consecutive Set Bits Pair](https://leetcode.com/problems/exactly-one-consecutive-set-bits-pair/)
- 🔴 [3990. Create Grid With Exactly K Paths II](https://leetcode.com/problems/create-grid-with-exactly-k-paths-ii/) 🔒
- 🟡 [4036. Lexicographically Largest String After Pair Transformations](https://leetcode.com/problems/lexicographically-largest-string-after-pair-transformations/)
- 🔴 [4059. Lexicographically Largest Power Array](https://leetcode.com/problems/lexicographically-largest-power-array/)

</details>

<details><summary><b>XOR Tricks</b> (25)</summary>

- 🟢 [136. Single Number](https://leetcode.com/problems/single-number/)
- 🟢 [268. Missing Number](https://leetcode.com/problems/missing-number/)
- 🔴 [810. Chalkboard XOR Game](https://leetcode.com/problems/chalkboard-xor-game/)
- 🟢 [1486. XOR Operation in an Array](https://leetcode.com/problems/xor-operation-in-an-array/)
- 🟢 [1720. Decode XORed Array](https://leetcode.com/problems/decode-xored-array/)
- 🟡 [1734. Decode XORed Permutation](https://leetcode.com/problems/decode-xored-permutation/)
- 🔴 [1835. Find XOR Sum of All Pairs Bitwise AND](https://leetcode.com/problems/find-xor-sum-of-all-pairs-bitwise-and/)
- 🟡 [2317. Maximum XOR After Operations ](https://leetcode.com/problems/maximum-xor-after-operations/)
- 🟡 [2425. Bitwise XOR of All Pairings](https://leetcode.com/problems/bitwise-xor-of-all-pairings/)
- 🟡 [2429. Minimize XOR](https://leetcode.com/problems/minimize-xor/)
- 🟡 [2433. Find The Original Array of Prefix Xor](https://leetcode.com/problems/find-the-original-array-of-prefix-xor/)
- 🟡 [2527. Find Xor-Beauty of Array](https://leetcode.com/problems/find-xor-beauty-of-array/)
- 🟡 [2564. Substring XOR Queries](https://leetcode.com/problems/substring-xor-queries/)
- 🟡 [2683. Neighboring Bitwise XOR](https://leetcode.com/problems/neighboring-bitwise-xor/)
- 🟡 [2939. Maximum Xor Product](https://leetcode.com/problems/maximum-xor-product/)
- 🟡 [2997. Minimum Number of Operations to Make Array XOR Equal to K](https://leetcode.com/problems/minimum-number-of-operations-to-make-array-xor-equal-to-k/)
- 🟢 [3158. Find the XOR of Numbers Which Appear Twice](https://leetcode.com/problems/find-the-xor-of-numbers-which-appear-twice/)
- 🟢 [3199. Count Triplets with Even XOR Set Bits I](https://leetcode.com/problems/count-triplets-with-even-xor-set-bits-i/) 🔒
- 🟡 [3215. Count Triplets with Even XOR Set Bits II](https://leetcode.com/problems/count-triplets-with-even-xor-set-bits-ii/) 🔒
- 🟡 [3513. Number of Unique XOR Triplets I](https://leetcode.com/problems/number-of-unique-xor-triplets-i/)
- 🟡 [3514. Number of Unique XOR Triplets II](https://leetcode.com/problems/number-of-unique-xor-triplets-ii/)
- 🔴 [3630. Partition Array for Maximum XOR and AND](https://leetcode.com/problems/partition-array-for-maximum-xor-and-and/)
- 🔴 [3681. Maximum XOR of Subsequences](https://leetcode.com/problems/maximum-xor-of-subsequences/)
- 🟡 [3702. Longest Subsequence With Non-Zero Bitwise XOR](https://leetcode.com/problems/longest-subsequence-with-non-zero-bitwise-xor/)
- 🟡 [3849. Maximum Bitwise XOR After Rearrangement](https://leetcode.com/problems/maximum-bitwise-xor-after-rearrangement/)

</details>

<details><summary><b>Bit Arithmetic</b> (1)</summary>

- 🟡 [371. Sum of Two Integers](https://leetcode.com/problems/sum-of-two-integers/)

</details>

## Math & Number Theory

*Primes, GCD, modular arithmetic, combinatorics, geometry, games.* — 343 problems

<details><summary><b>Arithmetic & Digits</b> (210)</summary>

- 🟡 [7. Reverse Integer](https://leetcode.com/problems/reverse-integer/)
- 🟢 [9. Palindrome Number](https://leetcode.com/problems/palindrome-number/)
- 🟡 [12. Integer to Roman](https://leetcode.com/problems/integer-to-roman/)
- 🟢 [13. Roman to Integer](https://leetcode.com/problems/roman-to-integer/)
- 🔴 [60. Permutation Sequence](https://leetcode.com/problems/permutation-sequence/)
- 🟢 [66. Plus One](https://leetcode.com/problems/plus-one/)
- 🟡 [166. Fraction to Recurring Decimal](https://leetcode.com/problems/fraction-to-recurring-decimal/)
- 🟢 [168. Excel Sheet Column Title](https://leetcode.com/problems/excel-sheet-column-title/)
- 🟢 [171. Excel Sheet Column Number](https://leetcode.com/problems/excel-sheet-column-number/)
- 🟡 [172. Factorial Trailing Zeroes](https://leetcode.com/problems/factorial-trailing-zeroes/)
- 🟢 [263. Ugly Number](https://leetcode.com/problems/ugly-number/)
- 🔴 [273. Integer to English Words](https://leetcode.com/problems/integer-to-english-words/)
- 🔴 [296. Best Meeting Point](https://leetcode.com/problems/best-meeting-point/) 🔒
- 🟡 [311. Sparse Matrix Multiplication](https://leetcode.com/problems/sparse-matrix-multiplication/) 🔒
- 🟢 [326. Power of Three](https://leetcode.com/problems/power-of-three/)
- 🟡 [356. Line Reflection](https://leetcode.com/problems/line-reflection/) 🔒
- 🟡 [390. Elimination Game](https://leetcode.com/problems/elimination-game/)
- 🟢 [412. Fizz Buzz](https://leetcode.com/problems/fizz-buzz/)
- 🟢 [415. Add Strings](https://leetcode.com/problems/add-strings/)
- 🟡 [423. Reconstruct Original Digits from English](https://leetcode.com/problems/reconstruct-original-digits-from-english/)
- 🟡 [447. Number of Boomerangs](https://leetcode.com/problems/number-of-boomerangs/)
- 🟡 [453. Minimum Moves to Equal Array Elements](https://leetcode.com/problems/minimum-moves-to-equal-array-elements/)
- 🟡 [462. Minimum Moves to Equal Array Elements II](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/)
- 🔴 [479. Largest Palindrome Product](https://leetcode.com/problems/largest-palindrome-product/)
- 🟢 [492. Construct the Rectangle](https://leetcode.com/problems/construct-the-rectangle/)
- 🟢 [504. Base 7](https://leetcode.com/problems/base-7/)
- 🟢 [507. Perfect Number](https://leetcode.com/problems/perfect-number/)
- 🟡 [537. Complex Number Multiplication](https://leetcode.com/problems/complex-number-multiplication/)
- 🟡 [539. Minimum Time Difference](https://leetcode.com/problems/minimum-time-difference/)
- 🔴 [564. Find the Closest Palindrome](https://leetcode.com/problems/find-the-closest-palindrome/)
- 🟡 [573. Squirrel Simulation](https://leetcode.com/problems/squirrel-simulation/) 🔒
- 🟢 [598. Range Addition II](https://leetcode.com/problems/range-addition-ii/)
- 🟢 [628. Maximum Product of Three Numbers](https://leetcode.com/problems/maximum-product-of-three-numbers/)
- 🟡 [640. Solve the Equation](https://leetcode.com/problems/solve-the-equation/)
- 🔴 [660. Remove 9](https://leetcode.com/problems/remove-9/) 🔒
- 🟡 [667. Beautiful Arrangement II](https://leetcode.com/problems/beautiful-arrangement-ii/)
- 🟢 [728. Self Dividing Numbers](https://leetcode.com/problems/self-dividing-numbers/)
- 🟡 [775. Global and Local Inversions](https://leetcode.com/problems/global-and-local-inversions/)
- 🟡 [789. Escape The Ghosts](https://leetcode.com/problems/escape-the-ghosts/)
- 🟢 [800. Similar RGB Color](https://leetcode.com/problems/similar-rgb-color/) 🔒
- 🔴 [829. Consecutive Numbers Sum](https://leetcode.com/problems/consecutive-numbers-sum/)
- 🟡 [840. Magic Squares In Grid](https://leetcode.com/problems/magic-squares-in-grid/)
- 🟡 [869. Reordered Power of 2](https://leetcode.com/problems/reordered-power-of-2/)
- 🔴 [891. Sum of Subsequence Widths](https://leetcode.com/problems/sum-of-subsequence-widths/)
- 🔴 [906. Super Palindromes](https://leetcode.com/problems/super-palindromes/)
- 🟢 [908. Smallest Range I](https://leetcode.com/problems/smallest-range-i/)
- 🔴 [927. Three Equal Parts](https://leetcode.com/problems/three-equal-parts/)
- 🟡 [932. Beautiful Array](https://leetcode.com/problems/beautiful-array/)
- 🟡 [970. Powerful Integers](https://leetcode.com/problems/powerful-integers/)
- 🔴 [972. Equal Rational Numbers](https://leetcode.com/problems/equal-rational-numbers/)
- 🟢 [989. Add to Array-Form of Integer](https://leetcode.com/problems/add-to-array-form-of-integer/)
- 🟡 [1017. Convert to Base -2](https://leetcode.com/problems/convert-to-base-2/)
- 🟡 [1041. Robot Bounded In Circle](https://leetcode.com/problems/robot-bounded-in-circle/)
- 🟢 [1056. Confusing Number](https://leetcode.com/problems/confusing-number/) 🔒
- 🟡 [1073. Adding Two Negabinary Numbers](https://leetcode.com/problems/adding-two-negabinary-numbers/)
- 🟢 [1085. Sum of Digits in the Minimum Number](https://leetcode.com/problems/sum-of-digits-in-the-minimum-number/) 🔒
- 🟢 [1103. Distribute Candies to People](https://leetcode.com/problems/distribute-candies-to-people/)
- 🟢 [1118. Number of Days in a Month](https://leetcode.com/problems/number-of-days-in-a-month/) 🔒
- 🟡 [1131. Maximum of Absolute Value Expression](https://leetcode.com/problems/maximum-of-absolute-value-expression/)
- 🟢 [1134. Armstrong Number](https://leetcode.com/problems/armstrong-number/) 🔒
- 🟢 [1154. Day of the Year](https://leetcode.com/problems/day-of-the-year/)
- 🟢 [1180. Count Substrings with Only One Distinct Letter](https://leetcode.com/problems/count-substrings-with-only-one-distinct-letter/) 🔒
- 🟢 [1185. Day of the Week](https://leetcode.com/problems/day-of-the-week/)
- 🟢 [1228. Missing Number In Arithmetic Progression](https://leetcode.com/problems/missing-number-in-arithmetic-progression/) 🔒
- 🟢 [1252. Cells with Odd Values in a Matrix](https://leetcode.com/problems/cells-with-odd-values-in-a-matrix/)
- 🟢 [1271. Hexspeak](https://leetcode.com/problems/hexspeak/) 🔒
- 🟡 [1276. Number of Burgers with No Waste of Ingredients](https://leetcode.com/problems/number-of-burgers-with-no-waste-of-ingredients/)
- 🟢 [1281. Subtract the Product and Sum of Digits of an Integer](https://leetcode.com/problems/subtract-the-product-and-sum-of-digits-of-an-integer/)
- 🟢 [1295. Find Numbers with Even Number of Digits](https://leetcode.com/problems/find-numbers-with-even-number-of-digits/)
- 🟢 [1304. Find N Unique Integers Sum up to Zero](https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/)
- 🟢 [1317. Convert Integer to the Sum of Two No-Zero Integers](https://leetcode.com/problems/convert-integer-to-the-sum-of-two-no-zero-integers/)
- 🟡 [1344. Angle Between Hands of a Clock](https://leetcode.com/problems/angle-between-hands-of-a-clock/)
- 🟢 [1360. Number of Days Between Two Dates](https://leetcode.com/problems/number-of-days-between-two-dates/)
- 🟢 [1399. Count Largest Group](https://leetcode.com/problems/count-largest-group/)
- 🟢 [1427. Perform String Shifts](https://leetcode.com/problems/perform-string-shifts/) 🔒
- 🟢 [1512. Number of Good Pairs](https://leetcode.com/problems/number-of-good-pairs/)
- 🟡 [1513. Number of Substrings With Only 1s](https://leetcode.com/problems/number-of-substrings-with-only-1s/)
- 🟢 [1518. Water Bottles](https://leetcode.com/problems/water-bottles/)
- 🟡 [1538. Guess the Majority in a Hidden Array](https://leetcode.com/problems/guess-the-majority-in-a-hidden-array/) 🔒
- 🟡 [1551. Minimum Operations to Make Array Equal](https://leetcode.com/problems/minimum-operations-to-make-array-equal/)
- 🟡 [1573. Number of Ways to Split a String](https://leetcode.com/problems/number-of-ways-to-split-a-string/)
- 🟢 [1688. Count of Matches in Tournament](https://leetcode.com/problems/count-of-matches-in-tournament/)
- 🟢 [1716. Calculate Money in Leetcode Bank](https://leetcode.com/problems/calculate-money-in-leetcode-bank/)
- 🟢 [1742. Maximum Number of Balls in a Box](https://leetcode.com/problems/maximum-number-of-balls-in-a-box/)
- 🟡 [1759. Count Number of Homogenous Substrings](https://leetcode.com/problems/count-number-of-homogenous-substrings/)
- 🟡 [1780. Check if Number is a Sum of Powers of Three](https://leetcode.com/problems/check-if-number-is-a-sum-of-powers-of-three/)
- 🟡 [1806. Minimum Number of Operations to Reinitialize a Permutation](https://leetcode.com/problems/minimum-number-of-operations-to-reinitialize-a-permutation/)
- 🟢 [1812. Determine Color of a Chessboard Square](https://leetcode.com/problems/determine-color-of-a-chessboard-square/)
- 🟡 [1814. Count Nice Pairs in an Array](https://leetcode.com/problems/count-nice-pairs-in-an-array/)
- 🟢 [1822. Sign of the Product of an Array](https://leetcode.com/problems/sign-of-the-product-of-an-array/)
- 🟡 [1823. Find the Winner of the Circular Game](https://leetcode.com/problems/find-the-winner-of-the-circular-game/)
- 🟢 [1837. Sum of Digits in Base K](https://leetcode.com/problems/sum-of-digits-in-base-k/)
- 🔴 [1840. Maximum Building Height](https://leetcode.com/problems/maximum-building-height/)
- 🟡 [1860. Incremental Memory Leak](https://leetcode.com/problems/incremental-memory-leak/)
- 🟡 [1904. The Number of Full Rounds You Have Played](https://leetcode.com/problems/the-number-of-full-rounds-you-have-played/)
- 🟡 [1922. Count Good Numbers](https://leetcode.com/problems/count-good-numbers/)
- 🟢 [1925. Count Square Sum Triples](https://leetcode.com/problems/count-square-sum-triples/)
- 🟡 [1999. Smallest Greater Multiple Made of Two Digits](https://leetcode.com/problems/smallest-greater-multiple-made-of-two-digits/) 🔒
- 🟡 [2028. Find Missing Observations](https://leetcode.com/problems/find-missing-observations/)
- 🟡 [2033. Minimum Operations to Make a Uni-Value Grid](https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/)
- 🔴 [2081. Sum of k-Mirror Numbers](https://leetcode.com/problems/sum-of-k-mirror-numbers/)
- 🟢 [2119. A Number After a Double Reversal](https://leetcode.com/problems/a-number-after-a-double-reversal/)
- 🟡 [2125. Number of Laser Beams in a Bank](https://leetcode.com/problems/number-of-laser-beams-in-a-bank/)
- 🟡 [2162. Minimum Cost to Set Cooking Time](https://leetcode.com/problems/minimum-cost-to-set-cooking-time/)
- 🟡 [2165. Smallest Value of the Rearranged Number](https://leetcode.com/problems/smallest-value-of-the-rearranged-number/)
- 🟢 [2169. Count Operations to Obtain Zero](https://leetcode.com/problems/count-operations-to-obtain-zero/)
- 🟡 [2177. Find Three Consecutive Integers That Sum to a Given Number](https://leetcode.com/problems/find-three-consecutive-integers-that-sum-to-a-given-number/)
- 🟢 [2180. Count Integers With Even Digit Sum](https://leetcode.com/problems/count-integers-with-even-digit-sum/)
- 🟡 [2217. Find Palindrome With Fixed Length](https://leetcode.com/problems/find-palindrome-with-fixed-length/)
- 🟢 [2235. Add Two Integers](https://leetcode.com/problems/add-two-integers/)
- 🟡 [2240. Number of Ways to Buy Pens and Pencils](https://leetcode.com/problems/number-of-ways-to-buy-pens-and-pencils/)
- 🟡 [2348. Number of Zero-Filled Subarrays](https://leetcode.com/problems/number-of-zero-filled-subarrays/)
- 🟡 [2364. Count Number of Bad Pairs](https://leetcode.com/problems/count-number-of-bad-pairs/)
- 🟢 [2409. Count Days Spent Together](https://leetcode.com/problems/count-days-spent-together/)
- 🟡 [2417. Closest Fair Integer](https://leetcode.com/problems/closest-fair-integer/) 🔒
- 🟡 [2442. Count Number of Distinct Integers After Reverse Operations](https://leetcode.com/problems/count-number-of-distinct-integers-after-reverse-operations/)
- 🟡 [2443. Sum of Number and Its Reverse](https://leetcode.com/problems/sum-of-number-and-its-reverse/)
- 🟡 [2450. Number of Distinct Binary Strings After Applying Operations](https://leetcode.com/problems/number-of-distinct-binary-strings-after-applying-operations/) 🔒
- 🟢 [2455. Average Value of Even Numbers That Are Divisible by Three](https://leetcode.com/problems/average-value-of-even-numbers-that-are-divisible-by-three/)
- 🟢 [2469. Convert the Temperature](https://leetcode.com/problems/convert-the-temperature/)
- 🟢 [2520. Count the Digits That Divide a Number](https://leetcode.com/problems/count-the-digits-that-divide-a-number/)
- 🟢 [2525. Categorize Box According to Criteria](https://leetcode.com/problems/categorize-box-according-to-criteria/)
- 🟢 [2535. Difference Between Element Sum and Digit Sum of an Array](https://leetcode.com/problems/difference-between-element-sum-and-digit-sum-of-an-array/)
- 🟢 [2544. Alternating Digit Sum](https://leetcode.com/problems/alternating-digit-sum/)
- 🟢 [2549. Count Distinct Numbers on Board](https://leetcode.com/problems/count-distinct-numbers-on-board/)
- 🟡 [2550. Count Collisions of Monkeys on a Polygon](https://leetcode.com/problems/count-collisions-of-monkeys-on-a-polygon/)
- 🟡 [2575. Find the Divisibility Array of a String](https://leetcode.com/problems/find-the-divisibility-array-of-a-string/)
- 🟡 [2579. Count Total Number of Colored Cells](https://leetcode.com/problems/count-total-number-of-colored-cells/)
- 🟢 [2582. Pass the Pillow](https://leetcode.com/problems/pass-the-pillow/)
- 🔴 [2647. Color the Triangle Red](https://leetcode.com/problems/color-the-triangle-red/) 🔒
- 🟢 [2651. Calculate Delayed Arrival Time](https://leetcode.com/problems/calculate-delayed-arrival-time/)
- 🟢 [2652. Sum Multiples](https://leetcode.com/problems/sum-multiples/)
- 🟢 [2729. Check if The Number is Fascinating](https://leetcode.com/problems/check-if-the-number-is-fascinating/)
- 🟢 [2739. Total Distance Traveled](https://leetcode.com/problems/total-distance-traveled/)
- 🟢 [2769. Find the Maximum Achievable Number](https://leetcode.com/problems/find-the-maximum-achievable-number/)
- 🟢 [2806. Account Balance After Rounded Purchase](https://leetcode.com/problems/account-balance-after-rounded-purchase/)
- 🟢 [2843.   Count Symmetric Integers](https://leetcode.com/problems/count-symmetric-integers/)
- 🟡 [2849. Determine if a Cell Is Reachable at a Given Time](https://leetcode.com/problems/determine-if-a-cell-is-reachable-at-a-given-time/)
- 🟢 [2894. Divisible and Non-divisible Sums Difference](https://leetcode.com/problems/divisible-and-non-divisible-sums-difference/)
- 🟢 [2946. Matrix Similarity After Cyclic Shifts](https://leetcode.com/problems/matrix-similarity-after-cyclic-shifts/)
- 🟡 [2961. Double Modular Exponentiation](https://leetcode.com/problems/double-modular-exponentiation/)
- 🟢 [2965. Find Missing and Repeated Values](https://leetcode.com/problems/find-missing-and-repeated-values/)
- 🟡 [3001. Minimum Moves to Capture The Queen](https://leetcode.com/problems/minimum-moves-to-capture-the-queen/)
- 🟡 [3021. Alice and Bob Playing Flower Game](https://leetcode.com/problems/alice-and-bob-playing-flower-game/)
- 🟢 [3079. Find the Sum of Encrypted Integers](https://leetcode.com/problems/find-the-sum-of-encrypted-integers/)
- 🟡 [3084. Count Substrings Starting and Ending with Given Character](https://leetcode.com/problems/count-substrings-starting-and-ending-with-given-character/)
- 🟢 [3099. Harshad Number](https://leetcode.com/problems/harshad-number/)
- 🟡 [3100. Water Bottles II](https://leetcode.com/problems/water-bottles-ii/)
- 🟡 [3101. Count Alternating Subarrays](https://leetcode.com/problems/count-alternating-subarrays/)
- 🟡 [3153. Sum of Digit Differences of All Pairs](https://leetcode.com/problems/sum-of-digit-differences-of-all-pairs/)
- 🟢 [3178. Find the Child Who Has the Ball After K Seconds](https://leetcode.com/problems/find-the-child-who-has-the-ball-after-k-seconds/)
- 🟢 [3190. Find Minimum Operations to Make All Elements Divisible by Three](https://leetcode.com/problems/find-minimum-operations-to-make-all-elements-divisible-by-three/)
- 🟢 [3232. Find if Digit Game Can Be Won](https://leetcode.com/problems/find-if-digit-game-can-be-won/)
- 🟢 [3270. Find the Key of the Numbers](https://leetcode.com/problems/find-the-key-of-the-numbers/)
- 🟢 [3274. Check if Two Chessboard Squares Have the Same Color](https://leetcode.com/problems/check-if-two-chessboard-squares-have-the-same-color/)
- 🟢 [3280. Convert Date to Binary](https://leetcode.com/problems/convert-date-to-binary/)
- 🟢 [3289. The Two Sneaky Numbers of Digitville](https://leetcode.com/problems/the-two-sneaky-numbers-of-digitville/)
- 🟢 [3300. Minimum Element After Replacement With Digit Sum](https://leetcode.com/problems/minimum-element-after-replacement-with-digit-sum/)
- 🟢 [3345. Smallest Divisible Digit Product I](https://leetcode.com/problems/smallest-divisible-digit-product-i/)
- 🟢 [3360. Stone Removal Game](https://leetcode.com/problems/stone-removal-game/)
- 🟡 [3404. Count Special Subsequences](https://leetcode.com/problems/count-special-subsequences/)
- 🟡 [3433. Count Mentions Per User](https://leetcode.com/problems/count-mentions-per-user/)
- 🟡 [3443. Maximum Manhattan Distance After K Changes](https://leetcode.com/problems/maximum-manhattan-distance-after-k-changes/)
- 🟡 [3468. Find the Number of Copy Arrays](https://leetcode.com/problems/find-the-number-of-copy-arrays/)
- 🟢 [3492. Maximum Containers on a Ship](https://leetcode.com/problems/maximum-containers-on-a-ship/)
- 🟢 [3512. Minimum Operations to Make Array Sum Divisible by K](https://leetcode.com/problems/minimum-operations-to-make-array-sum-divisible-by-k/)
- 🟢 [3516. Find Closest Person](https://leetcode.com/problems/find-closest-person/)
- 🟢 [3536. Maximum Product of Two Digits](https://leetcode.com/problems/maximum-product-of-two-digits/)
- 🔴 [3549. Multiply Two Polynomials](https://leetcode.com/problems/multiply-two-polynomials/) 🔒
- 🟢 [3550. Smallest Index With Digit Sum Equal to Index](https://leetcode.com/problems/smallest-index-with-digit-sum-equal-to-index/)
- 🟢 [3560. Find Minimum Log Transportation Cost](https://leetcode.com/problems/find-minimum-log-transportation-cost/)
- 🟢 [3602. Hexadecimal and Hexatrigesimal Conversion](https://leetcode.com/problems/hexadecimal-and-hexatrigesimal-conversion/)
- 🔴 [3609. Minimum Moves to Reach Target in Grid](https://leetcode.com/problems/minimum-moves-to-reach-target-in-grid/)
- 🟢 [3622. Check Divisibility by Digit Sum and Product](https://leetcode.com/problems/check-divisibility-by-digit-sum-and-product/)
- 🟡 [3648. Minimum Sensors to Cover Grid](https://leetcode.com/problems/minimum-sensors-to-cover-grid/)
- 🟢 [3663. Find The Least Frequent Digit](https://leetcode.com/problems/find-the-least-frequent-digit/)
- 🟢 [3697. Compute Decimal Representation](https://leetcode.com/problems/compute-decimal-representation/)
- 🟢 [3726. Remove Zeros in Decimal Representation](https://leetcode.com/problems/remove-zeros-in-decimal-representation/)
- 🟢 [3736. Minimum Moves to Equal Array Elements III](https://leetcode.com/problems/minimum-moves-to-equal-array-elements-iii/)
- 🟢 [3754. Concatenate Non-Zero Digits and Multiply by Sum I](https://leetcode.com/problems/concatenate-non-zero-digits-and-multiply-by-sum-i/)
- 🟡 [3761. Minimum Absolute Distance Between Mirror Pairs](https://leetcode.com/problems/minimum-absolute-distance-between-mirror-pairs/)
- 🔴 [3782. Last Remaining Integer After Alternating Deletion Operations](https://leetcode.com/problems/last-remaining-integer-after-alternating-deletion-operations/)
- 🟢 [3783. Mirror Distance of an Integer](https://leetcode.com/problems/mirror-distance-of-an-integer/)
- 🟡 [3790. Smallest All-Ones Multiple](https://leetcode.com/problems/smallest-all-ones-multiple/)
- 🟡 [3792. Sum of Increasing Product Blocks](https://leetcode.com/problems/sum-of-increasing-product-blocks/) 🔒
- 🟡 [3805. Count Caesar Cipher Pairs](https://leetcode.com/problems/count-caesar-cipher-pairs/)
- 🟡 [3817. Good Indices in a Digit String](https://leetcode.com/problems/good-indices-in-a-digit-string/) 🔒
- 🟡 [3848. Check Digitorial Permutation](https://leetcode.com/problems/check-digitorial-permutation/)
- 🟢 [3870. Count Commas in Range](https://leetcode.com/problems/count-commas-in-range/)
- 🟡 [3871. Count Commas in Range II](https://leetcode.com/problems/count-commas-in-range-ii/)
- 🟡 [3874. Valid Subarrays With Exactly One Peak](https://leetcode.com/problems/valid-subarrays-with-exactly-one-peak/) 🔒
- 🟢 [3875. Construct Uniform Parity Array I](https://leetcode.com/problems/construct-uniform-parity-array-i/)
- 🟡 [3876. Construct Uniform Parity Array II](https://leetcode.com/problems/construct-uniform-parity-array-ii/)
- 🔴 [3886. Sum of Sortable Integers](https://leetcode.com/problems/sum-of-sortable-integers/)
- 🟢 [3894. Traffic Signal Color](https://leetcode.com/problems/traffic-signal-color/)
- 🟡 [3895. Count Digit Appearances](https://leetcode.com/problems/count-digit-appearances/)
- 🟢 [3908. Valid Digit Number](https://leetcode.com/problems/valid-digit-number/)
- 🟢 [3945. Digit Frequency Score](https://leetcode.com/problems/digit-frequency-score/)
- 🟡 [3958. Minimum Cost to Split into Ones II](https://leetcode.com/problems/minimum-cost-to-split-into-ones-ii/) 🔒
- 🟢 [3959. Check Good Integer](https://leetcode.com/problems/check-good-integer/)
- 🟡 [3968. Maximum Manhattan Distance After All Moves](https://leetcode.com/problems/maximum-manhattan-distance-after-all-moves/)
- 🟢 [3982. Sum of Integers with Maximum Digit Range](https://leetcode.com/problems/sum-of-integers-with-maximum-digit-range/)
- 🟢 [3986. Number of Elapsed Seconds Between Two Times](https://leetcode.com/problems/number-of-elapsed-seconds-between-two-times/)
- 🟡 [3987. Minimum Total Cost to Process All Elements](https://leetcode.com/problems/minimum-total-cost-to-process-all-elements/)
- 🟢 [3996. Even Number of Knight Moves](https://leetcode.com/problems/even-number-of-knight-moves/)
- 🟡 [4021. Minimum Operations to Make a Rotated Palindrome I](https://leetcode.com/problems/minimum-operations-to-make-a-rotated-palindrome-i/)
- 🔴 [4028. Minimum Operations to Make a Rotated Palindrome II](https://leetcode.com/problems/minimum-operations-to-make-a-rotated-palindrome-ii/) 🔒
- 🟡 [4034. Minimum Bishop Moves to Reach Target](https://leetcode.com/problems/minimum-bishop-moves-to-reach-target/)
- 🟡 [4039. Sum of Decoded Numbers](https://leetcode.com/problems/sum-of-decoded-numbers/)
- 🟢 [4061. Minimum Queen Moves to Reach Target](https://leetcode.com/problems/minimum-queen-moves-to-reach-target/)

</details>

<details><summary><b>Number Theory (Primes / GCD / Mod)</b> (51)</summary>

- 🟡 [204. Count Primes](https://leetcode.com/problems/count-primes/)
- 🟢 [258. Add Digits](https://leetcode.com/problems/add-digits/)
- 🟡 [372. Super Pow](https://leetcode.com/problems/super-pow/)
- 🟡 [592. Fraction Addition and Subtraction](https://leetcode.com/problems/fraction-addition-and-subtraction/)
- 🔴 [780. Reaching Points](https://leetcode.com/problems/reaching-points/)
- 🟡 [866. Prime Palindrome](https://leetcode.com/problems/prime-palindrome/)
- 🟢 [914. X of a Kind in a Deck of Cards](https://leetcode.com/problems/x-of-a-kind-in-a-deck-of-cards/)
- 🟢 [1071. Greatest Common Divisor of Strings](https://leetcode.com/problems/greatest-common-divisor-of-strings/)
- 🟢 [1175. Prime Arrangements](https://leetcode.com/problems/prime-arrangements/)
- 🔴 [1250. Check If It Is a Good Array](https://leetcode.com/problems/check-if-it-is-a-good-array/)
- 🟡 [1362. Closest Divisors](https://leetcode.com/problems/closest-divisors/)
- 🟡 [1390. Four Divisors](https://leetcode.com/problems/four-divisors/)
- 🟡 [1447. Simplified Fractions](https://leetcode.com/problems/simplified-fractions/)
- 🟡 [1492. The kth Factor of n](https://leetcode.com/problems/the-kth-factor-of-n/)
- 🔴 [1808. Maximize Number of Nice Divisors](https://leetcode.com/problems/maximize-number-of-nice-divisors/)
- 🔴 [1819. Number of Different Subsequences GCDs](https://leetcode.com/problems/number-of-different-subsequences-gcds/)
- 🟢 [1952. Three Divisors](https://leetcode.com/problems/three-divisors/)
- 🟢 [1979. Find Greatest Common Divisor of Array](https://leetcode.com/problems/find-greatest-common-divisor-of-array/)
- 🟡 [2001. Number of Pairs of Interchangeable Rectangles](https://leetcode.com/problems/number-of-pairs-of-interchangeable-rectangles/)
- 🔴 [2117. Abbreviating the Product of a Range](https://leetcode.com/problems/abbreviating-the-product-of-a-range/)
- 🔴 [2183. Count Array Pairs Divisible by K](https://leetcode.com/problems/count-array-pairs-divisible-by-k/)
- 🟢 [2413. Smallest Even Multiple](https://leetcode.com/problems/smallest-even-multiple/)
- 🟢 [2427. Number of Common Factors](https://leetcode.com/problems/number-of-common-factors/)
- 🟡 [2447. Number of Subarrays With GCD Equal to K](https://leetcode.com/problems/number-of-subarrays-with-gcd-equal-to-k/)
- 🟡 [2470. Number of Subarrays With LCM Equal to K](https://leetcode.com/problems/number-of-subarrays-with-lcm-equal-to-k/)
- 🟡 [2507. Smallest Value After Replacing With Sum of Prime Factors](https://leetcode.com/problems/smallest-value-after-replacing-with-sum-of-prime-factors/)
- 🟡 [2521. Distinct Prime Factors of Product of Array](https://leetcode.com/problems/distinct-prime-factors-of-product-of-array/)
- 🟡 [2523. Closest Prime Numbers in Range](https://leetcode.com/problems/closest-prime-numbers-in-range/)
- 🔴 [2543. Check if Point Is Reachable](https://leetcode.com/problems/check-if-point-is-reachable/)
- 🔴 [2584. Split the Array to Make Coprime Products](https://leetcode.com/problems/split-the-array-to-make-coprime-products/)
- 🟢 [2614. Prime In Diagonal](https://leetcode.com/problems/prime-in-diagonal/)
- 🟡 [2654. Minimum Number of Operations to Make All Array Elements Equal to 1](https://leetcode.com/problems/minimum-number-of-operations-to-make-all-array-elements-equal-to-1/)
- 🟢 [2748. Number of Beautiful Pairs](https://leetcode.com/problems/number-of-beautiful-pairs/)
- 🟡 [2761. Prime Pairs With Target Sum](https://leetcode.com/problems/prime-pairs-with-target-sum/)
- 🔴 [2862. Maximum Element-Sum of a Complete Subset of Indices](https://leetcode.com/problems/maximum-element-sum-of-a-complete-subset-of-indices/)
- 🟡 [3044. Most Frequent Prime](https://leetcode.com/problems/most-frequent-prime/)
- 🟡 [3115. Maximum Prime Difference](https://leetcode.com/problems/maximum-prime-difference/)
- 🟡 [3233. Find the Count of Numbers Which Are Not Special](https://leetcode.com/problems/find-the-count-of-numbers-which-are-not-special/)
- 🟡 [3334. Find the Maximum Factor Score of Array](https://leetcode.com/problems/find-the-maximum-factor-score-of-array/)
- 🟡 [3556. Sum of Largest Prime Substrings](https://leetcode.com/problems/sum-of-largest-prime-substrings/)
- 🔴 [3574. Maximize Subarray GCD Score](https://leetcode.com/problems/maximize-subarray-gcd-score/)
- 🟢 [3591. Check if Any Element Has Prime Frequency](https://leetcode.com/problems/check-if-any-element-has-prime-frequency/)
- 🟡 [3618. Split Array by Prime Indices](https://leetcode.com/problems/split-array-by-prime-indices/)
- 🟢 [3658. GCD of Odd and Even Sums](https://leetcode.com/problems/gcd-of-odd-and-even-sums/)
- 🟡 [3765. Complete Prime Number](https://leetcode.com/problems/complete-prime-number/)
- 🟡 [3770. Largest Prime from Consecutive Prime Sum](https://leetcode.com/problems/largest-prime-from-consecutive-prime-sum/)
- 🟡 [3918. Sum of Primes Between Number and Its Reverse](https://leetcode.com/problems/sum-of-primes-between-number-and-its-reverse/)
- 🔴 [4005. Minimum Operations to Make Array Equal III](https://leetcode.com/problems/minimum-operations-to-make-array-equal-iii/) 🔒
- 🟢 [4010. Maximize Pair Strength Using GCD](https://leetcode.com/problems/maximize-pair-strength-using-gcd/)
- 🟡 [4035. Maximum Valid Split Positions I](https://leetcode.com/problems/maximum-valid-split-positions-i/)
- 🔴 [4037. Maximum Valid Split Positions II](https://leetcode.com/problems/maximum-valid-split-positions-ii/)

</details>

<details><summary><b>Geometry</b> (32)</summary>

- 🔴 [149. Max Points on a Line](https://leetcode.com/problems/max-points-on-a-line/)
- 🔴 [335. Self Crossing](https://leetcode.com/problems/self-crossing/)
- 🟡 [469. Convex Polygon](https://leetcode.com/problems/convex-polygon/) 🔒
- 🟡 [478. Generate Random Point in a Circle](https://leetcode.com/problems/generate-random-point-in-a-circle/)
- 🔴 [587. Erect the Fence](https://leetcode.com/problems/erect-the-fence/)
- 🟡 [593. Valid Square](https://leetcode.com/problems/valid-square/)
- 🟢 [812. Largest Triangle Area](https://leetcode.com/problems/largest-triangle-area/)
- 🟡 [858. Mirror Reflection](https://leetcode.com/problems/mirror-reflection/)
- 🟢 [883. Projection Area of 3D Shapes](https://leetcode.com/problems/projection-area-of-3d-shapes/)
- 🟢 [892. Surface Area of 3D Shapes](https://leetcode.com/problems/surface-area-of-3d-shapes/)
- 🟡 [939. Minimum Area Rectangle](https://leetcode.com/problems/minimum-area-rectangle/)
- 🟡 [963. Minimum Area Rectangle II](https://leetcode.com/problems/minimum-area-rectangle-ii/)
- 🟢 [1030. Matrix Cells in Distance Order](https://leetcode.com/problems/matrix-cells-in-distance-order/)
- 🟢 [1037. Valid Boomerang](https://leetcode.com/problems/valid-boomerang/)
- 🟢 [1232. Check If It Is a Straight Line](https://leetcode.com/problems/check-if-it-is-a-straight-line/)
- 🟢 [1266. Minimum Time Visiting All Points](https://leetcode.com/problems/minimum-time-visiting-all-points/)
- 🔴 [1453. Maximum Number of Darts Inside of a Circular Dartboard](https://leetcode.com/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/)
- 🔴 [1515. Best Position for a Service Centre](https://leetcode.com/problems/best-position-for-a-service-centre/)
- 🟡 [1828. Queries on Number of Points Inside a Circle](https://leetcode.com/problems/queries-on-number-of-points-inside-a-circle/)
- 🔴 [1924. Erect the Fence II](https://leetcode.com/problems/erect-the-fence-ii/) 🔒
- 🟡 [2249. Count Lattice Points Inside a Circle](https://leetcode.com/problems/count-lattice-points-inside-a-circle/)
- 🟡 [2280. Minimum Lines to Represent a Line Chart](https://leetcode.com/problems/minimum-lines-to-represent-a-line-chart/)
- 🟢 [2481. Minimum Cuts to Divide a Circle](https://leetcode.com/problems/minimum-cuts-to-divide-a-circle/)
- 🔴 [2613. Beautiful Pairs](https://leetcode.com/problems/beautiful-pairs/) 🔒
- 🟢 [3024. Type of Triangle](https://leetcode.com/problems/type-of-triangle/)
- 🟡 [3025. Find the Number of Ways to Place People I](https://leetcode.com/problems/find-the-number-of-ways-to-place-people-i/)
- 🔴 [3027. Find the Number of Ways to Place People II](https://leetcode.com/problems/find-the-number-of-ways-to-place-people-ii/)
- 🟡 [3047. Find the Largest Area of Square Inside Two Rectangles](https://leetcode.com/problems/find-the-largest-area-of-square-inside-two-rectangles/)
- 🔴 [3102. Minimize Manhattan Distances](https://leetcode.com/problems/minimize-manhattan-distances/)
- 🟡 [3623. Count Number of Trapezoids I](https://leetcode.com/problems/count-number-of-trapezoids-i/)
- 🔴 [3625. Count Number of Trapezoids II](https://leetcode.com/problems/count-number-of-trapezoids-ii/)
- 🟡 [3899. Angles of a Triangle](https://leetcode.com/problems/angles-of-a-triangle/)

</details>

<details><summary><b>Combinatorics</b> (28)</summary>

- 🟡 [164. Maximum Gap](https://leetcode.com/problems/maximum-gap/)
- 🟢 [961. N-Repeated Element in Size 2N Array](https://leetcode.com/problems/n-repeated-element-in-size-2n-array/)
- 🟡 [1015. Smallest Integer Divisible by K](https://leetcode.com/problems/smallest-integer-divisible-by-k/)
- 🔴 [1830. Minimum Number of Operations to Make String Sorted](https://leetcode.com/problems/minimum-number-of-operations-to-make-string-sorted/)
- 🟡 [2221. Find Triangular Sum of an Array](https://leetcode.com/problems/find-triangular-sum-of-an-array/)
- 🔴 [2514. Count Anagrams](https://leetcode.com/problems/count-anagrams/)
- 🟡 [2539. Count the Number of Good Subsequences](https://leetcode.com/problems/count-the-number-of-good-subsequences/) 🔒
- 🔴 [2927. Distribute Candies Among Children III](https://leetcode.com/problems/distribute-candies-among-children-iii/) 🔒
- 🟢 [2928. Distribute Candies Among Children I](https://leetcode.com/problems/distribute-candies-among-children-i/)
- 🟡 [2929. Distribute Candies Among Children II](https://leetcode.com/problems/distribute-candies-among-children-ii/)
- 🔴 [2954. Count the Number of Infection Sequences](https://leetcode.com/problems/count-the-number-of-infection-sequences/)
- 🔴 [2963. Count the Number of Good Partitions](https://leetcode.com/problems/count-the-number-of-good-partitions/)
- 🟡 [3128. Right Triangles](https://leetcode.com/problems/right-triangles/)
- 🔴 [3272. Find the Count of Good Integers](https://leetcode.com/problems/find-the-count-of-good-integers/)
- 🔴 [3395. Subsequences with a Unique Middle Mode I](https://leetcode.com/problems/subsequences-with-a-unique-middle-mode-i/)
- 🔴 [3405. Count the Number of Arrays with K Matching Adjacent Elements](https://leetcode.com/problems/count-the-number-of-arrays-with-k-matching-adjacent-elements/)
- 🔴 [3416. Subsequences with a Unique Middle Mode II](https://leetcode.com/problems/subsequences-with-a-unique-middle-mode-ii/) 🔒
- 🔴 [3426. Manhattan Distances of All Arrangements of Pieces](https://leetcode.com/problems/manhattan-distances-of-all-arrangements-of-pieces/)
- 🟢 [3461. Check If Digits Are Equal in String After Operations I](https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-i/)
- 🔴 [3463. Check If Digits Are Equal in String After Operations II](https://leetcode.com/problems/check-if-digits-are-equal-in-string-after-operations-ii/)
- 🔴 [3470. Permutations IV](https://leetcode.com/problems/permutations-iv/)
- 🔴 [3518. Smallest Palindromic Rearrangement II](https://leetcode.com/problems/smallest-palindromic-rearrangement-ii/)
- 🟡 [3577. Count the Number of Computer Unlocking Permutations](https://leetcode.com/problems/count-the-number-of-computer-unlocking-permutations/)
- 🔴 [3855. Sum of K-Digit Numbers in a Range](https://leetcode.com/problems/sum-of-k-digit-numbers-in-a-range/)
- 🟡 [3881. Direction Assignments with Exactly K Visible People](https://leetcode.com/problems/direction-assignments-with-exactly-k-visible-people/)
- 🔴 [3953. Maximum Score with Co-Prime Element](https://leetcode.com/problems/maximum-score-with-co-prime-element/)
- 🟡 [3988. Create Grid With Exactly K Paths I](https://leetcode.com/problems/create-grid-with-exactly-k-paths-i/)
- 🟡 [4002. Count Valid Sequences](https://leetcode.com/problems/count-valid-sequences/)

</details>

<details><summary><b>Guessed from title (no tags yet)</b> (6)</summary>

- 🟢 [4078. Three Fibonacci Sum](https://leetcode.com/problems/three-fibonacci-sum/)
- 🟡 [4079. Prime Subset Selection I](https://leetcode.com/problems/prime-subset-selection-i/)
- 🔴 [4081. Prime Subset Selection II](https://leetcode.com/problems/prime-subset-selection-ii/)
- 🟢 [4092. Binary Digit Score](https://leetcode.com/problems/binary-digit-score/)
- 🟡 [4093. Maximize Sum After At Most K Digit Rearrangements](https://leetcode.com/problems/maximize-sum-after-at-most-k-digit-rearrangements/)
- 🟡 [4113. Game of Divisible Sums](https://leetcode.com/problems/game-of-divisible-sums/)

</details>

<details><summary><b>Game Theory</b> (5)</summary>

- 🟢 [292. Nim Game](https://leetcode.com/problems/nim-game/)
- 🔴 [843. Guess the Word](https://leetcode.com/problems/guess-the-word/)
- 🟢 [3222. Find the Winning Player in Coin Game](https://leetcode.com/problems/find-the-winning-player-in-coin-game/)
- 🟡 [3227. Vowels Game in a String](https://leetcode.com/problems/vowels-game-in-a-string/)
- 🟡 [3828. Final Element After Subarray Deletions](https://leetcode.com/problems/final-element-after-subarray-deletions/)

</details>

<details><summary><b>Brainteaser</b> (5)</summary>

- 🟡 [319. Bulb Switcher](https://leetcode.com/problems/bulb-switcher/)
- 🟡 [1033. Moving Stones Until Consecutive](https://leetcode.com/problems/moving-stones-until-consecutive/)
- 🟡 [1503. Last Moment Before All Ants Fall Out of a Plank](https://leetcode.com/problems/last-moment-before-all-ants-fall-out-of-a-plank/)
- 🟡 [3596. Minimum Cost Path with Alternating Directions I](https://leetcode.com/problems/minimum-cost-path-with-alternating-directions-i/) 🔒
- 🟡 [4062. Transform Array Using Pair Operations](https://leetcode.com/problems/transform-array-using-pair-operations/)

</details>

<details><summary><b>Probability & Randomized</b> (4)</summary>

- 🟡 [398. Random Pick Index](https://leetcode.com/problems/random-pick-index/)
- 🟡 [470. Implement Rand10() Using Rand7()](https://leetcode.com/problems/implement-rand10-using-rand7/)
- 🟡 [519. Random Flip Matrix](https://leetcode.com/problems/random-flip-matrix/)
- 🟡 [1093. Statistics from a Large Sample](https://leetcode.com/problems/statistics-from-a-large-sample/)

</details>

<details><summary><b>Big-number Arithmetic</b> (1)</summary>

- 🟡 [43. Multiply Strings](https://leetcode.com/problems/multiply-strings/)

</details>

<details><summary><b>Fast Exponentiation</b> (1)</summary>

- 🟡 [50. Pow(x, n)](https://leetcode.com/problems/powx-n/)

</details>

## Design (Data Structures)

*Build a class: LRU cache, iterators, time-based stores.* — 42 problems

<details><summary><b>Class Design</b> (34)</summary>

- 🟢 [225. Implement Stack using Queues](https://leetcode.com/problems/implement-stack-using-queues/)
- 🟡 [288. Unique Word Abbreviation](https://leetcode.com/problems/unique-word-abbreviation/) 🔒
- 🟢 [346. Moving Average from Data Stream](https://leetcode.com/problems/moving-average-from-data-stream/) 🔒
- 🟡 [348. Design Tic-Tac-Toe](https://leetcode.com/problems/design-tic-tac-toe/) 🔒
- 🟡 [353. Design Snake Game](https://leetcode.com/problems/design-snake-game/) 🔒
- 🟢 [359. Logger Rate Limiter](https://leetcode.com/problems/logger-rate-limiter/) 🔒
- 🔴 [381. Insert Delete GetRandom O(1) - Duplicates allowed](https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/)
- 🟡 [384. Shuffle an Array](https://leetcode.com/problems/shuffle-an-array/)
- 🟡 [635. Design Log Storage System](https://leetcode.com/problems/design-log-storage-system/) 🔒
- 🔴 [895. Maximum Frequency Stack](https://leetcode.com/problems/maximum-frequency-stack/)
- 🟢 [933. Number of Recent Calls](https://leetcode.com/problems/number-of-recent-calls/)
- 🟡 [1244. Design A Leaderboard](https://leetcode.com/problems/design-a-leaderboard/) 🔒
- 🟡 [1352. Product of the Last K Numbers](https://leetcode.com/problems/product-of-the-last-k-numbers/)
- 🟡 [1357. Apply Discount Every n Orders](https://leetcode.com/problems/apply-discount-every-n-orders/)
- 🟡 [1381. Design a Stack With Increment Operation](https://leetcode.com/problems/design-a-stack-with-increment-operation/)
- 🟡 [1396. Design Underground System](https://leetcode.com/problems/design-underground-system/)
- 🟡 [1429. First Unique Number](https://leetcode.com/problems/first-unique-number/) 🔒
- 🟡 [1476. Subrectangle Queries](https://leetcode.com/problems/subrectangle-queries/)
- 🟢 [1603. Design Parking System](https://leetcode.com/problems/design-parking-system/)
- 🟢 [1656. Design an Ordered Stream](https://leetcode.com/problems/design-an-ordered-stream/)
- 🟡 [1865. Finding Pairs With a Certain Sum](https://leetcode.com/problems/finding-pairs-with-a-certain-sum/)
- 🟡 [2043. Simple Bank System](https://leetcode.com/problems/simple-bank-system/)
- 🟡 [2069. Walking Robot Simulation II](https://leetcode.com/problems/walking-robot-simulation-ii/)
- 🟡 [2166. Design Bitset](https://leetcode.com/problems/design-bitset/)
- 🟡 [2241. Design an ATM Machine](https://leetcode.com/problems/design-an-atm-machine/)
- 🟡 [2408. Design SQL](https://leetcode.com/problems/design-sql/)
- 🟡 [2502. Design Memory Allocator](https://leetcode.com/problems/design-memory-allocator/)
- 🟡 [2526. Find Consecutive Integers from a Data Stream](https://leetcode.com/problems/find-consecutive-integers-from-a-data-stream/)
- 🟡 [2590. Design a Todo List](https://leetcode.com/problems/design-a-todo-list/) 🔒
- 🟡 [2671. Frequency Tracker](https://leetcode.com/problems/frequency-tracker/)
- 🟢 [3242. Design Neighbor Sum Service](https://leetcode.com/problems/design-neighbor-sum-service/)
- 🟡 [3484. Design Spreadsheet](https://leetcode.com/problems/design-spreadsheet/)
- 🟡 [3822. Design Order Management System](https://leetcode.com/problems/design-order-management-system/) 🔒
- 🟡 [3829. Design Ride Sharing System](https://leetcode.com/problems/design-ride-sharing-system/)

</details>

<details><summary><b>Iterator</b> (4)</summary>

- 🟡 [281. Zigzag Iterator](https://leetcode.com/problems/zigzag-iterator/) 🔒
- 🟡 [284. Peeking Iterator](https://leetcode.com/problems/peeking-iterator/)
- 🟢 [604. Design Compressed String Iterator](https://leetcode.com/problems/design-compressed-string-iterator/) 🔒
- 🟡 [900. RLE Iterator](https://leetcode.com/problems/rle-iterator/)

</details>

<details><summary><b>Hash Map + Doubly Linked List</b> (2)</summary>

- 🟡 [146. LRU Cache](https://leetcode.com/problems/lru-cache/)
- 🔴 [460. LFU Cache](https://leetcode.com/problems/lfu-cache/)

</details>

<details><summary><b>Hash Map + Array</b> (1)</summary>

- 🟡 [380. Insert Delete GetRandom O(1)](https://leetcode.com/problems/insert-delete-getrandom-o1/)

</details>

<details><summary><b>Guessed from title (no tags yet)</b> (1)</summary>

- 🟡 [4080. Design Bus Seat Booking System](https://leetcode.com/problems/design-bus-seat-booking-system/)

</details>

## Matrix & Simulation

*Follow the rules step by step; spiral, rotate, game boards.* — 103 problems

<details><summary><b>Simulation</b> (55)</summary>

- 🔴 [68. Text Justification](https://leetcode.com/problems/text-justification/)
- 🟢 [495. Teemo Attacking](https://leetcode.com/problems/teemo-attacking/)
- 🟡 [544. Output Contest Matches](https://leetcode.com/problems/output-contest-matches/) 🔒
- 🟢 [657. Robot Return to Origin](https://leetcode.com/problems/robot-return-to-origin/)
- 🟡 [755. Pour Water](https://leetcode.com/problems/pour-water/) 🔒
- 🟡 [985. Sum of Even Numbers After Queries](https://leetcode.com/problems/sum-of-even-numbers-after-queries/)
- 🟢 [1243. Array Transformation](https://leetcode.com/problems/array-transformation/) 🔒
- 🟡 [1324. Print Words Vertically](https://leetcode.com/problems/print-words-vertically/)
- 🟢 [1389. Create Target Array in the Given Order](https://leetcode.com/problems/create-target-array-in-the-given-order/)
- 🟡 [1535. Find the Winner of an Array Game](https://leetcode.com/problems/find-the-winner-of-an-array-game/)
- 🟡 [1545. Find Kth Bit in Nth Binary String](https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/)
- 🟢 [1560. Most Visited Sector in  a Circular Track](https://leetcode.com/problems/most-visited-sector-in-a-circular-track/)
- 🟡 [1583. Count Unhappy Friends](https://leetcode.com/problems/count-unhappy-friends/)
- 🟡 [1599. Maximum Profit of Operating a Centennial Wheel](https://leetcode.com/problems/maximum-profit-of-operating-a-centennial-wheel/)
- 🟢 [1646. Get Maximum in Generated Array](https://leetcode.com/problems/get-maximum-in-generated-array/)
- 🟡 [1701. Average Waiting Time](https://leetcode.com/problems/average-waiting-time/)
- 🟢 [1920. Build Array from Permutation](https://leetcode.com/problems/build-array-from-permutation/)
- 🟢 [1929. Concatenation of Array](https://leetcode.com/problems/concatenation-of-array/)
- 🟢 [1945. Sum of Digits of String After Convert](https://leetcode.com/problems/sum-of-digits-of-string-after-convert/)
- 🟢 [2011. Final Value of Variable After Performing Operations](https://leetcode.com/problems/final-value-of-variable-after-performing-operations/)
- 🟢 [2073. Time Needed to Buy Tickets](https://leetcode.com/problems/time-needed-to-buy-tickets/)
- 🟡 [2075. Decode the Slanted Ciphertext](https://leetcode.com/problems/decode-the-slanted-ciphertext/)
- 🟡 [2079. Watering Plants](https://leetcode.com/problems/watering-plants/)
- 🟡 [2120. Execution of All Suffix Instructions Staying in a Grid](https://leetcode.com/problems/execution-of-all-suffix-instructions-staying-in-a-grid/)
- 🟢 [2138. Divide a String Into Groups of Size k](https://leetcode.com/problems/divide-a-string-into-groups-of-size-k/)
- 🟢 [2243. Calculate Digit Sum of a String](https://leetcode.com/problems/calculate-digit-sum-of-a-string/)
- 🟢 [2293. Min Max Game](https://leetcode.com/problems/min-max-game/)
- 🟢 [2303. Calculate Amount Paid in Taxes](https://leetcode.com/problems/calculate-amount-paid-in-taxes/)
- 🔴 [2534. Time Taken to Cross the Door](https://leetcode.com/problems/time-taken-to-cross-the-door/) 🔒
- 🟢 [2553. Separate the Digits in an Array](https://leetcode.com/problems/separate-the-digits-in-an-array/)
- 🟢 [2660. Determine the Winner of a Bowling Game](https://leetcode.com/problems/determine-the-winner-of-a-bowling-game/)
- 🟢 [2717. Semi-Ordered Permutation](https://leetcode.com/problems/semi-ordered-permutation/)
- 🟢 [2810. Faulty Keyboard](https://leetcode.com/problems/faulty-keyboard/)
- 🟢 [2899. Last Visited Integers](https://leetcode.com/problems/last-visited-integers/)
- 🟢 [3038. Maximum Number of Operations With the Same Score I](https://leetcode.com/problems/maximum-number-of-operations-with-the-same-score-i/)
- 🟢 [3168. Minimum Number of Chairs in a Waiting Room](https://leetcode.com/problems/minimum-number-of-chairs-in-a-waiting-room/)
- 🟡 [3175. Find The First Player to win K Games in a Row](https://leetcode.com/problems/find-the-first-player-to-win-k-games-in-a-row/)
- 🟢 [3248. Snake in Matrix](https://leetcode.com/problems/snake-in-matrix/)
- 🟡 [3271. Hash Divided String](https://leetcode.com/problems/hash-divided-string/)
- 🟡 [3324. Find the Sequence of Strings Appeared on the Screen](https://leetcode.com/problems/find-the-sequence-of-strings-appeared-on-the-screen/)
- 🟢 [3379. Transformed Array](https://leetcode.com/problems/transformed-array/)
- 🟢 [3498. Reverse Degree of a String](https://leetcode.com/problems/reverse-degree-of-a-string/)
- 🟢 [3582. Generate Tag for Video Caption](https://leetcode.com/problems/generate-tag-for-video-caption/)
- 🟡 [3612. Process String with Special Operations I](https://leetcode.com/problems/process-string-with-special-operations-i/)
- 🔴 [3614. Process String with Special Operations II](https://leetcode.com/problems/process-string-with-special-operations-ii/)
- 🟡 [3616. Number of Student Replacements](https://leetcode.com/problems/number-of-student-replacements/) 🔒
- 🟢 [3687. Library Late Fee Calculator](https://leetcode.com/problems/library-late-fee-calculator/) 🔒
- 🟢 [3701. Compute Alternating Sum](https://leetcode.com/problems/compute-alternating-sum/)
- 🟢 [3813. Vowel-Consonant Score](https://leetcode.com/problems/vowel-consonant-score/)
- 🟡 [3819. Rotate Non Negative Elements](https://leetcode.com/problems/rotate-non-negative-elements/)
- 🟢 [3838. Weighted Word Mapping](https://leetcode.com/problems/weighted-word-mapping/)
- 🟡 [3847. Find the Score Difference in a Game](https://leetcode.com/problems/find-the-score-difference-in-a-game/)
- 🟢 [3921. Score Validator](https://leetcode.com/problems/score-validator/)
- 🟢 [3925. Concatenate Array With Reverse](https://leetcode.com/problems/concatenate-array-with-reverse/)
- 🟢 [4020. Elevator Requests I](https://leetcode.com/problems/elevator-requests-i/)

</details>

<details><summary><b>Matrix</b> (40)</summary>

- 🟡 [59. Spiral Matrix II](https://leetcode.com/problems/spiral-matrix-ii/)
- 🟢 [422. Valid Word Square](https://leetcode.com/problems/valid-word-square/) 🔒
- 🟡 [498. Diagonal Traverse](https://leetcode.com/problems/diagonal-traverse/)
- 🟢 [566. Reshape the Matrix](https://leetcode.com/problems/reshape-the-matrix/)
- 🟢 [661. Image Smoother](https://leetcode.com/problems/image-smoother/)
- 🟢 [766. Toeplitz Matrix](https://leetcode.com/problems/toeplitz-matrix/)
- 🟡 [794. Valid Tic-Tac-Toe State](https://leetcode.com/problems/valid-tic-tac-toe-state/)
- 🟢 [867. Transpose Matrix](https://leetcode.com/problems/transpose-matrix/)
- 🟡 [885. Spiral Matrix III](https://leetcode.com/problems/spiral-matrix-iii/)
- 🟢 [999. Available Captures for Rook](https://leetcode.com/problems/available-captures-for-rook/)
- 🟡 [1222. Queens That Can Attack the King](https://leetcode.com/problems/queens-that-can-attack-the-king/)
- 🟢 [1260. Shift 2D Grid](https://leetcode.com/problems/shift-2d-grid/)
- 🟢 [1380. Lucky Numbers in a Matrix](https://leetcode.com/problems/lucky-numbers-in-a-matrix/)
- 🟢 [1572. Matrix Diagonal Sum](https://leetcode.com/problems/matrix-diagonal-sum/)
- 🟢 [1582. Special Positions in a Binary Matrix](https://leetcode.com/problems/special-positions-in-a-binary-matrix/)
- 🟢 [1672. Richest Customer Wealth](https://leetcode.com/problems/richest-customer-wealth/)
- 🟡 [1706. Where Will the Ball Fall](https://leetcode.com/problems/where-will-the-ball-fall/)
- 🟢 [1886. Determine Whether Matrix Can Be Obtained By Rotation](https://leetcode.com/problems/determine-whether-matrix-can-be-obtained-by-rotation/)
- 🟡 [1914. Cyclically Rotating a Grid](https://leetcode.com/problems/cyclically-rotating-a-grid/)
- 🟡 [1958. Check if Move is Legal](https://leetcode.com/problems/check-if-move-is-legal/)
- 🟡 [2018. Check if Word Can Be Placed In Crossword](https://leetcode.com/problems/check-if-word-can-be-placed-in-crossword/)
- 🟢 [2022. Convert 1D Array Into 2D Array](https://leetcode.com/problems/convert-1d-array-into-2d-array/)
- 🟡 [2061. Number of Spaces Cleaning Robot Cleaned](https://leetcode.com/problems/number-of-spaces-cleaning-robot-cleaned/) 🔒
- 🟡 [2257. Count Unguarded Cells in the Grid](https://leetcode.com/problems/count-unguarded-cells-in-the-grid/)
- 🟢 [2319. Check if Matrix Is X-Matrix](https://leetcode.com/problems/check-if-matrix-is-x-matrix/)
- 🟢 [2373. Largest Local Values in a Matrix](https://leetcode.com/problems/largest-local-values-in-a-matrix/)
- 🟡 [2482. Difference Between Ones and Zeros in Row and Column](https://leetcode.com/problems/difference-between-ones-and-zeros-in-row-and-column/)
- 🟢 [2639. Find the Width of Columns of a Grid](https://leetcode.com/problems/find-the-width-of-columns-of-a-grid/)
- 🟢 [2643. Row With Maximum Ones](https://leetcode.com/problems/row-with-maximum-ones/)
- 🟢 [2923. Find Champion I](https://leetcode.com/problems/find-champion-i/)
- 🟡 [3030. Find the Grid of Region Average](https://leetcode.com/problems/find-the-grid-of-region-average/)
- 🟢 [3033. Modify the Matrix](https://leetcode.com/problems/modify-the-matrix/)
- 🟢 [3127. Make a Square with the Same Color](https://leetcode.com/problems/make-a-square-with-the-same-color/)
- 🟢 [3142. Check if Grid Satisfies Conditions](https://leetcode.com/problems/check-if-grid-satisfies-conditions/)
- 🟡 [3195. Find the Minimum Area to Cover All Ones I](https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-i/)
- 🔴 [3197. Find the Minimum Area to Cover All Ones II](https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/)
- 🟢 [3417. Zigzag Grid Traversal With Skip](https://leetcode.com/problems/zigzag-grid-traversal-with-skip/)
- 🟡 [3537. Fill a Special Grid](https://leetcode.com/problems/fill-a-special-grid/)
- 🟡 [3565. Sequential Grid Path Cover](https://leetcode.com/problems/sequential-grid-path-cover/) 🔒
- 🟢 [4052. Cyclically Shift Rows and Columns](https://leetcode.com/problems/cyclically-shift-rows-and-columns/)

</details>

<details><summary><b>Interactive</b> (4)</summary>

- 🟢 [157. Read N Characters Given Read4](https://leetcode.com/problems/read-n-characters-given-read4/) 🔒
- 🔴 [158. Read N Characters Given read4 II - Call Multiple Times](https://leetcode.com/problems/read-n-characters-given-read4-ii-call-multiple-times/) 🔒
- 🔴 [1274. Number of Ships in a Rectangle](https://leetcode.com/problems/number-of-ships-in-a-rectangle/) 🔒
- 🟢 [2728. Count Houses in a Circular Street](https://leetcode.com/problems/count-houses-in-a-circular-street/) 🔒

</details>

<details><summary><b>Spiral / Rotate</b> (2)</summary>

- 🟡 [48. Rotate Image](https://leetcode.com/problems/rotate-image/)
- 🟡 [54. Spiral Matrix](https://leetcode.com/problems/spiral-matrix/)

</details>

<details><summary><b>In-place Matrix</b> (1)</summary>

- 🟡 [73. Set Matrix Zeroes](https://leetcode.com/problems/set-matrix-zeroes/)

</details>

<details><summary><b>Board Simulation</b> (1)</summary>

- 🟡 [289. Game of Life](https://leetcode.com/problems/game-of-life/)

</details>

## Sorting & Custom Ordering

*Sort first, custom comparators, counting / bucket sort.* — 39 problems

<details><summary><b>Sort then Scan</b> (36)</summary>

- 🟢 [414. Third Maximum Number](https://leetcode.com/problems/third-maximum-number/)
- 🟢 [747. Largest Number At Least Twice of Others](https://leetcode.com/problems/largest-number-at-least-twice-of-others/)
- 🔴 [761. Special Binary String](https://leetcode.com/problems/special-binary-string/)
- 🟡 [937. Reorder Data in Log Files](https://leetcode.com/problems/reorder-data-in-log-files/)
- 🟡 [950. Reveal Cards In Increasing Order](https://leetcode.com/problems/reveal-cards-in-increasing-order/)
- 🟢 [1200. Minimum Absolute Difference](https://leetcode.com/problems/minimum-absolute-difference/)
- 🟡 [1329. Sort the Matrix Diagonally](https://leetcode.com/problems/sort-the-matrix-diagonally/)
- 🟡 [1333. Filter Restaurants by Vegan-Friendly, Price and Distance](https://leetcode.com/problems/filter-restaurants-by-vegan-friendly-price-and-distance/)
- 🟡 [1451. Rearrange Words in a Sentence](https://leetcode.com/problems/rearrange-words-in-a-sentence/)
- 🟢 [1491. Average Salary Excluding the Minimum and Maximum Salary](https://leetcode.com/problems/average-salary-excluding-the-minimum-and-maximum-salary/)
- 🟢 [1502. Can Make Arithmetic Progression From Sequence](https://leetcode.com/problems/can-make-arithmetic-progression-from-sequence/)
- 🟢 [1619. Mean of Array After Removing Some Elements](https://leetcode.com/problems/mean-of-array-after-removing-some-elements/)
- 🟢 [1637. Widest Vertical Area Between Two Points Containing No Points](https://leetcode.com/problems/widest-vertical-area-between-two-points-containing-no-points/)
- 🟢 [1859. Sorting the Sentence](https://leetcode.com/problems/sorting-the-sentence/)
- 🟡 [1887. Reduction Operations to Make the Array Elements Equal](https://leetcode.com/problems/reduction-operations-to-make-the-array-elements-equal/)
- 🟢 [1913. Maximum Product Difference Between Two Pairs](https://leetcode.com/problems/maximum-product-difference-between-two-pairs/)
- 🟢 [2164. Sort Even and Odd Indices Independently](https://leetcode.com/problems/sort-even-and-odd-indices-independently/)
- 🟡 [2191. Sort the Jumbled Numbers](https://leetcode.com/problems/sort-the-jumbled-numbers/)
- 🟡 [2274. Maximum Consecutive Floors Without Special Floors](https://leetcode.com/problems/maximum-consecutive-floors-without-special-floors/)
- 🟡 [2545. Sort the Students by Their Kth Score](https://leetcode.com/problems/sort-the-students-by-their-kth-score/)
- 🟡 [2655. Find Maximal Uncovered Ranges](https://leetcode.com/problems/find-maximal-uncovered-ranges/) 🔒
- 🟢 [2733. Neither Minimum nor Maximum](https://leetcode.com/problems/neither-minimum-nor-maximum/)
- 🟡 [2740. Find the Value of the Partition](https://leetcode.com/problems/find-the-value-of-the-partition/)
- 🟡 [2785. Sort Vowels in a String](https://leetcode.com/problems/sort-vowels-in-a-string/)
- 🟡 [2860. Happy Students](https://leetcode.com/problems/happy-students/)
- 🟡 [2943. Maximize Area of Square Hole in Grid](https://leetcode.com/problems/maximize-area-of-square-hole-in-grid/)
- 🟢 [3010. Divide an Array Into Subarrays With Minimum Cost I](https://leetcode.com/problems/divide-an-array-into-subarrays-with-minimum-cost-i/)
- 🟡 [3169. Count Days Without Meetings](https://leetcode.com/problems/count-days-without-meetings/)
- 🟡 [3394. Check if Grid can be Cut into Sections](https://leetcode.com/problems/check-if-grid-can-be-cut-into-sections/)
- 🟡 [3446. Sort Matrix by Diagonals](https://leetcode.com/problems/sort-matrix-by-diagonals/)
- 🟡 [3567. Minimum Absolute Difference in Sliding Submatrix](https://leetcode.com/problems/minimum-absolute-difference-in-sliding-submatrix/)
- 🟡 [3631. Sort Threats by Severity and Exploitability](https://leetcode.com/problems/sort-threats-by-severity-and-exploitability/) 🔒
- 🟢 [3769. Sort Integers by Binary Reflection](https://leetcode.com/problems/sort-integers-by-binary-reflection/)
- 🟢 [3774. Absolute Difference Between Maximum and Minimum K Elements](https://leetcode.com/problems/absolute-difference-between-maximum-and-minimum-k-elements/)
- 🟡 [3951. Minimum Energy to Maintain Brightness](https://leetcode.com/problems/minimum-energy-to-maintain-brightness/)
- 🟡 [4101. Find All Numbers Disappeared in an Array III](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array-iii/) 🔒

</details>

<details><summary><b>Counting / Bucket Sort</b> (3)</summary>

- 🟡 [274. H-Index](https://leetcode.com/problems/h-index/)
- 🟢 [1051. Height Checker](https://leetcode.com/problems/height-checker/)
- 🟡 [3517. Smallest Palindromic Rearrangement I](https://leetcode.com/problems/smallest-palindromic-rearrangement-i/)

</details>

## Arrays & Strings (Basics)

*Direct scans, enumeration, string building.* — 182 problems

<details><summary><b>String Scan / Building</b> (91)</summary>

- 🟡 [6. Zigzag Conversion](https://leetcode.com/problems/zigzag-conversion/)
- 🟡 [8. String to Integer (atoi)](https://leetcode.com/problems/string-to-integer-atoi/)
- 🟡 [38. Count and Say](https://leetcode.com/problems/count-and-say/)
- 🟢 [58. Length of Last Word](https://leetcode.com/problems/length-of-last-word/)
- 🔴 [65. Valid Number](https://leetcode.com/problems/valid-number/)
- 🟢 [243. Shortest Word Distance](https://leetcode.com/problems/shortest-word-distance/) 🔒
- 🟡 [245. Shortest Word Distance III](https://leetcode.com/problems/shortest-word-distance-iii/) 🔒
- 🟢 [293. Flip Game](https://leetcode.com/problems/flip-game/) 🔒
- 🟢 [434. Number of Segments in a String](https://leetcode.com/problems/number-of-segments-in-a-string/)
- 🟡 [468. Validate IP Address](https://leetcode.com/problems/validate-ip-address/)
- 🟢 [482. License Key Formatting](https://leetcode.com/problems/license-key-formatting/)
- 🟢 [520. Detect Capital](https://leetcode.com/problems/detect-capital/)
- 🟢 [521. Longest Uncommon Subsequence I](https://leetcode.com/problems/longest-uncommon-subsequence-i/)
- 🟢 [551. Student Attendance Record I](https://leetcode.com/problems/student-attendance-record-i/)
- 🟢 [709. To Lower Case](https://leetcode.com/problems/to-lower-case/)
- 🟡 [722. Remove Comments](https://leetcode.com/problems/remove-comments/)
- 🟢 [806. Number of Lines To Write String](https://leetcode.com/problems/number-of-lines-to-write-string/)
- 🟢 [824. Goat Latin](https://leetcode.com/problems/goat-latin/)
- 🟢 [830. Positions of Large Groups](https://leetcode.com/problems/positions-of-large-groups/)
- 🟡 [831. Masking Personal Information](https://leetcode.com/problems/masking-personal-information/)
- 🟢 [1078. Occurrences After Bigram](https://leetcode.com/problems/occurrences-after-bigram/)
- 🟢 [1108. Defanging an IP Address](https://leetcode.com/problems/defanging-an-ip-address/)
- 🟢 [1119. Remove Vowels from a String](https://leetcode.com/problems/remove-vowels-from-a-string/) 🔒
- 🟢 [1309. Decrypt String from Alphabet to Integer Mapping](https://leetcode.com/problems/decrypt-string-from-alphabet-to-integer-mapping/)
- 🟢 [1374. Generate a String With Characters That Have Odd Counts](https://leetcode.com/problems/generate-a-string-with-characters-that-have-odd-counts/)
- 🟢 [1417. Reformat The String](https://leetcode.com/problems/reformat-the-string/)
- 🟢 [1446. Consecutive Characters](https://leetcode.com/problems/consecutive-characters/)
- 🟢 [1507. Reformat Date](https://leetcode.com/problems/reformat-date/)
- 🟢 [1528. Shuffle String](https://leetcode.com/problems/shuffle-string/)
- 🟢 [1556. Thousand Separator](https://leetcode.com/problems/thousand-separator/)
- 🟢 [1576. Replace All ?'s to Avoid Consecutive Repeating Characters](https://leetcode.com/problems/replace-all-s-to-avoid-consecutive-repeating-characters/)
- 🟢 [1592. Rearrange Spaces Between Words](https://leetcode.com/problems/rearrange-spaces-between-words/)
- 🟢 [1629. Slowest Key](https://leetcode.com/problems/slowest-key/)
- 🟢 [1662. Check If Two String Arrays are Equivalent](https://leetcode.com/problems/check-if-two-string-arrays-are-equivalent/)
- 🟢 [1678. Goal Parser Interpretation](https://leetcode.com/problems/goal-parser-interpretation/)
- 🟢 [1694. Reformat Phone Number](https://leetcode.com/problems/reformat-phone-number/)
- 🟢 [1758. Minimum Changes To Make Alternating Binary String](https://leetcode.com/problems/minimum-changes-to-make-alternating-binary-string/)
- 🟢 [1773. Count Items Matching a Rule](https://leetcode.com/problems/count-items-matching-a-rule/)
- 🟢 [1784. Check if Binary String Has at Most One Segment of Ones](https://leetcode.com/problems/check-if-binary-string-has-at-most-one-segment-of-ones/)
- 🟢 [1816. Truncate Sentence](https://leetcode.com/problems/truncate-sentence/)
- 🟢 [1844. Replace All Digits with Characters](https://leetcode.com/problems/replace-all-digits-with-characters/)
- 🟢 [1869. Longer Contiguous Segments of Ones than Zeros](https://leetcode.com/problems/longer-contiguous-segments-of-ones-than-zeros/)
- 🟢 [1880. Check if Word Equals Summation of Two Words](https://leetcode.com/problems/check-if-word-equals-summation-of-two-words/)
- 🟢 [1933. Check if String Is Decomposable Into Value-Equal Substrings](https://leetcode.com/problems/check-if-string-is-decomposable-into-value-equal-substrings/) 🔒
- 🟢 [1957. Delete Characters to Make Fancy String](https://leetcode.com/problems/delete-characters-to-make-fancy-string/)
- 🟢 [1967. Number of Strings That Appear as Substrings in Word](https://leetcode.com/problems/number-of-strings-that-appear-as-substrings-in-word/)
- 🟢 [2042. Check if Numbers Are Ascending in a Sentence](https://leetcode.com/problems/check-if-numbers-are-ascending-in-a-sentence/)
- 🟢 [2047. Number of Valid Words in a Sentence](https://leetcode.com/problems/number-of-valid-words-in-a-sentence/)
- 🟢 [2114. Maximum Number of Words Found in Sentences](https://leetcode.com/problems/maximum-number-of-words-found-in-sentences/)
- 🟢 [2124. Check if All A's Appears Before All B's](https://leetcode.com/problems/check-if-all-as-appears-before-all-bs/)
- 🟢 [2129. Capitalize the Title](https://leetcode.com/problems/capitalize-the-title/)
- 🟢 [2194. Cells in a Range on an Excel Sheet](https://leetcode.com/problems/cells-in-a-range-on-an-excel-sheet/)
- 🟢 [2255. Count Prefixes of a Given String](https://leetcode.com/problems/count-prefixes-of-a-given-string/)
- 🟢 [2264. Largest 3-Same-Digit Number in String](https://leetcode.com/problems/largest-3-same-digit-number-in-string/)
- 🟢 [2278. Percentage of Letter in String](https://leetcode.com/problems/percentage-of-letter-in-string/)
- 🟡 [2288. Apply Discount to Prices](https://leetcode.com/problems/apply-discount-to-prices/)
- 🟢 [2299. Strong Password Checker II](https://leetcode.com/problems/strong-password-checker-ii/)
- 🟢 [2315. Count Asterisks](https://leetcode.com/problems/count-asterisks/)
- 🟡 [2414. Length of the Longest Alphabetical Continuous Substring](https://leetcode.com/problems/length-of-the-longest-alphabetical-continuous-substring/)
- 🟢 [2446. Determine if Two Events Have Conflict](https://leetcode.com/problems/determine-if-two-events-have-conflict/)
- 🟢 [2490. Circular Sentence](https://leetcode.com/problems/circular-sentence/)
- 🟢 [2496. Maximum Value of a String in an Array](https://leetcode.com/problems/maximum-value-of-a-string-in-an-array/)
- 🟢 [2515. Shortest Distance to Target String in a Circular Array](https://leetcode.com/problems/shortest-distance-to-target-string-in-a-circular-array/)
- 🟢 [2609. Find the Longest Balanced Substring of a Binary String](https://leetcode.com/problems/find-the-longest-balanced-substring-of-a-binary-string/)
- 🟢 [2678. Number of Senior Citizens](https://leetcode.com/problems/number-of-senior-citizens/)
- 🟢 [2710. Remove Trailing Zeros From a String](https://leetcode.com/problems/remove-trailing-zeros-from-a-string/)
- 🟢 [2788. Split Strings by Separator](https://leetcode.com/problems/split-strings-by-separator/)
- 🟢 [2828. Check if a String Is an Acronym of Words](https://leetcode.com/problems/check-if-a-string-is-an-acronym-of-words/)
- 🟢 [2839. Check if Strings Can be Made Equal With Operations I](https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-i/)
- 🟡 [2914. Minimum Number of Changes to Make Binary String Beautiful](https://leetcode.com/problems/minimum-number-of-changes-to-make-binary-string-beautiful/)
- 🟢 [2937. Make Three Strings Equal](https://leetcode.com/problems/make-three-strings-equal/)
- 🟢 [2942. Find Words Containing Character](https://leetcode.com/problems/find-words-containing-character/)
- 🟢 [3019. Number of Changing Keys](https://leetcode.com/problems/number-of-changing-keys/)
- 🟢 [3110. Score of a String](https://leetcode.com/problems/score-of-a-string/)
- 🟢 [3136. Valid Word](https://leetcode.com/problems/valid-word/)
- 🟡 [3163. String Compression III](https://leetcode.com/problems/string-compression-iii/)
- 🟢 [3210. Find the Encrypted String](https://leetcode.com/problems/find-the-encrypted-string/)
- 🟢 [3330. Find the Original Typed String I](https://leetcode.com/problems/find-the-original-typed-string-i/)
- 🟢 [3340. Check Balanced String](https://leetcode.com/problems/check-balanced-string/)
- 🟢 [3456. Find Special Substring of Length K](https://leetcode.com/problems/find-special-substring-of-length-k/)
- 🟢 [3571. Find the Shortest Superstring II](https://leetcode.com/problems/find-the-shortest-superstring-ii/) 🔒
- 🟡 [3598. Longest Common Prefix Between Adjacent Strings After Removals](https://leetcode.com/problems/longest-common-prefix-between-adjacent-strings-after-removals/)
- 🟢 [3696. Maximum Distance Between Unequal Words in Array I](https://leetcode.com/problems/maximum-distance-between-unequal-words-in-array-i/) 🔒
- 🟡 [3706. Maximum Distance Between Unequal Words in Array II](https://leetcode.com/problems/maximum-distance-between-unequal-words-in-array-ii/) 🔒
- 🟡 [3744. Find Kth Character in Expanded String](https://leetcode.com/problems/find-kth-character-in-expanded-string/) 🔒
- 🟢 [3798. Largest Even Number](https://leetcode.com/problems/largest-even-number/)
- 🟢 [3856. Trim Trailing Vowels](https://leetcode.com/problems/trim-trailing-vowels/)
- 🟡 [3863. Minimum Operations to Sort a String](https://leetcode.com/problems/minimum-operations-to-sort-a-string/)
- 🟡 [3922. Minimum Flips to Make Binary String Coherent](https://leetcode.com/problems/minimum-flips-to-make-binary-string-coherent/)
- 🟢 [3931. Check Adjacent Digit Differences](https://leetcode.com/problems/check-adjacent-digit-differences/)
- 🟡 [4106. Find Mismatched Segments Between Two Strings](https://leetcode.com/problems/find-mismatched-segments-between-two-strings/)

</details>

<details><summary><b>Array Scan</b> (62)</summary>

- 🟢 [163. Missing Ranges](https://leetcode.com/problems/missing-ranges/) 🔒
- 🟢 [228. Summary Ranges](https://leetcode.com/problems/summary-ranges/)
- 🟢 [485. Max Consecutive Ones](https://leetcode.com/problems/max-consecutive-ones/)
- 🟡 [665. Non-decreasing Array](https://leetcode.com/problems/non-decreasing-array/)
- 🟢 [674. Longest Continuous Increasing Subsequence](https://leetcode.com/problems/longest-continuous-increasing-subsequence/)
- 🟢 [717. 1-bit and 2-bit Characters](https://leetcode.com/problems/1-bit-and-2-bit-characters/)
- 🟡 [849. Maximize Distance to Closest Person](https://leetcode.com/problems/maximize-distance-to-closest-person/)
- 🟢 [896. Monotonic Array](https://leetcode.com/problems/monotonic-array/)
- 🟢 [941. Valid Mountain Array](https://leetcode.com/problems/valid-mountain-array/)
- 🟢 [1184. Distance Between Bus Stops](https://leetcode.com/problems/distance-between-bus-stops/)
- 🟢 [1287. Element Appearing More Than 25% In Sorted Array](https://leetcode.com/problems/element-appearing-more-than-25-in-sorted-array/)
- 🟢 [1299. Replace Elements with Greatest Element on Right Side](https://leetcode.com/problems/replace-elements-with-greatest-element-on-right-side/)
- 🟢 [1313. Decompress Run-Length Encoded List](https://leetcode.com/problems/decompress-run-length-encoded-list/)
- 🟡 [1375. Number of Times Binary String Is Prefix-Aligned](https://leetcode.com/problems/number-of-times-binary-string-is-prefix-aligned/)
- 🟢 [1431. Kids With the Greatest Number of Candies](https://leetcode.com/problems/kids-with-the-greatest-number-of-candies/)
- 🟢 [1437. Check If All 1's Are at Least Length K Places Away](https://leetcode.com/problems/check-if-all-1s-are-at-least-length-k-places-away/)
- 🟢 [1450. Number of Students Doing Homework at a Given Time](https://leetcode.com/problems/number-of-students-doing-homework-at-a-given-time/)
- 🟢 [1470. Shuffle the Array](https://leetcode.com/problems/shuffle-the-array/)
- 🟢 [1550. Three Consecutive Odds](https://leetcode.com/problems/three-consecutive-odds/)
- 🟢 [1725. Number Of Rectangles That Can Form The Largest Square](https://leetcode.com/problems/number-of-rectangles-that-can-form-the-largest-square/)
- 🟢 [1752. Check if Array Is Sorted and Rotated](https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/)
- 🟢 [1779. Find Nearest Point That Has the Same X or Y Coordinate](https://leetcode.com/problems/find-nearest-point-that-has-the-same-x-or-y-coordinate/)
- 🟢 [1800. Maximum Ascending Subarray Sum](https://leetcode.com/problems/maximum-ascending-subarray-sum/)
- 🟢 [1848. Minimum Distance to the Target Element](https://leetcode.com/problems/minimum-distance-to-the-target-element/)
- 🟢 [1909. Remove One Element to Make the Array Strictly Increasing](https://leetcode.com/problems/remove-one-element-to-make-the-array-strictly-increasing/)
- 🟡 [2012. Sum of Beauty in the Array](https://leetcode.com/problems/sum-of-beauty-in-the-array/)
- 🟢 [2016. Maximum Difference Between Increasing Elements](https://leetcode.com/problems/maximum-difference-between-increasing-elements/)
- 🟢 [2057. Smallest Index With Equal Value](https://leetcode.com/problems/smallest-index-with-equal-value/)
- 🟡 [2113. Elements in Array After Removing and Replacing Elements](https://leetcode.com/problems/elements-in-array-after-removing-and-replacing-elements/) 🔒
- 🟡 [2155. All Divisions With the Highest Score of a Binary Array](https://leetcode.com/problems/all-divisions-with-the-highest-score-of-a-binary-array/)
- 🟢 [2176. Count Equal and Divisible Pairs in an Array](https://leetcode.com/problems/count-equal-and-divisible-pairs-in-an-array/)
- 🟢 [2210. Count Hills and Valleys in an Array](https://leetcode.com/problems/count-hills-and-valleys-in-an-array/)
- 🟢 [2239. Find Closest Number to Zero](https://leetcode.com/problems/find-closest-number-to-zero/)
- 🟢 [2432. The Employee That Worked on the Longest Task](https://leetcode.com/problems/the-employee-that-worked-on-the-longest-task/)
- 🟢 [2644. Find the Maximum Divisibility Score](https://leetcode.com/problems/find-the-maximum-divisibility-score/)
- 🟡 [2672. Number of Adjacent Elements With the Same Color](https://leetcode.com/problems/number-of-adjacent-elements-with-the-same-color/)
- 🟢 [2798. Number of Employees Who Met the Target](https://leetcode.com/problems/number-of-employees-who-met-the-target/)
- 🟢 [2855. Minimum Right Shifts to Sort the Array](https://leetcode.com/problems/minimum-right-shifts-to-sort-the-array/)
- 🟢 [2908. Minimum Sum of Mountain Triplets I](https://leetcode.com/problems/minimum-sum-of-mountain-triplets-i/)
- 🟢 [3000. Maximum Area of Longest Diagonal Rectangle](https://leetcode.com/problems/maximum-area-of-longest-diagonal-rectangle/)
- 🟢 [3065. Minimum Operations to Exceed Threshold Value I](https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-i/)
- 🟢 [3105. Longest Strictly Increasing or Strictly Decreasing Subarray](https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/)
- 🟢 [3131. Find the Integer Added to Array I](https://leetcode.com/problems/find-the-integer-added-to-array-i/)
- 🟢 [3151. Special Array I](https://leetcode.com/problems/special-array-i/)
- 🟢 [3285. Find Indices of Stable Mountains](https://leetcode.com/problems/find-indices-of-stable-mountains/)
- 🟢 [3349. Adjacent Increasing Subarrays Detection I](https://leetcode.com/problems/adjacent-increasing-subarrays-detection-i/)
- 🟢 [3353. Minimum Total Operations](https://leetcode.com/problems/minimum-total-operations/) 🔒
- 🟢 [3386. Button with Longest Push Time](https://leetcode.com/problems/button-with-longest-push-time/)
- 🟢 [3392. Count Subarrays of Length Three With a Condition](https://leetcode.com/problems/count-subarrays-of-length-three-with-a-condition/)
- 🟢 [3423. Maximum Difference Between Adjacent Elements in a Circular Array](https://leetcode.com/problems/maximum-difference-between-adjacent-elements-in-a-circular-array/)
- 🟢 [3452. Sum of Good Numbers](https://leetcode.com/problems/sum-of-good-numbers/)
- 🟢 [3502. Minimum Cost to Reach Every Position](https://leetcode.com/problems/minimum-cost-to-reach-every-position/)
- 🟢 [3637. Trionic Array I](https://leetcode.com/problems/trionic-array-i/)
- 🟢 [3683. Earliest Time to Finish One Task](https://leetcode.com/problems/earliest-time-to-finish-one-task/)
- 🟡 [3708. Longest Fibonacci Subarray](https://leetcode.com/problems/longest-fibonacci-subarray/)
- 🟡 [3809. Best Reachable Tower](https://leetcode.com/problems/best-reachable-tower/)
- 🟡 [3818. Minimum Prefix Removal to Make Array Strictly Increasing](https://leetcode.com/problems/minimum-prefix-removal-to-make-array-strictly-increasing/)
- 🟢 [3861. Minimum Capacity Box](https://leetcode.com/problems/minimum-capacity-box/)
- 🟡 [3909. Compare Sums of Bitonic Parts](https://leetcode.com/problems/compare-sums-of-bitonic-parts/)
- 🟢 [3912. Valid Elements in an Array](https://leetcode.com/problems/valid-elements-in-an-array/)
- 🟢 [3917. Count Indices With Opposite Parity](https://leetcode.com/problems/count-indices-with-opposite-parity/)
- 🟡 [3942. Minimum Operations to Sort a Permutation](https://leetcode.com/problems/minimum-operations-to-sort-a-permutation/)

</details>

<details><summary><b>Brute-force Enumeration</b> (24)</summary>

- 🟡 [1291. Sequential Digits](https://leetcode.com/problems/sequential-digits/)
- 🟢 [1534. Count Good Triplets](https://leetcode.com/problems/count-good-triplets/)
- 🟢 [1566. Detect Pattern of Length M Repeated K or More Times](https://leetcode.com/problems/detect-pattern-of-length-m-repeated-k-or-more-times/)
- 🟡 [1620. Coordinate With Maximum Network Quality](https://leetcode.com/problems/coordinate-with-maximum-network-quality/)
- 🟡 [2232. Minimize Result by Adding Parentheses to Expression](https://leetcode.com/problems/minimize-result-by-adding-parentheses-to-expression/)
- 🟢 [2437. Number of Valid Clock Times](https://leetcode.com/problems/number-of-valid-clock-times/)
- 🔴 [2468. Split Message Based on Limit](https://leetcode.com/problems/split-message-based-on-limit/)
- 🟡 [2735. Collecting Chocolates](https://leetcode.com/problems/collecting-chocolates/)
- 🟢 [2765. Longest Alternating Subarray](https://leetcode.com/problems/longest-alternating-subarray/)
- 🟢 [2778. Sum of Squares of Special Elements ](https://leetcode.com/problems/sum-of-squares-of-special-elements/)
- 🟡 [2934. Minimum Operations to Maximize Last Elements in Arrays](https://leetcode.com/problems/minimum-operations-to-maximize-last-elements-in-arrays/)
- 🟢 [2951. Find the Peaks](https://leetcode.com/problems/find-the-peaks/)
- 🟢 [3114. Latest Time You Can Obtain After Replacing Characters](https://leetcode.com/problems/latest-time-you-can-obtain-after-replacing-characters/)
- 🟢 [3200. Maximum Height of a Triangle](https://leetcode.com/problems/maximum-height-of-a-triangle/)
- 🟡 [3234. Count the Number of Substrings With Dominant Ones](https://leetcode.com/problems/count-the-number-of-substrings-with-dominant-ones/)
- 🟡 [3499. Maximize Active Section with Trade I](https://leetcode.com/problems/maximize-active-section-with-trade-i/)
- 🟢 [3833. Count Dominant Indices](https://leetcode.com/problems/count-dominant-indices/)
- 🟡 [3872. Longest Arithmetic Sequence After Changing At Most One Element](https://leetcode.com/problems/longest-arithmetic-sequence-after-changing-at-most-one-element/)
- 🟢 [3880. Minimum Absolute Difference Between Two Values](https://leetcode.com/problems/minimum-absolute-difference-between-two-values/)
- 🟡 [3937. Minimum Operations to Make Array Modulo Alternating I](https://leetcode.com/problems/minimum-operations-to-make-array-modulo-alternating-i/)
- 🔴 [3944. Minimum Operations to Make Array Modulo Alternating II](https://leetcode.com/problems/minimum-operations-to-make-array-modulo-alternating-ii/) 🔒
- 🟡 [3979. Maximum Valid Pair Sum](https://leetcode.com/problems/maximum-valid-pair-sum/)
- 🟢 [4024. Nearest Available Drone](https://leetcode.com/problems/nearest-available-drone/)
- 🟡 [4102. Count Valid Substrings I](https://leetcode.com/problems/count-valid-substrings-i/)

</details>

<details><summary><b>Cyclic Sort / Index as Hash</b> (2)</summary>

- 🔴 [41. First Missing Positive](https://leetcode.com/problems/first-missing-positive/)
- 🟢 [448. Find All Numbers Disappeared in an Array](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/)

</details>

<details><summary><b>Recursion</b> (2)</summary>

- 🟡 [247. Strobogrammatic Number II](https://leetcode.com/problems/strobogrammatic-number-ii/) 🔒
- 🔴 [248. Strobogrammatic Number III](https://leetcode.com/problems/strobogrammatic-number-iii/) 🔒

</details>

<details><summary><b>String Encoding</b> (1)</summary>

- 🟡 [271. Encode and Decode Strings](https://leetcode.com/problems/encode-and-decode-strings/) 🔒

</details>

## Database (SQL / Pandas)

*SQL queries and Pandas DataFrame problems.* — 338 problems

<details><summary><b>Medium queries</b> (144)</summary>

- 🟡 [176. Second Highest Salary](https://leetcode.com/problems/second-highest-salary/)
- 🟡 [177. Nth Highest Salary](https://leetcode.com/problems/nth-highest-salary/)
- 🟡 [178. Rank Scores](https://leetcode.com/problems/rank-scores/)
- 🟡 [180. Consecutive Numbers](https://leetcode.com/problems/consecutive-numbers/)
- 🟡 [184. Department Highest Salary](https://leetcode.com/problems/department-highest-salary/)
- 🟡 [534. Game Play Analysis III](https://leetcode.com/problems/game-play-analysis-iii/) 🔒
- 🟡 [550. Game Play Analysis IV](https://leetcode.com/problems/game-play-analysis-iv/)
- 🟡 [570. Managers with at Least 5 Direct Reports](https://leetcode.com/problems/managers-with-at-least-5-direct-reports/)
- 🟡 [574. Winning Candidate](https://leetcode.com/problems/winning-candidate/) 🔒
- 🟡 [578. Get Highest Answer Rate Question](https://leetcode.com/problems/get-highest-answer-rate-question/) 🔒
- 🟡 [580. Count Student Number in Departments](https://leetcode.com/problems/count-student-number-in-departments/) 🔒
- 🟡 [585. Investments in 2016](https://leetcode.com/problems/investments-in-2016/)
- 🟡 [602. Friend Requests II: Who Has the Most Friends](https://leetcode.com/problems/friend-requests-ii-who-has-the-most-friends/)
- 🟡 [608. Tree Node](https://leetcode.com/problems/tree-node/)
- 🟡 [612. Shortest Distance in a Plane](https://leetcode.com/problems/shortest-distance-in-a-plane/) 🔒
- 🟡 [614. Second Degree Follower](https://leetcode.com/problems/second-degree-follower/) 🔒
- 🟡 [626. Exchange Seats](https://leetcode.com/problems/exchange-seats/)
- 🟡 [1045. Customers Who Bought All Products](https://leetcode.com/problems/customers-who-bought-all-products/)
- 🟡 [1070. Product Sales Analysis III](https://leetcode.com/problems/product-sales-analysis-iii/)
- 🟡 [1077. Project Employees III](https://leetcode.com/problems/project-employees-iii/) 🔒
- 🟡 [1098. Unpopular Books](https://leetcode.com/problems/unpopular-books/) 🔒
- 🟡 [1107. New Users Daily Count](https://leetcode.com/problems/new-users-daily-count/) 🔒
- 🟡 [1112. Highest Grade For Each Student](https://leetcode.com/problems/highest-grade-for-each-student/) 🔒
- 🟡 [1126. Active Businesses](https://leetcode.com/problems/active-businesses/) 🔒
- 🟡 [1132. Reported Posts II](https://leetcode.com/problems/reported-posts-ii/) 🔒
- 🟡 [1149. Article Views II](https://leetcode.com/problems/article-views-ii/) 🔒
- 🟡 [1158. Market Analysis I](https://leetcode.com/problems/market-analysis-i/)
- 🟡 [1164. Product Price at a Given Date](https://leetcode.com/problems/product-price-at-a-given-date/)
- 🟡 [1174. Immediate Food Delivery II](https://leetcode.com/problems/immediate-food-delivery-ii/)
- 🟡 [1193. Monthly Transactions I](https://leetcode.com/problems/monthly-transactions-i/)
- 🟡 [1204. Last Person to Fit in the Bus](https://leetcode.com/problems/last-person-to-fit-in-the-bus/)
- 🟡 [1205. Monthly Transactions II](https://leetcode.com/problems/monthly-transactions-ii/) 🔒
- 🟡 [1212. Team Scores in Football Tournament](https://leetcode.com/problems/team-scores-in-football-tournament/) 🔒
- 🟡 [1264. Page Recommendations](https://leetcode.com/problems/page-recommendations/) 🔒
- 🟡 [1270. All People Report to the Given Manager](https://leetcode.com/problems/all-people-report-to-the-given-manager/) 🔒
- 🟡 [1285. Find the Start and End Number of Continuous Ranges](https://leetcode.com/problems/find-the-start-and-end-number-of-continuous-ranges/) 🔒
- 🟡 [1308. Running Total for Different Genders](https://leetcode.com/problems/running-total-for-different-genders/) 🔒
- 🟡 [1321. Restaurant Growth](https://leetcode.com/problems/restaurant-growth/)
- 🟡 [1341. Movie Rating](https://leetcode.com/problems/movie-rating/)
- 🟡 [1355. Activity Participants](https://leetcode.com/problems/activity-participants/) 🔒
- 🟡 [1364. Number of Trusted Contacts of a Customer](https://leetcode.com/problems/number-of-trusted-contacts-of-a-customer/) 🔒
- 🟡 [1393. Capital Gain/Loss](https://leetcode.com/problems/capital-gainloss/)
- 🟡 [1398. Customers Who Bought Products A and B but Not C](https://leetcode.com/problems/customers-who-bought-products-a-and-b-but-not-c/) 🔒
- 🟡 [1440. Evaluate Boolean Expression](https://leetcode.com/problems/evaluate-boolean-expression/) 🔒
- 🟡 [1445. Apples & Oranges](https://leetcode.com/problems/apples-oranges/) 🔒
- 🟡 [1454. Active Users](https://leetcode.com/problems/active-users/) 🔒
- 🟡 [1459. Rectangles Area](https://leetcode.com/problems/rectangles-area/) 🔒
- 🟡 [1468. Calculate Salaries](https://leetcode.com/problems/calculate-salaries/) 🔒
- 🟡 [1501. Countries You Can Safely Invest In](https://leetcode.com/problems/countries-you-can-safely-invest-in/) 🔒
- 🟡 [1532. The Most Recent Three Orders](https://leetcode.com/problems/the-most-recent-three-orders/) 🔒
- 🟡 [1549. The Most Recent Orders for Each Product](https://leetcode.com/problems/the-most-recent-orders-for-each-product/) 🔒
- 🟡 [1555. Bank Account Summary](https://leetcode.com/problems/bank-account-summary/) 🔒
- 🟡 [1596. The Most Frequently Ordered Products for Each Customer](https://leetcode.com/problems/the-most-frequently-ordered-products-for-each-customer/) 🔒
- 🟡 [1613. Find the Missing IDs](https://leetcode.com/problems/find-the-missing-ids/) 🔒
- 🟡 [1699. Number of Calls Between Two Persons](https://leetcode.com/problems/number-of-calls-between-two-persons/) 🔒
- 🟡 [1709. Biggest Window Between Visits](https://leetcode.com/problems/biggest-window-between-visits/) 🔒
- 🟡 [1715. Count Apples and Oranges](https://leetcode.com/problems/count-apples-and-oranges/) 🔒
- 🟡 [1747. Leetflex Banned Accounts](https://leetcode.com/problems/leetflex-banned-accounts/) 🔒
- 🟡 [1783. Grand Slam Titles](https://leetcode.com/problems/grand-slam-titles/) 🔒
- 🟡 [1811. Find Interview Candidates](https://leetcode.com/problems/find-interview-candidates/) 🔒
- 🟡 [1831. Maximum Transaction Each Day](https://leetcode.com/problems/maximum-transaction-each-day/) 🔒
- 🟡 [1841. League Statistics](https://leetcode.com/problems/league-statistics/) 🔒
- 🟡 [1843. Suspicious Bank Accounts](https://leetcode.com/problems/suspicious-bank-accounts/) 🔒
- 🟡 [1867. Orders With Maximum Quantity Above Average](https://leetcode.com/problems/orders-with-maximum-quantity-above-average/) 🔒
- 🟡 [1875. Group Employees of the Same Salary](https://leetcode.com/problems/group-employees-of-the-same-salary/) 🔒
- 🟡 [1907. Count Salary Categories](https://leetcode.com/problems/count-salary-categories/)
- 🟡 [1934. Confirmation Rate](https://leetcode.com/problems/confirmation-rate/)
- 🟡 [1949. Strong Friendship](https://leetcode.com/problems/strong-friendship/) 🔒
- 🟡 [1951. All the Pairs With the Maximum Number of Common Followers](https://leetcode.com/problems/all-the-pairs-with-the-maximum-number-of-common-followers/) 🔒
- 🟡 [1988. Find Cutoff Score for Each School](https://leetcode.com/problems/find-cutoff-score-for-each-school/) 🔒
- 🟡 [1990. Count the Number of Experiments](https://leetcode.com/problems/count-the-number-of-experiments/) 🔒
- 🟡 [2020. Number of Accounts That Did Not Stream](https://leetcode.com/problems/number-of-accounts-that-did-not-stream/) 🔒
- 🟡 [2041. Accepted Candidates From the Interviews](https://leetcode.com/problems/accepted-candidates-from-the-interviews/) 🔒
- 🟡 [2051. The Category of Each Member in the Store](https://leetcode.com/problems/the-category-of-each-member-in-the-store/) 🔒
- 🟡 [2066. Account Balance](https://leetcode.com/problems/account-balance/) 🔒
- 🟡 [2084. Drop Type 1 Orders for Customers With Type 0 Orders](https://leetcode.com/problems/drop-type-1-orders-for-customers-with-type-0-orders/) 🔒
- 🟡 [2112. The Airport With the Most Traffic](https://leetcode.com/problems/the-airport-with-the-most-traffic/) 🔒
- 🟡 [2142. The Number of Passengers in Each Bus I](https://leetcode.com/problems/the-number-of-passengers-in-each-bus-i/) 🔒
- 🟡 [2159. Order Two Columns Independently](https://leetcode.com/problems/order-two-columns-independently/) 🔒
- 🟡 [2175. The Change in Global Rankings](https://leetcode.com/problems/the-change-in-global-rankings/) 🔒
- 🟡 [2228. Users With Two Purchases Within Seven Days](https://leetcode.com/problems/users-with-two-purchases-within-seven-days/) 🔒
- 🟡 [2238. Number of Times a Driver Was a Passenger](https://leetcode.com/problems/number-of-times-a-driver-was-a-passenger/) 🔒
- 🟡 [2292. Products With Three or More Orders in Two Consecutive Years](https://leetcode.com/problems/products-with-three-or-more-orders-in-two-consecutive-years/) 🔒
- 🟡 [2298. Tasks Count in the Weekend](https://leetcode.com/problems/tasks-count-in-the-weekend/) 🔒
- 🟡 [2308. Arrange Table by Gender](https://leetcode.com/problems/arrange-table-by-gender/) 🔒
- 🟡 [2314. The First Day of the Maximum Recorded Degree in Each City](https://leetcode.com/problems/the-first-day-of-the-maximum-recorded-degree-in-each-city/) 🔒
- 🟡 [2324. Product Sales Analysis IV](https://leetcode.com/problems/product-sales-analysis-iv/) 🔒
- 🟡 [2346. Compute the Rank as a Percentage](https://leetcode.com/problems/compute-the-rank-as-a-percentage/) 🔒
- 🟡 [2372. Calculate the Influence of Each Salesperson](https://leetcode.com/problems/calculate-the-influence-of-each-salesperson/) 🔒
- 🟡 [2388. Change Null Values in a Table to the Previous Value](https://leetcode.com/problems/change-null-values-in-a-table-to-the-previous-value/) 🔒
- 🟡 [2394. Employees With Deductions](https://leetcode.com/problems/employees-with-deductions/) 🔒
- 🟡 [2686. Immediate Food Delivery III](https://leetcode.com/problems/immediate-food-delivery-iii/) 🔒
- 🟡 [2688. Find Active Users](https://leetcode.com/problems/find-active-users/) 🔒
- 🟡 [2738. Count Occurrences in Text](https://leetcode.com/problems/count-occurrences-in-text/) 🔒
- 🟡 [2783. Flight Occupancy and Waitlist Analysis](https://leetcode.com/problems/flight-occupancy-and-waitlist-analysis/) 🔒
- 🟡 [2820. Election Results](https://leetcode.com/problems/election-results/) 🔒
- 🟡 [2854. Rolling Average Steps](https://leetcode.com/problems/rolling-average-steps/) 🔒
- 🟡 [2893. Calculate Orders Within Each Interval](https://leetcode.com/problems/calculate-orders-within-each-interval/) 🔒
- 🟡 [2922. Market Analysis III](https://leetcode.com/problems/market-analysis-iii/) 🔒
- 🟡 [2978. Symmetric Coordinates](https://leetcode.com/problems/symmetric-coordinates/) 🔒
- 🟡 [2984. Find Peak Calling Hours for Each City](https://leetcode.com/problems/find-peak-calling-hours-for-each-city/) 🔒
- 🟡 [2986. Find Third Transaction](https://leetcode.com/problems/find-third-transaction/) 🔒
- 🟡 [2988. Manager of the Largest Department](https://leetcode.com/problems/manager-of-the-largest-department/) 🔒
- 🟡 [2989. Class Performance](https://leetcode.com/problems/class-performance/) 🔒
- 🟡 [2993. Friday Purchases I](https://leetcode.com/problems/friday-purchases-i/) 🔒
- 🟡 [3050. Pizza Toppings Cost Analysis](https://leetcode.com/problems/pizza-toppings-cost-analysis/) 🔒
- 🟡 [3054. Binary Tree Nodes](https://leetcode.com/problems/binary-tree-nodes/) 🔒
- 🟡 [3055. Top Percentile Fraud](https://leetcode.com/problems/top-percentile-fraud/) 🔒
- 🟡 [3056. Snaps Analysis](https://leetcode.com/problems/snaps-analysis/) 🔒
- 🟡 [3058. Friends With No Mutual Friends](https://leetcode.com/problems/friends-with-no-mutual-friends/) 🔒
- 🟡 [3087. Find Trending Hashtags](https://leetcode.com/problems/find-trending-hashtags/) 🔒
- 🟡 [3089. Find Bursty Behavior](https://leetcode.com/problems/find-bursty-behavior/) 🔒
- 🟡 [3118. Friday Purchase III ](https://leetcode.com/problems/friday-purchase-iii/) 🔒
- 🟡 [3124. Find Longest Calls](https://leetcode.com/problems/find-longest-calls/) 🔒
- 🟡 [3126. Server Utilization Time](https://leetcode.com/problems/server-utilization-time/) 🔒
- 🟡 [3140. Consecutive Available Seats II](https://leetcode.com/problems/consecutive-available-seats-ii/) 🔒
- 🟡 [3166. Calculate Parking Fees and Duration](https://leetcode.com/problems/calculate-parking-fees-and-duration/) 🔒
- 🟡 [3182. Find Top Scoring Students](https://leetcode.com/problems/find-top-scoring-students/) 🔒
- 🟡 [3204. Bitwise User Permissions Analysis](https://leetcode.com/problems/bitwise-user-permissions-analysis/) 🔒
- 🟡 [3220. Odd and Even Transactions](https://leetcode.com/problems/odd-and-even-transactions/)
- 🟡 [3230. Customer Purchasing Behavior Analysis](https://leetcode.com/problems/customer-purchasing-behavior-analysis/) 🔒
- 🟡 [3252. Premier League Table Ranking II](https://leetcode.com/problems/premier-league-table-ranking-ii/) 🔒
- 🟡 [3262. Find Overlapping Shifts](https://leetcode.com/problems/find-overlapping-shifts/) 🔒
- 🟡 [3278. Find Candidates for Data Scientist Position II](https://leetcode.com/problems/find-candidates-for-data-scientist-position-ii/) 🔒
- 🟡 [3293. Calculate Product Final Price](https://leetcode.com/problems/calculate-product-final-price/) 🔒
- 🟡 [3308. Find Top Performing Driver](https://leetcode.com/problems/find-top-performing-driver/) 🔒
- 🟡 [3322. Premier League Table Ranking III](https://leetcode.com/problems/premier-league-table-ranking-iii/) 🔒
- 🟡 [3328. Find Cities in Each State II](https://leetcode.com/problems/find-cities-in-each-state-ii/) 🔒
- 🟡 [3338. Second Highest Salary II](https://leetcode.com/problems/second-highest-salary-ii/) 🔒
- 🟡 [3421. Find Students Who Improved](https://leetcode.com/problems/find-students-who-improved/)
- 🟡 [3475. DNA Pattern Recognition ](https://leetcode.com/problems/dna-pattern-recognition/)
- 🟡 [3497. Analyze Subscription Conversion ](https://leetcode.com/problems/analyze-subscription-conversion/)
- 🟡 [3521. Find Product Recommendation Pairs](https://leetcode.com/problems/find-product-recommendation-pairs/)
- 🟡 [3564. Seasonal Sales Analysis](https://leetcode.com/problems/seasonal-sales-analysis/)
- 🟡 [3580. Find Consistently Improving Employees](https://leetcode.com/problems/find-consistently-improving-employees/)
- 🟡 [3586. Find COVID Recovery Patients](https://leetcode.com/problems/find-covid-recovery-patients/)
- 🟡 [3601. Find Drivers with Improved Fuel Efficiency](https://leetcode.com/problems/find-drivers-with-improved-fuel-efficiency/)
- 🟡 [3611. Find Overbooked Employees](https://leetcode.com/problems/find-overbooked-employees/)
- 🟡 [3626. Find Stores with Inventory Imbalance](https://leetcode.com/problems/find-stores-with-inventory-imbalance/)
- 🟡 [3642. Find Books with Polarized Opinions](https://leetcode.com/problems/find-books-with-polarized-opinions/)
- 🟡 [3657. Find Loyal Customers](https://leetcode.com/problems/find-loyal-customers/)
- 🟡 [3705. Find Golden Hour Customers](https://leetcode.com/problems/find-golden-hour-customers/)
- 🟡 [3716. Find Churn Risk Customers](https://leetcode.com/problems/find-churn-risk-customers/)
- 🟡 [3808. Find Emotionally Consistent Users](https://leetcode.com/problems/find-emotionally-consistent-users/)

</details>

<details><summary><b>Easy queries</b> (128)</summary>

- 🟢 [175. Combine Two Tables](https://leetcode.com/problems/combine-two-tables/)
- 🟢 [181. Employees Earning More Than Their Managers](https://leetcode.com/problems/employees-earning-more-than-their-managers/)
- 🟢 [182. Duplicate Emails](https://leetcode.com/problems/duplicate-emails/)
- 🟢 [183. Customers Who Never Order](https://leetcode.com/problems/customers-who-never-order/)
- 🟢 [196. Delete Duplicate Emails](https://leetcode.com/problems/delete-duplicate-emails/)
- 🟢 [197. Rising Temperature](https://leetcode.com/problems/rising-temperature/)
- 🟢 [511. Game Play Analysis I](https://leetcode.com/problems/game-play-analysis-i/)
- 🟢 [512. Game Play Analysis II](https://leetcode.com/problems/game-play-analysis-ii/) 🔒
- 🟢 [577. Employee Bonus](https://leetcode.com/problems/employee-bonus/)
- 🟢 [584. Find Customer Referee](https://leetcode.com/problems/find-customer-referee/)
- 🟢 [586. Customer Placing the Largest Number of Orders](https://leetcode.com/problems/customer-placing-the-largest-number-of-orders/)
- 🟢 [595. Big Countries](https://leetcode.com/problems/big-countries/)
- 🟢 [596. Classes With at Least 5 Students](https://leetcode.com/problems/classes-with-at-least-5-students/)
- 🟢 [597. Friend Requests I: Overall Acceptance Rate](https://leetcode.com/problems/friend-requests-i-overall-acceptance-rate/) 🔒
- 🟢 [603. Consecutive Available Seats](https://leetcode.com/problems/consecutive-available-seats/) 🔒
- 🟢 [607. Sales Person](https://leetcode.com/problems/sales-person/)
- 🟢 [610. Triangle Judgement](https://leetcode.com/problems/triangle-judgement/)
- 🟢 [613. Shortest Distance in a Line](https://leetcode.com/problems/shortest-distance-in-a-line/) 🔒
- 🟢 [619. Biggest Single Number](https://leetcode.com/problems/biggest-single-number/)
- 🟢 [620. Not Boring Movies](https://leetcode.com/problems/not-boring-movies/)
- 🟢 [627. Swap Sex of Employees](https://leetcode.com/problems/swap-sex-of-employees/)
- 🟢 [1050. Actors and Directors Who Cooperated At Least Three Times](https://leetcode.com/problems/actors-and-directors-who-cooperated-at-least-three-times/)
- 🟢 [1068. Product Sales Analysis I](https://leetcode.com/problems/product-sales-analysis-i/)
- 🟢 [1069. Product Sales Analysis II](https://leetcode.com/problems/product-sales-analysis-ii/) 🔒
- 🟢 [1075. Project Employees I](https://leetcode.com/problems/project-employees-i/)
- 🟢 [1076. Project Employees II](https://leetcode.com/problems/project-employees-ii/) 🔒
- 🟢 [1082. Sales Analysis I](https://leetcode.com/problems/sales-analysis-i/) 🔒
- 🟢 [1083. Sales Analysis II](https://leetcode.com/problems/sales-analysis-ii/) 🔒
- 🟢 [1084. Sales Analysis III](https://leetcode.com/problems/sales-analysis-iii/)
- 🟢 [1113. Reported Posts](https://leetcode.com/problems/reported-posts/) 🔒
- 🟢 [1141. User Activity for the Past 30 Days I](https://leetcode.com/problems/user-activity-for-the-past-30-days-i/)
- 🟢 [1142. User Activity for the Past 30 Days II](https://leetcode.com/problems/user-activity-for-the-past-30-days-ii/) 🔒
- 🟢 [1148. Article Views I](https://leetcode.com/problems/article-views-i/)
- 🟢 [1173. Immediate Food Delivery I](https://leetcode.com/problems/immediate-food-delivery-i/) 🔒
- 🟢 [1179. Reformat Department Table](https://leetcode.com/problems/reformat-department-table/)
- 🟢 [1211. Queries Quality and Percentage](https://leetcode.com/problems/queries-quality-and-percentage/)
- 🟢 [1241. Number of Comments per Post](https://leetcode.com/problems/number-of-comments-per-post/) 🔒
- 🟢 [1251. Average Selling Price](https://leetcode.com/problems/average-selling-price/)
- 🟢 [1280. Students and Examinations](https://leetcode.com/problems/students-and-examinations/)
- 🟢 [1294. Weather Type in Each Country](https://leetcode.com/problems/weather-type-in-each-country/) 🔒
- 🟢 [1303. Find the Team Size](https://leetcode.com/problems/find-the-team-size/) 🔒
- 🟢 [1322. Ads Performance](https://leetcode.com/problems/ads-performance/) 🔒
- 🟢 [1327. List the Products Ordered in a Period](https://leetcode.com/problems/list-the-products-ordered-in-a-period/)
- 🟢 [1350. Students With Invalid Departments](https://leetcode.com/problems/students-with-invalid-departments/) 🔒
- 🟢 [1378. Replace Employee ID With The Unique Identifier](https://leetcode.com/problems/replace-employee-id-with-the-unique-identifier/)
- 🟢 [1407. Top Travellers](https://leetcode.com/problems/top-travellers/)
- 🟢 [1421. NPV Queries](https://leetcode.com/problems/npv-queries/) 🔒
- 🟢 [1435. Create a Session Bar Chart](https://leetcode.com/problems/create-a-session-bar-chart/) 🔒
- 🟢 [1484. Group Sold Products By The Date](https://leetcode.com/problems/group-sold-products-by-the-date/)
- 🟢 [1495. Friendly Movies Streamed Last Month](https://leetcode.com/problems/friendly-movies-streamed-last-month/) 🔒
- 🟢 [1511. Customer Order Frequency](https://leetcode.com/problems/customer-order-frequency/) 🔒
- 🟢 [1517. Find Users With Valid E-Mails](https://leetcode.com/problems/find-users-with-valid-e-mails/)
- 🟢 [1527. Patients With a Condition](https://leetcode.com/problems/patients-with-a-condition/)
- 🟢 [1543. Fix Product Name Format](https://leetcode.com/problems/fix-product-name-format/) 🔒
- 🟢 [1565. Unique Orders and Customers Per Month](https://leetcode.com/problems/unique-orders-and-customers-per-month/) 🔒
- 🟢 [1571. Warehouse Manager](https://leetcode.com/problems/warehouse-manager/) 🔒
- 🟢 [1581. Customer Who Visited but Did Not Make Any Transactions](https://leetcode.com/problems/customer-who-visited-but-did-not-make-any-transactions/)
- 🟢 [1587. Bank Account Summary II](https://leetcode.com/problems/bank-account-summary-ii/)
- 🟢 [1607. Sellers With No Sales](https://leetcode.com/problems/sellers-with-no-sales/) 🔒
- 🟢 [1623. All Valid Triplets That Can Represent a Country](https://leetcode.com/problems/all-valid-triplets-that-can-represent-a-country/) 🔒
- 🟢 [1633. Percentage of Users Attended a Contest](https://leetcode.com/problems/percentage-of-users-attended-a-contest/)
- 🟢 [1661. Average Time of Process per Machine](https://leetcode.com/problems/average-time-of-process-per-machine/)
- 🟢 [1667. Fix Names in a Table](https://leetcode.com/problems/fix-names-in-a-table/)
- 🟢 [1677. Product's Worth Over Invoices](https://leetcode.com/problems/products-worth-over-invoices/) 🔒
- 🟢 [1683. Invalid Tweets](https://leetcode.com/problems/invalid-tweets/)
- 🟢 [1693. Daily Leads and Partners](https://leetcode.com/problems/daily-leads-and-partners/)
- 🟢 [1729. Find Followers Count](https://leetcode.com/problems/find-followers-count/)
- 🟢 [1731. The Number of Employees Which Report to Each Employee](https://leetcode.com/problems/the-number-of-employees-which-report-to-each-employee/)
- 🟢 [1741. Find Total Time Spent by Each Employee](https://leetcode.com/problems/find-total-time-spent-by-each-employee/)
- 🟢 [1757. Recyclable and Low Fat Products](https://leetcode.com/problems/recyclable-and-low-fat-products/)
- 🟢 [1777. Product's Price for Each Store](https://leetcode.com/problems/products-price-for-each-store/) 🔒
- 🟢 [1789. Primary Department for Each Employee](https://leetcode.com/problems/primary-department-for-each-employee/)
- 🟢 [1795. Rearrange Products Table](https://leetcode.com/problems/rearrange-products-table/)
- 🟢 [1809. Ad-Free Sessions](https://leetcode.com/problems/ad-free-sessions/) 🔒
- 🟢 [1821. Find Customers With Positive Revenue this Year](https://leetcode.com/problems/find-customers-with-positive-revenue-this-year/) 🔒
- 🟢 [1853. Convert Date Format](https://leetcode.com/problems/convert-date-format/) 🔒
- 🟢 [1873. Calculate Special Bonus](https://leetcode.com/problems/calculate-special-bonus/)
- 🟢 [1890. The Latest Login in 2020](https://leetcode.com/problems/the-latest-login-in-2020/)
- 🟢 [1939. Users That Actively Request Confirmation Messages](https://leetcode.com/problems/users-that-actively-request-confirmation-messages/) 🔒
- 🟢 [1965. Employees With Missing Information](https://leetcode.com/problems/employees-with-missing-information/)
- 🟢 [1978. Employees Whose Manager Left the Company](https://leetcode.com/problems/employees-whose-manager-left-the-company/)
- 🟢 [2026. Low-Quality Problems](https://leetcode.com/problems/low-quality-problems/) 🔒
- 🟢 [2072. The Winner University](https://leetcode.com/problems/the-winner-university/) 🔒
- 🟢 [2082. The Number of Rich Customers](https://leetcode.com/problems/the-number-of-rich-customers/) 🔒
- 🟢 [2205. The Number of Users That Are Eligible for Discount](https://leetcode.com/problems/the-number-of-users-that-are-eligible-for-discount/) 🔒
- 🟢 [2230. The Users That Are Eligible for Discount](https://leetcode.com/problems/the-users-that-are-eligible-for-discount/) 🔒
- 🟢 [2329. Product Sales Analysis V](https://leetcode.com/problems/product-sales-analysis-v/) 🔒
- 🟢 [2339. All the Matches of the League](https://leetcode.com/problems/all-the-matches-of-the-league/) 🔒
- 🟢 [2356. Number of Unique Subjects Taught by Each Teacher](https://leetcode.com/problems/number-of-unique-subjects-taught-by-each-teacher/)
- 🟢 [2377. Sort the Olympic Table](https://leetcode.com/problems/sort-the-olympic-table/) 🔒
- 🟢 [2480. Form a Chemical Bond](https://leetcode.com/problems/form-a-chemical-bond/) 🔒
- 🟢 [2504. Concatenate the Name and the Profession](https://leetcode.com/problems/concatenate-the-name-and-the-profession/) 🔒
- 🟢 [2668. Find Latest Salaries](https://leetcode.com/problems/find-latest-salaries/) 🔒
- 🟢 [2669. Count Artist Occurrences On Spotify Ranking List](https://leetcode.com/problems/count-artist-occurrences-on-spotify-ranking-list/) 🔒
- 🟢 [2687. Bikes Last Time Used ](https://leetcode.com/problems/bikes-last-time-used/) 🔒
- 🟢 [2837. Total Traveled Distance](https://leetcode.com/problems/total-traveled-distance/) 🔒
- 🟢 [2853. Highest Salaries Difference](https://leetcode.com/problems/highest-salaries-difference/) 🔒
- 🟢 [2877. Create a DataFrame from List](https://leetcode.com/problems/create-a-dataframe-from-list/)
- 🟢 [2878. Get the Size of a DataFrame](https://leetcode.com/problems/get-the-size-of-a-dataframe/)
- 🟢 [2879. Display the First Three Rows](https://leetcode.com/problems/display-the-first-three-rows/)
- 🟢 [2880. Select Data](https://leetcode.com/problems/select-data/)
- 🟢 [2881. Create a New Column](https://leetcode.com/problems/create-a-new-column/)
- 🟢 [2882. Drop Duplicate Rows](https://leetcode.com/problems/drop-duplicate-rows/)
- 🟢 [2883. Drop Missing Data](https://leetcode.com/problems/drop-missing-data/)
- 🟢 [2884. Modify Columns](https://leetcode.com/problems/modify-columns/)
- 🟢 [2885. Rename Columns](https://leetcode.com/problems/rename-columns/)
- 🟢 [2886. Change Data Type](https://leetcode.com/problems/change-data-type/)
- 🟢 [2887. Fill Missing Data](https://leetcode.com/problems/fill-missing-data/)
- 🟢 [2888. Reshape Data: Concatenate](https://leetcode.com/problems/reshape-data-concatenate/)
- 🟢 [2889. Reshape Data: Pivot](https://leetcode.com/problems/reshape-data-pivot/)
- 🟢 [2890. Reshape Data: Melt](https://leetcode.com/problems/reshape-data-melt/)
- 🟢 [2891. Method Chaining](https://leetcode.com/problems/method-chaining/)
- 🟢 [2985. Calculate Compressed Mean](https://leetcode.com/problems/calculate-compressed-mean/) 🔒
- 🟢 [2987. Find Expensive Cities](https://leetcode.com/problems/find-expensive-cities/) 🔒
- 🟢 [2990. Loan Types](https://leetcode.com/problems/loan-types/) 🔒
- 🟢 [3051. Find Candidates for Data Scientist Position](https://leetcode.com/problems/find-candidates-for-data-scientist-position/) 🔒
- 🟢 [3053. Classifying Triangles by Lengths](https://leetcode.com/problems/classifying-triangles-by-lengths/) 🔒
- 🟢 [3059. Find All Unique Email Domains](https://leetcode.com/problems/find-all-unique-email-domains/) 🔒
- 🟢 [3150. Invalid Tweets II](https://leetcode.com/problems/invalid-tweets-ii/) 🔒
- 🟢 [3172. Second Day Verification](https://leetcode.com/problems/second-day-verification/) 🔒
- 🟢 [3198. Find Cities in Each State](https://leetcode.com/problems/find-cities-in-each-state/) 🔒
- 🟢 [3246. Premier League Table Ranking](https://leetcode.com/problems/premier-league-table-ranking/) 🔒
- 🟢 [3358. Books with NULL Ratings](https://leetcode.com/problems/books-with-null-ratings/) 🔒
- 🟢 [3415. Find Products with Three Consecutive Digits ](https://leetcode.com/problems/find-products-with-three-consecutive-digits/) 🔒
- 🟢 [3436. Find Valid Emails](https://leetcode.com/problems/find-valid-emails/)
- 🟢 [3465. Find Products with Valid Serial Numbers](https://leetcode.com/problems/find-products-with-valid-serial-numbers/)
- 🟢 [3570. Find Books with No Available Copies](https://leetcode.com/problems/find-books-with-no-available-copies/)
- 🟢 [3793. Find Users with High Token Usage](https://leetcode.com/problems/find-users-with-high-token-usage/)

</details>

<details><summary><b>Hard queries</b> (66)</summary>

- 🔴 [185. Department Top Three Salaries](https://leetcode.com/problems/department-top-three-salaries/)
- 🔴 [262. Trips and Users](https://leetcode.com/problems/trips-and-users/)
- 🔴 [569. Median Employee Salary](https://leetcode.com/problems/median-employee-salary/) 🔒
- 🔴 [571. Find Median Given Frequency of Numbers](https://leetcode.com/problems/find-median-given-frequency-of-numbers/) 🔒
- 🔴 [579. Find Cumulative Salary of an Employee](https://leetcode.com/problems/find-cumulative-salary-of-an-employee/) 🔒
- 🔴 [601. Human Traffic of Stadium](https://leetcode.com/problems/human-traffic-of-stadium/)
- 🔴 [615. Average Salary: Departments VS Company](https://leetcode.com/problems/average-salary-departments-vs-company/) 🔒
- 🔴 [618. Students Report By Geography](https://leetcode.com/problems/students-report-by-geography/) 🔒
- 🔴 [1097. Game Play Analysis V](https://leetcode.com/problems/game-play-analysis-v/) 🔒
- 🔴 [1127. User Purchase Platform](https://leetcode.com/problems/user-purchase-platform/) 🔒
- 🔴 [1159. Market Analysis II](https://leetcode.com/problems/market-analysis-ii/) 🔒
- 🔴 [1194. Tournament Winners](https://leetcode.com/problems/tournament-winners/) 🔒
- 🔴 [1225. Report Contiguous Dates](https://leetcode.com/problems/report-contiguous-dates/) 🔒
- 🔴 [1336. Number of Transactions per Visit](https://leetcode.com/problems/number-of-transactions-per-visit/) 🔒
- 🔴 [1369. Get the Second Most Recent Activity](https://leetcode.com/problems/get-the-second-most-recent-activity/) 🔒
- 🔴 [1384. Total Sales Amount by Year](https://leetcode.com/problems/total-sales-amount-by-year/) 🔒
- 🔴 [1412. Find the Quiet Students in All Exams](https://leetcode.com/problems/find-the-quiet-students-in-all-exams/) 🔒
- 🔴 [1479. Sales by Day of the Week](https://leetcode.com/problems/sales-by-day-of-the-week/) 🔒
- 🔴 [1635. Hopper Company Queries I](https://leetcode.com/problems/hopper-company-queries-i/) 🔒
- 🔴 [1645. Hopper Company Queries II](https://leetcode.com/problems/hopper-company-queries-ii/) 🔒
- 🔴 [1651. Hopper Company Queries III](https://leetcode.com/problems/hopper-company-queries-iii/) 🔒
- 🔴 [1767. Find the Subtasks That Did Not Execute](https://leetcode.com/problems/find-the-subtasks-that-did-not-execute/) 🔒
- 🔴 [1892. Page Recommendations II](https://leetcode.com/problems/page-recommendations-ii/) 🔒
- 🔴 [1917. Leetcodify Friends Recommendations](https://leetcode.com/problems/leetcodify-friends-recommendations/) 🔒
- 🔴 [1919. Leetcodify Similar Friends](https://leetcode.com/problems/leetcodify-similar-friends/) 🔒
- 🔴 [1972. First and Last Call On the Same Day](https://leetcode.com/problems/first-and-last-call-on-the-same-day/) 🔒
- 🔴 [2004. The Number of Seniors and Juniors to Join the Company](https://leetcode.com/problems/the-number-of-seniors-and-juniors-to-join-the-company/) 🔒
- 🔴 [2010. The Number of Seniors and Juniors to Join the Company II](https://leetcode.com/problems/the-number-of-seniors-and-juniors-to-join-the-company-ii/) 🔒
- 🔴 [2118. Build the Equation](https://leetcode.com/problems/build-the-equation/) 🔒
- 🔴 [2153. The Number of Passengers in Each Bus II](https://leetcode.com/problems/the-number-of-passengers-in-each-bus-ii/) 🔒
- 🔴 [2173. Longest Winning Streak](https://leetcode.com/problems/longest-winning-streak/) 🔒
- 🔴 [2199. Finding the Topic of Each Post](https://leetcode.com/problems/finding-the-topic-of-each-post/) 🔒
- 🔴 [2252. Dynamic Pivoting of a Table](https://leetcode.com/problems/dynamic-pivoting-of-a-table/) 🔒
- 🔴 [2253. Dynamic Unpivoting of a Table](https://leetcode.com/problems/dynamic-unpivoting-of-a-table/) 🔒
- 🔴 [2362. Generate the Invoice](https://leetcode.com/problems/generate-the-invoice/) 🔒
- 🔴 [2474. Customers With Strictly Increasing Purchases](https://leetcode.com/problems/customers-with-strictly-increasing-purchases/) 🔒
- 🔴 [2494. Merge Overlapping Events in the Same Hall](https://leetcode.com/problems/merge-overlapping-events-in-the-same-hall/) 🔒
- 🔴 [2701. Consecutive Transactions with Increasing Amounts](https://leetcode.com/problems/consecutive-transactions-with-increasing-amounts/) 🔒
- 🔴 [2720. Popularity Percentage](https://leetcode.com/problems/popularity-percentage/) 🔒
- 🔴 [2752. Customers with Maximum Number of Transactions on Consecutive Days](https://leetcode.com/problems/customers-with-maximum-number-of-transactions-on-consecutive-days/) 🔒
- 🔴 [2793. Status of Flight Tickets](https://leetcode.com/problems/status-of-flight-tickets/) 🔒
- 🔴 [2991. Top Three Wineries ](https://leetcode.com/problems/top-three-wineries/) 🔒
- 🔴 [2994. Friday Purchases II ](https://leetcode.com/problems/friday-purchases-ii/) 🔒
- 🔴 [2995. Viewers Turned Streamers](https://leetcode.com/problems/viewers-turned-streamers/) 🔒
- 🔴 [3052. Maximize Items](https://leetcode.com/problems/maximize-items/) 🔒
- 🔴 [3057. Employees Project Allocation](https://leetcode.com/problems/employees-project-allocation/) 🔒
- 🔴 [3060. User Activities within Time Bounds](https://leetcode.com/problems/user-activities-within-time-bounds/) 🔒
- 🔴 [3061. Calculate Trapping Rain Water](https://leetcode.com/problems/calculate-trapping-rain-water/) 🔒
- 🔴 [3103. Find Trending Hashtags II ](https://leetcode.com/problems/find-trending-hashtags-ii/) 🔒
- 🔴 [3156. Employee Task Duration and Concurrent Tasks](https://leetcode.com/problems/employee-task-duration-and-concurrent-tasks/) 🔒
- 🔴 [3188. Find Top Scoring Students II](https://leetcode.com/problems/find-top-scoring-students-ii/) 🔒
- 🔴 [3214. Year on Year Growth Rate](https://leetcode.com/problems/year-on-year-growth-rate/) 🔒
- 🔴 [3236. CEO Subordinate Hierarchy](https://leetcode.com/problems/ceo-subordinate-hierarchy/) 🔒
- 🔴 [3268. Find Overlapping Shifts II](https://leetcode.com/problems/find-overlapping-shifts-ii/) 🔒
- 🔴 [3368. First Letter Capitalization](https://leetcode.com/problems/first-letter-capitalization/) 🔒
- 🔴 [3374. First Letter Capitalization II](https://leetcode.com/problems/first-letter-capitalization-ii/)
- 🔴 [3384. Team Dominance by Pass Success](https://leetcode.com/problems/team-dominance-by-pass-success/) 🔒
- 🔴 [3390. Longest Team Pass Streak](https://leetcode.com/problems/longest-team-pass-streak/) 🔒
- 🔴 [3401. Find Circular Gift Exchange Chains](https://leetcode.com/problems/find-circular-gift-exchange-chains/) 🔒
- 🔴 [3451. Find Invalid IP Addresses](https://leetcode.com/problems/find-invalid-ip-addresses/)
- 🔴 [3482. Analyze Organization Hierarchy](https://leetcode.com/problems/analyze-organization-hierarchy/)
- 🔴 [3554. Find Category Recommendation Pairs](https://leetcode.com/problems/find-category-recommendation-pairs/)
- 🔴 [3617. Find Students with Study Spiral Pattern](https://leetcode.com/problems/find-students-with-study-spiral-pattern/)
- 🔴 [3673. Find Zombie Sessions](https://leetcode.com/problems/find-zombie-sessions/)
- 🔴 [3764. Most Common Course Pairs](https://leetcode.com/problems/most-common-course-pairs/)
- 🔴 [3832. Find Users with Persistent Behavior Patterns](https://leetcode.com/problems/find-users-with-persistent-behavior-patterns/)

</details>

## JavaScript

*Closures, promises, debounce, the '30 Days of JavaScript' set.* — 67 problems

<details><summary><b>JavaScript</b> (67)</summary>

- 🟡 [2618. Check if Object Instance of Class](https://leetcode.com/problems/check-if-object-instance-of-class/)
- 🟢 [2619. Array Prototype Last](https://leetcode.com/problems/array-prototype-last/)
- 🟢 [2620. Counter](https://leetcode.com/problems/counter/)
- 🟢 [2621. Sleep](https://leetcode.com/problems/sleep/)
- 🟡 [2622. Cache With Time Limit](https://leetcode.com/problems/cache-with-time-limit/)
- 🟡 [2623. Memoize](https://leetcode.com/problems/memoize/)
- 🟡 [2624. Snail Traversal](https://leetcode.com/problems/snail-traversal/)
- 🟡 [2625. Flatten Deeply Nested Array](https://leetcode.com/problems/flatten-deeply-nested-array/)
- 🟢 [2626. Array Reduce Transformation](https://leetcode.com/problems/array-reduce-transformation/)
- 🟡 [2627. Debounce](https://leetcode.com/problems/debounce/)
- 🟡 [2628. JSON Deep Equal](https://leetcode.com/problems/json-deep-equal/) 🔒
- 🟢 [2629. Function Composition](https://leetcode.com/problems/function-composition/)
- 🔴 [2630. Memoize II](https://leetcode.com/problems/memoize-ii/)
- 🟡 [2631. Group By](https://leetcode.com/problems/group-by/)
- 🟡 [2632. Curry](https://leetcode.com/problems/curry/) 🔒
- 🟡 [2633. Convert Object to JSON String](https://leetcode.com/problems/convert-object-to-json-string/) 🔒
- 🟢 [2634. Filter Elements from Array](https://leetcode.com/problems/filter-elements-from-array/)
- 🟢 [2635. Apply Transform Over Each Element in Array](https://leetcode.com/problems/apply-transform-over-each-element-in-array/)
- 🟡 [2636. Promise Pool](https://leetcode.com/problems/promise-pool/) 🔒
- 🟡 [2637. Promise Time Limit](https://leetcode.com/problems/promise-time-limit/)
- 🟢 [2648. Generate Fibonacci Sequence](https://leetcode.com/problems/generate-fibonacci-sequence/)
- 🟡 [2649. Nested Array Generator](https://leetcode.com/problems/nested-array-generator/)
- 🔴 [2650. Design Cancellable Function](https://leetcode.com/problems/design-cancellable-function/)
- 🟢 [2665. Counter II](https://leetcode.com/problems/counter-ii/)
- 🟢 [2666. Allow One Function Call](https://leetcode.com/problems/allow-one-function-call/)
- 🟢 [2667. Create Hello World Function](https://leetcode.com/problems/create-hello-world-function/)
- 🔴 [2675. Array of Objects to Matrix](https://leetcode.com/problems/array-of-objects-to-matrix/) 🔒
- 🟡 [2676. Throttle](https://leetcode.com/problems/throttle/) 🔒
- 🟢 [2677. Chunk Array](https://leetcode.com/problems/chunk-array/)
- 🟢 [2690. Infinite Method Object](https://leetcode.com/problems/infinite-method-object/) 🔒
- 🔴 [2691. Immutability Helper](https://leetcode.com/problems/immutability-helper/) 🔒
- 🟡 [2692. Make Object Immutable](https://leetcode.com/problems/make-object-immutable/) 🔒
- 🟡 [2693. Call Function with Custom Context](https://leetcode.com/problems/call-function-with-custom-context/)
- 🟡 [2694. Event Emitter](https://leetcode.com/problems/event-emitter/)
- 🟢 [2695. Array Wrapper](https://leetcode.com/problems/array-wrapper/)
- 🟡 [2700. Differences Between Two Objects](https://leetcode.com/problems/differences-between-two-objects/) 🔒
- 🟢 [2703. Return Length of Arguments Passed](https://leetcode.com/problems/return-length-of-arguments-passed/)
- 🟢 [2704. To Be Or Not To Be](https://leetcode.com/problems/to-be-or-not-to-be/)
- 🟡 [2705. Compact Object](https://leetcode.com/problems/compact-object/)
- 🟢 [2715. Timeout Cancellation](https://leetcode.com/problems/timeout-cancellation/)
- 🟡 [2721. Execute Asynchronous Functions in Parallel](https://leetcode.com/problems/execute-asynchronous-functions-in-parallel/)
- 🟡 [2722. Join Two Arrays by ID](https://leetcode.com/problems/join-two-arrays-by-id/)
- 🟢 [2723. Add Two Promises](https://leetcode.com/problems/add-two-promises/)
- 🟢 [2724. Sort By](https://leetcode.com/problems/sort-by/)
- 🟢 [2725. Interval Cancellation](https://leetcode.com/problems/interval-cancellation/)
- 🟢 [2726. Calculator with Method Chaining](https://leetcode.com/problems/calculator-with-method-chaining/)
- 🟢 [2727. Is Object Empty](https://leetcode.com/problems/is-object-empty/)
- 🟡 [2754. Bind Function to Context](https://leetcode.com/problems/bind-function-to-context/) 🔒
- 🟡 [2755. Deep Merge of Two Objects](https://leetcode.com/problems/deep-merge-of-two-objects/) 🔒
- 🔴 [2756. Query Batching](https://leetcode.com/problems/query-batching/) 🔒
- 🟡 [2757. Generate Circular Array Values](https://leetcode.com/problems/generate-circular-array-values/) 🔒
- 🟢 [2758. Next Day](https://leetcode.com/problems/next-day/) 🔒
- 🔴 [2759. Convert JSON String to Object](https://leetcode.com/problems/convert-json-string-to-object/) 🔒
- 🟢 [2774. Array Upper Bound](https://leetcode.com/problems/array-upper-bound/) 🔒
- 🟡 [2775. Undefined to Null](https://leetcode.com/problems/undefined-to-null/) 🔒
- 🟡 [2776. Convert Callback Based Function to Promise Based Function](https://leetcode.com/problems/convert-callback-based-function-to-promise-based-function/) 🔒
- 🟡 [2777. Date Range Generator](https://leetcode.com/problems/date-range-generator/) 🔒
- 🟢 [2794. Create Object from Two Arrays](https://leetcode.com/problems/create-object-from-two-arrays/) 🔒
- 🟡 [2795. Parallel Execution of Promises for Individual Results Retrieval](https://leetcode.com/problems/parallel-execution-of-promises-for-individual-results-retrieval/) 🔒
- 🟢 [2796. Repeat String](https://leetcode.com/problems/repeat-string/) 🔒
- 🟢 [2797. Partial Function with Placeholders](https://leetcode.com/problems/partial-function-with-placeholders/) 🔒
- 🟢 [2803. Factorial Generator](https://leetcode.com/problems/factorial-generator/) 🔒
- 🟢 [2804. Array Prototype ForEach](https://leetcode.com/problems/array-prototype-foreach/) 🔒
- 🟡 [2805. Custom Interval](https://leetcode.com/problems/custom-interval/) 🔒
- 🟡 [2821. Delay the Resolution of Each Promise](https://leetcode.com/problems/delay-the-resolution-of-each-promise/) 🔒
- 🟢 [2822. Inversion of Object](https://leetcode.com/problems/inversion-of-object/) 🔒
- 🟡 [2823. Deep Object Filter](https://leetcode.com/problems/deep-object-filter/) 🔒

</details>

## Concurrency

*Threads, locks, semaphores.* — 9 problems

<details><summary><b>Concurrency</b> (9)</summary>

- 🟢 [1114. Print in Order](https://leetcode.com/problems/print-in-order/)
- 🟡 [1115. Print FooBar Alternately](https://leetcode.com/problems/print-foobar-alternately/)
- 🟡 [1116. Print Zero Even Odd](https://leetcode.com/problems/print-zero-even-odd/)
- 🟡 [1117. Building H2O](https://leetcode.com/problems/building-h2o/)
- 🟡 [1188. Design Bounded Blocking Queue](https://leetcode.com/problems/design-bounded-blocking-queue/) 🔒
- 🟡 [1195. Fizz Buzz Multithreaded](https://leetcode.com/problems/fizz-buzz-multithreaded/)
- 🟡 [1226. The Dining Philosophers](https://leetcode.com/problems/the-dining-philosophers/)
- 🟡 [1242. Web Crawler Multithreaded](https://leetcode.com/problems/web-crawler-multithreaded/) 🔒
- 🟢 [1279. Traffic Light Controlled Intersection](https://leetcode.com/problems/traffic-light-controlled-intersection/) 🔒

</details>

## Shell

*Bash one-liners.* — 4 problems

<details><summary><b>Shell</b> (4)</summary>

- 🟡 [192. Word Frequency](https://leetcode.com/problems/word-frequency/)
- 🟢 [193. Valid Phone Numbers](https://leetcode.com/problems/valid-phone-numbers/)
- 🟡 [194. Transpose File](https://leetcode.com/problems/transpose-file/)
- 🟢 [195. Tenth Line](https://leetcode.com/problems/tenth-line/)

</details>

## Not Tagged Yet

*Very new problems LeetCode has not tagged; placed by title where possible.* — 13 problems

<details><summary><b>General</b> (13)</summary>

- 🟡 [3253. Construct String with Minimum Cost (Easy)](https://leetcode.com/problems/construct-string-with-minimum-cost-easy/) 🔒
- 🟡 [3778. Minimum Distance Excluding One Maximum Weighted Edge](https://leetcode.com/problems/minimum-distance-excluding-one-maximum-weighted-edge/) 🔒
- 🟡 [3907. Count Smaller Elements With Opposite Parity](https://leetcode.com/problems/count-smaller-elements-with-opposite-parity/) 🔒
- 🔴 [4029. Elevator Requests IV](https://leetcode.com/problems/elevator-requests-iv/) 🔒
- 🟢 [4070. Minimum Rotations to Dial a Number I](https://leetcode.com/problems/minimum-rotations-to-dial-a-number-i/)
- 🟡 [4071. Minimum Rotations to Dial a Number II](https://leetcode.com/problems/minimum-rotations-to-dial-a-number-ii/)
- 🔴 [4073. Count Good Strings](https://leetcode.com/problems/count-good-strings/)
- 🟢 [4074. Maximum Product Pair With Target Sum](https://leetcode.com/problems/maximum-product-pair-with-target-sum/)
- 🟢 [4083. Minimum Deletions to Make Array Sharp](https://leetcode.com/problems/minimum-deletions-to-make-array-sharp/)
- 🟢 [4088. Difference Between Peaks and Valleys](https://leetcode.com/problems/difference-between-peaks-and-valleys/)
- 🟡 [4096. Simulate Bomb Explosions and Falling Boxes](https://leetcode.com/problems/simulate-bomb-explosions-and-falling-boxes/) 🔒
- 🟢 [4097. Minimum Value of Merged Integers](https://leetcode.com/problems/minimum-value-of-merged-integers/)
- 🔴 [4115. Sum of Compatible Numbers in Range II](https://leetcode.com/problems/sum-of-compatible-numbers-in-range-ii/) 🔒

</details>

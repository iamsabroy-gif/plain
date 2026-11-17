// The playground's algorithm gallery: classic algorithms written to be watched. Each opens in
// "Watch it run" next to its flowchart. tests/algorithms_test.js runs every one of them.
"use strict";
(function (root, factory) {
  if (typeof module === "object" && module.exports) module.exports = factory();
  else root.PlainAlgorithms = factory();
})(this, function () {
  return [
    {
      id: "biggest", name: "Find the biggest", picture: "\u{1F3C6}", group: "Searching", cost: "O(n)",
      about: "Look at every number once, remembering the biggest so far.",
      code: String.raw`# Find the biggest: look at every number once, remembering the biggest so far.
# watch: numbers as bars, i, biggest
set numbers to [4, 9, 2, 7, 5]
set biggest to numbers[1]
for i from 2 to length of numbers
    if numbers[i] is greater than biggest then
        set biggest to numbers[i]
    end
end
say "The biggest is", biggest
`,
    },
    {
      id: "linear-search", name: "Linear search", picture: "\u{1F50E}", group: "Searching", cost: "O(n)",
      about: "Check each item in turn until the one you want turns up.",
      code: String.raw`# Linear search: check each item in turn until the one we want turns up.
# watch: numbers as bars, i, target, found_at
set numbers to [8, 3, 12, 5, 9, 1, 7]
set target to 9
set found_at to 0
for i from 1 to length of numbers
    if numbers[i] is target then
        set found_at to i
        stop
    end
end
say "Found {target} at position {found_at}"
`,
    },
    {
      id: "binary-search", name: "Binary search", picture: "\u{1F3AF}", group: "Searching", cost: "O(log n)",
      about: "In a sorted list, look in the middle and throw away the half that can't hold it.",
      code: String.raw`# Binary search: in a sorted list, look in the middle and throw away the half that can't hold it.
# watch: numbers as bars, low, high, mid, target
set numbers to [2, 5, 8, 12, 16, 23, 38, 56, 72, 91]
set target to 23
set low to 1
set high to length of numbers
set found_at to 0
while low is at most high
    set mid to quotient(low + high, 2)
    if numbers[mid] is target then
        set found_at to mid
        stop
    otherwise if numbers[mid] is less than target then
        set low to mid + 1
    otherwise
        set high to mid - 1
    end
end
say "Found {target} at position {found_at}"
`,
    },
    {
      id: "bubble-sort", name: "Bubble sort", picture: "\u{1FAE7}", group: "Sorting", cost: "O(n²)",
      about: "Swap neighbours that are the wrong way round; the biggest bubbles to the end.",
      code: String.raw`# Bubble sort: swap neighbours that are the wrong way round; the biggest bubbles to the end.
# watch: numbers as bars, i, j
set numbers to [5, 1, 4, 2, 8, 3]
set n to length of numbers
for i from 1 to n - 1
    for j from 1 to n - i
        if numbers[j] is greater than numbers[j + 1] then
            set temp to numbers[j]
            set numbers[j] to numbers[j + 1]
            set numbers[j + 1] to temp
        end
    end
end
say numbers
`,
    },
    {
      id: "selection-sort", name: "Selection sort", picture: "\u{1F446}", group: "Sorting", cost: "O(n²)",
      about: "Find the smallest of what is left and put it next in line.",
      code: String.raw`# Selection sort: find the smallest of what is left and put it next in line.
# watch: numbers as bars, i, j, smallest
set numbers to [29, 10, 14, 37, 13]
set n to length of numbers
for i from 1 to n - 1
    set smallest to i
    for j from i + 1 to n
        if numbers[j] is less than numbers[smallest] then
            set smallest to j
        end
    end
    if smallest is not i then
        set temp to numbers[i]
        set numbers[i] to numbers[smallest]
        set numbers[smallest] to temp
    end
end
say numbers
`,
    },
    {
      id: "insertion-sort", name: "Insertion sort", picture: "\u{1F0CF}", group: "Sorting", cost: "O(n²)",
      about: "Like sorting cards in your hand: slide each one left into its place.",
      code: String.raw`# Insertion sort: like sorting cards in your hand, slide each one left into its place.
# watch: numbers as bars, i, j, key
set numbers to [7, 3, 5, 1, 6, 2]
for i from 2 to length of numbers
    set key to numbers[i]
    set j to i - 1
    while j is at least 1 and numbers[j] is greater than key
        set numbers[j + 1] to numbers[j]
        set j to j - 1
    end
    set numbers[j + 1] to key
end
say numbers
`,
    },
    {
      id: "merge-sort", name: "Merge sort", picture: "✂️", group: "Sorting", cost: "O(n log n)",
      about: "Split the list in half, sort each half the same way, then merge the sorted halves.",
      code: String.raw`# Merge sort: split the list in half, sort each half the same way, then merge the two sorted halves.
define merge_sort with items
    if length of items is at most 1 then
        give back items
    end
    set middle to quotient(length of items, 2)
    set left_half to merge_sort(slice(items, 1, middle))
    set right_half to merge_sort(slice(items, middle + 1, length of items))
    set merged to []
    set a to 1
    set b to 1
    while a is at most length of left_half and b is at most length of right_half
        if left_half[a] is at most right_half[b] then
            add left_half[a] to merged
            increase a by 1
        otherwise
            add right_half[b] to merged
            increase b by 1
        end
    end
    while a is at most length of left_half
        add left_half[a] to merged
        increase a by 1
    end
    while b is at most length of right_half
        add right_half[b] to merged
        increase b by 1
    end
    give back merged
end

say merge_sort([38, 27, 43, 3, 9, 82, 10])
`,
    },
    {
      id: "quick-sort", name: "Quick sort", picture: "⚡", group: "Sorting", cost: "O(n log n) usually",
      about: "Pick a pivot, put smaller numbers before it and bigger after, then sort each side.",
      code: String.raw`# Quick sort: pick a pivot, put the smaller numbers before it and the bigger ones after it,
# then sort each side the same way.
# watch: numbers as bars, low, high, pivot, i, j
set numbers to [10, 80, 30, 90, 40, 50, 70]

define partition with low, high
    set pivot to numbers[high]
    set i to low - 1
    for j from low to high - 1
        if numbers[j] is less than pivot then
            increase i by 1
            set temp to numbers[i]
            set numbers[i] to numbers[j]
            set numbers[j] to temp
        end
    end
    set temp to numbers[i + 1]
    set numbers[i + 1] to numbers[high]
    set numbers[high] to temp
    give back i + 1
end

define quick_sort with low, high
    if low is less than high then
        set place to partition(low, high)
        quick_sort(low, place - 1)
        quick_sort(place + 1, high)
    end
end

quick_sort(1, length of numbers)
say numbers
`,
    },
    {
      id: "fibonacci", name: "Fibonacci by recursion", picture: "\u{1F300}", group: "Recursion", cost: "O(2ⁿ)",
      about: "An action that calls itself twice: watch the tree of calls, and how often calls repeat.",
      code: String.raw`# Fibonacci by calling itself: watch the tree of calls grow, and see the same call made again and again.
define fib with n
    if n is less than 2 then
        give back n
    end
    give back fib(n - 1) + fib(n - 2)
end

say "fib(5) is", fib(5)
`,
    },
    {
      id: "hanoi", name: "Towers of Hanoi", picture: "\u{1F5FC}", group: "Recursion", cost: "O(2ⁿ)",
      about: "Move n discs by moving n - 1 out of the way, the biggest across, then n - 1 back on top.",
      code: String.raw`# Towers of Hanoi: to move n discs, move n - 1 out of the way, move the biggest,
# then move the n - 1 back on top of it.
define hanoi with n, from_peg, to_peg, spare
    if n is 0 then
        give back nothing
    end
    hanoi(n - 1, from_peg, spare, to_peg)
    say "Move disc {n} from {from_peg} to {to_peg}"
    hanoi(n - 1, spare, to_peg, from_peg)
end

hanoi(3, "A", "C", "B")
`,
    },
    {
      id: "bfs", name: "Breadth-first search", picture: "\u{1F310}", group: "Graphs", cost: "O(places + roads)",
      about: "Visit a graph level by level, with a queue of places to visit next.",
      code: String.raw`# Breadth-first search: visit a graph level by level, using a queue of places to visit next.
# watch: roads as graph, queue, seen, order
set roads to {Home: ["Park", "School"], Park: ["Shop"], School: ["Shop", "Library"], Shop: ["Library"], Library: []}
set queue to ["Home"]
set seen to {Home: true}
set order to []
while length of queue is greater than 0
    set place to pop_at(queue, 1)
    add place to order
    for each next_place in roads[place]
        if not has_key(seen, next_place) then
            set seen[next_place] to true
            add next_place to queue
        end
    end
end
say "Visited in order:", order
`,
    },
    {
      id: "dfs", name: "Depth-first search", picture: "\u{1F9ED}", group: "Graphs", cost: "O(places + roads)",
      about: "Go as deep as you can down one road before coming back to try the next.",
      code: String.raw`# Depth-first search: go as deep as you can down one road before coming back to try the next.
# watch: roads as graph, seen, order
set roads to {Home: ["Park", "School"], Park: ["Shop"], School: ["Shop", "Library"], Shop: ["Library"], Library: []}
set seen to {}
set order to []

define visit with place
    set seen[place] to true
    add place to order
    for each next_place in roads[place]
        if not has_key(seen, next_place) then
            visit(next_place)
        end
    end
end

visit("Home")
say "Visited in order:", order
`,
    },
    {
      id: "brackets", name: "Matching brackets", picture: "\u{1F9F1}", group: "Stacks", cost: "O(n)",
      about: "Push each opening bracket on a stack; each closing one must match the top.",
      code: String.raw`# Matching brackets with a stack: push each opening bracket,
# and each closing one must match the bracket on top.
# watch: stack as boxes, c, ok
set brackets to "([]{()})"
set partner to {")": "(", "]": "[", "}": "{"}
set stack to []
set ok to true
for each c in brackets
    if "([{" contains c then
        add c to stack
    otherwise if length of stack is 0 or pop(stack) is not partner[c] then
        set ok to false
        stop
    end
end
if length of stack is not 0 then
    set ok to false
end
say brackets, "balanced:", ok
`,
    },
    {
      id: "gcd", name: "Euclid's algorithm", picture: "\u{1F522}", group: "Numbers", cost: "O(log n)",
      about: "The greatest common divisor of two numbers, by taking remainders: 2,300 years old.",
      code: String.raw`# Euclid's algorithm: the greatest common divisor of two numbers, by taking remainders.
# watch: a, b, r
set a to 48
set b to 18
while b is not 0
    set r to a % b
    set a to b
    set b to r
end
say "The greatest common divisor is", a
`,
    },
  ];
});

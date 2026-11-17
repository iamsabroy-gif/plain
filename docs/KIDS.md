# Plain for kids

Hello! This page will teach you to make a computer do what you tell it.

You will write **programs**. A program is a list of instructions, one on each line, like
a recipe. The computer reads it from the top to the bottom and does each line.

Plain is a language made of words you already know. If you can read this page, you can
write Plain.

> **Grown-up helper:** the quickest way to start is the Plain playground, a web page where
> you type and press Run, with nothing to install. If it is not set up yet, install Plain
> from the [main page](../README.md#install) and type your programs into a file.

## Where do I type?

Open the playground. You will see a big box for your program on the left and a box called
**What it says** on the right. Type a program, then press the green **Run** button.

You can also press **Examples** to pick a program that is already written, and change it
to see what happens. Changing things is the best way to learn!

The box helps you as you type:

* It **colours your words**: the words that tell the computer what to do are blue, the words
  you make up for your own actions stand out, and what is inside quote marks is green.
* When you press Enter after a line like `if` or `repeat`, it **writes the `end` for you** and
  puts you in the right place to type the next line.
* If Plain can see a mistake, it draws a **red wavy line** under that line and tells you what
  to fix, underneath the box. (An orange line just means a block is not finished yet.)

Press **Flowchart** to see your program as a picture: boxes for each step, diamonds for each
question, and arrows that go round for loops. Press **Watch it run** and the box the computer is
doing lights up, one step at a time. And **Algorithms** has famous programs, like sorting
numbers and finding your way round a map, ready to watch.

## 1. Make the computer talk

`say` makes the computer say something. Put what it should say inside quote marks.

```plain
say "Hello, world!"
say "My name is Asha"
```

```output
Hello, world!
My name is Asha
```

Each `say` is one line, and the computer says them in order, top to bottom.

**Try it:** change the words. Make it say your name. Make it say three things!

## 2. Boxes with names

A computer can remember things. Think of a **box with a name** stuck on the front. You
can put something inside, and later you can look inside by using the name.

`set` puts something in a box.

```plain
set pet to "puppy"
say "I have a", pet
set pet to "kitten"
say "Now I have a", pet
```

```output
I have a puppy
Now I have a kitten
```

See how the box called `pet` first held `"puppy"`, then we put `"kitten"` in it? The old
thing is gone and the new one is inside.

Notice that `say` can say lots of things in one go. Put commas between them.

**Try it:** make a box called `favourite_colour` and say it. Use an underscore `_`
where you want a space in a name, because a name can't have spaces.

## 3. Sums

Computers are very good at maths. Use `+` to add, `-` to take away, `*` to multiply
(times) and `/` to share out (divide).

```plain
set apples to 12
set friends to 3
say "I have", apples, "apples"
say "Each friend gets", apples / friends
say "If I find 5 more I will have", apples + 5
say "Twice as many is", apples * 2
```

```output
I have 12 apples
Each friend gets 4
If I find 5 more I will have 17
Twice as many is 24
```

You can change what is in a box using maths too:

```plain
set stickers to 10
increase stickers by 5
say stickers
decrease stickers by 3
say stickers
```

```output
15
12
```

**Try it:** you have 20 sweets and 4 friends. How many does each friend get?

## 4. Asking questions

A program can ask you something and remember your answer in a box.

```input
Asha
```

```plain
ask "What is your name?" into name
say "Hello,", name
say "Nice to meet you!"
```

```output
What is your name? Hello, Asha
Nice to meet you!
```

In the playground, open **Typed answers for ask** under the program box and type your
answers there, one on each line, before you press Run. When you use Plain on a computer,
it waits for you to type.

## 5. Doing things again and again

Computers never get bored. Use `repeat` to do something many times. Everything between
`repeat` and `end` is done each time round.

```plain
repeat 3 times
    say "Hip hip hooray!"
end
```

```output
Hip hip hooray!
Hip hip hooray!
Hip hip hooray!
```

Notice that the lines inside are pushed in a little (4 spaces). It helps you see what is
inside. The playground does it for you when you press Enter.

You can also **count**. Here `i` is a box that holds the number, and it changes each time
round.

```plain
for i from 1 to 5
    say i, "times 2 is", i * 2
end
```

```output
1 times 2 is 2
2 times 2 is 4
3 times 2 is 6
4 times 2 is 8
5 times 2 is 10
```

And you can count down to a launch with `while`, which keeps going as long as something
is true:

```plain
set count to 3
while count is greater than 0
    say count
    decrease count by 1
end
say "Blast off!"
```

```output
3
2
1
Blast off!
```

**Try it:** make the computer print the 7 times table from 1 to 10.

## 6. Making choices

A program can look at things and decide what to do. That is what `if` is for.

```plain
set age to 9
if age is less than 5 then
    say "You are little!"
otherwise if age is less than 13 then
    say "You are a kid!"
otherwise
    say "You are grown up!"
end
```

```output
You are a kid!
```

The computer tries the first question. If the answer is yes, it does the lines under it.
If not, it tries the next one. `otherwise` on its own catches everything else.

Here are the ways to compare things:

| You write | It means |
|---|---|
| `a is b` | a is the same as b |
| `a is not b` | a is different from b |
| `a is less than b` | a is smaller than b |
| `a is greater than b` | a is bigger than b |
| `a is at most b` | a is smaller than b, or the same |
| `a is at least b` | a is bigger than b, or the same |

You can join questions with `and` and `or`:

```plain
set weather to "sunny"
set day to "Saturday"
if weather is "sunny" and day is "Saturday" then
    say "Let's go to the park!"
end
```

```output
Let's go to the park!
```

**Try it:** change `weather` to `"rainy"`. What happens? Why?

## 7. Lists

Sometimes you want one box that holds lots of things, in order, like a shopping list.
That is a **list**. Write it with square brackets, with commas between the things.

```plain
set fruits to ["mango", "banana", "lychee"]
add "guava" to fruits
say fruits
say "The first fruit is", fruits[1]
say "I have", length of fruits, "fruits"
```

```output
["mango", "banana", "lychee", "guava"]
The first fruit is mango
I have 4 fruits
```

Careful: the first thing in a list is number **1**, the second is number 2, and so on.

`for each` goes through a list and does something with every thing in it:

```plain
set fruits to ["mango", "banana", "lychee"]
for each fruit in fruits
    say "I like", fruit
end
```

```output
I like mango
I like banana
I like lychee
```

**Try it:** make a list of your three best friends. Make the computer say hello to each
one.

## 8. Make your own magic words

Do you do the same thing again and again? You can give it a name, and then use the name
whenever you want. In Plain this is `define`. Think of it as teaching the computer a new
magic word.

```plain
define cheer with name
    say "Hooray for", name + "!"
end

cheer("Asha")
cheer("Ravi")
```

```output
Hooray for Asha!
Hooray for Ravi!
```

`with name` says "this magic word needs a name to work with". When we write
`cheer("Asha")`, the box `name` holds `"Asha"` while the magic word runs.

A magic word can also **give back** an answer:

```plain
define double with amount
    give back amount * 2
end

say double(21)
say double(double(5))
```

```output
42
20
```

**Try it:** teach the computer a magic word called `triple` that gives back 3 times a
number.

## 9. When something goes wrong

Every programmer makes mistakes, even grown-up ones who have done it for 40 years.
Mistakes are called **bugs**, and finding them is called **debugging**. It is a bit like
being a detective.

Plain tries to help. It tells you **what** went wrong, **which line**, and what to try.

Here is a program with a spelling mistake: `totl` instead of `total`.

```plain-fails
set total to 5
say totl
```

```output
Oops! Line 2: I don't know anything called 'totl'. Did you mean 'total'?
     2 | say totl
```

Plain even guessed what you meant! Read the message slowly, look at the line it shows,
and fix it.

Here is another one. Lists count from 1, so this list has no item 5:

```plain-fails
set colours to ["red", "blue"]
say colours[5]
```

```output
Oops! Line 2: The list has 2 items, so there is no item 5. Use a number from 1 to 2, or check 'length of' first.
     2 | say colours[5]
```

**If your program is stuck**, there is a **Stop** button. If it is not doing what you
expect, press **Watch it run** and step through it one line at a time. You will see the
boxes change after each line, and you can find the moment it goes wrong.

## 10. Words you can't use as box names

A few words already mean something to Plain, so you can't use them as the name of a box.
`item` and `times` are two of them. If you try, Plain explains and suggests another name:

```plain-fails
for each item in [1, 2]
    say item
end
```

```output
Oops! Line 1: 'item' is a reserved word: Plain uses it in 'item 2 of list', so it can't also be a name. Pick another name, such as 'entry' or 'thing' (or 'my_item').
     1 | for each item in [1, 2]
```

So use `thing` instead:

```plain
for each thing in [1, 2]
    say thing
end
```

```output
1
2
```

## 11. Watch your program think

Press the **Watch it run** button, and the computer shows your program one line at a
time. The line that just ran is lit up. Below it you can see all your boxes.

Try it on this program that puts numbers in order. The numbers are drawn as bars, and the
bars that the computer is comparing glow yellow. When two bars swap places, they turn red.

```plain
define bubble_sort with numbers
    set n to length of numbers
    for pass from 1 to n - 1
        for j from 1 to n - pass
            if numbers[j] is greater than numbers[j + 1] then
                set tmp to numbers[j]
                set numbers[j] to numbers[j + 1]
                set numbers[j + 1] to tmp
            end
        end
    end
    give back numbers
end

say bubble_sort([5, 2, 9, 1, 7, 3])
```

```output
[1, 2, 3, 5, 7, 9]
```

You do not have to understand all of this yet. Just press the play button and watch the
bars dance.

## Challenges

Try these on your own. The answers are at the bottom, but try first!

1. Make the computer say your name 5 times.
2. Make a list of your 4 favourite foods and say each one.
3. Count from 10 down to 1, then say "Go!".
4. Ask for a number and say what it is times 10.
5. Teach the computer a magic word called `greet` that says "Hello, " and then a name.
6. Make the computer say whether a number is big (more than 100) or small.

### Answers

```plain
repeat 5 times
    say "Asha"
end
```

```output
Asha
Asha
Asha
Asha
Asha
```

```plain
set foods to ["pizza", "noodles", "mango", "ice cream"]
for each food in foods
    say food
end
```

```output
pizza
noodles
mango
ice cream
```

```plain
for i from 10 to 1 by -1
    say i
end
say "Go!"
```

```output
10
9
8
7
6
5
4
3
2
1
Go!
```

```input
7
```

```plain
ask "Pick a number:" into number_in
say number_in, "times 10 is", number_in * 10
```

```output
Pick a number: 7 times 10 is 70
```

```plain
define greet with name
    say "Hello,", name
end

greet("Asha")
```

```output
Hello, Asha
```

```plain
set number_in to 250
if number_in is greater than 100 then
    say "big"
otherwise
    say "small"
end
```

```output
big
```

## Words to remember

| Word | What it means |
|---|---|
| **program** | a list of instructions for the computer |
| **box** (a *variable*) | a name with something inside it |
| **list** | one box that holds many things, in order |
| **loop** | doing something again and again (`repeat`, `for`, `while`) |
| **magic word** (a *function*) | something you teach the computer and then use by name |
| **bug** | a mistake in a program |
| **debugging** | finding and fixing bugs |

## What next?

* Press **Examples** in the playground and change each one.
* Make a game: ask for a name, say a story with it, add a loop.
* Ask a grown-up to show you the [next steps for beginners](CORE.md): there are more
  words to learn, and problems to solve with `plain practice`.

Keep going. Every programmer started exactly where you are now.

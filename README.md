# Assignment 2 : Dance of the Strings

## Learning goals
Strings, pointers, dynamic memory management

---
**Caution:** *<string.h>* may **not** be used to solve this task!

---

## Task - Overview
The program receives several records via `stdin`. If a `\n` is read, the program stops reading records.

A selection menu is now displayed:
```
Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Concatenate two sentences
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice:
```
---
The functions of the options are explained using the following input:
```
That's an unnecessary sentence. C is so heavy.
```
---

If the\*the user\* types in `t`:
```
Text Statistics:
2 sentences, 37 characters
35 letters (3 uppercase, 32 lowercase)
```

If the\*the user\*types in `s`:
```
First record number: 1 [Note: 1 was entered]
Second Set Number: 2 [Note: 2 was entered]
```
Now set 1 is swapped with set 2 (result: `C is so hard. This is an unnecessary set.`).


If the\*the user\*types in `c`:
```
First record number: 1 [Note: 1 was entered]
Second Set Number: 2 [Note: 2 was entered]
```
Now sentence 1 is connected to sentence 2 with an `and` (result: `This is an unnecessary sentence and C is so difficult.`).

If the\*the user\* types in `p`:
```
  No. | Sentence
-----+----------------------------------------
    1 | That's an unnecessary sentence.
    2 | C is so heavy.
```

If the\*the user\*types in `o`:
```
Text:
That's an unnecessary sentence. C is so heavy.
```

If the\*the user\*types in `e`:
```
Program end!
```
Then the program is terminated with the return value `0`.

The selection menu is then displayed again for all operations (except for `e` - end of program).

---

## Task - Detailed

**Note:** Each output line is terminated with a `\n`. The exception is input by users, because *only with the [first input](#read-in-the-sentences)* (at `Please enter text:`) a `\n` is output.

### Read in the records

The program starts with the output of:
```
Please enter text:
```

After that, the\*the user\*can type in an **any** number of sentences. A sentence ends with a period (`.`), question mark (`?`), or exclamation mark (`!`). If a `\n` (Enter pressed) is read, the program stops reading sentences.

---
**Tip:** It doesn't make sense to always call `realloc()` for every single character read. For example, always reserve space for 100 characters, if this space is no longer sufficient, again for 100 characters, and so on (hint: `fgets()`).
Then save the sentences internally as individual strings (without spaces before or after the text)! This means you use one string per block and thus one `malloc()`.

---

**Error Messages:**
  - If no character is found in the input that completes a sentence (`.`, `?`, `!`), the following output is produced
       ```
       No sentence found!
       ```
       and the program exits with the return value `1`.


  - If there is no period (`.`), question mark (`?`) or exclamation mark (`!`) at the end of the last sentence, then
       ```
       The text ends without punctuation marks!
       ```
       is output and the program exits with the return value `2`.


  - If there is not enough memory, the error message reads
       ```
       Insufficient memory available!
       ```
       and the program exits with the return value `3`.

---

### Selection menu

After successfully entering the sentences, an empty line is output and then a selection menu is displayed:
```
Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Concatenate two sentences
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: <Enter>
```

die\*the user\*in now types in to select an option. If the input is invalid (not equal to `t`, `s`, `c`, `p`, `o` or `e`), it returns `Your choice: ` (*Note:* `getchar()` ). If a space is entered before the letter, the entry is invalid.

---

### Output text without line number

If the selection `o` was made by the\*user\*in, the saved text is output. Exactly one space is printed after **each** sentence. Note that the text can change while the program is running (e.g. with the option `s` - *swap two sentences*)!

Example input:
```
That's an unnecessary sentence. C is so heavy.
```

Output by option `o`:
```
Text:
That's an unnecessary sentence. C is so heavy.
```

More example output after swapping sentence 1 and sentence 2 (option `s`, then option `o`):
```
Text:
C is so heavy. That's an unnecessary sentence.
```

---

### Output text with line number

If the selection `p` was made by the\*the user\*in, the saved text is output with the sentence number (the first sentence has the number 1). Note that the text can change while the program is running (e.g. with the option `s` - *swap two sentences*)!

Example input:
```
That's an unnecessary sentence. C is so heavy.
```

Output by option `p`:
```
  No. | Sentence
-----+----------------------------------------
    1 | That's an unnecessary sentence.
    2 | C is so heavy.
```

More sample output after swapping set 1 and set 2 (option `s`, then option `p`):
```
  No. | Sentence
-----+----------------------------------------
    1 | C is so heavy.
    2 | That's an unnecessary sentence.

```
Please also note that a two-digit number is not indented. So you could output the block number with `%4d`.

---

### Exit program

If the choice `e` was made by the\*user\*in, then
```
Program end!
```
is output and the program exits with the return value `0`.

---

### Text statistics

If the selection `t` was made by the\*user\*in, statistics about the records are displayed. The number of sentences, the number of characters (without spaces), as well as the number of upper and lower case letters are output. The output looks like this (replace `x` with the corresponding number):
```
Text Statistics:
x sentences, x characters
x letters (x uppercase, x lowercase)
```

---
**DANGER!**

If the option `c` ("concatenate two sentences") was previously selected, the number of sentences and also the number of characters has changed compared to the entered sentences!

---

### Swap two sentences

If the selection `s` was made by the\*user\*in, the number of records is checked first. If the text consists of only one sentence, `Only one sentence left!` will appear
output and then the selection menu is displayed again. Otherwise, the block numbers of the blocks that are to be swapped are queried first:

```
First record number: <Input>
Second record number: <Input>
```

If an invalid number or no number is entered, `First block number: ` or `Second block number: ` is output again.
The numbers of the first and second sentence must be different. Therefore, when asking for the second block number, entering the first block number again is invalid! Example:
```
First sentence number: 2
Second set number: 2
Second set number: 1
```

After entering the block numbers, the blocks are swapped in the internal data structure.

---

### Concatenate two sentences

If the selection `c` was made by the\*the user\*in, the block numbers of the blocks that are to be joined are queried first:

```
First record number: <Input>
Second record number: <Input>
```

The input should be exactly the same as for the `s` option. Also remember to check if there are at least 2 sets left!

After entering the block numbers, the blocks are combined in the internal data structure. The punctuation mark that ends the first sentence is replaced by ` and `. (Sentence structure: sentence with the number `number of the first sentence` (without final punctuation mark) + ` and ` + sentence with the number `number of the second sentence`.) Remember that there can be several sentences between the two sentences, e.g. sentence 6 connect to set 2.

Upper and lower case (beginning of sentence) is not to be taken into account. In the [example output](#example output) you can see further examples in which sentences are concatenated. These also clarify the concatenation of sentences that are not consecutive.

---


## Example output
```
Please enter text:
This is a text. Here comes the second sentence. I am the third sentence. A fourth sentence is also possible!

Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Chain two sets together
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: u
Your choice: t
Your choice: t
Your choice: t
Text Statistics:
4 sentences, 84 characters
80 letters (8 uppercase, 72 lowercase)

Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Chain two sets together
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: o
Text:
This is a text. Here comes the second sentence. I am the third sentence. A fourth sentence is also possible!

Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Chain two sets together
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: p
  No. | Sentence
-----+----------------------------------------
    1 | This is a text.
    2 | Here comes the second sentence.
    3 | I am the third sentence.
    4 | A fourth sentence is also possible!

Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Chain two sets together
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: s
First set number: 100
First sentence number: 2
Second set number: 4

Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Chain two sets together
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: o
Text:
This is a text. A fourth sentence is also possible! I am the third sentence. Here comes the second sentence.

Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Chain two sets together
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: p
  No. | Sentence
-----+----------------------------------------
    1 | This is a text.
    2 | A fourth sentence is also possible!
    3 | I am the third sentence.
    4 | Here comes the second sentence.

Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Chain two sets together
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: t
Text Statistics:
4 sentences, 84 characters
80 letters (8 uppercase, 72 lowercase)

Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Chain two sets together
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: c
First sentence number: 4
Second set number: 1

Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Chain two sets together
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: p
  No. | Sentence
-----+----------------------------------------
    1 | A fourth sentence is also possible!
    2 | I am the third sentence.
    3 | Here comes the second sentence and This is a text.

Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Chain two sets together
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: o
Text:
A fourth sentence is also possible! I am the third sentence. Here comes the second sentence and This is a text.

Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Chain two sets together
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: t
Text Statistics:
3 sentences, 86 characters
83 letters (8 uppercase, 75 lowercase)

Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Chain two sets together
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: c
First sentence number: 3
Second set number: 2

Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Chain two sets together
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: p
  No. | Sentence
-----+----------------------------------------
    1 | A fourth sentence is also possible!
    2 | Here comes the second sentence and This is a text and I am the third sentence.

Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Chain two sets together
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: c
First sentence number: 2
Second set number: 1

Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Chain two sets together
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: p
  No. | Sentence
-----+----------------------------------------
    1 | Here comes the second sentence and This is a text and I am the third sentence and A fourth sentence is also possible!

Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Chain two sets together
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: o
Text:
Here comes the second sentence and This is a text and I am the third sentence and A fourth sentence is also possible!

Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Chain two sets together
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: t
Text Statistics:
1 sentences, 90 characters
89 letters (8 uppercase, 81 lowercase)

Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Chain two sets together
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: s
Only one set left!

Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Chain two sets together
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: c
Only one set left!

Choose an option:
   t: text statistics
   s: Swap two sentences
   c: Chain two sets together
   p: Output text with line number
   o: Output text without line number
   e: Exit program

Your choice: e
Program end!

```

---
**DANGER!**

Please follow the output instructions *precisely* as even small errors (e.g. a space
too little or too much) fail! You can also use the test system provided, which provides valuable information about errors in your program.

---


## specification
* All output is to stdout
     * No output to stderr
* string.h must **not** be used!
* Submission by *at the latest*: 11.12.2021 23:59 (valid time in Austria)
* File to submit: a2.c

## Evaluation
The assignment is evaluated [as described in the TeachCenter](https://tc.tugraz.at/main/mod/page/view.php?id=55761). Familiarize yourself with the [assessment scheme](https://tc.tugraz.at/main/mod/page/view.php?id=55602) for the exercises, especially with the rules on plagiarism!

# Advent of Code 2019 #

My solutions to the [Advent of Code 2019](https://adventofcode.com/2019).

Please note that this code has been written on a Linux system, using Clang
version 9 as the compiler.

## Common ##

The `common/` directory contains some useful code shared amongst the
implementations for the Advent of Code days to reduce boilerplate code
writing.

### AoC Exceptions ###

The file `common/aoc_except.hpp` contains a few exceptions specifically
for AoC:

* `FileNotFound`: Pretty much what the name says. Uses a `runtime_error`
  with a custom string message based on the path handed to its initializer.
* `AoCError`: Just a child inheriting from runtime error to distinguish
  my own exceptions in try-catch blocks.

### The Tokenizer ###

The tokenizer, which can be found in `common/Tokenizer.hpp`, is a tool to
read in a ASCII text file or String, and tokenize it by a specific delimiter
and store the tokens as a specific type.

To that end, the Tokenizer's `TType` template argument sets the type of token
to store. Tokens are taken from the String or filepath provided in the
constructor. It cannot be changed after initialization. 

The string is tokenized when the `tokenize(const char& delim)` is called,
splitting it at each occurence of `delim`. The tokens are then coverted
to `TType` and stored.
Calling `tokenize()` with another delimiter will clear the current tokens
and retokenize the input according to the new delimiter.

The conversion to `TType` is implmented currently for `TType`s which are
convertible to `std::string` as well as those `TType` which can be
converted from string via the `std::from_chars` function.

Just implementing a single constructor accepting `const std::string&`
should suffice to allow usage of user defined classes without any
adaptations to the `Tokenizer` class itself.

The converted tokens are made available via standard `begin/end`
members, which also makes `Tokenizer` amendable to use in ranged
for loops.
In addition, the `tokens` function can be used to get a copy of 
the entire container of tokens, in case the user wishes to mutate
them.

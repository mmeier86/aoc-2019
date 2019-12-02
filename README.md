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


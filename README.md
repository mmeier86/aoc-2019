# Advent of Code 2019 #

My solutions to the [Advent of Code 2019](https://adventofcode.com/2019).

Please note that this code has been written on a Linux system, using Clang
version 9 as the compiler.

## Running ##

Each `day_<DD>/` dir is a standalone project and contains the solutions for
one Advent of Code 2019 day.

The build can be launched with (Day 1 as an example):
```bash
$ mkdir day_01/build && cd day_01/build
$ cmake -DUNITTESTS_ENABLED=ON -DCMAKE_BUILD_TYPE=Debug ../
$ make -j $(nproc)
```

The executable `day_01` executes the actual puzzles. It's
called like this:

```bash
$ day_01 1|2 <INPUT_FILE>
```

It will read the `<INPUT_FILE>` and run either part 1 or part 2 of the puzzle,
depending on which part has been choosen as the first parameter.

Furhtermore, an executable `day_01_ut` is produced. It runs the UTs for the day,
written with the [Catch2](https://github.com/catchorg/Catch2) UT framework.

A recompilation and rerun of the UTs can also be started by running `make check`.
The additional target `check_valg` will also rebuild the UT as necessary,
but will run it under Valgrind.

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

## Templating ##

The `template.sh` script provides a small scaffolding mechanism to provide
easy generation of new project skeletons for AoC Day puzzles.

The approach taken here is that each AoC 2019 day is its own independent
project. The script uses [Advent of Code 2019](https://github.com/tests-always-included/mo)
to realize the templates in `template/`.

### Invocation ###

```bash
~$ template.sh <TARGET_DIR> <DAY> <NAME> 
```

It is important to note that the script will exit if the `<TARGET_DIR>` already exists.
Furthermore, `<DAY>` has to have the form `DD`, e.g. `01` or `22`. Finally, `<NAME>` must
be a valid filename in your OS.

When executed, `template.sh` does the following:

- Create `<TARGET_DIR>`
- Template the files in `./template` with the values given in `<DAY>` and `<NAME>`
- Create `<TARGET_DIR>/build`
- Run `cmake -S <TARGET_DIR> -B <TARGET_DIR>/build -DUNITTESTS_ENABLED=ON -DCMAKE_BUILD_TYPE=Debug`
- Run `make -j $(nproc)` on the newly created build dir
- Create a symlink `<TARGET_DIR>/build/compile_commands.json` -> `<TARGET_DIR>/compile_commands.json`
  for use by C++ tooling

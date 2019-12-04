/**
 * @file aoc_main.hpp
 * @brief Main function for AoC 2019 Day implementations
 */

#pragma once

#include "aoc_except.hpp"
#include "AocDay.hpp"
#include "Tokenizer.hpp"

#include <filesystem>
#include <string>
#include <string_view>

const char* const usage = "Usage: progname 1|2 INPUT_FILE\n";

namespace AoC::common{
  namespace fs = std::filesystem;

  template<class DayClass>
  std::string aoc_main(int argc, char** argv){
    if(argc < 3){
      throw AoCError(std::string("Too few arguments.\n")+usage);
    }
    else if(argc > 3){
      throw AoCError(std::string("Too many arguments.\n")+usage);
    }

    std::string part(argv[1]);
    fs::path input(argv[2]);
    typename DayClass::TokType tok(input);
    DayClass day = DayClass(tok);
    if(part == "1"){
      return day.part1();
    }
    else if(part == "2"){
      return day.part2();
    }
    else{
      throw AoCError(std::string("Invalid Day part: ")+part);
    }
  }

}


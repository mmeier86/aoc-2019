/**
 * @file ut_helpers.hpp
 * @brief A few helpers for AoC UTs
 */

#pragma once

#include "AocDay.hpp"

#include <filesystem>
#include <fstream>

namespace AoC::common{

namespace fs = std::filesystem;

/**
  * @brief Little helper to quickly create tmp files for
  *        Tokenizer testing.
  *
  * @param input The string to write into the temporary file
  * @returns The path to the temporary file with input as it's
  *          contents.
  */

class Tempfile{
public:
  Tempfile(const std::string& content, const std::string& fname){
    filepath /= fs::temp_directory_path()/fname;
    std::ofstream os(filepath);
    os << content;
    os.close();
  }
  ~Tempfile(){
    fs::remove(filepath);
  }
  const fs::path& path() const{
    return this->filepath;
  }
private:
  fs::path filepath;
};

template<typename TType,std::string Part1Mock(), std::string Part2Mock()>
class DayClassMock: public AoCDay<TType>{
public:
  using AoCDay<TType>::AoCDay;

  virtual std::string part1() override{
    return Part1Mock();
  }

  virtual std::string part2() override{
    return Part2Mock();
  }
};


}


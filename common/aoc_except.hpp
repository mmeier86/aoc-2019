/**
 * @file aoc_except.hpp
 * @brief Exceptions for the Advent of Code
 */

#pragma once

#include <filesystem>
#include <stdexcept>
#include <string>

namespace AoC::common{

namespace fs = std::filesystem;

  class AoCError: std::runtime_error{
  public:
    explicit AoCError(const std::string& msg):
      runtime_error(msg){}
  };

class FileNotFound: AoCError{
public:
  explicit FileNotFound(const fs::path& failedFile):
    AoCError(std::string("File not found: ").append(failedFile)){}
};

}

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

class FileNotFound: std::runtime_error{
public:
  explicit FileNotFound(const fs::path& failedFile):
    runtime_error(std::string("File not found: ").append(failedFile)){}
};

class AoCError: std::runtime_error{
public:
  explicit AoCError(const std::string& msg):
    runtime_error(msg){}
};

}

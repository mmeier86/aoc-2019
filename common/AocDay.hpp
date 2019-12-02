/**
 * @file AoCDay.hpp
 * @brief Base class for AoC Day class implementations.
 */

#pragma once

#include "Tokenizer.hpp"
#include <string>

namespace AoC::common{

template<typename TType>
class AoCDay{
public:
  using TokType = Tokenizer<TType>;
  AoCDay(const TokType& tok)
    : tok(tok){}

  virtual std::string part1() = 0;
  virtual std::string part2() = 0;

private:
  TokType tok;
};

}

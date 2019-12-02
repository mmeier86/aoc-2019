/**
 * @file Tokenizer.hpp
 * @brief A Tokenizer for Advent of Code input files
 */

#pragma once

#include "aoc_except.hpp"

#include <charconv>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace AoC::common {

namespace fs = std::filesystem;

template <typename TType>
class Tokenizer{
public:
  explicit Tokenizer(const char *input){
    st.str(input);
  }

  explicit Tokenizer(const fs::path& path){
    if(!fs::exists(path)){
      throw FileNotFound(path);
    }
    else{
      std::ifstream in(path,std::ios::in | std::ios::binary);
      if(in){
        st << in.rdbuf();
        in.close();
      }
      else{
        throw std::runtime_error(std::string("IO error opening file ")+path.string());
      }
    }
  }

  explicit Tokenizer(const std::string &input){
    st.str(input);
  }

  Tokenizer(const Tokenizer& other)
      :vec(other.vec)
      ,delim(other.delim){
    st.str(other.st.str());
  }

  Tokenizer& operator=(const Tokenizer& other){
    st.str(other.st.str());
    delim = other.delim;
    vec = other.vec;
  }

  auto size() const{
    return this->vec.size();
  }

  auto begin(){
    return this->vec.begin();
  }

  auto end(){
    return this->vec.end();
  }

  void tokenize(const char& delim){
    if(delim == this->delim && vec.size() != 0){
      return;
    }

    vec.clear();

    std::string input;
    while(std::getline(st, input, delim)){
      insert(input);
    }

    this->delim = delim;
  }

  auto tokens(){
    return vec;
  }

private:
  std::vector<TType> vec;
  char delim = '\0';
  std::stringstream st;

  template<typename Z = TType>
	typename std::enable_if<std::is_arithmetic<Z>::value
                          && !std::is_same<char, Z>::value,void
                          >::type insert(std::string& s){
    TType val;
    auto res = std::from_chars(s.c_str(), s.c_str()+s.size(), val);
    if(res.ptr == s.c_str()+s.size()){
      if(res.ec != std::errc::result_out_of_range){
        // Complete string successfully parsed
        vec.emplace_back(val);
      }
      else{
        // Result of parse out of range of TType
        throw AoCError(std::string("Error: String ")+s+" produced out of range value.");
      }
    }
    else{
      throw AoCError(std::string("Error: String ")+s+" not fully parsed.");
    }
	}

  template<typename Z = TType>
	typename std::enable_if<std::is_convertible<std::string,Z>::value,void
                          >::type insert(std::string& s){
    vec.emplace_back(s);
	}

};

}

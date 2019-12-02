/**
 * @file tokenizer_ut.cpp
 * @brief Unit Tests for the AoC common Tokenizer
 */

#include "Tokenizer.hpp"
#include "aoc_except.hpp"
#include "ut_helpers.hpp"

#include <cstdio>
#include <catch.hpp>
#include <filesystem>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

using namespace AoC::common;


TEST_CASE("Tokenizer initial state"){
  Tokenizer<int> t("Hello, World.");

  REQUIRE(t.size() == 0);
  REQUIRE(t.begin() == t.end());

  SECTION("Non-existant file throws exception") {
    REQUIRE_THROWS_AS(Tokenizer<int>(fs::path("Non-existant-file")), FileNotFound);
  }
}

TEST_CASE("Tokens Function"){
  const std::string teststring("1\n2\n3");
  const std::vector<int> resvals = {1,2,3};
  Tokenizer<int> t(teststring);

  SECTION("Getting tokens before calling tokenize returns empty tokens"){
    REQUIRE(t.tokens().size() == 0);
  }

  SECTION("Returned tokens container contains same tokens as iterating over Tokenizer"){
    t.tokenize('\n');
    auto tokens = t.tokens();
    REQUIRE(t.size() == 3);
    REQUIRE(tokens.size() == 3);
    auto iter_t = t.begin();
    auto iter_tokens = tokens.begin();
    for(decltype(tokens)::size_type i = 0; i<3; i++){
      REQUIRE(*iter_t++ == *iter_tokens++);
    }
  }
}

TEST_CASE("Tokenizer Copying"){
  const std::string teststring("1\n2\n3");
  Tokenizer<int> orig(teststring);

  SECTION("Copying tokenizer which has not yet been tokenized"){

    SECTION("Copy Constructor"){
      Tokenizer<int> copy(orig);
      REQUIRE(orig.size() == copy.size());

      SECTION("Tokenizers deliver similar tokens"){
        orig.tokenize('\n');
        copy.tokenize('\n');
        for(auto iter_orig=orig.begin(),iter_copy=copy.begin();
            iter_orig != orig.end() && iter_copy != copy.end();
            ++iter_orig,++iter_copy
            ){
          REQUIRE(*iter_orig == *iter_copy);
        }
      }
    }

    SECTION("Copy Operator"){
      Tokenizer<int> copy = orig;
      REQUIRE(orig.size() == copy.size());

      SECTION("Tokenizers deliver similar tokens"){
        orig.tokenize('\n');
        copy.tokenize('\n');
        for(auto iter_orig=orig.begin(),iter_copy=copy.begin();
            iter_orig != orig.end() && iter_copy != copy.end();
            ++iter_orig,++iter_copy
            ){
          REQUIRE(*iter_orig == *iter_copy);
        }
      }
    }
  }
  SECTION("Copying tokenizer which has already been tokenized"){
    orig.tokenize('\n');

    SECTION("Copy Constructor"){
      Tokenizer<int> copy(orig);
      REQUIRE(orig.size() == copy.size());

      SECTION("Tokenizers deliver similar tokens"){
        for(auto iter_orig=orig.begin(),iter_copy=copy.begin();
            iter_orig != orig.end() && iter_copy != copy.end();
            ++iter_orig,++iter_copy
            ){
          REQUIRE(*iter_orig == *iter_copy);
        }
      }
    }

    SECTION("Copy Operator"){
      Tokenizer<int> copy = orig;
      REQUIRE(orig.size() == copy.size());

      SECTION("Tokenizers deliver similar tokens"){
        for(auto iter_orig=orig.begin(),iter_copy=copy.begin();
            iter_orig != orig.end() && iter_copy != copy.end();
            ++iter_orig,++iter_copy
            ){
          REQUIRE(*iter_orig == *iter_copy);
        }
      }
    }
  }
}

TEST_CASE("Tokenizer handling of empty input"){
  const std::string teststring("");
  Tempfile testfile(teststring,"aoc_testfile");

  SECTION("Empty string leads to no tokens"){
    Tokenizer<int> t(teststring);
    t.tokenize('\n');
    REQUIRE(t.begin() == t.end());
    REQUIRE(t.size() == 0);
  }
  SECTION("Empty file leads to no tokens") {
    Tokenizer<int> t(testfile.path());
    t.tokenize('\n');
    REQUIRE(t.begin() == t.end());
    REQUIRE(t.size() == 0);
  }

}

TEST_CASE("Tokenizer over ints"){
  const std::string teststring("1\n2\n3");
  const std::array<int, 3> resvals = {1,2,3};
  Tokenizer<int> t(teststring);
  t.tokenize('\n');

  SECTION("Tokenize call leads to increased size"){
    REQUIRE(t.size() == 3);
  }

  SECTION("Tokenizer contains exactly the three numbers given"){
    unsigned counter = 0;
    for(auto& i:t){
      REQUIRE(i == resvals[counter++]);
    }
  }
}

TEST_CASE("Tokenizer over strings") {
  const std::string teststring("Foo\nBar\nBaz");
  const std::array<std::string, 3> resvals = {"Foo", "Bar", "Baz"};
  Tokenizer<std::string> t(teststring);
  t.tokenize('\n');

  SECTION("Tokenize call leads to increased size") {
    REQUIRE(t.size() == 3);
  }

  SECTION("Tokenizer contains exactly the three strings given") {
    unsigned counter = 0;
    for (auto &i : t) {
      REQUIRE(i == resvals[counter++]);
    }
  }
}

class TestTokenType{
public:
  TestTokenType(const char* s): content(s[0]){}
  TestTokenType(const std::string& s): content(s[0]){}
  bool operator==(const TestTokenType& other) const{
    return this->content == other.content;
  }
private:
  char content;
};

TEST_CASE("Tokenizer over user defined type"){
  const std::string teststring("Foo\nBar\nNone");
  const std::array<TestTokenType, 3> resvals = {"Foo","Bar","None"};
  Tokenizer<TestTokenType> t(teststring);
  t.tokenize('\n');

  SECTION("Tokenize call leads to increased size") {
    REQUIRE(t.size() == 3);
  }

  SECTION("Tokenizer contains exactly the three TestTokenType given") {
    unsigned counter = 0;
    for (auto &i : t) {
      REQUIRE(i == resvals[counter++]);
    }
  }
}

TEST_CASE("Tokenizers from files and strings proudce similar results"){
  const std::string teststring("1\n2\n3");
  Tempfile testfile(teststring, "aoc_testfile");
  Tokenizer<int> s(teststring);
  Tokenizer<int> f(testfile.path());

  SECTION("Tokenizers start out with same size"){
    REQUIRE(s.size() == f.size());
  }

  SECTION("Both Tokenizers have the same size after tokenize() call"){
    s.tokenize('\n');
    f.tokenize('\n');
    REQUIRE(s.size() == f.size());
  }

  SECTION("Tokenizers produce the same tokens"){
    s.tokenize('\n');
    f.tokenize('\n');
    for(auto iter_s=s.begin(),iter_f=f.begin();
        iter_s != s.end() && iter_f != f.end();
        ++iter_s,++iter_f
        ){
      REQUIRE(*iter_s == *iter_f);
    }
  }
}

TEST_CASE("Token Parsing"){
  const std::string var_delimiter("1|2|3");
  const std::string no_numbers("a,b,c");
  const std::string partially_unparseable("15|189f");

  SECTION("Parser handles delimiters other than newline"){
    Tokenizer<int> t(var_delimiter);
    t.tokenize('|');
    REQUIRE(t.size() == 3);
    auto iter = t.begin();
    REQUIRE(*iter++ == 1);
    REQUIRE(*iter++ == 2);
    REQUIRE(*iter++ == 3);
  }

  SECTION("Parser throws exception for non-numbers"){
    Tokenizer<int> t(no_numbers);
    REQUIRE_THROWS_AS(t.tokenize(','), AoCError);
  }

  SECTION("Parser throws exception on partially parseable strings"){
    Tokenizer<int> t(partially_unparseable);
    REQUIRE_THROWS_AS(t.tokenize(','), AoCError);
  }

}

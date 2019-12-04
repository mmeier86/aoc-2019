#include "aoc_main.hpp"
#include "ut_helpers.hpp"

#include <catch.hpp>

#include <array>
#include <string>

using namespace AoC::common;

std::string empty1(){
  return "one";
}

std::string empty2(){
  return "two";
}

TEST_CASE("Wrong input arguments"){
  using DayClass = DayClassMock<int, empty1, empty2>;

  SECTION("One Argument results in error (only progname handed over)"){
    char* argv[] = {(char*)"ut"};
    int argc = 2;

    REQUIRE_THROWS_AS(aoc_main<DayClass>(argc, argv), AoCError);
  }

  SECTION("One Argument results in error"){
    char* argv[] = {(char*)"ut",(char*)"Foo"};
    int argc = 2;

    REQUIRE_THROWS_AS(aoc_main<DayClass>(argc, argv), AoCError);
  }

  SECTION("Five Arguments results in error"){
    char* argv[] = {(char*)"Foo",
                    (char*)"Bar",
                    (char*)"Baz",
                    (char*)"One",
                    (char*)"Three"};
    int argc = 5;

    REQUIRE_THROWS_AS(aoc_main<DayClass>(argc, argv), AoCError);
  }

  SECTION("Part != 1|2 results in error"){
    char* argv[] = {(char*)"ut",(char*)"3",(char*)"Foo"};
    int argc = 2;

    REQUIRE_THROWS_AS(aoc_main<DayClass>(argc, argv), AoCError);
  }
}

TEST_CASE("Full Execution"){
  const std::string teststring("1\n2\n3");
  Tempfile testfile(teststring, "aoc_testfile");
  using DayClass = DayClassMock<int, empty1, empty2>;
  char* argv[] = {(char*)"ut",(char*)"1",(char*)testfile.path().c_str()};
  int argc = 3;

  SECTION("Part 1 results are returned"){
    std::string res = aoc_main<DayClass>(argc, argv);
    REQUIRE(res == "one");
  }

  SECTION("Part 2 results are returned"){
    argv[1] = (char*)"2";
    INFO("Inputs: " << argv[1]);
    std::string res = aoc_main<DayClass>(argc, argv);
    REQUIRE(res == "two");
  }

}

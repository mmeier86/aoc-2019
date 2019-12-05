##
# Function to handle an AoC Day
##

include_guard(GLOBAL)

get_filename_component(AOC_ROOT "${CMAKE_CURRENT_LIST_DIR}/../" ABSOLUTE)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

# Macro to generate a full AoC 2019 build setup
# NOTE: The initial cmake_minimum_required and project calls still
# need to be placed in the root CMakeLists.txt file.
#
# Parameters:
# ----------
#
#   DAY:   The AoC day, in the form of "DD", e.g. "01" or "21"
#   NAME:  The name of the AoC day - should be a valid filename
#
# The macro will first include the cmake/preamble.cmake file.
# After that, the full build project is generated.
#
# The following variables are available after the macro:
#
#   AOC_LIB:   The name of the library generated
#   AOC_EXEC:  The main executable target for the day
#   AOC_UT:    The UT executable for the day
macro(init_aoc_day)
  cmake_parse_arguments(AOC
    ""
    "DAY;NAME"
    ""
    ${ARGN}
    )
  if(AOC_UNPARSED_ARGUMENTS)
    message(FATAL_ERROR "Invalid arguments to init_aoc_day: ${AOC_UNPARSED_ARGUMENTS}")
  endif()
  if(AOC_KEYWORDS_MISSING_VALUES)
    message(FATAL_ERROR "Missing values for parameters to init_aoc_day: ${AOC_KEYWORDS_MISSING_VALUES}")
  endif()

  include(preamble)
  set(AOC_LIB "${AOC_NAME}")
  add_library(${AOC_LIB} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/${AOC_NAME}.cpp
    )
  target_include_directories(${AOC_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    )
  target_link_libraries(${AOC_LIB} PUBLIC
    aoc::common
    )

  set(AOC_EXEC "day_${AOC_DAY}")
  add_executable(${AOC_EXEC}
    ${CMAKE_CURRENT_SOURCE_DIR}/day_${AOC_DAY}.cpp
    )
  target_link_libraries(${AOC_EXEC} PRIVATE
    ${AOC_LIB}
    )

  set(AOC_UT "day_${AOC_DAY}_ut")
  add_ut(${AOC_UT} day_${AOC_DAY}_ut.cpp)
  link_ut(${AOC_UT} PRIVATE ${AOC_LIB})
endmacro()

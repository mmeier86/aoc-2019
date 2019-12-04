# Include module for AoC common utilities

include_guard(GLOBAL)

include(ExternalProject)

get_filename_component(COMMON_DIR ${CMAKE_CURRENT_LIST_DIR}/../common ABSOLUTE)

add_library(common INTERFACE)
target_include_directories(common INTERFACE ${COMMON_DIR})
add_library(aoc::common ALIAS common)

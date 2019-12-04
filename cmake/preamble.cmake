# A common preamble for all AoC 2019 projects

include_guard(GLOBAL)

get_filename_component(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR}/.. ABSOLUTE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

string(APPEND CMAKE_CXX_FLAGS_DEBUG " -Wall -Werror -Wextra")

list(APPEND CMAKE_MODULE_PATH ${ROOT_DIR}/cmake)

include(UT)
include(common)

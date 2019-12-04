# Common library for the AoC 2019

cmake_minimum_required(VERSION 3.15)

project("Common AoC 2019" LANGUAGES CXX)

include(${CMAKE_CURRENT_LIST_DIR}/../cmake/preamble.cmake)

add_library(common INTERFACE)
target_include_directories(common INTERFACE ${CMAKE_CURRENT_LIST_DIR})

add_ut(tokenizer_ut tokenizer_ut.cpp)
link_ut(tokenizer_ut PRIVATE common)

add_ut(main_ut main_ut.cpp)
link_ut(main_ut PRIVATE common)

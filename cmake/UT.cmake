# UT functionality for AoC 2019

include_guard(GLOBAL)

option(UNITTESTS_ENABLED
  "ENABLE Unit Test Functionality"
  OFF
  )

if(UNITTESTS_ENABLED)
  enable_testing()
  set(VALGRIND_LABEL "Valgrind")
  find_program(VALGRIND_CMD valgrind)
  if(NOT VALGRIND_CMD)
    message(INFO "Valgrind not found. Valgrind UTs will not be genrated.")
  else()
    add_custom_target(check_valg
      COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -L "${VALGRIND_LABEL}"
      )
  endif()
  add_custom_target(check
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -LE "${VALGRIND_LABEL}"
    )

  get_filename_component(CATCH_DIR ${CMAKE_CURRENT_LIST_DIR}/../third_party/catch/ ABSOLUTE)

  add_library(catch2 STATIC ${CATCH_DIR}/catch_main.cpp)
  target_include_directories(catch2
    PUBLIC
    ${CATCH_DIR}
    )

  macro(add_ut t_name t_file)
    cmake_parse_arguments(ADDUT "" "T_DIR" "" ${ARGN})
    add_executable(${t_name} ${t_file} ${ADDUT_UNPARSED_ARGUMENTS})
    target_compile_definitions(${t_name} PRIVATE UNITTESTS_ENABLED)
    target_link_libraries(${t_name} PRIVATE catch2)
    add_test(NAME ${t_name}
      COMMAND ${t_name} --use-colour yes ${ADDUT_T_DIR}
      )
    add_dependencies(check ${t_name})
    if(VALGRIND_CMD)
      add_test(NAME ${t_name}_valgrind
        COMMAND ${VALGRIND_CMD} --error-exitcode=1 --leak-check=full --track-origins=yes $<TARGET_FILE:${t_name}> --use-colour yes ${ADDUT_T_DIR}
        )
      set_tests_properties(${t_name}_valgrind PROPERTIES LABELS "${VALGRIND_LABEL}")
      add_dependencies(check_valg ${t_name})
    endif()
  endmacro()
  macro(link_ut t_name)
    target_link_libraries(${t_name} ${ARGN})
  endmacro()
else()
  macro(add_ut)
  endmacro()
  macro(link_ut)
  endmacro()
endif()

# https://cmake.org/cmake/help/v3.5/manual/ctest.1.html
# https://cmake.org/Wiki/CMake/Testing_With_CTest
# https://cmake.org/cmake/help/v3.5/command/add_test.html?

include(CTest)
enable_testing()

# Convenience targets for fast testing
add_custom_target(check
    COMMAND echo [----] Running tests
    COMMAND ${CMAKE_CTEST_COMMAND}  --output-on-failure -C Debug
    DEPENDS example unittests)

add_custom_target(checkVerbose
    COMMAND echo [----] Running tests
    COMMAND ${CMAKE_CTEST_COMMAND}  -V --output-on-failure -C Debug
    DEPENDS example unittests)

#------------------------------------------------------------------------------
# CTest test suite
#
# Good to use to integration test, run whole program with parameters,
# check if it will crash, produce correct results, etc.


# Basic runable tests (will not crash)
add_test(NAME "Is_Runable "
    COMMAND $<TARGET_FILE:example>)

add_test(NAME "Is_Runable-v"
    COMMAND $<TARGET_FILE:example> -v)

add_test(NAME "Is_Runable-h"
    COMMAND $<TARGET_FILE:example> -h)





# Add unit test to CTest suite as one of the tests
add_test(NAME "catch_unit_tests"
    COMMAND $<TARGET_FILE:unittests>
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

#------------------------------------------------------------------------------
# Unit tests via Catch framework
#
# For testing on the function/class level.

set(SRCTEST
    ${CMAKE_CURRENT_SOURCE_DIR}/testmain.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../source/SomeClass.cpp
    )

add_executable(unittests EXCLUDE_FROM_ALL ${SRCTEST})
target_compile_definitions(unittests PRIVATE UNIT_TESTS)
set_property(TARGET unittests PROPERTY CXX_STANDARD 14) # we want C++14
add_dependencies(unittests Catch) # Catch is needed for unit tests, located in ../external
target_include_directories(unittests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../source
    ${EXTERNAL_CATCH_INCLUDE_DIR}
    )

# convenience target for running only the unit tests
add_custom_target(unit
    #this way we can use faux data from /test dir (if we hady any):
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND $<TARGET_FILE:unittests>
    DEPENDS unittests)
add_custom_target(unitall
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND $<TARGET_FILE:unittests> -s -a -r=compact
    DEPENDS unittests)



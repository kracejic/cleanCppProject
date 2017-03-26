# https://cmake.org/cmake/help/latest/manual/ctest.1.html
# https://cmake.org/Wiki/CMake/Testing_With_CTest
# https://cmake.org/cmake/help/latest/command/add_test.html?

include(CTest)

# Convenience targets for fast testing, they depends on binaries (so the build
# is triggered, when sources were changed).
add_custom_target(check
    COMMAND echo [----] Running tests
    COMMAND ${CMAKE_CTEST_COMMAND}  --output-on-failure -C Debug
    DEPENDS exampleApp unittests)

add_custom_target(checkVerbose
    COMMAND echo [----] Running tests
    COMMAND ${CMAKE_CTEST_COMMAND}  -V --output-on-failure -C Debug
    DEPENDS exampleApp unittests)

#------------------------------------------------------------------------------
# CTest test suite
#
# Test suite is defined here, when executed test fails (returns not 0), test
# failed. There are more options, check CMake documentation. 
#
# Good to use to integration test, run whole program with parameters,
# check if it will crash, produce correct results, etc.


# Basic runable tests (will not crash)
add_test(NAME "Is_Runable "
    COMMAND $<TARGET_FILE:exampleApp>)

add_test(NAME "Is_Runable-v"
    COMMAND $<TARGET_FILE:exampleApp> -v)

add_test(NAME "Is_Runable-h"
    COMMAND $<TARGET_FILE:exampleApp> -h)





# Add unit test to CTest suite as one of the tests
# unit test build is located in source/unittest/CMakeLists.txt
add_test(NAME "catch_unit_tests"
    COMMAND $<TARGET_FILE:unittests>
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


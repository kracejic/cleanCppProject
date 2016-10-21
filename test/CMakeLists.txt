# https://cmake.org/cmake/help/v3.5/manual/ctest.1.html
# https://cmake.org/Wiki/CMake/Testing_With_CTest
# https://cmake.org/cmake/help/v3.5/command/add_test.html?

include(CTest)

add_custom_target(check
    COMMAND echo [----] Running tests
    COMMAND ${CMAKE_CTEST_COMMAND}  --output-on-failure
    DEPENDS example)

add_custom_target(checkVerbose
    COMMAND echo [----] Running tests
    COMMAND ${CMAKE_CTEST_COMMAND}  -V --output-on-failure
    DEPENDS example)




# Basic runable tests (will not crash)
add_test(NAME "Is_Runable "
    COMMAND $<TARGET_FILE:example>)

add_test(NAME "Is_Runable-v"
    COMMAND $<TARGET_FILE:example> -v)

add_test(NAME "Is_Runable-h"
    COMMAND $<TARGET_FILE:example> -h)






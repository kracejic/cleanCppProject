#------------------------------------------------------------------------------
# Unit tests via Catch framework
#
# For testing on the function/class level.

add_executable(unittests EXCLUDE_FROM_ALL
    testmain.cpp
    ../SomeClass.cpp
    )
target_compile_definitions(unittests PRIVATE UNIT_TESTS) # add -DUNIT_TESTS define
target_include_directories(unittests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(unittests PRIVATE Catch)

# convenience target for running only the unit tests
add_custom_target(unit
    #this way we can use faux data from /test dir (if we have any):
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test
    COMMAND $<TARGET_FILE:unittests>
    DEPENDS unittests)
# Verbose printing of results
add_custom_target(unitall
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test
    COMMAND $<TARGET_FILE:unittests> -s -a -r=compact
    DEPENDS unittests)

add_custom_target(junit
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test
    COMMAND $<TARGET_FILE:unittests> -r=junit -o ${CMAKE_BINARY_DIR}/junit.xml
    DEPENDS unittests)


if(GDB_PATH)
    add_custom_target(unit-gdb
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test
        USES_TERMINAL
        DEPENDS unittests
        COMMAND ${GDB_PATH} $<TARGET_FILE:unittests>)
endif()

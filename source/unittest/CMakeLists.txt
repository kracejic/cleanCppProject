#------------------------------------------------------------------------------
# Unit tests via Catch framework
#
# For testing on the function/class level.

set(SRCTEST
    testmain.cpp
    ../SomeClass.cpp
    )

add_executable(unittests EXCLUDE_FROM_ALL ${SRCTEST})
target_compile_definitions(unittests PRIVATE UNIT_TESTS) #add -DUNIT_TESTS define
set_property(TARGET unittests PROPERTY CXX_STANDARD 14) # we want C++14
add_dependencies(unittests Catch) # Catch is needed for unit tests, located in ../external
target_include_directories(unittests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../source
    ${EXTERNAL_CATCH_INCLUDE_DIR}
    )

# convenience target for running only the unit tests
add_custom_target(unit
    #this way we can use faux data from /test dir (if we hady any):
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test
    COMMAND $<TARGET_FILE:unittests>
    DEPENDS unittests)
add_custom_target(unitall
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test
    COMMAND $<TARGET_FILE:unittests> -s -a -r=compact
    DEPENDS unittests)



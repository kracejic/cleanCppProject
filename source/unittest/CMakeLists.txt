#------------------------------------------------------------------------------
# Unit tests via Catch framework
#
# For testing on the function/class level.

add_executable(unittests EXCLUDE_FROM_ALL
    testmain.cpp
    ../SomeClass.cpp
    )
add_dependencies(unittests Catch) # Catch is needed for unit tests, located in ../external
target_compile_definitions(unittests PRIVATE UNIT_TESTS) # add -DUNIT_TESTS define
target_include_directories(unittests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories(unittests SYSTEM PRIVATE 
    ${EXTERNAL_CATCH_INCLUDE_DIR})

# convenience target for running only the unit tests
add_custom_target(unit
    #this way we can use faux data from /test dir (if we have any):
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test
    COMMAND $<TARGET_FILE:unittests>
    DEPENDS unittests)
add_custom_target(unitall
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test
    COMMAND $<TARGET_FILE:unittests> -s -a -r=compact
    DEPENDS unittests)



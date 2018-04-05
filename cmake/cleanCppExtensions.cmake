# Helper macro for creating convenient targets
find_program(GDB_PATH gdb)

# Adds -run and -dbg targets
macro(addRunAndDebugTargets TARGET)
    add_custom_target(${TARGET}-run
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        USES_TERMINAL
        DEPENDS ${TARGET}
        COMMAND ./${TARGET})

    # convenience run gdb target
    if(GDB_PATH)
        add_custom_target(${TARGET}-gdb
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            USES_TERMINAL
            DEPENDS ${TARGET}
            COMMAND ${GDB_PATH} ./${TARGET})
    endif()
endmacro()


#------------------------------------------------------------------------------
# Clang and gcc sanitizers
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message(STATUS "Sanitizers:")

    option(ADDRESS_SANITIZER "description" OFF)
    message(STATUS "  + ADDRESS_SANITIZER                     ${ADDRESS_SANITIZER}")
    if(ADDRESS_SANITIZER)
        add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
        link_libraries(-fsanitize=address -fno-omit-frame-pointer)
    endif()

    option(UB_SANITIZER "description" OFF)
    message(STATUS "  + UB_SANITIZER                          ${UB_SANITIZER}")
    if(UB_SANITIZER)
        add_compile_options(-fsanitize=undefined)
        link_libraries(-fsanitize=undefined)
    endif()

    option(THREAD_SANITIZER "description" OFF)
    message(STATUS "  + THREAD_SANITIZER                      ${THREAD_SANITIZER}")
    if(THREAD_SANITIZER)
        add_compile_options(-fsanitize=undefined)
        link_libraries(-fsanitize=undefined)
    endif()

    # Clang only
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        option(MEMORY_SANITIZER "description" OFF)
        message(STATUS "  + MEMORY_SANITIZER                      ${MEMORY_SANITIZER}")
        if(MEMORY_SANITIZER)
            add_compile_options(-fsanitize=memory -fno-omit-frame-pointer)
            link_libraries(-fsanitize=memory -fno-omit-frame-pointer)
        endif()
    endif()
endif()

#------------------------------------------------------------------------------
# Other MISC targets - formating, static analysis
# format, cppcheck, tidy
macro(addMiscTargets)
    file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.cc *.c)
    file(GLOB_RECURSE ALL_HEADER_FILES *.h *.hpp)

    # Static analysis via clang-tidy target
    # We check for program, since when it is not here, target makes no sense
    find_program(TIDY_PATH clang-tidy PATHS /usr/local/Cellar/llvm/*/bin)
    if(TIDY_PATH)
        message(STATUS "clang-tidy - static analysis              YES ")
        add_custom_target(tidy
            COMMAND ${TIDY_PATH} -header-filter=.* ${ALL_SOURCE_FILES} -p=./ )
    else()
        message(STATUS "clang-tidy - static analysis              NO ")
    endif()

    # cpp check static analysis
    find_program(CPPCHECK_PATH cppcheck)
    if(CPPCHECK_PATH)
        message(STATUS "cppcheck - static analysis                YES ")
        add_custom_target(
                cppcheck
                COMMAND ${CPPCHECK_PATH}
                --enable=warning,performance,portability,information,missingInclude
                --std=c++11
                --template=gcc
                --verbose
                --quiet
                ${ALL_SOURCE_FILES}
        )
    else()
        message(STATUS "cppcheck - static analysis                NO ")
    endif()

    # run clang-format on all files
    find_program(FORMAT_PATH clang-format)
    if(FORMAT_PATH)
        message(STATUS "clang-format - code formating             YES ")
        add_custom_target(format
            COMMAND ${FORMAT_PATH} -i ${ALL_SOURCE_FILES} ${ALL_HEADER_FILES} )
    else()
        message(STATUS "clang-format - code formating             NO ")
    endif()


    # Does not work well, left here for future work, but it would still only
    # provides same info as tidy, only in html form.
    #
    # Produces html analysis in *.plist dirs in build dir or build/source directory
    # add_custom_target(
    #     analyze
    #     COMMAND rm -rf ../*.plist
    #     COMMAND rm -rf *.plist
    #     COMMAND clang-check -analyze -extra-arg -Xclang -extra-arg -analyzer-output=html
    #     ${ALL_SOURCE_FILES}
    #     -p=./
    #     COMMAND echo ""
    #     )
endmacro()


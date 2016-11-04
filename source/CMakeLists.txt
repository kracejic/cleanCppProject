# configure version.cpp.in with selected version
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/version.cpp.in"
  "${CMAKE_CURRENT_BINARY_DIR}/version.cpp"
  )


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# source files are listed here
set(SRCS
    ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
    SomeClass.cpp
    SomeClass.h
    main.cpp
)

find_package (Threads REQUIRED) #threading

#-------------------------------------------------------------------------------
#example executable setup
add_executable(example ${SRCS})
target_link_libraries (example ${CMAKE_THREAD_LIBS_INIT}) #threading
if(NOT MSVC)
    target_compile_options(example PRIVATE -Wall -Wextra) # extra warnings
endif()
set_property(TARGET example PROPERTY CXX_STANDARD 14) # we want C++14
install(TARGETS example DESTINATION bin) #copy executable to bin folder on install
# convenience target for running the binary
add_custom_target(example-run
    WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin
    COMMAND ./example
    DEPENDS example Install_)

# short convenience target
add_custom_target(run DEPENDS example-run)


# And this would add -DBAR_ENABLE_FEATURE or equivalent
# target_compile_definitions(example PRIVATE BAR_ENABLE_FEATURE)

# Add compile time definition based on option
# option(OPTION_NAME "description for end user" OFF)
# if(OPTION_NAME)
#     # you can do anything here, eg. setup new optional executable
#     target_compile_definitions(example PRIVATE DEFINE_NAME)
# endif()

# Add shared library
# add_library(exampleLibrary SHARED ${LIBRARY_SOURCES})
# target_link_libraries (exampleLibrary ${CMAKE_THREAD_LIBS_INIT})
# set_property(TARGET exampleLibrary PROPERTY CXX_STANDARD 14) # we want C++14



#-------------------------------------------------------------------------------
# Copy MINGW needed libraries for building on windows
if(MINGW)
    message(STATUS "MinGW detected")
    get_filename_component(GCC_PATH ${CMAKE_C_COMPILER} PATH)
    if(${GCC_PATH} MATCHES "mingw64/bin")
        set(libgcc "libgcc_s_seh-1.dll") #64bit
        message(STATUS "  64bit dlls is building")
    else()
        set(libgcc "libgcc_s_dw2-1.dll") #32bit
        message(STATUS "  32bit dlls is building")
    endif()

    install(FILES ${GCC_PATH}/${libgcc}
        ${GCC_PATH}/libwinpthread-1.dll
        ${GCC_PATH}/libstdc++-6.dll
        DESTINATION ./
    )
endif(MINGW)


#------------------------------------------------------------------------------
# Other targets

file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.cc *.c)
file(GLOB_RECURSE ALL_HEADER_FILES *.h *.hpp)

# Static analysis via clang-tidy target
# We check for program, since when it is not here, target makes no sense
find_program(TIDY_PATH clang-tidy PATHS /usr/local/Cellar/llvm/*/bin)
if(TIDY_PATH)
    message(STATUS "clang-tidy - static analysis              YES ")
    add_custom_target(tidy
        COMMAND ${TIDY_PATH} ${ALL_SOURCE_FILES} -p=./ )
else()
    message(STATUS "clang-tidy - static analysis              NO ")
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
            ${ALL_SOURCE_FILES} ${ALL_HEADER_FILES}
    )
else()
    message(STATUS "cppcheck - static analysis                NO ")
endif()


# Does not work well, left here for future work, but it would still only
# provide same info as tidy, only in html form.
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



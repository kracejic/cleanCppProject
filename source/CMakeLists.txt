# configure version.cpp.in with selected version
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/version.cpp.in"
  "${CMAKE_CURRENT_BINARY_DIR}/version.cpp"
  )


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#-------------------------------------------------------------------------------
#exampleApp executable setup
set(ICON_RESOURCE "")

if(WIN32) #windows icon resource file, provided from /packaging directory
    set(ICON_RESOURCE "${PROJECT_BINARY_DIR}/exampleApp.icon.rc")
elseif (APPLE) #osx icon ressource file, provided from /packaging directory
	set(ICON_RESOURCE "${PROJECT_SOURCE_DIR}/packaging/exampleApp.icns")
endif()

# source files are listed here
set(SRCS
    ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
    SomeClass.cpp
    SomeClass.h
    main.cpp
)

find_package (Threads REQUIRED) #threading

add_executable(exampleApp MACOSX_BUNDLE ${SRCS} ${ICON_RESOURCE})
target_link_libraries (exampleApp ${CMAKE_THREAD_LIBS_INIT}) #threading

if(NOT MSVC)
    target_compile_options(exampleApp PRIVATE -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wunused -pedantic) # extra warnings
endif()

if(APPLE)
    set_target_properties(exampleApp PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "exampleApp")
    set_target_properties(exampleApp PROPERTIES MACOSX_BUNDLE_BUNDLE_GUI_IDENTIFIER "com.exampleApp.exampleApp")
    set_target_properties(exampleApp PROPERTIES MACOSX_BUNDLE_ICON_FILE exampleApp.icns)
    set_target_properties(exampleApp PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${PROJECT_SOURCE_DIR}/packaging/MacOSXBundleInfo.plist.in)
    set_source_files_properties(${PROJECT_SOURCE_DIR}/packaging/exampleApp.icns PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
endif()

set_property(TARGET exampleApp PROPERTY CXX_STANDARD 14) # we want C++14
# Bundle destination specific for Mac DMG.
install(TARGETS exampleApp BUNDLE DESTINATION "." RUNTIME DESTINATION bin)
# convenience target for running the binary
add_custom_target(exampleApp-run
    WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin
    COMMAND ./exampleApp
    DEPENDS exampleApp Install_)

# short convenience target
add_custom_target(run DEPENDS exampleApp-run)

# convenience run gdb target
find_program(GDB_PATH gdb)
if(GDB_PATH)
    add_custom_target(gdb
        WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin
        COMMAND ${GDB_PATH} ./exampleApp
        DEPENDS exampleApp Install_)
endif()

# And this would add -DBAR_ENABLE_FEATURE or equivalent to build command
# target_compile_definitions(exampleApp PRIVATE BAR_ENABLE_FEATURE)

# Add compile time definition based on option
# option(OPTION_NAME "description for end user" OFF)
# if(OPTION_NAME)
#     # you can do anything here, eg. setup new optional executable
#     target_compile_definitions(exampleApp PRIVATE DEFINE_NAME)
# endif()

# Add building new shared library
# add_library(exampleLibrary SHARED ${LIBRARY_SOURCES})
# target_link_libraries (exampleLibrary ${CMAKE_THREAD_LIBS_INIT})
# set_property(TARGET exampleLibrary PROPERTY CXX_STANDARD 14) # we want C++14

# How to include and link OpenGL and GLUT libraries
# find_package(OpenGL REQUIRED)
# find_package(GLUT REQUIRED)
# target_include_directories(exampleApp SYSTEM ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )
# target_link_libraries(exampleApp ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ) 

#------------------------------------------------------------------------------
# Unit tests

add_subdirectory(unittest)

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
        DESTINATION ./bin/
    )
endif(MINGW)


#------------------------------------------------------------------------------
# Other MISC targets
#------------------------------------------------------------------------------

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



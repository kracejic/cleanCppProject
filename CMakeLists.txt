cmake_minimum_required (VERSION 3.6)

# Project setup, versioning stuff here, change when changing the version
# Note: keep the project name lower case only for easy linux packaging support
project (cleancppproject VERSION 0.3.5)
set(VERSION_TYPE "beta" CACHE STRING "version type" FORCE)
site_name(VERSION_HOST) # read hostname to VERSION_HOST
set(VERSION_HOST "${VERSION_HOST}" CACHE STRING "host of build" FORCE)

message(STATUS "")
message(STATUS "    == ${PROJECT_NAME} Project configuration ==")
message(STATUS "")

#------------------------------------------------------------------------------
# General settings

# Be nice to visual studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Be nice and export compile commands by default, this is handy for clang-tidy
# and for other tools.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# We can use include() and find_package() for our scripts in there
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Use gold linker to speed up linking time, see cmake/useGoldLinker.cmake
include(useGoldLinker)

# Helpful option enable build profiling to identify slowly compiling files
option(MEASURE_ALL "When enabled all commands will be passed through time command" OFF)
if(MEASURE_ALL)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "time")
endif()

#-------------------------------------------------------------------------------
# Set default install location to dist folder in build dir
# we do not want to install to /usr by default
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/dist" CACHE PATH
        "Install path prefix, prepended onto install directories." FORCE )
endif()
#------------------------------------------------------------------------------
# Custom Install target, used in run target in source/CMakeLists.txt
if (CMAKE_GENERATOR MATCHES "Makefiles")
    # Make it multithreaded
    add_custom_target( Install_ COMMAND "${CMAKE_COMMAND}" --build . --target
        install -- -j WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
else()
    add_custom_target( Install_ COMMAND "${CMAKE_COMMAND}" --build . --target
        install WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
endif()


#------------------------------------------------------------------------------
# Included CMakeLists.txt

# External resources/repositories are downloaded here
add_subdirectory(external)

# Documentation build
add_subdirectory(doc)

# Images, databases and other data which needs to be installed for project
add_subdirectory(data)

# Testing
enable_testing()
add_subdirectory(test)

# Source code
add_subdirectory(source)

# Packaging stuff (deb, rpm, windows installer)
add_subdirectory(packaging)



#-------------------------------------------------------------------------------
# Wrap up of settings printed on build
message(STATUS "")
message(STATUS "    == Final overview for ${PROJECT_NAME} ==")
message(STATUS "Version:              ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH} ${VERSION_TYPE} @ ${VERSION_HOST}")
message(STATUS "Install prefix:       ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Compiler:             ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_BUILD_TYPE:     ${CMAKE_BUILD_TYPE}")
message(STATUS "  possible options: Debug Release RelWithDebInfo MinSizeRel")
message(STATUS "  set with ` cmake -DCMAKE_BUILD_TYPE=Debug .. `")
message(STATUS "")



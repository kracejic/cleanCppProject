cmake_minimum_required (VERSION 3.2)
message(STATUS "")
message(STATUS "    == Clean Cpp Project configuration ==")
message(STATUS "")


# Project setup, versioning stuff here, change when changing the version
# Note: keep the project name lower case only for easy linux packaging support
project (cleancppproject VERSION 0.3.2)
set(VERSION_TYPE "beta" CACHE STRING "version type" FORCE)
site_name(VERSION_HOST)
set(VERSION_HOST "${VERSION_HOST}" CACHE STRING "host of build" FORCE)

# Be nice to visual studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Be nice and export compile commands by default, this is handy for clang-tidy
# and for other tools.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
message(STATUS "    == Final overview ==")
message(STATUS "Version:              ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH} ${VERSION_TYPE} @ ${VERSION_HOST}")
message(STATUS "Install prefix:       ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_BUILD_TYPE:     ${CMAKE_BUILD_TYPE}")
message(STATUS "  possible options: Debug Release RelWithDebInfo MinSizeRel")
message(STATUS "  set with ` cmake -DCMAKE_BUILD_TYPE=Debug .. `")
message(STATUS "")



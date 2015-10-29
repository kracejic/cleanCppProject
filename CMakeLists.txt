cmake_minimum_required (VERSION 3.0)

# Project setup
project (emptyProject)
set(MAJOR_VERSION 0 CACHE STRING "major version" FORCE)
set(MINOR_VERSION 1 CACHE STRING "minor version" FORCE)
set(PATCH_VERSION 0 CACHE STRING "patch version" FORCE)
set(VERSION_TYPE "beta" CACHE STRING "version type" FORCE)
site_name(VERSION_HOST)
set(VERSION_HOST "${VERSION_HOST}" CACHE STRING "host of build" FORCE)

configure_file (
  "${PROJECT_SOURCE_DIR}/source/version.cpp.in"
  "${PROJECT_BINARY_DIR}/source/version.cpp"
  )


# Flags
set(CMAKE_CXX_FLAGS "-std=c++14")

include_directories( 
    ${PROJECT_SOURCE_DIR}/source
)

set(SRCS
    ${PROJECT_BINARY_DIR}/source/version.cpp
    source/main.cpp
)


add_executable(runMe ${SRCS})


install(TARGETS runMe DESTINATION bin)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/data
        DESTINATION ./
    )




if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/dist" CACHE PATH "Install path prefix, prepended onto install directories." FORCE )
endif()

message(STATUS "")
message(STATUS "    == Overview ==")
message(STATUS "Version: ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION} ${VERSION_TYPE}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "")


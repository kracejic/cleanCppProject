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
set(CMAKE_CXX_FLAGS "-std=c++14 -O3")

include_directories( 
    ${PROJECT_SOURCE_DIR}/source
)

set(SRCS
    ${PROJECT_BINARY_DIR}/source/version.cpp
    source/main.cpp
)


find_package (Threads) #threading
add_executable(runMe ${SRCS})
target_link_libraries (runMe ${CMAKE_THREAD_LIBS_INIT}) #threading

install(TARGETS runMe DESTINATION bin)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/data
        DESTINATION ./
    )


# Copy MINGW libraries
if(MINGW)
  get_filename_component(GCC_PATH ${CMAKE_C_COMPILER} PATH)
  install(FILES ${GCC_PATH}/libgcc_s_dw2-1.dll
      ${GCC_PATH}/libwinpthread-1.dll
      ${GCC_PATH}/libstdc++-6.dll
      DESTINATION ./
    )
endif(MINGW)



if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/dist" CACHE PATH "Install path prefix, prepended onto install directories." FORCE )
endif()

message(STATUS "")
message(STATUS "    == Overview ==")
message(STATUS "Version: ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION} ${VERSION_TYPE}")
message(STATUS "Install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "")

if(MINGW) 
  # MESSAGE (STATUS "* Will copy MINGW libs to install folder: " ${GCC_PATH}) 
  MESSAGE (STATUS "* Will copy MINGW libs to install folder: ") 
endif(MINGW)

message(STATUS "")


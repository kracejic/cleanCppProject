cmake_minimum_required (VERSION 3.2)
message(STATUS "")
message(STATUS "    == Empty Project configuration ==")
message(STATUS "")


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


# Flags for all, used every time, see target_compile_options
# set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra")

include_directories(
    ${PROJECT_SOURCE_DIR}/source
)

set(SRCS
    ${PROJECT_BINARY_DIR}/source/version.cpp
    source/main.cpp
)


find_package (Threads REQUIRED) #threading
add_executable(runMe ${SRCS})
target_compile_options(runMe PRIVATE -funroll-loops -std=c++14 -Wall -Wextra)
target_link_libraries (runMe ${CMAKE_THREAD_LIBS_INIT}) #threading

# Will add -DBAR_ENABLE_FEATURE or equivalent
# target_compile_definitions(bar PRIVATE BAR_ENABLE_FEATURE)


install(TARGETS runMe DESTINATION bin)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/data
        DESTINATION ./
    )


# Copy MINGW libraries
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



if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/dist" CACHE PATH "Install path prefix, prepended onto install directories." FORCE )
endif()

message(STATUS "")
message(STATUS "    == Overview ==")
message(STATUS "Version:              ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION} ${VERSION_TYPE} @ ${VERSION_HOST}")
message(STATUS "Install prefix:       ${CMAKE_INSTALL_PREFIX}")
message(STATUS "PROJECT_SOURCE_DIR:   ${PROJECT_SOURCE_DIR}")
message(STATUS "CMAKE_BUILD_TYPE:     ${CMAKE_BUILD_TYPE}")
message(STATUS "  possible options: Debug Release RelWithDebInfo MinSizeRel")
message(STATUS "  set with ` cmake -DCMAKE_BUILD_TYPE=Debug .. `")
message(STATUS "")

if(MINGW)
  # MESSAGE (STATUS "* Will copy MINGW libs to install folder: " ${GCC_PATH})
  MESSAGE (STATUS "* Will copy MINGW libs to install folder: ")
endif(MINGW)

message(STATUS "")


cmake_minimum_required (VERSION 3.2)
message(STATUS "")
message(STATUS "    == Clean Cpp Project configuration ==")
message(STATUS "")


# Project setup, versioning stuff here, change when changing the version
project (cleanCppProject VERSION 0.3.2)
set(VERSION_TYPE "beta" CACHE STRING "version type" FORCE)
site_name(VERSION_HOST)
set(VERSION_HOST "${VERSION_HOST}" CACHE STRING "host of build" FORCE)

#be nice to visual studio
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#be nice and export compile commands by default, this is handy for clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_testing()

#-------------------------------------------------------------------------------
# Set default install location to dist folder in build dir
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/dist" CACHE PATH
        "Install path prefix, prepended onto install directories." FORCE )
endif()
#------------------------------------------------------------------------------
# Custom Install target, used in run target in source/CMakeLists.txt
add_custom_target( Install_ COMMAND "${CMAKE_COMMAND}" --build . --target install
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")


#------------------------------------------------------------------------------
# Included CMakeLists.txt

# Documentation build
add_subdirectory(doc)

# External resources/repositories are downloaded here
add_subdirectory(external)

# install images, databases and other data
add_subdirectory(data)

add_subdirectory(test)
add_subdirectory(source)


#------------------------------------------------------------------------------
# CPACK
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_VENDOR "kracejic")
set(CPACK_PACKAGE_CONTACT "kracejic@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Clean cpp project")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/readme.md")
SET(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/license.md")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CMAKE_PROJECT_NAME}")
set(CPACK_PACKAGE_DIRECTORY "${CMAKE_BINARY_DIR}/packages")

if(WIN32 AND NOT UNIX)
    # There is a bug in NSI that does not handle full unix paths properly. Make
    # sure there is at least one set of four (4) backlasshes.
    set(CPACK_GENERATOR "NSIS;STGZ;ZIP")

    # set(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
    # set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\MyExecutable.exe")
    set(CPACK_NSIS_DISPLAY_NAME "Clean cpp Project")
    # set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org")
    # set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
    # set(CPACK_NSIS_CONTACT "me@my-personal-home-page.com")
    set(CPACK_NSIS_MODIFY_PATH ON)
else()
    set(CPACK_GENERATOR "DEB;TGZ;TBZ2")
    find_program(RPMBUILD_PATH rpmbuild)
    if(RPMBUILD_PATH)
        # TODO rpms
        set(CPACK_GENERATOR "${CPACK_GENERATOR};RPM")
    endif()

    # TODO do this better
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
    # Debian dependencies
    # set(CPACK_DEBIAN_PACKAGE_DEPENDS "libgtkmm-3.0")
endif()

set(CPACK_PACKAGE_EXECUTABLES "example" "My Example Executable")
set(CPACK_CREATE_DESKTOP_LINKS "example")

# TODO
# set(CPACK_PACKAGE_ICON "${PROJECT_SOURCE_DIR}/packages")

include(CPack)



#-------------------------------------------------------------------------------
# Wrap up of settings printed on build
message(STATUS "")
message(STATUS "    == Final overview ==")
message(STATUS "Version:              ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH} ${VERSION_TYPE} @ ${VERSION_HOST}")
message(STATUS "Install prefix:       ${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_BUILD_TYPE:     ${CMAKE_BUILD_TYPE}")
message(STATUS "  possible options: Debug Release RelWithDebInfo MinSizeRel")
message(STATUS "  set with ` cmake -DCMAKE_BUILD_TYPE=Debug .. `")

if(MINGW)
  MESSAGE (STATUS "* Will copy MINGW libs to install folder")
endif(MINGW)
message(STATUS "")



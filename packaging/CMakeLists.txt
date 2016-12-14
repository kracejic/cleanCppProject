
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
    #--------------------------------------------------------------------------
    # Windows
    set(CPACK_GENERATOR "STGZ;ZIP")
    message(STATUS "Package generation - Windows")
    message(STATUS "   + STGZ                                 YES ")
    message(STATUS "   + ZIP                                  YES ")

    # NSIS windows installer
    find_program(NSIS_PATH nsis)
    if(NSIS_PATH)
        set(CPACK_GENERATOR "${CPACK_GENERATOR};NSIS")
        message(STATUS "   + NSIS                                 YES ")
        # Note: There is a bug in NSI that does not handle full unix paths properly. Make
        # sure there is at least one set of four (4) backlasshes.
        # set(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
        # set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\MyExecutable.exe")
        set(CPACK_NSIS_DISPLAY_NAME "Clean cpp Project")
        # set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org")
        # set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
        # set(CPACK_NSIS_CONTACT "me@my-personal-home-page.com")
        set(CPACK_NSIS_MODIFY_PATH ON)
    else()
        message(STATUS "   + NSIS                                 NO ")
    endif()



else()
    #-----------------------------------------------------------------------------
    # Linux
    set(CPACK_GENERATOR "DEB;TGZ;TBZ2")
    message(STATUS "Package generation - UNIX")
    message(STATUS "   + DEB                                  YES ")
    message(STATUS "   + TGZ                                  YES ")
    message(STATUS "   + TBZ2                                 YES ")

    find_program(RPMBUILD_PATH rpmbuild)
    if(RPMBUILD_PATH)
        # TODO rpms
        message(STATUS "   + RPM                                  YES ")
        set(CPACK_GENERATOR "${CPACK_GENERATOR};RPM")
        set(CPACK_RPM_PACKAGE_LICENSE "MIT")
        # set(CPACK_RPM_PACKAGE_REQUIRES "gtkmm30")
    else()
        message(STATUS "   + RPM                                  NO ")
    endif()

    # TODO do this better
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
    set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/kracejic/cleanCppProject")
    # set(CPACK_DEBIAN_PACKAGE_DEPENDS "libgtkmm-3.0")
endif()


set(CPACK_PACKAGE_EXECUTABLES "example" "My Example Executable")
set(CPACK_CREATE_DESKTOP_LINKS "example")

# TODO
# set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/packages")


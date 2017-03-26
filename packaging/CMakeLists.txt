
#------------------------------------------------------------------------------
# CPACK
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_VENDOR "kracejic")
set(CPACK_PACKAGE_CONTACT "kracejic <kracejic@gmail.com>")
set(HOMEPAGE "https://github.com/kracejic/cleanCppProject")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
    "Clean cpp project. This is simple cpp example project build with CMake.")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/readme.md")
SET(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/license.md")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CMAKE_PROJECT_NAME}")
set(CPACK_PACKAGE_DIRECTORY "${CMAKE_BINARY_DIR}/out")


# set human names to exetuables
set(CPACK_PACKAGE_EXECUTABLES "exampleApp" "My Example Executable")
set(CPACK_CREATE_DESKTOP_LINKS "exampleApp")
set(CPACK_STRIP_FILES TRUE)


if(WIN32 AND NOT UNIX)
    #--------------------------------------------------------------------------
    # Windows specific
    set(CPACK_GENERATOR "STGZ;ZIP")
    message(STATUS "Package generation - Windows")
    message(STATUS "   + STGZ                                 YES ")
    message(STATUS "   + ZIP                                  YES ")

    # NSIS windows installer
    find_program(NSIS_PATH nsis PATH_SUFFIXES nsis)
    if(NSIS_PATH)
        set(CPACK_GENERATOR "${CPACK_GENERATOR};NSIS")
        message(STATUS "   + NSIS                                 YES ")
        # Note: There is a bug in NSI that does not handle full unix paths properly. Make
        # sure there is at least one set of four (4) backlasshes.
        set(CPACK_NSIS_DISPLAY_NAME "Clean cpp Project")
        # Icon of the installer
        set(CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\exampleApp.ico")
        # set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org")
        # set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
        set(CPACK_NSIS_CONTACT "${CPACK_PACKAGE_CONTACT}")
        set(CPACK_NSIS_MODIFY_PATH ON)
    else()
        message(STATUS "   + NSIS                                 NO ")
    endif()

    set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\exampleApp.png")

    # Configure file with right path, place the result to PROJECT_BINARY_DIR.
    # When ${PROJECT_BINARY_DIR}/exampleApp.icon.rc is added to an executable
    # it will have icon specified in exampleApp.icon.in.rc
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/exampleApp.icon.in.rc
        ${PROJECT_BINARY_DIR}/exampleApp.icon.rc)

else()
    #-----------------------------------------------------------------------------
    # Linux specific
    set(CPACK_GENERATOR "DEB;TBZ2;TXZ")
    message(STATUS "Package generation - UNIX")
    message(STATUS "   + DEB                                  YES ")
    message(STATUS "   + TBZ2                                 YES ")
    message(STATUS "   + TXZ                                  YES ")

    find_program(RPMBUILD_PATH rpmbuild)
    if(RPMBUILD_PATH)
        message(STATUS "   + RPM                                  YES ")
        set(CPACK_GENERATOR "${CPACK_GENERATOR};RPM")
        set(CPACK_RPM_PACKAGE_LICENSE "MIT")
        # set(CPACK_RPM_PACKAGE_REQUIRES "gtkmm30")
        # exclude folders which clash with default ones
        set(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST
            ${CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST}
            /usr
            /usr/bin
            /usr/share
            /usr/share/applications
            /usr/share/doc
            /usr/share/icons
            /usr/share/icons/hicolor
            /usr/share/icons/hicolor/256x256
            /usr/share/icons/hicolor/256x256/apps
            /usr/share/icons/gnome
            /usr/share/icons/gnome/256x256
            /usr/share/icons/gnome/256x256/apps)
    else()
        message(STATUS "   + RPM                                  NO ")
    endif()

    # TODO do this better
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
    set(CPACK_DEBIAN_PACKAGE_CONTROL_STRICT_PERMISSION TRUE)
    set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "${HOMEPAGE}")
    # set(CPACK_DEBIAN_COMPRESSION_TYPE "xz")
    # set(CPACK_DEBIAN_PACKAGE_DEPENDS "libgtkmm-3.0")



    # Icon and app shortcut for Linux systems
    # Note: .desktop file must have same name as executable
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/exampleApp.desktop
        DESTINATION share/applications/
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
        )
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/exampleApp.png
        DESTINATION share/icons/hicolor/256x256/apps/
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
        )
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/exampleApp.png
        DESTINATION share/icons/gnome/256x256/apps/
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
        )
    # License file
    install(FILES ${PROJECT_SOURCE_DIR}/license.md
        DESTINATION share/doc/${PROJECT_NAME}/
        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
        RENAME copyright)
    # set package icon
    set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/exampleApp.png")
endif()




#------------------------------------------------------------------------------
# and include CPack, so we get target for packages
include(CPack)




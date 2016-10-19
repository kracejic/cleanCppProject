cmake_minimum_required (VERSION 2.8)

# Helper functions
macro(path_linux_to_win MsysPath ResultingPath)
  string(REGEX REPLACE "^/([a-zA-Z])/" "\\1:/" ${ResultingPath} "${MsysPath}")
endmacro()
macro(path_win_to_linux MsysPath ResultingPath)
  string(REGEX REPLACE "^([a-zA-Z]):/" "/\\1/" ${ResultingPath} "${MsysPath}")
endmacro()

# enable if doxygen found
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})
if(DOXYGEN_VERSION VERSION_LESS "1.8.0")
    message(WARNING "Doxygen version " ${DOXYGEN_VERSION} " is older than 1.8.0, disabling documentation build")
    set(BUILD_DOCUMENTATION FALSE)
endif()

if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()

    path_win_to_linux(${CMAKE_CURRENT_SOURCE_DIR} CMAKE_CURRENT_SOURCE_DIR_LINUX)
    path_win_to_linux(${PROJECT_SOURCE_DIR} PROJECT_SOURCE_DIR_LINUX)

    # configure doxygen configuration file
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    # doc build only target, target is not in default build, so it must be
    # triggered explicitly
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

    # where doc will be installed
    install(
        DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/
        DESTINATION ./doc
        OPTIONAL)
endif()


message(STATUS "Building doc:         ${BUILD_DOCUMENTATION}")



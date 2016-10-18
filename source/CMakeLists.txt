
# wsourceill configure version.cpp.in with selected version
configure_file (
  "${CMAKE_CURRENT_SOURCE_DIR}/version.cpp.in"
  "${CMAKE_CURRENT_BINARY_DIR}/version.cpp"
  )


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(SRCS
    ${CMAKE_CURRENT_BINARY_DIR}/version.cpp
    SomeClass.cpp
    main.cpp
)

find_package (Threads REQUIRED) #threading

#-------------------------------------------------------------------------------
#runMe executable setup
add_executable(runMe ${SRCS})
target_link_libraries (runMe ${CMAKE_THREAD_LIBS_INIT}) #threading
if(NOT MSVC)
    target_compile_options(runMe PRIVATE -Wall -Wextra) # extra warnings
endif()
set_property(TARGET runMe PROPERTY CXX_STANDARD 14) # we want C++14
install(TARGETS runMe DESTINATION bin) #copy executable to bin folder on install

# And this would add -DBAR_ENABLE_FEATURE or equivalent
# target_compile_definitions(runMe PRIVATE BAR_ENABLE_FEATURE)


#-------------------------------------------------------------------------------
# copy all from data to install dir /share
install(DIRECTORY ${PROJECT_SOURCE_DIR}/data
        DESTINATION ./share
    )

#-------------------------------------------------------------------------------
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


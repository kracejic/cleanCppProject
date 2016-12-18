


# Description of the directory structure

* mainProjectFolder
    - **build** - user created, build takes place here
        + **dist** - here builded application is copied (by deafult, see CMAKE_INSTALL_PREFIX in main CMakeLists.txt)
            * **bin**
            * **share**
                - **data** - here folder data is copied
            * **doc**
                - doxygen lives here documentation
    - **data** - contain data
    - **doc** - contains documentation
        + CMakeLists.txt - doc building
        + **doxygen**
            * doxygen settings, and modern style config
    - **packaging**
        + CMakeLists.txt - package creation
        + example.desktop - linux shortcut (app is then visible in launchers)
        + example.png - icon for linux shortcut
        + example.icon.in.rc - icon for windows description file (used in source/CMakeLists.txt)
        + example.ico - icon for windows shortcut (linked via example.icon.in.rc into the executable)
    - **source** - contain source files
        + CMakeLists.txt - source building
        + .ycm_extra_conf.py - for ycm smart autocompletion
    - **test** - testing
        + CMakeLists.txt - tests building
        + testmain.cpp - main tests function
    - **external**
        + CMakeLists.txt - external projects handling (eg. Download of Catch)
    - readme.md - main readme file
    - CMakeLists.md - Main CMake configuration
    - .clang-format - clang format config file
    - .clang-tidy - clang tidy config file
    - .travis.yml - continuous integration configuration






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
    - **source** - contain source files
        + CMakeLists.txt - source building
        + .ycm_extra_conf.py - for ycm smart autocompletion
    - **test** - testing
        + CMakeLists.txt - tests building
    - **external**
        + CMakeLists.txt - external projects handling (eg. Download of Catch)
    - readme.md - main readme file
    - CMakeLists.md - Main CMake configuration
    - .clang-format - clang format config file



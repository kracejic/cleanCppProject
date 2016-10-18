# Design Document

I have prepared CMake configuration as well as gitignore file, doxygen documentation

Main technologies used here
* Git
    - Source control
* CMake
    - Used as build tool
    - Doxygen generation
* Doxygen
    - For documentation and API reference generation
    - Custom modern style included
        + to try modern style see doc/doxygen/Doxyfile.in line 3
        + if you do not care feel free to delete `doc/doxygen/*.html` and `doc/doxygen/*.ccs`

There is extra support for these:
* .ycm_extra_conf.py for ycmd support 
    - Smart autocompletion, goto def, etc.
    - Works in Vim, Sublime Text 3, Atom
* Sublime text 3 project file
    - Build system defined for *make* or *ninja*
* Feel free to delete these files.

# Design Document


Goal of this project is to create a base empty project for everyone to use.

## Used technologies

Project is built on these technologies:

* Git
    - Source control
* CMake
    - Used as build tool
    - Doxygen generation
* Doxygen
    - For documentation and API reference generation
    - Generates wiki from markdown files
    - Custom modern style included
        + to try modern style see doc/doxygen/Doxyfile.in line 3
        + if you do not care feel free to delete `doc/doxygen/*.html` and `doc/doxygen/*.ccs`
    - Graphviz - for creating UML diagrams with doxygen
* clang-format 
    - Configuration file in the root of project for easy formating
    - Clang-format automaticaly uses nearest *.clang-format* file
* clang-tidy 
    - With target *tidy* you can run static code analysis


There is extra support for these:

* .ycm_extra_conf.py for ycmd support
    - Smart autocompletion, goto def, etc.
    - Works in Vim, Sublime Text 3, Atom
* Sublime text 3 project file





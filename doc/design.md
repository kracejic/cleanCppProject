# Design Document

Goal of this project is to create a base empty project for everyone to use.

## Used technologies

Project is built on these technologies:

* Git
    - Source control
* CMake
    - Used as build tool
    - Doxygen generation
    - CTest - for running tests
    - CPack - for packaging the releases
        + NSIS - windows installer
        + RPM / DEB - linux packages
        + compressed archives
* Doxygen
    - For documentation and API reference generation
    - Generates wiki from markdown files
    - Custom modern style included
        + to try modern style see doc/doxygen/Doxyfile.in line 3
        + if you do not care feel free to delete `doc/doxygen/*.html` and `doc/doxygen/*.ccs`
    - Graphviz - for creating UML diagrams with doxygen
* clang-format 
    - Configuration file in the root of project for easy formating
    - Clang-format automatically uses nearest *.clang-format* file
    - Target *format* will run format on all source files
* clang-tidy 
    - With target *tidy* you can run static code analysis
* cppcheck
    - With target *cppcheck* you can run static code analysis
* [Catch](https://github.com/philsquared/Catch)
    - Modern unit test framework
    - Downloaded via externalproject from *external/CMakeLists.txt*



There is extra support for these:

* .ycm_extra_conf.py for ycmd support
    - Smart autocompletion, goto def, etc.
    - Works in Vim, Emacs, Sublime Text 3, Atom, Visual Studio Code
    - Site: [github.com/Valloric/ycmd](https://github.com/Valloric/ycmd)
* Sublime text 3 project file
    - with build system targets


## Deployment view

To showcase PlantUML, here is a graph for you:

\startuml
top to bottom direction

frame "Internal network" {

    frame "git server" {
      artifact "git repository" as gitS
    }

    frame "build server" {
      artifact "build git repository" as gitB
      node doxygen
      node "build system" as buildB
    }

    frame "developer machine" as dev {
      artifact "local git repository" as gitD
      node "build system" as buildD
      artifact "binaries" as releaseD
    }

    gitD --> buildD
    buildD --> releaseD

    gitS --> gitB
    gitS <--> gitD

    frame "internal web server" {
      artifact "generated documentation" as doc
    }

    :developer: ..> dev : "develops at"
    :developer: ..> doc : "looks at"


    gitB --> doxygen
    doxygen --> doc

}

frame "external web server" {
  artifact "customer support, etc."
  artifact "released versions" as release
}

:customer: ..> release : downloads 

gitB --> buildB
buildB -right-> release
\enduml

This graph was generated from this:

~~~
\\startuml
top to bottom direction

frame "Internal network" {

    frame "git server" {
      artifact "git repository" as gitS
    }

    frame "build server" {
      artifact "build git repository" as gitB
      node doxygen
      node "build system" as buildB
    }

    frame "developer machine" as dev {
      artifact "local git repository" as gitD
      node "build system" as buildD
      artifact "binaries" as releaseD
    }

    gitD --> buildD
    buildD --> releaseD

    gitS --> gitB
    gitS <--> gitD

    frame "internal web server" {
      artifact "generated documentation" as doc
    }

    :developer: ..> dev : "develops at"
    :developer: ..> doc : "looks at"


    gitB --> doxygen
    doxygen --> doc

}

frame "external web server" {
  artifact "customer support, etc."
  artifact "released versions" as release
}

:customer: ..> release : downloads 

gitB --> buildB
buildB -right-> release
\\enduml

~~~

For more inspiration on what can be done with PlantUML look at their pages [plantuml.com](http://plantuml.com/sequence-diagram), and see #main function for example sequence diagram.





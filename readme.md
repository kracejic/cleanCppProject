# EmptyCppProject

This is a empty frame for project in C++. It should help everybody to start a new project without caring for build enviroment setup.

I have prepared CMake configuration as well as gitignore file, doxygen documentation

Main technologies used here
* Git
    - Source control
* CMake
    - Used as build tool
    - Doxygen generation
* Doxygen
    - For documentation and API reference generation

There is extra support for these:
* .ycm_extra_conf.py for ycmd support 
    - Smart autocompletion, goto def, etc.
    - Works in Vim, Sublime Text 3, Atom
* Sublime text 3 project file
    - Build system defined for *make* or *ninja*
* Feel free to delete these files.


## Important pages

* [List of todos](./todo.html)
* [Basic directory structure](./md_doc_directoryStructure.html)
<!-- * \link todo List of todos DoxygenStyle \endlink -->

\todo see how todo works

## Building

### Build on linux

Standard Makefiles:
~~~
mkdir build ; cd build
cmake ..
make -j8
~~~


Ninja build witch clang, build all+doc and install it to dist folder:
~~~
mkdir build ; cd build
cmake -GNinja -DCMAKE_CXX_COMPILER="clang++-3.8" ..
ninja all doc install
~~~



### Build on windows using MSYS2 + ninja

On windows prefer Ninja since it is **MUCH** faster than make.

With gcc:
~~~
mkdir build ; cd build
cmake -GNinja ..
ninja install
~~~

With clang++, build executable, doxygen documentation and install:
~~~
mkdir build ; cd build
cmake -GNinja -DCMAKE_CXX_COMPILER="clang++" ..
ninja all doc install
~~~

Notes for sublime text: You want to have *c:/runLinux32.bat* with this:
~~~
set MSYSTEM=MINGW32
C:\msys64\usr\bin\bash.exe --login -c "cd - ; %*"
~~~
    * and edit makebuildrun.sh and ninjabuildrun.sh to execute final executable



### CMAKE variables

* -DCMAKE_INSTALL_PREFIX= - location for instalation
* -DVERSION_HOST= - build machine name
* -DCMAKE_BUILD_TYPE=RelWithDebInfo - for build type





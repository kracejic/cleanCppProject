# cleanCppProject

This is a empty frame for project in C++. It should help to start a new project without caring much about project/build environment setup.


## Important pages

* [Design document](./md_design.html)
* [List of todos](./todo.html)
* [Basic directory structure](./md_directoryStructure.html)
<!-- * \link todo List of todos DoxygenStyle \endlink -->

\todo see how todo works

## How to convert this to your new project

~~~
git clone https://github.com/kracejic/cleanCppProject.git yourNewProject
cd yourNewProject
rm -rf .git
git init
git add .
git commit -m "first commit"
~~~

Do not forget to change name of *example* binary in `source/CMakeLists.txt` and `test/CMakeLists.txt`. 

## Building instructions

### Prerequisites

* CMake 3.2 and newer
* Compiler with support for C++14
* git - for downloading external resources
* Doxygen for docs (*Graphviz for more graphs in docs, PlantUML for more UML diagrams*, PlantUML needs java)
* clang-tools for static analysis and formating
* cpp check for another static analysis

Arch Linux: `sudo pacman -S cmake g++ graphviz git clang clang-tools-extra cppcheck`, download plantuml.jar and have it somewhere where *PATH* points to
Ubuntu: `sudo apt-get install cmake g++ graphviz plantuml git clang clang-tools-extra`

#### Prerequisites on Windows

Two ways, which were tested:

* msys2 based
    * Minimal: `pacman -S cmake g++ git`
    * Additional software `pacman -S clang mingw-w64-x86_64-clang-tools-extra mingw-w64-x86_64-clang-analyzer doxygen`
    * For graphs in documentation install Graphviz (to `c:\Program Files\Graphviz`, so scripts can find it) and add its `bin` subdirectory to *PATH*, install java (have it on *PATH*), download PlantUML jar file and have it on *PATH*. 

* Microsoft Visual Studio
    * Install cmake
    * Install git
    * For additional features install clang with tools, doxygen, graphviz, plantuml, java and add them to the PATH (*not tested*)



### Build on Linux

Standard Makefiles:
~~~
mkdir build ; cd build
cmake ..
make -j8
~~~


Ninja build witch clang, build all+doc and install it to dist folder:
~~~
mkdir build ; cd build
cmake -GNinja -DCMAKE_CXX_COMPILER="clang++" ..
ninja all doc && ninja install
~~~


### Build on windows

#### Build on windows using MSYS2 + ninja

On windows you should prefer Ninja since it is much faster than make (but has no color in shell).

With gcc:
~~~
mkdir build ; cd build
cmake -GNinja ..
ninja install
~~~


#### Build on Windows using Microsoft Visual Studio 14

First you may wan to change project name in main `CMakeLists.txt`. Just go to the folder with the project and create new directory and create project files with this:

~~~
mkdir buildmsvc
cd buildmsvc
cmake -G "Visual Studio 14 2015" ..
~~~

and you can now open a `.sln` file with Visual Studio. You need to right click on executable target and *Set as StartUp project*. To really see the console window you want to do *Start without debugging*, since when run in debug mode only, console widow is closed too fast.

### Targets

* Build
    * *all* (the default if no target is provided)
    * *clean*
    * *install* - install binaries into *CMAKE_INSTALL_PREFIX*
    * *example* - build example binary
    * *example-run* - build, install and run example binary (for your convenience)
    * *run* - alias for example-run (in order to keep it short)
* Testing
    * *check* - run whole test suite (see test/CMakeLists.txt)
    * *checkVerbose* - run whole test suite (see test/CMakeLists.txt), but more verbose
    * *unit* - build and run unit tests only (see test/CMakeLists.txt)
    * *unitall* - same as previous, only prints even successful unit tests results
* Miscellaneous
    * *doc* - build documentation (if doxygen is available)
    * *format* - run clang-format on all source files (.clang-format in root directory of a project is used)
* Static analysis
    * *tidy* - run clang static analysis on all sources
    * *cppcheck* - call cppcheck on all files (another static analysis)
* External
    * *external-update-all* - update all external sources/projects
    * *external-update-Catch* - update Catch (Unit test library)


### CMAKE variables

* `-DCMAKE_INSTALL_PREFIX`= - location for installation
* `-DVERSION_HOST`= - build machine name, see Version::getVersionLong
* `-DCMAKE_BUILD_TYPE`=RelWithDebInfo - for build type




# License

> Copyright (c) 2016 Kracejic
>
> Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

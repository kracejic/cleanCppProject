# EmptyCppProject

This is a empty frame for project in C++. It should help to start a new project without caring much about project/build enviroment setup.


## Important pages

* [Design document](./md_design.html)
* [List of todos](./todo.html)
* [Basic directory structure](./md_directoryStructure.html)
<!-- * \link todo List of todos DoxygenStyle \endlink -->

\todo see how todo works

## Building instructions

### Prerequisites

* CMake 3.2 and newer
* Doxygen for docs (*Graphviz for more graphs in docs, PlantUML for more UML diagrams*)


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
cmake -GNinja -DCMAKE_CXX_COMPILER="clang++" ..
ninja all doc && ninja install
~~~


### Build on windows

#### Build on windows using MSYS2 + ninja

On windows prefer Ninja since it is **MUCH** faster than make.

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

and you can now open a `.sln` file with Visual Studio. You need to RMB click on executable target and *Set as StartUp project*. To really see the console window you want to do *Start without debugging*, since when run in debug mode only, console widow is closed too fast.

### CMAKE variables

* `-DCMAKE_INSTALL_PREFIX`= - location for instalation
* `-DVERSION_HOST`= - build machine name
* `-DCMAKE_BUILD_TYPE`=RelWithDebInfo - for build type




# License

> Copyright (c) 2016 Kracejic
> 
> Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
> 
> The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
> 
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

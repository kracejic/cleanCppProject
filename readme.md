# EmptyCppProject

This is a frame for project in C++.
These tools are in mind:

    * Sublime text
        * build system defined for *make* or *ninja*
        * cppinabox support
    * CMake based build
    * YCMD



## Building


### Build on linux

```
mkdir build ; cd build
cmake ..
make -j8
```

```
mkdir build ; cd build
cmake -GNinja -DCMAKE_CXX_COMPILER="clang++-3.6" ..
ninja
```

* Notes for sublime text: You want to have *c:/runLinux32.bat* with this:
```
set MSYSTEM=MINGW32
C:\msys64\usr\bin\bash.exe --login -c "cd - ; %*"
```
    * and edit makebuildrun.sh and ninjabuildrun.sh to execute final executable



### Build on windows using MSYS2 + ninja

* With gcc:

```
mkdir build ; cd build
cmake -G "Ninja" ..
ninja install
```

* With clang++

```
mkdir build ; cd build
cmake -G "Ninja" -DCMAKE_CXX_COMPILER="clang++" ..
ninja install
```

### CMAKE variables

* -DCMAKE_INSTALL_PREFIX= - location for instalation
* -DVERSION_HOST= - build machine name






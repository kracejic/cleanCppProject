# EmptyCppProject

This is a frame for project in C++.
These tools are in mind:
    
    * Sublime text
    * CMake based build
    * YCMD



## Building


### Build on linux

```
mkdir build ; cd build
cmake -DCMAKE_CXX_COMPILER="g++-5" ..
make -j8
```


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






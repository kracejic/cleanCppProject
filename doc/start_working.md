
# How to start working

## Build System

Big help will be the official CMake docs at [cmake.org/cmake/help/latest/](https://cmake.org/cmake/help/latest/). You can consult them for function description.

Other than that CMake is simple language, which can get things done more. 

If you found yourself in a situation when you do not know the status if variables, use `cmake .. -LH` or `cmake .. -LAH` for actual variables values.

Start reading `project/CMakeLists.txt` and continue to `project/source/CMakeLists.txt`. If you are interested in testing (you should be), read also `project/test/CMakeLists.txt` and see how testing is done.

## Source code

Function main is in the `source/main.cpp`. 

If you want to add an file, add it to `source/CMakeLists.txt` into *SRCS* variable, then it will be compiled to example target.


## Tests

### Unit tests

Checkout [catch tutorial](https://github.com/philsquared/Catch/blob/master/docs/tutorial.md). 

When you want to add new unit tests, add source file to `test/CMakeLists.txt` to *SRCTEST* variable. You can use following snippet to add tests to a file:

~~~
#ifdef UNIT_TESTS
#include "catch.hpp"

TEST_CASE("SomeClass set and get")
{
    //setup
    ...

    REQUIRE(something.get() != 2);
}

#endif
~~~

This way you can have tests part of an implementation file and yet they will not be part of a regular build because *UNIT_TESTS* define is defined only for producing unit test binary.

### Integration tests

Start with `test/CMakeLists.txt`.


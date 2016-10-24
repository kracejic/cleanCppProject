#include "SomeClass.h"


//------------------------------------------------------------------------------
SomeClass::SomeClass()
{
}
//------------------------------------------------------------------------------
SomeClass::~SomeClass()
{
}
//------------------------------------------------------------------------------
void SomeClass::set(int x)
{
    this->mVal = x;
}
//------------------------------------------------------------------------------
int SomeClass::get()
{
    return this->mVal;
}
//------------------------------------------------------------------------------


#ifdef UNIT_TESTS
#include "catch.hpp"

TEST_CASE("SomeClass set and get")
{
    SomeClass some;
    some.set(5);
    REQUIRE(some.get() == 5);
    REQUIRE(some.get() != 2);
}

#endif

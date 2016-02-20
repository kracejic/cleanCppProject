#pragma once
#include <vector>
#include <string>



/**
 * Empty BaseClass, just to show how it looks in doxygen.
 */
class BaseClass
{
public:
    BaseClass(){};
    ~BaseClass(){};

};

/**
 * Empty data class, just to show how it looks in doxygen.
 */
class Data
{
public:
    Data(){};
    ~Data(){};

};

/**
 * SomeClass description. This is a test class ment to show
 * how to create, build, use and document classes from other files.
 *
 * \warning beware, this is how warning looks like.
 */
class SomeClass : public BaseClass
{
    int mVal {0};  ///< Stores the value
    std::vector<Data> mData;
    std::vector<std::string> mStrings;
    Data* mParent;
public:
    SomeClass(); ///< Creates empty SomeClass
    ~SomeClass();


    /**
     * Sets the value
     * @param x input value
     */
    void set(int x);

    /**
     * get the value
     * @return current value
     */
    int get();

};



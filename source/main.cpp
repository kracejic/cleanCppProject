#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "SomeClass.h"
#include "version.h"


using namespace std;

void printHelp()
{
    cout << "Help for cleanCppApplication " << endl;
    cout << "Version: " << Version::getVersionLong() << endl;
    cout << "Author:  " << endl;
    cout << "URL:     " << endl;
    /// @todo Do stuff in here also
}

int main(int argc, char const *argv[])
{
    // Print help if no arguments are given
    if (argc == 1)
        printHelp();

    // process parameters
    int argIt;
    for (argIt = 1; argIt < argc; ++argIt)
    {
        string tmp = argv[argIt];

        if (tmp == "--help" || tmp == "-h")
            printHelp();
        else if (tmp == "--version")
            cout << "v" << Version::getVersionShort() << endl;
        else
            break;
    }
    // process rest of the free arguments. EG. file list, word list
    for (; argIt < argc; ++argIt)
        cout << argv[argIt] << endl;

    /// @todo Do more stuff.
    {
        BaseClass c;
        if (argc == 1)
            c.freePtr();
        /// @todo fix another leak
    }

    SomeClass o;
    o.set(5);
    cout << o.get() << endl;

    // possible memory leak here, run with `make analyze`
    int *a = new int(5);
    cout << *a << endl;

    if (argc == 3)
        return 1;


    delete a;
    cout << *a << endl;


    return 0;
}

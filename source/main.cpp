#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>

#include "version.h"

using namespace std;

void printHelp()
{
    cout << "Help for cleanCppApplication " << endl;
    cout << "Version: " << Version::getVersionLong() << endl;
    cout << "Author:  " << endl;
    cout << "URL:     " << endl;
}

int main(int argc, char const* argv[])
{
    // Print help if no arguments are given
    if(argc == 1)
        printHelp();

    // process parameters
    int argIt;
    for(argIt = 1; argIt < argc; ++argIt)
    {
        string tmp = argv[argIt];

        if(tmp == "--help" || tmp == "-h")
            printHelp();
        else if(tmp == "--version")
            cout << "v" << Version::getVersionShort() << endl;
        else
            break;
    }
    // process rest of the free arguments. EG. file list, word list
    for(; argIt < argc; ++argIt)
        cout << argv[argIt] << endl;

    return 0;
}

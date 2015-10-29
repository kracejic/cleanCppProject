#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>

#include "version.h"

//g++ main.cpp  -std=c++11 -o a.exe && ./a.exe

using namespace std;

int main(int argc, char const *argv[])
{
    cout<<"hello world!"<<endl;
    cout<<"VersionShort is "<<Version::getVersionShort()<<endl;
    cout<<"VersionLong is  "<<Version::getVersionLong()<<endl;
    cout<<"VersionNumber is  "<<Version::getVersionNumber()<<endl;
    return 0;
}

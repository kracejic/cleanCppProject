#pragma once
#include <string>


namespace Version
{
std::string getBuildTime();
int getMajor();
int getMinor();
int getPatch();
long long getVersionNumber();
std::string getVersionShort();
std::string getVersionLong();
}

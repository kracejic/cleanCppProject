#pragma once
#include <string>


namespace Version
{
/// Get time of build in format like: Feb 20 2016 14:38:27
std::string getBuildTime();

int getMajor(); ///< Returns Major part of version
int getMinor(); ///< Returns Minor part of version
int getPatch(); ///< Return Patch part of version

/**
 * Returns version in one big number with format:
 *
 * * MMMMmmmmpppp (M-Major, m-minor, p-patch)
 *
 * So 1.2.3 will be 100020003 (leading zeroes are not displayed)
 * @return long integer with version
 */
long long getVersionNumber();

/**
 * Returns version string with version in format:
 * * vMajor.Minor.Patch VersionType
 * * v1.2.3 beta
 */
std::string getVersionShort();

/**
 * Returns Version + Date + Build machine
 *
 * Will produce result similar to:
 *  1.2.6 beta / Feb 20 2016 14:42:41 / buildMachine
 */
std::string getVersionLong();

/**
 * Returns name of the build machine.
 *
 * Can be changed with cmake .. -DVERSION_HOST=newName
 */
std::string getBuildMachine();
}

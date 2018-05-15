#pragma once
#include <string>


namespace Version
{

struct Version
{
    /// Creates empty Version object
    Version();

    /**
     * Converts number to version object.
     * @param version - number in format MMMMmmmmpppp (M-Major, m-minor,
     * p-patch)
     *
     * @return Version object
     */
    Version(long long version);

    int major{0};
    int minor{0};
    int patch{0};

    /// Type of build
    std::string type{""};

    /// Get time of build in format like: Feb 20 2016 14:38:27
    std::string datetime{""};

    /// Machine where it was built
    std::string machine{""};

    /**
     * Returns version in one big number with format:
     *
     * * MMMMmmmmpppp (M-Major, m-minor, p-patch)
     *
     * So 1.2.3 will be 100020003 (leading zeroes are not displayed)
     * @return long integer with version
     */
    long long asNumber() const;

    /**
     * Returns version string with version in format:
     * * Major.Minor.Patch VersionType
     * * 1.2.3 beta
     */
    std::string asShortStr() const;

    /**
     * Returns Version + Date + Build machine
     *
     * Will produce result similar to:
     *  1.2.6 beta / Feb 20 2016 14:42:41 / buildMachine
     */
    std::string asLongStr() const;

    // Operators
    bool operator<(const Version& other);
    bool operator>(const Version& other);
    bool operator<=(const Version& other);
    bool operator>=(const Version& other);
    bool operator==(const Version& other);
    bool operator!=(const Version& other);
};

/// Get current version
const Version& current();


} // namespace Version

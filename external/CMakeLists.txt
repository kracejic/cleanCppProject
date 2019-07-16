include(ExternalProject)
find_package(Git REQUIRED)
# find_package(Hg REQUIRED)
include(cleanCppExtensions)

#------------------------------------------------------------------------------
# Convenience update all, dependencies are added in ExternalHeaderOnly_Add
add_custom_target(update COMMENT "Updated all external projects")

#------------------------------------------------------------------------------
# Catch - Unit test header only library

# For details about ExternalHeaderOnly_Add see cmake/cleanCppExtensions.cmake

# target_link_libraries (exampleApp PRIVATE catch)
# #include <catch.hpp>
ExternalHeaderOnly_Add(Catch
    "https://github.com/catchorg/Catch2.git" "master" "single_include/catch2")

#------------------------------------------------------------------------------
# Examples of other external projects
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# target_link_libraries (exampleApp PRIVATE json)
# #include <nlohmann/json.hpp>
# ExternalHeaderOnly_Add(json
#     "https://github.com/nlohmann/json.git" "master" "single_include")

#------------------------------------------------------------------------------
# target_link_libraries (exampleApp PRIVATE spdlog)
# #include <spdlog/spdlog.h>
# Bundled fmt can be used: #include <spdlog/fmt/fmt.h>
# spdlog::error("Some error message with arg: {}", 1);
# ExternalHeaderOnly_Add(spdlog
#     "https://github.com/gabime/spdlog.git" "v1.x" "include")

#------------------------------------------------------------------------------
# target_link_libraries (exampleApp PRIVATE doctest)
# #include <doctest.h>
# ExternalHeaderOnly_Add("DocTest"
#     "https://github.com/onqtam/doctest.git" "master" "src/DocTest")

#------------------------------------------------------------------------------
# target_link_libraries (exampleApp PRIVATE fmt)
# #include <fmt/format.h>
# Use with: `fmt::print("Hello {} - {}!\n", "world", 3.56f);`

# ExternalDownloadNowGit(fmt "https://github.com/fmtlib/fmt.git" "master")
# add_library(fmt STATIC ${fmt_SOURCE_DIR}/src/format.cc)
# target_include_directories(fmt SYSTEM PUBLIC ${fmt_SOURCE_DIR}/include)
# # target_compile_definitions(spdlog INTERFACE -DSPDLOG_FMT_EXTERNAL) #if using SPDLOG


#------------------------------------------------------------------------------
# cpr - HTTP(S) requests library with nice interface

# target_link_libraries (exampleApp PRIVATE fmt)
# #include <cpr/cpr.h>
# auto r = cpr::Get(cpr::Url{"https://ohnheiser.cz"});
# cout<<r.text<<endl;

# find_package(CURL REQUIRED)
# ExternalDownloadNowGit(cpr https://github.com/finkandreas/cpr.git master)
# option(BUILD_CPR_TESTS "" OFF) #disable tests
# option(USE_SYSTEM_CURL "" ON ) #use system curl
# add_subdirectory(${cpr_SOURCE_DIR} EXCLUDE_FROM_ALL)
# # Make headers come as SYSTEM, to get rid of all warning on included headers
# target_include_directories(cpr SYSTEM PUBLIC ${CPR_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS})



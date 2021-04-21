# 特殊包管理器
include(cmake/CPM.cmake)

# CPMAddPackage("gh:catchorg/Catch2@2.5.0")

# set (CMAKE_LIBRARY_PATH ~/.cmake_modules/vcpkg/installed/x64-osx/debug/lib/manual-link)

# CPMAddPackage(
#   NAME googletest
#   GITHUB_REPOSITORY google/googletest
#   GIT_TAG release-1.8.1
#   VERSION 1.8.1
#   OPTIONS
#       "INSTALL_GTEST OFF"
#       "gtest_force_shared_crt ON"
# )

# set(GTEST_LIBRARY GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

# 外部库依赖
find_package(GTest MODULE REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
# find_package(GTest CONFIG REQUIRED)
# target_link_libraries(main PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)

# 前置： brew install pkg-config , vcpkg install openssl
find_package(OpenSSL MODULE REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR}) # fixme: 猜测他是关联project的。。。。！！！！！！！！！！！！！！！！！！1
# FIXME: 头文件目录有了，但是库搜索目录，却不是这个：OPENSSL_LIBRARY
# find_package(OpenSSL REQUIRED)
# target_link_libraries(main PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# FATAL_ERROR CMake Error, stop processing and generation.
# SEND_ERROR CMake Error, continue processing, but skip generation.
# WARNING CMake Warning, continue processing.
# AUTHOR_WARNING CMake Warning (dev), continue processing.
# DEPRECATION CMake Deprecation Error or Warning if variable CMAKE_ERROR_DEPRECATED or CMAKE_WARN_DEPRECATED is enabled, respectively, else no message.
# (none) or NOTICE Important message printed to stderr to attract user's attention.
# STATUS The main interesting messages that project users might be interested in. Ideally these should be concise, no more than a single line, but still informative.
# VERBOSE Detailed informational messages intended for project users. These messages should provide additional details that won't be of interest in most cases, but which may be useful to those building the project when they want deeper insight into what's happening.
# DEBUG Detailed informational messages intended for developers working on the project itself as opposed to users who just want to build it. These messages will not typically be of interest to other users building the project and will often be closely related to internal implementation details.
# TRACE
message(STATUS "###################################")
message(STATUS "# 外部库依赖")
message(STATUS "###################################")

message(STATUS 头文件搜索路径=${CMAKE_INCLUDE_PATH}) # 不使用 FIND_PATH，CMAKE_INCLUDE_PATH 变量的设置是没有作用的
message(STATUS 库搜索路径=${CMAKE_LIBRARY_PATH})
message(STATUS 包搜索路径=${CMAKE_MODULE_PATH})

message(STATUS gtest_found=${GTEST_FOUND}) 
message(STATUS gtest_include_dir=${GTEST_INCLUDE_DIR}) 
message(STATUS gtest_include_dir=${GTEST_INCLUDE_DIRS})
message(STATUS gtest_include_dir=${GTEST_INCLUDES})
message(STATUS gtest_library=${GTEST_MAIN_LIBRARY})
message(STATUS gtest_library=${GTEST_LIBRARY})
message(STATUS gtest_library=${GTEST_LIBRARIES})

set (GTEST_LIBRARY ${GTEST_LIBRARIES})

# ~/.cmake_modules/vcpkg/packages/openssl_x64-osx/include/openssl/
message(STATUS openssl_found=${OPENSSL_FOUND})
message(STATUS openssl_include_dir=${OPENSSL_INCLUDE_DIR}) # openssl_include_dir=/Users/seven/.cmake_modules/vcpkg/installed/x64-osx/include
message(STATUS openssl_library=${OPENSSL_LIBRARY})
# target_link_libraries(${LIB_NAME} PUBLIC OpenSSL::SSL OpenSSL::Crypto)

message(STATUS "###################################")

find_package(Threads)


# 性能测试
# CPMAddPackage(
#   NAME benchmark
#   GITHUB_REPOSITORY google/benchmark
#   VERSION 1.5.2
#   OPTIONS "BENCHMARK_ENABLE_TESTING Off"
# )

if(benchmark_ADDED)
  # enable c++11 to avoid compilation errors
  set_target_properties(benchmark PROPERTIES CXX_STANDARD 14)
endif()
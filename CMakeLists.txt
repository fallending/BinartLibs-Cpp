cmake_minimum_required(VERSION 3.17.0)

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

#################
# 选项卡
option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." ON)

# 判断cmake的运行平台
message(STATUS "###################################")
message(STATUS "# 当前平台")
message(STATUS "###################################")

if (WIN32)
  message(STATUS "Now is windows")
elseif (APPLE)
  message(STATUS "Now is Apple systems.")

  set (CMAKE_C_COMPILER /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc)
  set (CMAKE_CXX_COMPILER /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++)

  set (CMAKE_CXX_FLAGS -std=c++14)
elseif (UNIX)
  message(STATUS "Now is UNIX-like OS's.")
endif ()

message(STATUS "CMAKE_CXX_COMPILER_ID             = ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "###################################")

# 编译配置
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS ON)
set (CMAKE_BUILD_TYPE "debug")
# set (CMAKE_CXX_FLAGS “${CMAKE_CXX_FLAGS} -g”)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # 导出 compiliation database，给 clang-tidy 用
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

# we use this to get code coverage
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

if (CMAKE_GENERATOR STREQUAL "Ninja")
  # Turn on colored output. https://github.com/ninja-build/ninja/wiki/FAQ
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always -Wno-unused-parameter -Wno-deprecated-declarations -Wno-format")
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdiagnostics-color=always -Wno-unused-parameter -Wno-deprecated-declarations -Wno-format")
endif ()

# 工程配置
set (MTVER 0.1.0)
set (MTPROJ mt-ccs)

project(${MTPROJ} VERSION ${MTVER} LANGUAGES C CXX)

# 全局环境变量
set (CMAKE_INSTALL_BINDIR bin)
set (CMAKE_INSTALL_LIBDIR lib)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

message(STATUS "###################################")
message(STATUS "# 全局环境变量")
message(STATUS "###################################")
message("CMAKE_BINARY_DIR = \'${CMAKE_BINARY_DIR}\'")
message("CMAKE_INSTALL_LIBDIR = \'${CMAKE_INSTALL_LIBDIR}\'")
message("CMAKE_INSTALL_BINDIR = \'${CMAKE_INSTALL_BINDIR}\'")
message("PROJECT_SOURCE_DIR = \'${PROJECT_SOURCE_DIR}\'")
message("CMAKE_ARCHIVE_OUTPUT_DIRECTORY = \'${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}\'")
message("CMAKE_LIBRARY_OUTPUT_DIRECTORY = \'${CMAKE_LIBRARY_OUTPUT_DIRECTORY}\'")
message("CMAKE_RUNTIME_OUTPUT_DIRECTORY = \'${CMAKE_RUNTIME_OUTPUT_DIRECTORY}\'")
message("CMAKE_HEADERS_OUTPUT_DIRECTORY = \'${CMAKE_HEADERS_OUTPUT_DIRECTORY}\'")
message(STATUS "###################################")

# 自定义环境变量
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/${MTPROJ}-${MTVER})

set(MT_LIBRARY_INCLUDE_DIRECTORY ${PROJECT_SOURCE_DIR}/src) # 单元测试依赖该文件夹
set(MT_EXPORTED_INCLUDE_DIRECTORY ${PROJECT_SOURCE_DIR}/include) # 相互依赖的本地模块，依赖这个

message(STATUS "###################################")
message(STATUS "# 自定义环境变量")
message(STATUS "###################################")
message(STATUS "###################################")

# place binaries and libraries according to GNU standards
include(GNUInstallDirs)
include(cmake/CPM.cmake)
# CPMAddPackage("gh:catchorg/Catch2@2.5.0")

# set (CMAKE_LIBRARY_PATH /Users/lilithgames/.cmake_modules/vcpkg/installed/x64-osx/debug/lib/manual-link)

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

# 准备全局配置头文件
# configure_file(tutorialConfig.h.in tutorialConfig.h)

# 配置开发库目录
add_subdirectory(src)
include_directories(src)

# 启用单元测试
enable_testing()
add_subdirectory(tests)

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
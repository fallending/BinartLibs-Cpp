cmake_minimum_required(VERSION 3.17.0)

set (MTVER 0.1.0)
set (MTPROJ mt-ccs)

project(${MTPROJ} VERSION ${MTVER} LANGUAGES C CXX)

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

# 判断cmake的运行平台
message(STATUS "###################################")
message(STATUS "# 当前平台")
message(STATUS "###################################")

message(STATUS "operation system is ${CMAKE_SYSTEM}")
message(STATUS "operation system is ${CMAKE_SYSTEM_NAME}")

if (WIN32)
  message(STATUS "Now is windows")
elseif (APPLE)
  message(STATUS "Now is Apple systens.")
elseif (UNIX)
  message(STATUS "Now is UNIX-like OS's.")
endif ()
 
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
  message(STATUS "current platform: Linux ")
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
  message(STATUS "current platform: Windows")
elseif (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
  message(STATUS "current platform: FreeBSD")
else ()
  message(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
endif ()
 
message(STATUS "###################################")

# 编译配置
set (CMAKE_CXX_STANDARD 14)

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
set(MT_HDR_OUTPUT_DIR ${CMAKE_BINARY_DIR}/${MTPROJ}-${MTVER}/inclue)
set(MT_LIB_OUTPUT_DIR ${CMAKE_BINARY_DIR}/${MTPROJ}-${MTVER}/lib)
set(MT_EXE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/${MTPROJ}-${MTVER}/bin)
set(MT_SRC_DIR ${PROJECT_SOURCE_DIR}/src)

message(STATUS "###################################")
message(STATUS "# 自定义环境变量")
message(STATUS "###################################")
message("MT_HDR_OUTPUT_DIR = \'${MT_HDR_OUTPUT_DIR}\'")
message("MT_LIB_OUTPUT_DIR = \'${MT_LIB_OUTPUT_DIR}\'")
message("MT_EXE_OUTPUT_DIR = \'${MT_EXE_OUTPUT_DIR}\'")
message("MT_SRC_DIR = \'${MT_SRC_DIR}\'")
message(STATUS "###################################")

# we use this to get code coverage
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

# place binaries and libraries according to GNU standards
include(GNUInstallDirs)

# 内部依赖

# set(ROOT /blah/blah/root)

# include_directories(${ROOT})

# 外部库依赖
find_package(GTest MODULE REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

# 前置： brew install pkg-config
find_package(OpenSSL MODULE REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

message(STATUS "###################################")
message(STATUS "# 外部库依赖")
message(STATUS "###################################")
message(gtest_include_dir=${GTEST_INCLUDE_DIR}) 
message(gtest_library=${GTEST_LIBRARY})
message(STATUS "###################################")

find_package(Threads)

# 准备全局配置头文件
# configure_file(tutorialConfig.h.in tutorialConfig.h)

# 配置需要引入的头文件基础目录
# include_directories(${MT_SRC_DIR}/include)

# 配置开发库目录
add_subdirectory(${MT_SRC_DIR})

# include(cmake/googletest.cmake)
# fetch_googletest(
#   ${PROJECT_SOURCE_DIR}/cmake
#   ${PROJECT_BINARY_DIR}/googletest
# )

# 启用单元测试
enable_testing()

add_subdirectory(test)


# 其他库示例：
# enable_testing()
# find_package(GTest MODULE REQUIRED)#查找GTest
# find_package(Threads)#查找Threads

# #一些调试信息
# message(gtest_include_dir=${GTEST_INCLUDE_DIR})
# message(gtest_library=${GTEST_LIBRARY})
# message(threads=${CMAKE_THREAD_LIBS_INIT})

# #包含GTest的库文件
# include_directories(${GTEST_INCLUDE_DIR})

# #包含src的项目文件
# include_directories(../src)

# add_executable(gtest_simple_test main.cpp okkk-test.cpp)

# #链接gtest_simple_lib,这个是src项目生成的静态库
# #链接${GTEST_LIBRARY},这个是gtest的库文件
# #链接${CMAKE_THREAD_LIBS_INIT},即-lpthread
# target_link_libraries(gtest_simple_test PUBLIC gtest_simple_lib ${GTEST_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})

# add_test(NAME gtest_simple_test COMMAND gtest_simple_test)
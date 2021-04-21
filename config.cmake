
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

  # 警告：下面几句同时生效，则在某些机器上出现vcpkg作用下find_package异常
  # --toolchain xcode --config Debug --install
  # xcode-select -p 
  # /Applications/Xcode.app/Contents/Developer
  # set (CMAKE_C_COMPILER /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc)
  # set (CMAKE_CXX_COMPILER /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++)

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

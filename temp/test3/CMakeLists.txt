project(hello_1)

file(GLOB SOURCE_1 "${CMAKE_SOURCE_DIR}/main.cpp") # CMake: 源文件在哪里
file(GLOB SOURCE_2 "${CMAKE_SOURCE_DIR}/hello/*.cpp")# 程序链接到hello.cpp里面的SayHello

include_directories("${CMAKE_SOURCE_DIR}/include/") # CMake: 头文件在哪里？

add_executable(hello_1 ${SOURCE_1} ${SOURCE_2})
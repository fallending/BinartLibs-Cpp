# 代码和CMake编译目录分离

project(hello_3)

set(PROJECT_ROOT_PATH "${CMAKE_SOURCE_DIR}/../")          # 工程的根目录
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/")    # 可执行生成后存放的目录(CMAKE_SOURCE_DIR是cmake目录)
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/lib/")       # 静态库生成后存放的目录

include_directories("${PROJECT_ROOT_PATH}/include/")

link_directories("${CMAKE_SOURCE_DIR}/lib/")              # CMake: 静态库在哪里？

add_subdirectory(src)                                     # 多目录管理
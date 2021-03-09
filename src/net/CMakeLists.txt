# 有源文件的库: 动态库+静态库

cmake_minimum_required(VERSION 3.6)
project (net)

# ######### 依赖关系

include_directories(../tcp) # 头文件搜索路径
# add_subdirectory(../tcp)  # 模块依赖关系
# 添加非标准的共享库搜索路径
# LINK_DIRECTORIES(../../../bin/lib)

# 这里的相对路径并不是相对于源码路径(CMakeLists.txt路径)，而是相对于执行命令的路径（build目录），向上三层目录结构。
link_directories(../tcp/outputs/)

set(CMAKE_CXX_STANDARD 14)
set(LIBNET_SRC netdetect.cpp)

add_library(net_d SHARED ${LIBNET_SRC})
add_library(net_s STATIC ${LIBNET_SRC})

target_link_libraries(net_d libtcp.dylib)
target_link_libraries(net_s libtcp.a)

set_target_properties(net_d PROPERTIES OUTPUT_NAME "net")
set_target_properties(net_s PROPERTIES OUTPUT_NAME "net")

set_target_properties(net_d PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(net_s PROPERTIES CLEAN_DIRECT_OUTPUT 1)

install(TARGETS net_d net_s 
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)  # 静态库用archive关键字
install(FILES netdetect.hpp DESTINATION inc/http)

## 小知识
# 不能指望它会直接为编译器命令添加参数-I<CMAKE_INCLUDE_PATH>。以此为例同样，因为这些变量直接为FIND_指令所使用，所以所有使用FIND_指令的cmake模块都会受益。
# FIND_PATH -> 依赖 -> CMAKE_INCLUDE_PATH
# FIND_LIBRARY -> 依赖 -> CMAKE_LIBRARY_PATH

# 示例
# FIND_PATH(myHeader hello.h)
# IF(myHeader)
# INCLUDE_DIRECTORIES(${myHeader})
# ENDIF(myHeader)
 

# ADD_EXECUTABLE(main main.c)
# FIND_PATH(myHeader hello.h)
# IF(myHeader)
# INCLUDE_DIRECTORIES(${myHeader})
# ENDIF(myHeader)
# TARGET_LINK_LIBRARIES(main libhello.so)
# LINK_DIRECTORIES(/home/wideking/cmakeDemo/libhello/bulid)
# ADD_EXECUTABLE(main main.c)


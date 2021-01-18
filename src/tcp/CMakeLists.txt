# 有源文件的库: 动态库+静态库，且有库之间的依赖

cmake_minimum_required(VERSION 3.6)
project (tcp)

set(CMAKE_CXX_STANDARD 14)
set(SRC_FILES tcp.cpp tcpcheck.cpp tcpquery.cpp)
set(INC_FILES tcp.hpp tcpcheck.hpp tcpquery.hpp)

add_library(tcp_shared SHARED ${SRC_FILES})
add_library(tcp_static STATIC ${SRC_FILES})

set_target_properties(tcp_shared PROPERTIES OUTPUT_NAME "tcp")
set_target_properties(tcp_static PROPERTIES OUTPUT_NAME "tcp")

set_target_properties(tcp_shared PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(tcp_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

install(TARGETS tcp_shared tcp_static 
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
install(FILES ${INC_FILES} DESTINATION inc/tcp)
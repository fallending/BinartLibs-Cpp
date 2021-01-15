# 有源文件的库: 动态库+静态库

cmake_minimum_required(VERSION 3.6)
project (http)


set(CMAKE_CXX_STANDARD 14)

# target_sources(
#   http
#   PRIVATE
#     http.cpp
#   PUBLIC
#     ${CMAKE_CURRENT_LIST_DIR}/http.hpp
#   )

# target_include_directories(
#   http
#   PUBLIC
#     ${CMAKE_CURRENT_LIST_DIR}
#   )

# set_target_properties(http PROPERTIES LINKER_LANGUAGE CXX)
# set_target_properties(http PROPERTIES VERSION 1.0 SOVERSION 1) # VERSION指代动态库版本，SOVERSION指代API版本

set(LIBHTTP_SRC http.cpp)

add_library(http_d SHARED ${LIBHTTP_SRC})
add_library(http_s STATIC ${LIBHTTP_SRC})

set_target_properties(http_d PROPERTIES OUTPUT_NAME "http")
set_target_properties(http_s PROPERTIES OUTPUT_NAME "http")

set_target_properties(http_d PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(http_s PROPERTIES CLEAN_DIRECT_OUTPUT 1)

install(TARGETS http_d http_s ARCHIVE DESTINATION lib)  # 静态库用archive关键字
install(FILES http.hpp DESTINATION inc/http)
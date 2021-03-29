# 有源文件的库: 动态库+静态库
cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 14)

add_library(http-objs
  OBJECT
    http.hpp
    http.cpp
  )

add_library(http-shared # shared library
  SHARED
    $<TARGET_OBJECTS:http-objs>
  )

set_target_properties(http-shared
  PROPERTIES
    OUTPUT_NAME "http"
    CLEAN_DIRECT_OUTPUT 1
)

add_library(http-static # static library
  STATIC
    $<TARGET_OBJECTS:http-objs>
  )

set_target_properties(http-static
  PROPERTIES
    OUTPUT_NAME "http"
    CLEAN_DIRECT_OUTPUT 1
  )

# install(TARGETS http-shared http-static 
#   LIBRARY DESTINATION http
#   ARCHIVE DESTINATION http)  # 静态库用archive关键字
# install(FILES http.hpp DESTINATION http)


  ############################### @seven 以下需要消化
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
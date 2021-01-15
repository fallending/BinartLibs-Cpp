# 没有源文件的库
project (bitbuffer)

add_library(bitbuffer "")

set_target_properties(bitbuffer PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(bitbuffer PROPERTIES VERSION 1.0 SOVERSION 1)

target_sources(
    bitbuffer
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/bitbuffer.hpp
        ${CMAKE_CURRENT_LIST_DIR}/bitutil.hpp
    )

target_include_directories(
    bitbuffer
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )
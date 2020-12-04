add_library(BitBuffer "")

target_sources(
    BitBuffer
    PRIVATE
        BitBuffer.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/BitBuffer.h
        ${CMAKE_CURRENT_LIST_DIR}/BitUtil.h
    )

target_include_directories(
    BitBuffer
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
    )
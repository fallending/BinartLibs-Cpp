
# 引入库的public headers目录
include_directories(${MT_SRC_DIR}/bitbuffer)

# 归纳测试源文件
aux_source_directory(. TEST_FILES)

# test_lib_bitbuffer 单元测试 可执行文件
add_executable(
  test_lib_bitbuffer
  ${TEST_FILES}
)

# test_lib_bitbuffer 源文件依赖的头文件目录
# target_include_directories(
#   test_lib_bitbuffer
#   PUBLIC
#   "${CMAKE_SOURCE_DIR}/include"
# )

# test_lib_bitbuffer 单元测试 可执行文件依赖的链接库
target_link_libraries(
  test_lib_bitbuffer
  ${GTEST_LIBRARY}
)

# test_lib_bitbuffer 单元测试
add_test(
  NAME
    test_lib_bitbuffer
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/test_lib_bitbuffer
)


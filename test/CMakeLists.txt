# ======= test_lib_bitbuffer

add_executable(
    test_lib_bitbuffer
    test_BitUtil.cpp
    test_BitBuffer.cpp
    )

target_link_libraries(
    test_lib_bitbuffer
    gtest_main
    )

add_test(
  NAME
    test_lib_bitbuffer
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )

# ======= test_lib_http





# ======= test_lib_netcore



add_executable(
    unit_tests
    test_BitUtil.cpp
    test_BitBuffer.cpp
    )

target_link_libraries(
    unit_tests
    gtest_main
    BitBuffer
    )

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )
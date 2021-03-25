
aux_source_directory(. SRCS)

add_executable( test_timber ${SRCS})
target_link_libraries( test_timber ${GTEST_LIBRARY} )
add_test( NAME test_timber COMMAND ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/test_timber )

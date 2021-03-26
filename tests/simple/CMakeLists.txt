
aux_source_directory(. SRCS)

add_executable( test_simple ${SRCS})
target_link_libraries( test_simple ${GTEST_LIBRARY} )
add_test( NAME test_simgle COMMAND ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/test_simgle )

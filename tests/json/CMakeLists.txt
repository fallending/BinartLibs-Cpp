
aux_source_directory(. SRCS)

add_executable( test_mtjson ${SRCS})

target_include_directories( test_mtjson PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries( test_mtjson ${GTEST_LIBRARY} "mtjson" )

add_test( NAME test_mtjson COMMAND ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/test_mtjson )


add_executable( test_fancy ${SRCS})

target_sources( test_fancy
    PRIVATE
    ./foundation/test_container_operator.cc
    
)
target_include_directories( test_fancy PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries( test_fancy ${GTEST_LIBRARY} )

add_test( NAME test_fancy COMMAND ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/test_fancy )

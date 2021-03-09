# 注意：该库，只有头文件，，没有没有源文件
project(bitbuffer)

file(GLOB HEADER_FILES "*.hpp" "*.h")

# build成功，才会执行。。。
# install(FILES ${HEADER_FILES} DESTINATION ${CMAKE_HEADERS_OUTPUT_DIRECTORY})
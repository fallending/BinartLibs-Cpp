# 注意：该库，只有头文件，，没有没有源文件
project(bitbuffer)

file(GLOB HEADER_FILES "*.hpp")

install(FILES ${HEADER_FILES} DESTINATION bitbuffer)
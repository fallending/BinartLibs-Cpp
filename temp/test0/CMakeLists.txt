
project(hello)                    # CMake工程名

file(GLOB SOURCE "./*.cpp")       # CMake：工程的源文件在哪里？

add_executable(hello ${SOURCE})   # CMake：生成可执行文件`hello`, 源文件是由上面定义
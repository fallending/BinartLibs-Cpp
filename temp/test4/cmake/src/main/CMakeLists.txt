# .main可执行文件

file(GLOB SOURCE_1 "${PROJECT_ROOT_PATH}/main/*.cpp")

add_executable(main ${SOURCE_1})

target_link_libraries(main hello)                           # CMake: 静态库在哪里?
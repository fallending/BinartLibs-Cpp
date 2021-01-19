# .hello静态库

file(GLOB SOURCE_1 "${PROJECT_ROOT_PATH}/hello/*.cpp")

add_library(hello STATIC ${SOURCE_1})                         # CMake: 生成一个静态库
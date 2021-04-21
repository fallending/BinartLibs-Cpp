cmake_minimum_required(VERSION 3.17)

include(config.cmake)
include(dependency.cmake)

# 准备全局配置头文件
# configure_file(tutorialConfig.h.in tutorialConfig.h)

# 配置开发库目录
add_subdirectory(src)
include_directories(src)

# 启用单元测试
enable_testing()
add_subdirectory(tests)
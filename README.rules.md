# 多项目、多模块综合开发规范

> 分久必合，合久必分，此为“合”，而“分”自不必说，分布式开发，联合编译，下一阶段。

## 目录结构

```
.
├── CMakeLists.txt                          cmake主配置
├── Makefile                                本地命令集合
├── bin                                     脚本集合
├── bootstrap.sh                            环境初始化脚本
├── cmake                                   可复用cmake
│   ├── googletest-download.cmake
│   ├── googletest.cmake
│   └── ios.toolchain.cmake
├── doc
├── examples
│   ├── CMakeLists.txt
│   └── main.cpp
├── include                                 发布文件夹 - 头文件
├── lib                                     发布文件夹 - 静态库、动态库
├── mt_config.h.in
├── src
│   ├── CMakeLists.txt
│   ├── bitbuffer
│   ├── disruptor
│   ├── http
│   ├── net
│   ├── queue
│   └── tcp
└── test
    ├── CMakeLists.txt
    ├── bitbuffer
    ├── http
    ├── net
    └── tcp
```

## 依赖关系


#### 本地库如何依赖

> 本地库的依赖，基于发布文件夹
> target_link_directories/target_include_directories/target_link_libraries 都面向发布文件夹

#### 三方库如何依赖




## 单元测试


## 项目关系



## 其他


#### 如何规范的使用动态宏开关

1. 所有宏模板应该定义在 ·mt_config.h· 中
2. 尽量不用 add_definetions(-DDEBUG) 直接注入宏
3. 尽量不使用 cmake .. -DCMAKE_BUILD_TYPE=DEBUG，然后 if (CMAKE_BUILD_TYPE STREQUAL DEBUG) 配合 2 直接注入宏
4. 

#### 子模块的CMakeLists.txt中应该尽可能少的依赖环境变量


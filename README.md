# mt-ccs
> Maketea .cc libs
> 简洁为主，效率至上
> 【规范+工具链】模块化、单元测试、例子编写、持续集成、增量编译、交叉编译

## 工具

感谢：https://github.com/bast/gtest-demo

- [Google Test](https://github.com/google/googletest/blob/master/googletest/docs/primer.md)
- [Travis-CI](https://docs.travis-ci.com/)
- [Coveralls](https://coveralls.io/)
- [cmake必看书目](https://github.com/xiaoweiChen/CMake-Cookbook/blob/master/SUMMARY.md)
- [cmake必翻文档](https://cmake.org/cmake/help/v3.19/command/configure_file.html)
- 命令组合：
  - ldd <xx.so><executable> 查看链接关系
- [谷歌项目风格指南-c++](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/naming/#macro-names)
- [polly](https://polly.readthedocs.io/en/latest/toolchains/android.html), 一大波可用的cmake toolchain

### 工程构建

```bash
git clone https://github.com/fallending/BinartLibs-Cpp.git
cd BinartLibs-Cpp
mkdir build // out-of-source 编译
cd build
cmake ..
cmake --build .
```

### 测试用例

使用 `ctest`:
```
$ ctest
```

或者 `unit_tests`:
```
$ ./bin/unit_tests
```


### 其他指令

```
// 项目清理
$ git clean -d -f -x
```

## 使用指南

### BitBuffer

```c++
#include "/path/to/BitBuffer.h"
#include <iostream>

BitBuffer bb;
bb.write_bits(true, 1);
bb.write_bits(false, 1);
bb.write_bits(2, 2);
bb.write_bits(10, 4);
bb.write_byte(100);

std::cout << bb.read_bit(0) << std::endl;      // Prints out 1 (aka true)
std::cout << bb.read_bit(1) << std::endl;      // Prints out 0 (aka false)
std::cout << bb.read_bits(2, 2) << std::endl;  // Prints out 2
std::cout << bb.read_bits(4, 4) << std::endl;  // Prints out 10
std::cout << bb.read_byte(1) << std::endl;     // Prints out 100
std::cout << bb.read_bits(8, 8) << std::endl;  // Prints out 100
std::cout << bb.read_byte(0) << std::endl;     // 1010 1010, so it prints out 170
std::cout << bb.read_bytes(0, 2) << std::endl; // 1010 1010 0110 0100, so it prints out 43620

// Iterators

// Bit Iterator
for (BitBuffer::iterator iter = bb.begin(); iter != bb.end(); ++iter) {
    uint8_t bit = *iter;

    // Do stuff with bit
}

for (auto& bit : bb) {
    // Do stuff with bit
}

// Byte iterator
for (auto& byte : bb.get_bytes()) {
    // Do stuff with byte
}
```


## 本仓库额外提供了什么？CMake作为工程构建工具的大型项目管理能力！

- 如何通过 ADD_LIBRARY 指令构建动态库和静态库。
- 如何通过 SET_TARGET_PROPERTIES 同时构建同名的动态库和静态库。
- 如何通过 SET_TARGET_PROPERTIES 控制动态库版本
- 如何通过 INSTALL 指令来安装头文件和动态、静态库

- 如何通过INCLUDE_DIRECTORIES指令加入非标准的头文件搜索路径。
- 如何通过LINK_DIRECTORIES指令加入非标准的库文件搜索路径。
- 如果通过TARGET_LINK_LIBRARIES为库或可执行二进制加入库链接。



## 为什么使用cmake？

1. 工程化

> 定义

- 工程化即系统化、模块化、规范化的一个过程
- 如果说计算机科学要解决的是系统的某个具体问题，或者更通俗点说是面向编码的，那么工程化要解决的是如何提高整个系统生产效率。
- 与其说软件工程是一门科学，不如说它更偏向于管理学和方法论。

> 目标

- 工程化解决的问题是，如何提高编码、测试、维护阶段的生产效率。


1. 工程化-系统化


2. 工程化-模块化
3. 工程化-规范化


草，这部分概念不清晰，换个表述，表示当前要做的几件事：



### 为什么使用cmake？2

##### 软件开发流程模型

需求分析 - 系统设计 - 软件编码 - 测试 - 运行 - 维护 （简单版本，还可以拆的更细）

##### 开发规范


1. 编码规范
2. 版本管理规范
3. 各种规范


##### 模块化/组件化开发


module侧重的是对属性的封装，重心是在设计和开发阶段，不关注runtime的逻辑。module是一个白盒；而component是一个可以独立部署的软件单元，面向的是runtime，侧重于产品的功能性。component是一个黑盒，内部的逻辑是不可见的。

模块/组件化开发的必要性
随着web应用规模越来越大，模块/组件化开发的需求就显得越来越迫切。模块/组件化开发的核心思想是分治，主要针对的是开发和维护阶段。


###### 工程构建&编译

构建的核心是资源管理。


###### 软件部署&发布

？？？？？？

### 参考

- [用cmake生成ios framework库](https://github.com/zhaowd2001/tvm_phone/blob/master/tvm-cmake-ios.md)
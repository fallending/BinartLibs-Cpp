# Libs for Cpp

## 工具

C/C++ unit test demo using [Google Test](https://github.com/google/googletest/blob/master/googletest/docs/primer.md) deployed to
[Travis-CI](https://travis-ci.org/bast/gtest-demo/builds) with test coverage
deployed to [Coveralls](https://coveralls.io/r/bast/gtest-demo).

- [Build and test history](https://travis-ci.org/bast/gtest-demo/builds)
- [Code coverage](https://coveralls.io/r/bast/gtest-demo)

- 十分抱歉，该项目代码采用iOS编码规范，与Cpper不兼容。

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


## References

- https://crascit.com/2015/07/25/cmake-gtest/

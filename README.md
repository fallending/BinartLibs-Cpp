# BitBuffer for Cpp

## Installation

To compile and run the test file:
```
$ git clone https://github.com/Aadeshp/BitBufferCpp.git
$ cd BitBufferCpp && make


// clean
$ rm -rf build

// clean with git 
$ 在Git的这些日子里，你可能会忘记CMake并使用git clean -d -f -x，这将删除所有不受源代码管理的文件。

git clone https://github.com/bast/gtest-demo.git
cd gtest-demo
mkdir build
cd build
cmake ..
cmake --build .


```

## How To Use BitBuffer

```c++
#include "/path/to/bit_buffer.hpp"
#include <iostream>

bit_buffer bb;
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
for (bit_buffer::iterator iter = bb.begin(); iter != bb.end(); ++iter) {
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

---

# gtest-demo

C/C++ unit test demo using [Google Test](https://code.google.com/p/googletest) deployed to
[Travis-CI](https://travis-ci.org/bast/gtest-demo/builds) with test coverage
deployed to [Coveralls](https://coveralls.io/r/bast/gtest-demo).

- [Build and test history](https://travis-ci.org/bast/gtest-demo/builds)
- [Code coverage](https://coveralls.io/r/bast/gtest-demo)
- Licensed under [BSD-3](../master/LICENSE)

This demo uses the approach presented by Craig Scott in https://crascit.com/2015/07/25/cmake-gtest/.


## How to build demo

```bash
git clone https://github.com/bast/gtest-demo.git
cd gtest-demo
mkdir build
cd build
cmake ..
cmake --build .
```


## Running the tests

Either using `ctest`:
```
$ ctest

Running tests...
Test project /home/user/gtest-demo/build
    Start 1: unit
1/1 Test #1: unit .............................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec
```

Or directly using `unit_tests`:
```
$ ./bin/unit_tests

[==========] Running 2 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 2 tests from example
[ RUN      ] example.add
[       OK ] example.add (0 ms)
[ RUN      ] example.subtract
[       OK ] example.subtract (0 ms)
[----------] 2 tests from example (1 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test case ran. (1 ms total)
[  PASSED  ] 2 tests.

```

## References

- https://crascit.com/2015/07/25/cmake-gtest/

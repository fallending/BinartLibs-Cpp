#ifndef __BA_BIT_UTIL_H__
#define __BA_BIT_UTIL_H__

#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include <ctype.h>
#include <vector>

#include <iostream>

#if CHAR_BIT == 8
typedef unsigned char       uint8_t;
typedef signed char         int8_t;
typedef unsigned short      uint16_t;
typedef signed short        int16_t;
typedef unsigned int        uint32_t;
typedef signed int          int32_t;
typedef long long           int64_t;
typedef unsigned long long  uint64_t;
typedef float               float32;
typedef double              float64;
#else
#error uint8_t is not supported as a fundamental type
#endif

namespace binart {

    // 字节流转vector容器
    inline std::vector<uint8_t> bytes2vector(const uint8_t *d) {
        std::vector<uint8_t>::size_type size = strlen((const char*)d);
        std::vector<uint8_t> vec(d, d + size);
        return vec;
    };

    // vector容器转字符串
    // vector<uint8_t> data = {'h', 'e', 'l', 'l', 'o', '!'};
    inline std::string vector2string(std::vector<uint8_t> v) {
        return std::string(std::begin(v), std::end(v)).c_str();
    }
    
}

#endif // __BA_BIT_UTIL_H__
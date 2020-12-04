#ifndef __BA_BIT_UTIL_H__
#define __BA_BIT_UTIL_H__

#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include <ctype.h>
#include <vector>

#include <iostream>

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
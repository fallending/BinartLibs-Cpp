

#include <gtest/gtest.h>

#include <functional>
#include <future>
#include <iostream>
#include <vector>

using namespace std;

enum GenderType
{
    GenderTypeMale,
    GenderTypeFemale,
};

TEST(template, aaaaa)  // 测试引用返回值
{
    const GenderType gender = GenderTypeMale;
    const uint64_t   age    = 23;

    const GenderType &genderRef = gender;
    const uint64_t &  ageRef    = age;

    // error: no matching function for call to 'make_pair'
    // std::pair<GenderType, uint64_t> attr_pair_1 = std::make_pair<GenderType, uint64_t>(genderRef, ageRef);
    std::pair<GenderType, uint64_t> attr_pair_2 =
        std::make_pair(gender, age);  // 疑问：右值引用，到底是个啥？？？草。。。
    std::pair<GenderType, uint64_t> attr_pair_3 = std::pair<GenderType, uint64_t>(genderRef, ageRef);
}
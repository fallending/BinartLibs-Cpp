/*
 * @Author: your name
 * @Date: 2021-03-26 13:09:34
 * @LastEditTime: 2021-03-26 13:52:34
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/tests/simple/test_reference.cc
 */

#include <gtest/gtest.h>

#include <iostream>
#include <vector>

// std::vector<int> &getIds() { // bad
std::vector<int> GetIds()
{  // good
    std::vector<int> v;
    return v;
};

// std::string &getNames() { // bad
std::string GetNames()
{  // good
    std::string s = "Faz";
    s += "Far";
    s += "Boo";
    return s;
};

TEST(reference, retval)  // 测试引用返回值
{
    using ::std::cout;
    using ::std::endl;
    using ::std::string;
    using ::std::vector;

    // 测试容器引用返回
    vector<int> ids = GetIds();

    ids.emplace_back(4);

    std::cout << ids[0] << endl;

    // 测试字符串引用返回
    string names = GetNames();

    std::cout << names << endl;
}

class MtCopyable
{
private:
    std::unique_ptr<std::string> strPtr_;

public:
    MtCopyable()  = default;
    ~MtCopyable() = default;
};

// TEST(Reference, TryCopyable)
// {
//     using ::std::map;
//     using ::std::vector;

//     MtCopyable           copy_a;
//     map<int, MtCopyable> copyables = {{1, copy_a}};

//     MtCopyable copy_tmp;

//     auto copy = copyables.find();
//     if (copy != copyables.end())
//     {
//         copyable = copy.second;
//     }
// }
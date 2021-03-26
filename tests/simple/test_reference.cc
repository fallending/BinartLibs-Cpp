/*
 * @Author: your name
 * @Date: 2021-03-26 13:09:34
 * @LastEditTime: 2021-03-26 13:52:34
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/tests/simple/test_reference.cc
 */

#include <gtest/gtest.h>
#include <vector>
#include <iostream>

// std::vector<int> &getIds() {
std::vector<int> getIds() {
    std::vector<int> v;
    return v;
};

// std::string &getNames() {
std::string getNames() {
    std::string s = "Faz";
    s += "Far";
    s += "Boo";
    return s;
};

using namespace std;

TEST(reference, retval) // 测试引用返回值
{
    // 测试容器引用返回
    vector<int> ids = getIds();

    ids.emplace_back(4);

    std::cout << ids[0] << endl;

    // 测试字符串引用返回
    string names = getNames();

    std::cout << names << endl;

}

TEST(reference, somethingElse) {

}
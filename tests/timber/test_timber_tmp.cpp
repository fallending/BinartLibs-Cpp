/*
 * @Author: your name
 * @Date: 2021-03-25 16:48:38
 * @LastEditTime: 2021-03-25 17:03:01
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/tests/timber/test_timber_tmp.cpp
 */

#include <gtest/gtest.h>
// #include "log/file_log.h"

// int apple = 0;

enum FruitType
{
    FruitTypeApple = 0,
};

// const char *getFruitName() {
//     return "";
// };

struct Fruit
{
    FruitType type;
    const char *name;
};

class FruitFactory
{
    void buildFruit();
};

TEST(timber, tmp)
{
    enum FruitType fruitType = FruitTypeApple;
    FruitFactory *fruitFactory = new FruitFactory();
}
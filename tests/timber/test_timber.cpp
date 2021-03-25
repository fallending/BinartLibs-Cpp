/*
 * @Author: your name
 * @Date: 2021-03-23 20:37:37
 * @LastEditTime: 2021-03-25 18:58:05
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/tests/timber/test_timber.cpp
 */
// MARK: - UT 入口

#include <gtest/gtest.h>
#include <iostream>
#include "timber/mt_timber.h"
#define __MT_TAG__ "Timber Unit Test"
#include "log/log.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

using namespace timber;

// MARK: - ...

int apple = 0;

enum FruitType {
    FruitTypeApple = 0,
};

const char *getFruitName() {
    return "";
};

struct Fruit {
    FruitType type;
    const char *name;
};

class FruitFactory {
    void buildFruit();
};

// MARK: - 测试tree

class TestTree : public Tree {
public:
    virtual bool isLoggable() {
        return true;
    }

    virtual void log(LogPriority priority, const std::string &tag, const std::string &message) {
        switch (priority)
        {
        case LogPriorityDebug:
            std::cout << green << "hello world" << reset << std::endl;
            break;

        case LogPriorityInfo:
            std::cout << white << "hello world" << reset << std::endl;
            break;

        case LogPriorityWarn:
            std::cout << yellow << "hello world" << reset << std::endl;
            break;

        case LogPriorityError:
            std::cout << red << "hello world" << reset << std::endl;
            break;

        default:
            break;
        }
    }
};

void test_print(const std::string &message) {
    if (&message != NULL) {
        std::cout << message << std::endl;
    }
}

// MARK: - 测试用例

TEST(timber, all)
{
    // 种树
    std::shared_ptr<TestTree> tree = std::make_shared<TestTree>();
    // Timber::plant(static_pointer_cast<Tree>(tree));
    logger.plant(tree);

    std::cout << green << "hello world" << reset << std::endl;
    std::cout << white << "hello world" << reset << std::endl;
    std::cout << yellow << "hello world" << reset << std::endl;
    std::cout << red << "hello world" << reset << std::endl;

    // 打印日志
    const char *p = NULL;
    // test_print(p);

    logger.d("");
    logger.i("");
    logger.w("");
    logger.e("");

    enum FruitType fruitType = FruitTypeApple;
    FruitFactory *fruitFactory = new FruitFactory();

}
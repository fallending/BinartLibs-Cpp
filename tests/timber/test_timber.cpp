/*
 * @Author: your name
 * @Date: 2021-03-23 20:37:37
 * @LastEditTime: 2021-03-27 16:06:09
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/tests/timber/test_timber.cpp
 */
// MARK: - UT 入口

#include <gtest/gtest.h>
#include <iostream>

#define TAG_ "Timber Unit Test"
#include <timber/mt_timber.h>
#include <log/log.h>

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

using namespace timber;
using namespace std;

// MARK: - ...

int apple = 0;

enum FruitType
{
    FruitTypeApple = 0,
};

const char *GetFruitName() { return ""; };

struct Fruit
{
    FruitType   type;
    const char *name;
};

class FruitFactory
{
    void BuildFruit();
};

// MARK: - 测试tree

void TestPrint(const std::string &message)
{
    // if (&message != NULL) {
    //     std::cout << message << std::endl;
    // }
}

// MARK: - 测试用例

//此宏展开后，类似于printf("123"),printf("456");
#define TRACE_CMH_1 \
    (printf("%s(%d)-<%s>: ", __FILE__, __LINE__, __FUNCTION__), printf)

//此宏展开后，类似于printf("%d""%d", 1, 2);
#define TRACE_CMH_2(fmt, ...) \
    printf(                   \
        "%s(%d)-<%s>: " #fmt, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

TEST(timber, all)
{
    cout << "TAG_ = " << TAG_ << endl;

    // 叶子

    LeafPtr default_leaf = CreateLeaf(LogPriorityDebug,
                                      "default-tag",
                                      __FILE__,
                                      __FUNCTION__,
                                      to_string(__LINE__));

    cout << default_leaf.get()->ToString() << endl;

    TRACE_CMH_2("BASE: [%d]\n", 100);

    // 种树
    shared_ptr<DebugTree> tree = make_shared<DebugTree>();
    logger.Plant(tree);

    cout << Green << "hello world" << Reset << endl;
    cout << White << "hello world" << Reset << endl;
    cout << Yellow << "hello world" << Reset << endl;
    cout << Red << "hello world" << Reset << endl;

    // 打印日志
    const char *p = nullptr;
    // TestPrint(p);

    logger.d("debug message");
    logger.i("info message");
    logger.w("warn message");
    logger.e("error message");

    logd("debug 2 message");
    logi("info 2 message");
    logw("warn 2 message");
    loge("error 2 message");

    logd("integer = %d", 100);
    logd("float = %f", 100.0);
    logd("string = %s", "i am what i am.");

    logw("ninja is online...");

    // 开线程测试

    // FruitType     fruit_type    = FruitTypeApple;
    // FruitFactory *fruit_factory = new FruitFactory();
}
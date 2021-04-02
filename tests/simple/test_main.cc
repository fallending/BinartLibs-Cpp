#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

class WarnMeBefore {
private:
    /* data */
    int _age;

public:
    WarnMeBefore(/* args */);
    ~WarnMeBefore();
};

WarnMeBefore::WarnMeBefore(/* args */) {}

WarnMeBefore::~WarnMeBefore() {}

// 修改后：

class WarnMeAfter {
private:
    /* data */
    int age_ = 1;

public:
    WarnMeAfter(/* args */) = default;
    ~WarnMeAfter() = default;
};

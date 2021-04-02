#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

class WarnMe {
private:
    /* data */
    int age;

public:
    WarnMe(/* args */);
    ~WarnMe();
};

WarnMe::WarnMe(/* args */){} = default;

WarnMe::~WarnMe() {}


#include <gtest/gtest.h>
#include <string>
#include <fancy/fancy.h>

int main()
{
    using ::mt::Pair;
    using ::std::cout;
    using ::std::endl;
    using ::std::string;
    using ::std::vector;

    vector<string> vv = {"a", "b", "c"};

    std::string outStr = join_str(vv, "|");

    vector<string> vv2 = split_str(outStr,  '|');

    return 0;
}
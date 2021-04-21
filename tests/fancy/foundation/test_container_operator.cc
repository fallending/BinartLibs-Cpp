
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

    // std::string outStr = join_str(vv, "|");

    // vector<string> vv2 = split_str(outStr,  '|');

    // 测试 Map
    std::vector<double>      ints = {1, 2, 3, 4, 5};
    std::vector<std::string> strs =
        mt::container::operating::Map<std::string>(ints, [](double i) -> std::string { return std::to_string(i); });

    strs.resize(ints.size());

    // std::transform(source.begin(), source.end(), mask.begin(), std::back_inserter(dest), [](int value, int filter){
    // return value * filter};);

    // mt::container::operating::Map(ints, strs, [](double i) -> std::string { return std::to_string(i); });
    // std::transform(ints.begin(), ints.end(), strs.begin(), [](double i) -> std::string { return std::to_string(i);
    // });

    cout << strs.at(0) << endl;
    cout << mt::container::operating::Join(strs, ",") << endl;

    cout << "end-----" << endl;

    std::vector<uint32_t>    ints1 = {1, 2, 3, 4, 5};
    std::vector<std::string> strs1 =
        mt::Map<std::string, uint32_t>(ints1, [](uint32_t i) -> std::string { return std::to_string(i); });

    cout << mt::container::operating::Join(strs1, ",") << endl;

    return 0;
}
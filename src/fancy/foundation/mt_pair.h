#include <iostream>

#ifndef MT_PAIR_
#define MT_PAIR_

namespace mt
{
template <class T1, class T2>
struct Pair
{
    using Type1 = T1;
    using Type2 = T2;

    T1 first;
    T2 second;

    // 默认构造
    Pair() : first(T1()), second(T2()) {}  // T1()用0初始化 T2()用0初始化

    // 构造
    Pair(const T1& a, const T2& b) : first(a), second(b) {}

    // 拷贝构造
    template <class U, class V>
    explicit Pair(const Pair<U, V>& p) : first(p.first), second(p.second)
    {
        std::cout << "a" << std::endl;
    }  // {用来测试那些对象创建调用了copy构造函数}
};

// MARK: - 比较
template <class T1, class T2>
bool operator==(const Pair<T1, T2>& s1, const Pair<T1, T2>& s2)
{
    return s1.first == s2.first && s1.second == s2.second;
}

template <class T1, class T2>
bool operator>(const Pair<T1, T2>& s1, const Pair<T1, T2>& s2)
{
    return (s1.first > s2.first) || (!(s1.first < s2.first) && s1.second > s2.second);
}

template <class T1, class T2>
bool operator<(const Pair<T1, T2>& s1, const Pair<T1, T2>& s2)
{
    return (s1.first < s2.first) || (!(s1.first > s2.first) && s1.second < s2.second);
}

}  // namespace mt

#endif  // MT_PAIR_
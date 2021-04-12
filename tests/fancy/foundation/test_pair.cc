
#include <gtest/gtest.h>
#include <string>
#include <fancy/fancy.h>

int main()
{
    using ::mt::Pair;
    using ::std::cout;
    using ::std::endl;
    using ::std::string;

    //默认构造函数
    Pair<int, string> a2;

    cout << "默认构造函数:" << endl;
    cout << a2.first << " " << a2.second << endl;

    //构造函数
    Pair<int, char*> a1(101, "lanzhihui");  //参数类型必须与定义类型一样
    cout << "构造函数:" << endl;
    cout << a1.first << " " << a1.second << endl;
    Pair<int, char*> a3(101, "laznzhihui");
    cout << a3.first << " " << a3.second << endl;

    //拷贝构造函数
    Pair<int, string> s1(a1), s2(a1);  //使用Template形式的copy构造函数，构造过程隐式类型转换
    cout << "拷贝构造函数:" << endl;
    cout << s1.first << " " << s1.second << endl;
    cout << s2.first << " " << s2.second << endl;

    Pair<int, string> s3;

    cout << "sss" << endl;
    s3 = a3;  // 调用拷贝构造函数
    cout << s3.first << " " << s3.second << endl;
    cout << "sss" << endl;
    cout << "测试:" << endl;
    //测试'==' '>' '<'
    if (s1 == s2)
    {
        cout << "operator==   OK!" << endl;
    }
    if (s1 < s3)
    {
        cout << "operator>   OK!" << endl;
    }
    if (s3 > s1)
    {
        cout << "operator<   OK!" << endl;
    }
    system("pause");
    return 0;
}
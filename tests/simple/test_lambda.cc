

#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <future>
#include <functional>

using namespace std;

void test_lambda_async_recursion()
{

  function<void(int, int)> merge;

  merge = [&merge](int a, int b) {
    sleep(1);
    cout << a << ", " << b << endl;

    if (a > 0)
    {
      merge(0, b);
    }
    else if (b > 0)
    {
      merge(a, 0);
      return;
    }
    else
    {
      return;
    }
  };

  std::async(std::launch::async, [=]() mutable {
    merge(1, 1);
  });

  sleep(3);
}

TEST(lambda, recursion) // 测试引用返回值
{
  // 同步递归调用

  function<void(int, int)> merge;

  // 空转一次
  try
  {
    /* code */
    merge(1, 2);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }

  // 正式测试
  merge = [&merge](int a, int b) {
    cout << a << ", " << b << endl;

    if (a > 0)
    {
      merge(0, b);
    }
    else if (b > 0)
    {
      merge(a, 0);
      return;
    }
    else
    {
      return;
    }
  };

  merge(1, 1);

  // 异步递归调用
  test_lambda_async_recursion();

  sleep(5);
}
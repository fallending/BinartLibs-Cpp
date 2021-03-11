# GTest使用说明


## API说明

#### Test

```cpp

// 获取参数并测试
TEST_P(IsPrimeParamTest, ExpectTrueReturn) {
  int n = GetParam();

  EXPECT_TRUE(IsPrime(n));
}

// 显式指定参数并测试
// testing::Range(3, 11, 2) 迭代（2是step、步长），3\5\7\9\11
// testing::ValuesIn(vector<int64_t>(...)) // 稀数组
INSTANTIATE_TEST_CASE_P(TrueReturn, IsPrimeParamTest, testing::Values(3, 5, 11, 14))

```

#### Expect

```cpp
EXPECT_EQ(1, 2) // 继续进行



```

#### Assert

```cpp
ASSERT_EQ(1, 2) // abort 当前单元测试
```
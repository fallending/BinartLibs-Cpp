


https://zhuanlan.zhihu.com/p/102248131


用 cpplint 做提交检查，用过clang-tidy做 CI 检查


https://clang.llvm.org/extra/clang-tidy/checks/readability-identifier-naming.html



# https://clang.llvm.org/extra/clang-tidy/checks/misc-non-private-member-variables-in-classes.html


## 接入备份

**重要的事情说一遍：.clang-tidy别有语法错误啊！**
#### 错误：PCH file uses an older PCH format that is no longer supported

**不支持预编译头？**

```
target_precompile_headers(lim
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/common/common_def.h
)
```

像上面这样的配置，会导致这个错误。

#### 错误：
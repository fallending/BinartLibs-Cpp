# mt_json - 为懒人打造的json对象序列化神器 #

> 从 slothjson 改造而成，移除中间文件的维护，用最简洁的代码维护DTO

TODO:
1. [支持] 丰富的类型支持
2. [支持] 模型嵌套
3. [支持] 字段映射
4. [准备支持] 字段黑名单
5. [支持] 模型容器直接解析 std::vector<MtLoginDTO>
6. [支持] decode字段有无判断：has_<field_name>，比如 `has_isStarted()`
7. [准备支持] 对象实例方法 string serialize(); 类方法 struct deserialize(string json);
8. [准备支持] 结构体 列表初始化： Student s = {name:"John", id:1, age: 23};
9. [准备支持] 字段异常处理：encode失败，如何处理？decode失败，如何处理？字段合法性如何保证？
10. [准备支持] 支持动态类型，1. 支持用户无限扩展类型（不限于 int32_t ，甚至可以是用户自定义的枚举）2. 支持decode类型判断，"" -> int 如何做？
11. [准备支持] 支持用户自定义枚举。。。。
12. [准备支持] 结构体嵌套初始化
13. [准备支持] 模型继承
14. [问题修复] 如果 std::string extra 对应json中 "extra": {} 解析会报错，导致其他字段解析不出来。。。。

## mtjson怎么用？ ##

首先，你需要将以下内容放到你的项目中：

* `rapidjson`: 对应 `include/rapidjson`，这个是世界上最快的 `json` 解析库，[`rapidjson`](https://github.com/miloyip/rapidjson)
* `slothjson`: 对应 `include/slothjson.h` 以及 `include/slothjson.cpp`，这两个是 `slothjson` 基础库文件，[`slothjson`]()
* `mtjson`: 对应`include/mtjson.h`


#### 结构定义

```
// Headers

#include "mtjson.h"

namespace mtjson {

mt_struct_begin(metest_object_t)
  mt_field(bool, isStarted)
  mt_field(int8_t, mak)
  mt_field(int16_t, th)
  mt_field(int32_t, len)
  mt_field(int64_t, length)
  mt_field(double_t, amount)
  mt_field(MtString, str_val)
  mt_field(MtArray, vec)
  mt_field(MtMap, dict)
mt_struct_end(metest_object_t)

} // namespace mtjson

// Impls

namespace mtjson {

  mt_def_struct(metest_object_t, isStarted, mak, th, len, length, amount, str_val, vec, dict)

} // namespace mtjson
```

其他使用规则和slothjson一致！
# mt_json - 为懒人打造的json对象序列化神器 #

> 从 slothjson 改造而成，移除中间文件的维护，用最简洁的代码维护DTO

TODO:
1. [支持] 更丰富的类型支持
2. [支持] 模型嵌套
3. [支持] 字段映射
4. [准备支持] 字段黑名单
5. 模型容器直接解析 std::vector<MtLoginDTO>
6. ?????????还有什么？
7. 默认值？？？？？比如json中有几个字段没有，如何告知外部？现在用的 has_<field_name>，比如 `has_isStarted()`

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
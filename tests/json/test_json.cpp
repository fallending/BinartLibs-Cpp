/*
 * @Author: your name
 * @Date: 2021-03-17 11:29:36
 * @LastEditTime: 2021-03-23 21:42:05
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/test/json/test_json.cpp
 */

/*
 * @Author: your name
 * @Date: 2021-03-16 19:00:46
 * @LastEditTime: 2021-03-17 11:25:48
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /lilithnext-sdk/sdk/core/test/mtjson/test_mtjson.cc
 */

// MARK: - UT 入口

#include <gtest/gtest.h>
#include <iostream>
#include <json/json.h>

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

// MARK: - 测试对象自定义

using namespace std;
using namespace mt;
using namespace json;

// MARK: - 普通示例
mt_struct_begin(metest_object_t);
mt_field(bool, isStarted);
mt_field(int8_t, mak);
mt_field(int16_t, th);
mt_field(int32_t, len);
mt_field(int64_t, length);
mt_field(double_t, amount);
mt_field(MtString, str_val);
mt_field(MtArray, vec);
mt_field(MtMap, dict);
mt_struct_end(metest_object_t, isStarted, mak, th, len, length, amount, str_val, vec, dict);

// MARK: - 嵌套示例
mt_struct_begin(metest_child_t);
mt_field(int8_t, val);
mt_struct_end(metest_child_t, val);

mt_struct_begin(metest_parent_t);
mt_field(int8_t, val);
mt_field(metest_child_t, child);
mt_struct_end(metest_parent_t, val, child);

// MARK: - 容器示例

// MARK: - 测试用例

TEST(mtjson, all)
{
    const char *kJsonStr = "{\"amount\":2.279495565e-314,\"length\":7017276123153527842,\"len\":12,\"th\":0,\"str\":\"fsdafas\",\"mak\":0,\"isStarted\":true,\"vec\":[0,1,2,3,4,5,6,7,8,9],\"dict\":{\"key0\":\"val0\",\"key1\":\"val1\",\"key2\":\"val2\",\"key3\":\"val3\",\"key4\":\"val4\",\"key5\":\"val5\",\"key6\":\"val6\",\"key7\":\"val7\",\"key8\":\"val8\",\"key9\":\"val9\"}}";

    string inStr = kJsonStr;
    metest_object_t outObj;

    // json string -> c++ struct
    decode(inStr, outObj);

    cout << "[mtjson][all] out.len = " << outObj.len << endl;

    ASSERT_TRUE(outObj.isStarted);

    // c++ struct -> json string
    string outStr;
    encode<false, metest_object_t>(outObj, outStr);

    // ASSERT_EQ(outStr, inStr);
    cout << "[mtjson][all] outStr = " << outStr << endl;

    // ------ 嵌套
    const char *parentJson = "{\"val\":2,\"child\":{\"val\":3}}";

    metest_parent_t parentObj;

    decode(parentJson, parentObj);

    ASSERT_EQ(parentObj.child.val, 3);
}
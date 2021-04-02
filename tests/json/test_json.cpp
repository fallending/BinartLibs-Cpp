/*
 * @Author: your name
 * @Date: 2021-03-17 11:29:36
 * @LastEditTime: 2021-03-23 21:42:05
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mt-ccs/test/json/test_json.cpp
 */

// MARK: - UT 入口

#include <gtest/gtest.h>
#include <json/json.h>

#include <iostream>

int main(int argc, char **argv) {
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
mt_field(MtArray<int32_t>, vec);
mt_field(MtMap, dict);
mt_struct_end(metest_object_t, isStarted, mak, th, len, length, amount, str_val,
              vec, dict);

// MARK: - 嵌套示例
mt_struct_begin(metest_child_t);
mt_field(int32_t, val);
mt_struct_end(metest_child_t, val);

mt_struct_begin(metest_parent_t);
mt_field(int32_t, val);
mt_field(metest_child_t, child);
mt_struct_end(metest_parent_t, val, child);

// MARK: - 容器示例

mt_struct_begin(metest_element_t);
mt_field(int32_t, val);
mt_struct_end(metest_element_t, val);

mt_struct_begin(metest_container_t);
mt_field(int32_t, val);
mt_field(MtArray<metest_element_t>, elements);
mt_struct_end(metest_container_t, val, elements);

// MARK: - 语法简化

struct MeTestSimplifyT {
    int32_t val;
    mt_json_struct(MeTestSimplifyT, val)
};

// MARK: - 测试map成员变量初始化
struct TestMapInitClass : public mt_struct_t {
private:
    /* data */
    mt_fields_mapping = {{"string", "val"}, {"sec", "val"}, {"trd", "val"}};

public:
    TestMapInitClass(/* args */){};
    ~TestMapInitClass(){};

    const std::map<std::string, std::string> &get_mapping() {
        return __fields_mapping;
    };
};

// MARK: - 序列化字段映射

mt_struct_begin(metest_mapping_t);
mt_field(int32_t, val);
mt_fields_mapping = {{"val", "init_val"}};
mt_struct_end(metest_mapping_t, val);

// MARK: - 测试用例

TEST(mtjson, all) {
    // 测试字段映射可行性
    TestMapInitClass testMapInitObj;
    std::cout << "test mapping = "
              << (testMapInitObj.get_mapping()).count("string") << std::endl;

    // 测试普通对象序列化
    const char *kJsonStr =
        "{\"amount\":2.279495565e-314,\"length\":7017276123153527842,\"len\":"
        "12,\"th\":0,\"str\":\"fsdafas\",\"mak\":0,\"isStarted\":true,\"vec\":["
        "0,1,2,3,4,5,6,7,8,9],\"dict\":{\"key0\":\"val0\",\"key1\":\"val1\","
        "\"key2\":\"val2\",\"key3\":\"val3\",\"key4\":\"val4\",\"key5\":"
        "\"val5\",\"key6\":\"val6\",\"key7\":\"val7\",\"key8\":\"val8\","
        "\"key9\":\"val9\"}}";

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

    cout << "[mtjson][all] parentObj.child.val = " << parentObj.child.val
         << endl;

    // 容器
    const char *containerJson =
        "{\"val\":2,\"elements\":[{\"val\":3},{\"val\":3}]}";

    metest_container_t containerObj;

    decode(containerJson, containerObj);

    ASSERT_EQ(containerObj.elements.size(), 2);

    cout << "[mtjson][all] containerObj.elements.size() = "
         << containerObj.elements.size() << endl;

    // 字段映射
    const char *mappingJson = "{\"init_val\":2}";

    metest_mapping_t mappingObj;

    decode(mappingJson, mappingObj);

    ASSERT_EQ(mappingObj.val, 2);

    cout << "[mtjson][all] mappingJson.val = " << mappingObj.val << endl;

    std::string mappedJson;
    encode<false, metest_mapping_t>(mappingObj, mappedJson);

    cout << "[mtjson][all] mappedJson = " << mappedJson << endl;

    // 语法简化
    const char *simplifyJson = "{\"val\":2}";

    MeTestSimplifyT simplifyObj;

    decode(simplifyJson, simplifyObj);

    ASSERT_EQ(simplifyObj.val, 2);

    cout << "[mtjson][all] simplifyObj.val = " << simplifyObj.val << endl;

    std::string simplifiedJson;
    encode<false, MeTestSimplifyT>(simplifyObj, simplifiedJson);

    cout << "[mtjson][all] simplifiedJson = " << simplifiedJson << endl;
}
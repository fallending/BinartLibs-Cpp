#include <gtest/gtest.h>
#include <json/json.h>
#include <iostream>
#include <http/http.h>

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    // test http
    const std::string host = "https://www.baidu.com";
    httplib::Client   cli{host.c_str()};

    return RUN_ALL_TESTS();
}

// MARK: - 测试对象自定义

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
mt_struct_end(metest_object_t, isStarted, mak, th, len, length, amount, str_val, vec, dict);

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

struct MeTestSimplifyT
{
    int32_t val = 0;
    mt_json_struct(MeTestSimplifyT, val)
    // ... 这里已经不是类定义的scope，切入添加任何东西 ...
};

// MARK: - 测试map成员变量初始化
struct TestMapInitClass : public mt::json::MtStruct
{
private:
    /* data */
    MT_FIELDS_MAPPING = {{"string", "val"}, {"sec", "val"}, {"trd", "val"}};

public:
    TestMapInitClass(/* args */) = default;
    ~TestMapInitClass()          = default;

    const std::map<std::string, std::string> &GetMapping() const { return fields_mapping_; };
};

// MARK: - 序列化字段映射

mt_struct_begin(metest_mapping_t);
mt_field(int32_t, val);
MT_FIELDS_MAPPING = {{"val", "init_val"}};
mt_struct_end(metest_mapping_t, val);

// MARK: - 测试用例

TEST(mtjson, all)
{
    using ::mt::json::Decode;
    using ::mt::json::Encode;
    using ::std::cout;
    using ::std::endl;
    using ::std::string;

    // 测试字段映射可行性
    TestMapInitClass test_map_init_obj;
    cout << "test mapping = " << (test_map_init_obj.GetMapping()).count("string") << std::endl;

    // 测试普通对象序列化
    const char *k_json_str =
        "{\"amount\":2.279495565e-314,\"length\":7017276123153527842,\"len\":"
        "12,\"th\":0,\"str\":\"fsdafas\",\"mak\":0,\"isStarted\":true,\"vec\":["
        "0,1,2,3,4,5,6,7,8,9],\"dict\":{\"key0\":\"val0\",\"key1\":\"val1\","
        "\"key2\":\"val2\",\"key3\":\"val3\",\"key4\":\"val4\",\"key5\":"
        "\"val5\",\"key6\":\"val6\",\"key7\":\"val7\",\"key8\":\"val8\","
        "\"key9\":\"val9\"}}";

    string          in_str = k_json_str;
    metest_object_t out_obj;

    // json string -> c++ struct
    Decode(in_str, out_obj);

    cout << "[mtjson][all] out.len = " << out_obj.len << endl;

    ASSERT_TRUE(out_obj.isStarted);

    // c++ struct -> json string
    string out_str;
    Encode<false, metest_object_t>(out_obj, out_str);

    // ASSERT_EQ(outStr, inStr);
    cout << "[mtjson][all] outStr = " << out_str << endl;

    // ------ 嵌套
    const char *parent_json = R"({"val":2,"child":{"val":3}})";

    metest_parent_t parent_obj;

    Decode(parent_json, parent_obj);

    ASSERT_EQ(parent_obj.child.val, 3);

    cout << "[mtjson][all] parent_obj.child.val = " << parent_obj.child.val << endl;

    // 容器
    const char *container_json = R"({"val":2,"elements":[{"val":3},{"val":3}]})";

    metest_container_t container_obj;

    Decode(container_json, container_obj);

    ASSERT_EQ(container_obj.elements.size(), 2);

    cout << "[mtjson][all] containerObj.elements.size() = " << container_obj.elements.size() << endl;

    // 字段映射
    const char *mapping_json = "{\"init_val\":2}";

    metest_mapping_t mapping_obj;

    Decode(mapping_json, mapping_obj);

    ASSERT_EQ(mapping_obj.val, 2);

    cout << "[mtjson][all] mappingJson.val = " << mapping_obj.val << endl;

    std::string mapped_json;
    Encode<false, metest_mapping_t>(mapping_obj, mapped_json);

    cout << "[mtjson][all] mappedJson = " << mapped_json << endl;

    // 语法简化
    const char *simplify_json = "{\"val\":2}";

    MeTestSimplifyT simplify_obj;

    Decode(simplify_json, simplify_obj);

    ASSERT_EQ(simplify_obj.val, 2);

    cout << "[mtjson][all] simplify_obj.val = " << simplify_obj.val << endl;

    string simplified_json;
    Encode<false, MeTestSimplifyT>(simplify_obj, simplified_json);

    cout << "[mtjson][all] simplifiedJson = " << simplified_json << endl;
}

// MARK: - mtjson对象的列表初始化

// 普通结构体
struct Student
{
    int         id;
    int         age;
    std::string name;
};

// 有默认构造的结构体
struct Teacher
{
    int         id{0};
    int         age{0};
    std::string name;

    Teacher()  = default;
    ~Teacher() = default;
};

TEST(mtjson, init)
{
    const int         id   = 1;
    const int         age  = 23;
    const std::string name = "John";
    Student           s1   = {id, age, "John"};
    Student           s2   = {id : id, age : age, name : name};
    Student           s3   = {.id = id, .age = age, .name = name};
}

// MARK: - mtjson对象模板化

template <typename T>
struct BaseModel
{
    // constructor does not initialize these fields:
    // codeclang-tidy(["{}",5526,0])
    // clang-tidy选项貌似关不掉这个警告，是个bug？看这里：https://bugs.llvm.org/show_bug.cgi?id=37902#c2
    // 暂时先添加 {}
    int32_t     code{0};
    std::string msg;
    T           data;
};

// 特化

struct TestBaseModel
{
    int32_t val = 0;
    mt_json_struct(TestBaseModel, val)
    // ... 这里已经不是类定义的scope，切入添加任何东西 ...
};

template <>
struct BaseModel<TestBaseModel>
{
    int32_t       code{};
    std::string   msg;
    TestBaseModel data;

    mt_json_tpl_struct(BaseModel, BaseModel<TestBaseModel>, code, msg, data)
}

TEST(mtjson, template)
{
    using ::mt::json::Decode;
    using ::mt::json::Encode;
    using ::std::cout;
    using ::std::endl;
    using ::std::string;

    const char *tpl_json =
        "{\"code\":123, \"msg\":\"hello template json "
        "model!\",\"data\":{\"val\":2}}";

    BaseModel<TestBaseModel> tpl_obj;

    Decode(tpl_json, tpl_obj);

    ASSERT_EQ(tpl_obj.data.val, 2);

    cout << "[mtjson][all] tpl_obj.val = " << tpl_obj.data.val << endl;

    string tpled_json;
    Encode<false, BaseModel<TestBaseModel>>(tpl_obj, tpled_json);

    cout << "[mtjson][all] tpled_json = " << tpled_json << endl;
}

// 字段兼容
struct FieldCompatModel : public mt::json::MtStruct
{
    int32_t channel_id{};
    int32_t game_id{};
    // std::string extra;

    MT_FIELDS_MAPPING = {{"channel_id", "channelId"}, {"game_id", "gameId"}};
    mt_json_struct(FieldCompatModel, channel_id, game_id)
}

TEST(mtjson, FieldCompat)
{
    using ::mt::json::Decode;
    using ::mt::json::Encode;
    using ::std::cout;
    using ::std::endl;
    using ::std::string;

    const char *compat_json = "{\"channelId\":123, \"gameId\":124,\"extra\":{\"val\":2}}";

    FieldCompatModel compat_obj;

    Decode(compat_json, compat_obj);

    ASSERT_EQ(compat_obj.channel_id, 123);

    cout << "[mtjson][all] compat_obj.game_id = " << compat_obj.game_id << endl;

    string compated_json;
    Encode<false, FieldCompatModel>(compat_obj, compated_json);

    cout << "[mtjson][all] compated_json = " << compated_json << endl;
}
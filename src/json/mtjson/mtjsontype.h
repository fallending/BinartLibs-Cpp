#include <iostream>
#include <array>
#include <vector>
#include <map>

#ifndef MT_JSON_TYPE_H_
#define MT_JSON_TYPE_H_

// ----------------------------------
// Meta macro
// ----------------------------------

#define MT_MACRO_FIRST_(A, ...) A
#define MT_MACRO_FIRST(...) MT_MACRO_FIRST_(__VA_ARGS__, 0)

#define MT_MACRO_CONCAT_(A, B) A##B
#define MT_MACRO_CONCAT(A, B) MT_MACRO_CONCAT_(A, B)

// 偏移取数
#define MT_MACRO_AT16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) \
    MT_MACRO_FIRST(__VA_ARGS__)
#define MT_MACRO_AT(N, ...) MT_MACRO_CONCAT(MT_MACRO_AT, N)(__VA_ARGS__)

#define mt_macro_count(...) MT_MACRO_AT(16, __VA_ARGS__, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#define mt_macro_count_dec(...) \
    MT_MACRO_AT(16, __VA_ARGS__, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)  // 总参数个数减一

#define MT_MACRO_JOIN0(...)
#define MT_MACRO_JOIN1(A) A
#define MT_MACRO_JOIN2(A, B) A##____##B
#define MT_MACRO_JOIN3(A, B, C) A##____##B##____##C
#define MT_MACRO_JOIN4(A, B, C, D) A##____##B##____##C##____##D
#define MT_MACRO_JOIN5(A, B, C, D, E) A##____##B##____##C##____##D##____##E
#define MT_MACRO_JOIN6(A, B, C, D, E, F) A##____##B##____##C##____##D##____##E##____##F
#define MT_MACRO_JOIN7(A, B, C, D, E, F, G) A##____##B##____##C##____##D##____##E##____##F##____##G
#define MT_MACRO_JOIN8(A, B, C, D, E, F, G, H) A##____##B##____##C##____##D##____##E##____##F##____##G##____##H
#define MT_MACRO_JOIN(...) MT_MACRO_CONCAT(MT_MACRO_JOIN, mt_macro_count(__VA_ARGS__))(__VA_ARGS__)

#define MT_MACRO_CSTR_(A) #A
#define MT_MACRO_CSTR(A) MT_MACRO_CSTR_(A)

// ----------------------------------
// Macros Customized
// ----------------------------------

#undef MT_INVOKE
#define MT_INVOKE(block, ...)   \
    {                           \
        if (block)              \
            block(__VA_ARGS__); \
    }

// ----------------------------------
// Mutation type
// ----------------------------------

using MtBool   = bool;
using MtInt8   = int8_t;
using MtInt16  = int16_t;
using MtInt32  = int32_t;
using MtInt64  = int64_t;
using MtDouble = double;
using MtMap    = std::map<std::string, std::string>;
template <class T>
using MtArray  = std::vector<T>;
using MtString = std::string;

// ----------------------------------
// Json base struct
// ----------------------------------

namespace mt
{
namespace json
{
struct MtStruct
{
public:
    // 字段映射
    std::map<std::string, std::string>                fields_mapping_;
    virtual const std::map<std::string, std::string> &GetFieldsMapping() const { return fields_mapping_; };
    const char *                                      FieldsMapping(const char *init_field) const
    {
        if (this->GetFieldsMapping().count(init_field) > 0) /* init_field 映射到 out_field */
        {
            try
            {
                const std::string &out_field_str = (this->GetFieldsMapping()).at(init_field);

                // std::cout << "sfasfasfa = " << out_field_str << std::endl;
                return out_field_str.c_str();
            }
            catch (const std::exception &e)
            {
                // std::cerr << e.what() << '\n';
            }
        }
        // std::cout << "fewrtrew = " << init_field << std::endl;
        return init_field;
    }

    // 字段黑名单
    std::vector<std::string>                fields_blacklist_;
    virtual const std::vector<std::string> &GetFieldsBlacklist() const { return fields_blacklist_; };
    bool                                    IsFieldBlocked(const char *init_field) const
    {
        bool                            ret_val   = false;
        const std::vector<std::string> &blacklist = this->GetFieldsBlacklist();
        if (std::count(blacklist.begin(), blacklist.end(), init_field) > 0)
        {
            ret_val = true;
        }
        return ret_val;
    }

    MtStruct(/* args */) = default;
    ~MtStruct()          = default;
};

}  // namespace json

}  // namespace mt

// ----------------------------------
// Json struct
// ----------------------------------

/**
 * @brief 字段映射
 * @example mt_fields_mapping = {{"string", "val"}, {"sec", "val"}, {"trd",
 * "val"}};
 */
#define MT_FIELDS_MAPPING \
public:                   \
    std::map<std::string, std::string> fields_mapping_

/**
 * @brief 字段黑名单
 * @example mt_fields_blacklist = {"string", "val"};
 */
#define MT_FIELDS_BLACKLIST \
public:                     \
    std::vector<std::string> fields_blacklist_

/**
 * @brief 字段定义的辅助设施定义
 *
 */
#define MT_FIELD_SHELL_SPEC(type, field)                                   \
public:                                                                    \
    void skip_##field() { skip_##field##_ = true; }                        \
    bool has_##field() const { return has_##field##_; }                    \
                                                                           \
public:                                                                    \
    bool        skip_##field##_                                   = false; \
    bool        has_##field##_                                    = true;  \
    std::string typeof_##field##_ /*shell模式不支持动态类型识别*/ = #type;

/**
 * @brief 字段定义
 *
 */
#define mt_field(type, field) \
public:                       \
    type field;               \
    MT_FIELD_SHELL_SPEC(type, field)

#define mt_field_shell_1(field) MT_FIELD_SHELL_SPEC(none, field)

#define mt_field_shell_2(a, ...)                                  \
    MT_MACRO_CONCAT(mt_field_shell_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_field_shell_1(a)
#define mt_field_shell_3(a, ...)                                  \
    MT_MACRO_CONCAT(mt_field_shell_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_field_shell_1(a)
#define mt_field_shell_4(a, ...)                                  \
    MT_MACRO_CONCAT(mt_field_shell_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_field_shell_1(a)
#define mt_field_shell_5(a, ...)                                  \
    MT_MACRO_CONCAT(mt_field_shell_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_field_shell_1(a)
#define mt_field_shell_6(a, ...)                                  \
    MT_MACRO_CONCAT(mt_field_shell_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_field_shell_1(a)
#define mt_field_shell_7(a, ...)                                  \
    MT_MACRO_CONCAT(mt_field_shell_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_field_shell_1(a)
#define mt_field_shell_8(a, ...)                                  \
    MT_MACRO_CONCAT(mt_field_shell_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_field_shell_1(a)
#define mt_field_shell_9(a, ...)                                  \
    MT_MACRO_CONCAT(mt_field_shell_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_field_shell_1(a)
#define mt_field_shell_10(a, ...)                                 \
    MT_MACRO_CONCAT(mt_field_shell_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_field_shell_1(a)
#define mt_field_shell_11(a, ...)                                 \
    MT_MACRO_CONCAT(mt_field_shell_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_field_shell_1(a)
#define mt_field_shell_12(a, ...)                                 \
    MT_MACRO_CONCAT(mt_field_shell_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_field_shell_1(a)
#define mt_field_shell_13(a, ...)                                 \
    MT_MACRO_CONCAT(mt_field_shell_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_field_shell_1(a)
#define mt_field_shell_14(a, ...)                                 \
    MT_MACRO_CONCAT(mt_field_shell_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_field_shell_1(a)
#define mt_field_shell_15(a, ...)                                 \
    MT_MACRO_CONCAT(mt_field_shell_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_field_shell_1(a)
#define mt_field_shell_16(a, ...)                                 \
    MT_MACRO_CONCAT(mt_field_shell_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_field_shell_1(a)

#define mt_field_shell(...) MT_MACRO_CONCAT(mt_field_shell_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__)

// Field encode

#define mt_def_field_encode_1(a)                                                       \
    if (!skip_##a##_ && !mt::json::EncodeField(a, FieldsMapping(#a), alloc, json_val)) \
        break;
#define mt_def_field_encode_2(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_encode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_3(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_encode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_4(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_encode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_5(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_encode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_6(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_encode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_7(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_encode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_8(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_encode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_9(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_encode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_10(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_encode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_11(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_encode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_12(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_encode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_13(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_encode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_14(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_encode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_15(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_encode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_16(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_encode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_encode_1(a)

#define mt_def_field_encode(...)                                       \
    MT_MACRO_CONCAT(mt_def_field_encode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__)

// Field decode

#define mt_def_field_decode_1(a)                                            \
    if (!mt::json::DecodeField(json_val, FieldsMapping(#a), a, has_##a##_)) \
        break;
#define mt_def_field_decode_2(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_decode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_3(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_decode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_4(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_decode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_5(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_decode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_6(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_decode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_7(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_decode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_8(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_decode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_9(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_decode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_10(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_decode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_11(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_decode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_12(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_decode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_13(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_decode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_14(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_decode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_15(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_decode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_16(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_decode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_decode_1(a)

#define mt_def_field_decode(...)                                       \
    MT_MACRO_CONCAT(mt_def_field_decode_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__)

// Field assign

#define mt_def_field_assign_1(a) this->a = obj_val.a;
#define mt_def_field_assign_2(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_assign_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_3(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_assign_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_4(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_assign_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_5(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_assign_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_6(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_assign_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_7(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_assign_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_8(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_assign_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_9(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_assign_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_10(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_assign_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_11(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_assign_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_12(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_assign_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_13(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_assign_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_14(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_assign_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_15(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_assign_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_16(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_assign_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__) mt_def_field_assign_1(a)

#define mt_def_field_assign(...)                                       \
    MT_MACRO_CONCAT(mt_def_field_assign_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__)

// Field equal

#define mt_def_field_equal_1(a)              \
    if (!(this->a == obj_val.a))             \
    { /*printf("%s is not equally\n", #a);*/ \
        ret_val = false;                     \
    }
#define mt_def_field_equal_2(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_equal_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__);                                                    \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_3(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_equal_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__);                                                    \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_4(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_equal_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__);                                                    \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_5(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_equal_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__);                                                    \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_6(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_equal_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__);                                                    \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_7(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_equal_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__);                                                    \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_8(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_equal_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__);                                                    \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_9(a, ...)                                  \
    MT_MACRO_CONCAT(mt_def_field_equal_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__);                                                    \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_10(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_equal_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__);                                                    \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_11(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_equal_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__);                                                    \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_12(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_equal_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__);                                                    \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_13(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_equal_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__);                                                    \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_14(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_equal_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__);                                                    \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_15(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_equal_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__);                                                    \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_16(a, ...)                                 \
    MT_MACRO_CONCAT(mt_def_field_equal_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__);                                                    \
    mt_def_field_equal_1(a)

#define mt_def_field_equal(...)                                       \
    MT_MACRO_CONCAT(mt_def_field_equal_, mt_macro_count(__VA_ARGS__)) \
    (__VA_ARGS__)

// 对应shell模式
// 1. 不支持动态类型识别
#define mt_json_tpl_struct(struct_name, struct_type, ...)                                                     \
    mt_field_shell(__VA_ARGS__);                                                                              \
                                                                                                              \
public:                                                                                                       \
    struct_name()  = default;                                                                                 \
    ~struct_name() = default;                                                                                 \
    /* Copy constructor. */                                                                                   \
    struct_name(const struct_type &obj_val)                                                                   \
    {                                                                                                         \
        if (this != &obj_val)                                                                                 \
        {                                                                                                     \
            mt_def_field_assign(__VA_ARGS__);                                                                 \
        }                                                                                                     \
    }                                                                                                         \
    /* Move constructor. */                                                                                   \
    struct_name(struct_type &&obj_val) noexcept                                                               \
    {                                                                                                         \
        if (this != &obj_val)                                                                                 \
        {                                                                                                     \
            mt_def_field_assign(__VA_ARGS__);                                                                 \
        }                                                                                                     \
    }                                                                                                         \
    /* Move assignment operator. */                                                                           \
    struct_type &operator=(struct_type &&obj_val) noexcept { mt_def_field_assign(__VA_ARGS__) return *this; } \
    /* Copy assignment operator. */                                                                           \
    struct_type &operator=(const struct_type &obj_val) { mt_def_field_assign(__VA_ARGS__) return *this; }     \
    bool         operator==(const struct_type &obj_val) const                                                 \
    {                                                                                                         \
        bool ret_val = true;                                                                                  \
        mt_def_field_equal(__VA_ARGS__) return ret_val;                                                       \
    }                                                                                                         \
    bool Encode(mt::json::allocator_t &alloc, rapidjson::Value &json_val) const                               \
    {                                                                                                         \
        do                                                                                                    \
        {                                                                                                     \
            json_val.SetObject();                                                                             \
            mt_def_field_encode(__VA_ARGS__) return true;                                                     \
        } while (0);                                                                                          \
        return false;                                                                                         \
    }                                                                                                         \
    bool Decode(const rapidjson::Value &json_val)                                                             \
    {                                                                                                         \
        do                                                                                                    \
        {                                                                                                     \
            mt_def_field_decode(__VA_ARGS__) return true;                                                     \
        } while (0);                                                                                          \
        return false;                                                                                         \
    }                                                                                                         \
    const char *FieldsMapping(const char *init_field) const { return init_field; }                            \
    }                                                                                                         \
    ;                                                                                                         \
    static bool Encode(const struct_type &obj_val, mt::json::allocator_t &alloc, rapidjson::Value &json_val)  \
    {                                                                                                         \
        return obj_val.Encode(alloc, json_val);                                                               \
    }                                                                                                         \
    static bool Decode(const rapidjson::Value &json_val, struct_type &obj_val)                                \
    {                                                                                                         \
        return obj_val.Decode(json_val);

#define mt_json_struct(name, ...) mt_json_tpl_struct(name, name, __VA_ARGS__)

//
#define mt_struct_begin(name)               \
    struct name : public mt::json::MtStruct \
    {
#define mt_struct_end(name, ...)                                                                            \
public:                                                                                                     \
    name &operator=(const name &obj_val) { mt_def_field_assign(__VA_ARGS__) return *this; }                 \
    bool  operator==(const name &obj_val) const                                                             \
    {                                                                                                       \
        bool ret_val = true;                                                                                \
        mt_def_field_equal(__VA_ARGS__) return ret_val;                                                     \
    }                                                                                                       \
    virtual const std::map<std::string, std::string> &GetFieldsMapping() const { return fields_mapping_; }; \
    bool Encode(mt::json::allocator_t &alloc, rapidjson::Value &json_val) const                             \
    {                                                                                                       \
        do                                                                                                  \
        {                                                                                                   \
            json_val.SetObject();                                                                           \
            mt_def_field_encode(__VA_ARGS__) return true;                                                   \
        } while (0);                                                                                        \
        return false;                                                                                       \
    }                                                                                                       \
    bool Decode(const rapidjson::Value &json_val)                                                           \
    {                                                                                                       \
        do                                                                                                  \
        {                                                                                                   \
            mt_def_field_decode(__VA_ARGS__) return true;                                                   \
        } while (0);                                                                                        \
        return false;                                                                                       \
    }                                                                                                       \
    }                                                                                                       \
    ;                                                                                                       \
    static bool Encode(const name &obj_val, mt::json::allocator_t &alloc, rapidjson::Value &json_val)       \
    {                                                                                                       \
        return obj_val.Encode(alloc, json_val);                                                             \
    }                                                                                                       \
    static bool Decode(const rapidjson::Value &json_val, name &obj_val) { return obj_val.Decode(json_val); }

#endif  // MT_JSON_TYPE_H_
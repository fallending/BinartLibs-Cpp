#include <iostream>
#include <array>
#include <vector>
#include <map>

#ifndef MT_JSON_TYPE_H__
#define MT_JSON_TYPE_H__

// ----------------------------------
// Meta macro
// ----------------------------------

#define mt_macro_first_(A, ...) A
#define mt_macro_first(...) mt_macro_first_(__VA_ARGS__, 0)

#define mt_macro_concat_(A, B) A##B
#define mt_macro_concat(A, B) mt_macro_concat_(A, B)

// 偏移取数
#define mt_macro_at16(                                                         \
    _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, ...) \
    mt_macro_first(__VA_ARGS__)
#define mt_macro_at(N, ...) mt_macro_concat(mt_macro_at, N)(__VA_ARGS__)

#define mt_macro_count(...)  \
    mt_macro_at(16,          \
                __VA_ARGS__, \
                16,          \
                15,          \
                14,          \
                13,          \
                12,          \
                11,          \
                10,          \
                9,           \
                8,           \
                7,           \
                6,           \
                5,           \
                4,           \
                3,           \
                2,           \
                1)
#define mt_macro_count_dec(...) \
    mt_macro_at(16,             \
                __VA_ARGS__,    \
                15,             \
                14,             \
                13,             \
                12,             \
                11,             \
                10,             \
                9,              \
                8,              \
                7,              \
                6,              \
                5,              \
                4,              \
                3,              \
                2,              \
                1,              \
                0)  // 总参数个数减一

#define mt_macro_join0(...)
#define mt_macro_join1(A) A
#define mt_macro_join2(A, B) A##____##B
#define mt_macro_join3(A, B, C) A##____##B##____##C
#define mt_macro_join4(A, B, C, D) A##____##B##____##C##____##D
#define mt_macro_join5(A, B, C, D, E) A##____##B##____##C##____##D##____##E
#define mt_macro_join6(A, B, C, D, E, F) \
    A##____##B##____##C##____##D##____##E##____##F
#define mt_macro_join7(A, B, C, D, E, F, G) \
    A##____##B##____##C##____##D##____##E##____##F##____##G
#define mt_macro_join8(A, B, C, D, E, F, G, H) \
    A##____##B##____##C##____##D##____##E##____##F##____##G##____##H
#define mt_macro_join(...) \
    mt_macro_concat(mt_macro_join, mt_macro_count(__VA_ARGS__))(__VA_ARGS__)

#define mt_macro_cstr(A) mt_macro_cstr_(A)
#define mt_macro_cstr_(A) #A

// ----------------------------------
// Macros Customized
// ----------------------------------

#undef mt_invoke
#define mt_invoke(block, ...)   \
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
protected:
    // 字段映射
    std::map<std::string, std::string>                fields_mapping_;
    virtual const std::map<std::string, std::string> &get_fields_mapping() const
    {
        return fields_mapping_;
    };
    const char *fields_mapping(const char *init_field) const
    {
        if (this->get_fields_mapping().count(init_field) >
            0) /* init_field 映射到 out_field */
        {
            try
            {
                const std::string &out_field_str =
                    (this->get_fields_mapping()).at(init_field);

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
    virtual const std::vector<std::string> &get_fields_blacklist() const
    {
        return fields_blacklist_;
    };
    bool is_field_blocked(const char *init_field) const
    {
        bool                            ret_val = false;
        const std::vector<std::string> &blacklist =
            this->get_fields_blacklist();
        if (std::count(blacklist.begin(), blacklist.end(), init_field) > 0)
        {
            ret_val = true;
        }
        return ret_val;
    }

public:
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
#define mt_fields_mapping \
private:                  \
    std::map<std::string, std::string> fields_mapping_

/**
 * @brief 字段黑名单
 * @example mt_fields_blacklist = {"string", "val"};
 */
#define mt_fields_blacklist \
private:                    \
    std::vector<std::string> fields_blacklist_

/**
 * @brief 字段定义
 *
 */
#define mt_field(type, field)                          \
public:                                                \
    type field;                                        \
    void skip_##field() { __skip_##field = true; }     \
    bool has_##field() const { return __has_##field; } \
                                                       \
private:                                               \
    bool        __skip_##field;                        \
    bool        __has_##field;                         \
    std::string __typeof_##field;                      \
    void        init_##field()                         \
    {                                                  \
        __skip_##field   = false;                      \
        __has_##field    = true;                       \
        __typeof_##field = #type;                      \
    }

#define mt_field_shell_1(field)                                   \
public:                                                           \
    void skip_##field() { __skip_##field = true; }                \
    bool has_##field() const { return __has_##field; }            \
                                                                  \
private:                                                          \
    bool        __skip_##field;                                   \
    bool        __has_##field;                                    \
    std::string __typeof_##field /*shell模式不支持动态类型识别*/; \
    void        init_##field()                                    \
    {                                                             \
        __skip_##field = false;                                   \
        __has_##field  = true;                                    \
    }

#define mt_field_shell_2(a, ...)                                               \
    mt_macro_concat(mt_field_shell_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_shell_1(a)
#define mt_field_shell_3(a, ...)                                               \
    mt_macro_concat(mt_field_shell_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_shell_1(a)
#define mt_field_shell_4(a, ...)                                               \
    mt_macro_concat(mt_field_shell_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_shell_1(a)
#define mt_field_shell_5(a, ...)                                               \
    mt_macro_concat(mt_field_shell_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_shell_1(a)
#define mt_field_shell_6(a, ...)                                               \
    mt_macro_concat(mt_field_shell_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_shell_1(a)
#define mt_field_shell_7(a, ...)                                               \
    mt_macro_concat(mt_field_shell_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_shell_1(a)
#define mt_field_shell_8(a, ...)                                               \
    mt_macro_concat(mt_field_shell_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_shell_1(a)
#define mt_field_shell_9(a, ...)                                               \
    mt_macro_concat(mt_field_shell_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_shell_1(a)
#define mt_field_shell_10(a, ...)                                              \
    mt_macro_concat(mt_field_shell_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_shell_1(a)
#define mt_field_shell_11(a, ...)                                              \
    mt_macro_concat(mt_field_shell_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_shell_1(a)
#define mt_field_shell_12(a, ...)                                              \
    mt_macro_concat(mt_field_shell_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_shell_1(a)
#define mt_field_shell_13(a, ...)                                              \
    mt_macro_concat(mt_field_shell_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_shell_1(a)
#define mt_field_shell_14(a, ...)                                              \
    mt_macro_concat(mt_field_shell_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_shell_1(a)
#define mt_field_shell_15(a, ...)                                              \
    mt_macro_concat(mt_field_shell_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_shell_1(a)
#define mt_field_shell_16(a, ...)                                              \
    mt_macro_concat(mt_field_shell_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_shell_1(a)

#define mt_field_shell(...) \
    mt_macro_concat(mt_field_shell_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__)

// Field init

#define mt_field_init_1(a) init_##a();
#define mt_field_init_2(a, ...)                                               \
    mt_macro_concat(mt_field_init_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_init_1(a)
#define mt_field_init_3(a, ...)                                               \
    mt_macro_concat(mt_field_init_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_init_1(a)
#define mt_field_init_4(a, ...)                                               \
    mt_macro_concat(mt_field_init_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_init_1(a)
#define mt_field_init_5(a, ...)                                               \
    mt_macro_concat(mt_field_init_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_init_1(a)
#define mt_field_init_6(a, ...)                                               \
    mt_macro_concat(mt_field_init_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_init_1(a)
#define mt_field_init_7(a, ...)                                               \
    mt_macro_concat(mt_field_init_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_init_1(a)
#define mt_field_init_8(a, ...)                                               \
    mt_macro_concat(mt_field_init_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_init_1(a)
#define mt_field_init_9(a, ...)                                               \
    mt_macro_concat(mt_field_init_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_init_1(a)
#define mt_field_init_10(a, ...)                                              \
    mt_macro_concat(mt_field_init_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_init_1(a)
#define mt_field_init_11(a, ...)                                              \
    mt_macro_concat(mt_field_init_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_init_1(a)
#define mt_field_init_12(a, ...)                                              \
    mt_macro_concat(mt_field_init_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_init_1(a)
#define mt_field_init_13(a, ...)                                              \
    mt_macro_concat(mt_field_init_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_init_1(a)
#define mt_field_init_14(a, ...)                                              \
    mt_macro_concat(mt_field_init_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_init_1(a)
#define mt_field_init_15(a, ...)                                              \
    mt_macro_concat(mt_field_init_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_init_1(a)
#define mt_field_init_16(a, ...)                                              \
    mt_macro_concat(mt_field_init_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__) \
        mt_field_init_1(a)

#define mt_field_init(...) \
    mt_macro_concat(mt_field_init_, mt_macro_count(__VA_ARGS__))(__VA_ARGS__)

// Field encode

#define mt_def_field_encode_1(a)                                         \
    if (!__skip_##a &&                                                   \
        !mt::json::encode_field(a, fields_mapping(#a), alloc, json_val)) \
        break;
#define mt_def_field_encode_2(a, ...)                                   \
    mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_3(a, ...)                                   \
    mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_4(a, ...)                                   \
    mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_5(a, ...)                                   \
    mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_6(a, ...)                                   \
    mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_7(a, ...)                                   \
    mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_8(a, ...)                                   \
    mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_9(a, ...)                                   \
    mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_10(a, ...)                                  \
    mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_11(a, ...)                                  \
    mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_12(a, ...)                                  \
    mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_13(a, ...)                                  \
    mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_14(a, ...)                                  \
    mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_15(a, ...)                                  \
    mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_encode_1(a)
#define mt_def_field_encode_16(a, ...)                                  \
    mt_macro_concat(mt_def_field_encode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_encode_1(a)

#define mt_def_field_encode(...)          \
    mt_macro_concat(mt_def_field_encode_, \
                    mt_macro_count(__VA_ARGS__))(__VA_ARGS__)

// Field decode

#define mt_def_field_decode_1(a)                                             \
    if (!mt::json::decode_field(json_val, fields_mapping(#a), a, __has_##a)) \
        break;
#define mt_def_field_decode_2(a, ...)                                   \
    mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_3(a, ...)                                   \
    mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_4(a, ...)                                   \
    mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_5(a, ...)                                   \
    mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_6(a, ...)                                   \
    mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_7(a, ...)                                   \
    mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_8(a, ...)                                   \
    mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_9(a, ...)                                   \
    mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_10(a, ...)                                  \
    mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_11(a, ...)                                  \
    mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_12(a, ...)                                  \
    mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_13(a, ...)                                  \
    mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_14(a, ...)                                  \
    mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_15(a, ...)                                  \
    mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_decode_1(a)
#define mt_def_field_decode_16(a, ...)                                  \
    mt_macro_concat(mt_def_field_decode_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_decode_1(a)

#define mt_def_field_decode(...)          \
    mt_macro_concat(mt_def_field_decode_, \
                    mt_macro_count(__VA_ARGS__))(__VA_ARGS__)

// Field assign

#define mt_def_field_assign_1(a) this->a = obj_val.a;
#define mt_def_field_assign_2(a, ...)                                   \
    mt_macro_concat(mt_def_field_assign_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_3(a, ...)                                   \
    mt_macro_concat(mt_def_field_assign_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_4(a, ...)                                   \
    mt_macro_concat(mt_def_field_assign_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_5(a, ...)                                   \
    mt_macro_concat(mt_def_field_assign_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_6(a, ...)                                   \
    mt_macro_concat(mt_def_field_assign_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_7(a, ...)                                   \
    mt_macro_concat(mt_def_field_assign_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_8(a, ...)                                   \
    mt_macro_concat(mt_def_field_assign_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_9(a, ...)                                   \
    mt_macro_concat(mt_def_field_assign_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_10(a, ...)                                  \
    mt_macro_concat(mt_def_field_assign_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_11(a, ...)                                  \
    mt_macro_concat(mt_def_field_assign_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_12(a, ...)                                  \
    mt_macro_concat(mt_def_field_assign_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_13(a, ...)                                  \
    mt_macro_concat(mt_def_field_assign_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_14(a, ...)                                  \
    mt_macro_concat(mt_def_field_assign_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_15(a, ...)                                  \
    mt_macro_concat(mt_def_field_assign_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_assign_1(a)
#define mt_def_field_assign_16(a, ...)                                  \
    mt_macro_concat(mt_def_field_assign_, mt_macro_count(__VA_ARGS__))( \
        __VA_ARGS__) mt_def_field_assign_1(a)

#define mt_def_field_assign(...)          \
    mt_macro_concat(mt_def_field_assign_, \
                    mt_macro_count(__VA_ARGS__))(__VA_ARGS__)

// Field equal

#define mt_def_field_equal_1(a)              \
    if (!(this->a == obj_val.a))             \
    { /*printf("%s is not equally\n", #a);*/ \
        return false;                        \
    }
#define mt_def_field_equal_2(a, ...)                           \
    mt_macro_concat(mt_def_field_equal_,                       \
                    mt_macro_count(__VA_ARGS__))(__VA_ARGS__); \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_3(a, ...)                           \
    mt_macro_concat(mt_def_field_equal_,                       \
                    mt_macro_count(__VA_ARGS__))(__VA_ARGS__); \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_4(a, ...)                           \
    mt_macro_concat(mt_def_field_equal_,                       \
                    mt_macro_count(__VA_ARGS__))(__VA_ARGS__); \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_5(a, ...)                           \
    mt_macro_concat(mt_def_field_equal_,                       \
                    mt_macro_count(__VA_ARGS__))(__VA_ARGS__); \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_6(a, ...)                           \
    mt_macro_concat(mt_def_field_equal_,                       \
                    mt_macro_count(__VA_ARGS__))(__VA_ARGS__); \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_7(a, ...)                           \
    mt_macro_concat(mt_def_field_equal_,                       \
                    mt_macro_count(__VA_ARGS__))(__VA_ARGS__); \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_8(a, ...)                           \
    mt_macro_concat(mt_def_field_equal_,                       \
                    mt_macro_count(__VA_ARGS__))(__VA_ARGS__); \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_9(a, ...)                           \
    mt_macro_concat(mt_def_field_equal_,                       \
                    mt_macro_count(__VA_ARGS__))(__VA_ARGS__); \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_10(a, ...)                          \
    mt_macro_concat(mt_def_field_equal_,                       \
                    mt_macro_count(__VA_ARGS__))(__VA_ARGS__); \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_11(a, ...)                          \
    mt_macro_concat(mt_def_field_equal_,                       \
                    mt_macro_count(__VA_ARGS__))(__VA_ARGS__); \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_12(a, ...)                          \
    mt_macro_concat(mt_def_field_equal_,                       \
                    mt_macro_count(__VA_ARGS__))(__VA_ARGS__); \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_13(a, ...)                          \
    mt_macro_concat(mt_def_field_equal_,                       \
                    mt_macro_count(__VA_ARGS__))(__VA_ARGS__); \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_14(a, ...)                          \
    mt_macro_concat(mt_def_field_equal_,                       \
                    mt_macro_count(__VA_ARGS__))(__VA_ARGS__); \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_15(a, ...)                          \
    mt_macro_concat(mt_def_field_equal_,                       \
                    mt_macro_count(__VA_ARGS__))(__VA_ARGS__); \
    mt_def_field_equal_1(a)
#define mt_def_field_equal_16(a, ...)                          \
    mt_macro_concat(mt_def_field_equal_,                       \
                    mt_macro_count(__VA_ARGS__))(__VA_ARGS__); \
    mt_def_field_equal_1(a)

#define mt_def_field_equal(...)          \
    mt_macro_concat(mt_def_field_equal_, \
                    mt_macro_count(__VA_ARGS__))(__VA_ARGS__)

// 对应shell模式
// 1. 不支持动态类型识别
#define mt_json_struct(name, ...)                                         \
    mt_field_shell(__VA_ARGS__);                                          \
                                                                          \
public:                                                                   \
    const char *fields_mapping(const char *init_field) const              \
    {                                                                     \
        return init_field;                                                \
    }                                                                     \
    name &operator=(const name &obj_val)                                  \
    {                                                                     \
        mt_def_field_assign(__VA_ARGS__) return *this;                    \
    }                                                                     \
    bool operator==(const name &obj_val) const                            \
    {                                                                     \
        mt_def_field_equal(__VA_ARGS__) return true;                      \
    }                                                                     \
    bool encode(mt::json::allocator_t &alloc, rapidjson::Value &json_val) \
        const                                                             \
    {                                                                     \
        do                                                                \
        {                                                                 \
            json_val.SetObject();                                         \
            mt_def_field_encode(__VA_ARGS__) return true;                 \
        } while (0);                                                      \
        return false;                                                     \
    }                                                                     \
    bool decode(const rapidjson::Value &json_val)                         \
    {                                                                     \
        do                                                                \
        {                                                                 \
            mt_def_field_decode(__VA_ARGS__) return true;                 \
        } while (0);                                                      \
        return false;                                                     \
    }                                                                     \
    }                                                                     \
    ;                                                                     \
    static bool encode(const name &           obj_val,                    \
                       mt::json::allocator_t &alloc,                      \
                       rapidjson::Value &     json_val)                   \
    {                                                                     \
        return obj_val.encode(alloc, json_val);                           \
    }                                                                     \
    static bool decode(const rapidjson::Value &json_val, name &obj_val)   \
    {                                                                     \
        return obj_val.decode(json_val);                                  \
    }                                                                     \
    static void mt_noop()                                                 \
    {
//
#define mt_struct_begin(name)               \
    struct name : public mt::json::MtStruct \
    {
#define mt_struct_end(name, ...)                                            \
public:                                                                     \
    name(){mt_field_init(__VA_ARGS__)} name &operator=(const name &obj_val) \
    {                                                                       \
        mt_def_field_assign(__VA_ARGS__) return *this;                      \
    }                                                                       \
    bool operator==(const name &obj_val) const                              \
    {                                                                       \
        mt_def_field_equal(__VA_ARGS__) return true;                        \
    }                                                                       \
    virtual const std::map<std::string, std::string> &get_fields_mapping()  \
        const                                                               \
    {                                                                       \
        return fields_mapping_;                                             \
    };                                                                      \
    bool encode(mt::json::allocator_t &alloc, rapidjson::Value &json_val)   \
        const                                                               \
    {                                                                       \
        do                                                                  \
        {                                                                   \
            json_val.SetObject();                                           \
            mt_def_field_encode(__VA_ARGS__) return true;                   \
        } while (0);                                                        \
        return false;                                                       \
    }                                                                       \
    bool decode(const rapidjson::Value &json_val)                           \
    {                                                                       \
        do                                                                  \
        {                                                                   \
            mt_def_field_decode(__VA_ARGS__) return true;                   \
        } while (0);                                                        \
        return false;                                                       \
    }                                                                       \
    }                                                                       \
    ;                                                                       \
    static bool encode(const name &           obj_val,                      \
                       mt::json::allocator_t &alloc,                        \
                       rapidjson::Value &     json_val)                     \
    {                                                                       \
        return obj_val.encode(alloc, json_val);                             \
    }                                                                       \
    static bool decode(const rapidjson::Value &json_val, name &obj_val)     \
    {                                                                       \
        return obj_val.decode(json_val);                                    \
    }

#endif  // MT_JSON_TYPE_H__
/*
 * @Author: your name
 * @Date: 2021-03-02 10:19:36
 * @LastEditTime: 2021-03-02 15:11:04
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: /slothjson/src/me_test_opt.cpp
 */

#include "me_test_opt.h"

namespace mtjson {

    mt_def_struct(metest_object_t, isStarted, mak, th, len, length, amount, str_val, vec, dict)

// bool metest_object_t::encode(allocator_t& alloc, rapidjson::Value& json_val) const
// {
//     do
//     {
//         json_val.SetObject();
//         if (!__skip_isStarted && !encode_field(isStarted, "isStarted", alloc, json_val)) break;
//         if (!__skip_mak && !encode_field(mak, "mak", alloc, json_val)) break;
//         if (!__skip_th && !encode_field(th, "th", alloc, json_val)) break;
//         if (!__skip_len && !encode_field(len, "len", alloc, json_val)) break;
//         if (!__skip_length && !encode_field(length, "length", alloc, json_val)) break;
//         if (!__skip_amount && !encode_field(amount, "amount", alloc, json_val)) break;
//         if (!__skip_vec && !encode_field(vec, "vec", alloc, json_val)) break;
//         if (!__skip_dict && !encode_field(dict, "dict", alloc, json_val)) break;
//         if (!__skip_str_val && !encode_field(str_val, "str_val", alloc, json_val)) break;

//         return true;
//     } while (0);

//     return false;
// }

// bool metest_object_t::decode(const rapidjson::Value& json_val)
// {
//     do
//     {
//         if (!decode_field(json_val, "isStarted", isStarted, __json_has_isStarted)) break;
//         if (!decode_field(json_val, "mak", mak, __json_has_mak)) break;
//         if (!decode_field(json_val, "fin", fin, __json_has_fin)) break;
//         if (!decode_field(json_val, "th", th, __json_has_th)) break;
//         if (!decode_field(json_val, "sh", sh, __json_has_sh)) break;
//         if (!decode_field(json_val, "len", len, __json_has_len)) break;
//         if (!decode_field(json_val, "count", count, __json_has_count)) break;
//         if (!decode_field(json_val, "length", length, __json_has_length)) break;
//         if (!decode_field(json_val, "age", age, __json_has_age)) break;
//         if (!decode_field(json_val, "amountd", amountd, __json_has_amountd)) break;
//         if (!decode_field(json_val, "amount", amount, __json_has_amount)) break;
//         if (!decode_field(json_val, "str", str, __json_has_str)) break;
//         if (!decode_field(json_val, "vec", vec, __json_has_vec)) break;
//         if (!decode_field(json_val, "dict", dict, __json_has_dict)) break;

//         return true;
//     } while (0);

//     return false;
// }

// bool encode(const metest_object_t& obj_val, allocator_t& alloc, rapidjson::Value& json_val)
// {
//     return obj_val.encode(alloc, json_val);
// }

// bool decode(const rapidjson::Value& json_val, metest_object_t& obj_val)
// {
//     return obj_val.decode(json_val);
// }

} // namespace mtjson
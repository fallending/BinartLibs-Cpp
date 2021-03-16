/*
 * @Author: your name
 * @Date: 2021-03-02 10:19:36
 * @LastEditTime: 2021-03-02 15:24:14
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /slothjson/src/me_test copy 2.h
 */

#ifndef __me_test_20210221003122_h__
#define __me_test_20210221003122_h__

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

#endif // __me_test_20210221003122_h__
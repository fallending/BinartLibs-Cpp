/*
 * @Author: your name
 * @Date: 2021-02-20 19:01:39
 * @LastEditTime: 2021-03-02 15:23:05
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /slothjson/include/jsonserializer.cpp
 */

// Mutations type json

#include "mtjson.h"

// 抽象json序列化的基类
// 实现一个基于rapidjson的序列化器

// 如何支持：fields mapping
//     + (nullable NSDictionary<NSString *, id> *)modelCustomPropertyMapper
// {
//     return @{@"avatarUrl" : @"avatar",
//              @"wxNickName" : @"userName",
//              @"accountId" : @"merchantId",
//              @"unionId" : @"unionID",
//              @"userid":@"userID",
//              };
// }

// 如何支持：model embeded
//     + (NSDictionary *)modelContainerPropertyGenericClass {
//     return @{@"areas" : [AreaModel class]};
// }

// 如何支持：skip fields
//     + (NSArray *)modelPropertyBlacklist 
// {
//     return @[@"avatarUrl", @"accountId"];
// }

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

// impl
namespace mt
{
namespace json
{
// std::string
bool Encode(const std::string &obj_val,
            allocator_t &      alloc,
            rapidjson::Value & json_val)
{
    json_val.SetString(rapidjson::StringRef(obj_val.c_str()));
    return true;
}
bool Decode(const rapidjson::Value &json_val, std::string &obj_val)
{
    if (json_val.IsString())
    {
        obj_val = json_val.GetString();
        return true;
    }
    return false;
}
// int32_t
bool Encode(const int32_t &   obj_val,
            allocator_t &     alloc,
            rapidjson::Value &json_val)
{
    json_val.SetInt(obj_val);
    return true;
}
bool Decode(const rapidjson::Value &json_val, int32_t &obj_val)
{
    if (json_val.IsInt())
    {
        obj_val = json_val.GetInt();
        return true;
    }
    return false;
}
// uint32_t
bool Encode(const uint32_t &  obj_val,
            allocator_t &     alloc,
            rapidjson::Value &json_val)
{
    json_val.SetUint(obj_val);
    return true;
}
bool Decode(const rapidjson::Value &json_val, uint32_t &obj_val)
{
    bool ret_val = false;
    if (json_val.IsInt())
    {
        obj_val = json_val.GetInt();
        ret_val = true;
    }
    else if (json_val.IsUint())
    {
        obj_val = json_val.GetUint();
        ret_val = true;
    }
    return ret_val;
}
// double
bool Encode(const double &    obj_val,
            allocator_t &     alloc,
            rapidjson::Value &json_val)
{
    json_val.SetDouble(obj_val);
    return true;
}
bool Decode(const rapidjson::Value &json_val, double &obj_val)
{
    if (json_val.IsNumber())
    {
        obj_val = json_val.GetDouble();
        return true;
    }
    return false;
}

// int64_t & uint64_t
bool Encode(const int64_t &   obj_val,
            allocator_t &     alloc,
            rapidjson::Value &json_val)
{
    json_val.SetInt64(obj_val);
    return true;
}
bool Decode(const rapidjson::Value &json_val, int64_t &obj_val)
{
    bool ret_val = false;
    if (json_val.IsInt64())
    {
        obj_val = json_val.GetInt64();
        ret_val = true;
    }
    else if (json_val.IsInt())
    {
        obj_val = json_val.GetInt();
        ret_val = true;
    }
    else if (json_val.IsUint())
    {
        obj_val = json_val.GetUint();
        ret_val = true;
    }
    return ret_val;
}
bool Encode(const uint64_t &  obj_val,
            allocator_t &     alloc,
            rapidjson::Value &json_val)
{
    json_val.SetUint64(obj_val);
    return true;
}
bool Decode(const rapidjson::Value &json_val, uint64_t &obj_val)
{
    bool ret_val = false;
    if (json_val.IsUint64())
    {
        obj_val = json_val.GetUint64();
        ret_val = true;
    }
    else if (json_val.IsInt())
    {
        obj_val = json_val.GetInt();
        ret_val = true;
    }
    else if (json_val.IsUint())
    {
        obj_val = json_val.GetUint();
        ret_val = true;
    }
    return ret_val;
}
}  // namespace json

namespace json
{
// int8_t & uint8_t
bool Encode(const int8_t &    obj_val,
            allocator_t &     alloc,
            rapidjson::Value &json_val)
{
    auto tmp_obj_val =
        static_cast<int32_t>(static_cast<unsigned char>(obj_val));
    return Encode(tmp_obj_val, alloc, json_val);
}
bool Decode(const rapidjson::Value &json_val, int8_t &obj_val)
{
    int32_t tmp_obj_val = 0;
    if (!Decode(json_val, tmp_obj_val))
    {
        return false;
    }
    obj_val = static_cast<int8_t>(tmp_obj_val);
    return true;
}

bool Encode(const uint8_t &   obj_val,
            allocator_t &     alloc,
            rapidjson::Value &json_val)
{
    auto tmp_obj_val = static_cast<uint32_t>(obj_val);
    return Encode(tmp_obj_val, alloc, json_val);
}
bool Decode(const rapidjson::Value &json_val, uint8_t &obj_val)
{
    uint32_t tmp_obj_val = 0;
    if (!Decode(json_val, tmp_obj_val))
    {
        return false;
    }
    obj_val = static_cast<uint8_t>(tmp_obj_val);
    return true;
}
// int16_t & uint16_t
bool Encode(const int16_t &   obj_val,
            allocator_t &     alloc,
            rapidjson::Value &json_val)
{
    auto tmp_obj_val = static_cast<int32_t>(obj_val);
    return Encode(tmp_obj_val, alloc, json_val);
}
bool Decode(const rapidjson::Value &json_val, int16_t &obj_val)
{
    int32_t tmp_obj_val = 0;
    if (!Decode(json_val, tmp_obj_val))
    {
        return false;
    }
    obj_val = static_cast<int16_t>(tmp_obj_val);
    return true;
}

bool Encode(const uint16_t &  obj_val,
            allocator_t &     alloc,
            rapidjson::Value &json_val)
{
    auto tmp_obj_val = static_cast<uint32_t>(obj_val);
    return Encode(tmp_obj_val, alloc, json_val);
}
bool Decode(const rapidjson::Value &json_val, uint16_t &obj_val)
{
    uint32_t tmp_obj_val = 0;
    if (!Decode(json_val, tmp_obj_val))
    {
        return false;
    }
    obj_val = static_cast<uint16_t>(tmp_obj_val);
    return true;
}

// float
bool Encode(const float &     obj_val,
            allocator_t &     alloc,
            rapidjson::Value &json_val)
{
    double tmp_obj_val = obj_val;
    return Encode(tmp_obj_val, alloc, json_val);
}
bool Decode(const rapidjson::Value &json_val, float &obj_val)
{
    double tmp_obj_val = 0;
    if (!Decode(json_val, tmp_obj_val))
    {
        return false;
    }
    obj_val = static_cast<float>(tmp_obj_val);
    return true;
}

}  // namespace json

namespace json
{
template <typename src_t, typename dst_t>
bool Convert(const src_t &src, dst_t &dst)
{
    if (src.IsBool())
    {
        dst.SetBool(src.GetBool());
    }
    else if (src.IsInt())
    {
        dst.SetInt(src.GetInt());
    }
    else if (src.IsUint())
    {
        dst.SetUint(src.GetUint());
    }
    else if (src.IsInt64())
    {
        dst.SetInt64(src.GetInt64());
    }
    else if (src.IsUint64())
    {
        dst.SetUint64(src.GetUint64());
    }
    else if (src.IsDouble())
    {
        dst.SetDouble(src.GetDouble());
    }
    else if (src.IsString())
    {
        dst.SetString(rapidjson::StringRef(src.GetString()));
    }
    else if (src.IsNull())
    {
        dst.SetNull();
    }
    else
    {
        return false;
    }
    return true;
}

bool EncodeDocument(rapidjson::Value &src, rapidjson::Document &dst)
{
    rapidjson::Document::AllocatorType &allocator = dst.GetAllocator();
    if (src.IsArray())
    {
        dst.SetArray();
        rapidjson::SizeType size = src.Size();
        for (rapidjson::SizeType i = 0; i < size; ++i)
        {
            dst.PushBack(src[i].Move(), allocator);
        }
        return true;
    }
    if (src.IsObject())  // seven: should not IsObject & IsArray, so replace
                         // `else if` with `if`
    {
        dst.SetObject();
        for (rapidjson::Value::MemberIterator it = src.MemberBegin();
             it != src.MemberEnd();
             ++it)
        {
            dst.AddMember(rapidjson::StringRef(it->name.GetString()),
                          it->value.Move(),
                          allocator);
        }
        return true;
    }
    return Convert(src, dst);
}
bool DecodeDocument(rapidjson::Document &src, rapidjson::Value &dst)
{
    rapidjson::Document::AllocatorType &allocator = src.GetAllocator();
    if (src.IsArray())
    {
        dst.SetArray();
        rapidjson::SizeType size = src.Size();
        for (rapidjson::SizeType i = 0; i < size; ++i)
        {
            dst.PushBack(src[i].Move(), allocator);
        }
        return true;
    }
    if (src.IsObject())  // seven: should not IsObject & IsArray, so replace
                         // `else if` with `if`
    {
        dst.SetObject();
        for (rapidjson::Document::MemberIterator it = src.MemberBegin();
             it != src.MemberEnd();
             ++it)
        {
            dst.AddMember(rapidjson::StringRef(it->name.GetString()),
                          it->value.Move(),
                          allocator);
        }
        return true;
    }
    return Convert(src, dst);
}

// char *Load(const char *path)
// {
//     if (path == nullptr)
//     {
//         return nullptr;
//     }
//     FILE *f = fopen(path, "rb");
//     if (f == nullptr)
//     {
//         return nullptr;
//     }
//     fseek(f, 0, SEEK_END);
//     int64_t len = ftell(f);
//     fseek(f, 0, SEEK_SET);
//     char *data = (char *)malloc(len + 1);
//     fread(data, 1, len, f);
//     data[len] = '\0';
//     fclose(f);
//     return data;
// }

// JsonLoader::JsonLoader(const char *path) { data_ = Load(path); }
// JsonLoader::~JsonLoader()
// {
//     if (data_ != nullptr)
//     {
//         free(data_);
//         data_ = nullptr;
//     }
// }
// const char *JsonLoader::c_str() { return data_; }

}  // namespace json

}  // namespace mt

#ifndef MT_JSON_H_
#define MT_JSON_H_

#ifdef WIN32
#pragma warning(disable : 4305)
#pragma warning(disable : 4996)
#endif  // WIN32

#include <document.h>
#include <cfloat>
#include <prettywriter.h>
#include <rapidjson.h>
#include <cstdint>
#include <stringbuffer.h>
#include <writer.h>

#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

namespace mt
{
namespace json
{
using allocator_t = rapidjson::Document::AllocatorType;

// MARK: - bool

inline bool Encode(const bool &      obj_val,
                   allocator_t &     alloc,
                   rapidjson::Value &json_val)
{
    json_val.SetBool(obj_val);
    return true;
};
inline bool Decode(const rapidjson::Value &json_val, bool &obj_val)
{
    bool ret_val = false;
    if (json_val.IsBool())
    {
        obj_val = json_val.GetBool();
        ret_val = true;
    }
    else if (json_val.IsInt())
    {
        int tmp = json_val.GetInt();
        obj_val = tmp == 0;
        ret_val = true;
    }
    return ret_val;
};

// MARK: - std::string
bool Encode(const std::string &obj_val,
            allocator_t &      alloc,
            rapidjson::Value & json_val);
bool Decode(const rapidjson::Value &json_val, std::string &obj_val);

// MARK: - int32_t
bool Encode(const int32_t &   obj_val,
            allocator_t &     alloc,
            rapidjson::Value &json_val);
bool Decode(const rapidjson::Value &json_val, int32_t &obj_val);

// MARK: - uint32_t
bool Encode(const uint32_t &  obj_val,
            allocator_t &     alloc,
            rapidjson::Value &json_val);
bool Decode(const rapidjson::Value &json_val, uint32_t &obj_val);

// MARK: - double
bool Encode(const double &    obj_val,
            allocator_t &     alloc,
            rapidjson::Value &json_val);
bool Decode(const rapidjson::Value &json_val, double &obj_val);

// MARK: - int64_t
bool Encode(const int64_t &   obj_val,
            allocator_t &     alloc,
            rapidjson::Value &json_val);
bool Decode(const rapidjson::Value &json_val, int64_t &obj_val);

// MARK: - uint64_t
bool Encode(const uint64_t &  obj_val,
            allocator_t &     alloc,
            rapidjson::Value &json_val);
bool Decode(const rapidjson::Value &json_val, uint64_t &obj_val);

// MARK: - int8_t as 字符
bool Encode(const int8_t &    obj_val,
            allocator_t &     alloc,
            rapidjson::Value &json_val);
bool Decode(const rapidjson::Value &json_val, int8_t &obj_val);

// MARK: - uint8_t as 字符
bool Encode(const uint8_t &   obj_val,
            allocator_t &     alloc,
            rapidjson::Value &json_val);
bool Decode(const rapidjson::Value &json_val, uint8_t &obj_val);

// MARK: - int16_t
bool Encode(const int16_t &   obj_val,
            allocator_t &     alloc,
            rapidjson::Value &json_val);
bool Decode(const rapidjson::Value &json_val, int16_t &obj_val);

// MARK: - uint16_t
bool Encode(const uint16_t &  obj_val,
            allocator_t &     alloc,
            rapidjson::Value &json_val);
bool Decode(const rapidjson::Value &json_val, uint16_t &obj_val);

// MARK: - float
bool Encode(const float &     obj_val,
            allocator_t &     alloc,
            rapidjson::Value &json_val);
bool Decode(const rapidjson::Value &json_val, float &obj_val);

template <typename T>
bool Encode(const std::vector<T> &obj_val,
            allocator_t &         alloc,
            rapidjson::Value &    json_val);
template <typename T>
bool Decode(const rapidjson::Value &json_val, std::vector<T> &obj_val);

template <typename T>
bool Encode(const std::map<std::string, T> &obj_val,
            allocator_t &                   alloc,
            rapidjson::Value &              json_val);
template <typename T>
bool Decode(const rapidjson::Value &  json_val,
            std::map<std::string, T> &obj_val);

template <typename T>
bool EncodeField(const T &         field,
                 const char *      field_name,
                 allocator_t &     alloc,
                 rapidjson::Value &json_val);
template <typename T>
bool DecodeField(const rapidjson::Value &json_val,
                 const char *            field_name,
                 T &                     field,
                 bool &                  field_in_json);

template <bool pretty, typename T>
bool Encode(const T &obj_val, std::string &json_val);
template <typename T>
bool Decode(const std::string &json_val, T &obj_val);

// template <bool pretty, typename T>
// bool Dump(const T &obj_val, const char *path);

template <typename T>
bool Load(const char *path, T &obj_val);

/////
template <typename T>
bool Encode(const std::map<std::string, T> &obj_val,
            allocator_t &                   alloc,
            rapidjson::Value &              json_val)
{
    json_val.SetObject();
    typename std::map<std::string, T>::const_iterator it;
    for (it = obj_val.begin(); it != obj_val.end(); ++it)
    {
        rapidjson::Value val;
        if (!Encode(it->second, alloc, val))
        {
            return false;
        }
        json_val.AddMember(
            rapidjson::StringRef(it->first.c_str()), val.Move(), alloc);
    }
    return true;
}
template <typename T>
bool Decode(const rapidjson::Value &json_val, std::map<std::string, T> &obj_val)
{
    if (!json_val.IsObject())
    {
        return false;
    }
    for (rapidjson::Value::ConstMemberIterator it = json_val.MemberBegin();
         it != json_val.MemberEnd();
         ++it)
    {
        T val;
        if (!Decode(it->value, val))
        {
            return false;
        }
        obj_val[it->name.GetString()] = val;
    }
    return true;
}

template <typename T>
bool Encode(const std::vector<T> &obj_val,
            allocator_t &         alloc,
            rapidjson::Value &    json_val)
{
    json_val.SetArray();
    typename std::vector<T>::const_iterator it;
    for (it = obj_val.begin(); it != obj_val.end(); ++it)
    {
        rapidjson::Value temp;
        if (!Encode(*it, alloc, temp))
        {
            return false;
        }
        json_val.PushBack(temp.Move(), alloc);
    }
    return true;
}

template <typename T>
bool Decode(const rapidjson::Value &json_val, std::vector<T> &obj_val)
{
    if (!json_val.IsArray())
    {
        return false;
    }
    rapidjson::SizeType size = json_val.Size();
    obj_val.reserve(size);

    for (rapidjson::SizeType i = 0; i < size; ++i)
    {
        T tmp_val;
        if (!Decode(json_val[i], tmp_val))
        {
            return false;
        }
        obj_val.push_back(tmp_val);
    }
    return true;
}

template <typename T>
bool EncodeField(const T &         field,
                 const char *      field_name,
                 allocator_t &     alloc,
                 rapidjson::Value &json_val)
{
    if (!field_name)
    {
        return false;
    }
    rapidjson::Value tmp_json_val;
    if (!Encode(field, alloc, tmp_json_val))
    {
        return false;
    }
    rapidjson::Value key(field_name, alloc);
    json_val.AddMember(key, tmp_json_val.Move(), alloc);
    return true;
}

template <typename T>
bool DecodeField(const rapidjson::Value &json_val,
                 const char *            field_name,
                 T &                     field,
                 bool &                  field_in_json)
{
    field_in_json = false;
    if (!json_val.IsObject() || !field_name)
    {
        return false;
    }
    if (json_val.HasMember(field_name))
    {
        field_in_json                        = true;
        const rapidjson::Value &tmp_json_val = json_val[field_name];
        if (!Decode(tmp_json_val, field))
        {
            return false;
        }
    }
    return true;
}

template <bool pretty>
struct json_writer_t;

template <>
struct json_writer_t<true>
{
    using writer_t = rapidjson::PrettyWriter<rapidjson::StringBuffer>;
};

template <>
struct json_writer_t<false>
{
    using writer_t = rapidjson::Writer<rapidjson::StringBuffer>;
};

template <bool pretty>
bool Encode(const rapidjson::Document &doc, std::string &json_val)
{
    rapidjson::StringBuffer                  buffer;
    typename json_writer_t<pretty>::writer_t writer(buffer);
    doc.Accept(writer);
    json_val = buffer.GetString();
    return true;
}

bool EncodeDocument(rapidjson::Value &dst, rapidjson::Document &src);
bool DecodeDocument(rapidjson::Document &src, rapidjson::Value &dst);

template <bool pretty, typename T>
bool Encode(const T &obj_val, std::string &json_val)
{
    rapidjson::Document doc;
    rapidjson::Value    value;
    if (!Encode(obj_val, doc.GetAllocator(), value))
    {
        return false;
    }
    if (!EncodeDocument(value, doc))
    {
        return false;
    }
    return Encode<pretty>(doc, json_val);
}

template <typename T>
bool Decode(const char *json_val, T &obj_val)
{
    rapidjson::Document doc;
    doc.Parse(json_val);
    rapidjson::Value value;
    if (!mt::json::DecodeDocument(doc, value))
    {
        return false;
    }
    return Decode(value, obj_val);
}

template <typename T>
bool Decode(const std::string &json_val, T &obj_val)
{
    return Decode(json_val.c_str(), obj_val);
}

};  // namespace json

};  // namespace mt

#include "mtjsontype.h"

#endif  // MT_JSON_H_

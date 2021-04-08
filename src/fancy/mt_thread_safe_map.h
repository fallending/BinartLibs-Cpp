#include <map>
#include <memory>
#include <mutex>

#ifndef MT_THREAD_SAFE_MAP_H_
#define MT_THREAD_SAFE_MAP_H_

namespace mt
{
namespace threadsafe
{
// thread safe map, need to free data youself
template <typename TKey, typename TValue>
class Map
{
public:
    Map() = default;

    virtual ~Map()
    {
        std::lock_guard<std::mutex> locker(mutexMap_);
        map_.clear();
    }

    bool Insert(const TKey &key, const TValue &value, bool cover = false)
    {
        std::lock_guard<std::mutex> locker(mutexMap_);

        auto find = map_.find(key);
        if (find != map_.end() && cover)
        {
            map_.erase(find);
        }

        auto result = map_.insert(std::pair<TKey, TValue>(key, value));
        return result.second;
    }

    void Remove(const TKey &key)
    {
        std::lock_guard<std::mutex> locker(mutexMap_);

        auto find = map_.find(key);
        if (find != map_.end())
        {
            map_.erase(find);
        }
    }

    bool Lookup(const TKey &key, TValue &value)
    {
        std::lock_guard<std::mutex> locker(mutexMap_);

        auto find = map_.find(key);
        if (find != map_.end())
        {
            value = (*find).second;
            return true;
        }
        return false;
    }

    int Size()
    {
        std::lock_guard<std::mutex> locker(mutexMap_);
        return map_.size();
    }

private:
    std::mutex             mutexMap_;
    std::map<TKey, TValue> map_;
};
}  // namespace threadsafe
}  // namespace mt

#endif  // MT_THREAD_SAFE_MAP_H_

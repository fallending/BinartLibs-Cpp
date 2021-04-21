
#include <vector>

#ifndef MT_MAP_
#define MT_MAP_

// https://pgon.dev/blog/posts/building-map-filter-and-reduce-in-c-with-templates-and-iterators/

namespace mt
{
template <typename T>
void ForEach(std::vector<T> &items, std::function<void(T &item)> foreach_cb)
{
    for (T item : items)
    {
        foreach_cb(item);
    }
}

template <typename T2, typename T1>
std::vector<T2> Map(std::vector<T1> &items, std::function<T2(T1 &item)> mapping_cb)
{
    std::vector<T2> mapped_vec;
    ForEach<T1>(items, [&mapped_vec, &mapping_cb](T1 &item) { mapped_vec.push_back(mapping_cb(item)); });
    return mapped_vec;
}

}  // namespace mt

#endif  // MT_MAP_
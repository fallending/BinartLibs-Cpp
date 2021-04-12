#include <string>
#include <sstream>
#include <vector>

#ifndef MT_CONTAINER_OPERATOR_H_
#define MT_CONTAINER_OPERATOR_H_

namespace mt
{
namespace container
{
namespace operating
{
// 一直喜欢python的map，filter和reduce函数，在标准C++中分别有std::transform（对应python的map），std::copy_if（对应python的filter），std::accumulate（对应python的reduce）。
template <class S, class T>
std::string Join(std::vector<T>& elems, S& delim)
{
    std::stringstream ss;

    typename std::vector<T>::iterator e = elems.begin();

    ss << *e++;

    for (; e != elems.end(); ++e)
    {
        ss << delim << *e;
    }

    return ss.str();
}

inline std::vector<std::string> Split(const std::string& s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string              token;
    std::istringstream       token_stream(s);

    while (std::getline(token_stream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}
}  // namespace operating

}  // namespace container

}  // namespace mt

#endif  // MT_CONTAINER_OPERATOR_H_
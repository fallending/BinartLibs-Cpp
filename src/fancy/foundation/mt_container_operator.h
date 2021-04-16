#include <string>
#include <sstream>
#include <vector>

// High Order Functional
// https://eloquentjavascript.net/05_higher_order.html#p_cao2fH68Tj

// std 提供的用法：

// std::transform
// Squaring a vector of integers in place:

// std::vector<int> nums{1,2,3,4};
// auto unary_op = [](int num) {return std::pow(num, 2);};
// std::transform(nums.begin(), nums.end(), nums.begin(), unary_op);
// // nums: 1, 4, 9, 16
// std::copy_if
// Filtering odd numbers only from a vector of integers:

// std::vector<int> nums{1,2,3,4};
// std::vector<int> odd_nums;
// auto pred = [](int num) {return num & 1;};
// std::copy_if(nums.begin(), nums.end(), std::back_inserter(odd_nums), pred);
// // odd_nums: 1, 3
// std::reduce
// Sum of integers in the vector starting from 0 using parallel execution model. This is really useful if, for example,
// you are doing a reduce operation on a really big list. Reckon that the binary operator in this case ("+") is
// associate and commutative, otherwise the behavior would've been non-deterministic. This is really important. The
// reduce operation is out-of-order if the execution model is not sequential. Only available since C++17.

// std::vector<int> nums{1,2,3,4};
// auto binary_op = [](int num1, int num2){return num1 + num2;};
// int result = std::reduce(std::execution::par, nums.begin(), nums.end(), 0, binary_op);
// // result: 10
// std::accumulate
// Same as reduce except it doesn't support execution model and the reduce operation is done in-order.

// std::vector<int> nums{1,2,3,4};
// auto binary_op = [](int num1, int num2){return num1 + num2;};
// int result = std::accumulate(nums.begin(), nums.end(), 0, binary_op);
// // result: 10

// 1. filter
// 2. map       -> std::transform
// 3. sort
// 4. reduce
// 5. ???

#ifndef MT_CONTAINER_OPERATOR_H_
#define MT_CONTAINER_OPERATOR_H_

namespace mt
{
namespace container
{
namespace operating
{
template <typename In>
inline std::string Stringify(In i)
{
    return std::to_string(i);
}

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

inline std::vector<std::string> Map()
{
    std::vector<std::string> v;

    return v;
}

// int op_increase (int i) { return ++i; }

// int main () {
//     std::vector<int> foo;
//     std::vector<int> bar;

//     // set some values:
//     for (int i=1; i<6; i++)
//         foo.push_back (i*10);                         // foo: 10 20 30 40 50

//     bar.resize(foo.size());                         // allocate space

//     std::transform (foo.begin(), foo.end(), bar.begin(), op_increase);
//                                                     // bar: 11 21 31 41 51

//     // std::plus adds together its two arguments:
//     std::transform (foo.begin(), foo.end(), bar.begin(), foo.begin(), std::plus<int>());
//                                                     // foo: 21 41 61 81 101

//     std::cout << "foo contains:";
//     for (std::vector<int>::iterator it=foo.begin(); it!=foo.end(); ++it)
//         std::cout << ' ' << *it;
//     std::cout << '\n';

//     return 0;
// }

// vector<int> numbers1 = {1, 5, 42, 7, 8};
// vector<int> numbers2 = {10, 7, 4, 2, 2};
// vector<int> results;
// std::transform(numbers1.begin(), numbers1.end(),
//                numbers2.begin(),
//                std::back_inserter(results),
//                [](int i, int j) {return i+j;});

template <typename InputIterator, typename OutputIterator, typename Function>
OutputIterator Map(InputIterator first1, InputIterator last1, OutputIterator result, Function op)
{
    return std::transform(first1, last1, result, op);
}

template <typename Out, typename In, typename Function>
std::vector<Out> Map(std::vector<In> input, Function func)
{
    std::vector<Out>                   output(input.size());
    typename std::vector<In>::iterator first1 = input.begin();
    typename std::vector<In>::iterator last1  = input.end();

    // typename std::back_insert_iterator<std::vector<Out>> result = std::back_inserter(output);

    typename std::vector<Out>::iterator result = output.begin();

    while (first1 != last1)
    {
        *(result) = func(*(first1++));

        std::cout << *result << std::endl;

        result++;
    }
    return output;

    // std::transform(input.begin(), input.end(), input.begin(), op);
}

// https://medium.com/@vgasparyan1995/generalizing-std-transform-8d2c41e1f958
// cpluscplus 17
// #ifdef __cplusplus17
template <typename InputIter1, typename OutputIter, typename Function, typename... InputIters>
OutputIter Map(InputIter1 first1, InputIter1 last1, OutputIter d_first, Function func, InputIters... firsts)
{
    while (first1 != last1)
    {
        *(d_first++) = func(*(first1++), *(firsts++)...);
    }
    return d_first;
}

// #include <tuple>
// #include <utility>

// template <typename InputIter1, typename ArgsTuple, size_t... I>
// decltype(auto) __transform_helper(InputIter1 first1, InputIter1 last1, ArgsTuple argsTuple,
// std::index_sequence<I...>)
// {
//     constexpr auto argsTupleSize = std::tuple_size<decltype(argsTuple)>::value;
//     auto           outputIter    = std::get<argsTupleSize - 2>(argsTuple);
//     auto           function      = std::get<argsTupleSize - 1>(argsTuple);
//     return Map(first1, last1, outputIter, function, std::get<I>(argsTuple)...);
// }

// template <typename InputIter1, typename... InputIters_OutputIter_Function>
// decltype(auto) transform(InputIter1 first1,
//                          InputIter1 last1,
//                          InputIters_OutputIter_Function... inputIters_outputIter_function)
// {
//     return __transform_helper(first1,
//                               last1,
//                               std::forward_as_tuple(inputIters_outputIter_function...),
//                               std::make_index_sequence<sizeof...(inputIters_outputIter_function) - 2>());
// }

// #include <vector>
// #include <iostream>
// #include <iterator>
// #include <algorithm>

// #include "transform.h"

// int main()
// {
//     std::vector<int> vec = { 1, 2, 3 };
//     my::transform(
//                   vec.begin(), vec.end(), // 1st range
//                   vec.begin(),            // 2nd range
//                   vec.begin(),            // 3rd range
//                   vec.begin(),            // 4th range
//                   vec.begin(),            // 5th range
//                   vec.begin(),            // output range
//                   [] (auto p1, auto p2, auto p3, auto p4, auto p5) { return p1 + p2 + p3 + p4 + p5; });
//     std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " ")); // must be { 5, 10, 15 }
// }

// #endif

void Append() {}

}  // namespace operating

}  // namespace container

}  // namespace mt

#endif  // MT_CONTAINER_OPERATOR_H_
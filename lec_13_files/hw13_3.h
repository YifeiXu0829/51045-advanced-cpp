#pragma once

#include <type_traits>
#include <utility>
#include <vector>
#include <array>

namespace hw13
{

using namespace std;

template <typename T, typename U>
struct product_type
{
    using type =  decltype( declval<T>() * declval<U>() );
};

template <typename U, typename V>
using product_t = typename product_type<U,V>::type;

// https://stackoverflow.com/questions/18497122/how-to-initialize-stdarrayt-n-elegantly-if-t-is-not-default-constructible
template<typename T, size_t...Ix, typename... Args>
std::array<T, sizeof...(Ix)> repeat(std::index_sequence<Ix...>, Args &&... args) {
   return {{((void)Ix, T(args...))...}};
}

template<typename T, size_t N>
class initialized_array: public std::array<T, N> {
public:
    template<typename... Args>
    initialized_array(Args &&... args)
        : std::array<T, N>(repeat<T>(std::make_index_sequence<N>(), std::forward<Args>(args)...)) {}
};

template <typename T1, std::size_t N1, typename T2, std::size_t N2>
decltype(auto)
outer_product(const std::array<T1, N1>& a1, const std::array<T2, N2>& a2)
{
    std::array<
        initialized_array<product_t<T1,T2>, N2>
        ,N1> ret{};

    for (std::size_t i = 0; i<N1; ++i)
    {
        for (std::size_t j = 0; j<N2; ++j)
        {
            ret[i][j] = a1[i]*a2[j];
        }
    }

    return ret;
}

};

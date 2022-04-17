#pragma once

#include <type_traits>
#include <utility>
#include <vector>

namespace hw12
{

using namespace std;

template <typename T, typename U>
struct product_type
{
    using type =  decltype( declval<T>() * declval<U>() );
};

template <typename U, typename V>
using product_t = typename product_type<U,V>::type;

template<typename U, typename V>
//vector<vector<product_t<U,V>>>
decltype(auto)
outer_product(const vector<U>& v1, const vector<V>& v2)
{
    vector<vector<product_t<U,V>>> ret;

    for (const auto& i : v1)
    {
        vector<product_t<U,V>> row;
        for (const auto& j : v2)
        {
            row.emplace_back(i*j);
        }
        ret.emplace_back(std::move(row));
    }

    return ret;
}

};

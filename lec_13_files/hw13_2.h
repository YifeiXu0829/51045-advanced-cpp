#pragma once

#include<utility>
#include<type_traits>
#include "Tuple.h"

namespace hw13
{
using mpcs::Tuple2;

template<typename T, typename ...Ts>
struct type_getter;

template<typename T, typename ...Ts>
struct type_getter<T, T, Ts...>
{
    static auto& get(Tuple2<T, Ts...>& tp)
    {
        return tp.val;
    }
};

template<typename T, typename H, typename ...Ts>
struct type_getter<T, H, Ts...>
{
    static auto& get(Tuple2<H, Ts...>& tp)
    {   
        return type_getter<T, Ts...>::get(static_cast<Tuple2<Ts...>&>(tp));
    }
};



template <typename T, typename ...Ts>
auto get(Tuple2<Ts...>& tp)
{
    return type_getter<T, Ts...>::get(tp);
}




};

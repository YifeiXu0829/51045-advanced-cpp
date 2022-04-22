#pragma once

#include<utility>
#include<type_traits>
#include"variadic_examples.h"
#include<tuple>

namespace hw13
{

using std::tuple;

// ReplaceAll

template <typename TUPLE, typename T, typename U>
struct replace_all;

template <typename TUPLE, typename T, typename U>
using replace_all_t = typename replace_all<TUPLE, T, U>::type;

template <typename T, typename U>
struct replace_all<tuple<>, T, U>
{
    using type = tuple<>;
};

template <typename H, typename... Ts, typename A, typename B>
struct replace_all<tuple<H, Ts...>, A, B> : public mpcs::Append<tuple<H>,
                                                                replace_all_t<tuple<Ts...>, A, B>
                                                               >
{
};


template <typename... Ts, typename A, typename B>
struct replace_all<tuple<A, Ts...>, A, B> : public mpcs::Append<tuple<B>,
                                                                replace_all_t<tuple<Ts...>, A, B>
                                                               >
{
};


//Reverse

template <typename TUPLE>
struct reverse_tuple;

template <typename TUPLE>
using reverse_tuple_t = typename reverse_tuple<TUPLE>::type;

template <>
struct reverse_tuple<tuple<>>
{
    using type = tuple<>;
};

template <typename T, typename... Ts>
struct reverse_tuple<tuple<T, Ts...>> : public mpcs::Append<reverse_tuple_t<tuple<Ts...>>,
                                           tuple<T>
                                           >
{
};


}; // namespace hw13

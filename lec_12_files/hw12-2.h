#pragma once

namespace hw12
{

template <typename T>
struct is_reference
{
    static constexpr bool value = false;
};

template <typename T>
struct is_reference<T&>
{
    static constexpr bool value = true;
};

template <typename T>
struct is_reference<T&&>
{
    static constexpr bool value = true;
};


template <typename T>
inline constexpr bool is_reference_v = is_reference<T>::value;


template <typename T>
struct remove_reference
{
    using type = T;
};

template <typename T>
struct remove_reference<T&>
{
    using type = T;
};

template <typename T>
struct remove_reference<T&&>
{
    using type = T;
};

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;


};

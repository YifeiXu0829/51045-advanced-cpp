#pragma once

#include <type_traits>
#include <utility>

namespace hw12
{
//worked
template <typename T, typename U = void>
struct remove_all_pointers
{
    using type = T;
};

template <typename T>
struct remove_all_pointers<T, typename std::enable_if_t<
                                    std::is_pointer_v<T>
                                    > 
    >
{
    using type = typename remove_all_pointers<std::remove_pointer_t<T>>::type;
};


// worked
/*
template <typename T>
struct remove_all_pointers : std::conditional_t<std::is_pointer_v<T>,
        remove_all_pointers<typename std::remove_pointer_t<T>>,
        std::type_identity<T>
    >
{
};
*/


// error: no type named 'type' in 'remove_all_pointers<int>'
/*
template <typename T>
struct remove_all_pointers
{
    using type = std::conditional_t<
        std::is_pointer_v<T>,
        typename remove_all_pointers<
              typename std::remove_pointer_t<T>
            >::type,
        T
    >;

};
*/

template <typename T>
using remove_all_pointers_t = typename remove_all_pointers<T>::type;

};

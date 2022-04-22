#ifndef HW_TRAITS_H
#  define HW_TRAITS_H
#include<type_traits>
using std::true_type;
using std::false_type;

namespace mpcs {
template<typename T>
struct remove_all_pointers {
	using type = T;
};

template<typename T>
struct remove_all_pointers<T *> : remove_all_pointers<T> {
};

template<typename T>
using remove_all_pointers_t = typename remove_all_pointers<T>::type;

template<typename T>
struct is_reference : public false_type {};

template<typename T>
struct is_reference<T&> : public true_type {};

template<typename T>
struct is_reference<T&&> : public true_type {};

template<typename T>
struct remove_reference {
	using type = T;
};

template<typename T>
struct remove_reference<T &> {
	using type = T;
};

template<typename T>
struct remove_reference<T&&> {
	using type = T;
};

template<typename T>
bool constexpr is_reference_v = is_reference<T>::value;

template<typename T>
using remove_reference_t = typename remove_reference<T>::type;

template<typename T, typename U>
struct product_type {
	using type = decltype(declval<T>() * declval<U>());
};
template<typename T, typename U>
using product_type_t = product_type<T, U>::type;
}
#endif

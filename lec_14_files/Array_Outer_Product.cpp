#include "HW_traits.h"
#include <array>
#include <utility>
using namespace mpcs;
using namespace std;

// This is gratuitously hard. For a proposal for a more natural solution, see 
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2020/p2163r0.pdf
template<typename T, typename U, size_t s2, size_t ...indexes>
array<product_type_t<T, U>, s2>
make_inner_array(
	T const& t, array<U, s2> const& r, integer_sequence<size_t, indexes...>)
{
	return { (t * r[indexes])... };
}

template<typename T, size_t s1, typename U, size_t s2, size_t ...indexes>
array<array<product_type_t<T, U>, s2>, s1>
make_outer_product_array(array<T, s1> const& l,
	array<U, s2> const& r,
	integer_sequence<size_t, indexes...>)
{
	return { make_inner_array(l[indexes], r, make_index_sequence<s2>())... };
}

template<typename T, std::size_t s1, typename U, std::size_t s2>
array<array<product_type_t<T, U>, s2>, s1>
outer_product(array<T, s1> const& l, array<U, s2> const& r)
{
	return make_outer_product_array(l, r, make_index_sequence<s1>());
}

int main()
{
	array ai = { 1, 2, 3 };
	array ad = { 4.1, 5.1 };

	auto m = outer_product(ai, ad);
	return 0;
}
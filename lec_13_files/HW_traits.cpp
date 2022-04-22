#include <type_traits>
#include "HW_Traits.h"

int main()
{
	static_assert(std::is_same_v<mpcs::remove_all_pointers_t<int>, int>);
	static_assert(std::is_same_v<mpcs::remove_all_pointers_t<int*>, int>);
	static_assert(std::is_same_v<mpcs::remove_all_pointers_t<int**>, int>);
	static_assert(!std::is_same_v<mpcs::remove_all_pointers_t<int&>, int>);
	static_assert(std::is_same_v<mpcs::remove_all_pointers_t<int*&>, int*&>);

	static_assert(mpcs::is_reference_v<int&>);
	static_assert(mpcs::is_reference_v<int&&>);
	static_assert(!mpcs::is_reference_v<int>);

	static_assert(std::is_same_v<mpcs::remove_reference_t<int>, int>);
	static_assert(std::is_same_v<mpcs::remove_reference_t<int&>, int>);
	static_assert(std::is_same_v<mpcs::remove_reference_t<int&&>, int>);

	static_assert(
		std::is_same_v<
		mpcs::remove_all_pointers_t<mpcs::remove_reference_t<int*&&>>,
		int>);

}
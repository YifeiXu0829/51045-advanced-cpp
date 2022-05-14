#ifndef OPTIMIZED_COPY_H
#define OPTIMIZED_COPY_H
#include<type_traits>
#include<iterator>
#include<iostream>
using std::iterator_traits;
using std::integral_constant;
using std::true_type;
using std::enable_if_t;
using std::remove_const_t;
using std::is_trivially_copy_assignable_v;
using std::cout;
using std::endl;

namespace mpcs {

	template<typename I1, typename I2>
	I2 optimized_copy(I1 first, I1 last, I2 out)
	{
        cout << "regular copy" <<endl;
		while (first != last)
		{
			*out = *first;
			++out;
			++first;
		}
		return out;
	}

    template<typename It>
    It optimized_copy(It begin, It end, It out, std::random_access_iterator_tag = typename iterator_traits<It>::iterator_category())
    {
        cout << "random_access_iterator memcpy" <<endl;
        memcpy(&(*out), &*begin, (end-begin)*sizeof(typename iterator_traits<It>::value_type));
        return out + (end-begin);
    }

	template<typename T, enable_if_t<is_trivially_copy_assignable_v<T>> * = nullptr>
	remove_const_t<T>* optimized_copy(T* first, T* last, remove_const_t<T>* out)
	{
        cout << "pointers copy" <<endl;
		memcpy(out, first, (last - first) * sizeof(T));
		return out + (last - first);
	}
}
#endif // !OPTIMIZED_COPY_H

#include "HW_traits.h"
#include <vector>
using namespace mpcs;
using namespace std;

template<typename T, typename U>
vector<vector<product_type_t<T, U>>>
outer_product(vector<T> const& l, vector<U> const& r)
{
	vector<vector<product_type_t<T, U>>> result;
	for (auto const& x : l) {
		result.push_back({});
		for (auto const& y : r)
			result.back().push_back(x * y);
	}
	return result;
}

int main()
{
	vector vi = { 1, 2, 3 };
	vector vd = { 4.1, 5.1 };

	auto m = outer_product(vi, vd);
	return 0;
}
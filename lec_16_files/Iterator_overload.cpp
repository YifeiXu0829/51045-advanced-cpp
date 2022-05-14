#include<iostream>
#include<vector>
#include<list>

using namespace std;

template<random_access_iterator It>
size_t my_distance(It beg, It end)
{
	return end - beg;
}

template<forward_iterator It>
size_t my_distance(It beg, It end)
{
	size_t d{};
	for (; beg != end; beg++, d++)
		;
	return d;
}

list l = { 1, 2, 3, 4 };
vector v = { 1, 2, 3, 4 };

int main()
{
	cout << my_distance(l.begin(), l.end()) << endl;
	cout << my_distance(v.begin(), v.end()) << endl;
}
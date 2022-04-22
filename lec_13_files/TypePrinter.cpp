#include<type_traits>
#include<string>
#include<typeinfo>
#include<typeindex>
#include<utility>
#include<map>
#include<stdexcept>
#include<iostream>
using namespace std;

map builtins = {
	pair{type_index(typeid(char)), "char"s },
	{type_index(typeid(int)), "int"s},
	{type_index(typeid(long)), "long"s },
	{type_index(typeid(float)), "float"s},
	{type_index(typeid(double)), "double"s}
};

template<typename T>
std::string TypePrinter()  {
	if (is_pointer_v<T>)
		return TypePrinter<remove_pointer_t<T>>() + " *"s;
	if (is_lvalue_reference_v<T>)			
		return TypePrinter<remove_reference_t<T>>() + " &"s;
	if (is_rvalue_reference_v<T>)
		return TypePrinter<remove_reference_t<T>>() + " &&"s;
	if (is_const_v<T>)
		return TypePrinter<remove_const_t<T>>() + " const"s;
	if (is_volatile_v<T>)
		return TypePrinter<remove_volatile_t<T>>() + " volatile"s;
	auto r = builtins.find(type_index(typeid(T)));
	if (r == builtins.end())
		throw runtime_error("Unknown type");
	return r->second;
}


int main()
{
	cout << TypePrinter<int *>() << endl;
	cout << TypePrinter<int const*&>() << endl;
	return 0;
}
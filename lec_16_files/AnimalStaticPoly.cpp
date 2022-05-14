// Static Polymorphism
#include<string>
#include<memory>
#include<iostream>
using namespace std;

template<typename T>
struct Animal {
	string name() const { return static_cast<T const *>(this)->name(); }
	string eats() const { return static_cast<T const&>(*this).eats(); } // If you'd rather not have a raw point
};

struct Cat : public Animal<Cat> {
	string name() const { return "cat"; }
	string eats() const { return "delicious mice"; }
};

int main() {
	cout << "Cat or Dog? ";
	string answer;

	Animal a = Cat();
	cout << "A " << a.name() << " eats " << a.eats();
}

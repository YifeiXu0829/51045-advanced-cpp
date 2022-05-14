// Concept version like normal programming
#include<string>
#include<type_traits>
#include<iostream>

using namespace std;

template<typename T>
concept Animal = requires(T const a) {
    { a.eats() } -> convertible_to<string>;
    { a.name() } -> convertible_to<string>;
};

struct Cat {
    string eats() const { return "delicious mice"; }
    string name() const { return "cat"; }
};
// More animals...

int main() {
    Animal auto a = Cat();
    cout << "A " << a.name() << " eats " << a.eats();
}

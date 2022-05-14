// Familiar OO Version
#include<string>
#include<memory>
#include<iostream>
using namespace std;

struct Animal {
    virtual string name() const = 0;
    virtual string eats() const = 0;
};

struct Cat : public Animal {
    string name() const override { return "cat"; }
    string eats() const override { return "delicious mice"; }
};
// More animals...

int main() {
    unique_ptr<Animal> a = make_unique<Cat>();
    cout << "A " << a->name() << " eats " << a->eats();
}

#include <iostream>
#include<string>
#include<type_traits>

using namespace std;

template <typename Impl>
struct Animal
{
    string name()
    {
        return impl().name();
    }

    string eats()
    {
        return impl().eats();
    }

    Impl& impl() {return *static_cast<Impl*>(this);}
};

struct Cat : Animal<Cat>
{
    string name()
    {
        return "cat";
    }

    string eats()
    {
        return "delicious mice";
    }
};


int main()
{
    while(true){

        int option=0;
        cout << "Choose Part: (0) Exit program (else) cat"<<endl;
        cin >> option;

        if (option==0)
        {
            return 0;
        }
        else 
        {
            auto a = make_unique<Animal<Cat>>();

            cout << "A " << a->name() << " eats " << a->eats();
        }
    }
}

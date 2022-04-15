#include "remove_all_pointers.h"
#include "hw12-2.h"
#include "type_printer.h"

#include <iostream>
#include <typeinfo>
using namespace std;

int main()
{
    cout<<typeid(hw12::remove_all_pointers_t<int*>).name()<<endl;
    cout<<typeid(hw12::remove_all_pointers_t<double******>).name()<<endl;
    cout<<typeid(hw12::remove_all_pointers_t<double>).name()<<endl;

    cout<<"is_reference_v<int>:"<<hw12::is_reference_v<int><<endl;
    cout<<"is_reference_v<int&>:"<<hw12::is_reference_v<int&><<endl;
    cout<<"is_reference_v<int&&>:"<<hw12::is_reference_v<int&&><<endl;

    cout<<typeid(hw12::remove_reference_t<int>).name()<<endl;
    cout<<typeid(hw12::remove_reference_t<int&>).name()<<endl;
    cout<<typeid(hw12::remove_reference_t<int&&>).name()<<endl;
 
    // int& a = 5; error
    hw12::remove_reference_t<int&> a = 5;
    hw12::remove_reference_t<int&&> b = 6;

    
    cout<<"int -> "<<hw12::TypePrinter<int>()<<endl;
    cout<<"double -> "<<hw12::TypePrinter<double>()<<endl;
    cout<<"int const * -> "<<hw12::TypePrinter<int const *>()<<endl;
    cout<<"float * const -> "<<hw12::TypePrinter<float * const>()<<endl;
    cout<<"int & -> "<<hw12::TypePrinter<int &>()<<endl;
    cout<<"long && -> "<<hw12::TypePrinter<long &&>()<<endl;
    cout<<"char volatile -> "<<hw12::TypePrinter<char volatile>()<<endl;
}

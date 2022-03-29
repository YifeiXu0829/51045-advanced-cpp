#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include "ctre.hpp"

int main()
{
    std::string s{"Here are some numbers: 1.23, 4, 5.6, 7.89, .0123"}; // added special case .0123

    std::cout<<"==================std::regex====================\n";
    std::regex decimal_num_regex{"([0-9]*)\\.([0-9]+)"};

    auto decimal_num_begin = std::sregex_iterator(s.begin(), s.end(), decimal_num_regex);
    auto decimal_num_end = std::sregex_iterator();

    for (std::sregex_iterator i = decimal_num_begin; i != decimal_num_end; ++i)
    {
        std::cout<< i->str() << std::endl;
        //for (const auto& item : *i)
        //{
        //    std::cout<< " " << item << " " << std::endl;
        // }
        std::cout<< (*i)[1] << " is before the decimal and " << (*i)[2] << " is after the decimal"  << std::endl;
    }

    std::cout<<"==================CTRE====================\n";

    // CTRE
    auto results = ctre::range<"([0-9]*)\\.([0-9]+)">(s);
    for (const auto& result : results)
    {
        std::cout<< result.to_view()<<std::endl;
        std::cout<< result.get<1>() << " is before the decimal and " << result.get<2>() << " is after the decimal"  << std::endl;
    }
}

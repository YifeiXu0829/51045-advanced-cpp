#include "hw13_1.h"
#include "hw13_2.h"
#include "hw13_3.h"
#include <cassert>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    static_assert(std::is_same_v<hw13::replace_all_t<std::tuple<char, int, char, float, char, char, char>,
                                               char,
                                               double
                                              >,
                                 tuple<double, int, double, float, double, double, double>
                                >);

    static_assert(std::is_same_v<hw13::reverse_tuple_t<std::tuple<char, int, double, float, long>
                                                      >,
                                 std::tuple<long, float, double, int, char>
                                >);


    mpcs::Tuple2<int, double, std::string> t2id(4, 5.6, "ha");
    assert(hw13::get<std::string>(t2id) == std::string("ha"));
    assert(hw13::get<double>(t2id) == 5.6);
    assert(hw13::get<int>(t2id) == 4);

    std::array<int, 3> v1 = { 1, 2, 3 };
    std::array<double, 2> v2 = { 4.1, 5.1 };

    auto m = hw13::outer_product(v1, v2);

    for (const auto& row : m)
    {
        for (const auto& item : row)
        {
            cout<<item<<" ";
        }

        cout<<""<<endl;
    }
}

#include "hw13_1.h"
#include "hw13_2.h"
#include <cassert>
#include <string>

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
}

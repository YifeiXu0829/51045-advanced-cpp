#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <tuple>
#include <map>
#include <cassert>
#include <fstream>

#include "ctre.hpp"

auto saffir_simpson_scale(int knots)
{
    if (knots < 64) return 0;
    if (knots >= 64 && knots <=82) return 1;
    if (knots >= 83 && knots <=95) return 2;
    if (knots >= 96 && knots <113) return 3;
    if (knots >= 114 && knots <=135) return 4;
    if (knots >= 136) return 5;

    assert (false && "unreachable !");
    return 0;
}

std::tuple<bool, std::string> get_year_ctre(const std::string& line)
{
    auto mmddyyyy = ctre::search<"[0-9]{2}/[0-9]{2}/([0-9]{4})">(line);
    if (mmddyyyy) return {true, std::move(mmddyyyy.get<1>().str())};
    return {false, ""};
}

std::tuple<bool, double> get_daily_res_ctre(const std::string& s)
{
    auto results = ctre::range<"[\\*SEWL\\s]\\s*[0-9]+\\s*[0-9]+\\s*([0-9]+)\\s*">(s);
    int count{0};
    auto ret{0.0};
    for (const auto& result : results)
    {
        int n{};
        auto str = result.get<1>().view();
        auto [ptr, ec] { std::from_chars(str.data(), str.data() + str.size(), n) };
        if (ec == std::errc())
        {
            //std::cout<<n<<std::endl;
            ret+= saffir_simpson_scale(n)/4.0;
        }
        else
        {
            assert (false && "not a number !");
        }
        ++count;
    }
 
    if (count == 0) return {false, 0};
    assert(count==4 && "not exact 4 records daily ??");

    return {true, ret};    
}

int main()
{
    std::string filename{"hurdat_atlantic_1851-2011.txt"};
    std::ifstream input_file(filename);
    std::string line{};
    std::string current_year{"no_year"};
    std::map<std::string, double> result;
    while (getline(input_file, line)){
        //std::cout<<"line: "<<line<<std::endl;
        auto [header, year] = get_year_ctre(line);
        if (header)
        {
            current_year = std::move(year);
            //std::cout<<current_year<<std::endl;
        }
        else
        {
            auto [body, res] = get_daily_res_ctre(line);
            if (body) result[current_year] += res;
        }
    }

    input_file.close();

    // print a table of the annual Saffir-Simpson day totals for each year
    for (const auto& [year, total] : result)
    {
        std::cout<<year<<":"<<total<<std::endl;
    }
}

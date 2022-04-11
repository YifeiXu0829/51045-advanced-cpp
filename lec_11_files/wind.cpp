#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stdexcept>
#include <string>
#include <charconv>
//#include <boost/progress.hpp>

using namespace std;
ofstream output("output.txt");

int
knotsToSaffirSimpson(int knots)
{
    if(knots < 64) {
        return 0;
    }
    if(knots < 83) {
        return 1;
    }
    if(knots < 96) {
        return 2;
    }
    if(knots < 114) {
        return 3;
    }
    if(knots < 136) {
        return 4;
    }
    return 5;
}

class YearEntry {
public:
    void addKnots(string_view str) {
        int n{};
        auto [ptr, ec] { std::from_chars(str.data(), str.data() + str.size(), n) };
        if (ec == std::errc())
        {
            ssDays += knotsToSaffirSimpson(n)/4.0;
        }
    }
    double ssDays{0};
};

void 
print_year(const pair<string const, YearEntry>& year_entry_pair) 
{
    output << year_entry_pair.first << ", " << year_entry_pair.second.ssDays << endl;
}

int main()
{
	//boost::progress_timer t;
    map<string, YearEntry > ssMap{};
    string line{};
    YearEntry* currentYearEntry{nullptr};
    ifstream tracks("hurdat_atlantic_1851-2011.txt");
    smatch what{};
    regex headerRegex("(?:\\d{2}/){2}(\\d{4})");
	regex dayRegex(".{11}[*SEWLD].{7}\\s+(\\d+).{13}\\s+(\\d+).{13}\\s+(\\d+).{13}\\s+(\\d+).*");
    while(getline(tracks, line)) {
        if(regex_search(line, what, headerRegex)) {
			//cout << line << endl;  // just so we can see progress...
            currentYearEntry = &ssMap[what[1].str()];
            continue;
        } else if ( regex_search( line, what, dayRegex ) ) {
			currentYearEntry->addKnots(what[1].str());
			currentYearEntry->addKnots(what[2].str());
			currentYearEntry->addKnots(what[3].str());
			currentYearEntry->addKnots(what[4].str());
		}
    }
	output << "Year, Safer-Simpson Days" << endl;
    for (const auto& [year, entry] : ssMap)
    {
        print_year({ year, entry });
    }
}

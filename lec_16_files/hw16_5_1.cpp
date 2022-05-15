#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template <typename T>
struct ostream_joiner
{
    explicit ostream_joiner(ostream& os, std::string d):os_(os), delimitor_(d)
    {
    }
    ostream& os_;
    std::string delimitor_{""};
    bool is_start_{true};

    ostream_joiner& operator= (const T& value)
    {
        if(is_start_)
        {
            os_ << value;
        }
        else
        {
            os_ << delimitor_ << value;
        }
        return *this;
    }

    ostream_joiner& operator* ()
    {
        return *this;
    }

    ostream_joiner& operator++ ()
    {
        is_start_ = false;
        return *this;
    }

    ostream_joiner& operator++ (int)
    {
        return *this;
    }

    
};

int main()
{
    vector v = {1,2,3};

    copy(v.begin(), v.end(), ostream_joiner<int>(cout, ", "));
}

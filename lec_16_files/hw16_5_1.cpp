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
    bool is_first_{true};

    ostream_joiner& operator= (const T& value)
    {
        if(is_first_)
        {
            os_ << value;
            is_first_ = false;
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

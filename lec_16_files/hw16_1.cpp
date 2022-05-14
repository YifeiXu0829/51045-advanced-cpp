#include "hw16_1.h"
#include <vector>

int main()
{
    std::vector<int> v{1, 2, 3, 4, 5};

    std::vector<int> cp{0,0,0,0,0,0,0,0};

    mpcs::optimized_copy(v.begin(), v.end(), std::begin(cp));
    for (auto& i : cp)
    {
        cout<<i<<endl;
    }
}

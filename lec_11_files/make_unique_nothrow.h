// Create a version of make_unique that doesn't throw exceptions

#include <memory>
#include <new>
#include <vector>
#include <iostream>

namespace hw11_1
{

template<typename T, typename ...  Args>
std::unique_ptr<T> make_unique(Args&& ... args) noexcept
{
    return std::unique_ptr<T>(new(std::nothrow) T(std::forward<Args>(args)...));
}


}


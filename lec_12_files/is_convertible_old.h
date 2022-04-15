#ifndef IS_CONVERTIBLE_H
#  define IS_CONVERTIBLE_H
#include <type_traits>

namespace cspp51044 {

template<class T, class U>
class Conversion {
    typedef char Small;
    class Big { char dummy[2]; };

    static Small Test(U);
    static Big Test(...);
    static T MakeT();
public:
    enum { exists = sizeof(Test(MakeT())) == sizeof(Small) };
};

template<bool b> class IsConvertibleHelper;
template<>
class IsConvertibleHelper<true> : public std::true_type {
};
template<>
class IsConvertibleHelper<false> : public std::false_type {
};

template<class T, class U>
class is_convertible 
  : public IsConvertibleHelper<Conversion<T, U>::exists> {
};

}

#endif
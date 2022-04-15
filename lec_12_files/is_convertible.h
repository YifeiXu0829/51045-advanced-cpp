#ifndef IS_CONVERTIBLE_H
#  define IS_CONVERTIBLE_H
#include <type_traits>

namespace cspp51044 {

template<class T, class U>
class Conversion {
    class CanConvert {};
    class NoConversion {};

    static CanConvert Test(U);
    static NoConversion Test(...);
public:
    static int constexpr value = is_same_v<decltype(Test(std::declval<T>())), CanConvert>;
    using type = is_same<decltype(Test(std::declval<T>())), CanConvert>;
};

template<class T, class U>
struct is_convertible 
  : public std::integral_constant<bool, Conversion<T, U>::value> {
};

template<class T, class U>
struct is_convertible_alt
      : public typename Conversion<T, U>::type { 
}

template<class T, class U>
bool is_convertible_v = is_convertible<T, U>::value;
};



}

#endif
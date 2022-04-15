#pragma once

#include <type_traits>
#include <string>
#include <array>

namespace hw12
{

// https://stackoverflow.com/questions/38955940/how-to-concatenate-static-strings-at-compile-time
template <std::string_view const&... Strs>
struct join
{
    // Join all strings into a single std::array of chars
    static constexpr auto impl() noexcept
    {
        constexpr std::size_t len = (Strs.size() + ... + 0);
        std::array<char, len + 1> arr{};
        auto append = [i = 0, &arr](auto const& s) mutable {
            for (auto c : s) arr[i++] = c;
        };
        (append(Strs), ...);
        arr[len] = 0;
        return arr;
    }
    // Give the joined string static storage
    static constexpr auto arr = impl();
    // View as a std::string_view
    static constexpr std::string_view value {arr.data(), arr.size() - 1};
};

template <typename T>
struct type_printer
{
    static constexpr std::string_view value = "unknown type";
};

template <>
struct type_printer<int>
{
    static constexpr std::string_view value = "int";
};

template <>
struct type_printer<long>
{   
    static constexpr std::string_view value = "long";
};

template <>
struct type_printer<char>
{   
    static constexpr std::string_view value = "char";
};

template <>
struct type_printer<double>
{   
    static constexpr std::string_view value = "double";
};

template <>
struct type_printer<float>
{   
    static constexpr std::string_view value = "float";
};


template <typename T>
struct type_printer<const T>
{
    static constexpr std::string_view s = "const ";
    static constexpr std::string_view value = join<s, type_printer<T>::value>::value;
};

template <typename T>
struct type_printer<volatile T>
{
    static constexpr std::string_view s = "volatile ";
    static constexpr std::string_view value = join<s, type_printer<T>::value>::value;
};

template <typename T>
struct type_printer<T*>
{
    static constexpr std::string_view s = " *";
    static constexpr std::string_view value = join<type_printer<T>::value, s>::value;
};

template <typename T>
struct type_printer<T* const>
{
    static constexpr std::string_view s = " * const";
    static constexpr std::string_view value = join<type_printer<T>::value, s>::value;
};

template <typename T>
struct type_printer<T* volatile>
{
    static constexpr std::string_view s = " * volatile";
    static constexpr std::string_view value = join<type_printer<T>::value, s>::value;
};

template <typename T>
struct type_printer<T&>
{
    static constexpr std::string_view s = " &";
    static constexpr std::string_view value = join<type_printer<T>::value, s>::value;
};

template <typename T>
struct type_printer<T&&>
{
    static constexpr std::string_view s = " &&";
    static constexpr std::string_view value = join<type_printer<T>::value, s>::value;
};


template <typename T>
std::string_view TypePrinter()
{
    return type_printer<T>::value;
}

};

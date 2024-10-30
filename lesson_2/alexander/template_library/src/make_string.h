#ifndef MAKE_STRING_H
#define MAKE_STRING_H

#include <vector>
#include <string>
#include <type_traits>

namespace ATL {

template <typename Numeric, typename = typename std::enable_if_t<std::is_arithmetic_v<Numeric> > >
auto make_string(Numeric num) -> decltype(std::to_string(num)) {
    return std::to_string(num);
}

template <>
std::string make_string<char>(char sym) {
    char str[] = {sym, 0};
    return {str};
}

template <typename StringType, typename = typename std::enable_if_t<std::is_convertible_v<StringType, std::string> > >
std::string make_string(StringType&& string)
{
    return std::string(std::forward<StringType>(string));
}

template <typename Iterable, typename = typename std::enable_if_t<!std::is_convertible_v<Iterable, std::string> > >
auto make_string(Iterable it) -> decltype(make_string(*std::begin(it))) {
    std::string res;
    for (const auto& val : it) {
        res += make_string(val) + ", ";
    }
    res.erase(res.size() - 2, 2);
    return res;
}

template <typename First, typename Second, typename ...Args>
std::string make_string(First&& f, Second&& s, Args&&... arg) {
    return make_string(std::forward<First>(f)) + make_string(std::forward<Second>(s), std::forward<Args>(arg)...);
}

}

#endif // MAKE_STRING_H

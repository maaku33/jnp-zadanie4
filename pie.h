#ifndef __PIE_H__
#define __PIE_H__

#include <type_traits>

template <typename T>
struct is_cherry {
    bool value = false;
};

template <>
struct is_cherry<CherryPie> {
    bool value = true;
};

template <typename T>
struct is_apple {
    bool value = false;
};

template <>
struct is_apple<ApplePie> {
    bool value = true;
};

template <typename R, R radius, typename P, typename T>
class Pie {

    int initialStock;
    P price;

public:
    void CherryPie(typename std::enable_if<is_cherry<T>, int>::type initialStock)
        : initialStock(initialStock) {};

    void ApplePie(typename std::enable_if<is_apple<T>, int>::type initialStock, P price)
        : initialStock(initialStock), price(price) {};
};

using CherryPie = Pie <R, R radius, double, CherryPie>;
using ApplePie = Pie <R, R radius, P, ApplePie>;

#endif /* __PIE_H__ */
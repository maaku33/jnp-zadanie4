#ifndef __PIE_H__
#define __PIE_H__

#include <type_traits>

template <int>
struct is_cherry {
    const static bool value = false;
};

template <>
struct is_cherry<1> {
    const static bool value = true;
};

template <int>
struct is_apple {
    const static bool value = false;
};

template <>
struct is_apple<2> {
    const static bool value = true;
};

template <typename R, R radius, typename P, int type>
class Pie {

    int initialStock;
    P price;

public:
    template <int t = type>
    Pie(int initialStock, typename std::enable_if<is_cherry<t>::value>::type* = nullptr):
        initialStock(initialStock) {};

    template <int t = type>
    Pie(int initialStock, P price, typename std::enable_if<is_apple<t>::value>::type* = nullptr):
        initialStock(initialStock),
        price(price) {};
};

template <typename R, R radius>
using CherryPie = Pie<R, radius, double, 1>;

template <typename R, R radius, typename P>
using ApplePie = Pie<R, radius, P, 2>;

#endif /* __PIE_H__ */
#ifndef __PIE_H__
#define __PIE_H__

#include <type_traits>
#include <cassert>

// courtesy of Newton
constexpr double pi_(unsigned n, unsigned i = 1, double last = 2.0) {
    return i > n + 1 ? 0.0 : last + 
        pi_(n, i + 1, last * (double)i / (2.0 * (double)i + 1.0));
}

// 10 digit precision of pi
constexpr double pi = pi_(30);

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

template <typename R, R radius, typename P, int type,
          typename EnableR = void, typename EnableP = void> 
class Pie;

template <typename R, R radius, typename P, int type>
class Pie<R, radius, P, type,
          typename std::enable_if<std::is_integral<R>::value>::type,
          typename std::enable_if<std::is_floating_point<P>::value>::type> {

    int stock;
    P price;

public:
    template <int t = type, typename std::enable_if<is_cherry<t>::value, int>::type = 0>
    Pie(int initialStock): stock(initialStock) {
        assert(initialStock > 0);
    }

    template <int t = type, typename std::enable_if<is_apple<t>::value, int>::type = 0>
    Pie(int initialStock, P price): stock(initialStock), price(price) {
        assert(initialStock > 0);
    }

    static double getArea() {
        return pi * radius * radius;
    }

    int getStock() {
        return stock;
    }

    template <typename ... Buffer, int t = type>
    typename std::enable_if<is_apple<t>::value, void>::type sell() {
        static_assert(sizeof ... (Buffer) == 0, 
            "Template arguments should not be specified.");

        assert(stock > 0);
        stock--;
    }

    template <typename ... Buffer, int t = type>
    typename std::enable_if<is_apple<t>::value, P>::type getPrice() {
        static_assert(sizeof ... (Buffer) == 0,
            "Template arguments should not be specified.");

        return price;
    }
};

template <typename R, R radius>
using CherryPie = Pie<R, radius, double, 1>;

template <typename R, R radius, typename P>
using ApplePie = Pie<R, radius, P, 2>;

#endif /* __PIE_H__ */
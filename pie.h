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

template <typename R, R radius, typename P, bool sellable>
class Pie {

    static_assert(std::is_integral<R>::value,
		"Measure type is not integral.");
    static_assert(std::is_floating_point<P>::value,
		"Price type is not floating point.");

    int stock;
    const P price;

public:

	static constexpr double c_area = pi * radius * radius;
    using price_type = P;
    using  measure_type = R;
    static constexpr bool is_for_sale = sellable;
    static constexpr bool is_apple_pie = true; //TODO 

    template <bool s = sellable, typename std::enable_if<!s, int>::type = 0>
    Pie(int initialStock): stock(initialStock), price() {
        assert(initialStock > 0);
    }

    template <bool s = sellable, typename std::enable_if<s, int>::type = 0>
    Pie(int initialStock, P price): stock(initialStock), price(price) {
        assert(initialStock > 0);
    }

    static double getArea() {
        return pi * radius * radius;
    }

    int getStock() {
        return stock;
    }
    

    template <typename ... Buffer, bool s = sellable>
    typename std::enable_if<s, void>::type sell() {
        static_assert(sizeof ... (Buffer) == 0,
            "Template arguments should not be specified.");

        stock = stock - (stock > 0 ? 1 : 0);
    }

    template <typename ... Buffer, bool s = sellable>
    typename std::enable_if<s, P>::type getPrice() {
        static_assert(sizeof ... (Buffer) == 0,
            "Template arguments should not be specified.");

        return price;
    }
};

template <typename R, R radius>
using CherryPie = Pie<R, radius, double, false>;

template <typename R, R radius, typename P>
using ApplePie = Pie<R, radius, P, true>;

#endif /* __PIE_H__ */

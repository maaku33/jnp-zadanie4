#ifndef __CAKE_H__
#define __CAKE_H__

#include <type_traits>
#include <cassert>

// returns the value of n-th Taylor polynomial of ln(1 + x) at x
constexpr double ln_(double x, unsigned n, unsigned i = 1, double last = 1) {
    return i >= n ? 0.0 : (i % 2 == 0 ? -1 : 1) *
        x * last / i + ln_(x, n, i + 1, x * last);
}

// 9 digit precision of natural log of 2
constexpr double ln2 = 3.0 * ln_(0.25, 20) + ln_(0.024, 20);

template <typename T, T length, T width, typename P, bool sellable>
class Cake {
    
   
    static_assert(std::is_integral<T>::value,
        "First template parameter is not integral.");
    static_assert(std::is_floating_point<P>::value,
        "Fourth template parameter is not floating point.");

    int stock;
    const P price;

public:

    static constexpr double c_area = ln2 * length * width;
    using price_type = P;
    using  measure_type = T;
    static constexpr bool is_for_sale = sellable;
    
    template <bool s = sellable, typename std::enable_if<!s, int>::type = 0>
    Cake(int initialStock): stock(initialStock), price() {
        assert(initialStock > 0);
    }

    template <bool s = sellable, typename std::enable_if<s, int>::type = 0>
    Cake(int initialStock, P price): stock(initialStock), price(price) {
        assert(initialStock > 0);
    }

    static double getArea() {
        return ln2 * length * width;
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

template <typename T, T length, T width>
using CheeseCake = Cake<T, length, width, double, false>;

template <typename T, T length, T width, typename P>
using CreamCake = Cake<T, length, width, P, true>;

#endif /* __CAKE_H__ */

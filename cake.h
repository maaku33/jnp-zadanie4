#ifndef __CAKE_H__
#define __CAKE_H__

#include <type_traits>
#include <cassert>

constexpr double ln2_(unsigned n, unsigned i = 0) {
    return 0.0;
}

// ? digit precision of natural log of 2
constexpr double ln2 = ln2_(0);

template <int>
struct is_cheese {
    const static bool value = false;
};

template <>
struct is_cheese<1> {
    const static bool value = true;
};

template <int>
struct is_cream {
    const static bool value = false;
};

template <>
struct is_cream<2> {
    const static bool value = true;
};

template <typename T, T length, T width, typename P, int type>
class Cake {

    static_assert(std::is_integral<T>::value,
        "First template parameter not integral.");
    static_assert(std::is_floating_point<P>::value,
        "Fourth template parameter not floating point.");

    int stock;
    const P price;

public:
    template <int t = type, typename std::enable_if<is_cheese<t>::value, int>::type = 0>
    Cake(int initialStock): stock(initialStock), price() {
        assert(initialStock > 0);
    }

    template <int t = type, typename std::enable_if<is_cream<t>::value, int>::type = 0>
    Cake(int initialStock, P price): stock(initialStock), price(price) {
        assert(initialStock > 0);
    }
};

#endif /* __CAKE_H__ */

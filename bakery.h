#ifndef __BAKERY_H__
#define __BAKERY_H__

#include <type_traits>
#include <tuple>

/* Checking if elements are unique */
template <typename...>
struct is_one_of;

template <typename F>
struct is_one_of<F> {
    static constexpr bool value = false;
};

template <typename F, typename S, typename... T>
struct is_one_of<F, S, T...> {
    static constexpr bool value = std::is_same<F, S>::value
        || is_one_of<F, T...>::value;
};

template <typename...>
struct is_unique;

template <>
struct is_unique<> {
    static constexpr bool value = true;
};

template <typename F, typename... T>
struct is_unique<F, T...> {
    static constexpr bool value = is_unique<T...>::value
        && !is_one_of<F, T...>::value;
};

/* Checking if price types are same as in bakery */
template <typename T, typename ...Ts>
struct is_price_type_correct;

template <typename T>
struct is_price_type_correct<T> {
    static constexpr bool value = true ;
};

template <typename T1, typename T2, typename ...Ts>
struct is_price_type_correct<T1, T2, Ts...> {
    static constexpr bool value = (!T2::is_sellable
        || std::is_same<T1,typename T2::price_type>::value)
        && is_price_type_correct<T1, Ts...>::value;
};

/* Checking if measures types are same as in bakery */
template <typename T, typename ...Ts>
struct is_measure_type_correct;

template <typename T>
struct is_measure_type_correct<T> {
    static constexpr bool value = true;
};

template <typename T1, typename T2, typename ...Ts>
struct is_measure_type_correct<T1, T2, Ts...> {
    static constexpr bool value =
        std::is_same<T1,typename T2::measure_type>::value 
        && is_measure_type_correct<T1, Ts...>::value;
};

/* Checking if product T is one of bakery products */
template <typename T, typename ...Ts>
struct contains;

template <typename T>
struct contains<T> {
    static constexpr bool value = false;
};

template <typename T1, typename T2, typename ...Ts>
struct contains<T1, T2, Ts...> {
    static constexpr bool value = std::is_same<T1, T2>::value
        || contains<T1, Ts...>::value;
};

/* Calculates sum area of all products */
constexpr auto sum_area() {
    return 0;
}

template <typename T1, typename... T>
constexpr auto sum_area(T1 sum, T... Trest) {
    return sum + sum_area(Trest...);
}

template <typename C, typename A, A shelfArea, typename... P>
class Bakery {
	
	C profits = 0;
	std::tuple<P...> bakery_products;
	
	static_assert(std::is_floating_point<C>::value,
	    "Price type is not floating point.");
        
	static_assert(std::is_integral<A>::value,
      	"Measure type is not integral.");
        
   	static_assert(is_unique<P...>::value,  
        "Bakery products must be unique!");
        
	static_assert(is_price_type_correct<C, P...>::value, 
	    "Price type of bakery and product are diffrent!");
	
	static_assert(is_measure_type_correct<A, P...>::value, 
	    "Measure type of bakery and product are diffrent!");
	
	static_assert( sum_area(P::getArea()...) <= shelfArea, 
	    "Sum of products area is greater than shelfArea!" );
		
public:
	
	Bakery(P... products) : bakery_products(products...) {}
	
	C getProfits() {
		return profits;
	}
	
	template <class Product> void sell() {
		static_assert(contains<Product,P...>::value,
		    "This bakery doesn't contain this product!");
		
		static_assert(Product::is_sellable, 
		    "This product is not for sale!");

        Product& product = std::get<Product>(bakery_products);		    		
		if (product.getStock() > 0) {
			product.sell();
			profits += product.getPrice();
		}
	}
	
	
	template <class Product> int getProductStock() {
		static_assert(contains<Product, P...>::value,
			"This bakery doesn't contain this product!");
		
		Product& product = std::get<Product>(bakery_products);
		return product.getStock();
	}
	
	template <class Product> void restock(int additionalStock) {
	    static_assert(contains<Product, P...>::value,
		    "This bakery doesn't contain this product!");

	    static_assert(Product::is_restockable, "Product is not an apple pie!");
		
	    Product& product = std::get<Product>(bakery_products);
		product.restock(additionalStock);		
	}
};

#endif /* __BAKERY_H__ */

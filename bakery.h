#ifndef __BAKERY_H__
#define __BAKERY_H__

#include <type_traits>
#include <cassert>
#include <tuple>
#include <cstddef>
#include <typeinfo>

/* Checking if elements are unique */
template< class T > using invoke = typename T :: type ;

template< class C, class I, class E > using if_t     = invoke< std::conditional< C{}, I, E> >;

template< class T > struct id{};
struct empty{};

template< class A, class B > struct base : A, B {};

template< class B , class ... > struct is_unique_impl;

template< class B > struct is_unique_impl<B>: std::true_type{};

template< class B, class T, class ... U>
struct is_unique_impl<B, T, U...> : if_t< std::is_base_of< id<T>, B>, std::false_type, is_unique_impl< base<B,id<T>>, U...> >{};

template< class ...T >struct is_unique : is_unique_impl< empty, T ... > {};



/* Checking if pricetypes are same as in bakery */
template<typename T, typename ...Ts>
struct is_price_type_correct;

template<typename T>
struct is_price_type_correct<T> {
    static constexpr bool value = true ;
};

template<typename T1, typename T2, typename ...Ts>
struct is_price_type_correct<T1, T2, Ts...> {
    static constexpr bool value = (!T2::is_for_sale || std::is_same<T1,typename T2::price_type>::value) && is_price_type_correct<T1, Ts...>::value;
};


/* Checking if measures types are same as in bakery */
template<typename T, typename ...Ts>
struct is_measure_type_correct;

template<typename T>
struct is_measure_type_correct<T> {
    static constexpr bool value = true ;
};

template<typename T1, typename T2, typename ...Ts>
struct is_measure_type_correct<T1, T2, Ts...> {
    static constexpr bool value = std::is_same<T1,typename T2::measure_type>::value && is_measure_type_correct<T1, Ts...>::value;
};



/* Checking if product T is one of bakery products */
template<typename T, typename ...Ts>
struct contains;

template<typename T>
struct contains<T> {
    static constexpr bool value = false ;
};

template<typename T1, typename T2, typename ...Ts>
struct contains<T1, T2, Ts...> {
    static constexpr bool value = std::is_same<T1, T2>::value || contains<T1, Ts...>::value;
};



/* Checking if product T from bakery is sellable */
template <typename T,typename = void>
struct is_sellable;

template <typename T>
struct is_sellable<T>{
 static constexpr bool value = T::is_for_sale;
};

/* Calculates sum area of all product */
constexpr auto sum_area(){
    return 0;
}

template<typename T1, typename... T>
constexpr auto sum_area(T1 sum, T... Trest){
    return sum + sum_area(Trest...);
}

template <typename C, typename A, A shelfArea, typename... P>
class Bakery {
	
	C profits = 0;
	std::tuple<P...> bakery_products;
	
	static_assert(std::is_floating_point<C>::value,
        "First template parameter is not floating point.");
        
	static_assert(std::is_integral<A>::value,
        "Second template parameter is not integral.");
        
        static_assert(is_unique<P...>::value,  
        "Bakery products must be unique!");
        
	static_assert(is_price_type_correct<C, P...>::value , 
	"Price type of bakery and product are diffrent!");
	
	static_assert(is_measure_type_correct<A, P...>::value , 
	"Measure type of bakery and product are diffrent!");
	
	static_assert( sum_area(P::c_area...) <= shelfArea, 
	"Sum of products area is greater than shelfArea!" );
		
public:
	
	Bakery(P... products) : bakery_products(products...){}
	
	C getProfits() {
		return profits;
	}
	
	template <class Product> void sell(){
		static_assert(contains<Product,P...>::value,
		"This bakery doesn't contain this product!");
		
		static_assert(is_sellable<Product>::value, 
		"This product is not for sale!");
		
		Product& product = std::get<Product>(bakery_products);		
		if( product.getStock() > 0 ){
			product.sell();
			profits += product.getPrice();
		}
	}
	
	
	template <class Product> int getProductStock(){
		static_assert(contains<Product,P...>::value,
			"This bakery doesn't contain this product!");
		Product& product = std::get<Product>(bakery_products);
			return product.getStock();
	}
	
	
	//TODO
	template <class Product> void restock(int additionalStock){
	Product& product = std::get<Product>(bakery_products);
			
	}
};

#endif /* __BAKERY_H__ */

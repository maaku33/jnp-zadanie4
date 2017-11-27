#ifndef __BAKERY_H__
#define __BAKERY_H__

#include <type_traits>

template <class ... Trest>
struct unique_types;

template <class T1, class T2, class ... Trest>
struct unique_types<T1, T2, Trest ...>
 : unique_types<T1, T2>, unique_types<T1, Trest ...>, unique_types<T2, Trest ...> {};

template <class T1, class T2>
struct unique_types<T1, T2>
{
    static_assert(!std::is_same<T1, T2>::value, "Types must be unique");
};


template <typename C, typename A, A shelfArea, typename... P>
class Bakery<C,A,shelfAreaR,
          typename std::enable_if<std::is_integral<A>::value>::type,
          typename std::enable_if<std::is_floating_point<C>::value>::type> {
	
	static_assert( unique_types<P...>::value, "Types must be unique!"); 
	
	
	
	C profits = 0;
	A shelfArea;
	
public:	
	Bakery(P... products){
	
	}
	
	C getProfits() {
		return profits;
	}
	
	//????
	template <class Product> void sell(){
	}
	
	//????
	template <class Product> int getProductStock()
	}
	
	//????
	template <class Product> restock(int additionalStock){
	}
}

#endif /* __BAKERY_H__ */

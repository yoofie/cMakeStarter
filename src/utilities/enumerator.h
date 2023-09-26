/* **************************************
	File Name: ENUMERATOR
	Created: Monday September 25 2023
*************************************** */
#ifndef _ENUMERATOR_H_
#define _ENUMERATOR_H_

#include <tuple>
/* **************************************
	#defines
*************************************** */

/* **************************************
	Declarations
*************************************** */

/* **************************************
	Extras
*************************************** */
// http://marksrig:8081/r/cpp/comments/16r8k9j/enumeratelike_semantics_in_c/k21t39w/?context=3

template <typename T,
		  typename TIter = decltype(std::begin(std::declval<T>())),
		  typename = decltype(std::end(std::declval<T>()))>
constexpr auto enumerate(T &&iterable) {
	struct iterator {
		size_t i;
		TIter iter;
		bool operator!=(const iterator &other) const { return iter != other.iter; }
		void operator++() {
			++i;
			++iter;
		}
		auto operator*() const { return std::tie(i, *iter); }
	};
	struct iterable_wrapper {
		T iterable;
		auto begin() { return iterator{0, std::begin(iterable)}; }
		auto end() { return iterator{0, std::end(iterable)}; }
	};
	return iterable_wrapper{std::forward<T>(iterable)};
}

#endif

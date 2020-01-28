#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <functional>
#include <algorithm>
#include <iterator>
#include <vector>

namespace detail {

template <typename InputIt, typename OutputIt,
		  typename BinaryPred = std::less<std::iterator_traits<InputIt>::value_type>>
OutputIt merge(InputIt first1, InputIt last1,
               InputIt2 first2, InputIt2 last2,
               OutputIt d_first,
               BinaryPred comp = BinaryPred()){
	for (; first1 != last1; ++d_first) {
		if (first2 == last2) {
			return std::copy(first1, last1, d_first);
		}
		if (comp(*first2, *first1)) {
			*d_first = *first2;
			++first2;
		} else {
			*d_first = *first1;
			++first1;
		}
	}
	return std::copy(first2, last2, d_first);
}

}

template <typename FrwdIt,
	      typename BinaryPred = std::less<typename std::iterator_traits<FrwdIt>::value_type>>
void merge_sort(FrwdIt first, FrwdIt last, BinaryPred comp = BinaryPred()) {
	const auto len = std::distance(first, last);
	if (len <= 1) {
		return;
	}

	auto cut = first + len/2;
	merge_sort(first, cut, comp);
    merge_sort(cut, last, comp);
    std::vector<typename std::iterator_traits<FrwdIt>::value_type> tmp;
    tmp.reserve(len);
    detail::merge(first, cut, cut, last, std::back_inserter(tmp), comp);
    std::copy(tmp.begin(), tmp.end(), first);	
}
#endif
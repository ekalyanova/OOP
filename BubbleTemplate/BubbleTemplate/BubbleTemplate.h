#pragma once
#include <algorithm>

template <class RandomAccessIterator>
void Bsort(RandomAccessIterator first, RandomAccessIterator last) {
	auto it = last;
	for (auto it1 = first; it1 != last; it1++) {
		for (auto it2 = first; it2 != it; it2++) {
			if ((it2 + 1) == it)    
				break;              
			if (*it2 > *(it2 + 1)) {
				std::swap(*it2, *(it2 + 1));
			}
		}
		it--;
	}
}
template <class RandomAccessIterator, class Compare>
void Bsort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
	auto it = last;
	for (auto it1 = first; it1 != last; it1++) {
		for (auto it2 = first; it2 != it; it2++){
			if ((it2 + 1) == it)
				break;
			if (comp(*it2, *(it2 + 1))) {
				std::swap(*it2, *(it2 + 1));
			}
		}
		it--;
	}
}
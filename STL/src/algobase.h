//此文件定义一系列常用函数
#include<cstring>
#include"iterator.h"

namespace mystl {
	template <class T>
	const T& max(const T& lhs, const T& rhs) {
		return lhs < rhs ? rhs : lhs;
	}
	template <class T, class Compare>
	const T& max(const T& lhs, const T& rhs, Compare cmp) {
		return cmp(lhs, rhs) ? rhs : lhs;
	}
	template<class T>
	const T& min(const T& lhs, const T& rhs) {
		return rhs < lhs ? rhs : lhs;
	}
	template <class T, class Compare>
	const T& min(const T& lhs, const T& rhs, Compare cmp) {
		return cmp(rhs, lhs) ? rhs : lhs;
	}

	//拷贝函数的input_iterator_tag标准
	template <class Inputiterator, class Outiterator>
	Outiterator _unchecked_copy_cat(Inputiterator first, Inputiterator last,
		Outiterator result, mystl::input_iterator_tag) {
		for (; first != last; ++first, ++result) {
			*result = *first;
		}
		return result;
	}
	//拷贝函数的random_access_iterator_tag标准
	template <class Inputiterator, class Outiterator>
	Outiterator _unchecked_copy_cat(Inputiterator first, Inputiterator last,
		Outiterator result, mystl::random_access_iterator_tag) {
		auto n = last - first;

		for (; n > 0; --n, ++first, ++result) {
			*result = *first;
		}
		return result;
	}

	template<class Inputiterator, class Outputiterator>
	Outputiterator unchecked_copy(Inputiterator first, Inputiterator last,
		Outputiterator result) {
		return  _unchecked_copy_cat(first, last, result, iterator_category(first));
	}


	//unchecked_copy特化版本
	template <class T, class U>
	U* unchecked_copy(T* first, T* last, U* result) {
		const auto n = last - first;
		if (n != 0)
			std::memmove(result, first, n * sizeof(U));
		return result + n;
	}

	template <class Inputiterator, class Outputiterator>
	Outputiterator copy(Inputiterator first, Inputiterator last, Outputiterator result) {
		return unchecked_copy(first, last, result);
	}


	//ubchecked_backward
	template <class Bidirectionaliterator, class BidirectionalIter2>
	BidirectionalIter2 _unchecked_copy_backward_cat(Bidirectionaliterator first, Bidirectionaliterator last,
		BidirectionalIter2 result, mystl::bidirectional_iterator_tag) {
		while (last != first) {
			*--result = *--last;
		}
		return result;
	}

	template <class Randomaccessiterator, class BidirectionalIter2>
	BidirectionalIter2 _unchecked_copy_backward_cat(Randomaccessiterator first, Randomaccessiterator last,
		BidirectionalIter2 result, mystl::random_access_iterator_tag) {
		auto n = last - first;
		for (; n; --n) {
			*--result = *--last;
		}
		return result;
	}

	template <class Randomaccessiterator, class BidirectionalIter2>
	BidirectionalIter2 _unchecked_copy_backward(Randomaccessiterator first, Randomaccessiterator last,
		BidirectionalIter2 result) {
		return  _unchecked_copy_backward_cat(first, last, result, iterator_categoty(first));
	}

	template <class T, class U>
	U* _unchecked_copy_backward(T* first, T* last, U* result) {
		auto n = last - first;
		std::memmove(result - n, first, n * sizeof(T));
		return result - n;
	}

	template <class BidirectionalIter, class BidirectionalIter2>
	BidirectionalIter2 copy_backward(BidirectionalIter first, BidirectionalIter last,
		BidirectionalIter2 result) {
		return  _unchecked_copy_backward(first, last, result, iterator_categoty(first));
	}

	template<class InputIter, class OutputIter, class UnaryPredicate>
	OutputIter copy_if(InputIter first, InputIter last, OutputIter result, UnaryPredicate unary) {
		while (first != last) {
			if (unary(*first)) {
				*result++ = *first;
			}
			++first;
		}
		return result;
	}







}
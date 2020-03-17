#pragma once
//此文件定义一系列常用函数
#include<cstring>
#include"iterator.h"

namespace mystl {
	template <class T>
	const T& max(const T& lhs, const T& rhs) {
		return lhs < rhs ? rhs : lhs;
	}
	template <class T,class Compare>
	const T& max(const T& lhs, const T& rhs, Compare cmp) {
		return cmp(lhs, rhs) ? rhs : lhs;
	}
	template<class T>
	const T& min(const T& lhs, const T& rhs) {
		return rhs < lhs ? rhs : lhs;
	}
	template <class T,class Compare>
	const T& min(const T& lhs, const T& rhs, Compare cmp) {
		return cmp(rhs, lhs) ? rhs : lhs;
	}

	//拷贝函数的input_iterator_tag标准
	template <class Inputiterator,class Outiterator>
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
		iterator_traits<Inputiterator>::distance_type n =
			last - first;

		for (; n>0; --n,++first, ++result) {
			*result = *first;
		}
		return result;
	}

	template<class Inputiterator,class Outputiterator>
	Outputiterator unchecked_copy(Inputiterator first, Inputiterator last,
		Outputiterator result) {
		return unchecked_copy_cat(first, last, result, iterator_category(first));
	}












}
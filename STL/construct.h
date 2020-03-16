#pragma once

#include<new>
#include "iterator.h"


/*
此文件包含两个全局函数
construct：负责对象构建
destroy：负责对象的析构
*/
namespace mystl {


	//调用默认构造函数构建
	template <class Ty>
	void construct(Ty* ptr) {
		::new ((void*)ptr) Ty();
	}

	//一定要用const＋引用,此版本非默认构造函数，而是用另一个或同类型的拷贝构造函数
	template <class Ty1, class Ty2>
	void construct(Ty1* ptr, const Ty2& value) {
		::new ((void*)ptr) Ty1(value);
	}

	//destroy函数

	//该析构函数是无害的，所以可以不用调用节省资源，内存的释放destroy不干涉
	template <class Ty>
	void _destroy_one(Ty* ptr, std::true_type) {}

	//此函数析构函数有有害的，所以必须调用该类型的析构函数释放资源
	template <class Ty>
	void _destroy_one(Ty* ptr, std::false_type) {
		ptr->~Ty();
	}

	template <class Forwarditerator>
	void _destroy_cat(Forwarditerator first, Forwarditerator last, std::true_type) {}

	template <class Forwarditerator>
	void _destroy_cat(Forwarditerator first, Forwarditerator last, std::false_type) {
		//？ 是否可以destroy迭代器后再++
		//认为：destroy不同于erase，元素位置不发生变动，而且迭代器独立于容器，所以应该是可以的
		for (; first != last; ++first) {
			destroy(&*first);
		}
	}

	template <class Ty>
	void destroy(Ty* ptr) {
		_destroy_one(ptr, std::is_trivially_destructible<Ty>());
	}

	template <class Forwarditerator>
	void destroy(Forwarditerator first, Forwarditerator last) {
		_destroy_cat(first, last, std::is_trivially_destructible<
			value_type(Forwarditerator)>());
	}


}
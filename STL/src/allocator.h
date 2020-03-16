#pragma once

#include<cstddef>

namespace mystl {
	template <typename T>
	class allocator {
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

	public:
		static T* allocate();
		static T* allocate(size_type n);
		static void deallocate(T*);
		static void deallocate(T*, size_type);
		//static void construct(T*);

	};

	template <typename T>
	T* allocator<T>::allocate() {
		return static_cast<T*>(::operator new(sizeof(T)));
	}

	template <typename T>
	T* allocator<T>::allocate(size_type n) {
		//operator delete一个指针会删除整个数组
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}

	template <typename T>
	void allocator<T>::deallocate(T* ptr) {
		::operator delete(ptr);
	}

	template <typename T>
	void allocator<T>::deallocate(T* ptr, size_type) {
		::operator delete(ptr);
	}
}

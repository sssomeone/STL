#pragma once

#include"iterator.h"
namespace {
	template<class T>
	class vector {
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef	const T* const_pointer;
		typedef const T& const const_reference;
	public:
		typedef pointer iterator;
		typedef const_pointer const_iterator;
		typedef type_traits<iterator>::difference_type difference_type;
	public:
		typedef allocator<T>  data_allocator;
		typedef allocator<T>  allocator_type;
		typedef allocator_type::size_type size_type;


	public:
		iterator _begin;
		iterator _end;
		iterator _cap;
	public:
		vector():_begin(nullptr),_end(nullptr),_cap(nullptr){}
		difference_type size() {
			return _end - _begin;
		}
		difference_type capacity() {
			return _cap - _begin;
		}


		iterator& begin() {
			return _begin;
		}
		const_iterator& begin() const{
			return _begin;
		}
		iterator& end() {
			return _end;
		}
		const_iterator& end() const{
			return _end;
		}
		reference operator[](size_type n) {
			return *(_begin + n);
		}
		const_reference operator[](size_type n) const{
			return *(_begin + n);
		}

		reference front() {
			return *_begin;
		}
		const_reference front()const {
			return *_begin;
		}

		reference back() {
			return *(_end-1);
		}
		const_reference back()const {
			return *(_end-1);
		}













	};



}
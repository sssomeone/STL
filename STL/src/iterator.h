#pragma once
#include<cstddef>


namespace mystl {
	//五种类型的迭代器
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag :public input_iterator_tag {};
	struct bidirectional_iterator_tag :public forward_iterator_tag {};
	struct random_access_iterator_tag :public bidirectional_iterator_tag {};

	//便于继承，防止忘记提供这五种回答
	template <class Category, class T, class Distance = ptrdiff_t,
		class Pointer = T*, class Reference = T&>
		struct iterator {
		typedef	Category		iterator_category;
		typedef	T  				value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef Distance        difference_type;
	};

	//迭代器萃取剂

	template <class T>
	struct iterator_traits {
		typedef typename T::value_type value_type;
		typedef typename T::pointer    pointer;
		typedef typename T::reference reference;
		typedef typename T::difference_type difference_type;
		typedef typename T::iterator_category iterator_category;
	};

	//针对指针的偏特化版本

	template<class T>
	struct iterator_traits<T*> {
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef ptrdiff_t difference_type;
		typedef random_access_iterator_tag iterator_category;
	};

	//针对const T*的偏特化版本，防止value被推测为const类型
	template<class T>
	struct iterator_traits<const T*> {
		typedef T value_type;
		typedef const T& reference;
		typedef const T* pointer;
		typedef ptrdiff_t difference_type;
		typedef random_access_iterator_tag iterator_category;
	};

	/*
	为什么不直接用 Iterator::iterator_category？
	答：可以便于iterator_traits进行偏特化，这可以使得此类推断同时适合普通指针
	*/
	template <class Iterator>
	typename iterator_traits<Iterator>::iterator_category
		iterator_category(Iterator) {
		typedef typename iterator_traits<Iterator>::iterator_category Category;
		return Category();
	}

	//萃取某个迭代器的value_type
	template <class Iterator>
	typename iterator_traits<Iterator>::value_type*
		value_type(const Iterator&) {
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}

	//萃取某个迭代器的distance_type
	template <class Iterator>
	typename iterator_traits<Iterator>::distance_type*
		distance_type(const Iterator&) {
		return static_cast<typename iterator_traits<Iterator>::distance_type*>(0);
	}


	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type
		_distance(Iterator first, Iterator last, input_iterator_tag) {
		typename iterator_traits<Iterator>::difference_type n = 0;
		while (first != last) {
			++first;
			++n;
		}
		return n;
	}
	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type
		_distance(Iterator first, Iterator last, random_access_iterator_tag) {
		return last - first;
	}
	template <class Iterator>
	typename iterator_traits<Iterator>::difference_type
		distance(Iterator first, Iterator last) {
		return _distance(first, last, iterator_category(first));
	}




	template <class Iterator, class Distance>
	void _advance(Iterator& first, Distance n, input_iterator_tag) {
		while (n--) {
			++first;
		}
	}
	template <class Iterator, class Distance>
	void _advance(Iterator& first, Distance n, bidirectional_iterator_tag) {
		if (n > 0) {
			while (n--) {
				++first;
			}
		}
		else if (n < 0) {
			while (n++) {
				--first;
			}
		}
	}
	template <class Iterator, class Distance>
	void _advance(Iterator& first, Distance n, random_access_iterator_tag) {
		first += n;
	}
	template <class Iterator, class Distance>
	void advance(Iterator& first, Distance distance) {
		_advance(first, distance, iterator_category(first));
	}



	template <class Iterator>
	class reverse_iterator {
	private:
		Iterator current;
	public:
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer point;
		typedef typename iterator_traits<Iterator>::reference reference;
		typedef	typename iterator_traits<Iterator>::iterator_category iterator_category;

		typedef Iterator iterator_type;
		typedef reverse_iterator<Iterator> self;

	public:
		explicit reverse_iterator(iterator_type res) :current(res) {};
		reverse_iterator();
		reverse_iterator(const self& rhs) :current(rhs.current) {};

	public:
		iterator_type base() const {
			return current;
		}
		//反向迭代器对应正向迭代器的前一个位置
		reference operator*()const {
			iterator_type tmp = current;
			--tmp;
			return *tmp;
		}
		//反向++对应正向--
		self& operator++() {
			current--;
			return *this;
		}
		//后置++借助前置++完成
		self operator++(int) {
			self tmp = *this;
			++this;
			return tmp;
		}

		self& operator--() {
			current++;
			return *this;
		}
		self operator--(int) {
			self tmp = *this;
			--* this;
			return tmp;
		}

		self& operator+=(difference_type n) {
			current -= n;
			return *this;
		}

		self& operator-=(difference_type n) {
			current += n;
			return *this;
		}


		self operator+(difference_type n)const {
			return self(current - n);
		}

		self operator-(difference_type n)const {
			return self(current + n);
		}
		reference operator[](difference_type n) const {
			return *(*this + n);
		}
		//为什么不直接返回 this，
		point operator->() const {
			return &(operator*());
		}
	};

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type
		operator -(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() - rhs.base();
	}

	template <class Iterator>
	bool
		operator ==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() == rhs.base();
	}

	//不等于借助等于号实现
	template <class Iterator>
	bool
		operator !=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return !(lhs == rhs);
	}

	template <class Iterator>
	bool
		operator <(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() > rhs.base();
	}

	template <class Iterator>
	bool
		operator >(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		return lhs.base() < rhs.base();
	}


	template <class Iterator>
	bool
		operator >=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		//return lhs > rhs || lhs==rhs;
		return !(lhs < rhs);
	}

	template <class Iterator>
	bool
		operator <=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
		//return lhs < rhs || lhs==rhs;
		return !(lhs > rhs);
	}
}
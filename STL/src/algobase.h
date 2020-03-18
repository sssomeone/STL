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

	//¿½±´º¯ÊýµÄinput_iterator_tag±ê×¼
	template <class Inputiterator, class Outiterator>
	Outiterator _unchecked_copy_cat(Inputiterator first, Inputiterator last,
		Outiterator result, mystl::input_iterator_tag) {
		for (; first != last; ++first, ++result) {
			*result = *first;
		}
		return result;
	}
	//¿½±´º¯ÊýµÄrandom_access_iterator_tag±ê×¼
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


	//unchecked_copyÌØ»¯°æ±¾
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

#ifdef pair

	template <class InputIter,class Size,class OutIter>
	mystl::pair<InputIter, OutputIter> _unchecked_copy_n(InputIter first,Size n,OutIter result,mystl::input_iterator_tag){
		for(;n;n--){
			*result++=*first++
		}
		return mystl::pair<InputIter, OutputIter>(first,result);
	}
	
	template <class InputIter,class Size,class OutIter>
	mystl::pair<InputIter, OutputIter> _unchecked_copy_n(InputIter first,Size n,OutIter result,mystl::random_access_iterator_tag){
		auto last = first + n;
  		return mystl::pair<RandomIter, OutputIter>(last, mystl::copy(first, last, result));
	}

	template <class InputIter, class Size, class OutputIter>
	mystl::pair<InputIter, OutputIter> 
	copy_n(InputIter first, Size n, OutputIter result){
		return unchecked_copy_n(first, n, result, iterator_category(first));
	}
#endif


#ifdef move
	template <class InputIter, class OutputIter>
	OutputIter unchecked_move_cat(InputIter first, InputIter last, OutputIter result,
                   mystl::input_iterator_tag){
		for (; first != last; ++first, ++result){
			*result = mystl::move(*first);
		}
		return result;
	}

	// ramdom_access_iterator_tag 版本
	template <class RandomIter, class OutputIter>
	OutputIter unchecked_move_cat(RandomIter first, RandomIter last, OutputIter result,
                   mystl::random_access_iterator_tag)
	{
		for (auto n = last - first; n > 0; --n, ++first, ++result)
		{
		 *result = mystl::move(*first);
		}
		return result;
	}
#endif
	template <class InputIter, class OutputIter>
	OutputIter 
	unchecked_move(InputIter first, InputIter last, OutputIter result)
	{
  		return unchecked_move_cat(first, last, result, iterator_category(first));
	}

	// 为 trivially_copy_assignable 类型提供特化版本
	template <class Tp, class Up>
	Up* unchecked_move(Tp* first, Tp* last, Up* result)
	{
		const size_t n = static_cast<size_t>(last - first);
		std::memmove(result, first, n * sizeof(Up));
		return result + n;
	}
	template <class InputIter, class OutputIter>
	OutputIter move(InputIter first, InputIter last, OutputIter result){
		return unchecked_move(first, last, result);
	}

	template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2
unchecked_move_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last,
                            BidirectionalIter2 result, mystl::bidirectional_iterator_tag)
{
  while (first != last)
    *--result = mystl::move(*--last);
  return result;
}

// random_access_iterator_tag 版本
template <class RandomIter1, class RandomIter2>
RandomIter2
unchecked_move_backward_cat(RandomIter1 first, RandomIter1 last,
                            RandomIter2 result, mystl::random_access_iterator_tag)
{
  for (auto n = last - first; n > 0; --n)
    *--result = mystl::move(*--last);
  return result;
}

template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2
unchecked_move_backward(BidirectionalIter1 first, BidirectionalIter1 last, 
                        BidirectionalIter2 result)
{
  return unchecked_move_backward_cat(first, last, result,
                                     iterator_category(first));
}

// 为 trivially_copy_assignable 类型提供特化版本
template <class Tp, class Up>
Up *
unchecked_move_backward(Tp* first, Tp* last, Up* result)
{
  const size_t n = static_cast<size_t>(last - first);
  if (n != 0)
  {
    result -= n;
    std::memmove(result, first, n * sizeof(Up));
  }
  return result;
}

template <class BidirectionalIter1, class BidirectionalIter2>
BidirectionalIter2
move_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result)
{
  return unchecked_move_backward(first, last, result);
}



template <class Iterator,class  Iterator2>
bool equal(Iterator first,Iterator last,Iterator2 first2){
	while(first!=last){
		if(*first!=*first2)return false;
		++first,++first2;
	}
	return true;
}


template <class InputIter1, class InputIter2, class Compared>
bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2, Compared comp)
{
  for (; first1 != last1; ++first1, ++first2)
  {
    if (!comp(*first1, *first2))  
      return false;
  }
  return true;
}

template <class OutputIter,class Size,class T>
OutputIter unchecked_fill_n(OutputIter first,Size n,const T&value){
	for(;n;--n,++first){
		*first=value;
	}
	return first;
}

template <class Tp,class Size,class Up>
Tp* unchecked_fill_n(Tp *first,Size n,Up value){
	std::memset(first, (unsigned char)value, (size_t)(n));
	return first+n;
}

template <class OutputIter,class Size,class T>
OutputIter fill_n(OutputIter first,Size n,const T& value){
	return unchecked_fill_n(first,n,value);
}


//input_iterator严格的只能在只读，所以最低要求是forward_iterator
template <class ForwardIter, class T>
void fill_cat(ForwardIter first, ForwardIter last, const T& value,
              mystl::forward_iterator_tag)
{
  for (; first != last; ++first)
  {
    *first = value;
  }
}


template <class RandomIter, class T>
void fill_cat(RandomIter first, RandomIter last, const T& value,
              mystl::random_access_iterator_tag)
{
  fill_n(first, last - first, value);
}

template <class ForwardIter, class T>
void fill(ForwardIter first, ForwardIter last, const T& value)
{
  fill_cat(first, last, value, iterator_category(first));
}


template <class InputIter1, class InputIter2>
bool lexicographical_compare(InputIter1 first1, InputIter1 last1,
                             InputIter2 first2, InputIter2 last2)
{
  for (; first1 != last1 && first2 != last2; ++first1, ++first2)
  {
    if (*first1 < *first2)
      return true;
    if (*first2 < *first1)
      return false;
  }
  return first1 == last1 && first2 != last2;
}



// 重载版本使用函数对象 comp 代替比较操作
template <class InputIter1, class InputIter2, class Compred>
bool lexicographical_compare(InputIter1 first1, InputIter1 last1,
                             InputIter2 first2, InputIter2 last2, Compred comp)
{
  for (; first1 != last1 && first2 != last2; ++first1, ++first2)
  {
    if (comp(*first1, *first2))
      return true;
    if (comp(*first2, *first1))
      return false;
  }
  return first1 == last1 && first2 != last2;
}

// 针对 const unsigned char* 的特化版本
bool lexicographical_compare(const unsigned char* first1,
                             const unsigned char* last1,
                             const unsigned char* first2,
                             const unsigned char* last2)
{
  const auto len1 = last1 - first1;
  const auto len2 = last2 - first2;
  // 先比较相同长度的部分
  const auto result = std::memcmp(first1, first2, mystl::min(len1, len2));
  // 若相等，长度较长的比较大
  return result != 0 ? result < 0 : len1 < len2;
}

/*****************************************************************************************/
// mismatch
// 平行比较两个序列，找到第一处失配的元素，返回一对迭代器，分别指向两个序列中失配的元素
/*****************************************************************************************/

#ifdef pair
template <class InputIter1, class InputIter2>
mystl::pair<InputIter1, InputIter2> 
mismatch(InputIter1 first1, InputIter1 last1, InputIter2 first2)
{
  while (first1 != last1 && *first1 == *first2)
  {
    ++first1;
    ++first2;
  }
  return mystl::pair<InputIter1, InputIter2>(first1, first2);
}

// 重载版本使用函数对象 comp 代替比较操作
template <class InputIter1, class InputIter2, class Compred>
mystl::pair<InputIter1, InputIter2> 
mismatch(InputIter1 first1, InputIter1 last1, InputIter2 first2, Compred comp)
{
  while (first1 != last1 && comp(*first1, *first2))
  {
    ++first1;
    ++first2;
  }
  return mystl::pair<InputIter1, InputIter2>(first1, first2);
}
#endif





	



}
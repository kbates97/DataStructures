#pragma once

#ifndef ForwardIterator_H
#define ForwardIterator_H

#include "ListIterator.h"

template<class T>
class ForwardIterator :public ListIterator<T>
{
public:
	ForwardIterator() = default;
	~ForwardIterator() = default;
	ForwardIterator(const ForwardIterator<T> & copy) noexcept;
	ForwardIterator(ForwardIterator<T> && copy) noexcept;
	ForwardIterator(const ListNode<T>* node) noexcept;
	ForwardIterator<T> & operator=(const ForwardIterator<T> & rhs) noexcept;
	ForwardIterator<T> & operator=(ForwardIterator<T> && rhs) noexcept;
	ListNode<T>* operator=(const ListNode<T>* rhs) noexcept override;
	ForwardIterator<T> & operator++() noexcept;
	ForwardIterator<T> operator++(int) noexcept;
	friend bool operator==(ForwardIterator<T>& lhs, ForwardIterator<T> & rhs) noexcept;
	friend bool operator!=(ForwardIterator<T>& lhs, ForwardIterator<T> & rhs) noexcept;

	void MoveNext() noexcept override;
	void Reset() noexcept override;
};


template<class T>
inline ForwardIterator<T>::ForwardIterator(const ForwardIterator<T>& copy) noexcept
{
	*this = copy;
}

template<class T>
inline ForwardIterator<T>::ForwardIterator(ForwardIterator<T>&& copy) noexcept
{
	*this = copy;
}

template<class T>
inline ForwardIterator<T>::ForwardIterator(const ListNode<T>* node) noexcept
{
	node_ = const_cast<ListNode<T>*>(node);
}

template<class T>
inline ForwardIterator<T>& ForwardIterator<T>::operator=(const ForwardIterator<T>& rhs) noexcept
{
	node_ = rhs.node_;
	done_ = rhs.done_;
	return *this;
}

template<class T>
inline ForwardIterator<T>& ForwardIterator<T>::operator=(ForwardIterator<T>&& rhs) noexcept
{
	node_ = rhs.node_;
	done_ = rhs.done_;
	rhs.done_ = true;
	rhs.node_ = nullptr;
	return *this;
}

template<class T>
inline ListNode<T>* ForwardIterator<T>::operator=(const ListNode<T>* rhs) noexcept
{
	node_ = const_cast<ListNode<T>*>(rhs);
	return node_;
}

template<class T>
inline ForwardIterator<T>& ForwardIterator<T>::operator++() noexcept
{
	MoveNext();
	return *this;
}

template<class T>
inline ForwardIterator<T> ForwardIterator<T>::operator++(int) noexcept
{
	MoveNext();
	return *this;
}

template<class T>
inline bool operator==(ForwardIterator<T>& lhs, ForwardIterator<T>& rhs) noexcept
{
	return lhs.GetCurrent() == rhs.GetCurrent();
}

template<class T>
inline bool operator!=(ForwardIterator<T>& lhs, ForwardIterator<T>& rhs) noexcept
{
	return !(lhs.GetCurrent() == rhs.GetCurrent());
}

template<class T>
inline void ForwardIterator<T>::MoveNext() noexcept
{
	node_ = node_->GetNext();
}

template<class T>
inline void ForwardIterator<T>::Reset() noexcept
{
	done_ = true;
	node_ = nullptr;
}


#endif // !ForwardIterator_H
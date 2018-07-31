#pragma once

#ifndef BackwardIterator_H
#define BackwardIterator_H

#include "ListIterator.h"

template<class T>
class BackwardIterator :public ListIterator<T>
{
public:
	BackwardIterator() = default;
	~BackwardIterator() = default;
	BackwardIterator(const BackwardIterator<T> & copy) noexcept;
	BackwardIterator(BackwardIterator<T> && copy) noexcept;
	BackwardIterator(const ListNode<T>* node) noexcept;
	BackwardIterator<T> & operator=(const BackwardIterator<T> & rhs) noexcept;
	BackwardIterator<T> & operator=(BackwardIterator<T> && rhs) noexcept;
	ListNode<T>* operator=(const ListNode<T>* rhs) noexcept override;
	BackwardIterator<T> & operator++() noexcept;
	BackwardIterator<T> operator++(int) noexcept;
	bool operator==(ListIterator<T> & rhs) noexcept;
	bool operator!=(ListIterator<T> & rhs) noexcept;

	void MoveNext() noexcept override;
	void Reset() noexcept override;
};

#endif // !BackwardIterator_H

template<class T>
inline BackwardIterator<T>::BackwardIterator(const BackwardIterator<T>& copy) noexcept
{
	*this = copy;
}

template<class T>
inline BackwardIterator<T>::BackwardIterator(BackwardIterator<T>&& copy) noexcept
{
	*this = copy;
}

template<class T>
inline BackwardIterator<T>::BackwardIterator(const ListNode<T>* node) noexcept
{
	node_ = const_cast<ListNode<T>*>(node);
}

template<class T>
inline BackwardIterator<T>& BackwardIterator<T>::operator=(const BackwardIterator<T>& rhs) noexcept
{
	node_ = rhs.node_;
	done_ = rhs.done_;
	return *this;
}

template<class T>
inline BackwardIterator<T>& BackwardIterator<T>::operator=(BackwardIterator<T>&& rhs) noexcept
{
	node_ = rhs.node_;
	done_ = rhs.done_;
	rhs.done_ = true;
	rhs.node_ = nullptr;
	return *this;
}

template<class T>
inline ListNode<T>* BackwardIterator<T>::operator=(const ListNode<T>* rhs) noexcept
{
	node_ = const_cast<ListNode<T>*>(rhs);
	return node_;
}

template<class T>
inline BackwardIterator<T>& BackwardIterator<T>::operator++() noexcept
{
	MoveNext();
	return *this;
}

template<class T>
inline BackwardIterator<T> BackwardIterator<T>::operator++(int) noexcept
{
	MoveNext();
	return *this;
}

template<class T>
inline bool BackwardIterator<T>::operator==(ListIterator<T>& rhs) noexcept
{
	return (*this == rhs.GetCurrent());
}

template<class T>
inline bool BackwardIterator<T>::operator!=(ListIterator<T>& rhs) noexcept
{
	return !(*this == rhs.GetCurrent());
}

template<class T>
inline void BackwardIterator<T>::MoveNext() noexcept
{
	node_ = node_->GetPrevious();
}

template<class T>
inline void BackwardIterator<T>::Reset() noexcept
{
	done_ = true;
	node_ = nullptr;
}
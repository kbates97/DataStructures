#pragma once

#ifndef ListIterator_H
#define ListIterator_H

#include "Iterator.h"
#include "ListNode.h"
#include "AdtException.h"

template<class T>
class ListIterator : public Iterator<T>
{
protected:
	ListNode<T>* node_ = nullptr;
	bool done_ = true;

	ListIterator() = default;
	~ListIterator() = default;
	ListIterator(const ListIterator<T> & copy) noexcept;
	ListIterator(ListIterator<T> && copy) noexcept;
public:
	ListIterator<T> & operator=(const ListIterator<T>& rhs) noexcept;
	ListIterator<T> & operator=(ListIterator<T> && rhs) noexcept;
	T & operator*() const noexcept(false);
	virtual ListNode<T>* operator=(const ListNode<T>* rhs) noexcept = 0;

	bool IsDone() const noexcept override;
	T & GetCurrent() const noexcept(false) override;
};

#endif // !ListIterator_H

template<class T>
inline ListIterator<T>::ListIterator(const ListIterator<T>& copy) noexcept
{
	*this = copy;
}

template<class T>
inline ListIterator<T>::ListIterator(ListIterator<T>&& copy) noexcept
{
	*this = copy;
}

template<class T>
inline ListIterator<T>& ListIterator<T>::operator=(const ListIterator<T>& rhs) noexcept
{
	node_ = rhs.node_;
	done_ = rhs.done_;

	return *this;
}

template<class T>
inline ListIterator<T>& ListIterator<T>::operator=(ListIterator<T>&& rhs) noexcept
{
	node = rhs.node_;
	done = rhs.done_;
	rhs.done_ = true;
	rhs.node_ = nullptr;

	return *this;
}

template<class T>
inline T & ListIterator<T>::operator*() const noexcept(false)
{
	return GetCurrent();
}

template<class T>
inline T & ListIterator<T>::GetCurrent() const noexcept(false)
{
	if (node_ == nullptr)
		throw AdtException("Out of bounds");
	return node_->GetData();
}

template<class T>
inline bool ListIterator<T>::IsDone() const noexcept
{
	return done_;
}
#pragma once

#ifndef ListNode_H
#define ListNode_H

#include "Node.h"

template<class T>
class ListNode : public Node<T>
{
public:
	ListNode() = default;
	ListNode(const T& data, ListNode<T>* next = nullptr, ListNode<T>* previous = nullptr) noexcept;
	ListNode(const ListNode<T>& copy) noexcept;
	ListNode(ListNode<T>&& copy) noexcept;
	~ListNode() = default;
	ListNode<T>& operator=(const ListNode<T>& rhs) noexcept;
	ListNode<T>& operator= (ListNode<T>&& rhs) noexcept;

	ListNode<T>* GetNext() noexcept;
	ListNode<T>* GetPrevious() noexcept;
	void SetNext(const ListNode<T> * next) noexcept;
	void SetPrevious(const ListNode<T>* prev) noexcept;
private:
	ListNode<T>* next_ = nullptr;
	ListNode<T>* previous_ = nullptr;
};

#endif // !ListNode_H

template<class T>
inline ListNode<T>::ListNode(const T & data, ListNode<T>* next, ListNode<T>* previous) noexcept
{
	this->SetData(data);
	this->next_ = next;
	this->previous_ = previous;
}

template<class T>
inline ListNode<T>::ListNode(const ListNode<T>& copy) noexcept
{
	this = copy;
}

template<class T>
inline ListNode<T>::ListNode(ListNode<T>&& copy) noexcept
{
	this = *copy;
	copy.~ListNode();
}

template<class T>
inline ListNode<T>& ListNode<T>::operator=(const ListNode<T>& rhs) noexcept
{
	this->data_ = rhs.data_;
	this->next_ = rhs.next_;
	this->previous_ = rhs.previous_;
	return *this;
}

template<class T>
inline ListNode<T>& ListNode<T>::operator=(ListNode<T>&& rhs) noexcept
{
	this = *rhs;
	rhs.~ListNode();
}

template<class T>
inline ListNode<T>* ListNode<T>::GetNext() noexcept
{
	return this->next_;
}

template<class T>
inline ListNode<T>* ListNode<T>::GetPrevious() noexcept
{
	return this->previous_;
}

template<class T>
inline void ListNode<T>::SetNext(const ListNode<T>* next) noexcept
{
	this->next_ = const_cast<ListNode<T>*>(next);
}

template<class T>
inline void ListNode<T>::SetPrevious(const ListNode<T>* prev) noexcept
{
	this->previous_ = const_cast<ListNode<T>*>(prev);
}

#pragma once

#ifndef List_H
#define List_H

#include "ListNode.h"
#include "Array.h"


template<class T>
class List
{
public:
	List() = default;
	List(const List<T>& copy) noexcept(false);
	List(List<T>&& copy) noexcept;
	~List() noexcept;
	List<T>& operator=(const List<T>& rhs) noexcept(false);
	List<T>& operator=(List<T>&& rhs) noexcept;

	void Append(const T& data) noexcept(false);
	void Extract(const T& data) noexcept(false);
	void InsertAfter(const T& data, const T& after) noexcept(false);
	void InsertBefore(const T& data, const T& before) noexcept(false);
	void Prepend(const T& data) noexcept(false);
	void Purge() noexcept(false);
	T& Last() noexcept(false);
	T Last() const noexcept(false);
	T& First() noexcept(false);
	T First() const noexcept(false);
	ListNode<T>* GetHead() const noexcept;
	ListNode<T>* GetTail() const noexcept;
	const bool IsEmpty() noexcept;

	List(const T* data, size_t & size) noexcept(false);
	List(const Array<T> array) noexcept(false);
	Array<T> & ToArray() noexcept(false);
private:
	ListNode<T>* head_ = nullptr;
	ListNode<T>* tail_ = nullptr;
};

#endif

template<class T>
inline List<T>::List(const T * data, size_t & size) noexcept(false)
{
	for (size_t i = 0; i < size; ++i)
	{
		Append(data[i]);
	}
}

template<class T>
inline List<T>::List(const Array<T> array) noexcept(false)
{
	for (size_t i = 0; i < array.GetLength(); ++i)
	{
		Append(array[i]);
	}
}

template<class T>
inline Array<T>& List<T>::ToArray() noexcept(false)
{
	int size = 0;
	ListNode<T>* trav = head_;
	for (auto list_node = head_; list_node != nullptr; list_node = list_node->GetNext())
	{
		++size;
	}
	Array<T> temp = new Array(size);
	for (size_t i = 0; i < size; ++i)
	{
		temp[i] = trav->GetData();
		trav = trav->GetNext();
	}
	return temp;
}

template<class T>
inline List<T>::List(const List<T> & copy) noexcept(false)
{
	*this = copy;
}

template<class T>
inline List<T>::List(List<T> && copy) noexcept
{
	*this = copy;
}

template<class T>
inline List<T>::~List() noexcept
{
	Purge();
}

template<class T>
inline List<T> & List<T>::operator=(const List<T> & rhs) noexcept(false)
{
	this->~List();
	for (ListNode<T>* list_node = rhs.head_; list_node != nullptr; list_node = list_node->GetNext())
	{
		this->Append(list_node->GetData());
	}
	return *this;
}

template<class T>
inline List<T> & List<T>::operator=(List<T> && rhs) noexcept
{
	this->~List();
	for (ListNode<T>* list_node = rhs.head_; list_node != nullptr; list_node = list_node->GetNext())
	{
		this->Append(list_node->GetData());
	}
	rhs.~List();
	return *this;
}

template<class T>
inline void List<T>::Append(const T & data) noexcept(false)
{
	ListNode<T>* newNode = new ListNode<T>(data, nullptr, tail_);
	this->tail_->SetNext(newNode);
	this->tail_ = newNode;
	if (this->head_ == nullptr)
		this->head_ = newNode;
}

template<class T>
inline void List<T>::Extract(const T & data) noexcept(false)
{
	ListNode<T>* travel = head_;
	while (travel->GetData() != data && travel->GetNext() != nullptr)
		travel = travel->GetNext();
	if (travel->GetData() != data)
		return;//throw exception data not found
	travel->GetNext()->SetPrevious(travel->GetPrevious());
	travel->GetPrevious()->SetNext(travel->GetNext());
	delete travel;
}

template<class T>
inline void List<T>::InsertAfter(const T & data, const T & after) noexcept(false)
{
	ListNode<T>* travel = head_;
	while (travel->GetData() != after && travel->GetNext() != nullptr)
		travel = travel->GetNext();
	if (travel->GetData() != after)
		return;//error: item not found
	if (travel == tail_)
		Append(data);
	else
	{
		ListNode<T>* newNode = new ListNode<T>(data, travel->GetNext(), travel);
		travel->SetNext(newNode);
		newNode->GetNext()->SetPrevious(newNode);
	}
}

template<class T>
inline void List<T>::InsertBefore(const T & data, const T & before) noexcept(false)
{
	ListNode<T>* travel = head_;
	while (travel->GetData() != before && travel->GetNext() != nullptr)
		travel = travel->GetNext();
	if (travel->GetData() != before)
		return;//error: item not found
	if (travel == head_)
		Prepend(data);
	else
	{
		ListNode<T>* newNode = new ListNode<T>(data, travel, travel->GetPrevious());
		travel->SetPrevious(newNode);
		newNode->GetPrevious()->SetNext(newNode);
	}
}

template<class T>
inline void List<T>::Prepend(const T & data) noexcept(false)
{
	ListNode<T>* newNode = new ListNode<T>(data, head_, nullptr);
	this->head_->SetPrevious(newNode);
	this->head_ = newNode;
	if (this->tail_ == nullptr)
		this->tail_ = newNode;
}

template<class T>
inline void List<T>::Purge() noexcept(false)
{
	if (head_ == nullptr)
		return;
	while (head_->GetNext() != nullptr)
	{
		head_ = head_->GetNext();
		delete head_->GetPrevious();
		//head_->SetPrevious(nullptr);
	}
	delete head_;
	delete tail_;
}

template<class T>
inline T & List<T>::Last() noexcept(false)
{
	return tail_->GetData();
}

template<class T>
inline T List<T>::Last() const noexcept(false)
{
	return tail_->GetData();
}

template<class T>
inline T & List<T>::First() noexcept(false)
{
	return head_->GetData();
}

template<class T>
inline T List<T>::First() const noexcept(false)
{
	return head_->GetData();
}

template<class T>
inline ListNode<T>* List<T>::GetHead() const noexcept
{
	return head_;
}

template<class T>
inline ListNode<T>* List<T>::GetTail() const noexcept
{
	return tail_;
}

template<class T>
inline const bool List<T>::IsEmpty() noexcept
{
	if (head_ == nullptr)
		return true;
	return false;
}

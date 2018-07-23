#pragma once

#ifndef List_H
#define List_H

#include "ListNode.h"
#include "Array.h"
#include "ForwardIterator.h"
#include "BackwardIterator.h"

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

	ForwardIterator<T> ForwardBegin();
	ForwardIterator<T> ForwardEnd();
	BackwardIterator<T> BackwardBegin();
	BackwardIterator<T> BackwardEnd();
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
inline ForwardIterator<T> List<T>::ForwardBegin()
{
	return ForwardIterator<T>(head_);
}

template<class T>
inline ForwardIterator<T> List<T>::ForwardEnd()
{
	return ForwardIterator<T>(tail_->GetNext());
}

template<class T>
inline BackwardIterator<T> List<T>::BackwardBegin()
{
	return BackwardIterator<T>(tail_);
}

template<class T>
inline BackwardIterator<T> List<T>::BackwardEnd()
{
	return BackwardIterator<T>(head_->GetPrevious());
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
	copy.Purge();
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
	rhs.Purge();
	return *this;
}

template<class T>
inline void List<T>::Append(const T & data) noexcept(false)
{
	if (tail_ != nullptr)
	{
		tail_ = new ListNode<T>(data, nullptr, tail_);
		tail_->GetPrevious()->SetNext(tail_);
	}
	else
	{
		head_ = tail_ = new ListNode<T>(data);
	}

}

template<class T>
inline void List<T>::Extract(const T & data) noexcept(false)
{
	ListNode<T>* travel = head_;
	while (travel->GetData() != data && travel->GetNext() != nullptr)
		travel = travel->GetNext();
	if (travel->GetData() != data)
		return;//throw exception data not found
	if (travel->GetNext())
	{
		travel->GetNext()->SetPrevious(travel->GetPrevious());
	}
	else
		tail_ = travel->GetPrevious();
	if (travel->GetPrevious())
	{

		travel->GetPrevious()->SetNext(travel->GetNext());
	}
	else
		head_ = travel->GetNext();
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
	if (head_ != nullptr)
	{
		head_ = new ListNode<T>(data, head_, nullptr);
		head_->GetNext()->SetPrevious(head_);
	}
	else
	{
		head_ = tail_ = new ListNode<T>(data, nullptr, nullptr);
	}
}

template<class T>
inline void List<T>::Purge() noexcept(false)
{
	while (head_)
	{
		auto temp = head_->GetNext();
		delete head_;
		head_ = temp;
	}
	head_ = tail_ = nullptr;
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

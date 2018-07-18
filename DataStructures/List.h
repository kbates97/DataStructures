#pragma once

#ifndef List_H
#define List_H

#include "ListNode.h"

template<class T>
class List
{
public:
	List() = default;
	List(const List& copy) noexcept(false);
	List(List&& copy) noexcept;
	~List() noexcept;
	List& operator=(const List& rhs) noexcept(false);
	List& operator=(List&& rhs) noexcept;

	void Append(const T& data) noexcept(false);
	void Extract(const T& data) noexcept(false);
	void InsertAfter(const T& data, const T& after) noexcept(false);
	void InsertBefore(const T& data, const T& before) noexcept(false);
	void Prepend(const T& data) noexcept(false);
	void Purge() noexcept(false);
	T& Last() noexcept(false);
	T Last() const noexcept(false);
	T& First() noexcept(false);
	T Last() const noexcept(false);
	const ListNode* GetHead() noexcept;
	const ListNode* GetTail() noexcept;
	const bool IsEmpty() noexcept;
private:
	ListNode<T>* head_ = nullptr;
	ListNode<T>* tail_ = nullptr;
};

#endif // !List_H

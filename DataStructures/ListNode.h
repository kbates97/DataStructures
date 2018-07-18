#pragma once

#ifndef ListNode_H
#define ListNode_H

template<class T>
class ListNode
{
public:
	ListNode() = default;
	ListNode(const T& data, ListNode<T>* next = nullptr, ListNode<T>* previous = nullptr) noexcept;
	ListNode(const ListNode<T>& copy) noexcept;
	ListNode(ListNode<T>&& copy) noexcept;
	ListNode() = default;
	ListNode<T>& operator=(const ListNode<T>& rhs) noexcept;
	ListNode<T>& oeprator = (ListNode<T>&& rhs) noexcept;

	ListNode<T>* GetNext() noexcept;
	ListNode<T>* GetPrevious() noexcept;
	void SetNext(const ListNode<T> * next) noexcept;
	void SetPrevious(const ListNode<T>* prev) noexcept;
private:
	ListNode<T>* next_ = nullptr;
	ListNode<T>* previous_ = nullptr;
};

#endif // !ListNode_H

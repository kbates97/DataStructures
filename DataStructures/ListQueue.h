#ifndef LINKEDLIST_QUEUE
#define LINKEDLIST_QUEUE

#include <iostream>
#include "AdtException.h"
#include "List.h"

template <class T>
class ListQueue
{
public:
	ListQueue();
	ListQueue(const ListQueue& copy) noexcept(false);
	ListQueue& operator= (const ListQueue& rhs) noexcept(false);
	ListQueue(ListQueue&& copy) noexcept;
	ListQueue& operator = (ListQueue&& rhs) noexcept;
	void Enqueue(T item) noexcept(false);
	T Dequeue() noexcept(false);
	T& Front() noexcept(false);
	size_t Size() const noexcept;
	bool IsEmpty() noexcept;
	void Clear() noexcept;

private:
	List<T> queue_;
	size_t size_ = 0;
};


#endif
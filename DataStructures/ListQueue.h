#ifndef LINKEDLIST_QUEUE
#define LINKEDLIST_QUEUE

#include <iostream>
#include "AdtException.h"
#include "List.h"

template <class T>
class ListQueue
{
public:
	ListQueue() = default;
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

template<class T>
inline ListQueue<T>::ListQueue(const ListQueue & copy) noexcept(false)
{
	*this = copy;
}

template<class T>
inline ListQueue<T> & ListQueue<T>::operator=(const ListQueue & rhs) noexcept(false)
{
	queue_ = rhs.queue_;
	size_ = rhs.size_;
	return *this;
}

template<class T>
inline ListQueue<T>::ListQueue(ListQueue && copy) noexcept
{
	*this = copy;
	copy.Clear();
}

template<class T>
inline ListQueue<T> & ListQueue<T>::operator=(ListQueue && rhs) noexcept
{
	queue_ = rhs.queue_;
	size_ = rhs.size_;
	rhs.Clear();
	return *this;
}

template<class T>
inline void ListQueue<T>::Enqueue(T item) noexcept(false)
{
	queue_.Append(item);
	++size_;
}

template<class T>
inline T ListQueue<T>::Dequeue() noexcept(false)
{
	if (size_ == 0)
		throw AdtException("Underflow");
	T data = queue_.First();
	queue_.Extract(data);
	--size_;
	return data;
}

template<class T>
inline T & ListQueue<T>::Front() noexcept(false)
{
	return queue_.First();
}

template<class T>
inline size_t ListQueue<T>::Size() const noexcept
{
	return size_;
}

template<class T>
inline bool ListQueue<T>::IsEmpty() noexcept
{
	return size_ == 0;
}

template<class T>
inline void ListQueue<T>::Clear() noexcept
{
	size_ = 0;
	queue_.Purge();
}

#ifndef ARRAY_QUEUE
#define ARRAY_QUEUE

#include "AdtException.h"
#include "Array.h"

template <class T>
class ArrayQueue
{
public:
	ArrayQueue() noexcept(false);
	ArrayQueue(size_t size) noexcept(false);
	~ArrayQueue() = default;
	ArrayQueue(const ArrayQueue<T>& copy) noexcept(false);
	ArrayQueue<T> & operator=(const ArrayQueue<T>& rhs) noexcept(false);
	ArrayQueue(ArrayQueue<T>&& copy) noexcept;
	ArrayQueue<T> & operator=(ArrayQueue<T>&& rhs) noexcept;
	void Enqueue(T data) noexcept(false);
	T Dequeue() noexcept(false);
	T& Front() noexcept(false);
	size_t Size() const noexcept;
	bool IsEmpty() const noexcept;
	bool IsFull() const noexcept;
	void Clear() noexcept;

private:
	Array<T> queue_;
	size_t size_ = 0;

};



#endif

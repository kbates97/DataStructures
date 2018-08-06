#ifndef ARRAY_QUEUE
#define ARRAY_QUEUE

#include "AdtException.h"
#include "Array.h"

template <class T>
class ArrayQueue
{
public:
	ArrayQueue() noexcept(false) = default;
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

template<class T>
inline ArrayQueue<T>::ArrayQueue(size_t size) noexcept(false)
{
	queue_.SetLength(size);
}

template<class T>
inline ArrayQueue<T>::ArrayQueue(const ArrayQueue<T>& copy) noexcept(false)
{
	*this = copy;
}

template<class T>
inline ArrayQueue<T>& ArrayQueue<T>::operator=(const ArrayQueue<T>& rhs) noexcept(false)
{
	queue_ = rhs.queue_;
	size_ = rhs.size_;
	return *this;
}

template<class T>
inline ArrayQueue<T>::ArrayQueue(ArrayQueue<T>&& copy) noexcept
{
	*this = copy;
	copy.Clear();
}

template<class T>
inline ArrayQueue<T>& ArrayQueue<T>::operator=(ArrayQueue<T>&& rhs) noexcept
{
	queue_ = rhs.queue_;
	size_ = rhs.size_;
	rhs.Clear();
	return *this;
}

template<class T>
inline void ArrayQueue<T>::Enqueue(T data) noexcept(false)
{
	if (size_ >= queue_.GetLength())
		throw AdtException("Overflow");
	queue_[size_++] = data;
}

template<class T>
inline T ArrayQueue<T>::Dequeue() noexcept(false)
{
	if (size_ <= 0)
		throw AdtException("Underflow");
	T data = queue_[0];
	for (size_t i = 0; i < size_ - 1; ++i)
	{
		queue_[i] = queue_[i + 1];
	}
	--size_;
	return data;
}

template<class T>
inline T & ArrayQueue<T>::Front() noexcept(false)
{
	return queue_[0];
}

template<class T>
inline size_t ArrayQueue<T>::Size() const noexcept
{
	return size_;
}

template<class T>
inline bool ArrayQueue<T>::IsEmpty() const noexcept
{
	return size_ == 0;
}

template<class T>
inline bool ArrayQueue<T>::IsFull() const noexcept
{
	return size_ == queue_.GetLength();
}

template<class T>
inline void ArrayQueue<T>::Clear() noexcept
{
	size_ = 0;
}

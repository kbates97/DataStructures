
#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include "Array.h"
#include "AdtException.h"

template <class T>
class ArrayStack
{
public:
	ArrayStack(const size_t size = 10) noexcept(false);
	~ArrayStack() = default;
	ArrayStack(const ArrayStack& copy) noexcept(false);
	ArrayStack<T>& operator=(const ArrayStack& rhs) noexcept(false);
	ArrayStack(ArrayStack&& copy) noexcept;
	ArrayStack<T>& operator=(ArrayStack&& rhs) noexcept;
	bool IsEmpty() const noexcept;
	bool IsFull() const noexcept;
	size_t Size() const noexcept;
	void Push(const T& data) noexcept(false);
	T Pop() noexcept(false);
	T Peek() const noexcept(false);
	void Clear() noexcept;

private:
	Array<T> stack_;
	size_t numItems_ = 0;
};



#endif    

template<class T>
inline ArrayStack<T>::ArrayStack(const size_t size) noexcept(false)
{
	stack_.SetLength(size);
}

template<class T>
inline ArrayStack<T>::ArrayStack(const ArrayStack & copy) noexcept(false)
{
	*this = copy;
}

template<class T>
inline ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack & rhs) noexcept(false)
{
	stack_.~Array();
	stack_ = rhs.stack_;
	numItems_ = rhs.numItems_;
	return *this;
}

template<class T>
inline ArrayStack<T>::ArrayStack(ArrayStack && copy) noexcept
{
	*this = copy;
	copy.numItems_ = 0;
}

template<class T>
inline ArrayStack<T>& ArrayStack<T>::operator=(ArrayStack && rhs) noexcept
{
	stack_.~Array();
	stack_ = std::move(rhs.stack_);
	numItems_ = rhs.numItems_;
	rhs.numItems_ = 0;
	return *this;
}

template<class T>
inline bool ArrayStack<T>::IsEmpty() const noexcept
{
	return numItems_ == 0;
}

template<class T>
inline bool ArrayStack<T>::IsFull() const noexcept
{
	return numItems_ == stack_.GetLength();
}

template<class T>
inline size_t ArrayStack<T>::Size() const noexcept
{
	return numItems_;
}

template<class T>
inline void ArrayStack<T>::Push(const T & data) noexcept(false)
{
	if (numItems_ >= stack_.GetLength())
		throw AdtException("Overflow");
	stack_[numItems_++] = data;
}

template<class T>
inline T ArrayStack<T>::Pop() noexcept(false)
{
	if (numItems_ <= 0)
		throw AdtException("Underflow");
	return stack_[--numItems_];
}

template<class T>
inline T ArrayStack<T>::Peek() const noexcept(false)
{
	if (numItems_ == 0)
		throw AdtException("Stack is empty");
	return stack_[numItems_ - 1];
}

template<class T>
inline void ArrayStack<T>::Clear() noexcept
{
	numItems_ = 0;
}

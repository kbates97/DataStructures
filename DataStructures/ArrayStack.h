
#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include "Array.h"
#include "AdtException.h"

template <class T>
class ArrayStack
{
public:
	ArrayStack(const size_t size_t = 10) noexcept(false);
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

};



#endif    

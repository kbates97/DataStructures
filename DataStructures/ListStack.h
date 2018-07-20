#ifndef LINKEDLISTSTACK_H
#define LINKEDLISTSTACK_H

#include "List.h"
#include "AdtException.h"

template <class T>
class ListStack
{
public:
	ListStack();
	~ListStack() = default;
	ListStack(const ListStack& copy);
	ListStack<T>& operator=(const ListStack& rhs);
	ListStack(ListStack&& copy) noexcept;
	ListStack<T>& operator=(ListStack&& rhs) noexcept;
	void Push(T data) noexcept(false);
	T Pop() noexcept(false);
	const T& Peek() const noexcept(false);
	size_t Size() const;
	bool IsEmpty() const;
	void Clear() noexcept;

private:
	List<T> stack_;
	size_t size_ = 0;

	
	
};



#endif    
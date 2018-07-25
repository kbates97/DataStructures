#ifndef LINKEDLISTSTACK_H
#define LINKEDLISTSTACK_H

#include "List.h"
#include "AdtException.h"

template <class T>
class ListStack
{
public:
	ListStack() = default;
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

template<class T>
inline ListStack<T>::ListStack(const ListStack & copy)
{
	*this = copy;
}

template<class T>
inline ListStack<T>& ListStack<T>::operator=(const ListStack & rhs)
{
	stack_ = rhs.stack_;
	size_ = rhs.size_;
	return *this;
}

template<class T>
inline ListStack<T>::ListStack(ListStack<T>&& copy) noexcept
{
	*this = copy;
	copy.Clear();
}

template<class T>
inline ListStack<T>& ListStack<T>::operator=(ListStack && rhs) noexcept
{
	stack_ = rhs.stack_;
	size_ = rhs.size_;
	rhs.Clear();
	return *this;
}

template<class T>
inline void ListStack<T>::Push(T data) noexcept(false)
{
	stack_.Prepend(data);
	++size_;
}

template<class T>
inline T ListStack<T>::Pop() noexcept(false)
{
	if (size_ == 0)
		throw AdtException("Underflow");
	T data = stack_.First();
	stack_.Extract(data);
	--size_;
	return data;
}

template<class T>
inline const T & ListStack<T>::Peek() const noexcept(false)
{
	return stack_.First();
}

template<class T>
inline size_t ListStack<T>::Size() const
{
	return size_;
}

template<class T>
inline bool ListStack<T>::IsEmpty() const
{
	return size_ == 0;
}

template<class T>
inline void ListStack<T>::Clear() noexcept
{
	size_ = 0;
	stack_.Purge();
}

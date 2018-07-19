#pragma once

#ifndef Node_H
#define Node_H

template<class T>
class Node
{
public:
	T & GetData() noexcept;
	T GetData() const noexcept;
	void SetData(const T& data) noexcept;
protected:
	Node() = default;
	virtual ~Node() = 0;
	Node(const T& data) noexcept;
	Node(const Node<T>& copy) noexcept;
	Node(Node<T>&& copy) noexcept;

	Node<T>& operator=(const Node& rhs) noexcept;
	Node<T>& operator=(Node&& rhs) noexcept;
private:
	T data_;
};

#endif // !Node_H

template<class T>
inline T & Node<T>::GetData() noexcept
{
	return this->data_;
}

template<class T>
inline T Node<T>::GetData() const noexcept
{
	return this->data_;
}

template<class T>
inline void Node<T>::SetData(const T & data) noexcept
{
	this->data_ = data;
}

template<class T>
inline Node<T>::~Node()
{
	
}

template<class T>
inline Node<T>::Node(const T & data) noexcept
{
	this->data_ = data;
}

template<class T>
inline Node<T>::Node(const Node & copy) noexcept
{
	this = copy;
}

template<class T>
inline Node<T>::Node(Node && copy) noexcept
{
	*this = copy;
	copy.~Node();
}

template<class T>
inline Node<T> & Node<T>::operator=(const Node & rhs) noexcept
{
	this->data_ = rhs.data_;
}

template<class T>
inline Node<T> & Node<T>::operator=(Node && rhs) noexcept
{
	this = *rhs;
	rhs.~Node();
}

#pragma once

#ifndef Node_H
#define Node_H

template<class T>
class Node
{
protected:
	Node() = default;
	~Node virtual = 0;
	Node(const T& data) noexcept;
	Node(const Node& copy) noexcept;
	Node(Node&& copy) noexcept;

	Node& operator=(const Node& rhs) noexcept;
	Node& operator=(Node&& rhs) noexcept;
private:
	T data_;
};

#endif // !Node_H

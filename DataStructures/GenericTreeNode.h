#ifndef GENERICTREENODE_H
#define GENERICTREENODE_H

#include "Node.h"
#include <list>

using std::list;
using std::move;

template <class T>
class GenericTreeNode : public Node<T>
{
public:
	explicit GenericTreeNode(const T data, GenericTreeNode<T>* parent = nullptr) noexcept;
	~GenericTreeNode();

	GenericTreeNode(const GenericTreeNode<T> & copy) noexcept;
	GenericTreeNode<T> & operator=(const GenericTreeNode<T> & rhs) noexcept;

	GenericTreeNode(GenericTreeNode<T> && copy) noexcept;
	GenericTreeNode<T> & operator=(GenericTreeNode<T> && rhs) noexcept;


	GenericTreeNode<T>* GetParent() const noexcept;
	void SetParent(GenericTreeNode<T>* parent) noexcept;

	list<GenericTreeNode<T>*> GetChildren() const noexcept;
	void AddChild(GenericTreeNode<T> * const child) noexcept;
	void SetChildren(list<GenericTreeNode<T> *> children) noexcept;

private:
	GenericTreeNode<T>* parent_ = nullptr;
	list<GenericTreeNode<T>*> children_;
};


#endif

template<class T>
inline GenericTreeNode<T>::GenericTreeNode(const T data, GenericTreeNode<T>* parent) noexcept
{
	this->SetData(data);
	parent_ = parent;
}

template<class T>
inline GenericTreeNode<T>::~GenericTreeNode()
{
	parent_ = nullptr;
	children_.clear();
}

template<class T>
inline GenericTreeNode<T>::GenericTreeNode(const GenericTreeNode<T>& copy) noexcept
{
	*this = copy;
}

template<class T>
inline GenericTreeNode<T>& GenericTreeNode<T>::operator=(const GenericTreeNode<T>& rhs) noexcept
{
	this->SetData(rhs.GetData());
	parent_ = rhs.parent_;
	children_ = rhs.children_;

	return *this;
}

template<class T>
inline GenericTreeNode<T>::GenericTreeNode(GenericTreeNode<T>&& copy) noexcept
{
	*this = std::move(copy);
}

template<class T>
inline GenericTreeNode<T>& GenericTreeNode<T>::operator=(GenericTreeNode<T>&& rhs) noexcept
{
	data = std::move(rhs.data_);
	parent_ = rhs.parent_;
	rhs.parent_ = nullptr;
	children_ = std::move(rhs.children_);

	return *this;
}

template<class T>
inline GenericTreeNode<T>* GenericTreeNode<T>::GetParent() const noexcept
{
	return parent_;
}

template<class T>
inline void GenericTreeNode<T>::SetParent(GenericTreeNode<T>* parent) noexcept
{
	parent_ = parent;
}

template<class T>
inline list<GenericTreeNode<T>*> GenericTreeNode<T>::GetChildren() const noexcept
{
	return children_;
}

template<class T>
inline void GenericTreeNode<T>::AddChild(GenericTreeNode<T>* const child) noexcept
{
	children_.push_back(child);
}

template<class T>
inline void GenericTreeNode<T>::SetChildren(list<GenericTreeNode<T>*> children) noexcept
{
	children_ = children;
}

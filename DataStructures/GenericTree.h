#ifndef GENERICTREE_H
#define GENERICTREE_H

#include <functional>
#include "GenericTreeNode.h"
#include <queue>
#include <list>
#include <iterator>
using std::list;
using std::queue;
using std::iterator;
using std::function;
using std::move;

template <class T>
class GenericTree
{
public:
	GenericTree() = default;
	~GenericTree() = default;
	GenericTree(const GenericTree<T>& copy) noexcept;
	GenericTree(GenericTree && copy) noexcept;
	GenericTree<T>& operator=(const GenericTree<T> &rhs);
	GenericTree<T>& operator=(GenericTree&& rhs) noexcept;
	void SetFunction(function<void(const GenericTreeNode<T> * const node)> visit) noexcept { visit_ = visit; }
	void BreadthFirst() noexcept { BreadthFirst_(root_); }
	void PostOrder() noexcept { 
		list<GenericTreeNode<T>*> traversal;
		PostOrder_(root_, traversal); }
	void SetRoot(GenericTreeNode<T>* root) noexcept { root_ = root; }
	GenericTreeNode<T>* GetRoot() const noexcept { return root_; }
	void Clear();

	bool IsEmpty(); //for testing

private:
	GenericTreeNode<T>* root_ = nullptr;
	function<void(const GenericTreeNode<T> * const node)> visit_;
	void BreadthFirst_(GenericTreeNode<T> * node) const;
	void PostOrder_(GenericTreeNode<T> * node, list<GenericTreeNode<T>*> & traversal);
	void copy_(GenericTreeNode<T>* lhsNode, GenericTreeNode<T> *rhsNode);
};

#endif

template<class T>
inline GenericTree<T>::GenericTree(const GenericTree<T>& copy) noexcept
{
	*this = copy;
}

template<class T>
inline GenericTree<T>::GenericTree(GenericTree && copy) noexcept
{
	*this = std::move(copy);
}

template<class T>
inline GenericTree<T>& GenericTree<T>::operator=(const GenericTree<T>& rhs)
{
	Clear();
	root_ = new GenericTreeNode<T>(rhs.root_->GetData());
	copy_(root_, rhs.root_);
	visit_ = rhs.visit_;
	return *this;
}

template<class T>
inline GenericTree<T>& GenericTree<T>::operator=(GenericTree && rhs) noexcept
{
	root_ = rhs.root_;
	rhs.root_ = nullptr;
	visit_ = std::move(rhs.visit_);
	return *this;
}

template<class T>
inline void GenericTree<T>::Clear()
{
	if (root_ != nullptr)
	{
		auto temp = visit_;
		visit_ = [](const GenericTreeNode<T>* const node) {
			delete node;
		};
		PostOrder();
		root_ = nullptr;
		visit_ = temp;
	}
}

template<class T>
inline bool GenericTree<T>::IsEmpty()
{
	return root_ == nullptr;
}

template<class T>
inline void GenericTree<T>::BreadthFirst_(GenericTreeNode<T>* node) const
{
	queue<GenericTreeNode<T> *> que;

	que.push(node);

	while (!que.empty())
	{
		node = que.front();
		que.pop();
		auto children = node->GetChildren();
		for (auto it = children.begin(); it != children.end(); ++it)
		{
			que.push(*it);
		}
		visit_(node);
	}
}

template<class T>
inline void GenericTree<T>::PostOrder_(GenericTreeNode<T>* node, list<GenericTreeNode<T>*>& traversal)
{
	if (!node->GetChildren().empty())
	{
		auto children = node->GetChildren();
		for (auto it = children.begin(); it != children.end(); ++it)
		{
			PostOrder_(*it, traversal);
		}
	}
	visit_(node);
	traversal.push_back(node);
}

template<class T>
inline void GenericTree<T>::copy_(GenericTreeNode<T>* lhsNode, GenericTreeNode<T>* rhsNode)
{
	if (!rhsNode->GetChildren().empty())
	{
		list<GenericTreeNode<T>*> children = rhsNode->GetChildren();
		for (auto it = children.begin(); it != children.end(); ++it)
		{
			lhsNode->AddChild(new GenericTreeNode<T>((*it)->GetData()));
			copy_(lhsNode->GetChildren().back(), *it);
		}
	}
}

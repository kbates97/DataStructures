#ifndef BSTREE_H
#define BSTREE_H

#include "BSTNode.h"
#include "ITree.h"
#include <functional>
#include "ListQueue.h"
#include "AdtException.h"

using std::function;

template <class T, class U>
class BSTree : ITree<T, U>
{
public:
	BSTree() = default;
    ~BSTree();
	BSTree<T,U>(const BSTree<T,U> & copy) noexcept(false);
	BSTree<T,U> & operator=(const BSTree<T,U> &rhs) noexcept(false);
	BSTree<T,U>(BSTree<T,U> && copy) noexcept;
	BSTree<T,U> & operator=(BSTree<T,U> && rhs) noexcept;
	void SetVisitFunction(const function<void(const BSTNode<T,U> * const node)> visit) noexcept;
	void Clear() noexcept override;
	size_t Height() noexcept override;
	void InOrder() const noexcept override;
	void PreOrder() const noexcept override;
	bool IsEmpty() const noexcept override;
	void PostOrder() const noexcept override;
	void BreadthFirst() const noexcept override;
	void Insert(const T item, const U key) noexcept(false) override;
	void Delete(const U& key) noexcept(false) override;
    T Search(const U& key) const noexcept(false) override;
    T& Search(const U& key) noexcept(false) override;
private:
	BSTNode<T,U>* root_ = nullptr;
	function<void(const BSTNode<T,U> * const node)> visit_;

	void InOrder_(const BSTNode<T, U> * const node) const;
	void PreOrder_(const BSTNode<T, U> * const node) const;
	void PostOrder_(const BSTNode<T, U> * const node) const;
	void BreadthFirst_(const BSTNode<T, U> * const node, ListQueue<BSTNode<T, U> *> & queue) const;
	size_t Height_(const BSTNode<T, U> * const node);
	void Insert_(BSTNode<T, U> * node, const T data, const U key);
	T Search_(const BSTNode<T, U> * const node, const U& key) const;
	T& Search_(BSTNode<T, U> * const node, const U& key);
	void FindNodeToDelete_(BSTNode<T, U> * prev, BSTNode<T, U> * current, const U& key);
	void RemoveFromTree_(BSTNode<T, U> * prev, BSTNode<T, U> * current, const U& key);
	void DeleteLeaf_(BSTNode<T, U> * prev, const U& key);
	void DeleteWithRightTree_(BSTNode<T, U> * prev, BSTNode<T, U> * current, const U& key);
	void DeleteWithLeftTree_(BSTNode<T, U> * prev, BSTNode<T, U> * current, const U& key);
	void DeleteWithLeftAndRightTree_(BSTNode<T, U>* deleteNode, BSTNode<T, U> * prev, BSTNode<T, U> * current, const U& key);
};
#endif

template<class T, class U>
inline BSTree<T, U>::~BSTree()
{
	Clear();
}

template<class T, class U>
inline BSTree<T, U>& BSTree<T, U>::operator=(const BSTree<T, U>& rhs) noexcept(false)
{
	Clear();
	visit_ = [&](const BSTNode<T, U> * const node)
	{
		Insert(node->GetData(), node->GetKey());
	};
	ListQueue<BSTNode<T, U>*> queue;
	BreadthFirst_(rhs.root_, queue);
	visit_ = rhs.visit_;
	return *this;
}

template<class T, class U>
inline BSTree<T, U>& BSTree<T, U>::operator=(BSTree<T, U>&& rhs) noexcept
{
	Clear();
	root_ = rhs.root_;
	visit_ = std::move(rhs.visit_);
	rhs.root_ = nullptr;
	return *this;
}

template<class T, class U>
inline void BSTree<T, U>::SetVisitFunction(const function<void(const BSTNode<T, U>*const node)> visit) noexcept
{
	visit_ = visit;
}

template<class T, class U>
inline void BSTree<T, U>::Delete(const U & key) noexcept(false)
{
	FindNodeToDelete_(root_, root_, key);
}

template<class T, class U>
inline T BSTree<T, U>::Search(const U & key) const noexcept(false)
{
	return Search_(root_, key);
}

template<class T, class U>
inline T & BSTree<T, U>::Search(const U & key) noexcept(false)
{
	return Search_(root_, key);
}

template<class T, class U>
inline BSTree<T, U>::BSTree(const BSTree<T, U>& copy) noexcept(false)
{
	*this = copy;
}

template<class T, class U>
inline BSTree<T, U>::BSTree(BSTree<T, U>&& copy) noexcept
{
	*this = std::move(copy);
}

template<class T, class U>
inline void BSTree<T, U>::Clear() noexcept
{
	if (root_ != nullptr)
	{
		auto temp = visit_;
		visit_ = [](const BSTNode<T, U>* const node) {
			delete node;
		};
		PostOrder();
		root_ = nullptr;
		visit_ = temp;
	}
}

template<class T, class U>
inline bool BSTree<T, U>::IsEmpty() const noexcept
{
	return root_ == nullptr;
}

template<class T, class  U>
inline size_t BSTree<T, U>::Height() noexcept
{
	size_t height = Height_(root_) - 1;
	return height;
}

template<class T, class U>
inline void BSTree<T, U>::InOrder() const noexcept
{
	InOrder_(root_);
}

template<class T, class U>
inline void BSTree<T, U>::PreOrder() const noexcept
{
	PreOrder_(root_);
}

template<class T, class U>
inline void BSTree<T, U>::PostOrder() const noexcept
{
	PostOrder_(root_);
}

template<class T, class U>
inline void BSTree<T, U>::BreadthFirst() const noexcept
{
	ListQueue<BSTNode<T, U> *> queue;
	BreadthFirst_(root_, queue);
}

template<class T, class U>
inline void BSTree<T, U>::Insert(const T item, const U key) noexcept(false)
{
	Insert_(root_, item, key);
}

template<class T, class U>
inline void BSTree<T, U>::InOrder_(const BSTNode<T, U>* const node) const
{
	if (node->GetLeft() != nullptr)
		InOrder_(node->GetLeft());
	visit_(node);
	if (node->GetRight() != nullptr)
		InOrder_(node->GetRight());
}

template<class T, class U>
inline void BSTree<T, U>::PreOrder_(const BSTNode<T, U>* const node) const
{
	visit_(node);
	if (node->GetLeft())
		PreOrder_(node->GetLeft());
	if (node->GetRight() != nullptr)
		PreOrder_(node->GetRight());
}

template<class T, class U>
inline void BSTree<T, U>::PostOrder_(const BSTNode<T, U>* const node) const
{
	if (node->GetLeft() != nullptr)
	{
		PostOrder_(node->GetLeft());
	}
	if (node->GetRight() != nullptr)
	{
		PostOrder_(node->GetRight());
	}
	visit_(node);
}

template<class T, class U>
inline void BSTree<T, U>::BreadthFirst_(const BSTNode<T, U>* const node, ListQueue<BSTNode<T, U> *> & queue) const
{
	if (node->GetLeft() != nullptr)
		queue.Enqueue(node->GetLeft());
	if (node->GetRight() != nullptr)
		queue.Enqueue(node->GetRight());
	visit_(node);
	if (! queue.IsEmpty())
		BreadthFirst_(queue.Dequeue(), queue);
}

template<class T, class U>
inline size_t BSTree<T, U>::Height_(const BSTNode<T, U>* const node)
{
	if (node == nullptr)
		return 0;
	int left_height = Height_(node->GetLeft());
	int right_height = Height_(node->GetRight());
	if (left_height > right_height)
		return left_height + 1;
	else
		return right_height + 1;
}

template<class T, class U>
inline void BSTree<T, U>::Insert_(BSTNode<T, U>* node, const T data, const U key)
{
	if (root_ == nullptr)
		root_ = new BSTNode<T, U>(data, key);
	else
	{
		if (key < node->GetKey())
			if (node->GetLeft() == nullptr)
				node->SetLeft(new BSTNode<T, U>(data, key));
			else
				Insert_(node->GetLeft(), data, key);
		else
			if (node->GetRight() == nullptr)
				node->SetRight(new BSTNode<T, U>(data, key));
			else
				Insert_(node->GetRight(), data, key);
	}
}

template<class T, class U>
inline T BSTree<T, U>::Search_(const BSTNode<T, U>* const node, const U & key) const
{
	if (node == nullptr)
		throw AdtException("Not Found");
	if (key < node->GetKey())
		Search_(node->GetLeft(), key);
	else if (key > node->GetKey())
		Search_(node->GetRight(), key);
	else return node->GetData();
}

template<class T, class U>
inline T& BSTree<T, U>::Search_(BSTNode<T, U>* const node, const U & key)
{
	if (node == nullptr)
		throw AdtException("Not Found");
	if (key < node->GetKey())
		Search_(node->GetLeft(), key);
	else if (key > node->GetKey())
		Search_(node->GetRight(), key);
	else return node->GetData();
}

template<class T, class U>
inline void BSTree<T, U>::FindNodeToDelete_(BSTNode<T, U>* prev, BSTNode<T, U>* current, const U & key)
{
	if (current == nullptr)
		throw AdtException("Not Found");
	if (key > current->GetKey())
		FindNodeToDelete_(current, current->GetRight(), key);
	else if (key < current->GetKey())
		FindNodeToDelete_(current, current->GetLeft(), key);
	else
		RemoveFromTree_(prev, current, key);
}

template<class T, class U>
inline void BSTree<T, U>::RemoveFromTree_(BSTNode<T, U>* prev, BSTNode<T, U>* current, const U & key)
{
	if (current->GetLeft() == nullptr && current->GetRight() == nullptr)
		DeleteLeaf_(prev, key);
	else if (current->GetLeft() == nullptr)
		DeleteWithRightTree_(prev, current, key);
	else if (current->GetRight() == nullptr)
		DeleteWithLeftTree_(prev, current, key);
	else
		DeleteWithLeftAndRightTree_(current, current, current->GetLeft(), key);
}

template<class T, class U>
inline void BSTree<T, U>::DeleteLeaf_(BSTNode<T, U>* prev, const U & key)
{
	if (prev == root_ && prev->GetKey() == key)
	{
		delete prev;
		root_ = nullptr;
	}
	else if (key > prev->GetKey())
	{
		delete prev->GetRight();
		prev->SetRight(nullptr);
	}
	else
	{
		delete prev->GetLeft();
		prev->SetLeft(nullptr);
	}
}

template<class T, class U>
inline void BSTree<T, U>::DeleteWithRightTree_(BSTNode<T, U>* prev, BSTNode<T, U>* current, const U & key)
{
	if (key > prev->GetKey())
		prev->SetRight(current->GetRight());
	else
		prev->SetLeft(current->GetRight());
	delete current;
}

template<class T, class U>
inline void BSTree<T, U>::DeleteWithLeftTree_(BSTNode<T, U>* prev, BSTNode<T, U>* current, const U & key)
{
	if (key > prev->GetKey())
		prev->SetRight(current->GetLeft());
	else
		prev->SetLeft(current->GetLeft());
	delete current;
}

template<class T, class U>
inline void BSTree<T, U>::DeleteWithLeftAndRightTree_(BSTNode<T, U>* deleteNode, BSTNode<T, U>* prev, BSTNode<T, U>* current, const U & key)
{
	if (current->GetRight() != nullptr)
		DeleteWithLeftAndRightTree_(deleteNode, current, current->GetRight(), key);
	else
	{
		deleteNode->SetData(current->GetData());
		deleteNode->SetKey(current->GetKey());
		RemoveFromTree_(prev, current, current->GetKey());
	}
}

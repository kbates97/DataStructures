#ifndef AVLTREE_H
#define AVLTREE_H

#include <functional>

#include "AVLNode.h"
#include "ITree.h"
#include "ListQueue.h"
#include "AdtException.h"

using std::function;

template <class T, class U>
class AVLTree : ITree<T, U>
{
public:
	AVLTree() = default;
	AVLTree(const AVLTree& copy) noexcept(false);
	~AVLTree();
	AVLTree<T, U> & operator=(const AVLTree<T, U>& rhs) noexcept(false);
	AVLTree(AVLTree && copy) noexcept;
	AVLTree<T, U> & operator=(AVLTree<T, U> && rhs) noexcept(false);
	void SetVisitFunction(function<void(const AVLNode<T, U> * const node)> visit);
	void Clear() noexcept override;
	size_t Height() noexcept override;
	bool IsEmpty() const noexcept override;
	void InOrder() const noexcept override;
	void PreOrder() const noexcept override;
	void PostOrder() const noexcept override;
	void BreadthFirst() const noexcept override;
	void Insert(const T data, const U key) noexcept(false) override;
	void Delete(const U& key) noexcept(false) override;
    T Search(const U& key) const noexcept(false) override;
    T& Search(const U& key) noexcept(false) override;
private:
	AVLNode<T, U>* root_ = nullptr;
	function<void(const AVLNode<T, U> * const node)> visit_;

	size_t Height_(const AVLNode<T, U> * const node);
	void InOrder_(const AVLNode<T, U> * const node) const;
	void PreOrder_(const AVLNode<T, U> * const node) const;
	void PostOrder_(const AVLNode<T, U> * const node) const;
	void BreadthFirst_(const AVLNode<T, U> * const node, ListQueue<AVLNode<T, U> *> & queue) const;
	AVLNode<T, U>* Insert_(AVLNode<T, U> * node, AVLNode<T, U> * newNode);
	AVLNode<T, U>* Delete_(AVLNode<T, U> * node, const U key);
	T Search_(const AVLNode<T, U> * const node, const U& key) const;
	T& Search_(AVLNode<T, U> * const node, const U& key);

	AVLNode<T, U>* Balance_(AVLNode<T, U> * node);
	AVLNode<T, U>* BalanceRight_(AVLNode<T, U> * node);
	AVLNode<T, U>* BalanceLeft_(AVLNode<T, U> * node);
	AVLNode<T, U>* RotateRight_(AVLNode<T, U> * node);
	AVLNode<T, U>* RotateLeft_(AVLNode<T, U> * node);
	AVLNode<T, U>* DeleteWithLeftAndRight_(AVLNode<T, U> * node);
};
#endif

template<class T, class U>
inline AVLTree<T, U>::AVLTree(const AVLTree & copy) noexcept(false)
{
	*this = copy;
}

template<class T, class U>
inline AVLTree<T, U>::~AVLTree()
{
	Clear();
}

template<class T, class U>
inline AVLTree<T, U>& AVLTree<T, U>::operator=(const AVLTree<T, U>& rhs) noexcept(false)
{
	visit_ = [&](const AVLNode<T, U> * const node)
	{
		Insert(node->GetData(), node->GetKey());
	};
	Clear();
	if (rhs.root_ != nullptr)
	{
		ListQueue<AVLNode<T, U>*> queue;
		BreadthFirst_(rhs.root_, queue);
	}
	return *this;
}

template<class T, class U>
inline AVLTree<T, U>::AVLTree(AVLTree && copy) noexcept
{
	*this = std::move(copy);
}

template<class T, class U>
inline AVLTree<T, U>& AVLTree<T, U>::operator=(AVLTree<T, U>&& rhs) noexcept(false)
{
	root_ = rhs.root_;
	rhs.root_ = nullptr;
	visit_ = std::move(rhs.visit_);
}

template<class T, class U>
inline void AVLTree<T, U>::SetVisitFunction(function<void(const AVLNode<T, U>*const node)> visit)
{
	visit_ = visit;
}

template<class T, class U>
inline void AVLTree<T, U>::Insert(const T data, const U key) noexcept(false)
{
	AVLNode<T, U>* newNode = new AVLNode<T, U>(data, key);
	root_ = Insert_(root_, newNode);
}

template<class T, class U>
inline void AVLTree<T, U>::Delete(const U& key) noexcept(false)
{
	root_ = Delete_(root_, key);
}

template<class T, class U>
inline T AVLTree<T, U>::Search(const U & key) const noexcept(false)
{
	return Search_(root_, key);
}

template<class T, class U>
inline T & AVLTree<T, U>::Search(const U & key) noexcept(false)
{
	return Search_(root_, key);
}

template<class T, class U>
inline void AVLTree<T, U>::Clear() noexcept
{
	if (root_ != nullptr)
	{
		auto temp = visit_;
		visit_ = [](const AVLNode<T, U>* const node) {
			delete node;
		};
		PostOrder();
		root_ = nullptr;
		visit_ = temp;
	}
}

template<class T, class  U>
inline size_t AVLTree<T, U>::Height() noexcept
{
	size_t height = Height_(root_) - 1;
	return height;
}

template<class T, class U>
inline bool AVLTree<T, U>::IsEmpty() const noexcept
{
	return root_ == nullptr;
}

template<class T, class U>
inline void AVLTree<T, U>::InOrder() const noexcept
{
	InOrder_(root_);
}

template<class T, class U>
inline void AVLTree<T, U>::PreOrder() const noexcept
{
	PreOrder_(root_);
}

template<class T, class U>
inline void AVLTree<T, U>::PostOrder() const noexcept
{
	PostOrder_(root_);
}

template<class T, class U>
inline void AVLTree<T, U>::BreadthFirst() const noexcept
{
	if (root_ == nullptr)
		return;
	ListQueue<AVLNode<T, U> *> queue;
	BreadthFirst_(root_, queue);
}

template<class T, class U>
inline size_t AVLTree<T, U>::Height_(const AVLNode<T, U>* const node)
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
inline void AVLTree<T, U>::InOrder_(const AVLNode<T, U>* const node) const
{
	if (node->GetLeft() != nullptr)
		InOrder_(node->GetLeft());
	visit_(node);
	if (node->GetRight() != nullptr)
		InOrder_(node->GetRight());
}

template<class T, class U>
inline void AVLTree<T, U>::PreOrder_(const AVLNode<T, U>* const node) const
{
	visit_(node);
	if (node->GetLeft())
		PreOrder_(node->GetLeft());
	if (node->GetRight() != nullptr)
		PreOrder_(node->GetRight());
}

template<class T, class U>
inline void AVLTree<T, U>::PostOrder_(const AVLNode<T, U>* const node) const
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
inline void AVLTree<T, U>::BreadthFirst_(const AVLNode<T, U>* const node, ListQueue<AVLNode<T, U> *> & queue) const
{
	if (node->GetLeft() != nullptr)
		queue.Enqueue(node->GetLeft());
	if (node->GetRight() != nullptr)
		queue.Enqueue(node->GetRight());
	visit_(node);
	if (!queue.IsEmpty())
		BreadthFirst_(queue.Dequeue(), queue);
}

template<class T, class U>
inline AVLNode<T, U>* AVLTree<T, U>::Insert_(AVLNode<T, U>* node, AVLNode<T, U>* newNode)
{
	if (node == nullptr)
		return newNode;
	if (newNode->GetData() > node->GetData())
		node->SetRight(Insert_(node->GetRight(), newNode));
	else
		node->SetLeft(Insert_(node->GetLeft(), newNode));
	return Balance_(node);
}

template<class T, class U>
inline AVLNode<T, U>* AVLTree<T, U>::Delete_(AVLNode<T, U>* node, const U key)
{
	if (node == nullptr)
		AdtException("Not Found");
	else if (key > node->GetKey())
		node->SetRight(Delete_(node->GetRight(), key));
	else if (key < node->GetKey())
		node->SetRight(Delete_(node->GetLeft(), key));
	else
	{
		if (node->GetLeft() == nullptr && node->GetRight() == nullptr)
		{
			delete node;
			return nullptr;
		}
		else if (node->GetLeft() == nullptr)
			return node->GetRight();
		else if (node->GetRight() == nullptr)
			return node->GetLeft();
		else
			return DeleteWithLeftAndRight_(node);
	}
	return Balance_(node);
}

template<class T, class U>
inline T AVLTree<T, U>::Search_(const AVLNode<T, U>* const node, const U & key) const
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
inline T& AVLTree<T, U>::Search_(AVLNode<T, U>* const node, const U & key)
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
inline AVLNode<T, U>* AVLTree<T, U>::Balance_(AVLNode<T, U>* node)
{
	int H = Height_(node->GetLeft()) - Height_(node->GetRight());
	if (H > 1)
		return BalanceLeft_(node);
	else if (H < -1)
		return BalanceRight_(node);
	else
		return node;
}

template<class T, class U>
inline AVLNode<T, U>* AVLTree<T, U>::BalanceRight_(AVLNode<T, U>* node)
{
	if (Height_(node->GetRight()->GetRight()) < Height_(node->GetRight()->GetLeft()))
		return RotateLeft_(RotateRight_(node->GetRight()));
	else
		return RotateLeft_(node);
}

template<class T, class U>
inline AVLNode<T, U>* AVLTree<T, U>::BalanceLeft_(AVLNode<T, U>* node)
{
	if (Height_(node->GetLeft()->GetRight()) > Height_(node->GetLeft()->GetLeft()))
		return RotateRight_(RotateLeft_(node->GetRight()));
	else
		return RotateRight_(node);
}

template<class T, class U>
inline AVLNode<T, U>* AVLTree<T, U>::RotateRight_(AVLNode<T, U>* node)
{
	AVLNode<T, U>* root = node->GetLeft();
	node->SetLeft(root->GetRight());
	root->SetRight(node);
	return root;
}

template<class T, class U>
inline AVLNode<T, U>* AVLTree<T, U>::RotateLeft_(AVLNode<T, U>* node)
{
	AVLNode<T, U>* root = node->GetRight();
	node->SetRight(root->GetLeft());
	root->SetLeft(node);
	return root;
}

template<class T, class U>
inline AVLNode<T, U>* AVLTree<T, U>::DeleteWithLeftAndRight_(AVLNode<T, U>* node)
{
	AVLNode<T, U> *root = node;
	node = node->GetLeft();
	while (node->GetRight() != nullptr)
		node = node->GetRight();
	root->SetData(node->GetData());
	root->SetKey(node->GetKey());
	Delete_(root->GetLeft(), node->GetKey());
	return root;
}

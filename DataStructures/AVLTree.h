#ifndef AVLTREE_H
#define AVLTREE_H

#include <functional>

#include "AVLNode.h"
#include "ITree.h"

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
	void SetVisitFunction(function<void(const AvlNode<T, U> * const node)> visit);
	void Clear() noexcept override;
	size_t Height() noexcept override;
	bool IsEmpty() const noexcept override;
	void InOrder() const noexcept override;
	void PreOrder() const noexcept override;
	void PostOrder() const noexcept override;
	void BreadthFirst() const noexcept override;
	void Insert(const T data) noexcept(false) override;
	void Delete(const T data) noexcept(false) override;
    T Search(const U& key) const noexcept(false) override;
    T& Search(const U& key) noexcept(false) override;
private:
	AvlNode<T, U>* root_ = nullptr;
	function<void(const AvlNode<T, U> * const node)> visit_;
};
#endif

#ifndef BSTREE_H
#define BSTREE_H

#include "BSTNode.h"
#include "ITree.h"
#include <functional>

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
	void SetVisitFunction(function<void(const BStNode<T,U> * const node)> visit) noexcept;
	void Clear() noexcept override;
	size_t  Height() noexcept override;
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
	BstNode<T,U>* root_ = nullptr;
	function<void(const BstNode<T,U> * const node)> visit_;
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
	root_ = rhs.root_;
	visit_ = rhs.visit_;
	return *this;
}

template<class T, class U>
inline BSTree<T, U>& BSTree<T, U>::operator=(BSTree<T, U>&& rhs) noexcept
{
	root_ = rhs.root;
	visit_ = std::move(visit);
	rhs.root_ = nullptr;
	return *this;
}

template<class T, class U>
inline void BSTree<T, U>::SetVisitFunction(function<void(const BStNode<T, U>*const node)> visit) noexcept
{
	visit_ = visit;
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

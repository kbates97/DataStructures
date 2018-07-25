#ifndef BSTNode_H
#define BSTNode_H

#include "PairNode.h"

template <class T, class U>
class BSTNode : public PairNode<T, U>
{
public:
    BSTNode(const T data, const U key, BSTNode<T,U>* right = nullptr, BSTNode<T, U>* left = nullptr);
	~BSTNode() = default;
	BSTNode(const BSTNode<T,U> & copy) noexcept;
	BSTNode<T, U>& operator=(const BSTNode<T,U> & rhs) noexcept;
	BSTNode(BSTNode<T, U> && copy) noexcept;
	BSTNode<T, U>& operator=(BSTNode<T,U> && rhs) noexcept;
	BSTNode<T, U> * GetLeft() const noexcept;
	BSTNode<T, U> * GetRight() const noexcept;
	void SetLeft(BSTNode<T,U> * const left) noexcept;
	void SetRight(BSTNode<T,U> * const right) noexcept;

private:
    BSTNode<T, U>* left_ = nullptr;
    BSTNode<T, U>* right_ = nullptr;
};

#endif

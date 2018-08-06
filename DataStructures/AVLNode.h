#ifndef AVLNODE_H
#define AVLNODE_H

#include "PairNode.h"

template <class T, class U>
class AVLNode : public PairNode<T, U>
{
public:
	explicit AVLNode<T,U>(const T data, const U key, AVLNode<T,U> * left = nullptr, AVLNode<T,U> * right = nullptr) noexcept;
	~AVLNode() = default;
	AVLNode<T,U>(const AVLNode<T,U> & copy) noexcept;
	AVLNode<T,U> & operator=(const AVLNode<T,U> & rhs);
	AVLNode<T,U>(AVLNode<T,U> && copy) noexcept;
	AVLNode<T,U> & operator=(AVLNode<T,U> && rhs) noexcept;
	AVLNode<T,U> * GetLeft() const noexcept;
	AVLNode<T,U> * GetRight() const noexcept;
	void SetLeft(AVLNode<T,U> * const left) noexcept;
	void SetRight(AVLNode<T,U> * const right) noexcept;
private:
	AVLNode<T,U> * left_ = nullptr;
	AVLNode<T,U> * right_ = nullptr;
};
#endif

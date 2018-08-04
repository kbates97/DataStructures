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

template<class T, class U>
inline BSTNode<T, U>::BSTNode(const T data, const U key, BSTNode<T, U>* right, BSTNode<T, U>* left)
{
	SetKey(key);
	SetData(data);
	right_ = right;
	left_ = left;
}

template<class T, class U>
inline BSTNode<T, U>::BSTNode(const BSTNode<T, U>& copy) noexcept
{
	*this = copy;
}

template<class T, class U>
inline BSTNode<T, U>& BSTNode<T, U>::operator=(const BSTNode<T, U>& rhs) noexcept
{
	if (this != &rhs)
	{
		data_ = rhs.data_;
		key_ = rhs.key_;
		left_ = rhs.left_;
		right_ = rhs.right_;
	}
	return *this;
}

template<class T, class U>
inline BSTNode<T, U>::BSTNode(BSTNode<T, U>&& copy) noexcept
{
	*this = std::move(copy);
}

template<class T, class U>
inline BSTNode<T, U>& BSTNode<T, U>::operator=(BSTNode<T, U>&& rhs) noexcept
{
	data_ = std::move(rhs.data_);
	key_ = std::move(rhs.key_);
	left_ = rhs.left_;
	right_ = rhs.right_;
	rhs.left_ = nullptr;
	rhs.right_ = nullptr;
	return *this;
}

template<class T, class U>
inline BSTNode<T, U>* BSTNode<T, U>::GetLeft() const noexcept
{
	return left_;
}

template<class T, class U>
inline BSTNode<T, U>* BSTNode<T, U>::GetRight() const noexcept
{
	return right_;
}

template<class T, class U>
inline void BSTNode<T, U>::SetLeft(BSTNode<T, U>* const left) noexcept
{
	left_ = left;
}

template<class T, class U>
inline void BSTNode<T, U>::SetRight(BSTNode<T, U>* const right) noexcept
{
	right_ = right;
}

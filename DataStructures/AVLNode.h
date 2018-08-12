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

template<class T, class U>
inline AVLNode<T, U>::AVLNode(const T data, const U key, AVLNode<T, U>* left, AVLNode<T, U>* right) noexcept
{
	SetData(data);
	SetKey(key);
	left_ = left;
	right_ = right;
}

template<class T, class U>
inline AVLNode<T, U>::AVLNode(const AVLNode<T, U>& copy) noexcept
{
	*this = copy;
}

template<class T, class U>
inline AVLNode<T, U>::AVLNode(AVLNode<T, U>&& copy) noexcept
{
	*this = std::move(copy);
}

template<class T, class U>
inline AVLNode<T, U>& AVLNode<T, U>::operator=(const AVLNode<T, U>& rhs)
{
	SetData(rhs.GetData());
	SetKey(rhs.GetKey());
	left_ = rhs.left_;
	right = rhs.right_;
	return *this;
}

template<class T, class U>
inline AVLNode<T, U>& AVLNode<T, U>::operator=(AVLNode<T, U>&& rhs) noexcept
{
	SetData(std::move(rhs.data_));
	key_ = std::move(rhs.key_);
	left = rhs.left_;
	right = rhs.right_;
	rhs.left_ = nullptr;
	rhs.right_ = nullptr;
}

template<class T, class U>
inline AVLNode<T, U>* AVLNode<T, U>::GetLeft() const noexcept
{
	return left_;
}

template<class T, class U>
inline AVLNode<T, U>* AVLNode<T, U>::GetRight() const noexcept
{
	return right_;
}

template<class T, class U>
inline void AVLNode<T, U>::SetLeft(AVLNode<T, U>* const left) noexcept
{
	left_ = left;
}

template<class T, class U>
inline void AVLNode<T, U>::SetRight(AVLNode<T, U>* const right) noexcept
{
	right_ = right;
}

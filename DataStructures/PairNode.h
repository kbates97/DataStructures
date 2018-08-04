#ifndef PAIRNODE_H
#define PAIRNODE_H

#include "Node.h"

template <class T, class U>
class PairNode : public Node<T>
{
public:
    U GetKey() const noexcept;
    U& GetKey() noexcept;
    void SetKey(const U key) noexcept(false);
	virtual ~PairNode() = 0;
protected:
	PairNode() = default;
	PairNode(const T data, const U key) noexcept;
	PairNode(const PairNode& copy) noexcept;
	PairNode(PairNode&& copy) noexcept;
	PairNode& operator=(const PairNode& rhs) noexcept;
	PairNode& operator=(PairNode&& rhs) noexcept;
private:
	U key_;
};

#endif

template<class T, class U>
inline U PairNode<T, U>::GetKey() const noexcept
{
	return key_;
}

template<class T, class U>
inline U & PairNode<T, U>::GetKey() noexcept
{
	return key_;
}

template<class T, class U>
inline void PairNode<T, U>::SetKey(const U key) noexcept(false)
{
	key_ = key;
}

template<class T, class U>
inline PairNode<T, U>::~PairNode()
{

}

template<class T, class U>
inline PairNode<T, U>::PairNode(const T data, const U key) noexcept
{
	data_ = data;
	key_ = key;
}

template<class T, class U>
inline PairNode<T, U>::PairNode(const PairNode & copy) noexcept
{
	*this = copy;
}

template<class T, class U>
inline PairNode<T, U>::PairNode(PairNode && copy) noexcept
{
	*this = std::move(copy);
}

template<class T, class U>
inline PairNode<T, U> & PairNode<T, U>::operator=(const PairNode & rhs) noexcept
{
	if (this != &rhs)
	{
		data_ = rhs.data_;
		key_ = rhs.key_;
	}
	return *this;
}

template<class T, class U>
inline PairNode<T, U> & PairNode<T, U>::operator=(PairNode && rhs) noexcept
{
	data_ = std::move(rhs.data_);
	key_ = std::move(rhs.key_);

	return *this;
}

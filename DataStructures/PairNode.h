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
	PairNode() = delete;
	PairNode(const T data, const U key) noexcept;
	PairNode(const PairNode& copy) noexcept;
	PairNode(PairNode&& copy) noexcept;
	PairNode& operator=(const PairNode& rhs) noexcept;
	PairNode& operator=(PairNode&& rhs) noexcept;
private:
	U key_;
};

#endif
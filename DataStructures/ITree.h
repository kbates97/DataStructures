#ifndef ITREE_H
#define ITREE_H

template <class T, class U>
class ITree
{
public:
    virtual ~ITree() = default;
    virtual void Clear() noexcept = 0;
    virtual size_t Height() noexcept = 0;
	virtual bool IsEmpty() const noexcept = 0;
    virtual void InOrder() const noexcept = 0;
    virtual void PreOrder() const noexcept = 0;
    virtual void PostOrder() const noexcept = 0;
	virtual void BreadthFirst() const noexcept = 0;
	virtual void Insert(const T data, const U key) noexcept(false);
	virtual void Delete(const U key) noexcept(false) = 0;
    virtual T Search(const U& key) const noexcept(false) = 0;
    virtual T& Search(const U& key) noexcept(false) = 0;
};
#endif

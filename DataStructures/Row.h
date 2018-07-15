#ifndef ROW_H
#define ROW_H

#include "IRow.h"

template <class T>
class IArray2D;

template <class T>
class Row : IRow<T>
{
public:
	Row(const IArray2D<T>& array, const int row);
	~Row() = default;
	T& operator[](const int col) override;
	T operator[](const int col) const override;

private:
	const IArray2D<T>& array2D_;
	const int row_;
};

#endif

template<class T>
inline Row<T>::Row(const IArray2D<T>& array, const int row) :array2D_(array), row_(row) {}

template<class T>
inline T& Row<T>::operator[](const int col)
{
	return const_cast<IArray2D<T>&>(array2D_).Select(row_, col);
}

template<class T>
inline T Row<T>::operator[](const int col) const
{
	return array2D_.Select(row_, col);
}
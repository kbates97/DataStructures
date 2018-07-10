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
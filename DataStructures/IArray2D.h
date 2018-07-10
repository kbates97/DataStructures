#ifndef IARRAY2D
#define IARRAY2D
#include "Row.h"

template <class T>
class Row;

template <class T>
class IArray2D
{
public:
	virtual ~IArray2D() = default;
	virtual T Select(int row, int column) const noexcept(false) = 0;
	virtual T& Select(int row, int column) noexcept(false) = 0;

	virtual Row<T> operator[](int row) const = 0;
	virtual Row<T> operator[](int row) = 0;

	virtual int GetRow() const noexcept = 0;
	virtual int GetColumn() const noexcept = 0;

	virtual void SetRow(int rows) noexcept(false) = 0;
	virtual void SetColumn(int columns) noexcept(false) = 0;
};

#endif

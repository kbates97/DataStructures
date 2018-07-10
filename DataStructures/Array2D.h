#ifndef ARRAY2D_H
#define ARRAY2D_H

#include "IArray2D.h"
#include "AdtException.h"
#include "Array.h"

template <class T>
class Array2D : public IArray2D<T>
{
public:
	Array2D() = default;
	Array2D(const int row, const int col) noexcept(false);
	Array2D(const Array2D& copy);
	~Array2D() = default;
	Array2D<T>& operator=(const Array2D& rhs);
	Array2D(Array2D<T>&& array) noexcept;
	Array2D<T>& operator=(Array2D<T>&& rhs) noexcept;

	T Select(const int row, const int column) const noexcept(false) override;
	T& Select(const int row, const int column) noexcept(false) override;

	Row<T> operator[](const int row) const override;
	Row<T> operator[](const int row) override;

	int GetRow() const noexcept override;
	int GetColumn() const noexcept override;

	void SetRow(const int rows) noexcept(false) override;
	void SetColumn(const int columns) noexcept(false) override;

private:
	Array<T> storage_;
	int row_ = 1;
	int col_ = 1;
};

#endif

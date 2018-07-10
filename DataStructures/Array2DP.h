#ifndef ARRAY2DP_h
#define ARRAY2DP_H

#include "AdtException.h"

#include "IArray2D.h"
#include "IRow.h"

template <class T>
class Array2DP : IArray2D<T>
{
public:
	explicit Array2DP();
	explicit Array2DP(int row, int col);

	~Array2DP();

	explicit Array2DP(const Array2DP& copy);
	Array2DP<T>& operator=(const Array2DP& rhs);

	Array2DP(Array2DP&& array) noexcept;
	Array2DP<T>& operator=(Array2DP&& array) noexcept;

	T Select(int row, int column) const override;
	T& Select(int row, int column) override;

	Row<T> operator[](int row) const override;
	Row<T> operator[](int row) override;

	int GetRow() const noexcept override;
	int GetColumn() const noexcept override;

	void SetRow(int rows) noexcept(false) override;
	void SetColumn(int columns) noexcept(false) override;

private:
	T** storage_ = nullptr;
	int row_ = 0;
	int col_ = 0;
};

#endif
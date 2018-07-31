#ifndef ARRAY2D_H
#define ARRAY2D_H

#include "IArray2D.h"
#include "AdtException.h"
#include "Array.h"

template <class T>
class Array2D : public IArray2D<T>
{
public:
	Array2D();
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


template<class T>
inline Array2D<T>::Array2D()
{
	storage_ = Array<T>(row_*col_, 0);
}

template<class T>
inline Array2D<T>::Array2D(const int row, const int col)
{
	row_ = row;
	col_ = col;
	if (row * col > 0)
		storage_ = Array<T>(row*col, 0);
}

template<class T>
inline Array2D<T>::Array2D(const Array2D<T>& copy)
{
	*this = copy;
}

template<class T>
inline Array2D<T>& Array2D<T>::operator=(const Array2D& rhs)
{
	if (this != &rhs)
	{
		/*storage_.SetLength(rhs.GetRow() * rhs.GetColumn());
		for (size_t i = 0; i < rhs.GetRow(); i++) {
			for (size_t k = 0; k < rhs.GetColumn(); k++) {
				storage_[(int)i*rhs.GetColumn() + (int)k] = rhs[(int)i][(int)k];
			}
		}*/
		storage_ = rhs.storage_;
		row_ = rhs.GetRow();
		col_ = rhs.GetColumn();
	}
	return *this;
}

template<class T>
inline Array2D<T>::Array2D(Array2D<T>&& array) noexcept
{
	storage_ = std::move(array.storage_);
	row_ = array.row_;
	col_ = array.col_;
	array.row_ = 0;
	array.col_ = 0;
}

template<class T>
inline Array2D<T>& Array2D<T>::operator=(Array2D<T>&& rhs) noexcept
{
	row_ = rhs.row_;
	col_ = rhs.col_;
	storage_ = std::move(rhs.storage_);
	rhs.row_ = 0;
	rhs.col_ = 0;

	return *this;
}

template<class T>
inline T& Array2D<T>::Select(const int row, const int column)
{
	if (row > row_-1 || column > col_-1 || row < 0 || column < 0)
		throw AdtException("Out of bounds");
	return storage_[row * col_ + column];
}

template<class T>
inline T Array2D<T>::Select(const int row, const int column) const
{
	if (row > row_ - 1 || column > col_ - 1 || row < 0 || column < 0)
		throw AdtException("Out of bounds");
	return storage_[row * col_ + column];
}

template <class T>
inline Row<T> Array2D<T>::operator[](int index) 
{
	return Row<T>(*this, index);
}

template <class T>
inline Row<T> Array2D<T>::operator[](int index) const 
{
	return Row<T>(*this, index);
}

template<class T>
inline int Array2D<T>::GetRow() const noexcept
{
	return row_;
}

template<class T>
inline int Array2D<T>::GetColumn() const noexcept
{
	return col_;
}

template<class T>
inline void Array2D<T>::SetRow(const int rows)
{
	Array<T> temp(rows * col_);
	if (rows < row_)
	{
		for (size_t i = 0; i < rows * col_; ++i)
		{
			temp[i] = storage_[i];
		}
	}
	else
	{
		for (size_t i = 0; i < row_ * col_; ++i)
		{
			temp[i] = storage_[i];
		}
	}
	storage_ = temp;
	row_ = rows;
}

template<class T>
inline void Array2D<T>::SetColumn(const int columns)
{
	Array2D<T> temp(row_, columns);
	if (columns < col_)
	{
		for (size_t i = 0; i < row_; ++i)
		{
			for (size_t k = 0; k < columns; ++k)
			{
				temp.Select(i, k) = Select(i, k);
			}
		}
	}
	else
	{
		for (size_t i = 0; i < row_ * col_; ++i)
		{
			temp.storage_[i] = storage_[i];
		}
	}
	*this = temp;
	col_ = columns;
}
#endif

#ifndef ARRAY2DP_h
#define ARRAY2DP_H

#include "AdtException.h"

#include "IArray2D.h"
#include "IRow.h"

template <class T>
class Array2DP : IArray2D<T>
{
public:
	explicit Array2DP() = default;
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

template<class T>
inline Array2DP<T>::Array2DP(int row, int col)
{
	row_ = row;
	col_ = col;
	if (row * col > 0)
		storage_ = new T*[row];
	for (size_t i = 0; i < row; ++i)
	{
		storage_[i] = new T[col];
	}
}

template<class T>
inline Array2DP<T>::~Array2DP()
{
	for (size_t i = 0; i < row_; ++i)
	{
		delete storage_[i];
	}
	delete [] storage_;
}

template<class T>
inline Array2DP<T>::Array2DP(const Array2DP & copy)
{
	T** temp = new T*[copy.row_];
	for (size_t i = 0; i < copy.row_; ++i)
	{
		temp[i] = new T[copy.col_];
	}
	for (size_t i = 0; i < copy.row_; ++i)
	{
		for (size_t k = 0; k < copy.col_; ++k)
		{
			temp[i][k] = copy.storage_[i][k];
		}
	}
	this->row_ = copy.row_;
	this->col_ = copy.col_;
	delete this->storage_;
	this->storage_ = temp;
}

template<class T>
inline Array2DP<T>& Array2DP<T>::operator=(const Array2DP & rhs)
{
	T** temp = new T*[rhs.row_];
	for (size_t i = 0; i < rhs.row_; ++i)
	{
		temp[i] = new T[rhs.col_];
	}
	for (size_t i = 0; i < rhs.row_; ++i)
	{
		for (size_t k = 0; k < rhs.col_; ++k)
		{
			temp[i][k] = rhs.storage_[i][k];
		}
	}
	delete this->storage_;
	this->storage_ = temp;
	this->row_ = rhs.row_;
	this->col_ = rhs.col_;

	return *this;
}

template<class T>
inline Array2DP<T>::Array2DP(Array2DP && array) noexcept
{
	this->row_ = array.row_;
	this->col_ = array.col_;
	this->storage_ = array.storage_;
	array.row_ = 0;
	array.col_ = 0;
	array.storage_ = nullptr;
}

template<class T>
inline Array2DP<T>& Array2DP<T>::operator=(Array2DP && array) noexcept
{
	this->row_ = array.row_;
	this->col_ = array.col_;
	this->storage_ = array.storage_;
	array.row_ = 0;
	array.col_ = 0;
	array.storage_ = nullptr;
	
	return *this;
}

template<class T>
inline T Array2DP<T>::Select(int row, int column) const
{
	if (row > row_ - 1 || column > col_ - 1 || row < 0 || column < 0)
		throw AdtException("Out of bounds");
	return storage_[row][column];
}

template<class T>
inline T & Array2DP<T>::Select(int row, int column)
{
	if (row > row_ - 1 || column > col_ - 1 || row < 0 || column < 0)
		throw AdtException("Out of bounds");
	return storage_[row][column];
}

template<class T>
inline Row<T> Array2DP<T>::operator[](int row) const
{
	return Row<T>(*this, row);
}

template<class T>
inline Row<T> Array2DP<T>::operator[](int row)
{
	return Row<T>(*this, row);
}

template<class T>
inline void Array2DP<T>::SetRow(int rows) noexcept(false)
{
	T** temp = new T*[rows];
	for (size_t i = 0; i < rows; ++i)
	{
		temp[i] = new T[col_];
	}
	if (this->row_ < rows)
	{
		for (size_t i = 0; i < this->row_; i++)
		{
			for (size_t k = 0; k < this->col_; k++)
			{
				temp[i][k] = this->storage_[i][k];
			}
		}
	}
	else
	{
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t k = 0; k < this->col_; k++)
			{
				temp[i][k] = this->storage_[i][k];
			}
		}
	}
	delete this->storage_;
	this->storage_ = temp;
	this->row_ = rows;
}

template<class T>
inline void Array2DP<T>::SetColumn(int columns) noexcept(false)
{
	T** temp = new T*[row_];
	for (size_t i = 0; i < this->row_; ++i)
	{
		temp[i] = new T[columns];
	}
	if (this->col_ < columns)
	{
		for (size_t i = 0; i < this->row_; i++)
		{
			for (size_t k = 0; k < this->col_; k++)
			{
				temp[i][k] = this->storage_[i][k];
			}
		}
	}
	else
	{
		for (size_t i = 0; i < this->row_; i++)
		{
			for (size_t k = 0; k < columns; k++)
			{
				temp[i][k] = this->storage_[i][k];
			}
		}
	}
	delete this->storage_;
	this->storage_ = temp;
	this->col_ = columns;
}

template<class T>
inline int Array2DP<T>::GetRow() const noexcept
{
	return this->row_;
}

template<class T>
inline int Array2DP<T>::GetColumn() const noexcept
{
	return this->col_;
}
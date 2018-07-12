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
	//Array2D(Array2D<T>&& array) noexcept;
	//Array2D<T>& operator=(Array2D<T>&& rhs) noexcept;

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
inline Array2D<T>::Array2D(const int row, const int col)
{
	row_ = row;
	col_ = col;
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
		storage_.setLength(rhs.getRow() * rhs.getColumn());
		for (size_t i = 0; i < rhs.getRow(); i++) {
			for (size_t k = 0; k < rhs.getColumn(); k++) {
				storage_[(int)i*rhs.getColumn() + (int)k] = rhs[(int)i][(int)k];
			}
		}
	}
	row_ = rhs.getRow();
	col_ = rhs.getColumn();
	return *this;
}

template<class T>
inline T& Array2D<T>::Select(const int row, const int column)
{
	return storage_[row * col_ + col];
}

template<class T>
inline T Array2D<T>::Select(const int row, const int column) const
{
	return storage_[row * col_ + col];
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

//template<class T>
//inline int Array2D<T>::GetRow() const
//{
//	return row_;
//}

template<class T>
inline void Array2D<T>::SetRow(const int rows)
{
	row_ = rows;
}

template<class T>
inline void Array2D<T>::SetColumn(const int columns)
{
	col_ = columns;
}
#endif

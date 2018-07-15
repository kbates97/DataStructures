#ifndef ARRAY_H
#define ARRAY_H

#include "AdtException.h"

template <class T>
class Array
{
public:
	explicit Array() = default;
	~Array();
	explicit Array(size_t length, int start_index = 0) noexcept(false);

	explicit Array(const int * c_array, const size_t size);

	Array(const Array<T>& array) noexcept(false);

	Array<T>& operator=(const Array<T>& rhs) noexcept(false);

	explicit Array(Array<T>&& array) noexcept;
	Array<T>& operator=(Array<T>&& rhs) noexcept(false);

	T& operator[](int index) noexcept(false);
	T operator[](int index) const noexcept(false);

	int GetStartIndex() const noexcept;
	size_t GetLength() const noexcept;

	void SetStartIndex(const int start_index) noexcept(false);
	void SetLength(const int length) noexcept(false);

	Array<T>& Merge(const Array<T>& array);

private:
	size_t length_ = 0;
	T* storage_ = nullptr;
	int start_index_ = 0;
};



template<class T>
inline Array<T>::~Array()
{
	delete[] storage_;
}

template<class T>
inline Array<T>::Array(size_t length, int start_index)
{
	length_ = length;
	start_index_ = start_index;
	if (length_ > 0)
		storage_ = new T[length];
}

template<class T>
inline Array<T>::Array(const int * c_array, const size_t size)
{
	if (size > 0)
	{
		storage_ = new T[size];
	}
	length_ = size;
	for (size_t i = 0; i < size; ++i)
	{
		storage_[i] = c_array[i];
	}
}

template<class T>
inline Array<T>::Array(const Array<T>& array)
{
	*this = array;
}

template<class T>
inline Array<T>& Array<T>::operator=(const Array<T>& rhs)
{
	storage_ = new T[rhs.length_];
	for (int i = 0; i < rhs.length_; i++)
	{
		storage_[i] = rhs.storage_[i];
	}
	length_ = rhs.length_;
	start_index_ = rhs.start_index_;
	return *this;
}

template<class T>
inline Array<T>::Array(Array<T>&& array) noexcept
{
	length_ = array.length_;
	storage_ = array.storage_;
	array.length_ = 0;
	array.storage_ = nullptr;
}

template<class T>
inline Array<T>& Array<T>::operator=(Array<T>&& rhs) noexcept(false)
{
	length_ = rhs.length_;
	storage_ = rhs.storage_;
	rhs.length_ = 0;
	rhs.storage_ = nullptr;

	return *this;
}

template<class T>
inline T& Array<T>::operator[](int index)
{
	if (length_ < index - start_index_)
		throw AdtException("Out of bounds");
	index -= start_index_;
	return storage_[index];
}

template<class T>
inline T Array<T>::operator[](int index) const
{
	index -= start_index_;
	return storage_[index];
}

template<class T>
inline int Array<T>::GetStartIndex() const noexcept
{
	return start_index_;
}

template<class T>
inline size_t Array<T>::GetLength() const noexcept
{
	return length_;
}

template <class T>
inline void Array<T>::SetStartIndex(const int start_index)
{
	start_index_ = start_index;
}

template<class T>
inline void Array<T>::SetLength(const int length)
{
	T* temp = new T[length];
	if (length_ < length)
	{
		for (int i = 0; i < length_; ++i)
		{
			temp[i] = storage_[i];
		}
	}
	else
	{
		for (int i = 0; i < length; ++i)
		{
			temp[i] = storage_[i];
		}
	}
	delete storage_;
	storage_ = temp;
	length_ = length;
}

template<class T>
inline Array<T>& Array<T>::Merge(const Array<T>& array)
{
	T* temp = new T[length_ + array.length_];
	if (length_ < array.length_)
	{
		for (size_t i = 0; i < length_; ++i)
		{
			temp[i * 2] = storage_[i];
			temp[i * 2 + 1] = array.storage_[i];
		}
		for (size_t i = length_; i < array.length_; ++i)
		{
			temp[i] = array.storage_[i];
		}
	}
	else
	{
		for (size_t i = 0; i < array.length_; ++i)
		{
			temp[i * 2] = storage_[i];
			temp[i * 2 + 1] = array.storage_[i];
		}
		for (size_t i = array.length_; i < length_; ++i)
		{
			temp[i] = storage_[i];
		}
	}
	delete storage_;
	storage_ = temp;
	length_ += array.length_;

	return *this;
}
#endif

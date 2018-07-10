#ifndef ARRAY_H
#define ARRAY_H

#include "AdtException.h"

template <class T>
class Array
{
public:
	explicit Array();
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

private:
	size_t length_ = 0;
	T* storage_ = nullptr;
	int start_index_ = 0;
};


#endif

#ifndef PAIR_H
#define PAIR_H

#include "AdtException.h"

#include <ostream>
#include <string>

using std::string;
using std::ostream;
using std::endl;
using std::bad_alloc;

template <class K, class V>
class Pair
{
public:
	Pair() = default;
	explicit Pair(const K key, const V value) noexcept(false);
	Pair(const Pair & copy) noexcept(false);
	~Pair();
	Pair<K, V> & operator=(const Pair<K, V> & rhs) noexcept(false);
	explicit Pair(Pair<K, V>&& pair) noexcept;
	Pair<K, V>& operator=(Pair<K, V> && rhs) noexcept(false);
	bool operator==(const Pair & rhs) noexcept;
	bool operator==(const Pair & rhs) const noexcept;
	K GetKey() noexcept;
	K GetKey() const noexcept;
	V GetValue() noexcept;
	V GetValue() const noexcept;
	void SetKey(const K & new_key) noexcept(false);
	void SetValue(const V & new_value) noexcept(false);

	friend ostream & operator<<(ostream & stream, const Pair<K, V> & pair);

private:
	K * key_ = nullptr;
	V * value_ = nullptr;
};



template<class K, class V>
inline Pair<K, V>::Pair(const K key, const V value) noexcept(false)
{
	try
	{
		key_ = new K(key);
		value_ = new V(value);
	}
	catch (bad_alloc bad_alloc)
	{
		throw AdtException(bad_alloc.what());
	}
}

template<class K, class V>
inline Pair<K, V>::Pair(const Pair & copy) noexcept(false)
{
	if (this != &copy)
		*this = copy;
}

template<class K, class V>
inline Pair<K, V>::~Pair()
{
	if (key_ != nullptr) delete key_;
	if (value_ != nullptr) delete value_;
}

template<class K, class V>
inline Pair<K, V>& Pair<K, V>::operator=(const Pair<K, V>& rhs) noexcept(false)
{
	if (this != &rhs)
	{
		if (key_ != nullptr) delete key_;
		if (value_ != nullptr) delete value_;

		try
		{
			key_ = new K(rhs.GetKey());
			value_ = new V(rhs.GetValue());
		}
		catch (bad_alloc bad_alloc)
		{
			throw AdtException(bad_alloc.what());
		}
	}

	return *this;
}

template<class K, class V>
inline Pair<K, V>::Pair(Pair<K, V>&& pair) noexcept
{
	if (this != &pair)
	{
		*this = std::move(pair);
	}
}

template<class K, class V>
inline Pair<K, V>& Pair<K, V>::operator=(Pair<K, V>&& rhs) noexcept(false)
{
	if (this != &rhs)

	{
		if (key_ != nullptr) delete key_;
		if (value_ != nullptr) delete value_;

		key_ = new K(rhs.key_);
		value_ = new V(rhs.value_);

		if (rhs.key_ != nullptr) delete rhs.key_;
		if (rhs.value_ != nullptr) delete rhs.value_;
		rhs.key_ = nullptr;
		rhs.value_ = nullptr;
	}
	return *this;
}

template<class K, class V>
inline bool Pair<K, V>::operator==(const Pair & rhs) noexcept
{
	return key_ == rhs.key_ && value_ == rhs.value_;
}

#endif

template<class K, class V>
inline K Pair<K, V>::GetKey() noexcept
{
	return *key_;
}

template<class K, class V>
inline K Pair<K, V>::GetKey() const noexcept
{
	return *key_;
}

template<class K, class V>
inline V Pair<K, V>::GetValue() noexcept
{
	return *value_;
}

template<class K, class V>
inline V Pair<K, V>::GetValue() const noexcept
{
	return *value_;
}

template<class K, class V>
ostream & operator<<(ostream & stream, const Pair<K, V>& pair)
{
	stream << "Key: " << pair.key_ << " Value: " << pair.value_ << endl;
	return stream;
}
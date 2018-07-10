#ifndef PAIR_H
#define PAIR_H

#include "AdtException.h"

#include <ostream>
#include <string>

using std::string;
using std::ostream;
using std::endl;

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

#endif
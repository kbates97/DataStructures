#ifndef ARC_H
#define ARC_H

#include "Vertex.h"

using std::move;

namespace Graphs
{
	template <class V, class E>
	class Vertex;

	template <class V, class E>
	class Arc
	{
	public:
		Arc<V, E>(Vertex<V, E> *destination, E data, int weight);

		Arc(const Arc<V, E> & other);
		Arc<V, E>& operator=(const Arc<V, E>& rhs);

		Arc(Arc<V, E> && other) noexcept;
		Arc<V, E>& operator=(Arc<V, E> && rhs) noexcept;

		Vertex<V, E> *GetDestination();
		int GetWeight() const;
		E GetData() const;
		E GetData();
		bool operator==(const Arc<V, E>& rhs);

	private:
		Vertex<V, E> *destination_ = nullptr;
		E data_;
		int weight_ = 0;
	};

	template<class V, class E>
	inline Arc<V, E>::Arc(Vertex<V, E>* destination, E data, int weight)
	{
		destination_ = destination;
		data_ = data;
		weight_ = weight;
	}

	template<class V, class E>
	inline Arc<V, E>::Arc(const Arc<V, E>& other)
	{
		*this = other;
	}

	template<class V, class E>
	inline Arc<V, E>& Arc<V, E>::operator=(const Arc<V, E>& rhs)
	{
		destination_ = rhs.destination_;
		data_ = rhs.data_;
		weight_ = rhs.weight_;
		return *this;
	}

	template<class V, class E>
	inline Arc<V, E>::Arc(Arc<V, E>&& other) noexcept
	{
		*this = std::move(other);
	}

	template<class V, class E>
	inline Arc<V, E>& Arc<V, E>::operator=(Arc<V, E>&& rhs) noexcept
	{
		destination_ = rhs.destination_;
		rhs.destination_ = nullptr;
		data_ = std::move(rhs.data_);
		weight_ = rhs.weight_;
		rhs.weight_ = 0;
		return *this;
	}

	template<class V, class E>
	inline Vertex<V, E>* Arc<V, E>::GetDestination()
	{
		return destination_;
	}

	template<class V, class E>
	inline int Arc<V, E>::GetWeight() const
	{
		return weight_;
	}

	template<class V, class E>
	inline E Arc<V, E>::GetData() const
	{
		return data_;
	}

	template<class V, class E>
	inline E Arc<V, E>::GetData()
	{
		return data_;
	}

	template<class V, class E>
	inline bool Arc<V, E>::operator==(const Arc<V, E>& rhs)
	{
		return data_ == rhs.data_;
	}

}

#endif

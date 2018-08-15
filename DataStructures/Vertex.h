#ifndef VERTEX_H
#define VERTEX_H

#include <list>
#include "Arc.h"

using std::list;
using std::move;

namespace Graphs
{
	template <class V, class E>
	class Vertex
	{
	public:
		explicit Vertex(V data);

		Vertex(const Vertex<V, E> & other);
		Vertex<V, E>& operator=(const Vertex<V, E> & rhs);

		Vertex(Vertex<V, E> && other) noexcept;
		Vertex<V, E>& operator=(Vertex<V, E> && rhs) noexcept;

		V GetData();
		V GetData() const;
		void IncrementInDegree();
		void IncrementOutDegree();
		void DecrementInDegree();
		void DecrementOutDegree();
		void AddArc(Arc<V, E> arc);
		list<Arc<V, E>> GetArcs();
		void RemoveArc(E arc_data);
		void SetProcessed(bool processed);
		bool GetProcessed() const;

	private:
		V data_;
		int in_degree_ = 0;
		int out_degree_ = 0;
		bool processed_ = false;
		list<Arc<V, E>> arcs_;
	};

	template<class V, class E>
	inline Vertex<V, E>::Vertex(V data)
	{
		data_ = data;
	}

	template<class V, class E>
	inline Vertex<V, E>::Vertex(const Vertex<V, E>& other)
	{
		*this = other;
	}

	template<class V, class E>
	inline Vertex<V, E>& Vertex<V, E>::operator=(const Vertex<V, E>& rhs)
	{
		data_ = rhs.data_;
		in_degree_ = rhs.in_degree_;
		out_degree_ = rhs.out_degree_;
		arcs_ = rhs.arcs_;
		return *this;
	}

	template<class V, class E>
	inline Vertex<V, E>::Vertex(Vertex<V, E>&& other) noexcept
	{
		*this = std::move(other);
	}

	template<class V, class E>
	inline Vertex<V, E>& Vertex<V, E>::operator=(Vertex<V, E>&& rhs) noexcept
	{
		data_ = std::move(rhs.data_);
		in_degree_ = rhs.in_degree_;
		rhs.in_degree_ = 0;
		out_degree_ = rhs.out_degree_;
		rhs.out_degree_ = 0;
		arcs_ = std::move(rhs.arcs_);
		return *this;
	}

	template<class V, class E>
	inline V Vertex<V, E>::GetData()
	{
		return data_;
	}

	template<class V, class E>
	inline V Vertex<V, E>::GetData() const
	{
		return data_;
	}

	template<class V, class E>
	inline void Vertex<V, E>::IncrementInDegree()
	{
		++in_degree_;
	}

	template<class V, class E>
	inline void Vertex<V, E>::IncrementOutDegree()
	{
		++out_degree_;
	}

	template<class V, class E>
	inline void Vertex<V, E>::DecrementInDegree()
	{
		--in_degree_;
	}

	template<class V, class E>
	inline void Vertex<V, E>::DecrementOutDegree()
	{
		--out_degree_;
	}

	template<class V, class E>
	inline void Vertex<V, E>::AddArc(Arc<V, E> arc)
	{
		arcs_.push_back(arc);
		arc.GetDestination()->IncrementInDegree();
		IncrementOutDegree();
	}

	template<class V, class E>
	inline list<Arc<V, E>> Vertex<V, E>::GetArcs()
	{
		return arcs_;
	}

	template<class V, class E>
	inline void Vertex<V, E>::RemoveArc(E arc_data)
	{
		auto it = arcs_.begin();
		while (it->GetData() != arc_data && it != arcs_.end())
			++it;
		if (it == arcs_.end())
			throw AdtException("Not Found");
		DecrementOutDegree();
		it->GetDestination()->DecrementInDegree();
		arcs_.erase(it);
	}

	template<class V, class E>
	inline void Vertex<V, E>::SetProcessed(bool processed)
	{
		processed_ = processed;
	}

	template<class V, class E>
	inline bool Vertex<V, E>::GetProcessed() const
	{
		return processed_;
	}

}

#endif



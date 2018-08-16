#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <iterator>
#include <queue>
#include <stack>
#include <functional>
#include "Vertex.h"
#include "AdtException.h"

using std::string;
using std::cout;
using std::list;
using std::iterator;
using std::endl;
using std::queue;
using std::stack;
using std::function;
using std::move;

namespace Graphs 
{
	template <class V, class E>
	class Graph
	{
	public:
		Graph() = default;
		~Graph() = default;
		
		Graph(const Graph & other);
		Graph<V, E> & operator=(const Graph& rhs);

		Graph(Graph && other) noexcept;
		Graph<V, E> & operator=(Graph && rhs) noexcept;

		void SetAllVertexesToNotProcessed();
		void InsertVertex(V data);
		void DeleteVertex(V data);
		void InsertArc(V from, V to, E arc_data, int arc_weight);
		void DeleteArc(V from, V to, E arc);
		void DepthFirst(V start_vertex);
		void BreadthFirst(V start_vertex);
		bool IsEmpty();
		size_t GetNumberOfVertices();
		typename list<Vertex<V, E>>::iterator GetMapBeginIterator();
		typename list<Vertex<V, E>>::iterator GetMapEndIterator();
		void SetFunction(function<void(Vertex<V, E> & vertex)> visit);

		void PrintGraph();
		Vertex<V, E> * GetVertex(V data);

	private:
		list<Vertex<V, E>> vertices_;
		function<void(Vertex<V, E> & vertex)> visit_;
	};

	template<class V, class E>
	inline Graph<V, E>::Graph(const Graph & other)
	{
		*this = other;
	}

	template<class V, class E>
	inline Graph<V, E>& Graph<V, E>::operator=(const Graph & rhs)
	{
		vertices_ = rhs.vertices_;
		for (auto vert_it = vertices_.begin(); vert_it != vertices_.end(); ++vert_it)
		{
			list<Arc<V, E>> arcs = vert_it->GetArcs();
			for (auto arc_it = arcs.begin(); arc_it != arcs.end(); ++arc_it)
			{
				vert_it->AddArc(Arc<V, E>(GetVertex(arc_it->GetDestination()->GetData()), arc_it->GetData(), arc_it->GetWeight()));
				vert_it->RemoveArc(arc_it->GetData());
			}
		}
		visit_ = rhs.visit_;
		return *this;
	}

	template<class V, class E>
	inline Graph<V, E>::Graph(Graph && other) noexcept
	{
		*this = std::move(other);
	}

	template<class V, class E>
	inline Graph<V, E>& Graph<V, E>::operator=(Graph && rhs) noexcept
	{
		vertices_ = std::move(rhs.vertices_);
		visit_ = std::move(rhs.visit_);
		return *this;
	}

	template<class V, class E>
	inline void Graph<V, E>::SetAllVertexesToNotProcessed()
	{
		for (auto it = vertices_.begin(); it != vertices_.end(); ++it)
			it->SetProcessed(false);
	}

	template<class V, class E>
	inline void Graph<V, E>::InsertVertex(V data)
	{
		auto it = GetMapBeginIterator();
		while (it != GetMapEndIterator() && it->GetData() != data)
			++it;
		if (it == GetMapEndIterator())
			vertices_.push_back(Vertex<V, E>(data));
	}

	template<class V, class E>
	inline void Graph<V, E>::DeleteVertex(V data)
	{
		auto vertex = GetVertex(data);
		list<Arc<V, E>> arcs = vertex->GetArcs();
		for (auto arc_it = arcs.begin(); arc_it != arcs.end(); ++arc_it)
		{
			arc_it->GetDestination()->RemoveArc(arc_it->GetData());
		}
		auto it = GetMapBeginIterator();
		while (it->GetData() != data)
			++it;
		vertices_.erase(it);
	}

	template<class V, class E>
	inline void Graph<V, E>::InsertArc(V from, V to, E arc_data, int arc_weight)
	{
		auto vertex_from = GetVertex(from);
		auto vertix_to = GetVertex(to);
		vertex_from->AddArc(Arc<V, E>(vertix_to, arc_data, arc_weight));
		vertix_to->AddArc(Arc<V, E>(vertex_from, arc_data, arc_weight));
	}

	template<class V, class E>
	inline void Graph<V, E>::DeleteArc(V from, V to, E arc)
	{
		auto vertex_from = GetVertex(from);
		auto vertex_to = GetVertex(to);
		vertex_from->RemoveArc(arc);
		vertex_to->RemoveArc(arc);
	}

	template<class V, class E>
	inline void Graph<V, E>::DepthFirst(V start_vertex)
	{
		SetAllVertexesToNotProcessed();
		stack<Vertex<V, E>*> depth_stack;
		depth_stack.push(GetVertex(start_vertex));
		GetVertex(start_vertex)->SetProcessed(true);
		while (!depth_stack.empty())
		{
			Vertex<V, E>* iterator = depth_stack.top();
			depth_stack.pop();
			visit_(*iterator);
			list<Arc<V, E>> arcs = iterator->GetArcs();
			for (auto it = arcs.begin(); it != arcs.end(); ++it)
			{
				if (!it->GetDestination()->GetProcessed())
				{
					depth_stack.push(it->GetDestination());
					it->GetDestination()->SetProcessed(true);
				}
			}
		}
	}

	template<class V, class E>
	inline void Graph<V, E>::BreadthFirst(V start_vertex)
	{
		SetAllVertexesToNotProcessed();
		queue<Vertex<V, E>*> breadth_queue;
		breadth_queue.push(GetVertex(start_vertex));
		GetVertex(start_vertex)->SetProcessed(true);
		while (!breadth_queue.empty())
		{
			Vertex<V, E>* iterator = breadth_queue.front();
			breadth_queue.pop();
			visit_(*iterator);
			list<Arc<V, E>> arcs = iterator->GetArcs();
			for (auto it = arcs.begin(); it != arcs.end(); ++it)
			{
				if (!it->GetDestination()->GetProcessed())
				{
					breadth_queue.push(it->GetDestination());
					it->GetDestination()->SetProcessed(true);
				}
			}
		}
	}

	template<class V, class E>
	inline bool Graph<V, E>::IsEmpty()
	{
		return vertices_.empty();
	}

	template<class V, class E>
	inline size_t Graph<V, E>::GetNumberOfVertices()
	{
		size_t size = 0;
		for (auto it = vertices_.begin(); it != vertices_.end(); ++it)
			++size;
		return size;
	}

	template<class V, class E>
	inline typename list<Vertex<V, E>>::iterator Graph<V, E>::GetMapBeginIterator()
	{
		return vertices_.begin();
	}

	template<class V, class E>
	inline typename list<Vertex<V, E>>::iterator Graph<V, E>::GetMapEndIterator()
	{
		return vertices_.end();
	}

	template<class V, class E>
	inline void Graph<V, E>::SetFunction(function<void(Vertex<V, E>&vertex)> visit)
	{
		visit_ = visit;
	}

	template<class V, class E>
	inline void Graph<V, E>::PrintGraph()
	{
		auto visit = visit_;
		visit_ = [](Vertex<V, E> & vertex)
		{
			cout << vertex.GetData() << ", ";
		};
		BreadthFirst(vertices_.begin()->GetData());
		visit_ = visit;
	}

	template<class V, class E>
	inline Vertex<V, E>* Graph<V, E>::GetVertex(V data)
	{
		auto it = GetMapBeginIterator();
		while (it->GetData() != data && it != GetMapEndIterator())
			++it;
		if (it->GetData() != data)
			throw AdtException("Not Found");
		return &*it;
	}

}
#endif
